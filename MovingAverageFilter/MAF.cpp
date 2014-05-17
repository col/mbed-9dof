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
 * 10-Point Moving Average Filter
 */
 
#include "MAF.h"

   MAF::MAF(){}
   
   float MAF::update(float data){
   
    _k[0] = data;
    _result = _k[0]*0.1 + _k[1]*0.1 + _k[2]*0.1 + _k[3]*0.1 + _k[4]*0.1 + _k[5]*0.1 + _k[6]*0.1 + _k[7]*0.1 + _k[8]*0.1 + _k[9]*0.1 ;
    _k[9] = _k[8];
    _k[8] = _k[7];
    _k[7] = _k[6];
    _k[6] = _k[5];
    _k[5] = _k[4];
    _k[4] = _k[3];
    _k[3] = _k[2];
    _k[2] = _k[1];
    _k[1] = _k[0];
   
   return _result;
   }
   
   int MAF::updateInt(int data){
   
    _a[0] = data;
    _result = _a[0]*0.1 + _a[1]*0.1 + _a[2]*0.1 + _a[3]*0.1 + _a[4]*0.1 + _a[5]*0.1 + _a[6]*0.1 + _a[7]*0.1 + _a[8]*0.1 + _a[9]*0.1 ;
    _a[9] = _a[8];
    _a[8] = _a[7];
    _a[7] = _a[6];
    _a[6] = _a[5];
    _a[5] = _a[4];
    _a[4] = _a[3];
    _a[3] = _a[2];
    _a[2] = _a[1];
    _a[1] = _a[0];
   
   return _resultInt;
   }