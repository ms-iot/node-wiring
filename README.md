node-wiring
===========

Wiring API implementation for Node.js

This package allows you to control the Intel Galileo natively with Node.js



# Building From Source
* Clone this repo
* Open the solution file
* Download the Node.js [sources](http://nodejs.org/download/)
* Unzip the sources and place them in your root c:\ directory
* Make sure [python](http://python.org) is installed
* Build the sources by running the vcbuild.bat file in the sources.
* In visual studio select properties (most of this should already be done)
    * In the `VC++ Directories > Include Directories` add
        * `%node source%\src`
        * `%node source%\deps\v8\include`
        * `%node source%\deps\uv\include`
    * We must also link against the node.lib file that was built when we compiled node sources.
    in `Linker > Input > Additional Dependencies` add
        * `%user directory%\.node-gyp\%node version%\ia32\node.lib`
    * In `General` change `Target Extension` to `.node`
* Build the project
* Copy the `nodewiring.node` folder from the Debug directory to your Galileo.

# Using the Module
This module can be required at the top of your node application.

Include the `nodewiring.node` file in the same directory as your application file.
```js
var io = require("./nodewiring");
```

## API

**ioInit()**

> Initializes board this must be run first

**pinMode(pin, 1|0)**

> Sets mode of pin 1 (INPUT) or 0 (OUTPUT)

**digitalWrite(pin, 1|0)**

> Sets the pin to 1 or 0 (HIGH or LOW)

Example:
```js
io.digitalWrite(13, 1);
```

**digitalRead(pin)**

> Returns the value of the pin, 1 or 0 (Our SDK reads HIGH and when connected to ground reads LOW)

Example:
```js
io.digitalRead(6);
```

**analogWrite(pin, value)**

> Writes value to the analog pin

Example:
```js
io.analogWrite(6, 255);
```

**analogRead(pin)**

> Returns value read from analog pin

Example:
```js
io.analogRead(14);
```

