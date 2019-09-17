#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define SCREEN_W 960
#define SCREEN_H 590
bool done;
int state = 0;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_DISPLAY *display;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *back  = NULL;
ALLEGRO_FONT *title = NULL;
int x;
int x2 = 850;

void abort_game(const char* message)
{
    printf("%s\n", message);
    exit(1);
}

void game_init(void)
{
    if (!al_init())
        abort_game("Failed to initialize allegro");
    
    if (!al_install_keyboard())
        abort_game("Failed to install keyboard");
    
    timer = al_create_timer(1.0 / 30);
    if (!timer)
        abort_game("Failed to create timer");
    
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display)
        abort_game("Failed to create display");
    
    event_queue = al_create_event_queue();
    if (!event_queue)
        abort_game("Failed to create event queue");
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
    done = false;
}

void game_destroy(void)
{
    if (timer)
        al_destroy_timer(timer);
    
    if (display)
        al_destroy_display(display);
    
    if (event_queue)
        al_destroy_event_queue(event_queue);
    
    if (image)
        al_destroy_bitmap(image);
    if (image2)
        al_destroy_bitmap(image2);
    if (back)
        al_destroy_bitmap(back);
    if (title)
        al_destroy_font(title);
    
}
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

void game_run(void)
{
    bool redraw = true;
    al_start_timer(timer);
    image = load_bitmap_at_size("image.png", 100, 100);
    image2 = load_bitmap_at_size("pika.png", 100, 100);
    back  = al_load_bitmap("background.png");
    title = al_load_font("SHREK.ttf", 64, NULL);
    
    
    int net_x[2] = { SCREEN_W/2-30 , SCREEN_W/2+30 };
    int net_y[2] = { SCREEN_H -200, SCREEN_H};
    
    while (!done) {
        
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        
        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                done = true;
            }
        }
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
            break;
        }
        
        if(state == 0 ) {
            
            
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    state = 1;
                }
            }
            
            if (redraw && al_is_event_queue_empty(event_queue)) {
                redraw = false;
                
                al_clear_to_color(al_map_rgb(102, 194, 165));
                al_draw_text(title, al_map_rgb(255,255,255), SCREEN_W/2, SCREEN_H/2-100, ALLEGRO_ALIGN_CENTER, "Pikachu Volleyball");
                al_flip_display();
            }
            
        }
        else if(state == 1) {
            
                
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_A:
                        if (x >= 15)
                            x -= 15;
                        break;
                    case ALLEGRO_KEY_D:
                        if (x <= 350)
                            x += 15;
                        break;
                    case ALLEGRO_KEY_J:
                        if (x2 >= 535)
                            x2 -= 15;
                        break;
                    case ALLEGRO_KEY_L:
                        if (x2 <= 835)
                            x2 += 15;
                        break;
                    default:
                        break;
                }
            }
            
            if (redraw && al_is_event_queue_empty(event_queue)) {
                redraw = false;
                
                al_draw_bitmap(back, 0, 0, 0);
                al_draw_filled_rectangle(net_x[0],
                                         net_y[0],
                                         net_x[1],
                                         net_y[1],
                                         al_map_rgb( 122, 122, 122));
                al_draw_bitmap(image , x ,SCREEN_H - al_get_bitmap_height(image) , 0);
                al_draw_bitmap(image2, x2, SCREEN_H - al_get_bitmap_height(image2), 0);
                
                al_flip_display();
                
            }
                
        }

    }
}

int main(int argc, char* argv[]) {
    
    game_init();
    game_run();
    game_destroy();
    
    return 0;
}
