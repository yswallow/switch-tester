/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "pico/stdlib.h"
#include "pico/time.h"
#include "tusb.h"
#include "usb_descriptors.h"

#define COL_COUNT 15
#define ROW_COUNT 10

uint8_t row_pins[ROW_COUNT] = { 20,19,18,17,16,29,28,27,22,21 };
uint8_t col_pins[COL_COUNT] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
uint16_t pressed[ROW_COUNT];
uint8_t report[1];

/*------------- MAIN -------------*/
void keyboard_init() {
    for(uint8_t i=0;i<ROW_COUNT;i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], false);
        gpio_pull_up(row_pins[i]);
        
        pressed[i] = 0;
    }
    
    for(uint8_t i=0;i<COL_COUNT;i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], false);
        gpio_pull_up(col_pins[i]);
    }
}

int main(void)
{
    stdio_init_all();
    
    keyboard_init(); 
    tusb_init();
    while(true) {
        tud_task();
        for(uint8_t row=0; row<ROW_COUNT; row++) {
            gpio_set_dir(row_pins[row], true);
            gpio_put(row_pins[row], false);
            sleep_us(10);
            for(uint8_t col=0; col<COL_COUNT; col++) {
                if( pressed[row] & (1<<col) ) {
                    if( gpio_get(col_pins[col]) ) {
                        pressed[row] &= ~(1<<col);
                    }
                } else {
                    if(! gpio_get(col_pins[col]) ) {
                        *report = row*COL_COUNT+col;
                        tud_hid_report(0, report, 1);
                        pressed[row] |= 1<<col;
                    }
                }
            }
            gpio_set_dir(row_pins[row], false);
            gpio_pull_up(row_pins[row]);
        }
    }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

