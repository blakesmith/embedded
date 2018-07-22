#include "layout.h"

uint16_t Layout::MapKey(uint16_t key_position, uint16_t key_count) {
    // TODO: Actual layer traversal
    return this->layers[0].keys[key_position];
}

const Layer::Key TEST_LAYER_KEYS[] = {
    LK_A, LK_B,
    LK_C, LK_D
};

const Layer TEST_LAYER = {
    .keys = TEST_LAYER_KEYS,
    .key_count = 4
};

const Layer DEFAULT_LAYERS[] = {
    TEST_LAYER
};

const Layout DEFAULT_LAYOUT = {
    .layers = DEFAULT_LAYERS,
    .layer_count = 1
};
