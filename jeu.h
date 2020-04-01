#include "regles.h"

typedef struct Configuration Configuration;
struct Configuration
{
    int des[NOMBRE_DES];
    int faceCombi;
    int score;
    int scoreFin;
};

// Initialise une configuration en mettant toutes les valeurs à 0
void initialiser_configuration(Configuration *c);

// Met à jour une configuration avec un lancer donné
void actualiser_configuration(Configuration *c, int lancer[]);

// affiche en console le contenu d'un lancer
void affiche_lancer(int lancer[]);

// sépare un lancer en 2 : la combinaison à garder (intégrée à la Configuration) et les dés à rejouer
// Par défaut, ne garde que les combinaisons, sauf s'il n'y en a pas
// Dans ce cas, garde un VALEUR_EX1 et à défaut un VALEUR_EX2
// Retourne 0 si on ne peut plus écarter de dés après une première sélection, 1 sinon
int ecarte_lancer(Configuration *c, int lancer[]);

// initialise une nouvelle partie
void nouvelle_partie(Configuration *c);

// simule un lancer de dés
void lancer_des(int lancer[], int nb_des);

// demande au joueur s'il veut garder les dés
void choix_des(Configuration *c, int lancer[]);

// initialise une nouvelle manche
void nouvelle_manche(Configuration *c);

// annonce le vainqueur et son score
void annoncer_vainqueur(Configuration *c);
