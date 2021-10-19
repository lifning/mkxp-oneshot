/*
** serial-util.h
**
** This file is part of mkxp.
**
** Copyright (C) 2013 Jonas Kulla <Nyocurio@gmail.com>
**
** mkxp is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** mkxp is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with mkxp.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SERIALUTIL_H
#define SERIALUTIL_H

#include <stdint.h>
#include <string.h>

#include <SDL_endian.h>

#if SDL_BYTEORDER != SDL_LIL_ENDIAN && SDL_BYTEORDER != SDL_BIG_ENDIAN
#error "Middle endian systems not supported"
#endif

static inline int32_t
readInt32(const char **dataP)
{
	int32_t result;

	memcpy(&result, *dataP, 4);
	*dataP += 4;

	return SDL_SwapLE32(result);
}

static inline double
readDouble(const char **dataP)
{
	int64_t result;

	memcpy(&result, *dataP, 8);
	*dataP += 8;

	result = SDL_SwapLE64(result);

	return *(double*)(&result);
}

static inline void
writeInt32(char **dataP, int32_t value)
{
	value = SDL_SwapLE32(value);
	memcpy(*dataP, &value, 4);
	*dataP += 4;
}

static inline void
writeDouble(char **dataP, double value)
{
	int64_t ivalue = *(int64_t*)&value;
	ivalue = SDL_SwapLE64(ivalue);
	memcpy(*dataP, &ivalue, 8);
	*dataP += 8;
}

#endif // SERIALUTIL_H
