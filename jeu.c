#include <stdio.h>

#include "jeu.h"
#include "regles.h"
#include "combinaisons.h"
#include "esperances.h"


void initialiser_configuration(Configuration *c)
{
    initialiser_lancer(c->des, 0);
    c->faceCombi = 0;
    c->score = 0;
    c->scoreFin = 0;
}


void actualiser_configuration(Configuration *c, int lancer[])
{
    copier_lancer(lancer, c->des);
    c->faceCombi = valeur_combinaison(lancer);
    c->score += score_lancer(lancer);
}


void affiche_lancer(int lancer[])
{
    for (int i = 0 ; (i < NOMBRE_DES) && (lancer[i] != 0) ; i++)
    {
        printf("<%d>", lancer[i]);
    }
}


int ecarte_lancer(Configuration *c, int lancer[])
{
    if (score_echec(lancer) && !c->score) //si lancer de NOMBRE_DES et échec
    {
        initialiser_lancer(lancer, 0); //on perd tous ses dés
        c->score = SCORE_ECHEC;
        return 0;
    }
    else if (score_suite(lancer)) // si lancer de NOMBRE_DES et suite
    {
        c->score += SCORE_SUITE; // on garde les dés pour rejouer et on prend un score bonus
        return 0;
    }
    else // par défaut
    {
        // On veut vérifier que le lancer n'a pas que des VALEURS_NEG différentes
        // de notre combinaison sinon on perd le tour
        int nb = nombre_des(lancer), verif = nb;
        for (int i = 0; i < nb; i++)
        {
            verif -= VALEURS_NEG(lancer[i]); // chaque fois qu'on tombe sur mauvais dé...
            verif += (lancer[i] == c->faceCombi); // chaque fois qu'on tombe sur un bon dé...
        }

        if (verif == 0 && score_lancer(lancer) == 0) // dans le cas ou on n'a que des mauvais dés on perd tout
        {
            initialiser_lancer(lancer, 0); // on perd tous ses dés
            initialiser_lancer(c->des, 0);
            c->score = 0; // on perd notre avancée du tour
            c->faceCombi = 0;
            return 0;
        }

        else // dans le cas contraire : notre lancer a des dés à sauvegarder
        {
            if (occurrences_de(lancer, c->faceCombi)) // si le lancer complète une combinaison
            {
                int lancer_combi[NOMBRE_DES] = {};
                int occ_lancer = occurrences_de(lancer, c->faceCombi);
                affecter_lancer(lancer_combi, occ_lancer, c->faceCombi);
                c->score -= score_lancer(c->des); // on retranche l'ancienne combinaison car on veut la recalculer
                joindre_lancer(c->des, lancer_combi);
                c->score += score_lancer(c->des); // on recalcule avec la nouvelle combinaison
                enlever_lancer(lancer, NOMBRE_DES, c->faceCombi);
            }
            else // si le lancer ne complète pas une combinaison
            {
                int a, b;
                score_combinaison(lancer, &a, &b);

                int occ_a = (a) ? occurrences_de(lancer, a) : 0, occ_b = (b) ? occurrences_de(lancer, b) : 0;
                int lancer_a[NOMBRE_DES] = {}, lancer_b[NOMBRE_DES] = {};

                // calculer le score d'une unique combinaison de a
                int score_a = 0, score_b = 0;
                if (a) // calcule score d'une combinaison de "a" si elle existe
                {
                    affecter_lancer(lancer_a, occ_a, a);
                    score_a = score_lancer(lancer_a);
                }
                if (b) // calcule score d'une combinaison de "b" si elle existe
                {
                    affecter_lancer(lancer_b, occ_b, b);
                    score_b = score_lancer(lancer_b);
                }

                if (score_b > score_a) // Si la combinaison de B est meilleure que celle de A
                {
                    joindre_lancer(c->des, lancer_b); //on récupère les dés de la combinaison
                    c->score += score_b; // on garde les dés pour rejouer ont gagne le score
                    c->faceCombi = b;
                    enlever_lancer(lancer, nb, b);// on enlève du lancer les dés conservés
                }
                else if (score_a) // si on a une combinaison
                {
                    joindre_lancer(c->des, lancer_a); //on récupère les dés de la combinaison
                    c->score += score_a; // on garde les dés pour rejouer ont gagne le score
                    c->faceCombi = a;
                    enlever_lancer(lancer, nb, a);// on enlève du lancer les dés conservés
                }
                else // si on n'a pas de combinaison
                {
                    if (occurrences_de(lancer, VALEUR_EX1)) // si on a au moins un dé VALEUR_EX1
                    {
                        int lex1[NOMBRE_DES] = {VALEUR_EX1};
                        joindre_lancer(c->des, lex1);
                        enlever_prem_occ(lancer, nb, VALEUR_EX1); // on enleve 1 VALEUR_EX1 du lancer
                        c->score += SCORE_EX1;
                    }
                    else // sinon, c'est qu'on a un dé VALEUR_EX2
                    {
                        int lex2[NOMBRE_DES] = {VALEUR_EX2};
                        joindre_lancer(c->des, lex2);
                        enlever_prem_occ(lancer, nb, VALEUR_EX2); // on enleve 1 VALEUR_EX2 du lancer
                        c->score += SCORE_EX2;
                    }
                }
            }

            // Si on a sauvegardé tous ses dés, il faut tout rejouer
            if (nombre_des(c->des) == NOMBRE_DES)
            {
                copier_lancer(c->des, lancer);
                initialiser_lancer(c->des, 0);
                c->faceCombi = 0;
            }

            return score_lancer(lancer);
        }
    }
}


void nouvelle_partie(Configuration *c)
{
    initialiser_configuration(c);
    printf("\n------ Nouvelle partie -------");
}

void lancer_des(int lancer[], int nb_des)
{
    initialiser_lancer(lancer, nb_des);
    printf("\nDés joués : ");
    affiche_lancer(lancer);
}

void choix_des(Configuration *c, int lancer[])
{
    int choix = 1, passe;
    while (choix == 1)
    {
        passe = ecarte_lancer(c, lancer);
        printf("\nDés écartés : ");
        affiche_lancer(c->des);
        printf("  -> Score: %d - Proba: %0.1f%% - Espérance: %d\nDés à rejouer : ", c->score + c->scoreFin, 100*probaGain(nombre_des(lancer), c->faceCombi), esperance(c, lancer));
        affiche_lancer(lancer);
        if (nombre_des(lancer) && nombre_des(c->des) && passe)
        {
            printf("\n - Mettre d'autres dés de côté ?\n 1. Oui\n 2. Non\n");
            if (scanf("%d", &choix) == EOF)
                choix = 2;
        }
        else
        {
            choix = 2;
        }
    }
}

void nouvelle_manche(Configuration *c)
{
    int monLancer[NOMBRE_DES], esp[NOMBRE_DES] = {7,7,7,7,7,7};

    int mesDes = NOMBRE_DES, choix = 1;
    printf("\n------ Nouvelle manche -------");
    printf("\nProba de ne pas perdre: %0.1f%%", 100*probaGain(NOMBRE_DES, 0));
    printf("\nEspérance de gain initiale: %d", esperance(c, esp));
    while (mesDes && choix == 1)
    {
        lancer_des(monLancer, mesDes);
        choix_des(c,monLancer);
        mesDes = nombre_des(monLancer);
        if (mesDes)
        {
            printf("\n - Rejouer ?\n 1. Oui\n 2. Non\n");
            if (scanf("%d", &choix) == EOF)
                choix = 2;

            if (choix == 2 && nombre_des(monLancer) == NOMBRE_DES)
            {
                printf("Votre combinaison implique tous les dés. Vous devez rejouer.\n");
                choix = 1;
            }
            if (choix == 2 && c->scoreFin == 0 && c->score < SCORE_MIN)
            {
                printf("Vous n'avez pas assez de points. Vous devez rejouer.\n");
                choix = 1;
            }
        }
    }

    c->scoreFin += c->score;
    c->score = 0;
    initialiser_lancer(c->des, 0);
    c->faceCombi = 0;
    printf("\nVotre score : %d", c->scoreFin);
    printf("\n--------- Fin manche ---------");
}

void annoncer_vainqueur(Configuration *c)
{
    printf("\nVotre score : %d", c->scoreFin);
    printf("\nFélicitations!!!");
    printf("\n--------- Fin partie ---------");
}
