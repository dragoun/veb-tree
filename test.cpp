#include <cstdlib>
#include "veb.hpp"

int main ( int argc, char ** argv )
{
  int res;
  int universe = 16;
  int testCnt = 0;
  int failedTestsCnt = 0;
  TvEB * tree = NULL;
  res = vEB_insert ( tree, 2 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 2 );
  testCnt++;
  if ( res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 3 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 8 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 13 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 15 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }

  for ( int i = 0; i < universe; ++i )
  {
    res = vEB_find ( tree, i );
    switch ( i )
    {
    case 2:
    case 3:
    case 8:
    case 13:
    case 15:
      testCnt++;
      if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    }
  }

  for ( int i = -1; i < universe; ++i )
  {
    int succ;
    res = vEB_succ ( tree, i, succ );
    switch ( i )
    {
    case -1:
    case 0:
    case 1:
      testCnt++;
      if ( !res || succ != 2 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 2:
      testCnt++;
      if ( !res || succ != 3 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      testCnt++;
      if ( !res || succ != 8 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      testCnt++;
      if ( !res || succ != 13 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 13:
    case 14:
      testCnt++;
      if ( !res || succ != 15 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    }
  }

  for ( int i = 0; i <= universe; ++i )
  {
    int pred;
    res = vEB_pred ( tree, i, pred );
    switch ( i )
    {
    case 3:
      testCnt++;
      if ( !res || pred != 2 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      testCnt++;
      if ( !res || pred != 3 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
      testCnt++;
      if ( !res || pred != 8 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 14:
    case 15:
      testCnt++;
      if ( !res || pred != 13 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 16:
      testCnt++;
      if ( !res || pred != 15 ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    }
  }

  res = vEB_delete ( tree, 5 );
  testCnt++;
  if ( res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_delete ( tree, 2 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_delete ( tree, 2 );
  testCnt++;
  if ( res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_delete ( tree, 3 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_delete ( tree, 13 );
  testCnt++;
  if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }

  for ( int i = 0; i < universe; ++i )
  {
    res = vEB_find ( tree, i );
    switch ( i )
    {
    case 8:
    case 15:
      testCnt++;
      if ( !res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( res ) { std::cout << "failed test " << testCnt << std::endl; failedTestsCnt++; }
      break;
    }
  }

  std::cout << failedTestsCnt << " out of " << testCnt << " tests failed" << std::endl;
  return 0;
}
