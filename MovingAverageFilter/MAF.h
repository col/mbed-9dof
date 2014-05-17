/* Copyright (c) <2012> MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Moving Average Filter
 *
 *
 */
 
#ifndef MAF_H
#define MAF_H

#include "mbed.h"

/** 10-Point Moving Average filter
 *
 * Example:
 * @code
 * // Update the filter with gyroscope readings
 * #include "mbed.h"
 * #include "ITG3200.h"
 * #include "MAF.h"
 * 
 * Serial pc(USBTX, USBRX);
 * ITG3200 gyro(p9, p10);
 * MAF Filter();
 * int Average;
 * 
 * int main() {
 *    
 *    gyro.setLpBandwidth(LPFBW_42HZ);
 *
 *     while(1){
 *   
 *      Average = Filter.updateInt(gyro.getGyroX());
 *      pc.printf("%i\n",Average);
 *      wait_ms(50);
 * }    
 * }
 * @endcode
 */
class MAF {

    public:
    
       /* Creates a 10-Point Moving Average Filter object
       *
       */   
        MAF(void);
        
        /* Updates the filter
        *  @param data new data input for the filter,returns the float average
        */
        float update(float data);
        
        /* Updates the filter
        *  @param data new data input for the filter, returns the integer average
        */
        int updateInt(int data);
    
    private :
    
        float _k[10];
        int   _a[10];
        
        float _result;
        int   _resultInt;
};

#endif 