/* Copyright 2020 markva
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

uint16_t mod_state;
uint16_t oneshot_mod_state;

enum custom_keycodes {
    CM_SCOL = SAFE_RANGE,
    CH_WIND
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    switch (keycode) {

    case CH_WIND:
        if (record->event.pressed){
            register_code(KC_LGUI);
            tap_code(KC_TAB);
            layer_on(1);
        } else {
            unregister_code(KC_LGUI);
            layer_off(1);
        }
        break;
    case CM_SCOL:
                /* from https://github.com/precondition/dactyl-manuform-keymap */
                 {
                     static bool sclkey_registered;
                     static bool sslkey_registered;
                     if (record->event.pressed) {
                         if (mod_state & MOD_MASK_CTRL) {

                             del_mods(MOD_MASK_CTRL);
                             register_code16(KC_COLN);
                             sclkey_registered = true;
                             set_mods(mod_state);
                             return false;
                         } else if (mod_state & MOD_MASK_ALT) {

                             del_mods(MOD_MASK_ALT);
                             register_code16(LSFT(KC_NUBS));
                             sslkey_registered = true;
                             set_mods(mod_state);
                             return false;
                         } else {
                             register_code(KC_SCLN);
                         }
                     } else {
                         if (sclkey_registered) {
                             unregister_code16(KC_COLN);
                             sclkey_registered = false;
                             return false;
                         } else if (sslkey_registered){
                             unregister_code16(LSFT(KC_NUBS));
                             sslkey_registered = false;
                             return false;
                         } else {
                             unregister_code(KC_SCLN);
                         }
                     }
                     return true;
                 }
    }
    return true;
};

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
            return false;
        case LALT_T(KC_TAB):
            return false;
        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_iso_arrow(
        LT(2,KC_NUBS),   KC_1,            KC_2,    KC_3,          KC_4,          KC_5,    KC_6,          KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,           KC_EQL,  KC_BSPC,
        LALT_T(KC_TAB),  KC_Q,            KC_W,    KC_E,          KC_R,          KC_T,    KC_Y,          KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,           KC_RBRC,
        LCTL_T(KC_ESC),  KC_A,            KC_S,    LT(1, KC_D),   LT(2,KC_F),    KC_G,    KC_H,          KC_J,    KC_K,    KC_L,    CM_SCOL, KC_QUOT,           KC_NUHS, KC_SFTENT,
        KC_LSFT,         KC_GRV,          KC_Z,    KC_X,          KC_C,          KC_V,    LT(3,KC_B),    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_UP,   KC_RSFT,
        LGUI(LSFT(KC_A)),LGUI(LCTL(KC_Q)),CH_WIND,                                        LGUI_T(KC_SPC),                  MO(1),   KC_RGUI, LGUI(LSFT(KC_4)),  KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_60_iso_arrow(
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,  _______, _______, _______,
        _______, _______, _______, _______, _______, KC_BSPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, KC_PGUP, _______,
        _______, _______, _______,                            _______,                   _______,  _______, KC_HOME, KC_PGDN, KC_END
    ),
    [2] = LAYOUT_60_iso_arrow(
        _______, _______, _______, _______, _______, _______, _______,       _______,        _______,       _______,        KC_MUTE, KC_VOLD, KC_VOLU, KC_SLEP,
        _______, _______, _______, _______, _______, _______, _______,       _______,        _______,       _______,        KC_MPRV, KC_MPLY, KC_MNXT,
        _______, _______, _______, _______, _______, _______, LCTL(KC_LEFT), LCTL(KC_DOWN),  LCTL(KC_UP),   LCTL(KC_RIGHT), _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,       _______,        _______,       _______,        _______, _______, _______, _______,
        _______, _______, _______,                            LGUI(KC_SPC),                                 _______,        _______, _______, _______, _______
    ),
    [3] = LAYOUT_60_iso_arrow(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, A(KC_7), A(KC_8), _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, KC_LPRN, KC_RPRN, _______,  _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, A(KC_9), A(KC_0), _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
    ),
    [4] = LAYOUT_60_iso_arrow(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                   _______, _______, _______, _______, _______
    ),
};
