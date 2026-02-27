# AGENTS.md - QMK Userspace Development Guide

This document provides guidance for agentic coding agents operating in this repository.

## Project Overview

This is a QMK (Quantum Mechanical Keyboard) userspace repository. It allows maintaining custom keyboard keymaps outside the main QMK firmware repository. The actual keyboard firmware code lives in the QMK firmware directory, which is configured via `qmk config user.qmk_home`.

## Build Commands

### Local Build

```bash
# Compile a specific keyboard/keymap
qmk compile -kb <keyboard> -km <keymap>

# Or using make directly
make <keyboard>:<keymap>

# Build all userspace targets (after adding via qmk userspace-add)
qmk userspace-compile
```

### GitHub Actions Build

Pushes to the repository automatically trigger GitHub Actions workflow (`.github/workflows/build_binaries.yaml`) which builds all targets and publishes firmware as releases.

### Single Test/Build

QMK doesn't have traditional unit tests. To verify a single keymap compiles:

```bash
# Single keyboard build
qmk compile -kb <keyboard> -km <keymap>

# Or use make with specific target
make <keyboard>:<keymap>
```

### Linting

For C code linting, QMK uses `clang-format` and `clang-tidy`:

```bash
# Format C code (requires clang-format)
clang-format -i <file.c>

# Check formatting without modifying
clang-format --dry-run -Werror <file.c>
```

## Code Style Guidelines

### General Principles

- This is a C-based embedded firmware project (QMK)
- Code must be compatible with AVR and ARM microcontrollers
- Keep code minimal and efficient for embedded constraints

### Formatting (`.clang-format`)

The repository uses Google-based formatting with these key settings:

- **Indent**: 4 spaces (no tabs)
- **Column limit**: 1000
- **Pointer alignment**: Right (`char *ptr`)
- **Max empty lines**: 1
- **Use tabs**: Never

Run `clang-format -i <file>` to auto-format.

### File Organization

```
users/<username>/           # User keymap directory
  ├── rules.mk              # Build rules
  ├── config.h              # User configuration
  ├── keymap.c              # Keymap definition
  └── lib/                  # Helper functions

keyboards/<board>/keymaps/<keymap>/  # Keyboard-specific keymaps
layouts/<layout>/<keymap>/           # Layout-based keymaps
```

### Naming Conventions

- **Functions**: `snake_case` (e.g., `process_record_user`)
- **Variables**: `snake_case` (e.g., `custom_key`)
- **Constants/Defines**: `UPPER_SNAKE_CASE` (e.g., `MY_CUSTOM_KEY`)
- **Keymap layers**: Descriptive names (e.g., `_QWERTY`, `_LAYER_NAME`)

### Keymap Structure

```c
// Typical keymap.c structure
#include QMK_KEYBOARD_H

// Custom macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) { ... }

// Layer indicators
layer_state_t layer_state_set_user(layer_state_t state) { ... }

// Keymap definition
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        // 36-key layout definition
    ),
};
```

### Import Conventions

- Always `#include QMK_KEYBOARD_H` first
- Standard library includes for C (`#include <string.h>`, etc.)
- User library includes: `#include "lib/filename.h"`

### Error Handling

- QMK uses return values for error handling (typically `true`/`false`)
- Check return values from QMK API functions
- Use `void` return type for functions that cannot fail

### QMK-Specific Patterns

- **Keycodes**: Use QMK keycodes (`KC_A`, `LT()`, `MT()`, etc.)
- **Tap-dance**: Use `tap_dance_fn_t` and related macros
- **OLED**: Use `oled_driver.c` APIs
- **RGB**: Use `rgb_matrix_driver.c` APIs
- **VIA**: Define `VARIANT_INCLUDE` and layout macros

### EditorConfig

The project includes `.editorconfig` which should be respected:
- 4-space indentation for C
- Tab indentation for Makefiles
- UTF-8 charset
- LF line endings

### Recommended VSCode Extensions

- `llvm-vs-code-extensions.vsclangd` - C/C++ language support
- `xaver.clang-format` - Code formatting
- `EditorConfig.EditorConfig` - Editor config support

## Configuration

### QMK Configuration

Userspace requires QMK to be set up:

```bash
qmk setup                    # Initial setup
qmk config user.overlay_dir="$(realpath .)"  # Enable userspace
```

### Adding New Keymaps

```bash
# Create new keymap
qmk new-keymap -kb <keyboard> -km <keymap>

# Add to userspace build list
qmk userspace-add -kb <keyboard> -km <keymap>

# List current targets
qmk userspace-list
```

## Known Constraints

- No native test framework in QMK userspace
- Build verification is done via successful compilation
- GitHub Actions provides firmware binaries as release artifacts
- Code must be compatible with QMK's ChibiOS and AVR backends
