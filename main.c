#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "regles.h"
#include "combinaisons.h"
#include "jeu.h"
#include "esperances.h"

int main()
{
    srand(time(NULL));

    printf("========  Dix Mille  =========\n");

    Configuration monJeu;

    nouvelle_partie(&monJeu);

    while(monJeu.scoreFin < SCORE_CIBLE)
        nouvelle_manche(&monJeu);

    annoncer_vainqueur(&monJeu);

    return 0;
}
