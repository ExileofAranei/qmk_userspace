#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// ============================================================
// Левый дисплей (мастер)
// ============================================================

enum layers { BASE, EXTRA, TAP, BUTTON, NAV, MOUSE, MEDIA, NUM, SYM, FUN };

static void render_layer(void) {
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("LYR: "), false);
    oled_set_cursor(0, 4);
    switch (get_highest_layer(layer_state)) {
        case BASE:   oled_write_P(PSTR("BASE "), false); break;
        case EXTRA:  oled_write_P(PSTR("EXTR "), false); break;
        case TAP:    oled_write_P(PSTR("TAP  "), false); break;
        case BUTTON: oled_write_P(PSTR("BTN  "), false); break;
        case NAV:    oled_write_P(PSTR("NAV  "), false); break;
        case MOUSE:  oled_write_P(PSTR("MOUS "), false); break;
        case MEDIA:  oled_write_P(PSTR("MED  "), false); break;
        case NUM:    oled_write_P(PSTR("NUM  "), false); break;
        case SYM:    oled_write_P(PSTR("SYM  "), false); break;
        case FUN:    oled_write_P(PSTR("FUN  "), false); break;
        default:     oled_write_P(PSTR("???  "), false); break;
    }
}

static void render_locks(void) {
    led_t leds = host_keyboard_led_state();
    oled_set_cursor(0, 6);
    oled_write_P(PSTR("LCKS:"), false);
    oled_set_cursor(0, 7);
    oled_write_P(PSTR("CAP  "), leds.caps_lock);
    oled_set_cursor(0, 8);
    oled_write_P(PSTR("NUM  "), leds.num_lock);
    oled_set_cursor(0, 9);
    oled_write_P(PSTR("SCR  "), leds.scroll_lock);
}

static void render_mods(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_set_cursor(0, 11);
    oled_write_P(PSTR("MODS:"), false);
    oled_set_cursor(0, 12);
    oled_write_char(mods & MOD_MASK_GUI   ? 'G' : '-', false);
    oled_write_char(mods & MOD_MASK_ALT   ? 'A' : '-', false);
    oled_write_char(mods & MOD_MASK_CTRL  ? 'C' : '-', false);
    oled_write_char(mods & MOD_MASK_SHIFT ? 'S' : '-', false);
}

static void render_stats(void) {
    render_layer();
    render_locks();
    render_mods();
}

// ============================================================
// Правый дисплей (slave)
// ============================================================

static void render_wpm(void)
{
    oled_set_cursor(1, 13);
    oled_write_P(PSTR(">"), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
}

// Основная функция рендеринга
static void render_info(void) {
    render_wpm();
}

// ============================================================
// Точка входа
// ============================================================

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_info();
    } else {
        render_stats();
    }
    return false;
}

#endif // OLED_ENABLE

