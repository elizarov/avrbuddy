#ifndef AVRBUDDY_FIXNUN_FIXNUM_UTIL_H_
#define AVRBUDDY_FIXNUN_FIXNUM_UTIL_H_

/*
  Internal utility methods and classes for FixNum library.
*/

#include <stdint.h>
#include <limits.h>

typedef uint8_t prec_t;

namespace FixNumUtil {
  // ----------- Define multiplier values -----------

  template<prec_t prec> struct Multiplier {};

  template<> struct Multiplier<0> { static const int8_t multiplier = 1; };
  template<> struct Multiplier<1> { static const int8_t multiplier = 10; };
  template<> struct Multiplier<2> { static const int8_t multiplier = 100; };
  template<> struct Multiplier<3> { static const int16_t multiplier = 1000; };
  template<> struct Multiplier<4> { static const int16_t multiplier = 10000; };
  template<> struct Multiplier<5> { static const int32_t multiplier = 100000; };
  template<> struct Multiplier<6> { static const int32_t multiplier = 1000000; };

  // ----------- Helper min/max function -----------

  inline uint8_t min(uint8_t a, uint8_t b) { return a < b ? a : b; }
  inline uint8_t max(uint8_t a, uint8_t b) { return a > b ? a : b; }

  // ----------- Define limits for supported types -----------
  
  template<typename T> struct Limits {};
  
  template<> struct Limits<uint8_t> {
    static const uint8_t minValue = 0;
    static const uint8_t maxValue = 0xff;
    static const uint8_t bufSize  = 6;
  };
  
  template<> struct Limits<int8_t> {
    static const int8_t minValue = -0x7f;
    static const int8_t maxValue =  0x7f;
    static const int8_t bufSize  = 6;
  };
  
  template<> struct Limits<int16_t> {
    static const int16_t minValue = -0x7fff;
    static const int16_t maxValue =  0x7fff;
    static const uint8_t bufSize  = 8;
  };
  
  template<> struct Limits<int32_t> {
    static const int32_t minValue = -0x7fffffffL;
    static const int32_t maxValue =  0x7fffffffL;
    static const uint8_t bufSize  = 13;
  };
  
  // ----------- Define largest type between a pair -----------

  template<typename T1, typename T2> struct Common {};
  
  template<> struct Common<uint8_t, uint8_t> { typedef uint8_t type; };
  template<> struct Common<uint8_t, int8_t>  { typedef int16_t type; };
  template<> struct Common<uint8_t, int16_t> { typedef int16_t type; };
  template<> struct Common<uint8_t, int32_t> { typedef int32_t type; };

  template<> struct Common<int8_t, uint8_t>  { typedef int16_t type; };
  template<> struct Common<int8_t, int8_t>   { typedef int8_t type; };
  template<> struct Common<int8_t, int16_t>  { typedef int16_t type; };
  template<> struct Common<int8_t, int32_t>  { typedef int32_t type; };

  template<> struct Common<int16_t, uint8_t> { typedef int16_t type; };
  template<> struct Common<int16_t, int8_t>  { typedef int16_t type; };
  template<> struct Common<int16_t, int16_t> { typedef int16_t type; };
  template<> struct Common<int16_t, int32_t> { typedef int32_t type; };

  template<> struct Common<int32_t, uint8_t> { typedef int32_t type; };
  template<> struct Common<int32_t, int8_t>  { typedef int32_t type; };
  template<> struct Common<int32_t, int16_t> { typedef int32_t type; };
  template<> struct Common<int32_t, int32_t> { typedef int32_t type; };
  
  // ----------- Narrow one type into the other -----------
  
  template<typename T1, typename T2> inline T2 narrow(T1 x) {
    T2 x2 = (T2)x;
    if (x2 != x) // does not fit
      return x < 0 ? Limits<T2>::minValue : Limits<T2>::maxValue;
    return x2; // narrow Ok  
  }

  // ----------- Change decimal precision -----------
  
  template<typename T> T scale(T x, prec_t prec1, prec_t prec2) {
    if (prec2 >= prec1) {
      for (prec_t i = prec1; i < prec2; i++) {
        if (x > Limits<T>::maxValue / 10)
          return Limits<T>::maxValue;
        if (x < Limits<T>::minValue / 10)
          return Limits<T>::minValue;
        x *= 10; 
      }
      return x;
    } else {
      if (x >= Limits<T>::maxValue || x <= Limits<T>::minValue)
        return x;
      // prec2 < prec1
      for (prec_t i = prec2; i < prec1; i++) {
        T mod = x % 10;
        x = x / 10;
        if (mod >= 5)
          x++;
        else if (mod <= -5)
          x--;  
      }
      return x;  
    }  
  }

  // ----------- Change decimal precision and type -----------
  
  template<typename T1, typename T2> T2 convert(T1 x, prec_t prec1, prec_t prec2) {
    typedef typename Common<T1,T2>::type T0;
    T0 x0 = scale((T0)x, prec1, prec2);
    return narrow<T0,T2>(x0);
  }
}

#endif