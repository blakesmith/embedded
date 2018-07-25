#include "layout.h"

Layer::Key Layout::MapKey(uint8_t current_layer, uint16_t key_position, uint16_t key_count) {
    for (uint8_t i = current_layer; i >= 0; i--) {
        Layer layer = this->layers[i];
        Layer::Key key = layer.keys[key_position];
        if (key != KEY_NONE) {
            return key;
        }
    }

    return KEY_NONE;
}

const Layer::Key TEST_NUMBER_KEYS[] = {
    KEY_1, KEY_2,
    KEY_3, KEY_NONE,
};

const Layer::Key TEST_LAYER_KEYS[] = {
    KEY_A, KEY_B,
    KEY_LEFTSHIFT, LYR_SHIFT(1)
};

const Layer TEST_LAYER = {
    .keys = TEST_LAYER_KEYS,
    .key_count = sizeof(TEST_LAYER_KEYS) / sizeof(Layer::Key)
};

const Layer TEST_NUMBER_LAYER = {
    .keys = TEST_NUMBER_KEYS,
    .key_count = sizeof(TEST_NUMBER_KEYS) / sizeof(Layer::Key)
};

const Layer TEST_LAYERS[] = {
    TEST_LAYER,
    TEST_NUMBER_LAYER,
};

const Layout TEST_LAYOUT = {
    .layers = TEST_LAYERS,
    .layer_count = sizeof(TEST_LAYERS) / sizeof(Layer)
};

const Layer::Key TEST_LAYER_KEYS_2[] = {
    KEY_E, KEY_F,
    KEY_G, KEY_H
};

const Layer TEST_LAYER_2 = {
    .keys = TEST_LAYER_KEYS_2,
    .key_count = sizeof(TEST_LAYER_KEYS_2) / sizeof(Layer::Key)
};

const Layer TEST_LAYERS_2[] = {
    TEST_LAYER_2,
    TEST_NUMBER_LAYER,
};

const Layout TEST_LAYOUT_2 = {
    .layers = TEST_LAYERS_2,
    .layer_count = sizeof(TEST_LAYERS_2) / sizeof(Layer)
};

const Layer::Key FUNCTION_LAYER_KEYS[] = {
    KEY_GRAVE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_DELETE,
    KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE,
    KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE,
    KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE,
    KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE,
};

const Layer::Key DVORAK_LAYER_KEYS[] = {
    KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_BACKSPACE,
    KEY_TAB, KEY_APOSTROPHE, KEY_COMMA, KEY_DOT, KEY_P, KEY_Y, KEY_F, KEY_G, KEY_C, KEY_R, KEY_L, KEY_SLASH, KEY_EQUAL, KEY_BACKSLASH,
    KEY_LEFTCTRL, KEY_A, KEY_O, KEY_E, KEY_U, KEY_I, KEY_D, KEY_H, KEY_T, KEY_N, KEY_S, KEY_MINUS, KEY_ENTER, KEY_NONE,
    KEY_LEFTSHIFT, KEY_SEMICOLON, KEY_Q, KEY_J, KEY_K, KEY_X, KEY_B, KEY_M, KEY_W, KEY_V, KEY_Z, KEY_RIGHTSHIFT, KEY_UP, KEY_NONE,
    KEY_LEFTCTRL, KEY_LEFTMETA, KEY_LEFTALT, KEY_NONE, KEY_NONE, KEY_NONE, KEY_SPACE, KEY_NONE, KEY_RIGHTALT, KEY_NONE, KEY_NONE, KEY_LEFT, KEY_DOWN, KEY_RIGHT
};

const Layer FUNCTION_LAYER = {
    .keys = FUNCTION_LAYER_KEYS,
    .key_count = sizeof(FUNCTION_LAYER_KEYS) / sizeof(Layer::Key)
};

const Layer DVORAK_LAYER = {
    .keys = DVORAK_LAYER_KEYS,
    .key_count = sizeof(DVORAK_LAYER_KEYS) / sizeof(Layer::Key)
};

const Layer DVORAK_LAYERS[] = {
    DVORAK_LAYER,
    FUNCTION_LAYER,
};

const Layout DVORAK_LAYOUT = {
    .layers = DVORAK_LAYERS,
    .layer_count = sizeof(DVORAK_LAYERS) / sizeof(Layer)
};

const Layout DEFAULT_LAYOUT = TEST_LAYOUT;

const Layout LAYOUTS[] = {
    TEST_LAYOUT,
    TEST_LAYOUT_2
};
