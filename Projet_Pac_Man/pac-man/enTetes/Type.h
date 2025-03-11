#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include "mingl/graphics/vec2d.h"
#include <map>
// Constantes
const unsigned SCREEN_WIDTH = 660;
const unsigned SCREEN_HEIGHT = 660;
const unsigned GRID_ROWS = 31;
const unsigned GRID_COLS = 28;
const unsigned FPS_LIMIT = 10;



// Types
typedef std::vector<std::vector<unsigned>> GameMap;
typedef nsGraphics::Vec2D Position;
typedef nsGraphics::Vec2D Taille;

struct AuthorizedKey {
    /** List of authorized key for the type char in a struct CMyParam*/
    const std::vector <std::string> VParamChar
        {"HAUTJ1", "BASJ1", "GAUCHEJ1",
         "DROITEJ1", "HAUTJ2", "BASJ2",
            "GAUCHEJ2", "DROITEJ2"};

};

struct CMyParam {
    std::map <std::string, char> MapParamChar;
};

const AuthorizedKey KAuthorizedKey;


// Enums
enum MoveDirection {
    HAUT = 1,
    BAS = 2,
    GAUCHE = 3,
    DROITE = 4,

};






#endif // TYPE_H
