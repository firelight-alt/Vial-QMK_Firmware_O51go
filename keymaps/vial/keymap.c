/* Original by Salicylic-acid3
 * Modified by firelight-alt for personal typing preferences
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
#include "process_key_override.h"
#include "os_detection.h"

#define CTL_EISU  MT(MOD_LCTL, KC_LANGUAGE_2)   // Hold: Control + Tap: Eisu
#define LT1_KANA  LT(1, KC_LANGUAGE_1)          // Hold: Layer 1 + Tap: Kana
#define GUI_EISU  MT(MOD_LGUI, KC_LANGUAGE_2)   // Hold: GUI + Tap: Eisu
#define SFT_ENTR  MT(MOD_LSFT, KC_ENTER)        // Hold: LShift + Tap: Enter
#define SFT_SPC   MT(MOD_RSFT, KC_SPACE)        // Hold: RShift + Tap: Space

// レイヤー定義 とりあえず0〜4を列挙
enum layers {
    _LAYER0,    // 通常入力用のレイヤー = 0
    _LAYER1,    // 数字・記号入力用のレイヤー = 1
    _LAYER2,    //
    _LAYER3,    //
    _LAYER4,    // Mac/iOS用のレイヤー = 4
};

// レイヤーのキー配置を定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_7,    KC_8,    KC_9,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_4,    KC_5,    KC_6,    KC_H,    KC_J,    KC_K,    KC_L,    KC_MINS,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_1,    KC_2,    KC_3,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_BSPC,
        KC_LSFT, KC_LALT, KC_LGUI, CTL_EISU, SFT_ENTR,   KC_0,   KC_KP_DOT,  SFT_SPC,    LT1_KANA,KC_TAB,  KC_RALT, KC_RSFT
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,   _______,   _______, _______,   _______,    _______, _______, _______, TG(_LAYER4)
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,   _______,   _______, _______,   _______,    _______, _______, _______, _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,   _______,   _______, _______,   _______,    _______, _______, _______, _______
    ),
    [4] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_LCTL, GUI_EISU,  _______,   _______, _______,   _______,    _______, _______, _______, _______
    )
};

// Host OS detection
// If Host OS is either macOS or iOS, activate _LAYER4
// Do nothing for the others. Just move to the default layer.
void keyboard_post_init_user(void) {
    wait_ms(400);
    switch (detected_host_os()) {
    case OS_MACOS:
        layer_on(_LAYER4);
        break;
    case OS_IOS:
        layer_on(_LAYER4);
        break;
    default:
        layer_move(_LAYER0);
        break;
    }
}
