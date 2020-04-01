#define ESPERANCE_GAIN 324

// Pour une configuration et un lancé donnés, renvoit l'espérance de gain
int esperance(Configuration *c, int lancer[]);

// Renvoit la probabilité d'améliorer son score en lançant nbDesLancer
// faceCombi vaut la valeur d'une face si on a déjà une combinaison de cette face côté de côté, et 0 sinon
double probaGain(int nbDesLancer, int faceCombi);
// Renvoit la probabilité de perdre son score en lançant nbDesLancer
// faceCombi vaut la valeur d'une face si on a déjà une combinaison de cette face côté de côté, et 0 sinon
double probaRien(int nbDesLancer, int faceCombi);


// renvoit la probabilité sur nbDesLancer de ne tirer aucun dé de type VALEURS_POS
double probaPasDeValPos(int nbDesLancer);
// renvoit la probabilité sur nbDesLancer de ne tirer au moins un dé de type VALEURS_POS
double probaUneValPos(int nbDesLancer);


// calcule la probabilité de ne pas pouvoir relancer les dés (= on perd)
// faceCombi vaut la valeur d'une face si on a déjà une combinaison de cette face côté de côté, et 0 sinon
double probaNePasRelancer(int nbDesLancer, int faceCombi);
double probaRelancer(int nbDesLancer, int faceCombi);

// comptabilise le nombre de configurations différentes de nbDesLancer à TYPE_DES faces
double denombreLancer(int nbDesLancer);


// renvoit le nombre de combinaisons possibles de suites
// de NOMBRE_DES dés (ex: 1,2,3,4,5,6)
double denombreSuite();
double probaSuite();


// Renvoit le nombre de combinaisons possibles de nbDesLances
// comptabilisant au moins nbDesCombin dés d'une même valeur
// Si typeCombin = 1, alors peu importe la valeur du dé
// Si typeCombin = 0, alors on ne s'intéresse qu'aux combinaisons de VALEURS_NEG
// Si typeCombin = -1, alors on s'intéresse à une seule valeur V
// /!\ ne fonctionne pas avec nbDesLancer <= 2 * nbDesCombin
double denombreCombin(int nbDesLancer, int nbDesCombin, int typeCombin);
double probaCombin(int nbDesLancer, int nbDesCombin, int typeCombin);


// Renvoit le nombre de combinaisons possibles de nbDesLances
// comptabilisant exactement nbDesCombin dés d'UNE MEME VALEUR INCLUE DANS VALEURS_NEG
// /!\ ne fonctionne pas avec nbDesLancer <= 2 * nbDesCombin
double probaCombinNegDe(int nbDesLancer, int nbDesCombin);
double denombreCombinNegDe(int nbDesLancer, int nbDesCombin);


// Renvoit le nombre de combinaisons possibles de nbDesLances
// comptabilisant exactement nbDesCombin dés d'UNE MEME VALEUR
// /!\ ne fonctionne pas avec nbDesLancer <= 2 * nbDesCombin
double denombreCombinDe(int nbDesLancer, int nbDesCombin);
double probaCombinDe(int nbDesLancer, int nbDesCombin);


// Renvoit le nombre de combinaisons possibles de nbDesLances
// comptabilisant exactement nbDesCombin dés de LA MEME VALEUR V
double denombreCombinValeurDe(int nbDesLancer, int nbDesCombin);
double probaCombinValeurDe(int nbDesLancer, int nbDesCombin);


// calcule de la factorielle d'un nombre
double factorielle(int nombre);

// renvoit le nombre de combinaisons de k parmi n
double parmi(int k, int n);
