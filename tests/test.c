#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include "../src/engine.h"

struct testDatum {
  char *input;

  char *snake_lower;
  char *snake_upper;
  char *snake_preserve;
  
  char *camel_lower;
  char *camel_upper;
  char *camel_preserve;

  char *pascal_lower;
  char *pascal_upper;
  char *pascal_preserve;

  char *title_lower;
  char *title_upper;
  char *title_preserve;
};

const struct testDatum testData[] = {
  {
    "a", 
    "a", "A", "a",
    "a", "a", "a",
    "A", "A", "A",
    "A", "A", "A",
  },
  {
    "ABC", 
    "abc", "ABC", "ABC",
    "abc", "abc", "abc",
    "Abc", "Abc", "Abc",
    "Abc", "Abc", "Abc",
  },
  {
    "aBc", 
    "abc", "ABC", "aBc",
    "abc", "abc", "abc",
    "Abc", "Abc", "Abc",
    "Abc", "Abc", "Abc",
  },
  {
    "a b", 
    "a_b", "A_B", "a_b",
    "aB", "aB", "aB",
    "AB", "AB", "AB",
    "A B", "A B", "A B",
  },
  {
    "a Bc", 
    "a_bc", "A_BC", "a_Bc",
    "aBc", "aBc", "aBc",
    "ABc", "ABc", "ABc",
    "A Bc", "A Bc", "A Bc",
  },
  {
    "1", 
    "1", "1", "1",
    "1", "1", "1",
    "1", "1", "1",
    "1", "1", "1",
  },
  {
    "100", 
    "100", "100", "100",
    "100", "100", "100",
    "100", "100", "100",
    "100", "100", "100",
  },
  {
    "101aBc", 
    "101abc", "101ABC", "101aBc",
    "101abc", "101abc", "101abc",
    "101abc", "101abc", "101abc",
    "101abc", "101abc", "101abc",
  },
  {
    "___", 
    "", "", "",
    "", "", "",
    "", "", "",
    "", "", "",
  },
  {
    "   ", 
    "", "", "",
    "", "", "",
    "", "", "",
    "", "", "",
  },
  {
    "  a__Bc  ", 
    "a_bc", "A_BC", "a_Bc",
    "aBc", "aBc", "aBc",
    "ABc", "ABc", "ABc",
    "A Bc", "A Bc", "A Bc",
  },
  {
    "CE3_Battery Compartment - Battery Compartment.gcode ", 
    "ce3_battery_compartment_-_battery_compartment.gcode", "CE3_BATTERY_COMPARTMENT_-_BATTERY_COMPARTMENT.GCODE", "CE3_Battery_Compartment_-_Battery_Compartment.gcode",
    "ce3BatteryCompartment-BatteryCompartment.gcode", "ce3BatteryCompartment-BatteryCompartment.gcode", "ce3BatteryCompartment-BatteryCompartment.gcode", 
    "Ce3BatteryCompartment-BatteryCompartment.gcode", "Ce3BatteryCompartment-BatteryCompartment.gcode", "Ce3BatteryCompartment-BatteryCompartment.gcode", 
    "Ce3 Battery Compartment - Battery Compartment.gcode", "Ce3 Battery Compartment - Battery Compartment.gcode", "Ce3 Battery Compartment - Battery Compartment.gcode",
  },
  {0} 
};


// SNAKE TESTS
START_TEST(test_snake_case_lower)
{
  Scheme scheme = SNAKE_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].snake_lower);
  }
}
END_TEST

START_TEST(test_snake_case_upper)
{
  Scheme scheme = SNAKE_CASE_SCHEME;
  LetterCase letterCase = TO_UPPER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].snake_upper);
  }
}
END_TEST

START_TEST(test_snake_case_preserve)
{
  Scheme scheme = SNAKE_CASE_SCHEME;
  LetterCase letterCase = PRESERVE_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].snake_preserve);
  }
}
END_TEST


//CAMEL TESTS
START_TEST(test_camel_case_lower)
{
  Scheme scheme = CAMEL_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].camel_lower);
  }
}
END_TEST

START_TEST(test_camel_case_upper)
{
  Scheme scheme = CAMEL_CASE_SCHEME;
  LetterCase letterCase = TO_UPPER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].camel_upper);
  }
}
END_TEST

START_TEST(test_camel_case_preserve)
{
  Scheme scheme = CAMEL_CASE_SCHEME;
  LetterCase letterCase = PRESERVE_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].camel_preserve);
  }
}
END_TEST


//PASCAL TESTS
START_TEST(test_pascal_case_lower)
{
  Scheme scheme = PASCAL_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].pascal_lower);
  }
}
END_TEST

START_TEST(test_pascal_case_upper)
{
  Scheme scheme = PASCAL_CASE_SCHEME;
  LetterCase letterCase = TO_UPPER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].pascal_upper);
  }
}
END_TEST

START_TEST(test_pascal_case_preserve)
{
  Scheme scheme = PASCAL_CASE_SCHEME;
  LetterCase letterCase = PRESERVE_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].pascal_preserve);
  }
}
END_TEST


//TITLE TESTS
START_TEST(test_title_case_lower)
{
  Scheme scheme = TITLE_CASE_SCHEME;
  LetterCase letterCase = TO_LOWER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].title_lower);
  }
}
END_TEST

START_TEST(test_title_case_upper)
{
  Scheme scheme = TITLE_CASE_SCHEME;
  LetterCase letterCase = TO_UPPER_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].title_upper);
  }
}
END_TEST

START_TEST(test_title_case_preserve)
{
  Scheme scheme = TITLE_CASE_SCHEME;
  LetterCase letterCase = PRESERVE_CASE;

  for(int i = 0; testData[i].input != 0; i++){
    ck_assert_str_eq(convert(testData[i].input, scheme, letterCase), testData[i].title_preserve);
  }
}
END_TEST


Suite *caser_suite(void)
{
  Suite *s;

  s = suite_create("Caser");

  TCase *tc_snake = tcase_create("Snake");
  tcase_add_test(tc_snake, test_snake_case_lower);
  tcase_add_test(tc_snake, test_snake_case_upper);
  tcase_add_test(tc_snake, test_snake_case_preserve);
  suite_add_tcase(s, tc_snake);

  TCase *tc_camel = tcase_create("Camel");
  tcase_add_test(tc_camel, test_camel_case_lower);
  tcase_add_test(tc_camel, test_camel_case_upper);
  tcase_add_test(tc_camel, test_camel_case_preserve);
  suite_add_tcase(s, tc_camel);

  TCase *tc_pascal = tcase_create("Pascal");
  tcase_add_test(tc_pascal, test_pascal_case_lower);
  tcase_add_test(tc_pascal, test_pascal_case_upper);
  tcase_add_test(tc_pascal, test_pascal_case_preserve);
  suite_add_tcase(s, tc_pascal);

  TCase *tc_title = tcase_create("Title");
  tcase_add_test(tc_title, test_title_case_lower);
  tcase_add_test(tc_title, test_title_case_upper);
  tcase_add_test(tc_title, test_title_case_preserve);
  suite_add_tcase(s, tc_title);

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
