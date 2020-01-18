#include "io.h"

CIO::CIO(io_port PortNumber, io_pin PinNumber, io_direction Dircetion, io_level Level, io_resistor Resistor)
{
    this->PortNumber = PortNumber;
    this->PinNumber = PinNumber;
    this->Dircetion = Dircetion;
    this->Level = Level;
    this->Resistor = Resistor;

/*
---------------------------------------------------------------------------------
|   D0  |   D1  |   D2  |   D3  |   D4  |   D5  |   D6  |   D7  |   D8  |   D9  |
- -------------------------------------------------------------------------------  
|   PD0 |   PD1 |   PD2 |   PD3 |   PD4 |   PD5 |   PD6 |   PD7 |   PB0 |   PB1 |
---------------------------------------------------------------------------------

---------------------------------------------------------------------------------
|   D10 |   D11 |   D12 |   D13 |   D14 |   D15 |   D16 |   D17 |   D18 |   D19 |
- -------------------------------------------------------------------------------  
|   PB2 |   PB3 |   PB4 |   PB5 |   PC0 |   PC1 |   PC2 |   PC3 |   PC4 |   PC5 |
---------------------------------------------------------------------------------

-------------------------
|   D20 |   D21 |   D22 |
- -----------------------
|   PB6 |   PB7 |   PC6 |
-------------------------
*/
    if (this->PortNumber == PortB)
    {
        if      (this->PinNumber == 0) this->ArduionPinNumber = 8;
        else if (this->PinNumber == 1) this->ArduionPinNumber = 9;
        else if (this->PinNumber == 2) this->ArduionPinNumber = 10;
        else if (this->PinNumber == 3) this->ArduionPinNumber = 11;
        else if (this->PinNumber == 4) this->ArduionPinNumber = 12;
        else if (this->PinNumber == 5) this->ArduionPinNumber = 13;
        else if (this->PinNumber == 6) this->ArduionPinNumber = 20;
        else if (this->PinNumber == 7) this->ArduionPinNumber = 21;
    }
    else if (this->PortNumber == PortC)
    {
        if      (this->PinNumber == 0) this->ArduionPinNumber = 14;
        else if (this->PinNumber == 1) this->ArduionPinNumber = 15;
        else if (this->PinNumber == 2) this->ArduionPinNumber = 16;
        else if (this->PinNumber == 3) this->ArduionPinNumber = 17;
        else if (this->PinNumber == 4) this->ArduionPinNumber = 18;
        else if (this->PinNumber == 5) this->ArduionPinNumber = 19;
        else if (this->PinNumber == 6) this->ArduionPinNumber = 22;        
    }
    else if (this->PortNumber == PortD)
    {
        if      (this->PinNumber == 0) this->ArduionPinNumber = 0;
        else if (this->PinNumber == 1) this->ArduionPinNumber = 1;
        else if (this->PinNumber == 2) this->ArduionPinNumber = 2;
        else if (this->PinNumber == 3) this->ArduionPinNumber = 3;
        else if (this->PinNumber == 4) this->ArduionPinNumber = 4;
        else if (this->PinNumber == 5) this->ArduionPinNumber = 5;
        else if (this->PinNumber == 6) this->ArduionPinNumber = 6;   
        else if (this->PinNumber == 7) this->ArduionPinNumber = 7;      
    }

    if (this->Dircetion == Output)
    {
        //引脚方向为输出
        pinMode(this->ArduionPinNumber, OUTPUT);
        digitalWrite(this->ArduionPinNumber, this->Level);
    }
    else
    {
        //引脚方向为输入
        if (this->Resistor == no_pull)
        {
            //无上拉电阻
            pinMode(this->ArduionPinNumber, INPUT);
        }
        else if (this->Resistor == pull_up)
        {
            //上拉电阻
            pinMode(this->ArduionPinNumber, INPUT_PULLUP);
        }
        else
        {
            //下拉电阻，AVR不支持
        }   
    }   
}

void CIO::Set_0(void)
{
    digitalWrite(this->ArduionPinNumber, LOW);
}

void CIO::Set_1(void)
{
    digitalWrite(this->ArduionPinNumber, HIGH);
}

void CIO::Set_I(void)
{
    if (digitalRead(this->ArduionPinNumber) == HIGH)
    {
        this->Set_0();
    }
    else
    {
        this->Set_1();
    }
    
}

CIO_Output::CIO_Output(io_port PortNumber, io_pin PinNumber, io_level Level):CIO(PortNumber, PinNumber, Output, Level, no_pull) {}

CIO_Output_OST::CIO_Output_OST(io_port PortNumber, io_pin PinNumber, io_level Level):CIO_Output(PortNumber, PinNumber, Level) {}

void CIO_Output_OST::Open(void)
{
    if (this->Level == Low)
    {
        this->Set_1();
    }
    else
    {
        this->Set_0();
    }    
}

void CIO_Output_OST::Shut(void)
{
    if (this->Level == Low)
    {
        this->Set_0();
    }
    else
    {
        this->Set_1();
    }   
}

void CIO_Output_OST::Turn(void)
{
    this->Set_I();
}

CIO_Output_OST_Low::CIO_Output_OST_Low(io_port PortNumber, io_pin PinNumber):CIO_Output_OST(PortNumber, PinNumber, Low) {}
	
CIO_Output_OST_High::CIO_Output_OST_High(io_port PortNumber, io_pin PinNumber):CIO_Output_OST(PortNumber, PinNumber, High) {}
