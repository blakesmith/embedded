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

const Layer::Key LK_A = 0x04;
const Layer::Key LK_B = 0x05;
const Layer::Key LK_C = 0x06;
const Layer::Key LK_D = 0x07;

extern const Layout DEFAULT_LAYOUT;

#endif
