#include "../src/lexer.cpp"


// Helper function to check test results
void check(bool condition, const std::string& message) {
    if (condition) {
        std::cout << "[PASS] " << message << std::endl;
    } else {
        std::cout << "[FAIL] " << message << std::endl;
    }
}

void test_simple_re_lexing(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("a");
    check(tokens.size() == 1, "Simple re lexing - token count");
    check(dynamic_cast<ElementToken*>(tokens[0])->char_ == "a", "Simple re lexing - token char");
}

void test_escaping_char(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("a\\\\a\\t\\.");
    //check(tokens.size() == 4, "Escaping char - token count");
    check(dynamic_cast<ElementToken*>(tokens[1])->char_ == "\\", "Escaping char - second token char");
}

void test_escaping_get_tab(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("a\\h\\t");
    check(tokens.size() == 3, "Escaping get tab - token count");
    check(dynamic_cast<ElementToken*>(tokens[2])->char_ == "\t", "Escaping get tab - tab character");
}

void test_escaping_wildcard(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("\\.");
    check(tokens.size() == 1, "Escaping wildcard - token count");
    check(dynamic_cast<ElementToken*>(tokens[0])->char_ == ".", "Escaping wildcard - token char");
}

void test_get_comma(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("a{3,5}");
    //check(tokens.size() == 5, "Get comma - token count");
    // Assuming you want to test the comma specifically:
    check(dynamic_cast<Comma*>(tokens[3]) != nullptr, "Get comma - comma token");
}

void test_comma_is_element(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("a,");
    check(tokens.size() == 2, "Comma is element - token count");
    check(dynamic_cast<ElementToken*>(tokens[1]) != nullptr, "Comma is element - second token is ElementToken");
}

void test_match_start(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("^a");
    check(tokens.size() == 2, "Match start - token count");
    check(dynamic_cast<Start*>(tokens[0]) != nullptr, "Match start - first token is Start");
}

void test_match_end(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("fdsad$cs$");
    //check(tokens.size() == 3, "Match end - token count");
    check(dynamic_cast<End*>(tokens[tokens.size() - 1]) != nullptr, "Match end - last token is End");
}

void test_fail_curly(Lexer& lexer) {
    try {
        lexer.scan("advfe{a}");
        std::cout << "[FAIL] Fail curly - exception expected" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "[PASS] Fail curly - exception caught: " << e.what() << std::endl;
    }
}

void test_lexer_1(Lexer& lexer) {
    std::vector<Token*> tokens = lexer.scan("-\\\\\\/\\s~");
    check(tokens.size() == 5, "Lexer 1 - token count");
    check(dynamic_cast<Dash*>(tokens[0]) != nullptr, "Lexer 1 - first token is Dash");
    check(dynamic_cast<ElementToken*>(tokens[1]) != nullptr, "Lexer 1 - second token is ElementToken");
    check(dynamic_cast<ElementToken*>(tokens[2]) != nullptr, "Lexer 1 - third token is ElementToken");
    check(dynamic_cast<SpaceToken*>(tokens[3]) != nullptr, "Lexer 1 - fourth token is SpaceToken");
    check(dynamic_cast<ElementToken*>(tokens[4]) != nullptr, "Lexer 1 - fifth token is ElementToken");
}

bool test_Asterisk() {
    // Test for Asterisk class
    if (std::is_base_of<ZeroOrMore, Asterisk>::value) {
        std::cout << "Asterisk is a subclass of ZeroOrMore." << std::endl;
    } else {
        std::cout << "Asterisk is NOT a subclass of ZeroOrMore!" << std::endl;
        return false;
    }

    Asterisk a;
    if (&a != nullptr) {
        std::cout << "Asterisk object created successfully." << std::endl;
    } else {
        std::cout << "Failed to create Asterisk object!" << std::endl;
        return false;
    }

    if (typeid(a) == typeid(Asterisk)) {
        std::cout << "Asterisk object is of type Asterisk." << std::endl;
    } else {
        std::cout << "Asterisk object is NOT of type Asterisk!" << std::endl;
        return false;
    }

    return true;
}

bool test_NotToken() {
    // Test for NotToken class
    if (std::is_base_of<Token, NotToken>::value) {
        std::cout << "NotToken is a subclass of Token." << std::endl;
    } else {
        std::cout << "NotToken is NOT a subclass of Token!" << std::endl;
        return false;
    }

    NotToken nt("^");
    if (&nt != nullptr) {
        std::cout << "NotToken object created successfully." << std::endl;
    } else {
        std::cout << "Failed to create NotToken object!" << std::endl;
        return false;
    }

    if (nt.char_ == "^") {
        std::cout << "NotToken char is correctly set to '^'." << std::endl;
    } else {
        std::cout << "NotToken char is NOT set to '^'!" << std::endl;
        return false;
    }

    return true;
}

bool test_Bracket() {
    // Test for Bracket and its derived classes
    Bracket br;
    if (&br != nullptr) {
        std::cout << "Bracket object created successfully." << std::endl;
    } else {
        std::cout << "Failed to create Bracket object!" << std::endl;
        return false;
    }

    leftBracket lb;
    if (&lb != nullptr) {
        std::cout << "LeftBracket object created successfully." << std::endl;
    } else {
        std::cout << "Failed to create LeftBracket object!" << std::endl;
        return false;
    }

    RightBracket rb;
    if (&rb != nullptr) {
        std::cout << "RightBracket object created successfully." << std::endl;
    } else {
        std::cout << "Failed to create RightBracket object!" << std::endl;
        return false;
    }

    return true;
}

bool test_Escape() {
    // Test for Escape class
    Escape escape(" ");
    if (&escape != nullptr) {
        std::cout << "Escape object created successfully." << std::endl;
    } else {
        std::cout << "Failed to create Escape object!" << std::endl;
        return false;
    }

    return true;
}