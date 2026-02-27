/**
 * Corne Keyboard Configuration
 * =============================
 *
 * This is the keyboard-specific configuration for the Corne (CRKBD) Rev1.
 * It enables features that are specific to this keyboard:
 * - OLED display (Corne has OLEDs)
 * - Master right side (your configuration)
 *
 * This file is separate from the user config so different keyboards
 * can have different features enabled.
 */

#pragma once

// ============================================================================
// Layout Mapping for Corne
// ============================================================================
//
// Corne uses LAYOUT_split_3x6_3 which has 42 positions (3 rows x 6 cols x 2 sides + 6 thumbs).
// We map our 36-key Miryoku layout to the Corne matrix by placing keys in the inner positions
// and using KC_NO for the outer columns.

#define EXILE_MAPPING( \
    K00, K01, K02, K03, K04,   K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14,   K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24,   K25, K26, K27, K28, K29, \
    N30, N31, K32, K33, K34,   K35, K36, K37, N38, N39  \
) \
LAYOUT_split_3x6_3( \
    KC_NO, K00, K01, K02, K03, K04,   K05, K06, K07, K08, K09, KC_NO, \
    KC_NO, K10, K11, K12, K13, K14,   K15, K16, K17, K18, K19, KC_NO, \
    KC_NO, K20, K21, K22, K23, K24,   K25, K26, K27, K28, K29, KC_NO, \
                      K32, K33, K34,   K35, K36, K37                   \
)

// ============================================================================
// Custom Base Layer Mapping for Russian Language Support
// ============================================================================
//
// Corne has 6 extra keys (3 on each side) compared to standard Miryoku 36-key layout.
// We use these for Russian language input:
// - Left outer column: KC_GRV (top), KC_NO (middle), OS_LSFT (bottom)
// - Right outer column: KC_LBRC (top), KC_QUOT (middle), KC_RBRC (bottom)
//
// Layout:
// ┌─────┬─────┬─────┬─────┬─────┬─────┐   ┌─────┬─────┬─────┬─────┬─────┬─────┐
// │ GRV │  Q  │  W  │  E  │  R  │  T  │   │  Y  │  U  │  I  │  O  │  P  │ [   │
// ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
// │     │  A  │  S  │  D  │  F  │  G  │   │  H  │  J  │  K  │  L  │  ;  │ '   │
// ├─────┼─────┼─────┼─────┼─────┼─────┤   ├─────┼─────┼─────┼─────┼─────┼─────┤
// │ SFT │  Z  │  X  │  C  │  V  │  B  │   │  N  │  M  │  ,  │  .  │  /  │ ]   │
// └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────┴─────┴─────┴─────┴─────┘
//                   │ ESC │ SPC │ TAB │   │ ENT │ BSP │ DEL │
//                   └─────┴─────┴─────┘   └─────┴─────┴─────┘

// Helper macro to force expansion
#define EXILE_CORNE_EXPAND(x) x

#undef EXILE_LAYERMAPPING_BASE
#define EXILE_LAYERMAPPING_BASE(...) \
    EXILE_CORNE_EXPAND(EXILE_CORNE_BASE_MAPPING(__VA_ARGS__))

#define EXILE_CORNE_BASE_MAPPING( \
    K00, K01, K02, K03, K04,   K05, K06, K07, K08, K09, \
    K10, K11, K12, K13, K14,   K15, K16, K17, K18, K19, \
    K20, K21, K22, K23, K24,   K25, K26, K27, K28, K29, \
    N30, N31, K32, K33, K34,   K35, K36, K37, N38, N39  \
) \
LAYOUT_split_3x6_3( \
    KC_GRV, K00, K01, K02, K03, K04,   K05, K06, K07, K08, K09, KC_LBRC, \
    OS_LCTL,  K10, K11, K12, K13, K14,   K15, K16, K17, K18, K19, KC_QUOT, \
    TD(TD_SHIFT), K20, K21, K22, K23, K24,   K25, K26, K27, K28, K29, KC_RBRC, \
                      K32, K33, K34,   K35, K36, K37                   \
)

// ============================================================================
// Hand Configuration
// ============================================================================
//
// Tell QMK which side is the master (connected to USB).
// The other side is the slave (connected via TRRS cable).

// Use right side as master (connected to USB)
#define MASTER_RIGHT

// Alternative options (commented out):
// #define MASTER_LEFT   // Use left side as master
// #define EE_HANDS      // Use EEPROM to remember which side is which

// ============================================================================
// OLED Configuration
// ============================================================================
//
// Enable OLED support for this keyboard.
// This define is checked in users/exileofaranei/rules.mk to enable OLED_ENABLE.

#define EXILE_OLED_ENABLE

// ============================================================================
// Caps Word Configuration
// ============================================================================
//
// Both Shift keys together toggle Caps Word mode.
// Caps Word automatically capitalizes words and turns off after word ends.

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// ============================================================================
// Mouse Configuration
// ============================================================================
//
// Additional mouse settings specific to this keyboard.

// Time to reach maximum mouse speed
// Must undef first to avoid redefinition error
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 200

// ============================================================================
// Font Configuration
// ============================================================================
//
// Use the standard Corne OLED font.
// This font includes special characters for the Corne logo.

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

// ============================================================================
// Font Configuration
// https://docs.qmk.fm/features/split_keyboard
// ============================================================================
#define SPLIT_OLED_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_ST7565_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WPM_ENABLE
