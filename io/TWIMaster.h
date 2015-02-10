#ifndef TWI_MASTER_H_
#define TWI_MASTER_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>

typedef uint16_t twi_speed_t;

const twi_speed_t TWI_10HZ  = 0; // todo
const twi_speed_t TWI_100HZ = 0; // todo

class TWIMaster {
private:
  uint8_t _prr;
  uint8_t _twbr;
  uint8_t _twcr;
  uint8_t _twsr;

public:
  TWIMaster(twi_speed_t speed);
  ~TWIMaster();
  void transmit(uint8_t addr);
  void receive(uint8_t addr);
};

#endif
