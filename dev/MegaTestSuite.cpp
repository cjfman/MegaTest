//MegaTestSuite

#include "MegaTestSuite.hpp"


/***************************************************************************
                                Helper Functions
***************************************************************************/

namespace MegaTest {

bool floatCompare(float a, float b) {
#ifdef AVR_FLOAT_MAXULPS
	return AlmostEqual2sComplement(a, b, AVR_FLOAT_MAXULPS);
#elif defined AVR_FLOAT_REL_COMPARE
	return AlmostEqualRelativeOrAbsolute(a, b, AVR_FLOAT_MAX_REL, AVR_FLOAT_MAX_ABS);
#else
	return a == b;
#endif
}

#define AVR_FLIP_VECTOR (unsigned long) 0x80000000UL

bool AlmostEqual2sComplement(float A, float B, int maxUlps)
{
    // Make sure maxUlps is non-negative and small enough that the
    // default NAN won't compare as equal to anything.
    if (maxUlps < 0 || maxUlps > 4 * 1024 * 1024) return false;
    int aInt = *(int*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = AVR_FLIP_VECTOR - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = AVR_FLIP_VECTOR - bInt;
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
