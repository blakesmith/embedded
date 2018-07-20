#include "layout.h"

const Layout::Key TEST_LAYOUT_KEYS[] = {
    LAYOUT_KEY_A, LAYOUT_KEY_B,
    LAYOUT_KEY_C, LAYOUT_KEY_D
};

const Layout DEFAULT_LAYOUT = {
    .keys = TEST_LAYOUT_KEYS,
    .key_count = 4
};
