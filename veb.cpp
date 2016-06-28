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

TvEB::TvEB ( int uniSize )
  : uni ( powTwoRoundUp ( uniSize ) ), uniSqrt ( sqrt ( uni ) ),
    lowerUniSqrt ( lowerSqrt ( uni ) ), higherUniSqrt ( higherSqrt ( uni ) ),
    min ( UNDEFINED ), max ( UNDEFINED ), summary ( NULL )
{
  if ( uniSize <= 0 )
  {
    std::cerr << "universe size of TvEB must be bigger than 0" << std::endl;
    return;
  }

  if ( uni > 2 )
  {
    cluster = new TvEB * [higherUniSqrt];
    for ( int i = 0; i < higherUniSqrt; ++i )
    {
      cluster[i] = NULL;
    }
  }
  else
  {
    cluster = NULL;
  }
}

TvEB::~TvEB()
{
  if ( summary ) delete summary;
  if ( cluster )
  {
    for ( int i = 0; i < higherUniSqrt; ++i )
    {
      if ( cluster[i] ) delete cluster[i];
    }
    delete [] cluster;
  }
}

int powTwoRoundUp ( int x )
{
  if ( x < 0 ) return 0;
  --x;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return x + 1;
}

float lowerSqrt ( int val )
{
  return pow ( 2, floor ( log2 ( val )  / 2 ) );
}

float higherSqrt ( int val )
{
  return pow ( 2, ceil ( log2 ( val )  / 2 ) );
}

int low ( TvEB * tree, int val )
{
  return val % ( int ) lowerSqrt ( tree->uni );
}

int high ( TvEB * tree, int val )
{
  return val / lowerSqrt ( tree->uni );
}

int index ( TvEB * tree, int high, int low )
{
  return high * lowerSqrt ( tree->uni ) + low;
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

bool vEB_insert ( TvEB *& tree, int val, int parentUniSqrt )
{
  if ( !tree )
  {
    tree = new TvEB ( parentUniSqrt );
  }

#ifdef DEBUG
  DEBUG_OS << "inserting " << val << " to tree " << tree
           << " of size " << tree->uni << DEBUG_OS_ENDL;
#endif /* DEBUG */

  if ( val < 0 || val >= tree->uni ) return false;

  if ( tree->min == val || tree->max == val ) return false;

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

  if ( tree->uni > 2 )
  {
    int lowVal = low ( tree, val );
    int highVal = high ( tree, val );
    if ( !tree->cluster[highVal] )
    {
      if ( !vEB_insert ( tree->summary, highVal, tree->higherUniSqrt ) ) return false;
    }

    if ( !vEB_insert ( tree->cluster[highVal], lowVal, tree->lowerUniSqrt ) ) return false;
  }
  return true;
}

bool vEB_delete ( TvEB *& tree, int val )
{
  if ( !tree ) return false;

#ifdef DEBUG
  DEBUG_OS << "deleting " << val << " from tree " << tree
           << " of size " << tree->uni << DEBUG_OS_ENDL;
#endif /* DEBUG */

  if ( val < 0 || val >= tree->uni ) return false;
  if ( tree->min > val || tree->max < val ) return false;

  if ( tree->min == val )
  {
    int i;
    if ( !vEB_min ( tree->summary, i ) || i == UNDEFINED )
    {
      if ( tree->min != tree->max )
      {
        tree->min = tree->max;
        return true;
      }

      tree->min = tree->max = UNDEFINED;
      delete tree;
      tree = NULL;
      return true;
    }

    val = tree->min = index ( tree, i, tree->cluster[i]->min );
  }

  if ( tree->uni > 2 )
  {
    int highVal = high ( tree, val );
    if ( !vEB_delete ( tree->cluster[highVal], low ( tree, val ) ) ) return false;

    int tmp;
    if ( !vEB_min ( tree->cluster[highVal], tmp ) || tmp == UNDEFINED )
    {
      if ( !vEB_delete ( tree->summary, highVal ) ) return false;
    }
  }

  if ( tree->max == val )
  {
    int tmp;
    if ( !vEB_max ( tree->summary, tmp ) || tmp == UNDEFINED )
    {
      tree->max = tree->min;
    }
    else
    {
      int i;
      if ( !vEB_max ( tree->summary, i ) ) return false;
      tree->max = index ( tree, i, tree->cluster[i]->max );
    }
  }
  return true;
}

bool vEB_find ( TvEB * tree, int val )
{
  if ( !tree ) return false;

#ifdef DEBUG
  DEBUG_OS << "looking for " << val << " in tree " << tree << DEBUG_OS_ENDL;
#endif /* DEBUG */

  if ( val < 0 || val >= tree->uni ) return false;
  if ( tree->min > val || tree->max < val ) return false;
  if ( tree->min == val ) return true;
  if ( !tree->summary )
  {
    return tree->max == val;
  }
  if ( !vEB_find ( tree->cluster[high ( tree, val )], low ( tree, val ) ) )
    return false;
  return true;
}

bool vEB_succ ( TvEB * tree, int val, int & res )
{
  if ( !tree ) return false;

#ifdef DEBUG
  DEBUG_OS << "looking for successor of " << val << " in tree " << tree
           << " of size " << tree->uni << DEBUG_OS_ENDL;
#endif /* DEBUG */

  if ( val < -1 || val >= tree->uni ) return false;

  if ( tree->min > val )
  {
    res = tree->min;
    return true;
  }

  if ( !tree->summary )
  {
    if ( tree->max > val )
    {
      res = tree->max;
      return true;
    }
    return false;
  }

  int lowVal = low ( tree, val );
  int highVal = high ( tree, val );
  int i = highVal;
  int j = UNDEFINED;
  int tmp;
  if ( vEB_max ( tree->cluster[i], tmp ) && lowVal < tmp )
  {
    if ( !vEB_succ ( tree->cluster[i], lowVal, j ) ) return false;
  }
  else
  {
    if ( !vEB_succ ( tree->summary, highVal, i ) )
    {
      if ( tree->max > val )
      {
        res = tree->max;
        return true;
      }
      return false;
    }
    if ( !vEB_min ( tree->cluster[i], j ) ) return false;
  }

  res = index ( tree, i, j );
  return true;
}

bool vEB_pred ( TvEB * tree, int val, int & res )
{
  if ( !tree ) return false;

#ifdef DEBUG
  DEBUG_OS << "looking for predecessor of " << val << " in tree " << tree
           << " of size " << tree->uni << DEBUG_OS_ENDL;
#endif /* DEBUG */

  if ( val < 0 || val > tree->uni ) return false;

  if ( tree->max < val )
  {
    res = tree->max;
    return true;
  }

  if ( !tree->summary )
  {
    if ( tree->min < val )
    {
      res = tree->min;
      return true;
    }
    return false;
  }

  int lowVal = low ( tree, val );
  int highVal = high ( tree, val );
  int i = highVal;
  int j = UNDEFINED;
  int tmp;
  if ( vEB_min ( tree->cluster[i], tmp ) && lowVal > tmp )
  {
    if ( !vEB_pred ( tree->cluster[i], lowVal, j ) ) return false;
  }
  else
  {
    if ( !vEB_pred ( tree->summary, highVal, i ) )
    {
      if ( tree->min < val )
      {
        res = tree->min;
        return true;
      }
      return false;
    }
    if ( !vEB_max ( tree->cluster[i], j ) ) return false;
  }

  res = index ( tree, i, j );
  return true;
}

void vEB_print ( TvEB * tree, std::ostream & os )
{
  if ( !tree ) return;
  os << "tree: " << tree << std::endl;
  os << "min: " << tree->min << ", max: " << tree->max << std::endl;
  os << "uni: " << tree->uni << ", uniSqrt: " << tree->uniSqrt << std::endl;
  os << "lowerUniSqrt: " << tree->lowerUniSqrt;
  os << ", higherUniSqrt: " << tree->higherUniSqrt << std::endl;
  os << "summary: " << tree->summary << std::endl;
  if ( tree->uni > 2 )
  {
    for ( int i = 0; i < tree->higherUniSqrt; ++i )
    {
      os << "cluster " << i << ": " << tree->cluster[i] << std::endl;
    }
  }
  else
  {
    os << "cluster " << tree->cluster << std::endl;
  }
}
