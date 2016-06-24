#include <cstdlib>
#include <cmath>
#include "veb.hpp"

void testSuite1()
{
  int res;
  int universe = 16;
  int testCnt = 0;
  int failedTestsCnt = 0;
  TvEB * tree = new TvEB ( universe );
  res = vEB_insert ( tree, 2 );
  testCnt++;
  if ( !res ) { std::cout << "failed insert test, test number " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 2 );
  testCnt++;
  if ( res ) { std::cout << "failed insert test, test number " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 3 );
  testCnt++;
  if ( !res ) { std::cout << "failed insert test, test number " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 8 );
  testCnt++;
  if ( !res ) { std::cout << "failed insert test, test number " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 13 );
  testCnt++;
  if ( !res ) { std::cout << "failed insert test, test number " << testCnt << std::endl; failedTestsCnt++; }
  res = vEB_insert ( tree, 15 );
  testCnt++;
  if ( !res ) { std::cout << "failed insert test, test number " << testCnt << std::endl; failedTestsCnt++; }

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
      if ( !res ) { std::cout << "failed find test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( res ) { std::cout << "failed find test, test number " << testCnt << std::endl; failedTestsCnt++; }
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
      if ( !res || succ != 2 ) { std::cout << "failed successor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 2:
      testCnt++;
      if ( !res || succ != 3 ) { std::cout << "failed successor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      testCnt++;
      if ( !res || succ != 8 ) { std::cout << "failed successor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      testCnt++;
      if ( !res || succ != 13 ) { std::cout << "failed successor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 13:
    case 14:
      testCnt++;
      if ( !res || succ != 15 ) { std::cout << "failed successor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( res ) { std::cout << "failed successor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    }
  }

  for ( int i = 0; i <= universe; ++i )
  {
    int pred;
    res = vEB_pred ( tree, i, pred );
    switch ( i )
    {
    case 0:
    case 1:
    case 2:
      testCnt++;
      if ( res ) { std::cout << "failed predecessor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 3:
      testCnt++;
      if ( !res || pred != 2 ) { std::cout << "failed predecessor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      testCnt++;
      if ( !res || pred != 3 ) { std::cout << "failed predecessor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
      testCnt++;
      if ( !res || pred != 8 ) { std::cout << "failed predecessor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    case 14:
    case 15:
      testCnt++;
      if ( !res || pred != 13 ) { std::cout << "failed predecessor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( !res || pred != 15 ) { std::cout << "failed predecessor test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    }
  }

  res = vEB_find ( tree, 8 );

  res = vEB_delete ( tree, 5 );
  testCnt++;
  if ( res ) { std::cout << "failed delete test, test number " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_find ( tree, 8 );

  res = vEB_delete ( tree, 2 );
  testCnt++;
  if ( !res ) { std::cout << "failed delete test, test number " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_find ( tree, 8 );

  res = vEB_delete ( tree, 2 );
  testCnt++;
  if ( res ) { std::cout << "failed delete test, test number " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_find ( tree, 8 );

  res = vEB_delete ( tree, 3 );
  testCnt++;
  if ( !res ) { std::cout << "failed delete test, test number " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_find ( tree, 8 );

  res = vEB_delete ( tree, 13 );
  testCnt++;
  if ( !res ) { std::cout << "failed delete test, test number " << testCnt << std::endl; failedTestsCnt++; }

  res = vEB_find ( tree, 8 );

  for ( int i = 0; i < universe; ++i )
  {
    res = vEB_find ( tree, i );
    switch ( i )
    {
    case 8:
    case 15:
      testCnt++;
      if ( !res ) { std::cout << "failed find test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    default:
      testCnt++;
      if ( res ) { std::cout << "failed find test, test number " << testCnt << std::endl; failedTestsCnt++; }
      break;
    }
  }

  std::cout << failedTestsCnt << " out of " << testCnt << " tests failed" << std::endl;

  if ( tree ) delete tree;
}

void testSuite2 ( int universe = 65536 )
{
  if ( universe < 64 )
  {
    std::cout << "testSuite2 is made for universe size > 64" << std::endl;
    return;
  }

  if ( ( universe & ( universe - 1 ) ) != 0 )
  {
    std::cout << "universe size have to be power of 2s" << std::endl;
    return;
  }

  int res;
  int testCnt = 0;
  int failedTestsCnt = 0;

  TvEB * tree = new TvEB ( universe );

  int timer = time ( NULL );
  // std::cout << timer << std::endl;
  srand ( timer ); // 1466724922
  int numberCnt = 0;
  int * numbers = new int [universe];
  for ( int i = 0; i < universe; ++i )
  {
    if ( rand() % 8 == 0 )
    {
      numbers[i] = 1;
      numberCnt++;
      res = vEB_insert ( tree, i );
      testCnt++;
      if ( !res )
      {
        std::cout << "failed to insert " << i << ", test number " << testCnt << std::endl;
        failedTestsCnt++;
        continue;
      }
      if ( rand() % 4 == 0 )
      {
        res = vEB_insert ( tree, i );
        testCnt++;
        if ( res )
        {
          std::cout << "second insert of " << i << " should fail and it did not, test number " << testCnt << std::endl;
          failedTestsCnt++;
        }
      }
    }
    else
    {
      numbers[i] = 0;
    }
    // std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
  }

  for ( int i = 0; i < rand() % 4; ++i )
  {
    int idx = rand() % universe;
    res = vEB_find ( tree, idx );
    testCnt++;
    if ( numbers[idx] )
    {
      if ( !res ) { std::cout << "failed to find " << idx << " which is in the tree, test number " << testCnt << std::endl; failedTestsCnt++; }
    }
    else
    {
      if ( res ) { std::cout << "number " << idx << " incorrectly found, test number " << testCnt << std::endl; failedTestsCnt++; }
    }
  }

  for ( int i = 0; i < rand() % ( universe ); ++i )
  {
    int idx = rand() % universe;
    if ( numbers[idx] )
    {
      res = vEB_delete ( tree, idx );
      numbers[idx] = 0;
      testCnt++;
      if ( !res )
      {
        std::cout << "failed to delete " << idx << ", test number " << testCnt << std::endl;
        failedTestsCnt++;
      }
      if ( rand() % 4 )
      {
        res = vEB_delete ( tree, idx );
        testCnt++;
        if ( res )
        {
          std::cout << "second delete of " << idx << " should fail and it did not, test number " << testCnt << std::endl;
          failedTestsCnt++;
        }
      }
    }
    else
    {
      res = vEB_delete ( tree, idx );
      testCnt++;
      if ( res )
      {
        std::cout << "delete of number " << idx << " should fail because it is not in the tree, test number " << testCnt << std::endl;
        failedTestsCnt++;
      }
    }
  }

  for ( int i = 0; i < universe % 8; ++i )
  {
    int idx = ( rand() % ( universe + 1 ) ) - 1;
    int succ;
    int realSucc = -1;
    res = vEB_succ ( tree, idx, succ );
    testCnt++;
    for ( int i = idx + 1; i < universe; ++i )
    {
      if ( numbers[i] )
      {
        realSucc = i;
        break;
      }
    }

    if ( realSucc >= 0 )
    {
      if ( !res || succ != realSucc )
      {
        std::cout << "failed to find successor of number " << idx << " which is " << realSucc << ", test number " << testCnt << std::endl;
        failedTestsCnt++;
      }
    }
    else if ( res )
    {
      std::cout << "successor " << succ << " of number " << idx << " found even when there is none, test number " << testCnt << std::endl;
      failedTestsCnt++;
    }
  }

  for ( int i = 0; i < universe % 8; ++i )
  {
    int idx = rand() % ( universe + 1 );
    int pred;
    int realPred = universe;
    res = vEB_pred ( tree, idx, pred );
    testCnt++;
    for ( int i = idx - 1; i >= 0; --i )
    {
      if ( numbers[i] )
      {
        realPred = i;
        break;
      }
    }

    if ( realPred < universe )
    {
      if ( !res || pred != realPred )
      {
        std::cout << "failed to find predessor of number " << idx << " which is " << realPred << ", test number " << testCnt << std::endl;
        failedTestsCnt++;
      }
    }
    else if ( res )
    {
      std::cout << "predessor " << pred << " of number " << idx << " found even when there is none, test number " << testCnt << std::endl;
      failedTestsCnt++;
    }
  }

  std::cout << failedTestsCnt << " out of " << testCnt << " tests failed" << std::endl;

  if ( tree ) delete tree;
}

int main ( int argc, char ** argv )
{
  testSuite1();
  testSuite2();
  return 0;
}
