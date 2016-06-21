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
    if ( !vEB_insert ( tree->summary, highVal ) )
    {
      return false;
    }
  }

  if ( !vEB_insert ( tree->cluster[highVal], low ( val ) ) )
  {
    return false;
  }
  return true;
}

bool vEB_delete ( TvEB * tree, int val )
{
  if ( tree->min == val )
  {
    int i = tree->summary->min;
    if ( i == UNDEFINED )
    {
      tree->min = tree->max = UNDEFINED;
      return true;
    }

    tree->min = index ( i, tree->cluster[i]->min );
  }

  int highVal = high ( val );
  if ( !vEB_delete ( tree->cluster[highVal], low ( val ) ) )
  {
    return false;
  }

  if ( tree->cluster[highVal]->min == UNDEFINED )
  {
    if ( !vEB_delete ( tree->summary, highVal ) )
    {
      return false;
    }
  }

  if ( tree->max == val )
  {
    if ( tree->summary->max == UNDEFINED )
    {
      tree->max = tree->min;
    }
    else
    {
      int i = tree->summary->max;
      tree->max = index ( i, tree->cluster[i]->max );
    }
  }
  return true;
}

bool vEB_find ( TvEB * tree, int val, int & res )
{
  return false;
}

bool vEB_succ ( TvEB * tree, int val, int & res )
{
  return false;
}
