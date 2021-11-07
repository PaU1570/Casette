#ifndef CLASSES_H
#define CLASSES_H

#include <arduino.h>

#define signed_byte int8_t // equivalent to 'char' but more clear

class A_Button
{
public:
	// pin should be an analog pin
	A_Button(byte pin) : m_pin(pin)
	{
		pinMode(m_pin, INPUT);
	}

	byte whichPressed() const;

private:
	const byte m_pin;
};

class B_Button
{
public:
	// pins should be analog pins
	B_Button(byte pin1, byte pin2) : m_pin1(pin1), m_pin2(pin2)
	{
		pinMode(m_pin1, INPUT);
		pinMode(m_pin2, INPUT);
	}

	byte whichPressed() const;

private:
	const byte m_pin1;
	const byte m_pin2;
};

class C_Button
{
public:
	// pin should be an analog pin
	C_Button(byte pin) : m_pin(pin)
	{
		pinMode(m_pin, INPUT);
	}

	byte whichPressed() const;
	
private:
	const byte m_pin;
};

class Volume_Knob
{
public:
	// pin should be analog pin
	Volume_Knob(byte pin) : m_pin(pin)
	{
		pinMode(m_pin, INPUT);
	}

	byte volLevel() const;

private:
	const byte m_pin;
	byte m_voltage_to_volume(int) const;
	const int m_volumeLookup[11][2] = {
	  {0, 0},
	  {10, 7},
	  {20, 16},
	  {30, 38},
	  {40, 105},
	  {50, 170},
	  {60, 240},
	  {70, 350},
	  {80, 700},
	  {90, 900},
	  {100, 1020}
	  };
	
};

#endif // CLASSES_H