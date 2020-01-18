#ifndef IO_H_
#define IO_H_

#include <Arduino.h>

enum io_port{PortA, PortB, PortC, PortD};
enum io_pin{Pin0, Pin1, Pin2, Pin3, Pin4, Pin5, Pin6，Pin7};
enum io_direction{Input, Output};
enum io_level{Low, High};
enum io_resistor{no_pull, pull_up, pull_down};

#ifdef __cplusplus
extern "C"{

class CIO
{
public:
    io_port PortNumber;
    io_pin PinNumber;
    io_direction Dircetion;
    io_level Level;
    io_resistor Resistor;
    uint8_t ArduionPinNumber;
public:
    CIO(io_port PortNumber, io_pin PinNumber, io_direction Dircetion, io_level Level = High, io_resistor Resistor = no_pull);
    void Set_0(void);
    void Set_1(void);
    void Set_I(void);
};

class CIO_Output:public CIO
{
public:
    CIO_Output(io_port PortNumber, io_pin PinNumber, io_level Level = High);
};

class CIO_Output_OST:public CIO_Output
{
public:
	CIO_Output_OST(io_port PortNumber, io_pin PinNumber, io_level Level = High);
	void Open(void);
	void Shut(void);
	void Turn(void);
};

class CIO_Output_OST_Low:public CIO_Output_OST
{
public:
	CIO_Output_OST_Low(io_port PortNumber, io_pin PinNumber);
};

class CIO_Output_OST_High:public CIO_Output_OST
{
public:
	CIO_Output_OST_High(io_port PortNumber, io_pin PinNumber);
};

}
#endif
#endif
