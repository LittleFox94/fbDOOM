//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
// Copyright(C) 2021      Mara Sophie Grosch
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	WAD I/O functions, loading compiled-in WAD file
//

#include <string.h>

#include "m_misc.h"
#include "w_file.h"
#include "z_zone.h"

typedef struct
{
    wad_file_t wad;
    unsigned char* data;
} compiled_wad_file_t;

extern wad_file_class_t compiled_wad_file;

extern size_t  _binary_DOOM1_WAD_size;
extern uint8_t _binary_DOOM1_WAD_start[];

static wad_file_t *W_CompiledIn_OpenFile(char *path)
{
    compiled_wad_file_t *result;
    // Create a new stdc_wad_file_t to hold the file handle.

    result = Z_Malloc(sizeof(compiled_wad_file_t), PU_STATIC, 0);
    result->wad.file_class = &compiled_wad_file;
    result->wad.mapped = NULL;
    result->wad.length = (size_t)&_binary_DOOM1_WAD_size;

    result->data = _binary_DOOM1_WAD_start;

    return &result->wad;
}

static void W_CompiledIn_CloseFile(wad_file_t *wad)
{
    Z_Free(wad);
}

// Read data from the specified position in the file into the 
// provided buffer.  Returns the number of bytes read.

size_t W_CompiledIn_Read(wad_file_t *wad, unsigned int offset,
                   void *buffer, size_t buffer_len)
{
    compiled_wad_file_t *compiled_in_wad;

    compiled_in_wad = (compiled_wad_file_t *) wad;

    memcpy(buffer, &compiled_in_wad->data[offset], buffer_len);
    return buffer_len;
}


wad_file_class_t compiled_wad_file = 
{
    W_CompiledIn_OpenFile,
    W_CompiledIn_CloseFile,
    W_CompiledIn_Read,
};


