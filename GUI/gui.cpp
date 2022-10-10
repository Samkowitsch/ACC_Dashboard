
/********************************************/
/****************  INCLUDES *****************/
/********************************************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <iostream>

#include "gui.h"
#include "lv_conf.h"

#if USE_FBDEV
  #include "lv_drivers/display/fbdev.h"
  #include "lv_drivers/indev/evdev.h"
#endif

#if USE_SDL
  #define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
  #include <SDL2/SDL.h>
  #include "lv_drivers/display/monitor.h"
  #include "lv_drivers/indev/mouse.h"
  #include "lv_drivers/indev/keyboard.h"
  #include "lv_drivers/indev/mousewheel.h"
  #include "lv_drivers/sdl/sdl.h"
#endif


#include "Version.h"

#include "mainDashboard.h"

/********************************************/
/****************  DEFINES  *****************/
/********************************************/

#define LV_BUF_SIZE 384000 //800 x 480 / 10



/********************************************/
/************ STATIC VARIABLES ****+*********/
/********************************************/

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[LV_BUF_SIZE];
static lv_color_t buf2[LV_BUF_SIZE];

static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;



/**
 * @brief init gui drivers
 * 
 */
void guiInit(){
    lv_init();


    
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    //disp_drv.direct_mode = 1;
    //disp_drv.full_refresh = 1;
    //disp_drv.monitor_cb = monitor_cb;

    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;

    lv_disp_draw_buf_init(&draw_buf , buf1 , buf2 , LV_BUF_SIZE);

    #if USE_FBDEV
        fbdev_init();
        evdev_init();

        disp_drv.flush_cb = fbdev_flush;
        indev_drv.read_cb = evdev_read;
    #endif


    #if USE_SDL
        sdl_init();

        disp_drv.flush_cb = sdl_display_flush;
        indev_drv.read_cb = sdl_mouse_read;

    #endif

    //indev_drv.feedback_cb = indev_feedback_callback;
    lv_disp_drv_register(&disp_drv);
    lv_indev_drv_register(&indev_drv);
  
}



/**
 * @brief Main Gui Thread
 * 
 */
void guiThread(){

    std::cout << "Init Gui" << std::endl;
    guiInit();
    //init custom styles
    initStyles();

    while(true){

        std::cout << "Draw main screen " << std::endl;
        initMainDashboard();
        //lv_scr_load(main_screen_obj);



        while(true){
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            lv_tick_inc(10);
            lv_task_handler();
        }

    }


}

