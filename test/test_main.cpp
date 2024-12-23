// main.cpp
#include "test_lexer.cpp"
#include "test_re_ast.cpp"

int main() {
    Lexer lexer;
    
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

    test_ASTNode();
    test_RE();
    //test_NotNode();
    test_LeafNode();
    test_WildcardElement();
    test_SpaceElement();
    test_RangeElement_positive_logic();
    test_RangeElement_negative_logic();


    bool result = true;

    result &= test_Asterisk();
    result &= test_NotToken();
    result &= test_Bracket();
    result &= test_Escape();

    if (result) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << "Some tests failed!" << std::endl;
    }

    return 0;
}
