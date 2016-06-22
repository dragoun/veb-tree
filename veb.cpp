/*******************************************************************************
* Copyright (C) 2016 Dominik Dragoun                                           *
*                                                                              *
* This file is part of my Van Emde Boas tree data structure implementation in  *
* C/C++. It is released under MIT License, which should be distributed with    *
* this file. It is also avaible at <https://opensource.org/licenses/MIT>.      *
*******************************************************************************/

/***************************************************************************//**
 * @file veb.cpp
 *
 * @brief      File containing definition of a class implementing Van Emde Boas
 *             tree data structure.
 * @author     Dominik Dragoun (dominik@dragoun.com)
 * @date       June, 2016
 * @copyright  Copyright (C) 2016 Dominik Dragoun.
 * @license    This project is released undes the MIT License.
 ******************************************************************************/

#include "veb.hpp"

int low ( int val )
{
  return val % uniSqrt;
}

int high ( int val )
{
  return val / uniSqrt;
}

int index ( int high, int low )
{
  return high * uniSqrt + low;
}

bool vEB_min ( TvEB * tree, int & res )
{
  if ( tree )
  {
    res = tree->min;
    return true;
  }
  return false;
}

bool vEB_max ( TvEB * tree, int & res )
{
  if ( tree )
  {
    res = tree->max;
    return true;
  }
  return false;
}

bool vEB_insert ( TvEB *& tree, int val )
{
  if ( val < 0 || val >= uni ) return false;

  if ( !tree )
  {
    tree = new TvEB();
  }

  if ( tree->min == val ) return false;

  if ( tree->min == UNDEFINED )
  {
    tree->min = tree->max = val;
    return true;
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
    if ( !vEB_insert ( tree->summary, highVal ) ) return false;
  }

  if ( !vEB_insert ( tree->cluster[highVal], low ( val ) ) ) return false;
  return true;
}

bool vEB_delete ( TvEB *& tree, int val )
{
  if ( val < 0 || val >= uni ) return false;

  if ( !tree ) return false;

  if ( tree->min == val )
  {
    int i;
    if ( !vEB_min ( tree->summary, i ) || i == UNDEFINED )
    {
      tree->min = tree->max = UNDEFINED;
      delete tree;
      tree = NULL;
      return true;
    }

    val = tree->min = index ( i, tree->cluster[i]->min ); // should there be val = ?
  }

  int highVal = high ( val );
  if ( !vEB_delete ( tree->cluster[highVal], low ( val ) ) ) return false;

  int tmp;
  if ( !vEB_min ( tree->cluster[highVal], tmp ) || tmp == UNDEFINED )
  {
    if ( !vEB_delete ( tree->summary, highVal ) ) return false;
  }

  if ( tree->max == val )
  {
    if ( !vEB_min ( tree->summary, tmp ) || tmp == UNDEFINED )
    {
      tree->max = tree->min;
    }
    else
    {
      int i;
      if ( !vEB_min ( tree->summary, i ) ) return false;
      tree->max = index ( i, tree->cluster[i]->max );
    }
  }
  return true;
}

bool vEB_find ( TvEB * tree, int val )
{
  if ( !tree ) return false;
  if ( tree->min == val ) return true;
  if ( !vEB_find ( tree->cluster[high ( val )], low ( val ) ) ) return false;
  return true;
}

bool vEB_succ ( TvEB * tree, int val, int & res )
{
  if ( val < 0 || val >= uni ) return false;

  if ( !tree ) return false;

  int lowVal = low ( val );
  int highVal = high ( val );
  int i = highVal;
  int j = UNDEFINED;
  int tmp;
  if ( vEB_max ( tree->cluster[i], tmp ) && lowVal < tmp )
  {
    if ( !vEB_succ ( tree->cluster[i], lowVal, j ) ) return false;
  }
  else
  {
    if ( !vEB_succ ( tree->summary, highVal, i ) ) return false;
    if ( !vEB_min ( tree->cluster[i], j ) ) return false;
  }

  res = index ( i, j );
  return true;
}

bool vEB_pred ( TvEB * tree, int val, int & res )
{
  return false;
}

void vEB_print ( TvEB * tree, ostream & os )
{
  if ( !tree ) return;
  os << "tree: " << tree << endl;
  os << "summary: " << tree->summary << endl;
  for ( int i = 0; i < uniSqrt; ++i )
  {
    os << "cluster " << i << ": " << tree->cluster[i] << endl;
  }
}
