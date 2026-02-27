// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 2 of the License, or (at your option)
// any later version. This program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
// Public License for more details. You should have received a copy of the GNU
// General Public License along with this program. If not, see
// <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H
#include "manna-harbour_miryoku.h"


// ============================================================
// Tap Dance
// ============================================================

enum {
    U_TD_BOOT,
    U_TD_SYM_INDEX,
    U_TD_SYM_MIDDLE,
    U_TD_SYM_RING,
    U_TD_SYM_PINKY,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
    MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        reset_keyboard();
    }
}

void u_td_sym_index(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_LCBR); // {
    } else if (state->count == 2) {
        default_layer_set((layer_state_t)1 << U_BASE);
    }
}

void u_td_sym_middle(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_RCBR); // }
    } else if (state->count == 2) {
        default_layer_set((layer_state_t)1 << U_EXTRA);
    }
}

void u_td_sym_ring(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_DLR); // $
    } else if (state->count == 2) {
        default_layer_set((layer_state_t)1 << U_TAP);
    }
}

void u_td_sym_pinky(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_BSLS); // backslash
    } else if (state->count == 2) {
        reset_keyboard();
    }
}

#define MIRYOKU_X(LAYER, STRING)                                               \
    void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) {        \
        if (state->count == 2) {                                               \
            default_layer_set((layer_state_t)1 << U_##LAYER);                  \
        }                                                                      \
    }
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT]       = ACTION_TAP_DANCE_FN(u_td_fn_boot),
#define MIRYOKU_X(LAYER, STRING) \
    [U_TD_U_##LAYER]  = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
    MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
    [U_TD_SYM_INDEX]  = ACTION_TAP_DANCE_FN(u_td_sym_index),
    [U_TD_SYM_MIDDLE] = ACTION_TAP_DANCE_FN(u_td_sym_middle),
    [U_TD_SYM_RING]   = ACTION_TAP_DANCE_FN(u_td_sym_ring),
    [U_TD_SYM_PINKY]  = ACTION_TAP_DANCE_FN(u_td_sym_pinky),
};


// ============================================================
// Keymaps
// ============================================================

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) \
    [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
    MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};


// ============================================================
// Key Overrides
// ============================================================

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL,
};


// ============================================================
// Custom Keycodes
// ============================================================

enum custom_keycodes {
    ARROW = SAFE_RANGE,
    CC_COPY_CUT, // tap = copy (Ctrl+C), hold = cut (Ctrl+X)
};

static uint16_t copy_cut_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    send_unicode_string("⇒"); // Shifted: ⇒ (U+21D2)
                    set_mods(get_mods());
                } else {
                    send_unicode_string("→"); // Unshifted: → (U+2192)
                }
            }
            return false;

        case CC_COPY_CUT:
            if (record->event.pressed) {
                copy_cut_timer = timer_read();
            } else {
                if (timer_elapsed(copy_cut_timer) < TAPPING_TERM) {
                    tap_code16(C(KC_C)); // tap: copy
                } else {
                    tap_code16(C(KC_X)); // hold: cut
                }
            }
            return false;
    }
    return true;
}


// ============================================================
// Combos
// ============================================================

#ifdef COMBO_ENABLE

// Key codes must match the base layer exactly:
//   Z = LT(U_BUTTON, KC_Z)
//   X = ALGR_T(KC_X)
//   C = KC_C
//   V = KC_V

// combo_redo must come before combo_undo so QMK matches the longer sequence first
const uint16_t PROGMEM combo_redo[]     = {LT(U_BUTTON, KC_Z), ALGR_T(KC_X), KC_C, COMBO_END};
const uint16_t PROGMEM combo_undo[]     = {LT(U_BUTTON, KC_Z), ALGR_T(KC_X), COMBO_END};
const uint16_t PROGMEM combo_copy_cut[] = {ALGR_T(KC_X), KC_C, COMBO_END};
const uint16_t PROGMEM combo_paste[]    = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_selall[]   = {LT(U_BUTTON, KC_Z), KC_V, COMBO_END};
const uint16_t PROGMEM combo_save[]     = {KC_M, KC_COMM, COMBO_END};


combo_t key_combos[5] = {
    COMBO(combo_redo,     C(KC_Y)),
    COMBO(combo_undo,     C(KC_Z)),
    COMBO(combo_copy_cut, CC_COPY_CUT),
    COMBO(combo_paste,    C(KC_V)),
    COMBO(combo_selall,   C(KC_A)),
    COMBO(combo_save,     C(KC_S)),
};

#endif // COMBO_ENABLE


// ============================================================
// Thumb Combos (optional)
// ============================================================

#if defined(MIRYOKU_KLUDGE_THUMBCOMBOS)

const uint16_t PROGMEM thumbcombos_base_right[] = {LT(U_SYM, KC_ENT),  LT(U_NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[]  = {LT(U_NAV, KC_SPC),  LT(U_MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[]         = {KC_ENT,  KC_BSPC,  COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[]       = {KC_BTN2, KC_BTN1,  COMBO_END};
const uint16_t PROGMEM thumbcombos_media[]       = {KC_MSTP, KC_MPLY,  COMBO_END};
const uint16_t PROGMEM thumbcombos_num[]         = {KC_0,    KC_MINS,  COMBO_END};
const uint16_t PROGMEM thumbcombos_fun[]         = {KC_SPC,  KC_TAB,   COMBO_END};

#if defined(MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
#else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
#endif

combo_t key_combos[COMBO_COUNT] = {
    COMBO(thumbcombos_base_right, LT(U_FUN, KC_DEL)),
    COMBO(thumbcombos_base_left,  LT(U_MEDIA, KC_ESC)),
    COMBO(thumbcombos_nav,        KC_DEL),
    COMBO(thumbcombos_mouse,      KC_BTN3),
    COMBO(thumbcombos_media,      KC_MUTE),
    COMBO(thumbcombos_num,        KC_DOT),
#if defined(MIRYOKU_LAYERS_FLIP)
    COMBO(thumbcombos_sym,        KC_RPRN),
#else
    COMBO(thumbcombos_sym,        KC_LPRN),
#endif
    COMBO(thumbcombos_fun,        KC_APP),
};

#endif // MIRYOKU_KLUDGE_THUMBCOMBOS
