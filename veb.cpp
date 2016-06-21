/*******************************************************************************
* Copyright (C) 2016 Dominik Dragoun                                           *
*                                                                              *
* This file is part of my Van Emde Boas tree data structure implementation in  *
* C/C++. It is released under MIT License, which should be distributed with    *
* this file. It is also avaible at <https://opensource.org/licenses/MIT>.      *
*******************************************************************************/

#include "veb.h"

bool vEB_insert ( TvEB * tree, int val )
{
  if ( !tree )
  {
    tree = new TvEB();
  }

  if ( tree->min == UNDEFINED )
  {
    tree->min = tree->max = val;
  }

  if ( val < tree->min )
  {
    int tmp = val;
    val = tree->min;
    tree->min = tmp;
  }

  if ( val > tree->max )
  {
    tree->max = val;
  }

  int highVal = high ( val );
  if ( !tree->cluster[highVal] )
  {
    vEB_insert ( tree->summary, highVal );
  }

  vEB_insert ( tree->cluster[highVal], low ( val ) );
  return true;
}

bool vEB_delete ( TvEB * tree, int val, int & res )
{
  return false;
}

bool vEB_find ( TvEB * tree, int val, int & res )
{
  return false;
}

bool vEB_succ ( TvEB * tree, int val, int & res )
{
  return false;
}
