/**
 * ExileofAranei QMK User Configuration
 * =====================================
 * 
 * This file defines all layers, custom keycodes, and helper macros
 * that are shared across ALL keyboards in this userspace.
 * 
 * HOW TO ADD A NEW KEYBOARD:
 * 1. Create folder: keyboards/<name>/keymaps/exileofaranei/
 * 2. Create config.h with: #define EXILE_OLED_ENABLE (if keyboard has OLED)
 * 3. Create rules.mk with: include users/exileofaranei/rules.mk
 * 4. Create empty keymap.c (keymaps come from this user folder)
 */

#pragma once

#include QMK_KEYBOARD_H

// ============================================================================
// Layer Definitions
// ============================================================================
// 
// We use an enum to assign numbers to each layer automatically.
// BASE = 0, EXTRA = 1, TAP = 2, etc.
// 
// These layer names match Miryoku naming convention.

enum layers {
    BASE,    // 0 - Main typing layer (QWERTY with home row mods)
    EXTRA,   // 1 - Alternative base layer (COLEMAK, DVORAK, etc.)
    TAP,     // 2 - Same as BASE but without home row mods
    BUTTON,  // 3 - Mouse buttons on home row
    NAV,     // 4 - Navigation (arrows, home, end)
    MOUSE,   // 5 - Mouse movement and scrolling
    MEDIA,   // 6 - Media keys (play, pause, volume)
    NUM,     // 7 - Numpad on right hand
    SYM,     // 8 - Symbols and brackets
    FUN,     // 9 - Function keys F1-F12
    _LAYER_COUNT  // Used internally to know how many layers we have
};

// ============================================================================
// Custom Keycodes
// ============================================================================
// 
// These are special keys that do more than just type a character.
// They are handled in process_record_user() in exileofaranei.c

enum custom_keycodes {
    EXILE_ARROW = SAFE_RANGE,  // → arrow symbol (Shift: ⇒)
    EXILE_COPY_CUT,            // Tap=Copy(Ctrl+C), Hold=Cut(Ctrl+X)
};

// ============================================================================
// Tap Dance Enums
// ============================================================================
// 
// Tap dance allows different actions for single-tap vs double-tap.
// For example: tap '$' once to type '$', twice to switch to TAP layer.

enum tap_dances {
    TD_BOOT,      // Double-tap to reset keyboard
    TD_SYM_IDX,   // { on tap, BASE layer on double-tap
    TD_SYM_MID,   // } on tap, EXTRA layer on double-tap  
    TD_SYM_RING,  // $ on tap, TAP layer on double-tap
    TD_SYM_PINKY, // \ on tap, reset on double-tap
    TD_SHIFT,     // Custom shift: single = one-shot, double = lock
    // Auto-generated layer switching tap dances:
    #define X(LAYER) TD_U_##LAYER,
    X(BASE) X(EXTRA) X(TAP) X(BUTTON) X(NAV) X(MOUSE) X(MEDIA) X(NUM) X(SYM) X(FUN)
    #undef X
};

// Custom shift lock state (TD_SHIFT tap dance)
extern bool shift_locked;

// ============================================================================
// Helper Macros
// ============================================================================
// 
// These make the keymap definitions cleaner and easier to read.

// U_NP = Key is Not Present (used for padding in matrix positions)
// U_NA = Key is present but Not Available for use
// U_NU = Key is available but Not Used
#define U_NP KC_NO
#define U_NA KC_NO  
#define U_NU KC_NO

// Clipboard shortcuts - using Windows/Linux defaults
// U_RDO = Redo, U_PST = Paste, U_CPY = Copy, U_CUT = Cut, U_UND = Undo
#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

// ============================================================================
// Layer Mapping Macro
// ============================================================================
// 
// This macro maps the 36-key Miryoku layout to a specific keyboard matrix.
// Each keyboard defines how to place these 36 keys in its physical layout.
// 
// The numbers represent positions:
//   00 01 02 03 04     05 06 07 08 09    <- Top row (10 keys)
//   10 11 12 13 14     15 16 17 18 19    <- Home row (10 keys)
//   20 21 22 23 24     25 26 27 28 29    <- Bottom row (10 keys)
//         32 33 34     35 36 37          <- Thumb row (6 keys)

// ============================================================================
// Layer Mapping Macro
// ============================================================================
// 
// This macro maps the 36-key Miryoku layout to a specific keyboard matrix.
// Each keyboard MUST define this macro in its config.h BEFORE including
// exileofaranei.h. The macro should expand to the keyboard's LAYOUT macro.
//
// Example for Corne:
// #define EXILE_MAPPING(...) LAYOUT_split_3x6_3(__VA_ARGS__)
//
// The numbers represent positions:
//   00 01 02 03 04     05 06 07 08 09    <- Top row (10 keys)
//   10 11 12 13 14     15 16 17 18 19    <- Home row (10 keys)
//   20 21 22 23 24     25 26 27 28 29    <- Bottom row (10 keys)
//         32 33 34     35 36 37          <- Thumb row (6 keys)

// ============================================================================
// Layer Definitions
// ============================================================================
// 
// Each layer is defined as a 4x10 grid (36 keys total).
// These use home row mods: GUI/ALT/CTL/SHIFT on the home positions.

// BASE Layer: QWERTY with home row mods
// ┌─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┐
// │  Q  │  W  │  E  │  R  │  T  │   │  Y  │  U  │  I  │  O  │  P  │
// │     │     │     │     │     │   │     │     │     │     │     │
// ├─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┤
// │  A  │  S  │  D  │  F  │  G  │   │  H  │  J  │  K  │  L  │  ;  │
// │ GUI │ ALT │ CTL │ SFT │     │   │     │ SFT │ CTL │ ALT │ GUI │
// ├─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┤
// │  Z  │  X  │  C  │  V  │  B  │   │  N  │  M  │  ,  │  .  │  /  │
// │ BTN │ ALGR│     │     │     │   │     │     │     │ ALGR│ BTN │
// └─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┘
//             │ ESC │ SPC │ TAB │   │ ENT │ BSP │ DEL │
//             │ MED │ NAV │ MOU │   │ SYM │ NUM │ FUN │

#define EXILE_LAYER_BASE \
    KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,                \
    LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_SCLN),     \
    LT(BUTTON,KC_Z),   ALGR_T(KC_X),      KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           ALGR_T(KC_DOT),    LT(BUTTON,KC_SLSH),  \
    U_NP,              U_NP,              LT(MEDIA,KC_ESC),  LT(NAV,KC_SPC),    LT(MOUSE,KC_TAB),  LT(SYM,KC_ENT),    LT(NUM,KC_BSPC),   LT(FUN,KC_DEL),    U_NP,              U_NP

// NAV Layer: Navigation keys
// Arrow keys on right hand, home/end/page up/page down
#define EXILE_LAYER_NAV \
    TD(TD_BOOT),       TD(TD_U_TAP),      TD(TD_U_EXTRA),    TD(TD_U_BASE),     U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,               \
    KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              CW_TOGG,           KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,             \
    U_NA,              KC_ALGR,           TD(TD_U_NUM),      TD(TD_U_NAV),      U_NA,              KC_INS,            KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,              \
    U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_ENT,            KC_BSPC,           KC_DEL,            U_NP,              U_NP

// MOUSE Layer: Mouse control
// Mouse movement on right hand, scrolling with wheel
#define EXILE_LAYER_MOUSE \
    TD(TD_BOOT),       TD(TD_U_TAP),      TD(TD_U_EXTRA),    TD(TD_U_BASE),     U_NA,              U_RDO,             U_PST,             U_CPY,             U_CUT,             U_UND,               \
    KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              U_NU,              MS_LEFT,           MS_DOWN,           MS_UP,             MS_RGHT,             \
    U_NA,              KC_ALGR,           TD(TD_U_SYM),      TD(TD_U_MOUSE),    U_NA,              U_NU,              MS_WHLL,           MS_WHLD,           MS_WHLU,           MS_WHLR,             \
    U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              MS_BTN2,           MS_BTN1,           MS_BTN3,           U_NP,              U_NP

// MEDIA Layer: Media controls
// Volume, play/pause, track skip on right hand
#define EXILE_LAYER_MEDIA \
    TD(TD_BOOT),       TD(TD_U_TAP),      TD(TD_U_EXTRA),    TD(TD_U_BASE),     U_NA,              U_NU,              U_NU,              U_NU,              U_NU,              U_NU,                \
    KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              U_NU,              KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,             \
    U_NA,              KC_ALGR,           TD(TD_U_FUN),      TD(TD_U_MEDIA),    U_NA,              OU_AUTO,           U_NU,              U_NU,              U_NU,              U_NU,                \
    U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE,           U_NP,              U_NP

// NUM Layer: Numpad
// Numbers on right hand in telephone layout (1-2-3 bottom row)
#define EXILE_LAYER_NUM \
    KC_LBRC,           KC_7,              KC_8,              KC_9,              KC_RBRC,           U_NA,              TD(TD_U_BASE),     TD(TD_U_EXTRA),    TD(TD_U_TAP),      TD(TD_BOOT),         \
    KC_SCLN,           KC_4,              KC_5,              KC_6,              KC_EQL,            U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             \
    KC_GRV,            KC_1,              KC_2,              KC_3,              KC_BSLS,           U_NA,              TD(TD_U_NUM),      TD(TD_U_NAV),      KC_ALGR,           U_NA,                \
    U_NP,              U_NP,              KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// SYM Layer: Symbols
// Brackets, operators, special characters
#define EXILE_LAYER_SYM \
    KC_GRV,            KC_LABK,           KC_RABK,           KC_MINS,           KC_PIPE,           KC_CIRC,           TD(TD_SYM_IDX),    TD(TD_SYM_MID),    TD(TD_SYM_RING),   TD(TD_SYM_PINKY),    \
    KC_EXLM,           KC_ASTR,           KC_SLSH,           KC_EQL,            KC_AMPR,           KC_HASH,           KC_LPRN,           KC_RPRN,           KC_SCLN,           KC_DQUO,             \
    KC_TILD,           KC_PLUS,           KC_LBRC,           KC_RBRC,           KC_PERC,           KC_AT,             KC_COLN,           KC_COMM,           KC_DOT,            KC_QUOT,             \
    U_NP,              U_NP,              KC_LPRN,           KC_RPRN,           KC_UNDS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// FUN Layer: Function keys
// F1-F12 in easy-to-reach positions
#define EXILE_LAYER_FUN \
    KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              TD(TD_U_BASE),     TD(TD_U_EXTRA),    TD(TD_U_TAP),      TD(TD_BOOT),         \
    KC_F11,            KC_F4,             KC_F5,             KC_F6,             KC_SCRL,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             \
    KC_F10,            KC_F1,             KC_F2,             KC_F3,             KC_PAUS,           U_NA,              TD(TD_U_FUN),      TD(TD_U_MEDIA),    KC_ALGR,           U_NA,                \
    U_NP,              U_NP,              KC_APP,            KC_SPC,            KC_TAB,            U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// BUTTON Layer: Mouse buttons on home row
// Easy access to mouse clicks without moving fingers
#define EXILE_LAYER_BUTTON \
    U_NP,              U_NP,              U_NP,              U_NP,              U_NP,              U_NP,              U_NP,              U_NP,              U_NP,              U_NP,                \
    KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NP,              U_NP,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,             \
    U_NP,              KC_ALGR,           U_NP,              U_NP,              U_NP,              U_NP,              U_NP,              U_NP,              KC_ALGR,           U_NP,                \
    U_NP,              U_NP,              MS_BTN2,           MS_BTN3,           MS_BTN1,           MS_BTN1,           MS_BTN3,           MS_BTN2,           U_NP,              U_NP

// EXTRA Layer: Alternative base (same structure as BASE, can be customized)
// By default, same as BASE but can be overridden per-keyboard
#ifndef EXILE_LAYER_EXTRA
#define EXILE_LAYER_EXTRA EXILE_LAYER_BASE
#endif

// TAP Layer: Same as BASE but without home row mods
// Useful when you want to type without accidentally triggering mods
#ifndef EXILE_LAYER_TAP
#define EXILE_LAYER_TAP \
    KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,                \
    KC_A,              KC_S,              KC_D,              KC_F,              KC_G,              KC_H,              KC_J,              KC_K,              KC_L,              KC_SCLN,             \
    KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMM,           KC_DOT,            KC_SLSH,             \
    U_NP,              U_NP,              LT(MEDIA,KC_ESC),  LT(NAV,KC_SPC),    LT(MOUSE,KC_TAB),  LT(SYM,KC_ENT),    LT(NUM,KC_BSPC),   LT(FUN,KC_DEL),    U_NP,              U_NP
#endif

// Custom Shift Lock - workaround for ONESHOT_TAP_TOGGLE not working
// ============================================================================
// Layer Mapping for Specific Keyboards
// ============================================================================
// 
// These macros define how each layer is mapped to a keyboard's physical layout.
// 
// The EXILE_EXPAND macro forces the preprocessor to expand the layer content
// BEFORE passing it to EXILE_MAPPING. This is necessary because macros with
// backslash continuation (like EXILE_LAYER_BASE) need to be fully expanded.
//
// Keyboards can override EXILE_LAYERMAPPING_BASE to add extra keys on the outer
// columns (like for Russian language support on Corne).

#define EXILE_EXPAND(x) x

// Only define these if the keyboard hasn't already defined custom mappings
#ifndef EXILE_LAYERMAPPING_BASE
#define EXILE_LAYERMAPPING_BASE(...)    EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_EXTRA
#define EXILE_LAYERMAPPING_EXTRA(...)   EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_TAP
#define EXILE_LAYERMAPPING_TAP(...)     EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_BUTTON
#define EXILE_LAYERMAPPING_BUTTON(...)  EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_NAV
#define EXILE_LAYERMAPPING_NAV(...)     EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_MOUSE
#define EXILE_LAYERMAPPING_MOUSE(...)   EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_MEDIA
#define EXILE_LAYERMAPPING_MEDIA(...)   EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_NUM
#define EXILE_LAYERMAPPING_NUM(...)     EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_SYM
#define EXILE_LAYERMAPPING_SYM(...)     EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
#ifndef EXILE_LAYERMAPPING_FUN
#define EXILE_LAYERMAPPING_FUN(...)     EXILE_EXPAND(EXILE_MAPPING(__VA_ARGS__))
#endif
