/**
 * ExileofAranei OLED Feature - Header
 * ====================================
 * 
 * This file declares the OLED functions.
 * It's included by exileofaranei.c when OLED is enabled.
 */

#pragma once

#include QMK_KEYBOARD_H

/**
 * OLED Task User
 * 
 * This is the main OLED update function called by QMK.
 * It renders different content on master vs slave sides.
 * 
 * Return false: We handled OLED update completely
 */
bool oled_task_user(void);

/**
 * OLED Init User
 * 
 * Called when OLED initializes. Sets the rotation.
 */
oled_rotation_t oled_init_user(oled_rotation_t rotation);
