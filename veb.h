/*******************************************************************************
* Copyright (C) 2016 Dominik Dragoun                                           *
*                                                                              *
* This file is part of my Van Emde Boas tree data structure implementation in  *
* C/C++. It is released under MIT License, which should be distributed with    *
* this file. It is also avaible at <https://opensource.org/licenses/MIT>.      *
*******************************************************************************/

/***************************************************************************//**
 * @file veb.h
 *
 * @brief      File containing declarations of a class implementing Van Emde
 *             Boas tree data structure.
 * @author     Dominik Dragoun (dominik@dragoun.com)
 * @date       June, 2016
 * @copyright  Copyright (C) 2016 Dominik Dragoun.
 * @license    This project is released undes the MIT License.
 ******************************************************************************/

#ifndef __VEB_H_458976543568798867538649758687654752463747856374562543646__
#define __VEB_H_458976543568798867538649758687654752463747856374562543646__

#include <cmath>
#include <climits>

#define UNDEFINED INT_MIN

const int uni = 16;
const int uniSqrt = sqrt ( uni );

/***************************************************************************//**
 * @brief      Struct containing the Van Emde Boas tree.
 *
 * @details    It is a data structure which implements an associative array with
 *             m-bit integer keys. It supports operations of ordered associative
 *             array (Insert, Delete and Find) and two more order opperations -
 *             Find Next (Succ) and Find Previous (Pred). All these operations
 *             are performed in O(log m) time, or equivalently in O(log log M)
 *             time, where M = 2^m is the maximum number of elements that can be
 *             stored in the tree. It also supports the operation Minimum (Min)
 *             and Maximum (Max), wich returns the minimum and maximum element
 *             stored in the tree respectively. These both run in O(1) time,
 *             since the minimum and maximum element are stored as attributes in
 *             each tree.
 ******************************************************************************/
struct TvEB
{
  /*************************************************************************//**
   * @brief      Constructor.
   ****************************************************************************/
  TvEB()
  {
    min = UNDEFINED;
    max = UNDEFINED;
    summary = NULL;
    cluster = new TvEB * [uniSqrt];
    for ( int i = 0; i < uniSqrt; ++i )
    {
      cluster[i] = NULL;
    }
  }

  /*************************************************************************//**
   * @brief      Minimal value in the tree.
   ****************************************************************************/
  int min;

  /*************************************************************************//**
   * @brief      Maximal value in the tree.
   ****************************************************************************/
  int max;

  /*************************************************************************//**
   * @brief      Pointer to the summary structure of the tree.
   ****************************************************************************/
  TvEB * summary;

  /*************************************************************************//**
   * @brief      Pointer to the array of clusters of the tree.
   ****************************************************************************/
  TvEB ** cluster;
};


/***************************************************************************//**
 * @brief      Returns the element's index in the cluster.
 *
 * @param[in]  val   The value of the element.
 *
 * @return     The element's index in the cluster.
 ******************************************************************************/
int low ( int val )
{
  return val % uniSqrt;
}

/***************************************************************************//**
 * @brief      Returns the index of the element's cluster.
 *
 * @param[in]  x     The value of the element.
 * @param[in]  u     The size of the universe.
 *
 * @return     The index of the element's cluster.
 ******************************************************************************/
int high ( int val )
{
  return val / uniSqrt;
}

/***************************************************************************//**
 * @brief      Returns the value on index low in the cluster high.
 *
 * @param[in]  high  The cluster index.
 * @param[in]  low   The index of the element in the cluster.
 *
 * @return     The value of the element.
 ******************************************************************************/
int index ( int high, int low )
{
  return high * uniSqrt + low;
}

/***************************************************************************//**
 * @brief      Finds the lowest value stored in the given tree.
 *
 * @param[in]  tree   The pointer to the van Emde Boas tree.
 * @param[out] res    The lowest element.
 *
 * @retval     true   Successfully found the minimum.
 * @retval     false  Failed to found the minimum.
 ******************************************************************************/
bool vEB_min ( TvEB * tree, int & res )
{
  if ( tree )
  {
    res = tree->min;
    return true;
  }
  return false;
}

/***************************************************************************//**
 * @brief      Finds the highest value stored in the given tree.
 *
 * @param[in]  tree   The pointer to the van Emde Boas tree.
 * @param[out] res    The highest element.
 *
 * @retval     true   Successfully found the maximum.
 * @retval     false  Failed to found the maximum.
 ******************************************************************************/
bool vEB_max ( TvEB * tree, int & res )
{
  if ( tree )
  {
    res = tree->max;
    return true;
  }
  return false;
}

/***************************************************************************//**
 * @brief      Inserts the given value into the given vEB tree.
 *
 * @param[in]  tree   The pointer to the van Emde Boas tree.
 * @param[in]  val    The value of the element to insert.
 *
 * @retval     true   Successfully inserted the value.
 * @retval     false  Failed to insert the value.
 ******************************************************************************/
bool vEB_insert ( TvEB * tree, int val );

/***************************************************************************//**
 * @brief      Removes the given value from the given vEB tree.
 *
 * @param[in]  tree   The pointer to the van Emde Boas tree.
 * @param[in]  val    The value of the element to remove.
 *
 * @retval     true   Successfully removed the value.
 * @retval     false  Failed to remove the value.
 ******************************************************************************/
bool vEB_delete ( TvEB * tree, int val );

/***************************************************************************//**
 * @brief      Finds if the given value is in the given vEB tree.
 *
 * @param[in]  tree   The pointer to the van Emde Boas tree.
 * @param[in]  val    The value of the element to find.
 * @param[out] res    The found element.
 *
 * @retval     true   Successfully found the element.
 * @retval     false  Failed to found the element.
 ******************************************************************************/
bool vEB_find ( TvEB * tree, int val, int & res );

/***************************************************************************//**
 * @brief      Finds the smallest value at least the given value in the given
 *             tree.
 *
 * @param[in]  tree   The pointer to the van Emde Boas tree.
 * @param[in]  val    The lower bound for the value of the sought element
 * @param[out] res    The found element.
 *
 * @retval     true   Successfully found the successor.
 * @retval     false  Failed to found the successor.
 ******************************************************************************/
bool vEB_succ ( TvEB * tree, int val, int & res );

/***************************************************************************//**
 * @brief      Finds the largest value at most the given value in the given
 *             tree.
 *
 * @param[in]  tree   The pointer to the van Emde Boas tree.
 * @param[in]  val    The upper bound for the value of the sought element
 * @param[out] res    The found element.
 *
 * @retval     true   Successfully found the predecessor.
 * @retval     false  Failed to found the predecessor.
 ******************************************************************************/
bool vEB_pred ( TvEB * tree, int val, int & res );

#endif /* __VEB_H_458976543568798867538649758687654752463747856374562543646__ */
