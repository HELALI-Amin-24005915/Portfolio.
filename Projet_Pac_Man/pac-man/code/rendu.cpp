#include "enTetes/rendu.h"
#include "enTetes/globals.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/rectangle.h"
#include "mingl/gui/text.h"
#include"mingl/gui/sprite.h"
#include"mingl/graphics/vec2d.h"


using namespace std;
using namespace nsShape;
using namespace nsGraphics;
using namespace nsGui ;

Sprite mapImg("image/mapLv1.si", Vec2D(0,0));



void Dessin(MinGL &window, const GameMap &map ,
            const unsigned &scoreJ1 , const unsigned &scoreJ2
            ) {
    RGBAcolor CouleurJ1(KYellow);
    RGBAcolor CouleurJ2(KBlue);

    if (BonnusJ1 !=0 ) {
        CouleurJ2 =KTransparent;
        ++BonnusJ1 ;
        if (BonnusJ1 >= 25) //3s d'invisibiliter pour le J2
            BonnusJ1 = 0;
    }

    if (BonnusJ2 !=0 ) {
        CouleurJ1 =KTransparent;
        ++BonnusJ2 ;
        if (BonnusJ2 >= 25)//3s d'invisibiliter pour le J1
            BonnusJ2 = 0;
    }



    //affiche L'image
    window<<mapImg;

    for (unsigned y  (0); y < GRID_ROWS; ++y) {
        for (unsigned x  (0); x < GRID_COLS; ++x) {
            if(map[y][x] == 1){
                Circle riz(Position(x * 20, y * 20), 5, KWhite);
                window << riz;
            }
            else if (map[y][x] == 6){
                Circle Bonnus(Position(x * 20, y * 20), 5, KMagenta );
                window << Bonnus;
            }
        }
    }




    //placement des joueurs
    Circle Joueur1(Joueur1Position * 20, 10,
                   CouleurJ1);
    window << Joueur1;

    Circle Joueur2(Joueur2Position * 20, 10,CouleurJ2);
    window << Joueur2;

    //affichage des Scores
    string scoreTextJ1 = "joueur1: " + to_string(scoreJ1);
    Text scoreDisplayJ1(
        Vec2D(SCREEN_WIDTH - 100, 20), // Position en haut à droite
        scoreTextJ1,                                 // Texte à afficher
        KWhite,                       // Couleur du texte
        GlutFont::BITMAP_HELVETICA_18 // Police du texte
        );
    window << scoreDisplayJ1;

    string scoreTextJ2 = "joueur2: " + to_string(scoreJ2);
    Text scoreDisplayJ2(
        Vec2D(SCREEN_WIDTH - 100, 40), // Position en haut à droite
        scoreTextJ2,                                 // Texte à afficher
        KWhite,                       // Couleur du texte
        GlutFont::BITMAP_HELVETICA_18 // Police du texte
        );
    window << scoreDisplayJ2;


    // Rectangle button1(Vec2D(SCREEN_WIDTH - 95, 425), Vec2D(SCREEN_WIDTH - 5, 390), KBlue);
    // Text Mode1J(Vec2D(SCREEN_WIDTH - 90, 415), "1 Joueur", KWhite, GlutFont::BITMAP_HELVETICA_18);
    // Text Mode2J(Vec2D(SCREEN_WIDTH - 90, 415), "2 Joueurs", KWhite, GlutFont::BITMAP_HELVETICA_18);
    // if (Bot)
    //     window << button1 << Mode2J;
    // else
    //     window<<button1<<Mode1J;


    Text PpourStop(Vec2D(60, SCREEN_HEIGHT-25), "Apuier sur P pour relancer la game", KWhite, GlutFont::BITMAP_HELVETICA_18);
    window<<PpourStop;


}


//ecrand de victoire

void ecrandDeFin(MinGL &window, unsigned &pointJ1,unsigned &pointJ2,unsigned & Victoire){

    string scoreTextJ1 = "joueur1 : " + to_string(pointJ1);
    Text scoreDisplayJ1(
        Vec2D(SCREEN_WIDTH-375, SCREEN_HEIGHT-450), // Position en haut à droite
        scoreTextJ1,                                 // Texte à afficher
        KWhite,                       // Couleur du texte
        GlutFont::BITMAP_HELVETICA_18 // Police du texte
        );
    window << scoreDisplayJ1;

    string scoreTextJ2 = "joueur2 : " + to_string(pointJ2);
    Text scoreDisplayJ2(
        Vec2D(SCREEN_WIDTH - 375, SCREEN_HEIGHT-400), // Position en haut à droite
        scoreTextJ2,                                 // Texte à afficher
        KWhite,                       // Couleur du texte
        GlutFont::BITMAP_HELVETICA_18 // Police du texte
        );
    window << scoreDisplayJ2;





    Text PpourStop(Vec2D(60, SCREEN_HEIGHT-25), "Apuier sur P pour relancer la game", KWhite, GlutFont::BITMAP_HELVETICA_18);
    window<<PpourStop;

    if(Victoire != 0){
        string GagnantTXT = "Le Gagnant est le joueur : " + to_string(Victoire);
        Text GagnantDisplay(
            Vec2D(SCREEN_WIDTH-400, SCREEN_HEIGHT-475), // Position en haut à droite
            GagnantTXT,                                 // Texte à afficher
            KWhite,                       // Couleur du texte
            GlutFont::BITMAP_TIMES_ROMAN_24 // Police du texte
            );
        window << GagnantDisplay;
    }
}




