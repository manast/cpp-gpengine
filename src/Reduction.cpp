/***************************************************************************
                          Reduction.cpp  -  description
                             -------------------
    begin                : Sun Jun 16 2002
    copyright            : (C) 2002 Manuel Astudillo
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
 #include "Reduction.h"

 Reduction::Reduction () {
   parent = NULL;
   tok = NULL;

 }

 Reduction::~Reduction () {
  
   //for (unsigned short i=0; i < childs.size(); i++) {
   //  delete childs[i]->reduction;
   //  delete childs[i];
   //}
 }
