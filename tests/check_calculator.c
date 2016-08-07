#include <stdlib.h>
#include <check.h>
#include <math.h>

#include "../src/calculator.h"

START_TEST (one_plus_one_is_two)
{
	ck_assert_str_eq("ii", add("i", "i"));
}
END_TEST

START_TEST (one_plus_two_is_three)
{
	ck_assert_str_eq("iii", add("i", "ii"));
}
END_TEST

START_TEST (two_plus_two_is_four)
{
	ck_assert_str_eq("iv", add("ii", "ii"));
}
END_TEST

START_TEST (i_represents_one)
{
	ck_assert_uint_eq(1, convertToInt("i"));
}
END_TEST

START_TEST (ii_represents_two)
{
	ck_assert_uint_eq(2, convertToInt("ii"));
}
END_TEST

START_TEST (v_represents_five)
{
	ck_assert_uint_eq(5, convertToInt("v"));
}
END_TEST

START_TEST (single_letters_by_themseleves_represent_core_values)
{
	ck_assert_uint_eq(1, convertToInt("i"));
	ck_assert_uint_eq(5, convertToInt("v"));
	ck_assert_uint_eq(10, convertToInt("x"));
	ck_assert_uint_eq(50, convertToInt("l"));
	ck_assert_uint_eq(100, convertToInt("c"));
	ck_assert_uint_eq(500, convertToInt("d"));
	ck_assert_uint_eq(1000, convertToInt("m"));
}
END_TEST

START_TEST (iv_represents_four)
{
	ck_assert_uint_eq(4, convertToInt("iv"));
}
END_TEST

START_TEST (xix_represents_nineteen)
{
	ck_assert_uint_eq(19, convertToInt("xix"));
}
END_TEST

START_TEST (mmmcdlvi_represents_three_thousand_four_hundred_fifty_six)
{
	ck_assert_uint_eq(3456, convertToInt("mmmcdlvi"));
}
END_TEST

START_TEST (uppercase_letters_also_represent_things)
{
	ck_assert_uint_eq(1, convertToInt("I"));
	ck_assert_uint_eq(5, convertToInt("V"));
	ck_assert_uint_eq(10, convertToInt("X"));
	ck_assert_uint_eq(50, convertToInt("L"));
	ck_assert_uint_eq(100, convertToInt("C"));
	ck_assert_uint_eq(500, convertToInt("D"));
	ck_assert_uint_eq(1000, convertToInt("M"));
}
END_TEST

Suite * calculator_suite(void) {
	Suite *s;
	TCase *tc_core;

    s = suite_create("Calculator Tests");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, one_plus_one_is_two);
    tcase_add_test(tc_core, one_plus_two_is_three);
    tcase_add_test(tc_core, two_plus_two_is_four);
    tcase_add_test(tc_core, i_represents_one);
    tcase_add_test(tc_core, ii_represents_two);
    tcase_add_test(tc_core, v_represents_five);
    tcase_add_test(tc_core, single_letters_by_themseleves_represent_core_values);
    tcase_add_test(tc_core, iv_represents_four);
    tcase_add_test(tc_core, xix_represents_nineteen);
    tcase_add_test(tc_core, mmmcdlvi_represents_three_thousand_four_hundred_fifty_six);
    tcase_add_test(tc_core, uppercase_letters_also_represent_things);
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
