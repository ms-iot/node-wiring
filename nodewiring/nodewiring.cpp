#include "stdafx.h"

#pragma comment(lib, "node")
#include "node.h"
#include "v8.h"
#include <Windows.h>
#include "arduino.h"


using namespace node;
using namespace v8;

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

/*
Export all the functions for module
*/
extern "C" void NODE_EXTERN init(Handle<Object> target)
{
	HandleScope scope;

	target->Set(v8::String::NewSymbol("ioInit"),
		FunctionTemplate::New(IOInit)->GetFunction());

  target->Set(v8::String::NewSymbol("pinMode"),
		FunctionTemplate::New(PinMode)->GetFunction());

	target->Set(v8::String::NewSymbol("digitalWrite"),
		FunctionTemplate::New(DigitalWrite)->GetFunction());

	target->Set(v8::String::NewSymbol("digitalRead"),
		FunctionTemplate::New(DigitalRead)->GetFunction());

  target->Set(v8::String::NewSymbol("analogWrite"),
		FunctionTemplate::New(AnalogWrite)->GetFunction());

	target->Set(v8::String::NewSymbol("analogRead"),
		FunctionTemplate::New(AnalogRead)->GetFunction());

    target->Set(v8::String::NewSymbol("delay"),
        FunctionTemplate::New(Delay)->GetFunction());

    target->Set(v8::String::NewSymbol("delayMicroseconds"),
        FunctionTemplate::New(DelayMicroseconds)->GetFunction());

    target->Set(v8::String::NewSymbol("millis"),
        FunctionTemplate::New(Millis)->GetFunction());

    target->Set(v8::String::NewSymbol("micros"),
        FunctionTemplate::New(Micros)->GetFunction());

    target->Set(v8::String::NewSymbol("shiftIn"),
        FunctionTemplate::New(ShiftIn)->GetFunction());

    target->Set(v8::String::NewSymbol("shiftOut"),
        FunctionTemplate::New(ShiftOut)->GetFunction());
}

NODE_MODULE(nodewiring, init)