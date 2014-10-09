var galileo = require("./nodewiring");

var led = 13;

//setup
galileo.ioInit();
galileo.pinMode(led, 1);

// loop
while (1) {
   // Global Variables
   console.log('----- Global Variables -----\n');
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
   console.log('----- DigitalTests -----\n');
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

    console.log('----- End of Loop -----\n\n');
}