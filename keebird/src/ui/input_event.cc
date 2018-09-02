#include "input_event.h"

namespace keebird {

InputEvent::InputEvent(InputEventType type)
    : type_(type)
{ }

InputEventType InputEvent::get_type() const {
    return type_;
}

}
