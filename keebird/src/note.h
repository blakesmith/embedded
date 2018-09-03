#ifndef KEEBIRD_NOTE_H_
#define KEEBIRD_NOTE_H_

#include <sstream>
#include <string>

struct Note {
    const char* note;
    const unsigned int note_number;
    const unsigned int octave;
    const double frequency;
    
    const std::string ToString() const {
        std::stringstream stream;
        stream << note << octave << ": " << frequency;
        return stream.str();
    }

    static const Note* ByIndex(size_t index);
};

#endif
