/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(KC_LALT, KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U, KC_P, KC_SCLN, TO(4), KC_LCTL, KC_A, LT(2,KC_S), LT(1,KC_H), KC_T, LT(3,KC_G), KC_Y, KC_N, KC_E, LT(2,KC_O), KC_I, KC_QUOT, KC_LSPO, KC_Z, KC_X, KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_LGUI, KC_TAB, KC_BSPC, KC_SPC, KC_ENT, KC_NO),
	[1] = LAYOUT_split_3x6_3(KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_MINS, KC_EQL, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LGUI, KC_TAB, KC_BSPC, KC_SPC, KC_ENT, KC_RALT),
	[2] = LAYOUT_split_3x6_3(KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LGUI, KC_TAB, KC_BSPC, KC_SPC, KC_ENT, KC_RALT),
	[3] = LAYOUT_split_3x6_3(RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_NO, KC_NO, KC_LGUI, KC_TAB, KC_BSPC, KC_SPC, KC_ENT, KC_P0),
	[4] = LAYOUT_split_3x6_3(LALT(KC_GRV), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TO(0), LALT(KC_LSFT), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_NO, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_LGUI, KC_TAB, KC_BSPC, KC_SPC, KC_ENT, KC_RALT)
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return OLED_ROTATION_270;
}

#define L_BASE 0
#define L_ARROW 1
#define L_SYMBOL 2
#define L_NUMPAD 3
#define L_QWERTY 4

void oled_render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case L_BASE:
            oled_write_P(PSTR("Base"), false);
            break;
        case L_ARROW:
            oled_write_P(PSTR("ARW "), false);
            break;
        case L_SYMBOL:
            oled_write_P(PSTR("SYM "), false);
            break;
        case L_NUMPAD:
            oled_write_P(PSTR("NUM "), false);
            break;
        case L_QWERTY:
            oled_write_P(PSTR("QRTY"), false);
            break;
        default:
            oled_write_P(PSTR("REEE"), false);
            break;
    }
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

// void oled_render_logo(void) {
//     static const char PROGMEM crkbd_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
//         0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
//         0};
//     oled_write_P(crkbd_logo, false);
// }

const rgblight_segment_t PROGMEM layer_base[] = RGBLIGHT_LAYER_SEGMENTS(
        { 0, 27, HSV_CYAN }
    );

const rgblight_segment_t PROGMEM layer_arrow[] = RGBLIGHT_LAYER_SEGMENTS(
        { 0, 27, HSV_PINK }
    );

const rgblight_segment_t PROGMEM layer_symbol[] = RGBLIGHT_LAYER_SEGMENTS(
        { 0, 27, HSV_GREEN }
    );

const rgblight_segment_t PROGMEM layer_numpad[] = RGBLIGHT_LAYER_SEGMENTS(
        { 0, 27, HSV_GOLD }
    );

const rgblight_segment_t PROGMEM layer_qwerty[] = RGBLIGHT_LAYER_SEGMENTS(
        { 0, 27, HSV_BLUE }
    );

const rgblight_segment_t* const PROGMEM rgb_indicator_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_base,
    layer_arrow,
    layer_symbol,
    layer_numpad,
    layer_qwerty
    );

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_indicator_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(L_BASE, layer_state_cmp(state, L_BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(L_ARROW, layer_state_cmp(state, L_ARROW));
    rgblight_set_layer_state(L_SYMBOL, layer_state_cmp(state, L_SYMBOL));
    rgblight_set_layer_state(L_NUMPAD, layer_state_cmp(state, L_NUMPAD));
    rgblight_set_layer_state(L_QWERTY, layer_state_cmp(state, L_QWERTY));
    return state;
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
    } else {
        //oled_render_logo();
    }
}

#endif // OLED_DRIVER_ENABLE
