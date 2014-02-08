//MegaTestSuite.cpp

// The MIT License (MIT)
// Copyright (c) 2013, Charles Jessup Franklin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "MegaTestSuite.h"


/***************************************************************************
                                Helper Functions
***************************************************************************/

namespace MegaTest {

bool floatCompare(float a, float b) {
#ifdef MEGA_FLOAT_MAXULPS
	return AlmostEqual2sComplement(a, b, MEGA_FLOAT_MAXULPS);
#elif defined MEGA_FLOAT_REL_COMPARE
	return AlmostEqualRelativeOrAbsolute(a, b, MEGA_FLOAT_MAX_REL, MEGA_FLOAT_MAX_ABS);
#else
	return a == b;
#endif
}

#define MEGA_FLIP_VECTOR (unsigned long) 0x80000000UL

bool AlmostEqual2sComplement(float A, float B, int maxUlps)
{
    // Make sure maxUlps is non-negative and small enough that the
    // default NAN won't compare as equal to anything.
    if (maxUlps < 0 || maxUlps > 4 * 1024 * 1024) return false;
    int aInt = *(int*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = MEGA_FLIP_VECTOR - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = MEGA_FLIP_VECTOR - bInt;
    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
}

bool AlmostEqualRelativeOrAbsolute(float A, float B,
                float maxRelativeError, float maxAbsoluteError)
{
    if (fabs(A - B) < maxAbsoluteError)
        return true;
    float relativeError;
    if (fabs(B) > fabs(A))
        relativeError = fabs((A - B) / B);
    else
        relativeError = fabs((A - B) / A);
    if (relativeError <= maxRelativeError)
        return true;
    return false;
}

} //namespace