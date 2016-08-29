#include <stdlib.h>
#include <check.h>
#include <math.h>

#include "check_suites.h"

Suite * make_master_suite(void) {
	Suite *s;
	s = suite_create("Master Suite");
	
	return s;
}
	
int main() {
	int number_failed;
	SRunner *sr;

    sr = srunner_create(make_master_suite());
    srunner_add_suite(sr, make_converter_suite());
    srunner_add_suite(sr, make_calculator_suite());
    srunner_add_suite(sr, make_rn_result_suite());

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
