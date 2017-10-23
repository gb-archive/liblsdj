#ifndef LSDJ_SONG_H
#define LSDJ_SONG_H

#include "chain.h"
#include "error.h"
#include "groove.h"
#include "instrument.h"
#include "phrase.h"
#include "row.h"
#include "synth.h"
#include "table.h"
#include "vio.h"
#include "wave.h"
#include "word.h"

static const unsigned int SONG_DECOMPRESSED_SIZE = 0x8000;
static const unsigned int ROW_COUNT = 256;
static const unsigned int CHAIN_COUNT = 128;
static const unsigned int PHRASE_COUNT = 0xFF;
static const unsigned int BOOKMARK_COUNT = 64;
static const unsigned int INSTRUMENT_COUNT = 64;
static const unsigned int SYNTH_COUNT = 16;
static const unsigned int TABLE_COUNT = 32;
static const unsigned int WAVE_COUNT = 256;
static const unsigned int GROOVE_COUNT = 32;
static const unsigned int WORD_COUNT = 42;
    
static const unsigned char CLONE_DEEP = 0;
static const unsigned char CLONE_SLIM = 1;

// An LSDJ song
struct lsdj_song_t
{
    unsigned char version;
    unsigned char tempo;
    unsigned char transposition;
    
    // The sequences of chains in the song
    lsdj_row_t rows[ROW_COUNT];
    
    // The chains in the song
    lsdj_chain_t* chains[CHAIN_COUNT];
    
    // The prases in the song
    lsdj_phrase_t* phrases[PHRASE_COUNT];
    
    // Instruments of the song
    lsdj_instrument_t* instruments[INSTRUMENT_COUNT];
    
    // Soft synths of the song
    lsdj_synth_t synths[SYNTH_COUNT];
    
    // Wave frames of the song
    lsdj_wave_t waves[WAVE_COUNT];
    
    // The tables in the song
    lsdj_table_t* tables[TABLE_COUNT];
    
    // The grooves in the song
    lsdj_groove_t grooves[GROOVE_COUNT];
    
    // The speech synth words in the song
    lsdj_word_t words[WORD_COUNT];
    char wordNames[WORD_COUNT][WORD_NAME_LENGTH];
    
    // Bookmarks
    unsigned char bookmarks[BOOKMARK_COUNT];
    
    struct
    {
        unsigned char keyDelay;
        unsigned char keyRepeat;
        unsigned char font;
        unsigned char sync;
        unsigned char colorSet;
        unsigned char clone;
        unsigned char fileChangedFlag;
        unsigned char powerSave;
        unsigned char preListen;
        
        struct
        {
            unsigned char days;
            unsigned char hours;
            unsigned char minutes;
        } totalTime;
        
        struct
        {
            unsigned char hours;
            unsigned char minutes;
        } workTime;
    } meta;
    
    unsigned char reserved1030[96];
    unsigned char reserved1fba[70];
    unsigned char reserved2000[32];
    unsigned char reserved3fbf;
    unsigned char reserved3fb9;
    unsigned char reserved3fc6[58];
    unsigned char reserved5fe0[32];
    unsigned char reserved7ff2[13];
};

typedef struct lsdj_song_t lsdj_song_t;

// Create/free projects
lsdj_song_t* lsdj_new_song(lsdj_error_t** error);
void lsdj_free_song(lsdj_song_t* song);

// Deserialize a song
lsdj_song_t* lsdj_read_song(lsdj_vio_read_t read, lsdj_vio_tell_t tell, lsdj_vio_seek_t seek, void* user_data, lsdj_error_t** error);
lsdj_song_t* lsdj_read_song_from_memory(const unsigned char* data, size_t size, lsdj_error_t** error);
    
// Serialize a song
void lsdj_write_song(const lsdj_song_t* song, lsdj_vio_write_t write, void* user_data, lsdj_error_t** error);
void lsdj_write_song_to_memory(const lsdj_song_t* song, unsigned char* data, size_t size, lsdj_error_t** error);

// Change data in a song

#endif