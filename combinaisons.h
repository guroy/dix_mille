// renvoit le score d'un lancer donné
int score_lancer(int lancer[]);

// renvoit le score d'un lancer en ne comptabilisant que la valeur unitairement (ex : 3 VALEUR_EX1 = 3*SCORE_EX1)
int score_simple(int lancer[], int valeur);

// si le lancer contient une ou plusieurs combinaisons de 3 à TYPE_DES renvoit le score associé, sinon 0
// initialise face1 et face2 à la valeur des faces donnant lieu à des combinaisons
int score_combinaison(int lancer[], int *face1, int *face2);

// renvoit la face concernée par la combinaison à mettre de côté, ou 0 si tous les dés sont à rejouer
int valeur_combinaison(int lancer[]);

// si le lancer contient toutes les valeurs jusqu'à TYPE_DES, renvoit le SCORE_SUITE, sinon 0
int score_suite(int lancer[]);

// si le lancer est de TYPE_DES dés et ne contient que des VALEURS_NEG, renvoit SCORE_ECHEC, sinon 0
int score_echec(int lancer[]);

// renvoit le nombre de fois ou la valeur est présente dans le lancer
int occurrences_de(int lancer[], int valeur);

// une copie case par case depuis lancer vers copie
void copier_lancer(int lancer[], int copie[]);

// met un lancer de nombreDes dés avec des valeurs aléatoires
void initialiser_lancer(int lancer[], int nombreDes);

// met un lancer de nombreDes dés avec une valeur fixe
void affecter_lancer(int lancer[], int nombreDes, int valeurFixe);

// enlève les occurences d'une valeur dans un lancer
void enlever_lancer(int lancer[], int nombreDes, int valeur);

// enlève première occurences d'une valeur dans un lancer
void enlever_prem_occ(int lancer[], int nombreDes, int valeur);

// nombre de dés dans un lancer
int nombre_des(int lancer[]);

// concaténer dans lancer1 les lancer 1 et 2
void joindre_lancer(int lancer1[], int lancer2[]);
