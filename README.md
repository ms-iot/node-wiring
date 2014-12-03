ms-iot-wiring
===========

Wiring API implementation for Node.js

This package allows you to control the Intel Galileo natively with Node.js by porting some of the Microsoft.IoT.Galileo.NativeWiring SDK found here:
https://github.com/ms-iot/galileo-sdk

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
* Copy the `ms-iot-wiring.node` folder from the Debug directory to your Galileo.
* Include the `ms-iot-wiring.node` file in the same directory as your application file.
```js
var galileo = require("./ms-iot-wiring");
```

# Publishing the Module
* Run `npm pack` in the folder that contains the package.json
* This will create a file (ms-iot-wiring-[version].tgz)
* Run `npm login` to login with your npmjs.org credentials
* Run `npm publish` to publish this to npm

# Using the Module
This module can be required at the top of your node application.

## HelloBlinky

```
var galileo = require("./ms-iot-wiring");

var led = 13;

//setup
galileo.pinMode(led, 1);

// loop
while (1) {
   galileo.digitalWrite(led, 0);
   galileo.delay(500);
   galileo.digitalWrite(led, 1);
   galileo.delay(500);
}
```

## API

**This exposes GPIO, Analog, I2C, and SPI APIs currently.**
> Examples for using these APIs can be found in test.js

**ioInit()**
> Initializes board this must be run first
