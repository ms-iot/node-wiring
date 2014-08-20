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

	if (args.Length() < 2) {
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

	if (args.Length() < 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 1 argument to read."))
			);
	}

	Local<Integer> pin = args[0]->ToInteger();
	int value = digitalRead(static_cast<int>(pin->Value()));


	return scope.Close(Integer::New(value));

}

Handle<Value> AnalogWrite(const Arguments& args) {
	HandleScope scope;
	if (args.Length() < 2) {
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
	if (args.Length() < 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 1 argument to read."))
			);
	}

	Local<Integer> pin = args[0]->ToInteger();
	int value = analogRead(static_cast<int>(pin->Value()));

	return scope.Close(Integer::New(value));
}


Handle<Value> Delay(const Arguments& args) {
	HandleScope scope;
	if (args.Length() < 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass a value in ms."))
			);
	}
	Local<Integer> val = args[0]->ToInteger();
	unsigned long ms = static_cast<unsigned long>(val->Value());
	delay(ms);
	return Undefined();
}


Handle<Value> PinMode(const Arguments& args) {
	if (args.Length() < 2) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 2 arguments, pin and mode."))
			);
	}
	Local<Integer> pin = args[0]->ToInteger();
	Local<Integer> mode = args[1]->ToInteger();
	pinMode(static_cast<int>(pin->Value()), static_cast<int>(mode->Value()));
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
}

NODE_MODULE(nodewiring, init)