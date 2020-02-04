/*
 
 This file is a part of liblsdj, a C library for managing everything
 that has to do with LSDJ, software for writing music (chiptune) with
 your gameboy. For more information, see:
 
 * https://github.com/stijnfrishert/liblsdj
 * http://www.littlesounddj.com
 
 --------------------------------------------------------------------------------
 
 MIT License
 
 Copyright (c) 2018 - 2020 Stijn Frishert
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */

#ifndef LSDJ_COMPRESSION_H
#define LSDJ_COMPRESSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "error.h"
#include "vio.h"

//! The block size used for the (de)crompression algorithm
#define BLOCK_SIZE (0x200)

//! The maximum amount of blocks stored in a sav
#define BLOCK_COUNT (191)

//! Decompress memory blocks according to the LSDJ compression spec
/*! This algorithm is used to store songs in the project slots in a sav,
	as well as in an .lsdsng file.

	@param followBlockSwitches Set this to true if block switches should be followed (the default), and false if block switches (0xE0, ID) should be ignored (in the case of reading lsdsng)

	See https://littlesounddj.fandom.com/wiki/File_Management_Structure for more info */
bool lsdj_decompress(lsdj_vio_t* rvio, lsdj_vio_t* wvio, bool followBlockSwitches, lsdj_error_t** error);

//! Compress memory blocks according to the LSDJ compression spec
/*! This algorithm is used to store songs in the project slots in a sav,
    as well as in an .lsdsng file.

    @param data The data that will be written
    @param blockOffset The offset to the block jump ids that will be written
 
    @return The amount of memory blocks written */
unsigned int lsdj_compress(const unsigned char* data, unsigned int blockOffset, lsdj_vio_t* wvio, lsdj_error_t** error);
    
#ifdef __cplusplus
}
#endif

#endif
