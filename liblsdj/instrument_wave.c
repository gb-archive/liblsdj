#include "instrument.h"

void lsdj_instrument_wave_set_synth(lsdj_song_t* song, uint8_t instrument, uint8_t synth)
{
	set_instrument_bits(song, instrument, 2, 4, 4, synth);
}

uint8_t lsdj_instrument_wave_get_synth(const lsdj_song_t* song, uint8_t instrument)
{
	return get_instrument_bits(song, instrument, 2, 4, 4);
}

void lsdj_instrument_wave_set_play_mode(lsdj_song_t* song, uint8_t instrument, lsdj_wave_play_mode mode)
{
	set_instrument_bits(song, instrument, 9, 0, 2, (uint8_t)mode);
}

lsdj_wave_play_mode lsdj_instrument_wave_get_play_mode(const lsdj_song_t* song, uint8_t instrument)
{
	return (lsdj_wave_play_mode)get_instrument_bits(song, instrument, 9, 0, 2);
}

void lsdj_instrument_wave_set_length(lsdj_song_t* song, uint8_t instrument, uint8_t length)
{
	const uint8_t version = lsdj_song_get_format_version(song);
	if (version >= 6)
		set_instrument_bits(song, instrument, 10, 0, 4, 0xF - length);
	else if (version == 6)
		set_instrument_bits(song, instrument, 10, 0, 4, length);
	else
		set_instrument_bits(song, instrument, 14, 4, 4, length);

}

uint8_t lsdj_instrument_wave_get_length(const lsdj_song_t* song, uint8_t instrument)
{
	const uint8_t version = lsdj_song_get_format_version(song);

	if (version >= 6)
		return 0xF - get_instrument_bits(song, instrument, 10, 0, 4);
	else if (version == 6)
		return get_instrument_bits(song, instrument, 10, 0, 4);
	else
		return get_instrument_bits(song, instrument, 14, 4, 4);
}

void lsdj_instrument_wave_set_repeat(lsdj_song_t* song, uint8_t instrument, uint8_t repeat)
{
	set_instrument_bits(song, instrument, 2, 0, 4, repeat);
}

uint8_t lsdj_instrument_wave_get_repeat(const lsdj_song_t* song, uint8_t instrument)
{
	return get_instrument_bits(song, instrument, 2, 0, 4);
}

bool lsdj_instrument_wave_set_speed(lsdj_song_t* song, uint8_t instrument, uint8_t speed)
{
    const uint8_t version = lsdj_song_get_format_version(song);
    
    // Speed is stored as starting at 0, but displayed as starting at 1, so subtract 1
    speed -= 1;
    
    if (version >= 6)
        set_instrument_bits(song, instrument, 11, 0, 8, speed - 3);
    else if (version == 6)
        set_instrument_bits(song, instrument, 11, 0, 8, speed);
    else {
    	if (speed > 0x0F)
    		return false;

        set_instrument_bits(song, instrument, 14, 0, 4, speed);
    }

    return true;
}

uint8_t lsdj_instrument_wave_get_speed(const lsdj_song_t* song, uint8_t instrument)
{
	const uint8_t version = lsdj_song_get_format_version(song);
    
    // Read the speed value
    uint8_t speed = 0;
	if (version >= 6)
		speed = get_instrument_bits(song, instrument, 11, 0, 8) + 3;
	else if (version == 6)
		speed = get_instrument_bits(song, instrument, 11, 0, 8);
	else
		speed = get_instrument_bits(song, instrument, 14, 0, 4);
    
    // Speed is stored as starting at 0, but displayed as starting at 1, so add 1
    return speed + 1;
}
