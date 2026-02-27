# ExileofAranei QMK Rules
# ========================
#
# This file tells QMK which features to compile and include.
# It applies to ALL keyboards using this user configuration.
#
# HOW THIS WORKS:
# - Each line like "MOUSEKEY_ENABLE = yes" turns on a feature
# - These features get compiled into the firmware
# - If you disable a feature, the code becomes smaller
#
# ADDING A NEW KEYBOARD:
# Just include this file in your keyboard's rules.mk:
#     include users/exileofaranei/rules.mk

# ============================================================================
# Essential Features
# ============================================================================

# Mouse keys - allows using keyboard keys to control mouse cursor
MOUSEKEY_ENABLE = yes

# Extra keys - media keys, system keys (sleep, wake, etc.)
EXTRAKEY_ENABLE = yes

# Auto Shift - hold keys to type shifted versions
AUTO_SHIFT_ENABLE = yes

# Tap Dance - different actions for single vs double tap
TAP_DANCE_ENABLE = yes

# Combos - press multiple keys together for special actions
COMBO_ENABLE = yes

# ============================================================================
# Text Editing Features
# ============================================================================

# Caps Word - automatically capitalize words
CAPS_WORD_ENABLE = yes

# Key Override - override key behavior with modifiers
KEY_OVERRIDE_ENABLE = yes

# Unicode - type special characters (arrows, etc.)
UNICODE_ENABLE = yes

# ============================================================================
# WPM Calculation
# ============================================================================

# Words Per Minute - calculate typing speed for OLED display
WPM_ENABLE = yes

# ============================================================================
# OLED Support (Optional)
# ============================================================================
#
# OLED is enabled per-keyboard by defining EXILE_OLED_ENABLE in config.h
# This keeps the code size smaller for keyboards without OLEDs.

# Check if OLED is enabled for this keyboard build
ifeq ($(strip $(EXILE_OLED_ENABLE)), yes)
    OLED_ENABLE = yes
endif

# ============================================================================
# Introspection Keymap
# ============================================================================
#
# This tells QMK to use the keymaps defined in exileofaranei.c
# instead of looking for them in the keyboard's keymap.c file.
#
# This is what makes the configuration reusable across keyboards!

INTROSPECTION_KEYMAP_C = $(QMK_USERSPACE)/users/exileofaranei/exileofaranei.c

# ============================================================================
# Build Configuration
# ============================================================================

# Enable link time optimization - makes firmware smaller
LTO_ENABLE = yes

# Disable unused features to save space
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

# ============================================================================
# Debugging (Optional)
# ============================================================================
#
# Uncomment these to enable debugging output via QMK Toolbox
# Only use when troubleshooting!

# CONSOLE_ENABLE = yes
# COMMAND_ENABLE = yes
