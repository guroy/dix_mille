#include <math.h>

#define NOMBRE_DES 6
#define TYPE_DES 6
#define SCORE_CIBLE 10000
#define SCORE_MIN 750
#define SCORE_SUITE 3000
#define SCORE_ECHEC -3000
#define SCORE_EX1 100
#define SCORE_EX2 50
#define VALEURS_POS(v) ((v == 1) || (v == 5))
#define VALEURS_NEG(v) ((v == 2) || (v == 3) || (v == 4) || (v == 6))
#define NB_VAL_POS 2
#define NB_VAL_NEG 4
#define VALEUR_EX1 1
#define VALEUR_EX2 5
#define SCORE_COMBINE(val, occ) (val * 100 * pow(2, occ - 3))
#define SCORE_COMBINE_EX(val, occ) (val * 1000 * pow(2, occ - 3))
#define NOMBRE_TRIPLE 14700 // nombre de combinaisons d'exactement 3 mêmes dés sur 6 dés à 6 faces
#define NOMBRE_TRIPLE_NEG 2040 // nombre de combinaisons d'exactement 3 mêmes dés sur 6 dés à 6 faces et aucun 1 ou 5
