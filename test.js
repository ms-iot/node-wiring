var io = require("./nodewiring");

var led = 13;

//setup
io.ioInit();
io.pinMode(led, 1);

// loop
while (1) {
   // Digital Tests
   io.digitalWrite(13, 0);
   io.Log("LED OFF\n");
   io.delay(500);
   io.digitalWrite(13, 1);
   io.Log("LED ON\n");
   io.delayMicroseconds(500000);
   io.digitalRead(2);
   
   console.log('Millis:');
   console.log(io.millis());
   console.log('Micros:');
   console.log(io.micros());

   // shift in: datapin, clockpin, bitorder
   io.shiftIn(1, 2, LSBFIRST);
   io.shiftOut(1, 2, LSBFIRST, 10);
}