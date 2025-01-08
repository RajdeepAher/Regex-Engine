#ifndef TEST_LEXER_HH
#define TEST_LEXER_HH

#include <iostream>
#include <vector>
#include <string>
#include "../../src/lexer/lexer.hh" // Include the Lexer class definition
#include "../../src/tokens/tokens.hh"

// Helper function to check test results
void check(bool condition, const std::string& message);

// Test functions
void test_simple_re_lexing(Lexer& lexer);
void test_escaping_char(Lexer& lexer);
void test_escaping_get_tab(Lexer& lexer);
void test_escaping_wildcard(Lexer& lexer);
void test_get_comma(Lexer& lexer);
void test_comma_is_element(Lexer& lexer);
void test_match_start(Lexer& lexer);
void test_match_end(Lexer& lexer);
void test_fail_curly(Lexer& lexer);
void test_lexer_1(Lexer& lexer);

// Token-specific test functions
bool test_Asterisk();
bool test_NotToken();
bool test_Bracket();
bool test_Escape();

#endif // TEST_LEXER_HH