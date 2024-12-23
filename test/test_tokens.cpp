
#pragma once

#include "../src/lexer.cpp"

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

