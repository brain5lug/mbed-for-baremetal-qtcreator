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
SPI _spi(PA_7,PA_6,PA_5);
DigitalOut _cs(PE_3);

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
		myled = 1;
		wait(0.2);
		myled = 0;
		wait(0.2);
	}
}
