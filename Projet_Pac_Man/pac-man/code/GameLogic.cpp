#include "enTetes/GameLogic.h"
#include "enTetes/globals.h"
#include"enTetes/rendu.h"
#include <thread>
#include<string>
#include <chrono>
#include"mingl/audio/audioengine.h"


using namespace std;
nsAudio::AudioEngine audioEngine;

void quiGagne( unsigned &scoreJ1 ,  unsigned &scoreJ2, unsigned &pointJ1,
              unsigned &pointJ2,unsigned &Victoire)
{
    if (scoreJ1 > scoreJ2)
        ++ pointJ1;
    else if (scoreJ1 < scoreJ2)
        ++ pointJ2;
    if (pointJ1 == 2){
        Victoire =1;
    }
    else if (pointJ2 == 2){
        Victoire = 2;
    }

}

void PartieStart(GameMap &map,GameMap &mapRef,
                 unsigned &scoreJ1 ,  unsigned &scoreJ2,
                 unsigned & DernierMouvementJ2,unsigned & DernierMouvementJ1, unsigned & NbRiz
                 ,unsigned &pointJ1,unsigned &pointJ2 ) {



    switch (PS) {
    case true:
        PS = false;
        NbRiz = 0;
        map = mapRef;
        quiGagne(scoreJ1,scoreJ2,pointJ1,pointJ2,Victoire);
        scoreJ1 =0;
        scoreJ2 = 0;
        Joueur1Position.setX(13);
        Joueur1Position.setY(11);
        DernierMouvementJ1 = 0;
        Joueur2Position.setX(13);
        Joueur2Position.setY(17);
        DernierMouvementJ2 =0;
        break;
    case false:
        PS =true;
        if(Victoire !=0){
            Victoire = 0;
            pointJ2 =0;
            pointJ1 =0;
        }
        break;
    }
    this_thread::sleep_for(chrono::milliseconds( 100));
}

int CaseRemplie(Position Pos) {
    if (Pos == 1)
        return 1;
    else if (Pos == 6)
        return 2 ;
    else
        return 0;
}

int Contact(Position &posJ1, Position &posJ2) {
    return (posJ1 == posJ2) ? true : false;
}

void J2bot(GameMap &map, unsigned &NbRiz,unsigned & DernierDirection) {

    //dernier Pos du bot
    Position PosInterdite ;

    unsigned mouvementDirection (0);


    switch (DernierDirection) {
    case HAUT:
        PosInterdite.setY(Joueur2Position.getY()+1);
        PosInterdite.setX(Joueur2Position.getX() );
        break;
    case BAS:
        PosInterdite.setY(Joueur2Position.getY()-1);
        PosInterdite.setX(Joueur2Position.getX() );
        break;
    case GAUCHE:
        PosInterdite.setY(Joueur2Position.getY());
        PosInterdite.setX(Joueur2Position.getX() +1);
        break;
    case DROITE:
        PosInterdite.setY(Joueur2Position.getY());
        PosInterdite.setX(Joueur2Position.getX() - 1);
        break;
    }


    // Bloc de choix de direction basé sur les différences de position
    if ( map[Joueur2Position.getY()][Joueur2Position.getX() + 1] == 1  &&
        Joueur2Position != PosInterdite) {

        mouvementDirection = DROITE;



    }
    else if (map[Joueur2Position.getY()][Joueur2Position.getX() - 1] == 1&&
             Joueur2Position != PosInterdite) {

        mouvementDirection = GAUCHE;


    }
    else if (map[Joueur2Position.getY() + 1][Joueur2Position.getX()] == 1&&
             Joueur2Position != PosInterdite)  {

        mouvementDirection = BAS;


    }
    else if (map[Joueur2Position.getY() - 1][Joueur2Position.getX()] == 1 &&
             Joueur2Position != PosInterdite ) {
        mouvementDirection = HAUT;


    }

    // Si aucune direction n'a été choisie, choix par défaut
    else if ( DernierDirection == DROITE && map[Joueur2Position.getY()][Joueur2Position.getX() + 1] != 0 &&
             Joueur2Position != PosInterdite
             ) {
        mouvementDirection = DROITE;

    }
    else if ( DernierDirection == GAUCHE &&map[Joueur2Position.getY()][Joueur2Position.getX() - 1] != 0&&
             Joueur2Position != PosInterdite

             ) {
        mouvementDirection = GAUCHE;


    }
    else if ( DernierDirection == BAS &&map[Joueur2Position.getY() + 1][Joueur2Position.getX()] != 0&&
             Joueur2Position != PosInterdite

             ) {
        mouvementDirection = BAS;


    }
    else if ( DernierDirection == HAUT &&map[Joueur2Position.getY() - 1][Joueur2Position.getX()] != 0
             && Joueur2Position != PosInterdite

             ) {
        mouvementDirection = HAUT;


    }

    // si meme la dernier direction est boucher alors on prend la direction libre
    else if (map[Joueur2Position.getY() - 1][Joueur2Position.getX()] != 0 &&
             Joueur2Position != PosInterdite &&DernierDirection != BAS ) {
        mouvementDirection = HAUT;

    }
    else if ( map[Joueur2Position.getY()][Joueur2Position.getX() + 1] != 0  &&
             Joueur2Position != PosInterdite  &&DernierDirection != GAUCHE ) {

        mouvementDirection = DROITE;

    }
    else if (map[Joueur2Position.getY()][Joueur2Position.getX() - 1] != 0&&
             Joueur2Position != PosInterdite  &&DernierDirection != DROITE ) {

        mouvementDirection = GAUCHE;


    }
    else if (map[Joueur2Position.getY() + 1][Joueur2Position.getX()] != 0&&
             Joueur2Position != PosInterdite  &&DernierDirection != HAUT )  {

        mouvementDirection = BAS;

    }



    //Verif contacte
    if (Contact(Joueur1Position,Joueur2Position) == true){
        switch (mouvementDirectionJ2) {
        case HAUT:
            mouvementDirectionJ2 = BAS;
            Joueur1Position.setY(Joueur1Position.getY() + 1);
            break;
        case BAS:
            mouvementDirectionJ2 = HAUT;
            Joueur1Position.setY(Joueur1Position.getY() - 1);
            break;
        case GAUCHE:
            mouvementDirectionJ2 =DROITE;
            Joueur1Position.setX(Joueur1Position.getX() +1);
            break;
        case DROITE :
            mouvementDirectionJ2 =GAUCHE;
            Joueur1Position.setX(Joueur1Position.getX() - 1);
            break;
        }
    }

    // Vérification des téléporteurs
    if (Joueur2Position == PosTP1) {

        Joueur2Position.setX(25);
        Joueur2Position.setY(14);
        mouvementDirectionJ2 = GAUCHE;
    }
    else if (Joueur2Position == PosTP2) {

        Joueur2Position.setX(1);
        Joueur2Position.setY(14);
        mouvementDirectionJ2 = DROITE;
    }

    // Application du déplacement
    if (mouvementDirection == HAUT) {
        switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
        case 1:
            map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
            ++J2score ;
            ++ NbRiz ;
            break;
        case 2 :
            map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
            J2score =J2score +5 ;
            ++ NbRiz ;
            ++ BonnusJ2;
            break;



        }
        Joueur2Position.setY(Joueur2Position.getY() - 1);
    }
        else if (mouvementDirection == BAS) {
            switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
            case 1:
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J2score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J2score =J2score +5 ;
                ++ NbRiz ;
                ++ BonnusJ2;
                break;



            }
            Joueur2Position.setY(Joueur2Position.getY() + 1);
        }
        else if (mouvementDirection == GAUCHE) {
            switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
            case 1:
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J2score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J2score =J2score +5 ;
                ++ NbRiz ;
                ++ BonnusJ2;
                break;



            }
            Joueur2Position.setX(Joueur2Position.getX() - 1);
        }
        else if (mouvementDirection == DROITE) {
            switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
            case 1:
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J2score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J2score =J2score +5 ;
                ++ NbRiz ;
                ++ BonnusJ2;
                break;



            }
             Joueur2Position.setX(Joueur2Position.getX() + 1);
        }







        DernierDirection = mouvementDirection ;


    }

    // Fonction pour gérer les entrées clavier
    void InputJoueur1(MinGL &window, GameMap &map,unsigned &NbRiz
                      ,unsigned & mouvementDirectionJ1, const CMyParam Param ) {


        char HAUTJ1 (Param.MapParamChar.find("HAUTJ1") ->second),
            BASJ1 (Param.MapParamChar.find("BASJ1") ->second),
            GAUCHEJ1 (Param.MapParamChar.find("GAUCHEJ1") ->second),
            DROITEJ1 (Param.MapParamChar.find("DROITEJ1") ->second);


        //teste pour les TP
        if ( Joueur1Position == PosTP1){
            Joueur1Position.setX(26);
            Joueur1Position.setY(14);
            mouvementDirectionJ1 = GAUCHE  ;

        }
        else if (Joueur1Position == PosTP2){
            mouvementDirectionJ1 = DROITE;
            Joueur1Position.setX(1);
            Joueur1Position.setY(14);

        }


        //teste pour les touches
        if (window.isPressed({HAUTJ1, false}) && map[Joueur1Position.getY() - 1][Joueur1Position.getX()] != 0)
        {
            mouvementDirectionJ1 =  HAUT;
        }
        else if (window.isPressed({BASJ1, false}) && map[Joueur1Position.getY() + 1][Joueur1Position.getX()] != 0)
        {
            mouvementDirectionJ1 = BAS;
        }
        else if (window.isPressed({GAUCHEJ1, false}) && map[Joueur1Position.getY()][Joueur1Position.getX() - 1] != 0)
        {
            mouvementDirectionJ1 =GAUCHE;
        }
        else if (window.isPressed({DROITEJ1, false}) && map[Joueur1Position.getY()][Joueur1Position.getX() + 1] != 0)
        {
            mouvementDirectionJ1 = DROITE;
        }


        //Aplication du mouvement
        if (mouvementDirectionJ1 == HAUT && map[Joueur1Position.getY() - 1][Joueur1Position.getX()] != 0)
        {
            switch (CaseRemplie(  map[Joueur1Position.getY()][Joueur1Position.getX()])) {
            case 1:
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J1score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J1score ;
                ++ NbRiz ;
                ++ BonnusJ1;
                break;

            }
            Joueur1Position.setY(Joueur1Position.getY() - 1);
        }
        else if (mouvementDirectionJ1 == BAS && map[Joueur1Position.getY() + 1][Joueur1Position.getX()] != 0)
        {
            switch (CaseRemplie(  map[Joueur1Position.getY()][Joueur1Position.getX()])) {
            case 1:
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J1score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J1score ;
                ++ NbRiz ;
                ++ BonnusJ1;
                break;

            }
            Joueur1Position.setY(Joueur1Position.getY() + 1);
        }
        else  if (mouvementDirectionJ1 == GAUCHE && map[Joueur1Position.getY()][Joueur1Position.getX() - 1] != 0)
        {
            switch (CaseRemplie(  map[Joueur1Position.getY()][Joueur1Position.getX()])) {
            case 1:
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J1score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J1score ;
                ++ NbRiz ;
                ++ BonnusJ1;
                break;

            }
            Joueur1Position.setX(Joueur1Position.getX() - 1);

        }
        else if (mouvementDirectionJ1 == DROITE && map[Joueur1Position.getY()][Joueur1Position.getX() + 1] != 0)
        {
            switch (CaseRemplie(  map[Joueur1Position.getY()][Joueur1Position.getX()])) {
            case 1:
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J1score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur1Position.getY()][Joueur1Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J1score  = J1score + 5 ;
                ++ NbRiz ;
                ++ BonnusJ1;
                break;

            }
            Joueur1Position.setX(Joueur1Position.getX() + 1);
        }

        if (Contact(Joueur1Position,Joueur2Position) == true){
            switch (mouvementDirectionJ1) {
            case HAUT:
                mouvementDirectionJ1 = BAS;
                Joueur1Position.setY(Joueur1Position.getY() + 1);
                break;
            case BAS:
                mouvementDirectionJ1 = HAUT;
                Joueur1Position.setY(Joueur1Position.getY() - 1);
                break;
            case GAUCHE:
                mouvementDirectionJ1 =DROITE;
                Joueur1Position.setX(Joueur1Position.getX() +1);
                break;
            case DROITE :
                mouvementDirectionJ1 =GAUCHE;
                Joueur1Position.setX(Joueur1Position.getX() - 1);
                break;
            }


        }


    }

    void InputJoueur2(MinGL &window,  GameMap &map, unsigned & NbRiz,
                      unsigned & mouvementDirectionJ2, const CMyParam Param  ) {

        char HAUTJ2 (Param.MapParamChar.find("HAUTJ2") ->second),
            BASJ2 (Param.MapParamChar.find("BASJ2") ->second),
            GAUCHEJ2 (Param.MapParamChar.find("GAUCHEJ2") ->second),
            DROITEJ2 (Param.MapParamChar.find("DROITEJ2") ->second);


        if ( Joueur2Position == PosTP1){
            mouvementDirectionJ2 = GAUCHE  ;
            Joueur2Position.setX(26);
            Joueur2Position.setY(14);


        }
        else if (Joueur2Position == PosTP2){
            mouvementDirectionJ2 = DROITE;
            Joueur2Position.setX(1);
            Joueur2Position.setY(14);

        }


        if (window.isPressed({HAUTJ2, false}) && map[Joueur2Position.getY() - 1][Joueur2Position.getX()] != 0)
        {
            mouvementDirectionJ2 = HAUT;

        }
        else if (window.isPressed({BASJ2, false}) && map[Joueur2Position.getY() + 1][Joueur2Position.getX()] != 0)
        {
            mouvementDirectionJ2 = BAS;
        }
        else if (window.isPressed({GAUCHEJ2, false}) && map[Joueur2Position.getY()][Joueur2Position.getX() - 1] != 0)
        {
            mouvementDirectionJ2 =GAUCHE ; // Gauche*

        }
        else if (window.isPressed({DROITEJ2, false}) && map[Joueur2Position.getY()][Joueur2Position.getX() + 1] != 0)
        {
            mouvementDirectionJ2 = DROITE; // Droite
        }

        if (mouvementDirectionJ2 == HAUT && map[Joueur2Position.getY() - 1][Joueur2Position.getX()] != 0)
        {
            switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
            case 1:
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J2score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J2score =J2score +5 ;
                ++ NbRiz ;
                ++ BonnusJ2;
                break;

            }
            Joueur2Position.setY(Joueur2Position.getY() - 1);

        }
        else if (mouvementDirectionJ2== BAS  && map[Joueur2Position.getY() + 1][Joueur2Position.getX()] != 0)
        {
            switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
            case 1:
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J2score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J2score =J2score +5 ;
                ++ NbRiz ;
                ++ BonnusJ2;
                break;

            }
            Joueur2Position.setY(Joueur2Position.getY() + 1);
        }
        else if (mouvementDirectionJ2 == GAUCHE  && map[Joueur2Position.getY()][Joueur2Position.getX() - 1] != 0)
        {
            switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
            case 1:
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J2score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J2score =J2score +5 ;
                ++ NbRiz ;
                ++ BonnusJ2;
                break;

            }
            Joueur2Position.setX(Joueur2Position.getX() - 1);
        }
        else if (mouvementDirectionJ2 == DROITE && map[Joueur2Position.getY()][Joueur2Position.getX() + 1] != 0)
        {
            switch (CaseRemplie(  map[Joueur2Position.getY()][Joueur2Position.getX()])) {
            case 1:
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                ++J2score ;
                ++ NbRiz ;
                break;
            case 2 :
                map[Joueur2Position.getY()][Joueur2Position.getX()] =4;//je mait la case a 4 pour enlever le riz
                J2score =J2score +5 ;
                ++ NbRiz ;
                ++ BonnusJ2;
                break;

            }
            Joueur2Position.setX(Joueur2Position.getX() + 1);
        }

        if (Contact(Joueur1Position,Joueur2Position) == true){
            switch (mouvementDirectionJ2) {
            case HAUT:
                mouvementDirectionJ2 = BAS;
                Joueur2Position.setY(Joueur2Position.getY() + 1);
                break;
            case BAS:
                mouvementDirectionJ2 = HAUT;
                Joueur2Position.setY(Joueur2Position.getY() - 1);
                break;
            case GAUCHE:
                mouvementDirectionJ2 =DROITE;
                Joueur2Position.setX(Joueur2Position.getX() + 1);
                break;
            case DROITE :
                mouvementDirectionJ2 =GAUCHE;
                Joueur2Position.setX(Joueur2Position.getX() - 1);
                break;
            }
        }

    }


