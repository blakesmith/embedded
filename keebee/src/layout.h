#ifndef KEEBEE_LAYOUT_H_
#define KEEBEE_LAYOUT_H_

#include "stdint.h"

struct Layer {
    using Key = uint8_t;

    const Key* keys;
    const uint16_t key_count;
};

struct Layout {
    const Layer* layers;
    const uint8_t layer_count;

    uint16_t MapKey(uint16_t key_position, uint16_t key_count);
};

const Layer::Key KEY_NONE = 0x00; // No key pressed
const Layer::Key KEY_ERR_OVF = 0x01; //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
const Layer::Key KEY_A = 0x04; // Keyboard a and A
const Layer::Key KEY_B = 0x05; // Keyboard b and B
const Layer::Key KEY_C = 0x06; // Keyboard c and C
const Layer::Key KEY_D = 0x07; // Keyboard d and D
const Layer::Key KEY_E = 0x08; // Keyboard e and E
const Layer::Key KEY_F = 0x09; // Keyboard f and F
const Layer::Key KEY_G = 0x0a; // Keyboard g and G
const Layer::Key KEY_H = 0x0b; // Keyboard h and H
const Layer::Key KEY_I = 0x0c; // Keyboard i and I
const Layer::Key KEY_J = 0x0d; // Keyboard j and J
const Layer::Key KEY_K = 0x0e; // Keyboard k and K
const Layer::Key KEY_L = 0x0f; // Keyboard l and L
const Layer::Key KEY_M = 0x10; // Keyboard m and M
const Layer::Key KEY_N = 0x11; // Keyboard n and N
const Layer::Key KEY_O = 0x12; // Keyboard o and O
const Layer::Key KEY_P = 0x13; // Keyboard p and P
const Layer::Key KEY_Q = 0x14; // Keyboard q and Q
const Layer::Key KEY_R = 0x15; // Keyboard r and R
const Layer::Key KEY_S = 0x16; // Keyboard s and S
const Layer::Key KEY_T = 0x17; // Keyboard t and T
const Layer::Key KEY_U = 0x18; // Keyboard u and U
const Layer::Key KEY_V = 0x19; // Keyboard v and V
const Layer::Key KEY_W = 0x1a; // Keyboard w and W
const Layer::Key KEY_X = 0x1b; // Keyboard x and X
const Layer::Key KEY_Y = 0x1c; // Keyboard y and Y
const Layer::Key KEY_Z = 0x1d; // Keyboard z and Z

const Layer::Key KEY_1 = 0x1e; // Keyboard 1 and !
const Layer::Key KEY_2 = 0x1f; // Keyboard 2 and @
const Layer::Key KEY_3 = 0x20; // Keyboard 3 and #
const Layer::Key KEY_4 = 0x21; // Keyboard 4 and $
const Layer::Key KEY_5 = 0x22; // Keyboard 5 and %
const Layer::Key KEY_6 = 0x23; // Keyboard 6 and ^
const Layer::Key KEY_7 = 0x24; // Keyboard 7 and &
const Layer::Key KEY_8 = 0x25; // Keyboard 8 and *
const Layer::Key KEY_9 = 0x26; // Keyboard 9 and (
const Layer::Key KEY_0 = 0x27; // Keyboard 0 and )

const Layer::Key KEY_ENTER = 0x28; // Keyboard Return (ENTER)
const Layer::Key KEY_ESC = 0x29; // Keyboard ESCAPE
const Layer::Key KEY_BACKSPACE = 0x2a; // Keyboard DELETE (Backspace)
const Layer::Key KEY_TAB = 0x2b; // Keyboard Tab
const Layer::Key KEY_SPACE = 0x2c; // Keyboard Spacebar
const Layer::Key KEY_MINUS = 0x2d; // Keyboard - and _
const Layer::Key KEY_EQUAL = 0x2e; // Keyboard = and +
const Layer::Key KEY_LEFTBRACE = 0x2f; // Keyboard [ and {
const Layer::Key KEY_RIGHTBRACE = 0x30; // Keyboard ] and }
const Layer::Key KEY_BACKSLASH = 0x31; // Keyboard \ and |
const Layer::Key KEY_HASHTILDE = 0x32; // Keyboard Non-US # and ~
const Layer::Key KEY_SEMICOLON = 0x33; // Keyboard ; and :
const Layer::Key KEY_APOSTROPHE = 0x34; // Keyboard ' and "
const Layer::Key KEY_GRAVE = 0x35; // Keyboard ` and ~
const Layer::Key KEY_COMMA = 0x36; // Keyboard , and <
const Layer::Key KEY_DOT = 0x37; // Keyboard . and >
const Layer::Key KEY_SLASH = 0x38; // Keyboard / and ?
const Layer::Key KEY_CAPSLOCK = 0x39; // Keyboard Caps Lock

const Layer::Key KEY_F1 = 0x3a; // Keyboard F1
const Layer::Key KEY_F2 = 0x3b; // Keyboard F2
const Layer::Key KEY_F3 = 0x3c; // Keyboard F3
const Layer::Key KEY_F4 = 0x3d; // Keyboard F4
const Layer::Key KEY_F5 = 0x3e; // Keyboard F5
const Layer::Key KEY_F6 = 0x3f; // Keyboard F6
const Layer::Key KEY_F7 = 0x40; // Keyboard F7
const Layer::Key KEY_F8 = 0x41; // Keyboard F8
const Layer::Key KEY_F9 = 0x42; // Keyboard F9
const Layer::Key KEY_F10 = 0x43; // Keyboard F10
const Layer::Key KEY_F11 = 0x44; // Keyboard F11
const Layer::Key KEY_F12 = 0x45; // Keyboard F12

const Layer::Key KEY_SYSRQ = 0x46; // Keyboard Print Screen
const Layer::Key KEY_SCROLLLOCK = 0x47; // Keyboard Scroll Lock
const Layer::Key KEY_PAUSE = 0x48; // Keyboard Pause
const Layer::Key KEY_INSERT = 0x49; // Keyboard Insert
const Layer::Key KEY_HOME = 0x4a; // Keyboard Home
const Layer::Key KEY_PAGEUP = 0x4b; // Keyboard Page Up
const Layer::Key KEY_DELETE = 0x4c; // Keyboard Delete Forward
const Layer::Key KEY_END = 0x4d; // Keyboard End
const Layer::Key KEY_PAGEDOWN = 0x4e; // Keyboard Page Down
const Layer::Key KEY_RIGHT = 0x4f; // Keyboard Right Arrow
const Layer::Key KEY_LEFT = 0x50; // Keyboard Left Arrow
const Layer::Key KEY_DOWN = 0x51; // Keyboard Down Arrow
const Layer::Key KEY_UP = 0x52; // Keyboard Up Arrow

const Layer::Key KEY_NUMLOCK = 0x53; // Keyboard Num Lock and Clear
const Layer::Key KEY_KPSLASH = 0x54; // Keypad /
const Layer::Key KEY_KPASTERISK = 0x55; // Keypad *
const Layer::Key KEY_KPMINUS = 0x56; // Keypad -
const Layer::Key KEY_KPPLUS = 0x57; // Keypad +
const Layer::Key KEY_KPENTER = 0x58; // Keypad ENTER
const Layer::Key KEY_KP1 = 0x59; // Keypad 1 and End
const Layer::Key KEY_KP2 = 0x5a; // Keypad 2 and Down Arrow
const Layer::Key KEY_KP3 = 0x5b; // Keypad 3 and PageDn
const Layer::Key KEY_KP4 = 0x5c; // Keypad 4 and Left Arrow
const Layer::Key KEY_KP5 = 0x5d; // Keypad 5
const Layer::Key KEY_KP6 = 0x5e; // Keypad 6 and Right Arrow
const Layer::Key KEY_KP7 = 0x5f; // Keypad 7 and Home
const Layer::Key KEY_KP8 = 0x60; // Keypad 8 and Up Arrow
const Layer::Key KEY_KP9 = 0x61; // Keypad 9 and Page Up
const Layer::Key KEY_KP0 = 0x62; // Keypad 0 and Insert
const Layer::Key KEY_KPDOT = 0x63; // Keypad . and Delete

const Layer::Key KEY_102ND = 0x64; // Keyboard Non-US \ and |
const Layer::Key KEY_COMPOSE = 0x65; // Keyboard Application
const Layer::Key KEY_POWER = 0x66; // Keyboard Power
const Layer::Key KEY_KPEQUAL = 0x67; // Keypad =

const Layer::Key KEY_F13 = 0x68; // Keyboard F13
const Layer::Key KEY_F14 = 0x69; // Keyboard F14
const Layer::Key KEY_F15 = 0x6a; // Keyboard F15
const Layer::Key KEY_F16 = 0x6b; // Keyboard F16
const Layer::Key KEY_F17 = 0x6c; // Keyboard F17
const Layer::Key KEY_F18 = 0x6d; // Keyboard F18
const Layer::Key KEY_F19 = 0x6e; // Keyboard F19
const Layer::Key KEY_F20 = 0x6f; // Keyboard F20
const Layer::Key KEY_F21 = 0x70; // Keyboard F21
const Layer::Key KEY_F22 = 0x71; // Keyboard F22
const Layer::Key KEY_F23 = 0x72; // Keyboard F23
const Layer::Key KEY_F24 = 0x73; // Keyboard F24

const Layer::Key KEY_LEFTCTRL = 0xe0; // Keyboard Left Control
const Layer::Key KEY_LEFTSHIFT = 0xe1; // Keyboard Left Shift
const Layer::Key KEY_LEFTALT = 0xe2; // Keyboard Left Alt
const Layer::Key KEY_LEFTMETA = 0xe3; // Keyboard Left GUI
const Layer::Key KEY_RIGHTCTRL = 0xe4; // Keyboard Right Control
const Layer::Key KEY_RIGHTSHIFT = 0xe5; // Keyboard Right Shift
const Layer::Key KEY_RIGHTALT = 0xe6; // Keyboard Right Alt
const Layer::Key KEY_RIGHTMETA = 0xe7; // Keyboard Right GUI

extern const Layout DEFAULT_LAYOUT;

#endif
