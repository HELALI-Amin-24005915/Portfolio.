#ifndef GLOBALS_H
#define GLOBALS_H

#include "Type.h"


// Variables globales
extern bool PS;//Partie Start
extern bool   Bot;
extern unsigned pointJ1, pointJ2;//nombre de partie gagner
//bool Bot; //si il y a 2 ou 1 joueur
extern Position PosTP1, PosTP2;
extern Position Joueur1Position, Joueur2Position;
extern unsigned J1score, J2score;
extern unsigned mouvementDirectionJ1, mouvementDirectionJ2;
extern unsigned DernierMouvementJ1, DernierMouvementJ2;
extern unsigned Victoire;
extern unsigned NbRiz;
extern unsigned BonnusJ1 ,BonnusJ2;

#endif // GLOBALS_H
