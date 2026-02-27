/**
 * ExileofAranei OLED Feature - Implementation
 * ============================================
 *
 * This file contains the OLED display code.
 * It shows:
 * - Master side: WPM counter
 * - Slave side: Current layer, lock states (Caps/Num/Scroll), active modifiers
 *
 * The OLED is rotated 270 degrees for Corne vertical displays.
 */

#include QMK_KEYBOARD_H
#include "oled.h"
#include "bongo.c"
#include "../exileofaranei.h"

// ============================================================================
// OLED Initialization
// ============================================================================

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // Rotate 270 degrees for vertical OLED orientation
    // This makes text display vertically on Corne keyboards
    return !is_keyboard_master() ? OLED_ROTATION_270 : OLED_ROTATION_180;
}

// ============================================================================
// Slave Side Rendering (Layer, Locks, Mods)
// ============================================================================
//
// The slave side shows useful information about keyboard state:
// - Current layer name
// - Lock states (Caps Lock, Num Lock, Scroll Lock)
// - Active modifiers (GUI, Alt, Ctrl, Shift)

// Convert layer number to human-readable name
static void render_layer(void) {
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("LAYER"), false);
    oled_set_cursor(0, 4);

    // Get the highest active layer
    switch (get_highest_layer(layer_state)) {
        case BASE:   oled_write_P(PSTR("BASE "), false); break;
        case EXTRA:  oled_write_P(PSTR("EXTRA"), false); break;
        case TAP:    oled_write_P(PSTR("TAP  "), false); break;
        case BUTTON: oled_write_P(PSTR("BTN  "), false); break;
        case NAV:    oled_write_P(PSTR("NAV  "), false); break;
        case MOUSE:  oled_write_P(PSTR("MOUSE"), false); break;
        case MEDIA:  oled_write_P(PSTR("MED  "), false); break;
        case NUM:    oled_write_P(PSTR("NUM  "), false); break;
        case SYM:    oled_write_P(PSTR("SYM  "), false); break;
        case FUN:    oled_write_P(PSTR("FUN  "), false); break;
        default:     oled_write_P(PSTR("???  "), false); break;
    }
}

// Show lock states (Caps, Num, Scroll)
// Each indicator lights up when that lock is active
static void render_locks(void) {
    // Get current LED states from the computer
    led_t leds = host_keyboard_led_state();

    oled_set_cursor(0, 6);
    oled_write_P(PSTR("CAP"), leds.caps_lock);

    oled_set_cursor(0, 7);
    oled_write_P(PSTR("NUM"), leds.num_lock);

    oled_set_cursor(0, 8);
    oled_write_P(PSTR("SCR"), leds.scroll_lock);
}

// Show active modifiers (GUI, Alt, Ctrl, Shift)
// Each letter appears when that modifier is held
static void render_mods(void) {
    // Get currently held modifiers (including one-shot mods)
    uint8_t mods = get_mods() | get_oneshot_mods();

    oled_set_cursor(0, 10);
    oled_write_P(PSTR("MODS"), false);
    oled_set_cursor(0, 11);

    // Write G, A, C, S if those modifiers are active
    // Show '-' if not active
    oled_write_char(mods & MOD_MASK_GUI   ? 'G' : '-', false);
    oled_write_char(mods & MOD_MASK_ALT   ? 'A' : '-', false);
    oled_write_char(mods & MOD_MASK_CTRL  ? 'C' : '-', false);
    oled_write_char(mods & MOD_MASK_SHIFT ? 'S' : '-', false);
}

// ============================================================================
// Main OLED Task
// ============================================================================
//
// This function is called continuously by QMK to update the OLED.
// It decides what to show based on which side of the keyboard this is.

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // This is the master side - show WPM
        render_anim();
    } else {
        // This is the slave side - show layer, locks, and mods
        render_layer();
        render_locks();
        render_mods();
    }

    // Return false to tell QMK we handled the OLED update
    return false;
}
