#include <stdlib.h>

#include "regles.h"
#include "combinaisons.h"


int score_lancer(int lancer[])
{
    int f1, f2;
    int s_combin = score_combinaison(lancer, &f1, &f2);
    int s_echec = score_echec(lancer);
    int s_suite = score_suite(lancer);

    if (s_echec != 0)
    {
        return s_echec;
    }
    else if (s_suite != 0)
    {
        return s_suite;
    }
    else
    {
        return s_combin
        + score_simple(lancer, VALEUR_EX1) * (f1 != VALEUR_EX1 && f2 != VALEUR_EX1)
        + score_simple(lancer, VALEUR_EX2) * (f1 != VALEUR_EX2 && f2 != VALEUR_EX2);
    }
}


int score_simple(int lancer[], int valeur)
{
    switch (valeur)
    {
        case VALEUR_EX1:
            return occurrences_de(lancer, VALEUR_EX1) * SCORE_EX1;
        case VALEUR_EX2:
            return occurrences_de(lancer, VALEUR_EX2) * SCORE_EX2;
        default:
            return 0;
    }
}


int score_combinaison(int lancer[], int *face1, int *face2)
{
    int score = 0, occ = 0;
    *face1 = 0;
    *face2 = 0;

    for (int i = 1 ; i <= TYPE_DES ; i++)
    {
        occ = occurrences_de(lancer, i);

        if (occ >= 3)
        {
            score += (i == VALEUR_EX1) ? SCORE_COMBINE_EX(i, occ) : SCORE_COMBINE(i, occ);
            (*face1 == 0) ? (*face1 = i) : (*face2 = i);
        }
    }

    return score;
}


int valeur_combinaison(int lancer[])
{
    int a, b;

    if (score_suite(lancer))
        return 0;
    if (score_echec(lancer))
        return 0;

    score_combinaison(lancer, &a, &b);

    if (b != 0)
        return 0;

    return a;
}


int score_suite(int lancer[])
{
    for (int i = 1 ; i <= TYPE_DES ; i++)
    {
        if (occurrences_de(lancer, i) != 1 || lancer[i - 1] == 0)
        {
            return 0;
        }
    }

    return SCORE_SUITE;
}


int score_echec(int lancer[])
{
    int f1, f2;
    int s_combi = score_combinaison(lancer, &f1, &f2);

    if (s_combi != 0)
    {
        return 0;
    }
    else
    {
        for (int i = 0 ; i < TYPE_DES ; i++)
        {
            if (VALEURS_POS(lancer[i]) == 1 || lancer[i] == 0)
            {
                return 0;
            }
        }

        return SCORE_ECHEC;
    }
}


int occurrences_de(int lancer[], int valeur)
{
    int occurrences = 0;

    for (int i = 0 ; (i < NOMBRE_DES) && (lancer[i] != 0) ; i++)
    {
        if (lancer[i] == valeur)
        {
            occurrences++;
        }
    }

    return occurrences;
}

void copier_lancer(int lancer[], int copie[])
{
    for(int i = 0; i < NOMBRE_DES; i++)
        copie[i] = lancer[i];
}

void initialiser_lancer(int lancer[], int nombreDes)
{
    for (int i = 0 ; i < NOMBRE_DES ; i++)
    {
        lancer[i] = (i < nombreDes) ? rand() % (TYPE_DES) + 1 : 0;
    }
}

void affecter_lancer(int lancer[], int nombreDes, int valeurFixe)
{
    for (int i = 0 ; i < NOMBRE_DES ; i++)
    {
        lancer[i] = (i < nombreDes) ? valeurFixe : 0;
    }
}


void enlever_lancer(int lancer[], int nombreDes, int valeur)
{
    int i = 0, lancerCopie[NOMBRE_DES] = {};

    for (int j = 0 ; j < NOMBRE_DES ; j++)
    {
        if(lancer[j] != valeur)
            lancerCopie[i++] = lancer[j];
    }

    copier_lancer(lancerCopie, lancer);
}


void enlever_prem_occ(int lancer[], int nombreDes, int valeur)
{
    int i = 0, lancerCopie[NOMBRE_DES] = {};

    for (int j = 0 ; j < NOMBRE_DES ; j++)
    {
        if(lancer[j] == valeur && i == j)
            lancerCopie[i] = 0;
        else
            lancerCopie[i++] = lancer[j];
    }

    copier_lancer(lancerCopie, lancer);
}


int nombre_des(int lancer[])
{
    int i;
    for (i = 0 ; (i < NOMBRE_DES) && (lancer[i] != 0) ; i++);
    return i;
}

void joindre_lancer(int lancer1[], int lancer2[])
{
    int i, j;
    for (i = 0; i < NOMBRE_DES && lancer1[i] != 0; i++);
    for (j = 0; j < NOMBRE_DES && lancer2[j] != 0; j++)
    {
        lancer1[i++] = lancer2[j];
    }
}
