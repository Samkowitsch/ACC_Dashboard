#include "mainDashboard.h"

#include "lvgl/lvgl.h"



static lv_obj_t *main_dashboard_obj;

static lv_obj_t *rev_bar;
static lv_style_t rev_bar_style;
static lv_style_t rev_bar_ind_style;

static lv_obj_t *rev_bar_number[9];
static lv_obj_t *rev_bar_line[9];
static lv_point_t rev_bar_line_points[] = {{0 , 0}, {0, 40}};

static lv_obj_t *gear_indicator;
static lv_obj_t *gear_indicator_box;
static lv_point_t gear_indicator_box_points[] = {{40 , 0}, {0 , 0} , {0 ,200} , {150, 200} , {150 , 0} , {110 , 0}};
static char gear_char[][2] = {"R" , "N" , "1" , "2" , "3" , "4" , "5" , "6"};


static lv_obj_t *delta_indicator;
static lv_obj_t *delta_indicator_box;
static lv_point_t delta_indicator_box_points[] = {{90 , 0}, {0 , 0} , {0 ,80} , {180, 80} , {180 , 0} , {90 , 0}};


static lv_obj_t *status_box;
static lv_point_t status_box_points[] = {{390 , 0}, {0 , 0} , {0 ,60} , {780, 60} , {780 , 0} , {390 , 0}};

int demo_revs = 5000 ;
int demo_revs_val = 35;
bool demo_revs_up_down = true;
int demo_gear = 1;
float demo_delta = 0.00;

void demo_timer_callback(lv_timer_t * timer){


    if(demo_revs_up_down){
        if(demo_revs < 7900){
            demo_revs += demo_revs_val;
        }else{
            demo_revs_up_down = false;
            demo_gear++;
            if(demo_gear == 8)
                demo_gear = 0;
        }
    }else{
        if(demo_revs > 4000){
            demo_revs -= demo_revs_val * 4;
        }else{
            demo_revs_up_down = true;
        }
    }

    if(demo_revs > 7400){
        lv_obj_set_style_bg_color(rev_bar , lv_color_hex(0xB33737) , LV_PART_INDICATOR);
    }else{
        lv_obj_set_style_bg_color(rev_bar , lv_color_hex(0x3587A4) , LV_PART_INDICATOR);
    }


    demo_delta += 0.001;
    if(demo_delta >= 2.00)
        demo_delta = -2.00;

    lv_bar_set_value(rev_bar , demo_revs , LV_ANIM_ON);
    lv_label_set_text(gear_indicator , gear_char[demo_gear]);

    if(demo_delta < 0.00){
        lv_obj_set_style_text_color(delta_indicator , lv_palette_main(LV_PALETTE_GREEN) , 0);
    }else{
        lv_obj_set_style_text_color(delta_indicator , lv_palette_main(LV_PALETTE_RED) , 0);
    }
    lv_label_set_text_fmt(delta_indicator , "%.2f", demo_delta);
}

void initMainDashboard(){


    main_dashboard_obj = lv_obj_create(NULL);
    lv_obj_set_size(main_dashboard_obj , LV_HOR_RES_MAX , LV_VER_RES_MAX);
    lv_obj_set_style_bg_color(main_dashboard_obj , lv_color_black() , 0);


    lv_style_init(&rev_bar_style);
    lv_style_set_radius(&rev_bar_style , 0);
    lv_style_set_bg_color(&rev_bar_style , lv_color_black());
    
    lv_style_init(&rev_bar_ind_style);
    lv_style_set_radius(&rev_bar_ind_style , 0);
    lv_style_set_bg_color(&rev_bar_ind_style , lv_color_hex(0x3587A4));



    int line_x_pos = 17;
    for(int i = 0 ; i < 9 ; i++){

        rev_bar_number[i] = lv_label_create(main_dashboard_obj);
        lv_obj_set_size(rev_bar_number[i]  , 20 , 25);
        lv_obj_align(rev_bar_number[i] , LV_ALIGN_TOP_LEFT , 11 + i * 95 , 5);
        lv_obj_set_style_text_align(rev_bar_number[i] , LV_TEXT_ALIGN_CENTER , 0);
        lv_label_set_text_fmt(rev_bar_number[i] , "%d" , i);
        lv_obj_set_style_text_color(rev_bar_number[i] , lv_color_white() , 0);
        lv_obj_set_style_text_font(rev_bar_number[i] , &lv_font_montserrat_20 , 0);


        rev_bar_line[i] = lv_line_create(main_dashboard_obj);
        lv_line_set_points(rev_bar_line[i] , rev_bar_line_points , 2);
        lv_obj_align(rev_bar_line[i] , LV_ALIGN_TOP_LEFT , 20 + i * 95 , 30);
        lv_obj_set_style_line_color(rev_bar_line[i] , lv_color_white() , 0);
        lv_obj_set_style_line_width(rev_bar_line[i] , 3 , 0);

    }

    rev_bar = lv_bar_create(main_dashboard_obj);
    lv_obj_set_size(rev_bar , 760, 40);
    lv_obj_align(rev_bar , LV_ALIGN_TOP_MID , 0 , 30);
    lv_obj_add_style(rev_bar , &rev_bar_style , 0);
    lv_obj_add_style(rev_bar , &rev_bar_ind_style , LV_PART_INDICATOR);

    lv_bar_set_range(rev_bar , 0 , 8000);
    lv_bar_set_value(rev_bar , 6000 , LV_ANIM_ON);

    gear_indicator_box = lv_line_create(main_dashboard_obj);
    lv_line_set_points(gear_indicator_box , gear_indicator_box_points , 6);
    lv_obj_align(gear_indicator_box , LV_ALIGN_CENTER , 0 , 30);
    lv_obj_set_style_line_color(gear_indicator_box , lv_color_white() , 0);
    lv_obj_set_style_line_width(gear_indicator_box , 3 , 0);

    lv_obj_t *gear_indicator_box_title = lv_label_create(gear_indicator_box);
    lv_obj_set_size(gear_indicator_box_title , 100 , 30);
    lv_obj_align(gear_indicator_box_title , LV_ALIGN_TOP_MID , 0 , -7);
    lv_label_set_text(gear_indicator_box_title , "Gear");
    lv_obj_set_style_text_color(gear_indicator_box_title , lv_color_white() , 0 );
    lv_obj_set_style_text_align(gear_indicator_box_title , LV_TEXT_ALIGN_CENTER , 0);
    lv_obj_set_style_text_font(gear_indicator_box_title , &din_bold_24 , 0);

    gear_indicator = lv_label_create(gear_indicator_box);
    lv_obj_set_size(gear_indicator , 150 , 200);
    lv_obj_align(gear_indicator , LV_ALIGN_CENTER , 0 , -25);
    lv_label_set_text(gear_indicator , gear_char[1]);
    lv_obj_set_style_text_font(gear_indicator , &din_bold_200 , 0);
    lv_obj_set_style_text_color(gear_indicator , lv_color_white() , 0);
    lv_obj_set_style_text_align(gear_indicator , LV_TEXT_ALIGN_CENTER , 0 );

    delta_indicator_box = lv_line_create(main_dashboard_obj);
    lv_obj_align(delta_indicator_box , LV_ALIGN_CENTER , 0 , -120);
    lv_line_set_points(delta_indicator_box , delta_indicator_box_points , 6);
    lv_obj_set_style_line_color(delta_indicator_box , lv_color_white() , 0);
    lv_obj_set_style_line_width(delta_indicator_box , 5 , 0);

    delta_indicator = lv_label_create(delta_indicator_box);
    lv_obj_set_size(delta_indicator , 180 , 90);
    lv_obj_align(delta_indicator , LV_ALIGN_CENTER , 0 , 10);
    lv_label_set_text(delta_indicator , "-0.00");
    lv_obj_set_style_text_color(delta_indicator , lv_color_white() , 0 );
    lv_obj_set_style_text_align(delta_indicator , LV_TEXT_ALIGN_CENTER , 0);
    lv_obj_set_style_text_font(delta_indicator , &din_bold_50 , 0);



    status_box = lv_line_create(main_dashboard_obj);
    lv_obj_align(status_box , LV_ALIGN_BOTTOM_MID , 0 , -5);
    lv_line_set_points(status_box , status_box_points , 6);
    lv_obj_set_style_line_color(status_box , lv_color_white() , 0);
    lv_obj_set_style_line_width(status_box , 5 , 0);

    lv_scr_load(main_dashboard_obj);

    lv_timer_t * demo_timer = lv_timer_create(demo_timer_callback , 10 , NULL);
    

}