#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <allegro5/allegro_native_dialog.h>
#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *Game = new GameWindow();

    Game->game_play();

    delete Game;
    return 0;
}
