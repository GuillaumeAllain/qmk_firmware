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
#include "shortcuts.h"


// Mod states
uint16_t mod_state;
uint16_t oneshot_mod_state;
uint16_t key_timer;

// Custom keycodes

enum custom_keycodes {
    CM_SCOL = SAFE_RANGE,
    CH_WIND,
    CM_TMUX,
    SP_ACC,
    KC_IHAT,
    KC_EHAT,
    KC_OHAT
};

// Tap Dance keycodes
enum td_keycodes {
    LSFT_OSL3 // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
};

// Define a type containing as many tapdance states as you need
typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;
// Function to determine the current tapdance state

uint8_t cur_dance(qk_tap_dance_state_t *state);

// Determine the tapdance state to return
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    }
    else return 2; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void lsftosl3_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case SINGLE_TAP:
            set_oneshot_layer(3,ONESHOT_START);clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case DOUBLE_TAP:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            set_oneshot_layer(3,ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
    }
}

void lsftosl3_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case SINGLE_TAP:
            break;
        case DOUBLE_TAP:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [LSFT_OSL3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsftosl3_finished, lsftosl3_reset)
};

// `finished` and `reset` functions for each tapdance keycode
void lsftosl3_finished(qk_tap_dance_state_t *state, void *user_data);
void lsftosl3_reset(qk_tap_dance_state_t *state, void *user_data);


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();

    switch (keycode) {

    case KC_IHAT:
        if (record->event.pressed){
            tap_code(KC_LBRC);
            register_code(KC_I);
        } else {
            unregister_code(KC_I);
        }
        break;
    case KC_EHAT:
        if (record->event.pressed){
            tap_code(KC_LBRC);
            register_code(KC_E);
        } else {
            unregister_code(KC_E);
        }
        break;
    case KC_OHAT:
        if (record->event.pressed){
            tap_code(KC_LBRC);
            register_code(KC_O);
        } else {
            unregister_code(KC_O);
        }
        break;
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
                     static bool CTLKEY_REGISTERED;
                     static bool ALTKEY_REGISTERED;
                     static uint16_t lcl_mod_state;
                     if (record->event.pressed) {
                         if (mod_state & MOD_MASK_CTRL) {
                             /* del_mods(MOD_MASK_CTRL); */
                             lcl_mod_state = mod_state;
                             clear_mods();
                             register_code16(KC_COLN);
                             CTLKEY_REGISTERED = true;
                             return false;
                         }  else if (mod_state & MOD_MASK_ALT) {
                             /* lcl_mod_state = mod_state; */
                             /* clear_mods(); */
                             register_code16(KC_QUOT);
                             ALTKEY_REGISTERED = true;
                             return false;
                         } else {
                             register_code(KC_SCLN);
                         }
                     } else {
                         if (CTLKEY_REGISTERED) {
                             unregister_code16(KC_COLN);
                             CTLKEY_REGISTERED = false;
                             /* set_mods(MOD_BIT(KC_LCTL)); */
                             set_mods(lcl_mod_state);
                             return false;
                         } else if (ALTKEY_REGISTERED) {
                             unregister_code16(KC_QUOT);
                             ALTKEY_REGISTERED = false;
                             /* set_mods(MOD_BIT(KC_LALT)); */
                             /* set_mods(lcl_mod_state); */
                             return false;
                         } else {
                             unregister_code(KC_SCLN);
                         }
                     }
                     return true;
                 }
    case SP_ACC:
                /* from https://github.com/precondition/dactyl-manuform-keymap */
                 {
                     static bool CTLKEY_REGISTERED;
                     static bool ALTKEY_REGISTERED;
                     static bool SFTKEY_REGISTERED;
                     if (record->event.pressed) {
                         if (mod_state & MOD_MASK_CTRL) {
                             del_mods(MOD_MASK_CTRL);
                             register_code16(LALT(KC_LBRC)); 
                             CTLKEY_REGISTERED = true;
                             set_mods(mod_state);
                             return false;
                         } else if (mod_state & MOD_MASK_ALT){
                             del_mods(MOD_MASK_ALT);
                             register_code16(LSFT(KC_LBRC)); 
                             ALTKEY_REGISTERED = true;
                             set_mods(mod_state);
                             return false;
                         } else if (mod_state & MOD_MASK_SHIFT){
                             del_mods(MOD_MASK_SHIFT);
                             register_code16(KC_LBRC); 
                             ALTKEY_REGISTERED = true;
                             set_mods(mod_state);
                             return false;
                         }else {
                             register_code16(LSA(KC_SCLN)); 
                         }
                     } else {
                         if (CTLKEY_REGISTERED) {
                             CTLKEY_REGISTERED = false;
                             unregister_code16(LALT(KC_LBRC)); 
                             return false;
                         } else if (ALTKEY_REGISTERED) {
                             ALTKEY_REGISTERED = false;
                             unregister_code16(LSFT(KC_LBRC)); 
                             return false;
                         } else if (SFTKEY_REGISTERED) {
                             SFTKEY_REGISTERED = false;
                             unregister_code16(KC_LBRC); 
                             return false;
                         }else {
                             unregister_code16(LSA(KC_SCLN)); 
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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(LSFT_OSL3):
            return 150;
        case LCTL_T(KC_ESC):
            return 100;
        case LALT_T(KC_TAB):
            return 100;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
            return false;
        case LALT_T(KC_TAB):
            return false;
        default:
            return false;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_SPACE):
            return true;
        case LCTL_T(KC_ESC):
            return false;
        case LALT_T(KC_TAB):
            return false;
        case TD(LSFT_OSL3):
            return false;
        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_iso_arrow(
        LT(2,KC_NUBS),   KC_1,   KC_2,      KC_3,        KC_4,       KC_5,    KC_6,    KC_7,   KC_8,         KC_9,      KC_0,      KC_MINS,          KC_EQL,      KC_BSPC,
        LALT_T(KC_TAB),  KC_Q,   KC_W,      KC_E,        KC_R,       KC_T,    KC_LBRC, KC_RBRC,KC_Y,         KC_U,      KC_I,      KC_O,             RCTL_T(KC_P),    
        LCTL_T(KC_ESC),  KC_A,   LT(4,KC_S),LT(1, KC_D), LT(2,KC_F), KC_G,    KC_NUHS, SP_ACC ,LT(2,KC_H),   LT(1,KC_J),LT(4,KC_K),KC_L,             CM_SCOL,     KC_SFTENT,
        TD(LSFT_OSL3),   OSL(3), KC_Z,      KC_X,        KC_C,       KC_V,    KC_B,    KC_DOT, LT(3,KC_COMM),KC_N,      KC_M,      KC_DOT,           KC_SLSH,      KC_RSFT,
        LGUI(LSFT(KC_A)),LGUI(LCTL(KC_Q)),  CH_WIND,                          LGUI_T(KC_SPC),                MO(1),     KC_RGUI,   LGUI(LSFT(KC_4)), KC_DOWN,     KC_RGHT
    ),
    [1] = LAYOUT_60_iso_arrow(
        KC_NO,   KC_F1,         KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET,
        KC_LALT, KC_NO,         KC_1,    KC_2,    KC_3,    KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_GRV,  KC_NO,   KC_NO,   KC_NO,  
        KC_LCTL, KC_0,          KC_4,    KC_5,    KC_6,    KC_NO,         KC_NO,   KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,  
        KC_LSFT, KC_NO,         KC_NO,   KC_7,    KC_8,    KC_9,          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_PGUP, KC_NO,  
        KC_NO,   KC_NO,         KC_NO,                                    LGUI_T(KC_0),              KC_NO,   KC_NO,   KC_HOME, KC_PGDN, KC_END
    ),
    [2] = LAYOUT_60_iso_arrow(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SLEP,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,
        KC_NO,   CH_WIND, KC_NO,   KC_NO,   CH_WIND,       KC_NO,   KC_NO,   KC_NO,   MI_LEFT, MI_DOWN, MI_UP,   MI_RGHT, KC_NO,   KC_NO,  
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   LCTL(KC_RBRC), KC_NO,   KC_NO,   KC_NO,   KC_TMUX, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,   KC_NO,                                    LGUI(KC_SPC),              KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______
    ),
    [3] = LAYOUT_60_iso_arrow(
        KC_NO,   KC_NO,         KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,         KC_NO,        A(KC_7), A(KC_8), KC_NO,   KC_NO,   KC_NO,   KC_LBRC, KC_GRV,  KC_NO,   KC_NO,   KC_NO,   
        KC_NO,   LALT(KC_COMM), LALT(KC_DOT), KC_LPRN, KC_RPRN, KC_NO,   KC_NO,   KC_NO,   KC_SLSH, KC_QUOT, KC_NUHS, KC_RBRC, KC_NO,   KC_NO,  
        KC_LSFT, KC_NO,         KC_NO,        KC_RBRC, A(KC_9), A(KC_0), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,         KC_NO,                                   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______
    ),
    [4] = LAYOUT_60_iso_arrow(
        KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,         KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4),    LSFT(KC_EQL),KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,      LALT(KC_MINS), KC_NUBS, LALT(KC_RBRC), KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,      LSFT(KC_5), LSFT(KC_6), LSFT(KC_7),    LSFT(KC_8),  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,      KC_NO,                                              KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______
    ),
};
