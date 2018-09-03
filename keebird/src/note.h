#ifndef KEEBIRD_NOTE_H_
#define KEEBIRD_NOTE_H_

#include <cstddef>

struct Note {
    const char* note;
    const unsigned int note_number;
    const unsigned int octave;
    const double frequency;
    
    static const Note* ByIndex(size_t index);
    static const Note* ByNumberAndOctave(unsigned int note_number,
                                         unsigned int octave);
    static const Note* ByNoteNameAndOctave(const char* note_name,
                                           unsigned int octave);
};

#endif
