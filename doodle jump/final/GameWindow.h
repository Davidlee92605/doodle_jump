#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED
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

#include"plat.h"
#include"doodle.h"
#include"score.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7
#define window_width 400
#define window_height 533

class GameWindow{
public:
    // constructor
    GameWindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_start_scene();
    void game_end_scene();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // draw running game map
    void draw_running_map();

    // process of updated event
    int process_event();

    void draw_slider();

    //Doodle* create_doodle();

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *start_pic = NULL;
    ALLEGRO_BITMAP *plat_pic = NULL;
    ALLEGRO_BITMAP *plat_pic_2 = NULL;
    ALLEGRO_BITMAP *doodle_pic = NULL;
    ALLEGRO_BITMAP *end_pic = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_FONT *title = NULL;
    ALLEGRO_FONT *subtitle = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *jumpSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;

    int mouse_x, mouse_y;

    bool redraw = false;
    bool mute = false;
    bool pause = false;
};

#endif // GAMEWINDOW_H_INCLUDED
