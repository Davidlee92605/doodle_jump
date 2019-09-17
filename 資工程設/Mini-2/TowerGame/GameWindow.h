#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Menu.h"
#include "Level.h"
#include "WolfKnight.h"
#include "CaveMan.h"
#include "Wolf.h"
#include "DemonNijia.h"
#include "Arcane.h"
#include "Archer.h"
#include "Canon.h"
#include "Poison.h"
#include "Storm.h"
#include "Attack.h"
#include "Slider.h"
#include "black_tower.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7
#define GAME_START_SCENE 8
#define GAME_PAUSE 9
#define GAME_SLIDER_SCENE 10

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();
    void game_start_scene();
    void game_pause();
    void game_slider_scene();
    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // draw running game map
    void draw_running_map();

    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    // detect if a tower will be constructed on road
    bool isOnRoad();

    Tower* create_tower(int);
    Monster* create_monster();

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tower[Num_TowerType];
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *image0 = NULL;
    ALLEGRO_BITMAP *pausebackground = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;
    ALLEGRO_FONT *title = NULL;
    ALLEGRO_FONT *subtitle = NULL;
    ALLEGRO_FONT *pauselist = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *monster_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;

    LEVEL *level = NULL;
    Menu *menu = NULL;

    ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h)
    {
        ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

        resized_bmp = al_create_bitmap(w, h);
        if (!resized_bmp) return NULL;

        loaded_bmp = al_load_bitmap(filename);
        if (!loaded_bmp)
        {
            al_destroy_bitmap(resized_bmp);
            return NULL;
        }

        prev_target = al_get_target_bitmap();
        al_set_target_bitmap(resized_bmp);

        al_draw_scaled_bitmap(loaded_bmp,
                              0, 0,
                              al_get_bitmap_width(loaded_bmp),
                              al_get_bitmap_height(loaded_bmp),
                              0, 0,
                              w, h, 0 );

        al_set_target_bitmap(prev_target);
        al_destroy_bitmap(loaded_bmp);

        return resized_bmp;
    }


    std::vector<Monster*> monsterSet;
    std::list<Tower*> towerSet;

    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int selectedTower = -1, lastClicked = -1;

    bool redraw = false;
    bool mute = false;
    bool keys[9] = {false, false, false, false, false, false, false, false, false};
    enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE, W, A, P, M};
};


#endif // MAINWINDOW_H_INCLUDED
