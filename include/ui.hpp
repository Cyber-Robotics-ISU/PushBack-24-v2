#pragma once
#include <vector>  
#include <string> 
#include <cmath>
#include "global.hpp"  
#include "autons.hpp"  
#include "driver_profile.hpp"

#include "liblvgl/lvgl.h"

// ============================================================================
//                              FORWARD DECLARATIONS
// ============================================================================

// LVGL Screens
void create_main_screen();
void create_auton_screen();
void create_profiles_screen();
void create_odometry_screen(); // <--- Added this to fix your error
void create_auton_color_screen(); 

// Auton Selection Logic
void auton_red_select();
void auton_blue_select();
void updateAutonList();

// Utilities
void clear_screen(lv_obj_t* screen);