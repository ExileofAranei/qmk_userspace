/**
 * ExileofAranei QMK Implementation
 * ==================================
 * 
 * This file contains the actual implementation of:
 * - Keymaps for all 10 layers
 * - Tap dance functions
 * - Combos (undo, redo, copy, paste, select-all, save)
 * - Custom keycodes (arrow, copy-cut)
 * - Process record user (handles custom keys)
 * 
 * This code is shared across ALL keyboards using this user config.
 */

#include QMK_KEYBOARD_H
#include "exileofaranei.h"

// ============================================================================
// Tap Dance Functions
// ============================================================================
// 
// Tap dance allows different actions for single-tap vs double-tap.
// These functions define what happens for each tap dance.

// TD_BOOT: Double-tap to reset keyboard
void td_fn_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // Double-tap detected - reset the keyboard
        reset_keyboard();
    }
}

// TD_SYM_IDX: { on single-tap, BASE layer on double-tap
void td_fn_sym_idx(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_LCBR);  // Type left brace
    } else if (state->count == 2) {
        default_layer_set((layer_state_t)1 << BASE);  // Switch to BASE
    }
}

// TD_SYM_MID: } on single-tap, EXTRA layer on double-tap
void td_fn_sym_mid(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_RCBR);  // Type right brace
    } else if (state->count == 2) {
        default_layer_set((layer_state_t)1 << EXTRA);  // Switch to EXTRA
    }
}

// TD_SYM_RING: $ on single-tap, TAP layer on double-tap
void td_fn_sym_ring(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_DLR);  // Type dollar sign
    } else if (state->count == 2) {
        default_layer_set((layer_state_t)1 << TAP);  // Switch to TAP
    }
}

// TD_SYM_PINKY: backslash on single-tap, reset on double-tap
void td_fn_sym_pinky(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_BSLS);  // Type backslash
    } else if (state->count == 2) {
        reset_keyboard();  // Reset keyboard
    }
}

// Auto-generated layer switching tap dances
// Each layer gets a tap dance that switches to it on double-tap

#define DEFINE_LAYER_TD(LAYER) \
    void td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
        if (state->count == 2) { \
            default_layer_set((layer_state_t)1 << LAYER); \
        } \
    }

DEFINE_LAYER_TD(BASE)
DEFINE_LAYER_TD(EXTRA)
DEFINE_LAYER_TD(TAP)
DEFINE_LAYER_TD(BUTTON)
DEFINE_LAYER_TD(NAV)
DEFINE_LAYER_TD(MOUSE)
DEFINE_LAYER_TD(MEDIA)
DEFINE_LAYER_TD(NUM)
DEFINE_LAYER_TD(SYM)
DEFINE_LAYER_TD(FUN)

// Custom shift handler - workaround for broken ONESHOT_TAP_TOGGLE
// Single tap = one-shot shift, Double tap = shift lock
bool shift_locked = false;

void td_fn_shift(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Single tap: One-shot shift
        if (shift_locked) {
            // If locked, unlock it
            shift_locked = false;
            unregister_mods(MOD_BIT(KC_LSFT));
        } else {
            // Normal one-shot behavior
            set_oneshot_mods(MOD_BIT(KC_LSFT));
        }
    } else if (state->count == 2) {
        // Double tap: Toggle shift lock
        if (shift_locked) {
            shift_locked = false;
            unregister_mods(MOD_BIT(KC_LSFT));
        } else {
            shift_locked = true;
            register_mods(MOD_BIT(KC_LSFT));
        }
    }
}

// ============================================================================
// Tap Dance Action Table
// ============================================================================
// 
// This table connects tap dance IDs to their handler functions.
// QMK looks up the handler here when a tap dance is triggered.

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT]       = ACTION_TAP_DANCE_FN(td_fn_boot),
    [TD_SYM_IDX]    = ACTION_TAP_DANCE_FN(td_fn_sym_idx),
    [TD_SYM_MID]    = ACTION_TAP_DANCE_FN(td_fn_sym_mid),
    [TD_SYM_RING]   = ACTION_TAP_DANCE_FN(td_fn_sym_ring),
    [TD_SYM_PINKY]  = ACTION_TAP_DANCE_FN(td_fn_sym_pinky),
    [TD_SHIFT]      = ACTION_TAP_DANCE_FN(td_fn_shift),
    
    // Layer switching tap dances
    [TD_U_BASE]     = ACTION_TAP_DANCE_FN(td_fn_U_BASE),
    [TD_U_EXTRA]    = ACTION_TAP_DANCE_FN(td_fn_U_EXTRA),
    [TD_U_TAP]      = ACTION_TAP_DANCE_FN(td_fn_U_TAP),
    [TD_U_BUTTON]   = ACTION_TAP_DANCE_FN(td_fn_U_BUTTON),
    [TD_U_NAV]      = ACTION_TAP_DANCE_FN(td_fn_U_NAV),
    [TD_U_MOUSE]    = ACTION_TAP_DANCE_FN(td_fn_U_MOUSE),
    [TD_U_MEDIA]    = ACTION_TAP_DANCE_FN(td_fn_U_MEDIA),
    [TD_U_NUM]      = ACTION_TAP_DANCE_FN(td_fn_U_NUM),
    [TD_U_SYM]      = ACTION_TAP_DANCE_FN(td_fn_U_SYM),
    [TD_U_FUN]      = ACTION_TAP_DANCE_FN(td_fn_U_FUN),
};

// ============================================================================
// Keymaps
// ============================================================================
// 
// These are the actual keymaps for all 10 layers.
// Each keyboard defines EXILE_MAPPING in its config.h to map the 36 keys
// to its physical layout. EXILE_LAYERMAPPING_XXX macros expand to EXILE_MAPPING.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE]   = EXILE_LAYERMAPPING_BASE(EXILE_LAYER_BASE),
    [EXTRA]  = EXILE_LAYERMAPPING_EXTRA(EXILE_LAYER_EXTRA),
    [TAP]    = EXILE_LAYERMAPPING_TAP(EXILE_LAYER_TAP),
    [BUTTON] = EXILE_LAYERMAPPING_BUTTON(EXILE_LAYER_BUTTON),
    [NAV]    = EXILE_LAYERMAPPING_NAV(EXILE_LAYER_NAV),
    [MOUSE]  = EXILE_LAYERMAPPING_MOUSE(EXILE_LAYER_MOUSE),
    [MEDIA]  = EXILE_LAYERMAPPING_MEDIA(EXILE_LAYER_MEDIA),
    [NUM]    = EXILE_LAYERMAPPING_NUM(EXILE_LAYER_NUM),
    [SYM]    = EXILE_LAYERMAPPING_SYM(EXILE_LAYER_SYM),
    [FUN]    = EXILE_LAYERMAPPING_FUN(EXILE_LAYER_FUN),
};

// ============================================================================
// Combos
// ============================================================================
// 
// Combos let you press multiple keys together to trigger an action.
// All combos work on the BASE layer using the home row keys.
// 
// IMPORTANT: Key codes must match the BASE layer exactly!
// Z = LT(BUTTON,KC_Z)
// X = ALGR_T(KC_X)
// C = KC_C
// V = KC_V

// Combo key sequences (order matters for overlapping combos)
const uint16_t PROGMEM combo_redo[]     = {LT(BUTTON,KC_Z), ALGR_T(KC_X), KC_C, COMBO_END};  // Z+X+C
const uint16_t PROGMEM combo_undo[]     = {LT(BUTTON,KC_Z), ALGR_T(KC_X), COMBO_END};         // Z+X
const uint16_t PROGMEM combo_copy_cut[] = {ALGR_T(KC_X), KC_C, COMBO_END};                    // X+C
const uint16_t PROGMEM combo_paste[]    = {KC_C, KC_V, COMBO_END};                            // C+V
const uint16_t PROGMEM combo_selall[]   = {LT(BUTTON,KC_Z), KC_V, COMBO_END};                 // Z+V
const uint16_t PROGMEM combo_save[]     = {KC_M, KC_COMM, COMBO_END};                         // M+,

// Combo table - connects sequences to actions
combo_t key_combos[] = {
    COMBO(combo_redo,     C(KC_Y)),          // Redo: Ctrl+Y
    COMBO(combo_undo,     C(KC_Z)),          // Undo: Ctrl+Z
    COMBO(combo_copy_cut, EXILE_COPY_CUT),   // Copy/Cut: Custom keycode
    COMBO(combo_paste,    C(KC_V)),          // Paste: Ctrl+V
    COMBO(combo_selall,   C(KC_A)),          // Select All: Ctrl+A
    COMBO(combo_save,     C(KC_S)),          // Save: Ctrl+S
};

// ============================================================================
// Custom Keycodes
// ============================================================================
// 
// Timer for the copy-cut key (to detect tap vs hold)
static uint16_t copy_cut_timer = 0;

/**
 * Process Record User
 * 
 * This function is called every time a key is pressed or released.
 * It handles custom keycodes that need special logic.
 * 
 * Return true:  QMK should process this key normally after this function
 * Return false: QMK should NOT process this key (we handled it completely)
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // EXILE_ARROW: Type → (or ⇒ when shifted)
        case EXILE_ARROW:
            if (record->event.pressed) {
                // Check if Shift is held
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Shift is pressed - type thick arrow (⇒)
                    del_mods(MOD_MASK_SHIFT);  // Temporarily remove shift
                    send_unicode_string("⇒");
                    set_mods(get_mods());      // Restore shift state
                } else {
                    // No shift - type normal arrow (→)
                    send_unicode_string("→");
                }
            }
            return false;  // We handled this key completely

        // EXILE_COPY_CUT: Tap=Copy, Hold=Cut
        case EXILE_COPY_CUT:
            if (record->event.pressed) {
                // Key pressed - start timer
                copy_cut_timer = timer_read();
            } else {
                // Key released - check how long it was held
                if (timer_elapsed(copy_cut_timer) < TAPPING_TERM) {
                    // Short press (tap) - Copy
                    tap_code16(C(KC_C));
                } else {
                    // Long press (hold) - Cut
                    tap_code16(C(KC_X));
                }
            }
            return false;  // We handled this key completely
    }
    
    // Key not handled by us - let QMK process it normally
    return true;
}

// ============================================================================
// Key Override
// ============================================================================
// 
// Key overrides change the behavior of keys when modifiers are held.
// This one makes Shift+CapsWord toggle normal Caps Lock.

const key_override_t capsword_key_override = ko_make_basic(
    MOD_MASK_SHIFT,   // When Shift is held
    CW_TOGG,          // And Caps Word toggle is pressed
    KC_CAPS           // Send Caps Lock instead
);

// Key override table - QMK uses this to find overrides
// Must be defined as an array for introspection to work properly
const key_override_t *key_overrides[] = {
    &capsword_key_override,
    NULL  // Must end with NULL
};

// ============================================================================
// Optional: OLED Task
// ============================================================================
// 
// If OLED is enabled for this keyboard, include the OLED code.
// This keeps the firmware smaller for keyboards without OLED.

#ifdef EXILE_OLED_ENABLE
#include "features/oled.h"
#include "features/oled.c"
#endif
