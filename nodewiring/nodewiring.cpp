// Copyright (c) Microsoft Open Technologies, Inc.  All rights reserved.
// Licensed under the MIT License. 
// See License.txt in the project root for license information.

#include "stdafx.h"

#pragma comment(lib, "node")
#include "node.h"
#include "v8.h"
#include <Windows.h>
#include "arduino.h"
#include "spi.h"
#include "PulseIn.h"

using namespace node;
using namespace v8;

// Arduino Functions
Handle<Value> IOInit(const Arguments& args) {
	HandleScope scope;
	ArduinoInit();


	return Undefined();
}

Handle<Value> DigitalWrite(const Arguments& args) {
	if (args.Length() != 2) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 2 arguments, pin and state"))
			);
	}

	Local<Integer> pin = args[0]->ToInteger();
	Local<Integer> state = args[1]->ToInteger();

    try
    {
        digitalWrite(static_cast<int>(pin->Value()), static_cast<int>(state->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
	
	return Undefined();
}

Handle<Value> DigitalRead(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 1 argument to digitalRead, the pin to read."))
			);
	}

	Local<Integer> pin = args[0]->ToInteger();

    try
    {
        int value = digitalRead(static_cast<int>(pin->Value()));
        return scope.Close(Integer::New(value));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
}

Handle<Value> AnalogWrite(const Arguments& args) {
    if (args.Length() != 2) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 2 arguments to AnalogWrite, pin and value."))
			);
	}
	Local<Integer> pin = args[0]->ToInteger();
	Local<Integer> value = args[1]->ToInteger();

    try
    {
        analogWrite(static_cast<uint8_t>(pin->Value()), static_cast<uint32_t>(value->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }

	return Undefined();
}

Handle<Value> AnalogWriteResolution(const Arguments& args) {
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to AnalogWriteResolution, the resolution"))
            );
    }

    Local<Integer> resolution = args[0]->ToInteger();
    
    try
    {
        analogWriteResolution(static_cast<int>(resolution->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }

    return Undefined();
}

Handle<Value> AnalogRead(const Arguments& args) {
	HandleScope scope;
	if (args.Length() != 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 1 argument to AnalogRead, the pin to read."))
			);
	}

	Local<Integer> pin = args[0]->ToInteger();
    try
    {
        int value = analogRead(static_cast<int>(pin->Value()));
        return scope.Close(Integer::New(value));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
	
}

Handle<Value> AnalogReadResolution(const Arguments& args) {
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to AnalogReadResolution, the resolution."))
            );
    }

    Local<Integer> resolution = args[0]->ToInteger();
    
    try
    {
        analogReadResolution(static_cast<int>(resolution->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

Handle<Value> Millis(const Arguments& args) {
    HandleScope scope;
    try
    {
        unsigned long value = millis();
        return scope.Close(Uint32::New(value));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
}

Handle<Value> Micros(const Arguments& args) {
    HandleScope scope;
    try
    {
        unsigned long value = micros();
        return scope.Close(Uint32::New(value));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
}

Handle<Value> Delay(const Arguments& args) {
	if (args.Length() != 1) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 1 argument to Delay, the value to in ms."))
			);
	}
	Local<Integer> val = args[0]->ToInteger();
	unsigned long ms = static_cast<unsigned long>(val->Value());

    try
    {
        delay(ms);
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
	
	return Undefined();
}


Handle<Value> DelayMicroseconds(const Arguments& args) {
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to DelayMicroseconds, the value in microseconds."))
            );
    }
    Local<Uint32> val = args[0]->ToUint32();
    unsigned long ms = static_cast<unsigned long>(val->Value());
    try
    {
        delayMicroseconds(ms);
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    return Undefined();
}

Handle<Value> PinMode(const Arguments& args) {
	if (args.Length() != 2) {
		return ThrowException(
			Exception::TypeError(v8::String::New("Must pass 2 arguments to PinMode, pin and mode."))
			);
	}
	Local<Integer> pin = args[0]->ToInteger();
	Local<Integer> mode = args[1]->ToInteger();

    try
    {
        pinMode(static_cast<int>(pin->Value()), static_cast<int>(mode->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }

	return Undefined();
}

Handle<Value> ShiftIn(const Arguments& args) {
    HandleScope scope;
    if (args.Length() != 3) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 3 arguments to ShiftIn, data_pin, clock_pin, and bit_order."))
            );
    }
    Local<Integer> data_pin = args[0]->ToInteger();
    Local<Integer> clock_pin = args[1]->ToInteger();
    Local<Integer> bit_order = args[2]->ToInteger();

    try
    {
        return scope.Close(Uint32::New(shiftIn(static_cast<uint8_t>(data_pin->Value()), static_cast<uint8_t>(clock_pin->Value()), static_cast<uint8_t>(bit_order->Value()))));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
}

Handle<Value> ShiftOut(const Arguments& args) {
    if (args.Length() != 4) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 4 arguments to ShiftOut, data_pin, clock_pin, bit_order, and byte."))
            );
    }
    Local<Integer> data_pin = args[0]->ToInteger();
    Local<Integer> clock_pin = args[1]->ToInteger();
    Local<Integer> bit_order = args[2]->ToInteger();
    Local<Integer> byte = args[3]->ToInteger();

    try
    {
        shiftOut(static_cast<uint8_t>(data_pin->Value()), static_cast<uint8_t>(clock_pin->Value()), static_cast<uint8_t>(bit_order->Value()), static_cast<uint8_t>(byte->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }

    return Undefined();
}


Handle<Value> Tone(const Arguments& args) {
    if (args.Length() == 2) {
        Local<Integer> pin = args[0]->ToInteger(); // int
        Local<Uint32> frequency = args[1]->ToUint32(); // unsigned int
        
        try
        {
            tone(static_cast<int>(pin->Value()), static_cast<int>(frequency->Value()));
        }
        catch (std::exception e)
        {
            return ThrowException(Exception::TypeError(v8::String::New(e.what())));
        }
        return Undefined();
    }
    else if (args.Length() == 3)
    {
        Local<Integer> pin = args[0]->ToInteger(); // int
        Local<Uint32> frequency = args[1]->ToUint32(); // unsigned int
        Local<Uint32> duration = args[2]->ToUint32(); // unsigned long

        try
        {
            tone(static_cast<int>(pin->Value()), static_cast<unsigned int>(frequency->Value()), static_cast<unsigned long>(duration->Value()));
        }
        catch (std::exception e)
        {
            return ThrowException(Exception::TypeError(v8::String::New(e.what())));
        }
        return Undefined();
    }
    else
    {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 2 or 3 arguments to Tone, (pin and frequency) or (pin, frequency, and duration)."))
            );
    }
}

Handle<Value> NoTone(const Arguments& args) {
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to NoTone, pin."))
            );
    }
    Local<Integer> pin = args[0]->ToInteger();
    
    try
    {
        noTone(static_cast<int>(pin->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }

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
    try
    {
        spiInstance.begin();
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiEnd(const Arguments& args)
{
    try
    {
        spiInstance.end();
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiSetDataMode(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to SpiSetDataMode, the mode."))
            );
    }
    Local<Integer> mode = args[0]->ToInteger();
    try
    {
        spiInstance.setDataMode(static_cast<uint8_t>(mode->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiSetClockDivider(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to SpiSetClockDivider, the clock divider."))
            );
    }
    Local<Integer> clockDiv = args[0]->ToInteger();
    try
    {
        spiInstance.setClockDivider(static_cast<uint8_t>(clockDiv->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiTransfer(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to SpiTransfer, the transfer value."))
            );
    }
    Local<Integer> value = args[0]->ToInteger();
    try
    {
        spiInstance.transfer(static_cast<uint8_t>(value->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

v8::Handle<Value> SpiNodeWrapper::SpiSetBitOrder(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to SpiSetBitOrder, the bitOrder."))
            );
    }
    Local<Integer> bitOrder = args[0]->ToInteger();
    try
    {
        spiInstance.setBitOrder(static_cast<uint8_t>(bitOrder->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();

}

/* Wire Wrapper Class and functions */

class WireNodeWrapper : public node::ObjectWrap
{
public:
    static void Init(v8::Handle<v8::Object> exports);
private:
    static v8::Persistent<v8::Function> constructor;
    static TwoWire wireInstance;

    WireNodeWrapper()
    {}
    ~WireNodeWrapper()
    {}

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireBegin(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireRequestFrom(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireBeginTransmission(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireEndTransmission(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireWrite(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireAvailable(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireRead(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireOnReceive(const v8::Arguments& args);
    static v8::Handle<v8::Value> WireOnRequest(const v8::Arguments& args);
};

// These need to be declared outside of the class as well
TwoWire WireNodeWrapper::wireInstance;
Persistent<Function> WireNodeWrapper::constructor;

void WireNodeWrapper::Init(v8::Handle<v8::Object> exports)
{
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(v8::String::NewSymbol("Wire"));
    tpl->InstanceTemplate()->SetInternalFieldCount(6);

    // Prototype
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("begin"), FunctionTemplate::New(WireBegin)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("requestFrom"), FunctionTemplate::New(WireRequestFrom)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("beginTransmission"), FunctionTemplate::New(WireBeginTransmission)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("endTransmission"), FunctionTemplate::New(WireEndTransmission)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("write"), FunctionTemplate::New(WireWrite)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("available"), FunctionTemplate::New(WireAvailable)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("read"), FunctionTemplate::New(WireRead)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("onReceive"), FunctionTemplate::New(WireOnReceive)->GetFunction());
    tpl->PrototypeTemplate()->Set(v8::String::NewSymbol("onRequest"), FunctionTemplate::New(WireOnRequest)->GetFunction());

    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(v8::String::NewSymbol("Wire"), constructor);
}

v8::Handle<v8::Value> WireNodeWrapper::New(const v8::Arguments& args)
{
    HandleScope scope;

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
        WireNodeWrapper* obj = new WireNodeWrapper();
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

v8::Handle<Value> WireNodeWrapper::WireBegin(const Arguments& args)
{
    try
    {
        wireInstance.begin();
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

v8::Handle<Value> WireNodeWrapper::WireBeginTransmission(const Arguments& args)
{
    if (args.Length() != 1) {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 argument to WireBeginTransmission, the slaveAddress."))
            );
    }
    Local<Integer> slaveAddress = args[0]->ToInteger();
    try
    {
        wireInstance.beginTransmission(static_cast<uint8_t>(slaveAddress->Value()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
    
    return Undefined();
}

v8::Handle<Value> WireNodeWrapper::WireEndTransmission(const Arguments& args)
{
    HandleScope scope;
    if (args.Length() == 0)
    {
        try
        {
            return scope.Close(Uint32::New(wireInstance.endTransmission()));
        }
        catch (std::exception e)
        {
            return ThrowException(Exception::TypeError(v8::String::New(e.what())));
        }
    }
    else if (args.Length() == 1)
    {
        Local<Integer> sendStop = args[0]->ToInteger();
        try
        {
            return scope.Close(Uint32::New(wireInstance.endTransmission(static_cast<uint8_t>(sendStop->Value()))));
        }
        catch (std::exception e)
        {
            return ThrowException(Exception::TypeError(v8::String::New(e.what())));
        }
    }
    else
    {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 0 or 1 argument to WireEndTransmission, the sendStop value"))
            );
    }
}

v8::Handle<Value> WireNodeWrapper::WireRequestFrom(const Arguments& args)
{
    HandleScope scope;
    if (args.Length() == 2)
    {
        Local<Integer> address = args[0]->ToInteger();
        Local<Integer> quantity = args[1]->ToInteger();

        try{
            return scope.Close(Uint32::New(wireInstance.requestFrom(
                static_cast<uint8_t>(address->Value()), 
                static_cast<uint8_t>(quantity->Value()))));
        }
        catch (std::exception e)
        {
            return ThrowException(Exception::TypeError(v8::String::New(e.what())));
        }
    }
    else if (args.Length() == 3)
    {
        Local<Integer> address = args[0]->ToInteger();
        Local<Integer> quantity = args[1]->ToInteger();
        Local<Integer> sendStop = args[2]->ToInteger();

        try
        {
            return scope.Close(Uint32::New(wireInstance.requestFrom(
                static_cast<uint8_t>(address->Value()),
                static_cast<uint8_t>(quantity->Value()),
                static_cast<uint8_t>(sendStop->Value()))));
        }
        catch (std::exception e)
        {
            return ThrowException(Exception::TypeError(v8::String::New(e.what())));
        }
    }
    else
    {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 2 or 3 arguments to WireRequestFrom, (address and quantity) or (address, quantity, and sendStop)"))
            );
    }
}

v8::Handle<Value> WireNodeWrapper::WireWrite(const Arguments& args)
{
    HandleScope scope;
    if (args.Length() == 1)
    {
        if (args[0]->IsInt32()) // integer
        {
            Local<Integer> data = args[0]->ToInteger();
            try
            {
                return scope.Close(Uint32::New(wireInstance.write(
                    static_cast<uint8_t>(data->Value()))));
            }
            catch (std::exception e)
            {
                return ThrowException(Exception::TypeError(v8::String::New(e.what())));
            }
        }
        else if (args[0]->IsString()) // string
        {
            Local<v8::String> data = args[0]->ToString();
            std::string str = std::string(*(v8::String::AsciiValue(data)));
            const char * c = str.c_str();
            try
            {
                return scope.Close(Uint32::New(wireInstance.write((const uint8_t *)c, strlen(c))));
            }
            catch (std::exception e)
            {
                return ThrowException(Exception::TypeError(v8::String::New(e.what())));
            }
        }
        else
        {
            return ThrowException(
                Exception::TypeError(v8::String::New("When passing in 1 argument to Wire.write, it must be an integer or string."))
                );
        }
    }
    else if (args.Length() == 2 && args[0]->IsArray())
    {
        // translation from a JS array to a uint8_t pointer that write is expecting
        Handle<Array> addressArray = Handle<Array>::Cast(args[0]);
        uint8_t *inputArray = new uint8_t[addressArray->Length()];
        Local<v8::String> data = args[0]->ToString();

        for (uint32_t i = 0; i < addressArray->Length(); i++)
        {
            Local<Value> value = addressArray->Get(i);
            inputArray[i] = static_cast<uint8_t>(value->ToInteger()->Value());
        }

        try
        {
            return scope.Close(Uint32::New(wireInstance.write(
                inputArray, 
                static_cast<uint8_t>(args[1]->ToInteger()->Value()))));
        }
        catch (std::exception e)
        {
            return ThrowException(Exception::TypeError(v8::String::New(e.what())));
        }
    }
    else
    {
        return ThrowException(
            Exception::TypeError(v8::String::New("Must pass 1 or 2 arguments to WireWrite, (integer or string) or (Array and size)"))
            );
    }
}

v8::Handle<Value> WireNodeWrapper::WireAvailable(const Arguments& args)
{
    HandleScope scope;
    try
    {
        return scope.Close(Uint32::New(wireInstance.available()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
}

v8::Handle<Value> WireNodeWrapper::WireRead(const Arguments& args)
{
    HandleScope scope;
    try
    {
        return scope.Close(Uint32::New(wireInstance.read()));
    }
    catch (std::exception e)
    {
        return ThrowException(Exception::TypeError(v8::String::New(e.what())));
    }
}

v8::Handle<Value> WireNodeWrapper::WireOnReceive(const Arguments& args)
{
    Log("FEATURE UNAVAILABLE: Galileo cannot act as I2C slave device!");
    return Undefined();
}

v8::Handle<Value> WireNodeWrapper::WireOnRequest(const Arguments& args)
{
    Log("FEATURE UNAVAILABLE: Galileo cannot act as I2C slave device!");
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
    WireNodeWrapper::Init(target);
}


NODE_MODULE(ms_iot_wiring, init)
