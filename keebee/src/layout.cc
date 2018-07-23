#include "layout.h"

Layer::Key Layout::MapKey(uint16_t key_position, uint16_t key_count) {
    // TODO: Actual layer traversal
    return this->layers[0].keys[key_position];
}

const Layer::Key TEST_LAYER_KEYS[] = {
    KEY_A, KEY_B,
    KEY_C, KEY_D
};

const Layer::Key DVORAK_LAYER_KEYS[] = {
    KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSPACE,
    KEY_TAB, KEY_APOSTROPHE, KEY_COMMA, KEY_DOT, KEY_P, KEY_Y, KEY_F, KEY_G, KEY_C, KEY_R, KEY_L, KEY_SLASH, KEY_EQUAL, KEY_BACKSLASH,
    KEY_LEFTCTRL, KEY_A, KEY_O, KEY_E, KEY_U, KEY_I, KEY_D, KEY_H, KEY_T, KEY_N, KEY_S, KEY_MINUS, KEY_ENTER, KEY_NONE,
    KEY_LEFTSHIFT, KEY_SEMICOLON, KEY_Q, KEY_J, KEY_K, KEY_X, KEY_B, KEY_M, KEY_W, KEY_V, KEY_Z, KEY_RIGHTSHIFT, KEY_UP, KEY_NONE,
    KEY_LEFTCTRL, KEY_LEFTMETA, KEY_LEFTALT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_SPACE, KEY_NONE, KEY_RIGHTALT, KEY_NONE, KEY_NONE, KEY_LEFT, KEY_DOWN, KEY_RIGHT
};

const Layer TEST_LAYER = {
    .keys = TEST_LAYER_KEYS,
    .key_count = sizeof(TEST_LAYER_KEYS) / sizeof(Layer::Key)
};

const Layer DVORAK_LAYER = {
    .keys = DVORAK_LAYER_KEYS,
    .key_count = sizeof(DVORAK_LAYER_KEYS) / sizeof(Layer::Key)
};

const Layer DEFAULT_LAYERS[] = {
    TEST_LAYER
};

const Layout DEFAULT_LAYOUT = {
    .layers = DEFAULT_LAYERS,
    .layer_count = 1
};
