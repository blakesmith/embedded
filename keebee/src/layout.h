#ifndef KEEBEE_LAYOUT_H_
#define KEEBEE_LAYOUT_H_

#include "stdint.h"

struct Layout {
    using Key = uint8_t;

    const Key* keys;
    const uint16_t key_count;
};

const Layout::Key LAYOUT_KEY_A = 0x04;
const Layout::Key LAYOUT_KEY_B = 0x05;
const Layout::Key LAYOUT_KEY_C = 0x06;
const Layout::Key LAYOUT_KEY_D = 0x07;

extern const Layout DEFAULT_LAYOUT;

#endif
