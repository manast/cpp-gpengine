/***************************************************************************
                          Reduction.h  -  description
                             -------------------
    begin                : Sun Jun 16 2002
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
 #ifndef REDUCTION_H
 #define REDUCTION_H

 #include <deque>

 class Reduction;

 #include "Token.h"

 using namespace std;

 class Reduction {
   public:
   Reduction *parent;
   Token *tok;

   deque <Token*> childs;

   Reduction ();
   ~Reduction ();
 };


 #endif



