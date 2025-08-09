#include "cu_test.h"

void test_fail_mix(void)
{
    CU_RUN_START;
    CU_SECTION("Before");
    CU_FAIL;
    CU_PASS;
    CU_SECTION("After");
    CU_PASS;
    CU_FAIL;
    CU_SECTION("Valid section");
    CU_PASS;
    CU_PASS;
    CU_RUN_END;
}


void test_fail_only(void)
{
    CU_RUN_START;
    CU_SECTION("Failed section");
    CU_FAIL;
    CU_FAIL;
    CU_FAIL;
    CU_RUN_END;
}

int main(void)
{
    CU_BEGIN("Demo bug in the project");
    CU_RUN(test_fail_only);
    CU_RUN(test_fail_mix);
    CU_RUN(test_fail_only);
    CU_END;
}
