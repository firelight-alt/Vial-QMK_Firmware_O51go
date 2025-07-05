/* Copyright 2021 Salicylic_acid3
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

#pragma once

/* Select hand configuration */

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 220
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define VIAL_KEYBOARD_UID {0x71, 0x6C, 0xE4, 0x1E, 0x36, 0x31, 0xDE, 0xAB}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 12 }

/* EEPROM size of ATmega32U4 is 1024 bytes */
/* VIAL_TAP_DANCE_ENTRIES consumes 10 bytes EEPROM per entry */
#define VIAL_TAP_DANCE_ENTRIES 4
/* VIAL_KEY_COMBO_ENTRIES consumes (6 + 2 * # of keys) bytes EEPROM per entry */
#define VIAL_COMBO_ENTRIES 4
/* VIAL_KEY_OVERRIDE_ENTRIES consumes 7 bytes EEPROM per entry */
#define VIAL_KEY_OVERRIDE_ENTRIES 20