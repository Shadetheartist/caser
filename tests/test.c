#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include "../src/engine.h"
#include "../src/caser.h"

struct conversionTestData
{
  char *input;

  char *snake;
  char *dash;
  char *camel;
  char *pascal;
  char *title;
};

const struct conversionTestData testData[] = {

    {
        "", // input

        "", // snake
        "", // dash
        "", // camel
        "", // pascal
        "", // title
    },
    {
        "--__  ..", // input

        "", // snake
        "", // dash
        "", // camel
        "", // pascal
        "", // title
    },
    {
        "a b", // input

        "a_b", // snake
        "a-b", // dash
        "aB",  // camel
        "AB",  // pascal
        "A B", // title
    },
    {
        "ab cd", // input

        "ab_cd", // snake
        "ab-cd", // dash
        "abCd",  // camel
        "AbCd",  // pascal
        "Ab Cd", // title
    },
    {   // program does not currently parse existing camelCased or other naming-schemed strings
        "testCase", // input

        "testcase", // snake
        "testcase", // dash
        "testcase",  // camel
        "Testcase",  // pascal
        "Testcase", // title
    },
    {
        "   CE3_Battery Compartment - Battery Compartment.gcode   ", // input

        "ce3_battery_compartment_battery_compartment_gcode", // snake
        "ce3-battery-compartment-battery-compartment-gcode", // dash
        "ce3BatteryCompartmentBatteryCompartmentGcode",      // camel
        "Ce3BatteryCompartmentBatteryCompartmentGcode",      // pascal
        "Ce3 Battery Compartment Battery Compartment Gcode", // title
    },
    {0}};

// SNAKE TESTS
START_TEST(test_snake_case)
{
  Scheme scheme = SNAKE_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for (int i = 0; testData[i].input != 0; i++)
  {
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase, DELIMITERS), testData[i].snake);
  }
}
END_TEST

// DASH TESTS
START_TEST(test_dash_case)
{
  Scheme scheme = DASH_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for (int i = 0; testData[i].input != 0; i++)
  {
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase, DELIMITERS), testData[i].dash);
  }
}
END_TEST

// CAMEL TESTS
START_TEST(test_camel_case)
{
  Scheme scheme = CAMEL_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for (int i = 0; testData[i].input != 0; i++)
  {
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase, DELIMITERS), testData[i].camel);
  }
}
END_TEST

// PASCAL TESTS
START_TEST(test_pascal_case)
{
  Scheme scheme = PASCAL_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for (int i = 0; testData[i].input != 0; i++)
  {
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase, DELIMITERS), testData[i].pascal);
  }
}
END_TEST

// TITLE TESTS
START_TEST(test_title_case)
{
  Scheme scheme = TITLE_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for (int i = 0; testData[i].input != 0; i++)
  {
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase, DELIMITERS), testData[i].title);
  }
}
END_TEST

// FILE TESTS
START_TEST(test_snake_file_case)
{
  Scheme scheme = SNAKE_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  ck_assert_str_eq(convert("a test file", scheme, letterCase, FILE_MODE_DELIMITERS), "a_test_file");
  ck_assert_str_eq(convert("testFile.jpeg", scheme, letterCase, FILE_MODE_DELIMITERS), "testfile.jpeg");
  ck_assert_str_eq(convert("my test File.tmp.jpeg", scheme, letterCase, FILE_MODE_DELIMITERS), "my_test_file.tmp.jpeg");
}
END_TEST

// CASING TESTS
START_TEST(test_casing)
{
  ck_assert_str_eq(convert("Test Case", SNAKE_CASE_SCHEME, TO_LOWER_CASE, DELIMITERS), "test_case");
  ck_assert_str_eq(convert("Test Case", SNAKE_CASE_SCHEME, TO_UPPER_CASE, DELIMITERS), "TEST_CASE");
  ck_assert_str_eq(convert("Test Case", SNAKE_CASE_SCHEME, PRESERVE_CASE, DELIMITERS), "Test_Case");

  ck_assert_str_eq(convert("TeSt CaSe", NO_SCHEME, TO_LOWER_CASE, DELIMITERS), "test case");
  ck_assert_str_eq(convert("TeSt CaSe", NO_SCHEME, TO_UPPER_CASE, DELIMITERS), "TEST CASE");
  ck_assert_str_eq(convert("TeSt CaSe", NO_SCHEME, PRESERVE_CASE, DELIMITERS), "TeSt CaSe");
}
END_TEST

Suite *caser_suite(void)
{
  Suite *s;

  s = suite_create("Caser");

  TCase *tc_snake = tcase_create("Snake");
  tcase_add_test(tc_snake, test_snake_case);
  suite_add_tcase(s, tc_snake);

  TCase *tc_dash = tcase_create("Dash");
  tcase_add_test(tc_dash, test_dash_case);
  suite_add_tcase(s, tc_dash);

  TCase *tc_camel = tcase_create("Camel");
  tcase_add_test(tc_camel, test_snake_case);
  suite_add_tcase(s, tc_camel);

  TCase *tc_pascal = tcase_create("Pascal");
  tcase_add_test(tc_pascal, test_pascal_case);
  suite_add_tcase(s, tc_pascal);

  TCase *tc_title = tcase_create("Title");
  tcase_add_test(tc_title, test_title_case);
  suite_add_tcase(s, tc_title);

  TCase *tc_file_snake = tcase_create("File (Snake)");
  tcase_add_test(tc_file_snake, test_snake_file_case);
  suite_add_tcase(s, tc_file_snake);

  TCase *tc_casing = tcase_create("Casing");
  tcase_add_test(tc_casing, test_casing);
  suite_add_tcase(s, tc_casing);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = caser_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
