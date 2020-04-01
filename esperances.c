#include <math.h>
#include <stdio.h>

#include "jeu.h"
#include "regles.h"
#include "esperances.h"
#include "combinaisons.h"


int esperance(Configuration *c, int lancer[])
{
    if (nombre_des(lancer) == 0)
        return 0;

    int nombreDes = nombre_des(lancer);
    double esperanceGain = 0, esperancePerte = 0;

    // si on perd, on perd notre score
    esperancePerte -= c->score * probaRien(nombreDes, c->faceCombi);
    // si on rejoue, on gagne en moyenne ESPERANCE_GAIN de notre nouveau lancer
    esperanceGain += ESPERANCE_GAIN * probaRelancer(nombreDes, c->faceCombi);

    // Espérance de lancers unitaires de VALEUR_EX1 ou VALEUR_EX2
    for (int j = 1; j <= nombreDes && j <= 2; j++)
    {
        // Si absence de combinaison de SCORE_EX1, on calcule l'esperance d'avoir unitairement j VALEUR_EX1
        esperanceGain += j * (c->faceCombi != SCORE_EX1) * SCORE_EX1 * probaCombinValeurDe(nombreDes, j);
        // Si absence de combinaison de SCORE_EX2, on calcule l'esperance d'avoir unitairement j VALEUR_EX2
        esperanceGain += j * (c->faceCombi != SCORE_EX2) * SCORE_EX2 * probaCombinValeurDe(nombreDes, j);
    }


    // Espérance de complétion de combinaisons préexistantes
    for (int j = 1; j <= nombreDes && j <= 3; j++)
    {
        // Si combinaison de SCORE_EX1, on calcule l'esperance d'améliorer la combinaison de j dés
        if (c->faceCombi == VALEUR_EX1)
            esperanceGain +=
            (SCORE_COMBINE_EX(c->faceCombi, occurrences_de(c->des, c->faceCombi) + j)
            - SCORE_COMBINE_EX(c->faceCombi, occurrences_de(c->des, c->faceCombi)))
            * probaCombinValeurDe(nombreDes, j);
        // Si combinaison d'autre chose, on calcule l'esperance d'améliorer la combinaison de j dés
        if (c->faceCombi > VALEUR_EX1)
            esperanceGain +=
            (SCORE_COMBINE(c->faceCombi, occurrences_de(c->des, c->faceCombi) + j)
            - SCORE_COMBINE(c->faceCombi, occurrences_de(c->des, c->faceCombi)))
            * probaCombinValeurDe(nombreDes, j);
    }

    // Espérance d'une nouvelle combinaison de j dés en tenant compte de combinaisons préexistantes
    if (nombreDes >= 3)
    {
        int totalScore = SCORE_COMBINE_EX(VALEUR_EX1, 3);
        // Si absence de combinaison, ou pour toutes les autres valeurs sans combinaison
        // on calcul l'espérance d'en avoir une pour chaque valeur de dé
        for(int i = 2; i <= TYPE_DES; i++)
            totalScore += SCORE_COMBINE(i, 3);
        esperanceGain += totalScore * probaCombinValeurDe(nombreDes, 3);
    }

    // Espérance d'une nouvelle combinaison de j dés
    for (int j = 4; j <= nombreDes; j++)
    {
        int totalScore = SCORE_COMBINE_EX(VALEUR_EX1, j);
        for(int i = 2; i <= TYPE_DES; i++)
            totalScore += SCORE_COMBINE(i, j);
        esperanceGain += totalScore * probaCombinValeurDe(nombreDes, j);
    }

    // Espérance de cas spéciaux dans le cas d'un lancer de NOMBRE_DES dés
    if (nombreDes == NOMBRE_DES)
    {
        // Calculer l'espérance de faire une suite
        esperanceGain += SCORE_SUITE * probaSuite();
        // Calculer l'esperance que le premier lancer (et seuelement le premier) conduise à un échec
        esperancePerte += (c->score == 0) * SCORE_ECHEC * probaRien(nombreDes, 0);
        // Espérance d'une combinaison de 6 dés
    }

    return esperanceGain + esperancePerte;
}


double probaGain(int nbDesLancer, int faceCombi)
{
    if (faceCombi == 0 || VALEURS_POS(faceCombi)) // Si on n'a pas de combinaison de côté ou une combinaison de VALEURS_POS
        // gain = avoir au moins une VALEURS_POS OU que des VALEURS_POS, mais avec une combinaison
        return probaUneValPos(nbDesLancer) + probaCombin(nbDesLancer, 3, 0);
    else // Si on a une combinaison de VALEURS_NEG de côté
        return
        // gain = avoir au moins une VALEURS_POS ou une VALEURS_NEG menant à une combinaison
        (1 - pow((double) (NB_VAL_NEG - 1) / (double) TYPE_DES, (double) nbDesLancer))
        // OU avoir une combinaison de VALEURS_NEG avec une valeur différente de celle avec combinaison
        + probaCombin(nbDesLancer, 3, 1) * (NB_VAL_NEG - 1) / NOMBRE_DES;
}

double probaRien(int nbDesLancer, int faceCombi)
{
    if (faceCombi == 0 || VALEURS_POS(faceCombi)) // Si on n'a pas de combinaison de côté ou une combinaison de VALEURS_POS
        // perte = avoir aucune VALEUR_POS ET ne pas avoir de combinaison de VALEUR_NEG
        return probaPasDeValPos(nbDesLancer) - probaCombin(nbDesLancer, 3, 0);
    else // Si on a une combinaison de VALEURS_NEG de côté
        return
        // perte = n'avoir aucune VALEURS_POS ou une VALEURS_NEG menant à une combinaison
        pow((double) (NB_VAL_NEG - 1) / (double) TYPE_DES, (double) nbDesLancer)
        // ET ne pas avoir une combinaison de VALEURS_NEG avec une valeur différente de celle avec combinaison
        - probaCombin(nbDesLancer, 3, 1) * (NB_VAL_NEG - 1) / NOMBRE_DES;
}


double probaPasDeValPos(int nbDesLancer)
{
    return pow((double) NB_VAL_NEG / (double) TYPE_DES, (double) nbDesLancer);
}

double probaUneValPos(int nbDesLancer)
{
    return 1.0 - probaPasDeValPos(nbDesLancer);
}


double probaNePasRelancer(int nbDesLancer, int faceCombi)
{
    if (nbDesLancer == 1)
        return pow((double) (NB_VAL_NEG - VALEURS_NEG(faceCombi)) / (double) TYPE_DES, (double) nbDesLancer);
    else
        return probaRien(nbDesLancer, faceCombi)
        + probaGain(nbDesLancer, faceCombi) * probaNePasRelancer(nbDesLancer - 1, faceCombi);
}

double probaRelancer(int nbDesLancer, int faceCombi)
{
    return 1 - probaNePasRelancer(nbDesLancer, faceCombi);
}


double denombreLancer(int nbDesLancer)
{
    return pow((double) TYPE_DES, (double) nbDesLancer);
}


double denombreSuite()
{
    return factorielle(TYPE_DES);
}

double probaSuite()
{
    return denombreSuite() / denombreLancer(NOMBRE_DES);
}


double denombreCombin(int nbDesLancer, int nbDesCombin, int typeCombin)
{
    double denombre = 0.0;
    for (int i = nbDesCombin; i <= nbDesLancer; i++)
        if(typeCombin == -1)
            denombre += denombreCombinValeurDe(nbDesLancer, i);
        else
            denombre += (typeCombin) ? denombreCombinDe(nbDesLancer, i) : denombreCombinNegDe(nbDesLancer, i);
    return denombre;
}

double probaCombin(int nbDesLancer, int nbDesCombin, int typeCombin)
{
    return denombreCombin(nbDesLancer, nbDesCombin, typeCombin) / denombreLancer(nbDesLancer);
}


double denombreCombinNegDe(int nbDesLancer, int nbDesCombin)
{
    if (nbDesLancer == NOMBRE_DES && nbDesCombin == 3)
    {
        return (double) NOMBRE_TRIPLE_NEG;
    }
    else
    {
        return (pow((double) (NB_VAL_NEG - 1), (double) (nbDesLancer - nbDesCombin))
        * parmi(nbDesCombin, nbDesLancer)) * (double) NB_VAL_NEG;
    }
}

double probaCombinNegDe(int nbDesLancer, int nbDesCombin)
{
    return denombreCombinNegDe(nbDesLancer, nbDesCombin) / denombreLancer(nbDesLancer);
}


double denombreCombinDe(int nbDesLancer, int nbDesCombin)
{
    if (nbDesLancer == NOMBRE_DES && nbDesCombin == 3)
        return (double) NOMBRE_TRIPLE;
    else
        return denombreCombinValeurDe(nbDesLancer, nbDesCombin) * (double) TYPE_DES;
}

double probaCombinDe(int nbDesLancer, int nbDesCombin)
{
    return denombreCombinDe(nbDesLancer, nbDesCombin) / denombreLancer(nbDesLancer);
}


double denombreCombinValeurDe(int nbDesLancer, int nbDesCombin)
{
    return (pow((double) (TYPE_DES - 1), (double) (nbDesLancer - nbDesCombin))
    * parmi(nbDesCombin, nbDesLancer));
}

double probaCombinValeurDe(int nbDesLancer, int nbDesCombin)
{
    return denombreCombinValeurDe(nbDesLancer, nbDesCombin) / denombreLancer(nbDesLancer);
}


double factorielle(int nombre)
{
    if (!nombre)
        return 1;
    return nombre * factorielle (nombre - 1);
}

double parmi(int k, int n)
{
    return factorielle(n) / (factorielle (k) * factorielle (n - k));
}
