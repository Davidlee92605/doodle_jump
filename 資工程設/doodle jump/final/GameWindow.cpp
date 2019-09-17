#include "GameWindow.h"
#include <iostream>

const float FPS = 60;

struct point{int x, y;};
int plat_type;
int x=100,y=100,h=200;
float dx=0,dy=0;

point randpos[20];
platform plat[20];
Doodle doodle;
Score score;
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

void
GameWindow::game_init()
{
    icon = al_load_bitmap("./icon.png");
    background = load_bitmap_at_size("./StartBackground.png", 400, 533);
    start_pic = load_bitmap_at_size("start_pic.jpg", 400, 533);
    plat_pic = al_load_bitmap("platform.png");
    plat_pic_2 = al_load_bitmap("platform2.png");
    doodle_pic = al_load_bitmap("doodle.png");
    end_pic = load_bitmap_at_size("end_pic.png", 400, 533);

    al_set_display_icon(display, icon);

    al_reserve_samples(3);
    sample = al_load_sample("fall.wav");
    failSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(failSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(failSound, al_get_default_mixer());

    sample = al_load_sample("jump.wav");
    jumpSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(jumpSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(jumpSound, al_get_default_mixer());
    /*
    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
    */
}


void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;

    static int first_time = 0;
    if(first_time == 0){
        game_start_scene();
        first_time = 1;
    }

    srand(time(0));
    for (int i=0;i<10;i++){
        randpos[i].x=rand()%400;
        randpos[i].y=rand()%533;
        plat[i].setPosition(randpos[i].x, randpos[i].y);
    }


    game_begin();

    while(msg != GAME_EXIT){

        msg = game_run();
    }

    show_err_msg(msg);
}

void GameWindow::game_start_scene(){
    while(true){
        al_draw_bitmap(start_pic, 0, 0, 0);
        al_flip_display();

        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if(event.mouse.button == 1 && event.mouse.y >= 130 && event.mouse.y <= 180){
                    return;
                }
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                return;
            }
        }

    }

}

void GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);

    if(timer == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font
    title = al_load_font("Caviar_Dreams_Bold.ttf", 80, NULL);
    subtitle = al_load_font("Caviar_Dreams_Bold.ttf", 40, NULL);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Initializing resources that tower game needs.
    game_init();
}

void
GameWindow::game_begin()
{
    draw_running_map();
    /*
    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);
    */
    al_start_timer(timer);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

void GameWindow::game_end_scene(){
    while(true){
        al_draw_bitmap(end_pic, 0, 0, 0);
        al_draw_textf(subtitle, al_map_rgb(178,34,34),250, 430,  ALLEGRO_ALIGN_LEFT, "%d", score.score);
        al_flip_display();

        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                return;
            }
        }

    }

}
int
GameWindow::game_update()
{   dy += 0.2;
    y += dy;

    if(x < 0) x = 400;
    if(x > 400) x = 0;

    if (y>500){
        al_play_sample_instance(failSound);
        while(al_get_sample_instance_playing(failSound));
        game_end_scene();
        return GAME_EXIT;

    }


    for (int i=0;i<10;i++){
        if ((x+50>plat[i].x) && (x+20<plat[i].x+68)&& (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0)){
            al_play_sample_instance(jumpSound);
            dy=-10;
        }
    }

    if (y<h){
        for (int i=0;i<10;i++){
            y = h;
            plat[i].y = plat[i].y - dy;
            if (plat[i].y>533){
                plat[i].setPosition(rand()%400, 0);
                plat_type = (rand()%10);
                score.score += rand()%30;
            }
        }
    }
    doodle.setPosition(x,y);

    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    // clear all towers

    mute = false;
    redraw = false;

    // stop sample instance
    //al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(failSound);
    al_stop_sample_instance(jumpSound);
    // stop timer
    al_stop_timer(timer);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);
    al_destroy_font(title);
    al_destroy_font(subtitle);

    al_destroy_timer(timer);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
    al_destroy_bitmap(start_pic);
    al_destroy_bitmap(plat_pic);
    al_destroy_bitmap(plat_pic_2);
    al_destroy_bitmap(doodle_pic);
    al_destroy_bitmap(end_pic);
    al_destroy_sample(sample);
    al_destroy_sample_instance(jumpSound);
    al_destroy_sample_instance(failSound);
    al_destroy_sample_instance(backgroundSound);
}

int
GameWindow::process_event()
{
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode == ALLEGRO_KEY_LEFT){
            x-=30;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
            x+=30;
        }
    }
    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;
}
/*
void GameWindow::draw_slider(){
    Slider slider = Slider(100, 150);

    while(true){
        slider.Draw();
        al_flip_display();
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(event.mouse.button == 1){
                if(slider.isClicked(mouse_x, mouse_y)){
                    slider.toggleDrag();
                }
            }
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
            if(slider.isDragged()){
                slider.Drag(mouse_x, mouse_y);
                al_set_sample_instance_gain(backgroundSound, slider.getDegree());
            }
        }
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(slider.isDragged()) slider.toggleDrag();
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                return;
            }
        }

    }



}
*/

void GameWindow::draw_running_map()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_textf(subtitle, al_map_rgb(178,34,34),10, 10,  ALLEGRO_ALIGN_LEFT, "%d", score.score);

    for (int i = 0;i<10;i++){
        if(score.score > 100 && plat_type == 9)al_draw_bitmap(plat_pic_2, plat[i].x, plat[i].y, 0);
        else al_draw_bitmap(plat_pic, plat[i].x, plat[i].y, 0);
    }

	//doodle.setPosition(x,y);
    al_draw_bitmap(doodle_pic, doodle.x, doodle.y, 0);


    al_flip_display();
}
