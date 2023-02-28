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
    RCTL_CM_SCOL,
    CH_PROG,
    CH_WIND,
    CM_TMUX,
    SP_ACC,
    KC_IHAT,
    KC_EHAT,
    KC_OHAT,
    KC_HCTL,
    KC_MCTL2,
    LCTLESC,
    KC_BTIC
};

// Tap Dance keycodes
// enum td_keycodes {
//     LSFT_OSL3, // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
//     KC_FWIN,
// };

// Define a type containing as many tapdance states as you need
// typedef enum {
//     SINGLE_TAP,
//     SINGLE_HOLD,
//     DOUBLE_TAP,
//     DOUBLE_HOLD
// } td_state_t;

// Create a global instance of the tapdance state type
// static td_state_t td_state;
// Function to determine the current tapdance state

// uint8_t cur_dance(qk_tap_dance_state_t *state);

// // Determine the tapdance state to return
// uint8_t cur_dance(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (!state->pressed) return SINGLE_TAP;
//         else return SINGLE_HOLD;
//     }
//     else if (state->count == 2) {
//         if (state->pressed) return DOUBLE_HOLD;
//         else return DOUBLE_TAP;
//     } else return 3; // Any number higher than the maximum state value you return above
// }

// // Handle the possible states for each tapdance keycode you define:

// void lsftosl3_finished(qk_tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case SINGLE_HOLD:
//             register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
//             break;
//         case SINGLE_TAP:
//             set_oneshot_layer(3,ONESHOT_START);clear_oneshot_layer_state(ONESHOT_PRESSED);
//             break;
//         case DOUBLE_HOLD:
//             register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
//             set_oneshot_layer(3,ONESHOT_START);
//             clear_oneshot_layer_state(ONESHOT_PRESSED);
//             break;
//         case DOUBLE_TAP:
//             break;
//     }
// }

// void lsftosl3_reset(qk_tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case SINGLE_HOLD:
//             unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
//             break;
//         case SINGLE_TAP:
//             break;
//         case DOUBLE_HOLD:
//             unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
//             break;
//         case DOUBLE_TAP:
//             break;
//     }
// }

// void kcfwin_finished(qk_tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case SINGLE_TAP:
//             register_code(KC_F);
//             break;
//         case SINGLE_HOLD:
//             layer_on(2);
//             break;
//         case DOUBLE_HOLD:
//             register_code16(CH_PROG);
//             break;
//         case DOUBLE_TAP:
//             break;
//     }
// }

// void kcfwin_reset(qk_tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case SINGLE_TAP:
//             unregister_code(KC_F);
//             break;
//         case SINGLE_HOLD:
//             layer_off(2);
//             break;
//         case DOUBLE_HOLD:
//             unregister_code16(CH_PROG);
//             break;
//         case DOUBLE_TAP:
//             break;
//     }
// }

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     [LSFT_OSL3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsftosl3_finished, lsftosl3_reset),
//     [KC_FWIN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, kcfwin_finished, kcfwin_reset)
// };

// `finished` and `reset` functions for each tapdance keycode
// void lsftosl3_finished(qk_tap_dance_state_t *state, void *user_data);
// void lsftosl3_reset(qk_tap_dance_state_t *state, void *user_data);
// void kcfwin_finished(qk_tap_dance_state_t *state, void *user_data);
// void kcfwin_reset(qk_tap_dance_state_t *state, void *user_data);


uint16_t key_timer;
static bool CTLKEY_RESET;
static bool CTLKEY2_RESET;
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
            tap_code16(LCTL(KC_DOWN));
            layer_on(1);
        } else {
            tap_code16(LCTL(KC_DOWN));
            layer_off(1);
        }
        break;
    case CH_PROG:
        if (record->event.pressed){
            register_code(KC_LGUI);
            tap_code(KC_TAB);
            layer_on(1);
        } else {
            unregister_code(KC_LGUI);
            layer_off(1);
        }
        break;
    case KC_BTIC:
        if (record->event.pressed){
            register_code16(LALT(KC_NUHS));
        } else {
            unregister_code16(LALT(KC_NUHS));
        }
        break;

    case LCTLESC:
        {
            if (record->event.pressed){
                key_timer = timer_read();
                register_code(KC_LCTL);
                CTLKEY_RESET = false;
            } else {
                if (timer_elapsed(key_timer) < TAPPING_TERM && !CTLKEY_RESET) {
                    del_mods(MOD_MASK_CTRL);
                    tap_code(KC_ESC);
                } else {
                    unregister_code(KC_LCTL);
                }
                CTLKEY_RESET = false;
            }
            return true;
        }
        break;

    case KC_HCTL:
                 {
                     static bool CTLKEY_REGISTERED;
                     /* static uint16_t lcl_mod_state; */
                     if (record->event.pressed) {
                         if (mod_state & MOD_MASK_CTRL) {
                             del_mods(MOD_MASK_CTRL);
                             register_code(KC_BSPC);
                             set_mods(mod_state);
                             CTLKEY_REGISTERED = true;
                             CTLKEY_RESET = true;
                             return false;
                         } else {
                             register_code(KC_H);
                             return false;
                         }
                     } else {
                         if (CTLKEY_REGISTERED) {
                             unregister_code(KC_BSPC);
                             CTLKEY_REGISTERED = false;
                             return false;
                         } else {
                             unregister_code(KC_H);
                             return false;
                         }
                     }
                     return true;
                 }
                 break;
    case KC_MCTL2:
                 {
                     static bool CTLKEY_REGISTERED;
                     /* static uint16_t lcl_mod_state; */
                     if (record->event.pressed) {
                         if (mod_state & MOD_MASK_CTRL) {
                             del_mods(MOD_MASK_CTRL);
                             register_code(KC_ENT);
                             set_mods(mod_state);
                             CTLKEY_REGISTERED = true;
                             CTLKEY_RESET = true;
                             return false;
                         } else {
                             register_code(KC_M);
                             return false;
                         }
                     } else {
                         if (CTLKEY_REGISTERED) {
                             unregister_code(KC_ENT);
                             CTLKEY_REGISTERED = false;
                             return false;
                         } else {
                             unregister_code(KC_M);
                             return false;
                         }
                     }
                     return true;
                 }
                 break;
    case CM_SCOL:
                /* from https://github.com/precondition/dactyl-manuform-keymap */
                 {
                     static bool CTLKEY_REGISTERED;
                     static bool ALTKEY_REGISTERED;
                     /* static uint16_t lcl_mod_state; */
                     if (record->event.pressed) {
                         if (mod_state & MOD_MASK_CTRL) {
                             /* lcl_mod_state = mod_state; */
                             /* del_mods(MOD_MASK_CTRL); */
                             /* register_code16(LSFT(KC_SCLN)); */
                             /* SEND_STRING(":"); */
                             /* set_mods(mod_state); */
                             /* clear */
                             del_mods(MOD_MASK_CTRL);
                             tap_code16(S(KC_SCLN));
                             set_mods(mod_state);
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
                             /* unregister_code16(S(KC_SCLN)); */
                             CTLKEY_REGISTERED = false;
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
                 break;
    case RCTL_CM_SCOL:
                /* from https://github.com/precondition/dactyl-manuform-keymap */
                 {
                     if (record->event.pressed) {
                         key_timer = timer_read();
                         register_code(KC_RCTL);
                         CTLKEY2_RESET = false;
                     } else {
                         if (timer_elapsed(key_timer) < TAPPING_TERM && !CTLKEY2_RESET) {
                             del_mods(MOD_MASK_CTRL);
                             register_code16(CM_SCOL);
                         } else if (!CTLKEY2_RESET) {
                             unregister_code16(CM_SCOL);
                         } else {
                             unregister_code(KC_RCTL);
                         }
                        CTLKEY2_RESET = false;
                     }
                     return true;
                 }
                 break;
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
                 break;
    }
    return true;
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LALT_T(KC_TAB):
            return true;
        // case TD(LSFT_OSL3):
        //     return false;
        // case TD(KC_FWIN):
        //     return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case TD(LSFT_OSL3):
        //     return 120;
        // case TD(KC_FWIN):
        //     return 100;
        case LALT_T(KC_TAB):
            return 100;
        default:
            return TAPPING_TERM;
    }
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTLESC:
            return false;
        case LALT_T(KC_TAB):
            return false;
        // case TD(LSFT_OSL3):
        //     return false;
        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_iso_arrow(
            LT(2,KC_NUBS),   KC_1,   KC_2,      KC_3,        KC_4,       KC_5,    KC_6,    KC_7,   KC_8,         KC_9,      KC_0,      KC_MINS,          KC_EQL,      KC_BSPC,
            LALT_T(KC_TAB),  LALT_T(KC_Q),   KC_W,     LCTL_T(KC_E),        KC_R,       KC_T,    KC_Y,         RCTL_T(KC_U),      KC_I,      KC_O,           RALT_T(KC_P),    KC_NO,   KC_NO,
            LCTLESC,       LCTL_T(KC_A),   LT(4,KC_S),LT(1, KC_D), LT(2,KC_F), KC_G,    KC_HCTL,      LT(1,KC_J),LT(4,KC_K),LT(2,KC_L),   SC_SENT,     SC_SENT, KC_NO,   KC_NO,
            KC_NO,KC_NO,    LSFT_T(KC_Z),    LT(3,KC_X),        KC_C,       KC_V,    LT(3,KC_B)   ,KC_N,      KC_MCTL2,     KC_COMM,  RCTL_T(KC_DOT),           LGUI(LSFT(KC_4)),      KC_RSFT,KC_NO,
            KC_NO,KC_NO,  LGUI(LSFT(KC_A)),                          LGUI_T(KC_SPC),                LGUI(LCTL(KC_Q)),     KC_RGUI,   LGUI(LSFT(KC_4)), KC_DOWN,     KC_RGHT
            ),
    [1] = LAYOUT_60_iso_arrow(
            KC_NO,   KC_F1,         KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  QK_BOOT,
            KC_LALT, KC_NO,         KC_1,    KC_2,    KC_3,    KC_NO,            KC_NO,   KC_GRV,  KC_NO,   KC_NO,   QK_BOOT,  KC_NO,   KC_NO,
            KC_LCTL, KC_0,          KC_4,    KC_5,    KC_6,    KC_NO,            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,  KC_NO,   KC_NO,
            KC_NO,   KC_LSFT,       KC_NO,   KC_7,    KC_8,    KC_9,          KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,  KC_NO,
            KC_NO,   KC_NO,         KC_NO,                                    LGUI_T(KC_0),              KC_NO,   KC_NO,   KC_HOME, KC_PGDN, KC_END
            ),
    [2] = LAYOUT_60_iso_arrow(
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SLEP,
            KC_NO,   KC_TAB,   KC_TAB,   KC_NO,   KC_NO,         KC_NO,      KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,KC_NO,   KC_NO,
            KC_NO,   KC_ESC,  CH_WIND,   CH_PROG, KC_NO,         KC_NO,      MI_LEFT, MI_DOWN, MI_UP,   MI_RGHT, KC_NO,   KC_NO,  KC_NO,   KC_NO,
            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,     KC_NO, CH_PROG, LCTL(KC_RBRC),   KC_NO,   KC_NO,   KC_NO,  KC_NO,
            KC_NO,   KC_NO,   LGUI(LSFT(KC_A)),                                    LGUI(KC_SPC),                LGUI(LSFT(KC_4)), KC_NO,   KC_NO,   KC_NO,   _______
            ),
    [3] = LAYOUT_60_iso_arrow(
            KC_NO,   KC_NO,         KC_NO,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
            KC_NO,   KC_NO,         KC_NO,        A(KC_7), A(KC_8), KC_NO,      KC_NO,   KC_GRV,  KC_NO,   KC_LBRC, KC_NO,   KC_NO,   KC_NO,
            KC_NO,   LALT(KC_COMM), LALT(KC_DOT), KC_LPRN, KC_RPRN, C(KC_K),    KC_SLSH, KC_QUOT, KC_NUHS, KC_RBRC, KC_NO,   KC_NO,  KC_NO,   KC_NO,
            KC_NO,KC_LSFT,          LSFT_T(KC_Z),        KC_RBRC, A(KC_9), A(KC_0), KC_NO,    S(KC_COMM),KC_NO,   KC_NO,  S(KC_DOT),KC_NO,   KC_NO,  KC_NO,
            KC_NO,   KC_NO,         KC_LSFT,                                   KC_NO,                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   _______
            ),
    [4] = LAYOUT_60_iso_arrow(
            KC_NO,   KC_NO,      KC_NO,      KC_NO,      KC_NO,         KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,  KC_NO,   KC_NO,   KC_NO,
            KC_NO,   LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4),    LSFT(KC_EQL), KC_NO,  LSFT(KC_MINS),KC_MINS,LSFT(KC_EQL), KC_EQL,  KC_NO,   KC_NO,
            KC_NO,   KC_BTIC,    LALT(KC_MINS), KC_NUBS,  LALT(KC_QUOT), LALT(KC_RBRC),        KC_BSPC,   KC_NO,     KC_NO,   LSFT(KC_SCLN), KC_SCLN,       KC_NO,  KC_NO,   KC_NO,
            KC_NO,   KC_NO,      LSFT(KC_5), LSFT(KC_6), LSFT(KC_7),    LSFT(KC_8),    KC_NO,   KC_NO,   KC_NO,       KC_NO,  KC_NO,   KC_NO,   KC_NO,  KC_NO,
            KC_NO,   KC_NO,      KC_NO,                                              KC_NO,                     KC_NO,       KC_NO,  KC_NO,   KC_NO,   _______
            ),
};

