#ifndef __include_UnShift_h__
#include "MersenneTwister.h"

u_int32_t getMSB(u_int32_t x,u_int32_t n);

u_int32_t setMSB(u_int32_t x,u_int32_t n,u_int32_t b);

u_int32_t undoRightShiftXor(u_int32_t y,u_int32_t s);

u_int32_t getLSB(u_int32_t x,u_int32_t n);

u_int32_t setLSB(u_int32_t x,u_int32_t n,u_int32_t b);

u_int32_t undoLeftShiftXorAnd(u_int32_t y,u_int32_t s,u_int32_t k);

u_int32_t untemper(u_int32_t y);

void UnShift();


#define __include_UnShift_h__
#endif 
