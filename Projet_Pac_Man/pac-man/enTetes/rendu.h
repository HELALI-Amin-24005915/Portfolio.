#ifndef RENDU_H
#define RENDU_H

#include "Type.h"
#include "mingl/mingl.h"
#include"mingl/event/event.hpp"
#include<string>

void Dessin(MinGL &window, const GameMap &map,
            const unsigned &scoreJ1, const unsigned &scoreJ2);
void ecrandDeFin(MinGL &window, unsigned &pointJ1,unsigned &pointJ2,
                 unsigned & Victoire);

#endif // RENDERER_H
