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
#include "keymap_japanese.h"
#include "process_key_override.h"
#include "os_detection.h"

// 疑似US配列を有効にする場合(Vial対応ファームウェアでは動作しない)
// #define PSEUDO_US_LAYOUT_ENABLE

// キー配置用定義
#define CTL_EISU  MT(MOD_LCTL, KC_LANGUAGE_2)   // Hold: Control + Tap: Eisu
#define LT1_KANA  LT(1, KC_LANGUAGE_1)          // Hold: Layer 1 + Tap: Kana
#define GUI_EISU  MT(MOD_LGUI, KC_LANGUAGE_2)   // Hold: GUI + Tap: Eisu
#define SFT_ENTR  MT(MOD_LSFT, KC_ENTER)        // Hold: LShift + Tap: Enter
#define SFT_SPC   MT(MOD_RSFT, KC_SPACE)        // Hold: RShift + Tap: Space

// 使用するレイヤー
enum layers {
    _LAYER0, // 0:通常入力用
    _LAYER1, // 1:かな入力時にレイヤー0にかぶせる
    _LAYER2, // 2:数字・記号入力用
    _LAYER3, //
    _LAYER4, // 4:Mac/iOS用のレイヤー
};

// カスタムキーコードの定義（Vialの予約領域（0x7E00〜）を使用する）
enum custom_keycodes {
    CUSTOM_KEYCODE_BASE = 0x7E00,  // Vialの予約領域（0x7E00〜） 
    TO_LAYER_1_KANA = CUSTOM_KEYCODE_BASE,
    TO_LAYER_0_EISU,
    TO_LAYER_0_LGUI,
};

// カスタムキーコードの動作
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t eisu_timer;
    static uint16_t kana_timer;
    static uint16_t lgui_timer;

#ifdef CONSOLE_ENABLE
    uprintf("Key pressed: %u\n", keycode);  // ← これで出力を確認
#endif
    switch (keycode) {
    case TO_LAYER_1_KANA:
        if (record->event.pressed) {
            kana_timer = timer_read();
            layer_on(2);  // MO(2)相当: レイヤー2をアクティベート
        } else {
            layer_off(2);
            if (timer_elapsed(kana_timer) < TAPPING_TERM) {
                // レイヤー1をアクティベート
                layer_on(_LAYER1);
                // 入力モードを「かな」に
                tap_code(KC_LANGUAGE_1);
            }
        }
        return false; // Skip all further processing of this key

    case TO_LAYER_0_EISU:
        if (record->event.pressed) {
            eisu_timer = timer_read();
            register_code(KC_LCTL);  // ホールド用にControlを押す
        } else {
            unregister_code(KC_LCTL);
            if (timer_elapsed(eisu_timer) < TAPPING_TERM) {
                // レイヤー0をアクティブにして、レイヤー1を非アクティブにする
                // レイヤー0はデフォルトレイヤーなので常にアクティブなはずだが念のため
                layer_on(_LAYER0);
                layer_off(_LAYER1);
                // 入力モードを「英数」に
                tap_code(KC_LANGUAGE_2);
            }
        }
        return false; // Skip all further processing of this key

    case TO_LAYER_0_LGUI:
        if (record->event.pressed) {
            lgui_timer = timer_read();
            register_code(KC_LGUI);  // ホールド用にWin/Commandを押す
        } else {
            unregister_code(KC_LGUI);
            if (timer_elapsed(lgui_timer) < TAPPING_TERM) {
                // レイヤー0をアクティブにして、レイヤー1を非アクティブにする
                layer_on(_LAYER0);
                layer_off(_LAYER1);
                // 入力モードを「英数」に
                tap_code(KC_LANGUAGE_2);
            }
        }
        return false; // Skip all further processing of this key
    }
    return true;
}

// 疑似US配列を実現するためのキーコード置き換え
#ifdef PSEUDO_US_LAYOUT_ENABLE
//These JIS keycodes have been overridden to emulate pseudo-US layout
const key_override_t jp2_key_override    = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_2,    JP_AT);
const key_override_t jp6_key_override    = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_6,    JP_CIRC);
const key_override_t jp7_key_override    = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_7,    JP_AMPR);
const key_override_t jp8_key_override    = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_8,    JP_ASTR);
const key_override_t jp9_key_override    = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_9,    JP_LPRN);
const key_override_t jp0_key_override    = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_0,    JP_RPRN);
const key_override_t jpunds_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_MINS, JP_UNDS);
const key_override_t jpplus_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_CIRC, JP_PLUS);
const key_override_t jpeql_key_override  = ko_make_basic(0,                                   JP_CIRC, JP_EQL);
const key_override_t jpcoln_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_SCLN, JP_COLN);
const key_override_t jpdquo_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_COLN, JP_DQUO);
const key_override_t jpquot_key_override = ko_make_basic(0,                                   JP_COLN, JP_QUOT);
const key_override_t jptild_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_ZKHK, JP_TILD);
const key_override_t jpgrv_key_override  = ko_make_basic(0,                                   JP_ZKHK, JP_GRV);
const key_override_t jp1_key_override    = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_1,    JP_TILD);
const key_override_t jpcomm_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_COMM, S(JP_1));
const key_override_t jpslsh_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_DOT,  S(JP_SLSH));
const key_override_t jprabk_key_override = ko_make_basic(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT), JP_BSLS, JP_RABK);
const key_override_t jplabk_key_override  = ko_make_basic(0,                                  JP_BSLS, JP_LABK);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
	&jp2_key_override,
	&jp6_key_override,
	&jp7_key_override,
	&jp8_key_override,
	&jp9_key_override,
	&jp0_key_override,
	&jpunds_key_override,
	&jpplus_key_override,
	&jpeql_key_override,
	&jpcoln_key_override,
	&jpdquo_key_override,
	&jpquot_key_override,
	&jptild_key_override,
	&jpgrv_key_override,
	&jp1_key_override,
	&jpcomm_key_override,
	&jpslsh_key_override,
    &jprabk_key_override,
	&jplabk_key_override
};
#endif // PSEUDO_US_LAYOUT_ENABLE

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
