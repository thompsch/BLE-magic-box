#include "Arduino.h"
#include <bluefruit.h>


const int shift = KEYBOARD_MODIFIER_LEFTCTRL+KEYBOARD_MODIFIER_LEFTALT+KEYBOARD_MODIFIER_LEFTGUI+KEYBOARD_MODIFIER_LEFTSHIFT;

const int noshift = KEYBOARD_MODIFIER_LEFTCTRL+KEYBOARD_MODIFIER_LEFTALT+KEYBOARD_MODIFIER_LEFTGUI;

typedef struct
{
    String name;
    int modifier;
    uint8_t keycode[6];
} magicButton;

//int pins[6] = {BTN_GREEN,BTN_BLACK,BTN_RED,BTN_WHITE,BTN_YELLOW,BTN_BLUE };
const magicButton magicButtons[12]{
    {
      "green A",// = zoom
      noshift,
      HID_KEY_1
    },
    {
      "green B",//= standup
      shift,
      HID_KEY_1
    },
    {
      "black A ",//= mic on/off
      noshift,
      HID_KEY_2
    },
    {
      "black B",// = my zoom
      shift,
      HID_KEY_2
    },
    {
      "red A",//= video on/off
      noshift,
      HID_KEY_3
    },
    {
      "red B",// = null
      shift,
      HID_KEY_3
    },
    {
      "white A",// = play/pause
      noshift,
      HID_KEY_4
    },
    {
      "white B",//= shrug
      shift,
      HID_KEY_4
    },
    {
      "yellow A",// = REW
      noshift,
      HID_KEY_5
    },
    {
      "yellow B",// = @
      shift,
      HID_KEY_5
    },
    {
      "blue A",// = FF
      noshift,
      HID_KEY_6
    },
    {
      "blue B",// = null
      shift,
      HID_KEY_6
    }
};

