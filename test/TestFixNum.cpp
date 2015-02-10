
#include <fixnum/FixNum.h>


int main() {
  FixNum<uint8_t,0> x = 23;
  FixNum<int16_t,1> y = x;
  if (x < y) { }
}