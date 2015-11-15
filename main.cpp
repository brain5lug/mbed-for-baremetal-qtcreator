#include "mbed.h"
#include "LIS302.h"

/* LIS302DL
 * SPI1_MOSI PA_7
 * SPI1_SCK  PA_5
 * SPI1_CS   PE_3
 * SPI1_MISO PA_6
 * MEMS_INT1 PE_0
 * MEMS_INT2 PE_1 */

DigitalOut myled(LED1);
DigitalOut myled2(LED4);
SPI _spi(PA_7,PA_6,PA_5);
DigitalOut _cs(PE_3);

extern "C" void __cxa_pure_virtual(void)
{
// call to a pure virtual function happened ... wow, should never happen ... stop
while(1)
;
}

void operator delete(void *)
{
// should never get here ... we don't use new
while(1)
;
}

void operator delete[](void *)
{
// should never get here ... we don't use new
while(1)
;
}

void* operator new(size_t)
{
// should never get here ... we don't use new
while(1)
;
}

void* operator new[](size_t)
{
// should never get here ... we don't use new
while(1)
;
}

int main() {
   int val=0;
   // 8 bit data, high steady state clock
   _spi.format(8,1);
   // 1 Mhz
   _spi.frequency(1000000);
   //chip select active low
   _cs = 0;
   // Enable the device, and all three channels
   _spi.write(0x47);
   //end transfer
   _cs = 1;
   wait(0.1);
   _cs = 0;
   // Send the command to read the WHOAMI register
   _spi.write(0x8F);
   // send a dummy byte to receive the contents of the WHOAMI register
   val = _spi.write(0x00);

	while(1) {
                myled2 = 0;
		myled = 1;
                wait(0.2);
		myled = 0;
                myled2 = 1;
                wait(0.2);
	}
}
