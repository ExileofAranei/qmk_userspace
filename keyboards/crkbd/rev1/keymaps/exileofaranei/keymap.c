/**
 * Corne Keyboard Keymap
 * =====================
 * 
 * This file exists because QMK expects a keymap.c in each keymap folder.
 * However, we're using the INTROSPECTION_KEYMAP_C feature to use keymaps
 * defined in users/exileofaranei/exileofaranei.c instead.
 * 
 * This approach means:
 * - One keymap definition works for ALL keyboards
 * - No need to copy-paste keymaps for each new keyboard
 * - Changes to layers automatically apply everywhere
 * 
 * The actual keymaps are in: users/exileofaranei/exileofaranei.c
 */

#include QMK_KEYBOARD_H

// This file is intentionally minimal.
// All keymaps, combos, and tap dances are defined in the user folder.
// See: users/exileofaranei/exileofaranei.c
// 
// Note: oneshot_locked_mods_changed_user callback is defined in exileofaranei.c
