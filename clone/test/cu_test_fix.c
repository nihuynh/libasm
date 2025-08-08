#include "cu_test.h"

void test_fail_before(void)
{
    CU_RUN_START;
    CU_SECTION("Before");
    CU_FAIL("Oups, this happend");
    CU_PASS;
    CU_RUN_END;
}


void test_fail_after(void)
{
    CU_RUN_START;
    CU_SECTION("After");
    CU_PASS;
    CU_FAIL("");
    CU_RUN_END;
}

int main(void)
{
    CU_BEGIN("Demo bug in the project");
    CU_RUN(test_fail_after);
    CU_RUN(test_fail_before);
    CU_END;
}
