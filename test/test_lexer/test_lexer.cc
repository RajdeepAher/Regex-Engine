#include "test_lexer.hh"
#include <string>
#include <iostream>
using namespace std;
// Helper function to check test results
void check(bool condition, const string& message) {
    if (condition) {
        cout << "[PASS] " << message << endl;
    } else {
        cout << "[FAIL] " << message << endl;
    }
}

// Test functions
void test_simple_re_lexing(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("a");
    check(tokens.size() == 1, "Simple re lexing - token count");
    check(dynamic_cast<ElementToken*>(tokens[0])->char_ == "a", "Simple re lexing - token char");
}

void test_escaping_char(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("a\\\\a\\t\\.");
    //check(tokens.size() == 4, "Escaping char - token count");
    check(dynamic_cast<ElementToken*>(tokens[1])->char_ == "\\", "Escaping char - second token char");
}

void test_escaping_get_tab(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("a\\h\\t");
    check(tokens.size() == 3, "Escaping get tab - token count");
    check(dynamic_cast<ElementToken*>(tokens[2])->char_ == "\t", "Escaping get tab - tab character");
}

void test_escaping_wildcard(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("\\.");
    check(tokens.size() == 1, "Escaping wildcard - token count");
    check(dynamic_cast<ElementToken*>(tokens[0])->char_ == ".", "Escaping wildcard - token char");
}

void test_get_comma(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("a{3,5}");
    //check(tokens.size() == 5, "Get comma - token count");
    // Assuming you want to test the comma specifically:
    check(dynamic_cast<Comma*>(tokens[3]) != nullptr, "Get comma - comma token");
}

void test_comma_is_element(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("a,");
    check(tokens.size() == 2, "Comma is element - token count");
    check(dynamic_cast<ElementToken*>(tokens[1]) != nullptr, "Comma is element - second token is ElementToken");
}

void test_match_start(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("^a");
    check(tokens.size() == 2, "Match start - token count");
    check(dynamic_cast<Start*>(tokens[0]) != nullptr, "Match start - first token is Start");
}

void test_match_end(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("fdsad$cs$");
    //check(tokens.size() == 3, "Match end - token count");
    check(dynamic_cast<End*>(tokens[tokens.size() - 1]) != nullptr, "Match end - last token is End");
}

void test_fail_curly(Lexer& lexer) {
    try {
        lexer.scan("advfe{a}");
        cout << "[FAIL] Fail curly - exception expected" << endl;
    } catch (const exception& e) {
        cout << "[PASS] Fail curly - exception caught: " << e.what() << endl;
    }
}

void test_lexer_1(Lexer& lexer) {
    vector<Token*> tokens = lexer.scan("-\\\\\\/\\s~");
    check(tokens.size() == 5, "Lexer 1 - token count");
    check(dynamic_cast<Dash*>(tokens[0]) != nullptr, "Lexer 1 - first token is Dash");
    check(dynamic_cast<ElementToken*>(tokens[1]) != nullptr, "Lexer 1 - second token is ElementToken");
    check(dynamic_cast<ElementToken*>(tokens[2]) != nullptr, "Lexer 1 - third token is ElementToken");
    check(dynamic_cast<SpaceToken*>(tokens[3]) != nullptr, "Lexer 1 - fourth token is SpaceToken");
    check(dynamic_cast<ElementToken*>(tokens[4]) != nullptr, "Lexer 1 - fifth token is ElementToken");
}



int main() {
    Lexer lexer;

    // Run all lexer tests
    test_simple_re_lexing(lexer);
    test_escaping_char(lexer);
    test_escaping_get_tab(lexer);
    test_escaping_wildcard(lexer);
    test_get_comma(lexer);
    test_comma_is_element(lexer);
    test_match_start(lexer);
    test_match_end(lexer);
    test_fail_curly(lexer);
    test_lexer_1(lexer);

    return 0;
}