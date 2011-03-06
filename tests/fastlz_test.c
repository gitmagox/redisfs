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


CuSuite *
fastlz_getsuite ()
{
    CuSuite *suite = CuSuiteNew ();

    SUITE_ADD_TEST (suite, TestNOP);

    return suite;
}
