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

#ifndef MBED_LIS302_H
#define MBED_LIS302_H
 
#include "mbed.h"

/** An interface for the LIS302 triple axis SPI accelerometer
 *
 * @code
 * // Print out the Z axis acceleration
 * #include "mbed.h"
 * #include "LIS302.h"
 * 
 * LIS302 acc(p5, p6, p7, p8); // mosi, miso, clk, ncs
 * 
 * int main() {
 *     while(1) {
 *         printf("Z axis acceleration = %.2f\n", acc.z());
 *         wait(0.1);              
 *     }
 * }
 * @endcode
 */
class LIS302  {
public:

    /** Create an LIS302 interface, connected to the specified pins
     *
     * @param mosi SPI data out
     * @param miso SPI data in
     * @param clk  SPI clock
     * @param ncs Active low chip select (DigitalOut)
     */
    LIS302(PinName mosi, PinName miso, PinName clk, PinName ncs);

    /** Read the X axis acceleration
     *
     * @return A floating-point value representing acceleration in g
     */    
    float x();

    /** Read the Y axis acceleration
     *
     * @return A floating-point value representing acceleration in g
     */    
    float y();

    /** Read the Z axis acceleration
     *
     * @return - A floating-point value representing acceleration in g
     */    
    float z();

    /** Select the range of the accelerometer
     *
     * @param range 0 = 2g, 1 = 8g
     */        
    void range(int g);

    /** Configure the minima and maxima for the axes to linearise the readings
     *
     * @param maxx float defining the maximum X value
     * @param minx float defining the minimum X value
     * @param maxy float defining the maximum Y value
     * @param miny float defining the minimum Y value
     * @param maxz float defining the maximum Z value
     * @param minz float defining the minimum Z value
     */        
    void calibrate(float maxx = 1, float minx = -1, float maxy = 1, float miny = -1, float maxz = 1, float minz = -1);
    
private:
    SPI _spi;
    DigitalOut _ncs;    

    int whoami();
    int status();
    
    float _factor;
    float _maxx, _minx;
    float _maxy, _miny;
    float _maxz, _minz;        
};

#endif
