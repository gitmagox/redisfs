/**
 * Test cases for fastlz compression code.
 *
 * The testing framework uses cutest:
 *
 *   http://cutest.sourceforge.net/
 *
 * All tests are driven by the code in AllTests.c
 *
 * Steve
 * --
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fastlz.h"
#include "fastlz_test.h"


/**
 * Simple test.
 */
void
TestNOP (CuTest * tc)
{
    char *ptr = NULL;
    char *nul = NULL;

    CuAssertPtrEquals (tc, nul, ptr);

    free (nul);
    free (ptr);
}


void
TestCompress (CuTest * tc)
{
  char input[] = { "This is a test input string.  I like to test input." };
  char output[200];
  int  input_len = strlen( input );

  int compressdata_size = fastlz_compress_level(2, (void*)input, input_len, output );

  printf("LEN:%d -> %d\n", input_len, compressdata_size);
  CuAssertTrue (tc, compressdata_size < input_len );

}

CuSuite *
fastlz_getsuite ()
{
    CuSuite *suite = CuSuiteNew ();

    SUITE_ADD_TEST (suite, TestNOP);
    SUITE_ADD_TEST (suite, TestCompress);

    return suite;
}
