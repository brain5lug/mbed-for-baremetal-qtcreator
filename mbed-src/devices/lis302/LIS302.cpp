/* mbed LIS302 Accelerometer Library
 * Copyright (c) 2008-2010, sford, cstyles, wreynolds
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
 */

#include "LIS302.h"
#include "mbed.h"

#define LIS302_WHOAMI               0x0F
#define LIS302_CTRL_REG1            0x20
#define LIS302_CTRL_REG2            0x21
#define LIS302_CTRL_REG3            0x22
#define LIS302_HP_FILTER_RST        0x23
#define LIS302_STATUS_REG           0x27
#define LIS302_OUTX                 0x29
#define LIS302_OUTY                 0x2B
#define LIS302_OUTZ                 0x2D
#define LIS302_FF_WU_CFG1           0x30
#define LIS302_FF_WU_SRC_1          0x31
#define LIS302_FF_WU_THS_1          0x32
#define LIS302_FF_WU_DURATION_1     0x33
#define LIS302_FF_WU_CFG_2          0x34
#define LIS302_FF_WU_SRC_2          0x35
#define LIS302_FF_WU_THS_2          0x36
#define LIS302_FF_WU_DURATION_2     0x37
#define LIS302_CLICK_CFG            0x38
#define LIS302_CLICK_SRC            0x39
#define LIS302_CLICK_THSY_X         0x3B
#define LIS302_CLICK_THSZ           0x3C
#define LIS302_READ                 0x80
#define LIS302_WRITE                0x00

#define LIS302_STATUS_X_AVAILABLE 0x1
#define LIS302_STATUS_Y_AVAILABLE 0x2
#define LIS302_STATUS_Z_AVAILABLE 0x4

#define FACTOR_2g 55.6
#define FACTOR_8g 13.9

LIS302::LIS302(PinName mosi, PinName miso, PinName clk, PinName ncs)
    : _spi(mosi, miso, clk), _ncs(ncs) {

    // Make sure CS is high
    _ncs = 1;

    // Set up the spi interface
    _spi.format(8, 3);
    _spi.frequency(1000000);

    // Write to CTRL_REG1
    _ncs = 0;
    _spi.write(LIS302_WRITE | LIS302_CTRL_REG1);
    _spi.write (0x47);
    _ncs = 1;

    // Write to CTRL_REG2
    _ncs = 0;
    _spi.write(LIS302_WRITE | LIS302_CTRL_REG2);
    _spi.write (0x0);  // This is default anyway
    _ncs = 1;

    // Write to CTRL_REG3
    _ncs = 0;
    _spi.write(LIS302_WRITE | LIS302_CTRL_REG3);
    _spi.write (0x0);  // This is default anyway
    _ncs = 1;

    range(0);
    calibrate();
}

float LIS302::x() {
    // wait for a new sample
    while(!(status() & LIS302_STATUS_X_AVAILABLE));

    _ncs = 0;
    _spi.write(LIS302_READ | LIS302_OUTX);
    signed char raw = _spi.write(0x00);
    _ncs = 1;

    float gradient = (2.0/(_maxx-_minx));
    return (gradient*(float)(raw)/_factor)+((-gradient*_maxx)+1);
}

float LIS302::y() {
    // wait for a new sample
    while(!(status() & LIS302_STATUS_Y_AVAILABLE));

    _ncs = 0;
    _spi.write(LIS302_READ | LIS302_OUTY);
    signed char raw = _spi.write(0x00);
    _ncs = 1;

    float gradient = (2.0/(_maxy-_miny));
    return (gradient*(float)(raw)/_factor)+((-gradient*_maxy)+1);
}

float LIS302::z() {
    // wait for a new sample
    while(!(status() & LIS302_STATUS_Z_AVAILABLE));

    _ncs = 0;
    _spi.write(LIS302_READ | LIS302_OUTZ);
    signed char raw = _spi.write(0x00);
    _ncs = 1;

    float gradient = (2.0/(_maxz-_minz));
    return (gradient*(float)(raw)/_factor)+((-gradient*_maxz)+1);
}

void LIS302::range(int g) {

    // fetch the current CRTL_REG1
    _ncs = 0;
    _spi.write(LIS302_READ | LIS302_CTRL_REG1);
    int value = _spi.write(0x00);
    _ncs = 1;

    // set the range bit, and the calculation factor
    if(g) {
        value |= 0x20; // 8g
        _factor = FACTOR_8g;
    } else {
        value &= ~0x20; // 2g
        _factor = FACTOR_2g;
    }

    _ncs = 0;
    _spi.write(LIS302_WRITE | LIS302_CTRL_REG1);
    _spi.write(value);
    _ncs = 1;
}

void LIS302::calibrate(float maxx, float minx, float maxy, float miny, float maxz, float minz) {
    _maxx = maxx;
    _minx = minx;
    _maxy = maxy;
    _miny = miny;
    _maxz = maxz;
    _minz = minz;
}

int LIS302::whoami() {
    _ncs = 0;
    _spi.write(LIS302_READ | LIS302_WHOAMI);
    int value = _spi.write(0x00);
    _ncs = 1;
    return value;
}

int LIS302::status() {
    _ncs = 0;
    _spi.write(0xA7);
    int value = _spi.write(LIS302_READ | LIS302_STATUS_REG);
    _ncs = 1;
    return value;
}
