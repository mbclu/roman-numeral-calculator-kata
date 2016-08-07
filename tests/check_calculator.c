#include <stdlib.h>
#include <check.h>
#include <math.h>

#include "../src/calculator.h"

START_TEST (one_plus_one_is_two)
{
	ck_assert_str_eq("ii", add("i", "i"));
}
END_TEST

Suite * calculator_suite(void) {
	Suite *s;
	TCase *tc_core;

    s = suite_create("Calculator");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, one_plus_one_is_two);
    suite_add_tcase(s, tc_core);

    return s;
}
	
int main() {
	int number_failed;
    Suite *s;
    SRunner *sr;

    s = calculator_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
