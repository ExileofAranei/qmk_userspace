# Corne Keyboard Rules
# ====================
# 
# This file tells QMK which features to enable for the Corne keyboard.
# It includes the shared user configuration and adds any keyboard-specific
# build options.

# Include the shared user configuration
# This brings in all the standard features: combos, tap dance, OLED, etc.
include $(QMK_USERSPACE)/users/exileofaranei/rules.mk

# ============================================================================
# Keyboard-Specific Features
# ============================================================================

# Corne-specific options can be added here if needed
# For example, if you had a Corne variant with RGB:
# RGBLIGHT_ENABLE = yes

# Console disabled - was used for debugging shift lock
# CONSOLE_ENABLE = yes

# ============================================================================
# Bootloader
# ============================================================================
# 
# For RP2040 microcontroller (Pi Pico), use the uf2 bootloader
# This allows flashing by copying the .uf2 file to the USB drive

BOOTLOADER = rp2040
