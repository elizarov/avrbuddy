
#include <io/Ports.h>

PortB<3> button1;
PortC<4> led1;
PortC<5> led2;

int main() {
  button1.input(); // configure as input
  led1.output();   // configure as output
  led1.set();      // write 1 in output or pullup in input
  led2.clear();    // write 0 in output or no pullup in input
  led2.flip();     // flip bit's state
  led2 = 1;        // clear or set based on expression
  if (button1) {}  // use in expressions to read value
  (led1 | led2).clear(); // clear both leds
}
