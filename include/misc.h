/***************************************************************************
                          misc.h  -  description
                             -------------------
    begin                : Sun Jun 2 2002
    copyright            : (C) 2002 by Manuel Astudillo
    email                : d00mas@efd.lth.se
 ***************************************************************************/

 /***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef MISC_H
#define MISC_H

#define integer unsigned short
#define byte unsigned char

typedef unsigned short UBYTE2;
#if defined (_BIGENDIAN)
    inline UBYTE2 EndianConversion (UBYTE2 input)
    {
	    UBYTE2 result = 
		      ((input & 0x00FF) << 8)
	        | ((input & 0xFF00) >> 8);
	    return result ;
    }
#else
    inline UBYTE2 EndianConversion (UBYTE2 input)
{
	return input ;
}
#endif 

#endif

