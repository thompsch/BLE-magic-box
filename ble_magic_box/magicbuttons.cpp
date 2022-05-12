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

const magicButton magicButtons[12]{
    {
      "green A",
      noshift,
      HID_KEY_1
    },
    {
      "green B",
      shift,
      HID_KEY_1
    },
    {
      "black A",
      noshift,
      HID_KEY_2
    },
    {
      "black B",
      shift,
      HID_KEY_2
    },
    {
      "red A",
      noshift,
      HID_KEY_3
    },
    {
      "red B",
      shift,
      HID_KEY_3
    },
    {
      "white A",
      noshift,
      HID_KEY_4
    },
    {
      "white B",
      shift,
      HID_KEY_4
    },
    {
      "yellow A",
      noshift,
      HID_KEY_5
    },
    {
      "yellow B",
      shift,
      HID_KEY_5
    },
    {
      "blue A",
      noshift,
      HID_KEY_6
    },
    {
      "blue B",
      shift,
      HID_KEY_6
    }
};

