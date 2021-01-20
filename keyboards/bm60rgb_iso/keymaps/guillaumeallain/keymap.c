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

enum custom_keycodes {
    CTL_UP = SAFE_RANGE,
    CTL_DOWN,
    CTL_LEFT,
    CTL_RIGHT,
    GUI_TAB,
    GUI_STAB,
    SPOTLIGHT
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CTL_UP:
        if (record->event.pressed) {
            register_code(KC_LCTL) ;
            register_code(KC_UP);
        } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_UP);
        }
        break;
    case CTL_DOWN:
        if (record->event.pressed) {
            register_code(KC_LCTL) ;
            register_code(KC_DOWN);
        } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_DOWN);
        }
        break;
    case CTL_LEFT:
        if (record->event.pressed) {
            register_code(KC_LCTL) ;
            register_code(KC_LEFT);
        } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_LEFT);
        }
        break;
    case CTL_RIGHT:
        if (record->event.pressed) {
            register_code(KC_LCTL) ;
            register_code(KC_RIGHT);
        } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_RIGHT);
        }
        break;
    case GUI_TAB:
        if (record->event.pressed) {
            register_code(KC_LGUI) ;
            register_code(KC_TAB);
        } else {
            unregister_code(KC_LGUI);
            unregister_code(KC_TAB);
        }
        break;
    case GUI_STAB:
        if (record->event.pressed) {
            register_code(KC_LGUI) ;
            register_code(KC_LSFT) ;
            register_code(KC_TAB);
        } else {
            unregister_code(KC_LGUI);
            unregister_code(KC_LSFT) ;
            unregister_code(KC_TAB);
        }
        break;
    case SPOTLIGHT:
        if (record->event.pressed) {
            register_code(KC_LGUI) ;
            register_code(KC_SPACE) ;
        } else {
            unregister_code(KC_LGUI) ;
            unregister_code(KC_SPACE) ;
        }
        break;
    }
    return true;
};

/* enum combo_events { */
/*   ctldotcomma_dotdot, */
/* }; */
/*  */
/* const uint16_t PROGMEM dotdot_combo[] = {KC_LCTL, KC_SCLN, COMBO_END}; */
/*  */
/* combo_t key_combos[COMBO_COUNT] = { */
/*   [ctldotcomma_dotdot] = COMBO_ACTION(dotdot_combo), */
/* }; */
/*  */
/* void process_combo_event(uint16_t combo_index, bool pressed) { */
/*   switch(combo_index) { */
/*     case ctldotcomma_dotdot: */
/*       if (pressed) { */
/*         send_string(":"); */
/*       } */
/*       break; */
/*   } */
/* } */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_iso_arrow(
        LT(2,KC_NUBS),   KC_1,           KC_2,    KC_3,          KC_4,          KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,         KC_EQL,  KC_BSPC,
        LALT_T(KC_TAB),  KC_Q,           KC_W,    KC_E,          KC_R,          KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,         KC_RBRC,
        LCTL_T(KC_ESC),  KC_A,           KC_S,    LT(1, KC_D),   LT(2,KC_F),    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,         KC_NUHS, KC_SFTENT,
        KC_LSFT,         KC_GRV,         KC_Z,    KC_X,          KC_C,          KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  RGUI_T(KC_SLSH), KC_UP,   KC_RSFT,
        KC_LGUI,         MO(1),          KC_LGUI,                               KC_SPC,                             MO(1),   MO(1),   KC_LEFT,         KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_60_iso_arrow(
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,  _______, _______, _______,
        _______, _______, _______, _______, _______, KC_BSPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, KC_PGUP, _______,
        _______, _______, _______,                            _______,                   _______,  _______, KC_HOME, KC_PGDN, KC_END
    ),
    [2] = LAYOUT_60_iso_arrow(
        _______, _______, _______, _______, _______, _______, _______,  KC_MPRV,  KC_MPLY, KC_MNXT,   KC_MUTE, KC_VOLD, KC_VOLU, _______,
        _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______,   GUI_STAB, _______, _______,
        _______, _______, _______, _______, _______, _______, CTL_LEFT, CTL_DOWN, CTL_UP,  CTL_RIGHT, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,  GUI_TAB,  _______, _______,   _______, _______, _______, _______,
        _______, _______, _______,                            SPOTLIGHT,                   _______,   _______, _______, _______, _______
    ),
};
