#include <testsuite.h>
#include <rbt_assert.h>

#include "test_wopr.h"

void WOPR_Test_Parse_Type( void )
{


}


void WOPR_Create_WOPR_TestSuite( void )
{
    RBT_TestSuite* suite = RBT_CreateSuite( "WOPR_TestSuite" );
    RBT_AddCase( suite, WOPR_Test_Parse_Type );
}

