// Sony Casette Buttons
// Paul Uriarte Vicandi
// 8 August 2021
// Last updated: 8 August 2021

#include "Classes.h"
#include "EventHandler.h"

#define DECK_A_BUTTONS A0
#define DECK_B_BUTTONS_1 A1
#define DECK_B_BUTTONS_2 A2
#define REC_LEVEL A3
#define CENTER_BUTTONS A4
//#define BALANCE_L A4
//#define BALANCE_R A5

#define DEBOUNCE_TIME 50 // minimum time a button has to be pressed for it to register as a click (in milliseconds)
#define BUTTON_TIMEOUT 5000 // maximum time a button can stay pressed before giving up

// Listeners
bool A_ClickListener(); // Always returns false
bool A_RewindListener();
bool A_FastForwardListener();
bool A_StopListener();
bool A_BackListener();
bool A_ForwardListener();

bool B_ClickListener(); // Always returns false
bool B_RewindListener();
bool B_FastForwardListener();
bool B_StopListener();
bool B_BackListener();
bool B_ForwardListener();
bool B_RecListener();
bool B_PauseListener();
bool B_RecMuteListener();

bool C_ClickListener(); // ALways returns false
bool SkipListener();
bool SpeedHighListener();
bool SpeedNormalListener();
bool AutoPauseListener();

bool RecLevelListener();
bool BalanceLeftListener();
bool BalanceRightListener();

bool DirModeStraightListener();
bool DirModeLoopListener();
bool DirModeRelayListener();
bool DolbyOffListener();
bool DolbyBListener();
bool DolbyCListener();
bool Tape1Listener();
bool Tape2Listener();
bool Tape3Listener();

// Callback functions
void on_A_Click() {} // Never called
void on_A_Rewind();
void on_A_FastForward();
void on_A_Stop();
void on_A_Back();
void on_A_Forward();

void on_B_Click() {} // Never called
void on_B_Rewind();
void on_B_FastForward();
void on_B_Stop();
void on_B_Back();
void on_B_Forward();
void on_B_Rec();
void on_B_Pause();
void on_B_RecMute();

void on_C_Click() {} // Never called
void onSkip();
void onSpeedHigh();
void onSpeedNormal();
void onAutoPause();

void onRecLevel();
void onBalanceLeft();
void onBalanceRight();

void onDirModeStraight();
void onDirModeLoop();
void onDirModeRelay();
void onDolbyOff();
void onDolbyB();
void onDolbyC();
void onTape1();
void onTape2();
void onTape3();

// Create buttons
A_Button Deck_A_Buttons(DECK_A_BUTTONS);
B_Button Deck_B_Buttons(DECK_B_BUTTONS_1, DECK_B_BUTTONS_2);
C_Button Center_Buttons(CENTER_BUTTONS);

Volume_Knob Volume(REC_LEVEL);

EventHandler eventHdl;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up...");

  eventHdl.addListener(&A_ClickListener, &on_A_Click); // This has to be added before the other A listeners
  eventHdl.addListener(&A_RewindListener, &on_A_Rewind);
  eventHdl.addListener(&A_StopListener, &on_A_Stop);
  eventHdl.addListener(&A_BackListener, &on_A_Back);
  eventHdl.addListener(&A_ForwardListener, &on_A_Forward);
  eventHdl.addListener(&A_FastForwardListener, &on_A_FastForward);

  eventHdl.addListener(&B_ClickListener, &on_B_Click); // This has to be added before the other B listeners
  eventHdl.addListener(&B_RewindListener, &on_B_Rewind);
  eventHdl.addListener(&B_StopListener, &on_B_Stop);
  eventHdl.addListener(&B_BackListener, &on_B_Back);
  eventHdl.addListener(&B_ForwardListener, &on_B_Forward);
  eventHdl.addListener(&B_FastForwardListener, &on_B_FastForward);
  eventHdl.addListener(&B_RecListener, &on_B_Rec);
  eventHdl.addListener(&B_PauseListener, &on_B_Pause);
  eventHdl.addListener(&B_RecMuteListener, &on_B_RecMute);

  eventHdl.addListener(&C_ClickListener, &on_C_Click); // This has to be added before the other C listeners
  eventHdl.addListener(&SkipListener, &onSkip);
  eventHdl.addListener(&SpeedHighListener, &onSpeedHigh);
  eventHdl.addListener(&SpeedNormalListener, &onSpeedNormal);
  eventHdl.addListener(&AutoPauseListener, &onAutoPause);

  eventHdl.addListener(&RecLevelListener, &onRecLevel);

  Serial.println("Started!");

  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void loop()
{
  eventHdl.listen();
  eventHdl.processEvent();
}

// ************************** //

/****************************************************************/
/*            LISTENERS                                         */
/****************************************************************/

bool A_ClickArray[] = {false, false, false, false, false}; // {rewind, stop, back, forward, fast forward}
bool A_ClickListener() // Always returns false
{
  // determine if button was clicked, and if so, which button.
  byte buttonNum = Deck_A_Buttons.whichPressed();
  if (buttonNum == 0)
    return false;

  // if a button is pressed, measure for how long it stays pressed
  unsigned long initial_time = millis();
  while ((Deck_A_Buttons.whichPressed() == buttonNum) && (millis() - initial_time <= BUTTON_TIMEOUT))
  {}
  unsigned long click_duration = millis() - initial_time;

  if ((click_duration >= DEBOUNCE_TIME) && (click_duration != BUTTON_TIMEOUT))
    A_ClickArray[buttonNum - 1] = true;

  return false;
}

bool A_RewindListener()
{
  if (A_ClickArray[0])
  {
    A_ClickArray[0] = false;
    return true;
  }
  return false;
}

bool A_StopListener()
{
  if (A_ClickArray[1])
  {
    A_ClickArray[1] = false;
    return true;
  }
  return false;
}

bool A_BackListener()
{
  if (A_ClickArray[2])
  {
    A_ClickArray[2] = false;
    return true;
  }
  return false;
}

bool A_ForwardListener()
{
  if (A_ClickArray[3])
  {
    A_ClickArray[3] = false;
    return true;
  }
  return false;
}

bool A_FastForwardListener()
{
  if (A_ClickArray[4])
  {
    A_ClickArray[4] = false;
    return true;
  }
  return false;
}

bool B_ClickArray[] = {false, false, false, false, false, false, false, false}; // {rewind, stop, back, forward, fast forward, rec, pause, rec mute}
bool B_ClickListener() // Always returns false
{
  // determine if button was clicked, and if so, which button.
  byte buttonNum = Deck_B_Buttons.whichPressed();
  if (buttonNum == 0)
    return false;

  // if a button is pressed, measure for how long it stays pressed
  unsigned long initial_time = millis();
  while ((Deck_B_Buttons.whichPressed() == buttonNum) && (millis() - initial_time <= BUTTON_TIMEOUT))
  {}
  unsigned long click_duration = millis() - initial_time;

  if ((click_duration >= DEBOUNCE_TIME) && (click_duration != BUTTON_TIMEOUT))
    B_ClickArray[buttonNum - 1] = true;

  return false;
}

bool B_RewindListener()
{
  if (B_ClickArray[0])
  {
    B_ClickArray[0] = false;
    return true;
  }
  return false;
}

bool B_StopListener()
{
  if (B_ClickArray[1])
  {
    B_ClickArray[1] = false;
    return true;
  }
  return false;
}

bool B_BackListener()
{
  if (B_ClickArray[2])
  {
    B_ClickArray[2] = false;
    return true;
  }
  return false;
}

bool B_ForwardListener()
{
  if (B_ClickArray[3])
  {
    B_ClickArray[3] = false;
    return true;
  }
  return false;
}

bool B_FastForwardListener()
{
  if (B_ClickArray[4])
  {
    B_ClickArray[4] = false;
    return true;
  }
  return false;
}

bool B_RecListener()
{
  if (B_ClickArray[5])
  {
    B_ClickArray[5] = false;
    return true;
  }
  return false;
}

bool B_PauseListener()
{
  if (B_ClickArray[6])
  {
    B_ClickArray[6] = false;
    return true;
  }
  return false;
}

bool B_RecMuteListener()
{
  if (B_ClickArray[7])
  {
    B_ClickArray[7] = false;
    return true;
  }
  return false;
}

bool C_ClickArray[] = {false, false, false, false}; // {skip, speed high, speed normal, auto pause}
bool C_ClickListener()
{
  // determine if button was clicked, and if so, which button.
  byte buttonNum = Center_Buttons.whichPressed();
  if (buttonNum == 0)
    return false;

  // if a button is pressed, measure for how long it stays pressed
  unsigned long initial_time = millis();
  while ((Center_Buttons.whichPressed() == buttonNum) && (millis() - initial_time <= BUTTON_TIMEOUT))
  {}
  unsigned long click_duration = millis() - initial_time;

  if ((click_duration >= DEBOUNCE_TIME) && (click_duration != BUTTON_TIMEOUT))
    C_ClickArray[buttonNum - 1] = true;

  return false;
}

bool SkipListener()
{
  if (C_ClickArray[0])
  {
    C_ClickArray[0] = false;
    return true;
  }
  return false;
}

bool SpeedHighListener()
{
  if (C_ClickArray[1])
  {
    C_ClickArray[1] = false;
    return true;
  }
  return false;
}

bool SpeedNormalListener()
{
  if (C_ClickArray[2])
  {
    C_ClickArray[2] = false;
    return true;
  }
  return false;
}

bool AutoPauseListener()
{
  if (C_ClickArray[3])
  {
    C_ClickArray[3] = false;
    return true;
  }
  return false;
}

byte current_volume = Volume.volLevel();
byte new_volume = Volume.volLevel();
bool RecLevelListener()
{
  byte tmp = Volume.volLevel();
  if ((current_volume < 20 and abs(tmp - current_volume) >= 3) or (current_volume >=20 and abs(tmp - current_volume) >= 2) or tmp == 0 or tmp == 100)
  {
    new_volume = tmp;
    return true;
  }
  return false;
}

/****************************************************************/
/*            CALLBACK FUNCTIONS                                */
/****************************************************************/
void on_A_Rewind()
{
  Serial.println("Deck A Rewind");
}

void on_A_Stop()
{
  Serial.println("Deck A Stop");
}

void on_A_Back()
{
  Serial.println("Deck A Back");
}

void on_A_Forward()
{
  Serial.println("Deck A Forward");
}

void on_A_FastForward()
{
  Serial.println("Deck A Fast Forward");
}



void on_B_Rewind()
{
  Serial.println("Deck B Rewind");
}

void on_B_Stop()
{
  Serial.println("Deck B Stop");
}

void on_B_Back()
{
  Serial.println("Deck B Back");
}

void on_B_Forward()
{
  Serial.println("Deck B Forward");
}

void on_B_FastForward()
{
  Serial.println("Deck B Fast Forward");
}

void on_B_Rec()
{
  Serial.println("Deck B REC");
}

void on_B_Pause()
{
  Serial.println("Deck B Pause");
}

void on_B_RecMute()
{
  Serial.println("Deck B REC Mute");
}



void onSkip()
{
  Serial.println("Center Skip");
}

void onSpeedHigh()
{
  Serial.println("Center Speed High");
}

void onSpeedNormal()
{
    Serial.println("Center Speed Normal");
}

void onAutoPause()
{
  Serial.println("Center Auto Pause");
}



void onRecLevel()
{
  signed_byte diff = new_volume - current_volume;

  if (diff > 0)
  {
    for (byte i = 0; i < abs(diff); i++)
    {
      current_volume++;
      Serial.print("Volume: ");
      Serial.println(current_volume);
    }
  }
  else if (diff < 0)
  {
    for (byte i = 0; i < abs(diff); i++)
    {
      current_volume--;
      Serial.print("Volume: ");
      Serial.println(current_volume);
    }
  }
}



