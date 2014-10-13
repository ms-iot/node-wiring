var galileo = require("./nodewiring");

var led = 13;

//setup
galileo.ioInit();
galileo.pinMode(led, 1);

// loop
while (1) {
   // Global Variables
   console.log('----- Global Variables -----');
   console.log("LOW: %d", galileo.LOW);
   console.log("HIGH: %d", galileo.HIGH);
   
   console.log("INPUT: %d", galileo.INPUT);
   console.log("OUTPUT: %d", galileo.OUTPUT);
   console.log("INPUT_PULLUP: %d", galileo.INPUT_PULLUP);
   
   console.log("CHANGE: %d", galileo.CHANGE);
   console.log("FALLING: %d", galileo.FALLING);
   console.log("RISING: %d", galileo.RISING);
   
   console.log("LSBFIRST: %d", galileo.LSBFIRST);
   console.log("MSBFIRST: %d", galileo.MSBFIRST);
   
   console.log("WLED: %d", galileo.WLED);
   console.log("LED_BUILTIN: %d", galileo.LED_BUILTIN);
   
   console.log("PI: %d", galileo.PI);
   console.log("HALF_PI: %d", galileo.HALF_PI);
   console.log("TWO_PI: %d", galileo.TWO_PI);

   // Digital Tests
   console.log('\n----- Digital Tests -----');
   console.log('Digital Write');
   galileo.digitalWrite(13, 0);
   console.log("LED OFF");
   console.log('Delay 1 seconds');
   galileo.delay(1000);
   galileo.digitalWrite(13, 1);
   console.log("LED ON");
   console.log('DelayMicroseconds for 1 second');
   galileo.delayMicroseconds(1000000);
   
   console.log('Digital Read');
   galileo.digitalRead(2);
   
   console.log('Millis: %d', galileo.millis());
   console.log('Micros: %d', galileo.micros());

   // shift in: datapin, clockpin, bitorder
   console.log('ShiftIn');
   galileo.shiftIn(1, 2, galileo.LSBFIRST);
   console.log('ShiftOut');
   galileo.shiftOut(1, 2, galileo.LSBFIRST, 10);
   
   // Analog Tests
   console.log('\n----- Analog Tests -----');
   console.log('AnalogWriteResolution');
   galileo.analogWriteResolution(12);
   console.log('AnalogReadResolution');
   galileo.analogReadResolution(12);
   console.log('AnalogWrite');
   galileo.analogWrite(3, 4095);
   
   console.log("Temperature: ");
   var temp = galileo.analogRead(-1);
   console.log(temp);
   console.log("\n");
   
   console.log('Tone with 2 arguments on pin 10');
   galileo.tone(10, 300);
   console.log('1 second delay');
   galileo.delay(1000);
   console.log('NoTone on pin 10:');
   galileo.noTone(10);
   console.log('1 second delay');
   galileo.delay(1000);
   console.log('Tone with 3 arguments on pin 10');
   galileo.tone(10, 300, 1000);
   console.log('5 second delay');
   galileo.delay(5000);
   
   // SPI Tests
   console.log('\n----- SPI Tests -----');
   var spi = galileo.Spi();
   console.log('Checking whether SPI is defined: ' + spi);
   console.log('Calling Spi Begin');
   spi.begin();
   console.log('Calling Spi SetDataMode');
   spi.setDataMode(galileo.SPI_MODE1);
   console.log('Calling Spi SetClockDivider');
   spi.setClockDivider(galileo.SPI_CLOCK_DIV64);
   console.log('Calling Spi SetBitOrder');
   spi.setBitOrder(galileo.LSBFIRST);
   console.log('Calling Spi Transfer');
   spi.transfer(10);
   console.log('Calling Spi End');
   spi.end();
   
   console.log('\n----- End of Loop -----\n\n');
   galileo.delay(5000);
}