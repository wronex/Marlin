/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * This module is off by default, but can be enabled to facilitate the display of
 * extra debug information during code development.
 *
 * Just connect up 5V and GND to give it power, then connect up the pins assigned
 * in Configuration_adv.h. For example, on the Re-ARM you could use:
 *
 *   #define MAX7219_CLK_PIN   77
 *   #define MAX7219_DIN_PIN   78
 *   #define MAX7219_LOAD_PIN  79
 *
 * Max7219_init() is called automatically at startup, and then there are a number of
 * support functions available to control the LEDs in the 8x8 grid.
 */

#ifndef __MAX7219_DEBUG_LEDS_H__
#define __MAX7219_DEBUG_LEDS_H__

//
// MAX7219 registers
//
#define max7219_reg_noop        0x00
#define max7219_reg_digit0      0x01
#define max7219_reg_digit1      0x02
#define max7219_reg_digit2      0x03
#define max7219_reg_digit3      0x04
#define max7219_reg_digit4      0x05
#define max7219_reg_digit5      0x06
#define max7219_reg_digit6      0x07
#define max7219_reg_digit7      0x08

#define max7219_reg_decodeMode  0x09
#define max7219_reg_intensity   0x0A
#define max7219_reg_scanLimit   0x0B
#define max7219_reg_shutdown    0x0C
#define max7219_reg_displayTest 0x0F

void Max7219_init();
void Max7219_register_setup();
void Max7219_PutByte(uint8_t data);

// Set a single register (e.g., a whole native row)
void Max7219(const uint8_t reg, const uint8_t data);

// Set a single LED by XY coordinate
void Max7219_LED_Set(const uint8_t x, const uint8_t y, const bool on);
void Max7219_LED_On(const uint8_t x, const uint8_t y);
void Max7219_LED_Off(const uint8_t x, const uint8_t y);
void Max7219_LED_Toggle(const uint8_t x, const uint8_t y);

// Set all 8 LEDs in a single column
void Max7219_Set_Column(const uint8_t col, const uint8_t val);
void Max7219_Set_2_Columns(uint8_t col, uint16_t val);
void Max7219_Set_4_Columns(uint8_t col, uint32_t val);
void Max7219_Clear_Column(const uint8_t col);

// Set all 8 LEDs in a single row
void Max7219_Set_Row(const uint8_t row, const uint8_t val);
void Max7219_Set_2_Rows(uint8_t row, uint16_t val);
void Max7219_Set_4_Rows(uint8_t row, uint32_t val);
void Max7219_Clear_Row(const uint8_t row);

// Quickly clear the whole matrix
void Max7219_Clear();

// Apply custom code to update the matrix
void Max7219_idle_tasks();

// RTOS hooks
void Max7219_Do_Cmd(uint8_t msg, uint8_t row, uint8_t col, uint32_t val);
TaskFunction_t Max7219_Cmd_Processor(void*);

#define LED_NOP          0x00
#define LED_LOAD_REGS    0x01
#define LED_INIT         0x02
#define LED_ON           0x03
#define LED_OFF          0x04
#define LED_TOGGLE       0x05
#define LED_CLEAR_MATRIX 0x06
#define LED_CLEAR_ROW    0x07
#define LED_CLEAR_COLUMN 0x08
#define LED_SET_ROW      0x09
#define LED_SET_2_ROWS   0x0a
#define LED_SET_4_ROWS   0x0b
#define LED_SET_COLUMN   0x0c
#define LED_IDLE_TASK    0x0d

struct LED_Msg {
  uint8_t operation;
  uint8_t row;
  uint8_t col;
  uint32_t val;
};

#endif // __MAX7219_DEBUG_LEDS_H__
