/**
 * ExileofAranei QMK Configuration
 * =================================
 *
 * This file contains QMK settings that apply to ALL keyboards
 * using this user configuration.
 *
 * These settings control timing, features, and behavior.
 */

#pragma once

// ============================================================================
// Tapping Settings
// ============================================================================
//
// Tapping term controls how long you need to hold a key before
// it registers as a "hold" (modifier) instead of a "tap" (normal key).
//
// Example: Hold 'A' for 200ms → acts as GUI key
//          Tap 'A' quickly   → types 'a'

#undef TAPPING_TERM
#define TAPPING_TERM 200  // Milliseconds (200 is a good default)

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// This means double-tapping a home row mod won't keep the mod held down.
#define QUICK_TAP_TERM 0

// ============================================================================
// Auto Shift Settings
// ============================================================================
//
// Auto Shift lets you type capital letters by holding a key longer
// instead of using Shift. This is disabled for alphas here because
// we use home row mods which could conflict.

// Disable auto-shift on alphas (A-Z), only use on numbers/symbols
#define NO_AUTO_SHIFT_ALPHA

// Use same timing as tapping term for consistency
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM

// Don't require setup - auto shift works immediately
#define AUTO_SHIFT_NO_SETUP

// ============================================================================
// Mouse Key Settings
// ============================================================================
//
// Controls how the mouse keys behave (speed, acceleration, etc.)
// Keyboards can override these by defining them before this file is included.

// Mouse key settings - keyboards can override in their config.h
// We only define these if the keyboard hasn't already defined them

#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0   // No delay before movement starts

#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       8   // Time between movements (ms)

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0   // No delay for scrolling

#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6   // Maximum cursor speed

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64  // Time to reach max speed (ms)

// ============================================================================
// Combo Settings
// ============================================================================
//
// Combos let you press multiple keys together to trigger an action.
// Example: Press Z+X together → Undo (Ctrl+Z)

// Time window for combos (ms) - keys must be pressed within this time
#define COMBO_TERM 40

// Number of combos defined (must match the number in exileofaranei.c)
#define COMBO_COUNT 6

// ============================================================================
// Oneshot Modifier Settings
// ============================================================================
//
// Oneshot mods let you tap a modifier once, then it applies to the next key only.
// Example: Tap GUI → next key press gets GUI modifier, then mod turns off.

// Number of taps to toggle oneshot mode (2 = double-tap to lock)
#define ONESHOT_TAP_TOGGLE 2

// ============================================================================
// Unicode Settings (for EXILE_ARROW keycode)
// ============================================================================
//
// Unicode allows typing special characters like arrows (→ ⇒).
// We support both Windows and Linux methods.

#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_LINUX

// ============================================================================
// Caps Word Settings
// ============================================================================
//
// Caps Word automatically capitalizes words when enabled.
// It turns off when you press a non-alpha key or space.

// ============================================================================
// WPM Settings
// ============================================================================
//
// Words Per Minute calculation for OLED display.
// WPM is calculated automatically based on typing speed.

// WPM feature is enabled in rules.mk
// No additional config needed - it just works!

// ============================================================================
// OLED Settings
// ============================================================================
//
// OLED display settings. These only apply if EXILE_OLED_ENABLE is defined
// in the keyboard's config.h file.

#ifdef EXILE_OLED_ENABLE
    // OLED rotation - 270 degrees works well for Corne vertical OLEDs
    #define OLED_ROTATION_270

    // WPM calculation for OLED
    #define WPM_ENABLE

    // OLED timeout - turn off after 5 minutes of inactivity (in ms)
    #define OLED_TIMEOUT 300000
#endif

// ============================================================================
// Keyboard-specific Overrides
// ============================================================================
//
// Keyboards can override these settings in their own config.h
// by using #undef and #define again.

// Example in keyboard config.h:
// #undef TAPPING_TERM
// #define TAPPING_TERM 150  // Faster tapping for this keyboard
