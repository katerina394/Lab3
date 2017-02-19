#include  < gtest/gtest.h>
#include "ArithmExp.h"
#include <iostream>
TEST(ArithmExp, can_convert_to_Polish_notation) {
    ArithmExp a("2+3*4");
    char exp[] = "2 3 4 *+";
    char* res = a.ReversePolishNotation();
    for (int i=0; exp[i] != 0; i++)
        EXPECT_EQ(exp[i], res[i]);
}
TEST(ArithmExp, can_convert_to_Polish_notation_an_expression_with_module) {
    ArithmExp a("|2+3|*4");
    char exp[] = "2 3 +||4 *";
    char* res = a.ReversePolishNotation();
    for (int i=0; exp[i] != 0; i++)
        EXPECT_EQ(exp[i], res[i]);
}
TEST(ArithmExp, can_convert_to_Polish_notation_an_expression_with_negative_numbers) {
    ArithmExp a("2+(-53)*4");
    char exp[] = "2 - 53 4 *+";
    char* res = a.ReversePolishNotation();
    for (int i=0; exp[i] != 0; i++)
        EXPECT_EQ(exp[i], res[i]);
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_one_operation) {
    ArithmExp a("2+3");
    EXPECT_EQ(5, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_two_operations) {
    ArithmExp a("2+3*4");
	std::cout << a.ReversePolishNotation() << std::endl;
	std::cout << a.Calc() << std::endl;
    EXPECT_EQ(14, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_pow) {
    ArithmExp a("2+3^2");
    EXPECT_EQ(11, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_brackets) {
    ArithmExp a("(2+3)^2");
    EXPECT_EQ(25, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_four_operations_and_brakets) {
    ArithmExp a("23+(2+3^2)*3");
    EXPECT_EQ(56, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_module) {
    ArithmExp a("2+|123|*2");
    EXPECT_EQ(248, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_div) {
    ArithmExp a("2+48/2");
    EXPECT_EQ(26, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_an_negative_number_1) {
    ArithmExp a("2+3*(-4)");
    EXPECT_EQ(-10, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_an_negative_number_2) {
    ArithmExp a("-3*4+2");
    EXPECT_EQ(-10, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_an_negative_number_3) {
    ArithmExp a("5*4+(-2*3+1)");
    EXPECT_EQ(15, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_an_negative_number_in_module) {
    ArithmExp a("5*4+(|-2|*3+1)");
    EXPECT_EQ(27, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_expression_in_module) {
    ArithmExp a("5*4+|-2*3+1|");
    EXPECT_EQ(25, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_nested_modules_1) {
    ArithmExp a("5*4+|3+|-2|*3+1|");
    EXPECT_EQ(30, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_nested_modules_2) {
    ArithmExp a("5*4+||-2|*3+1|");
    EXPECT_EQ(27, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_nested_modules_3) {
    ArithmExp a("||3|+|-7|+|18||");
    EXPECT_EQ(28, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_right_associative_operation) {
    ArithmExp a("2^2^3");
    EXPECT_EQ(256, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_parametr) {
    ArithmExp a("a+1");
    a.InputParametr('a', 5);
    EXPECT_EQ(6, a.Calc());
}
TEST(ArithmExp, throw_when_there_are_not_enough_parametrs) {
    ArithmExp a("a+b");
    a.InputParametr('a', 155);
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_parametr_with_negative_value) {
    ArithmExp a("a+b");
    a.InputParametr('a', -52);
    a.InputParametr('b', 57);
    EXPECT_EQ(5, a.Calc());
}
TEST(ArithmExp, can_calculate_arifmetic_expression_with_parametr_with_negative_value_in_module) {
    ArithmExp a("|a|+|b|");
    a.InputParametr('a', -52);
    a.InputParametr('b', 57);
    EXPECT_EQ(109, a.Calc());
}
TEST(ArithmExp, throw_when_there_are_not_enough_brackets) {
    ArithmExp a("(2+3");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_there_are_not_enough_module) {
    ArithmExp a("|2+3");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_the_expression_is_incorrect_1) {
    ArithmExp a("2+3(5)*7");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_the_expression_is_incorrect_2) {
    ArithmExp a("2+8+||");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_the_expression_is_incorrect_3) {
    ArithmExp a("2+8+()");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_the_expression_is_incorrect_4) {
    ArithmExp a("--2");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_there_are_not_enough_operands) {
    ArithmExp a("2+");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_there_is_no_operands) {
    ArithmExp a("+");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_there_is_div_by_zero) {
    ArithmExp a("2+8/0");
    EXPECT_ANY_THROW(a.Calc());
}
TEST(ArithmExp, throw_when_the_expression_contains_invalid_characters) {
    ArithmExp a("2+3%8");
    EXPECT_ANY_THROW(a.Calc());
}
