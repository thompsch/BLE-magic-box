#include <bluefruit.h>
#include <Arduino.h>
#include "RotaryEncoder.h"
#include "magicbuttons.cpp"

// *********** PINS **************** //

SwRotaryEncoder swEncoder;
#define MUTE_PIN 9
#define SWITCH_PIN 11
#define BTN_GREEN A1
#define BTN_BLACK A3
#define BTN_RED A5 
#define BTN_WHITE A0
#define BTN_YELLOW A2
#define BTN_BLUE A4
#define ROTARY_A 7
#define ROTARY_B 10

uint8_t REcode[6] = {HID_KEY_V};

int pins[6] = {BTN_GREEN, BTN_BLACK, BTN_RED, BTN_WHITE, BTN_YELLOW, BTN_BLUE};
boolean muted = false;
bool bank = false;
bool wasKeyPressed = false;
int lastRE;

// ************* BLE ***************** //
BLEDis bledis;
BLEHidAdafruit blehid;

// ************ SETUP **************** //

void setup()
{
  Serial.begin(115200);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(MUTE_PIN, INPUT_PULLUP);
  for (int x = 0; x < 6; x++)
  {
    pinMode(pins[x], INPUT_PULLUP);
  }

  while (!Serial)
    delay(10); // for nrf52840 with native usb

  RotaryEncoder.begin(ROTARY_A, ROTARY_B);

  // Start encoder
  RotaryEncoder.start();
  lastRE = millis();

  //swEncoder.begin(ROTARY_A, ROTARY_B);
  //swEncoder.setCallback(encoder_callback);
  
  Bluefruit.begin();
  Bluefruit.setTxPower(0); // { -40, -20, -16, -12, -8, -4, 0, 2, 3, 4, 5, 6, 7, 8 }

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather 52x");
  bledis.begin();
  blehid.begin();
  Bluefruit.Periph.setConnInterval(9, 25);
  startAdv();
}

void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);

  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();

  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);   // number of seconds in fast mode
  Bluefruit.Advertising.start(0);             // 0 = Don't stop advertising after n seconds
}

void loop()
{
  checkRE();

  if ( wasKeyPressed )
  {
    wasKeyPressed = false;
    blehid.keyRelease();
    delay(5);
  }

  /* MUTE */
  if (digitalRead(MUTE_PIN) == LOW)
  {
    //Serial.println(String(muted));
    uint8_t keycode[6] = {HID_KEY_M};
    if (muted)
      blehid.keyboardReport(shift, keycode);
    else
      blehid.keyboardReport(noshift, keycode);
    muted = !muted;
    delay(300);
    blehid.keyRelease();
  }

  /* BUTTONS */
  for (int i = 0; i < 6; i++)
  {
    if (digitalRead(pins[i]) == LOW)
    {
      wasKeyPressed = true;
      /*Serial.print("button: ");
      Serial.print(String(i));
      Serial.print("; bank: ");
      Serial.println(String(bank));*/
      
      if (digitalRead(SWITCH_PIN) == LOW) bank = 0;
      else bank = 1;
      magicButton btn = magicButtons[i + i + bank];
      //Serial.println(btn.name);
      blehid.keyboardReport(btn.modifier, btn.keycode);
      delay(300);
    }
  }
}

/* VOLUME */
void checkRE(){

  int value = RotaryEncoder.read();

  if (value && ((millis() - lastRE) > 100))
  {
    if ( value > 0 )
    {
      blehid.keyboardReport(noshift, REcode);
      //Serial.println("LEFT");
    } 
    else
    {
      blehid.keyboardReport(shift, REcode);
      //Serial.println("RIGHT");
    }
      lastRE = millis();
      blehid.keyRelease();
  }

}
