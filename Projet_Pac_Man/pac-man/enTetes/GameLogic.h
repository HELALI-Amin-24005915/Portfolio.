#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Type.h"
#include "mingl/mingl.h"

void quiGagne(const unsigned &scoreJ1 , const unsigned &scoreJ2, unsigned &pointJ1,unsigned &pointJ2,unsigned &Victoire);

void PartieStart(GameMap &map,GameMap &mapRef,unsigned &scoreJ1 ,  unsigned &scoreJ2,
                 unsigned & DernierMouvementJ1,unsigned & DernierMouvementJ2,unsigned & NbRiz
                 , unsigned &pointJ1,unsigned &pointJ2
                 );

int CaseRemplie(Position Pos);

int Contact(Position &posJ1, Position &posJ2);

void J2bot(GameMap &map, unsigned &NbRiz, unsigned &DernierDirection);

void InputJoueur1(MinGL &window, GameMap &map, unsigned &NbRiz, unsigned &mouvementDirectionJ1, const CMyParam Param );

void InputJoueur2(MinGL &window, GameMap &map, unsigned &NbRiz, unsigned &mouvementDirectionJ1, const CMyParam Param );

#endif // GAMELOGIC_H
