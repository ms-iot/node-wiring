#include "stdafx.h"

#pragma comment(lib, "node")
#include "node.h"
#include "v8.h"
#include <Windows.h>
#include "arduino.h"
#include "spi.h"

using namespace node;
using namespace v8;

// Arduino Functions
Handle<Value> IOInit(const Arguments& args) {
	HandleScope scope;
	ArduinoInit();
	return Undefined();
}

Handle<Value> DigitalWrite(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 2 arguments, pin and state"))
			);
	}
	Local<Integer> pin = args[0]->ToInteger();
	Local<Integer> state = args[1]->ToInteger();

	digitalWrite(static_cast<int>(pin->Value()), static_cast<int>(state->Value()));

	return Undefined();
}

Handle<Value> DigitalRead(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 1 argument, the pin to read."))
			);
	}

	Local<Integer> pin = args[0]->ToInteger();
	int value = digitalRead(static_cast<int>(pin->Value()));


	return scope.Close(Integer::New(value));

}

Handle<Value> AnalogWrite(const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 2) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 2 arguments, pin and value."))
			);
	}
	Local<Integer> pin = args[0]->ToInteger();
	Local<Integer> value = args[1]->ToInteger();

	analogWrite(static_cast<int>(pin->Value()), static_cast<int>(value->Value()));

	return Undefined();
}

Handle<Value> AnalogWriteResolution(const Arguments& args) {
    HandleScope scope;
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to write resolution."))
            );
    }

    Local<Integer> resolution = args[0]->ToInteger();
    analogWriteResolution(static_cast<int>(resolution->Value()));

    return Undefined();
}

Handle<Value> AnalogRead(const Arguments& args) {
	HandleScope scope;
	if (args.Length() != 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 1 argument, the pin to read."))
			);
	}

	Local<Integer> pin = args[0]->ToInteger();
	int value = analogRead(static_cast<int>(pin->Value()));

	return scope.Close(Integer::New(value));
}

Handle<Value> AnalogReadResolution(const Arguments& args) {
    HandleScope scope;
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to read resolution."))
            );
    }

    Local<Integer> resolution = args[0]->ToInteger();
    analogReadResolution(static_cast<int>(resolution->Value()));

    return Undefined();
}

Handle<Value> Millis(const Arguments& args) {
    HandleScope scope;
    unsigned long value = millis();
    return scope.Close(Uint32::New(value));;
}

Handle<Value> Micros(const Arguments& args) {
    HandleScope scope;
    unsigned long value = micros();
    return scope.Close(Uint32::New(value));;
}

Handle<Value> Delay(const Arguments& args) {
	HandleScope scope;
	if (args.Length() != 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass a value in ms."))
			);
	}
	Local<Integer> val = args[0]->ToInteger();
	unsigned long ms = static_cast<unsigned long>(val->Value());

	delay(ms);

	return Undefined();
}


Handle<Value> DelayMicroseconds(const Arguments& args) {
    HandleScope scope;
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass a value in microseconds."))
            );
    }
    Local<Uint32> val = args[0]->ToUint32();
    unsigned long ms = static_cast<unsigned long>(val->Value());
    delayMicroseconds(ms);
    return Undefined();
}

Handle<Value> PinMode(const Arguments& args) {
	if (args.Length() != 2) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 2 arguments, pin and mode."))
			);
	}
	Local<Integer> pin = args[0]->ToInteger();
	Local<Integer> mode = args[1]->ToInteger();

	pinMode(static_cast<int>(pin->Value()), static_cast<int>(mode->Value()));

	return Undefined();
}

Handle<Value> ShiftIn(const Arguments& args) {
    if (args.Length() != 3) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 3 arguments, data_pin, clock_pin, and bit_order."))
            );
    }
    Local<Integer> data_pin = args[0]->ToInteger();
    Local<Integer> clock_pin = args[1]->ToInteger();
    Local<Integer> bit_order = args[2]->ToInteger();

    shiftIn(static_cast<uint8_t>(data_pin->Value()), static_cast<uint8_t>(clock_pin->Value()), static_cast<uint8_t>(bit_order->Value()));

    return Undefined();
}

Handle<Value> ShiftOut(const Arguments& args) {
    if (args.Length() != 4) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 4 arguments, data_pin, clock_pin, bit_order, and byte."))
            );
    }
    Local<Integer> data_pin = args[0]->ToInteger();
    Local<Integer> clock_pin = args[1]->ToInteger();
    Local<Integer> bit_order = args[2]->ToInteger();
    Local<Integer> byte = args[3]->ToInteger();

    shiftOut(static_cast<uint8_t>(data_pin->Value()), static_cast<uint8_t>(clock_pin->Value()), static_cast<uint8_t>(bit_order->Value()), static_cast<uint8_t>(byte->Value()));

    return Undefined();
}


Handle<Value> Tone(const Arguments& args) {
    if (args.Length() == 2) {
        Local<Integer> pin = args[0]->ToInteger(); // int
        Local<Uint32> frequency = args[1]->ToUint32(); // unsigned int
        tone(static_cast<int>(pin->Value()), static_cast<int>(frequency->Value()));

        return Undefined();
    }
    else if (args.Length() == 3)
    {
        Local<Integer> pin = args[0]->ToInteger(); // int
        Local<Uint32> frequency = args[1]->ToUint32(); // unsigned int
        Local<Uint32> duration = args[2]->ToUint32(); // unsigned long

        tone(static_cast<int>(pin->Value()), static_cast<unsigned int>(frequency->Value()), static_cast<unsigned long>(duration->Value()));

        return Undefined();
    }
    else
    {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 2 or 3 arguments (pin and frequency) or (pin, frequency, and duration)."))
            );
    }
}

Handle<Value> NoTone(const Arguments& args) {
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument, pin."))
            );
    }
    Local<Integer> pin = args[0]->ToInteger();
    noTone(static_cast<int>(pin->Value()));

    return Undefined();
}

/* Spi Wrapper Class and functions */

class SpiNodeWrapper : public node::ObjectWrap
{
public:
    static void Init(v8::Handle<v8::Object> exports);
private:
    static v8::Persistent<v8::Function> constructor;
    static SPIClass spiInstance;

    SpiNodeWrapper()
    {}
    ~SpiNodeWrapper()
    {}

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> SpiBegin(const v8::Arguments& args);
    static v8::Handle<v8::Value> SpiEnd(const v8::Arguments& args);
    static v8::Handle<v8::Value> SpiSetDataMode(const v8::Arguments& args);
    static v8::Handle<v8::Value> SpiSetClockDivider(const v8::Arguments& args);
    static v8::Handle<v8::Value> SpiTransfer(const v8::Arguments& args);
    static v8::Handle<v8::Value> SpiSetBitOrder(const v8::Arguments& args);

};

// These need to be declared outside of the class as well
SPIClass SpiNodeWrapper::spiInstance;
Persistent<Function> SpiNodeWrapper::constructor;

void SpiNodeWrapper::Init(v8::Handle<v8::Object> exports)
{
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(v8::String::NewSymbol("Spi"));
    tpl->InstanceTemplate()->SetInternalFieldCount(6);

    // Prototype
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("begin"), FunctionTemplate::New(SpiBegin)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("end"), FunctionTemplate::New(SpiEnd)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setDataMode"), FunctionTemplate::New(SpiSetDataMode)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setClockDivider"), FunctionTemplate::New(SpiSetClockDivider)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("transfer"), FunctionTemplate::New(SpiTransfer)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("setBitOrder"), FunctionTemplate::New(SpiSetBitOrder)->GetFunction());


    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(v8::String::NewSymbol("Spi"), constructor);
}

v8::Handle<v8::Value> SpiNodeWrapper::New(const v8::Arguments& args)
{
    HandleScope scope;

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        SpiNodeWrapper* obj = new SpiNodeWrapper();
        obj->Wrap(args.This());
        return args.This();
    }
    else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 1;
        Local<Value> argv[argc] = { args[0] };
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

v8::Handle<Value> SpiNodeWrapper::SpiBegin(const Arguments& args)
{
    spiInstance.begin();
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiEnd(const Arguments& args)
{
    spiInstance.end();
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiSetDataMode(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument mode."))
            );
    }
    Local<Integer> mode = args[0]->ToInteger();
    spiInstance.setDataMode(static_cast<uint8_t>(mode->Value()));
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiSetClockDivider(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument clock divider."))
            );
    }
    Local<Integer> clockDiv = args[0]->ToInteger();
    spiInstance.setClockDivider(static_cast<uint8_t>(clockDiv->Value()));
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiTransfer(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument the transfer value."))
            );
    }
    Local<Integer> value = args[0]->ToInteger();
    spiInstance.transfer(static_cast<uint8_t>(value->Value()));
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiSetBitOrder(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument the bitOrder."))
            );
    }
    Local<Integer> bitOrder = args[0]->ToInteger();
    spiInstance.setBitOrder(static_cast<uint8_t>(bitOrder->Value()));
    return Undefined();

}

/*
Export all the functions for module
*/
extern "C" void NODE_EXTERN init(Handle<Object> target)
{
	HandleScope scope;

    // Global Variables
    target->Set(v8::String::New("LOW"), v8::Number::New(LOW));
    target->Set(v8::String::New("HIGH"), v8::Number::New(HIGH));

    target->Set(v8::String::New("INPUT"), v8::Number::New(INPUT));
    target->Set(v8::String::New("OUTPUT"), v8::Number::New(OUTPUT));
    target->Set(v8::String::New("INPUT_PULLUP"), v8::Number::New(INPUT_PULLUP));

    target->Set(v8::String::New("CHANGE"), v8::Number::New(CHANGE));
    target->Set(v8::String::New("FALLING"), v8::Number::New(FALLING));
    target->Set(v8::String::New("RISING"), v8::Number::New(RISING));

    target->Set(v8::String::New("LSBFIRST"), v8::Number::New(LSBFIRST));
    target->Set(v8::String::New("MSBFIRST"), v8::Number::New(MSBFIRST));

    target->Set(v8::String::New("WLED"), v8::Number::New(WLED));
    target->Set(v8::String::New("LED_BUILTIN"), v8::Number::New(LED_BUILTIN));

    target->Set(v8::String::New("PI"), v8::Number::New(PI));
    target->Set(v8::String::New("HALF_PI"), v8::Number::New(HALF_PI));
    target->Set(v8::String::New("TWO_PI"), v8::Number::New(TWO_PI));

    // Arduino Functions
    target->Set(v8::String::NewSymbol("ioInit"), FunctionTemplate::New(IOInit)->GetFunction());
    target->Set(v8::String::NewSymbol("pinMode"), FunctionTemplate::New(PinMode)->GetFunction());
    target->Set(v8::String::NewSymbol("digitalWrite"), FunctionTemplate::New(DigitalWrite)->GetFunction());
    target->Set(v8::String::NewSymbol("digitalRead"), FunctionTemplate::New(DigitalRead)->GetFunction());
    target->Set(v8::String::NewSymbol("analogWrite"), FunctionTemplate::New(AnalogWrite)->GetFunction());
    target->Set(v8::String::NewSymbol("analogWriteResolution"), FunctionTemplate::New(AnalogWriteResolution)->GetFunction());
    target->Set(v8::String::NewSymbol("analogRead"), FunctionTemplate::New(AnalogRead)->GetFunction());
    target->Set(v8::String::NewSymbol("analogReadResolution"), FunctionTemplate::New(AnalogReadResolution)->GetFunction());
    target->Set(v8::String::NewSymbol("delay"), FunctionTemplate::New(Delay)->GetFunction());
    target->Set(v8::String::NewSymbol("delayMicroseconds"), FunctionTemplate::New(DelayMicroseconds)->GetFunction());
    target->Set(v8::String::NewSymbol("millis"), FunctionTemplate::New(Millis)->GetFunction());
    target->Set(v8::String::NewSymbol("micros"), FunctionTemplate::New(Micros)->GetFunction());

    target->Set(v8::String::NewSymbol("shiftIn"), FunctionTemplate::New(ShiftIn)->GetFunction());
    target->Set(v8::String::NewSymbol("shiftOut"), FunctionTemplate::New(ShiftOut)->GetFunction());

    target->Set(v8::String::NewSymbol("tone"), FunctionTemplate::New(Tone)->GetFunction());
    target->Set(v8::String::NewSymbol("noTone"), FunctionTemplate::New(NoTone)->GetFunction());

    // Spi Class Wrapper and Variables
    target->Set(v8::String::New("SPI_MODE0"), v8::Number::New(SPI_MODE0));
    target->Set(v8::String::New("SPI_MODE1"), v8::Number::New(SPI_MODE1));
    target->Set(v8::String::New("SPI_MODE2"), v8::Number::New(SPI_MODE2));
    target->Set(v8::String::New("SPI_MODE3"), v8::Number::New(SPI_MODE3));

    target->Set(v8::String::New("SPI1_MOSI"), v8::Number::New(SPI1_MOSI));
    target->Set(v8::String::New("SPI1_MISO"), v8::Number::New(SPI1_MISO));
    target->Set(v8::String::New("SPI1_SCK"), v8::Number::New(SPI1_SCK));

    target->Set(v8::String::New("SPI1_SPEED"), v8::Number::New(SPI1_SPEED));
    target->Set(v8::String::New("SPI1_BITS_PER_WORD"), v8::Number::New(SPI1_BITS_PER_WORD));
    target->Set(v8::String::New("SPI1_MODE"), v8::Number::New(SPI1_MODE));

    target->Set(v8::String::New("SPI_CLOCK_DIV_MIN"), v8::Number::New(SPI_CLOCK_DIV_MIN));
    target->Set(v8::String::New("SPI_CLOCK_DIV2"), v8::Number::New(SPI_CLOCK_DIV2));
    target->Set(v8::String::New("SPI_CLOCK_DIV4"), v8::Number::New(SPI_CLOCK_DIV4));
    target->Set(v8::String::New("SPI_CLOCK_DIV8"), v8::Number::New(SPI_CLOCK_DIV8));
    target->Set(v8::String::New("SPI_CLOCK_DIV16"), v8::Number::New(SPI_CLOCK_DIV16));
    target->Set(v8::String::New("SPI_CLOCK_DIV32"), v8::Number::New(SPI_CLOCK_DIV32));
    target->Set(v8::String::New("SPI_CLOCK_DIV64"), v8::Number::New(SPI_CLOCK_DIV64));
    target->Set(v8::String::New("SPI_CLOCK_DIV128"), v8::Number::New(SPI_CLOCK_DIV128));
    target->Set(v8::String::New("SPI_CLOCK_DIV_MAX"), v8::Number::New(SPI_CLOCK_DIV_MAX));
    target->Set(v8::String::New("SPI_CLOCK_DIV_DEFAULT"), v8::Number::New(SPI_CLOCK_DIV_DEFAULT));

    SpiNodeWrapper::Init(target);
}


NODE_MODULE(nodewiring, init)
