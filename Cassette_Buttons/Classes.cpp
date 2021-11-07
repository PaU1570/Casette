#include "Classes.h"

// Thresholds for buttons in ascending order
#define AB_OFF_THRESHOLD 100
#define A_FASTFORWARD_THRESHOLD 460
#define A_REWIND_THRESHOLD 500
#define A_STOP_THRESHOLD 600
#define A_BACK_THRESHOLD 820
#define A_FORWARD_THRESHOLD 1024

#define B_RECMUTE_THRESHOLD 700
#define B_REC_THRESHOLD 700
#define B_FASTFORWARD_THRESHOLD 820
#define B_BACK_THRESHOLD 820
#define B_FORWARD_THRESHOLD 950
#define B_REWIND_THRESHOLD 950
#define B_PAUSE_THRESHOLD 1024
#define B_STOP_THRESHOLD 1024

#define C_OFF_THRESHOLD 20
#define C_SKIP_THRESHOLD 150
#define C_HIGHSPEED_THRESHOLD 320
#define C_NORMALSPEED_THRESHOLD 500
#define C_AUTOPAUSE_THRESHOLD 1023

/****************************************************************/
/*						A BUTTON																					*/
/****************************************************************/
// 0: No button pressed
// 1: Rewind
// 2: Stop
// 3: Back
// 4: Forward
// 5: Fast Forward

byte A_Button::whichPressed() const
{
	int vout = analogRead(m_pin);

	if (vout <= AB_OFF_THRESHOLD)
		return 0;
	if (vout <= A_FASTFORWARD_THRESHOLD)
		return 5;
	if (vout <= A_REWIND_THRESHOLD)
		return 1;
	if (vout <= A_STOP_THRESHOLD)
		return 2;
	if (vout <= A_BACK_THRESHOLD)
		return 3;
	return 4;
}

/****************************************************************/
/*						B BUTTON																					*/
/****************************************************************/
// 0: No button pressed
// 1: Rewind
// 2: Stop
// 3: Back
// 4: Forward
// 5: Fast Forward
// 6: REC
// 7: Pause
// 8: REC Mute

byte B_Button::whichPressed() const
{
	int vout1 = analogRead(m_pin1);
	int vout2 = analogRead(m_pin2);

	// Both off
	if ((vout1 <= AB_OFF_THRESHOLD) && (vout2 <= AB_OFF_THRESHOLD))
		return 0;
	// Side 1
	if ((vout1 <= B_RECMUTE_THRESHOLD) && (vout2 <= AB_OFF_THRESHOLD))
		return 8;
	if ((vout1 <= B_BACK_THRESHOLD) && (vout2 <= AB_OFF_THRESHOLD))
		return 3;
	if ((vout1 <= B_FORWARD_THRESHOLD) && (vout2 <= AB_OFF_THRESHOLD))
		return 4;
	if ((vout1 <= B_PAUSE_THRESHOLD) && (vout2 <= AB_OFF_THRESHOLD))
		return 7;
	// Side 2
	if ((vout1 <= AB_OFF_THRESHOLD) && (vout2 <= B_REC_THRESHOLD))
		return 6;
	if ((vout1 <= AB_OFF_THRESHOLD) && (vout2 <= B_FASTFORWARD_THRESHOLD))
		return 5;
	if ((vout1 <= AB_OFF_THRESHOLD) && (vout2 <= B_REWIND_THRESHOLD))
		return 1;
	if ((vout1 <= AB_OFF_THRESHOLD) && (vout2 <= B_STOP_THRESHOLD))
		return 2;

	return -1; // Should never happen
}

/****************************************************************/
/*						C BUTTON																					*/
/****************************************************************/
// 0: No button pressed
// 1: Skip
// 2: High Speed
// 3: Normal Speed
// 4: Auto Pause

byte C_Button::whichPressed() const
{
	int vout = analogRead(m_pin);

	if (vout <= C_OFF_THRESHOLD)
		return 0;
	if (vout <= C_SKIP_THRESHOLD)
		return 1;
	if (vout <= C_HIGHSPEED_THRESHOLD)
		return 2;
	if (vout <= C_NORMALSPEED_THRESHOLD)
		return 3;

	return 4;

}

/****************************************************************/
/*						VOLUME KNOB																				*/
/****************************************************************/

byte Volume_Knob::m_voltage_to_volume(int vin) const
{
  byte index = 0;
  while (vin > m_volumeLookup[index][1] && index < 11)
  {
    index++;
  }
  if (index == 0)
    return 0;
  
  return map(vin, m_volumeLookup[index - 1][1], m_volumeLookup[index][1], m_volumeLookup[index - 1][0], m_volumeLookup[index][0]);
}

byte Volume_Knob::volLevel() const
{
	int vout = analogRead(m_pin);
	return m_voltage_to_volume(vout);
}
