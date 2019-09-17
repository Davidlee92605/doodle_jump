#ifndef BLACK_TOWER_H_INCLUDED
#define BLACK_TOWER_H_INCLUDED

#include "Tower.h"

class black_tower : public Tower
{
public:
    black_tower(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = BLACK_TOWER;

        circle->r = 80;
        attack_frequency = 15;
        attack_velocity = 8;
        attack_harm_point = 7;
        img = al_load_bitmap("./Tower/BlackTower.png");
        attack_img = al_load_bitmap("./Tower/BlackTower_Beam.png");
    }

    int getWidth() override { return TowerWidth[BLACK_TOWER]; }
    int getHeight() override { return TowerHeight[BLACK_TOWER]; }
};

#endif // BLACK_TOWER_H_INCLUDED


