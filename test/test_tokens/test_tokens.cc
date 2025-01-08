#include "test_tokens.hh"
#include <iostream>
#include <typeinfo>
#include <cassert>
#include "../../src/tokens/tokens.hh"

bool test_Asterisk() {
    // Test for Asterisk class
    if (is_base_of<ZeroOrMore, Asterisk>::value) {
        cout << "[PASS] Asterisk is a subclass of ZeroOrMore." << endl;
    } else {
        cout << "[FAIL] Asterisk is NOT a subclass of ZeroOrMore!" << endl;
        return false;
    }

    Asterisk a;
    if (&a != nullptr) {
        cout << "[PASS] Asterisk object created successfully." << endl;
    } else {
        cout << "[FAIL] Failed to create Asterisk object!" << endl;
        return false;
    }

    if (typeid(a) == typeid(Asterisk)) {
        cout << "[PASS] Asterisk object is of type Asterisk." << endl;
    } else {
        cout << "[FAIL] Asterisk object is NOT of type Asterisk!" << endl;
        return false;
    }

    return true;
}

bool test_NotToken() {
    // Test for NotToken class
    if (is_base_of<Token, NotToken>::value) {
        cout << "[PASS] NotToken is a subclass of Token." << endl;
    } else {
        cout << "[FAIL] NotToken is NOT a subclass of Token!" << endl;
        return false;
    }

    NotToken nt("^");
    if (&nt != nullptr) {
        cout << "[PASS] NotToken object created successfully." << endl;
    } else {
        cout << "[FAIL] Failed to create NotToken object!" << endl;
        return false;
    }

    if (nt.char_ == "^") {
        cout << "[PASS] NotToken char is correctly set to '^'." << endl;
    } else {
        cout << "[FAIL] NotToken char is NOT set to '^'!" << endl;
        return false;
    }

    return true;
}

bool test_Bracket() {
    // Test for Bracket and its derived classes
    Bracket br;
    if (&br != nullptr) {
        cout << "[PASS] Bracket object created successfully." << endl;
    } else {
        cout << "[FAIL] Failed to create Bracket object!" << endl;
        return false;
    }

    LeftBracket lb;
    if (&lb != nullptr) {
        cout << "[PASS] LeftBracket object created successfully." << endl;
    } else {
        cout << "[FAIL] Failed to create LeftBracket object!" << endl;
        return false;
    }

    RightBracket rb;
    if (&rb != nullptr) {
        cout << "[PASS] RightBracket object created successfully." << endl;
    } else {
        cout << "[FAIL] Failed to create RightBracket object!" << endl;
        return false;
    }

    return true;
}

bool test_Escape() {
    // Test for Escape class
    Escape escape(" ");
    if (&escape != nullptr) {
        cout << "[PASS] Escape object created successfully." << endl;
    } else {
        cout << "[FAIL] Failed to create Escape object!" << endl;
        return false;
    }

    return true;
}

bool test_Tokens() {

    // Store individual test results
    bool asteriskTestPassed = test_Asterisk();
    bool notTokenTestPassed = test_NotToken();
    bool bracketTestPassed = test_Bracket();
    bool escapeTestPassed = test_Escape();

    // Use assertions to validate results
    assert(asteriskTestPassed && "test_Asterisk failed.");
    assert(notTokenTestPassed && "test_NotToken failed.");
    assert(bracketTestPassed && "test_Bracket failed.");
    assert(escapeTestPassed && "test_Escape failed.");

    //cout << "All token tests passed!" << endl;
    return true;
}

int main() {
    bool allTestsPassed = true;

    if (!test_Asterisk()) {
        cerr << "test_Asterisk failed!" << endl;
        allTestsPassed = false;
    }

    if (!test_NotToken()) {
        cerr << "test_NotToken failed!" << endl;
        allTestsPassed = false;
    }

    if (!test_Bracket()) {
        cerr << "test_Bracket failed!" << endl;
        allTestsPassed = false;
    }

    if (!test_Escape()) {
        cerr << "test_Escape failed!" << endl;
        allTestsPassed = false;
    }

    if (!test_Tokens()) {
        cerr << "test_Tokens failed!" << endl;
        allTestsPassed = false;
    }

    if (allTestsPassed) {
        cout << "All tokens tests passed!" << endl;
        return 0;
    } else {
        cerr << "Some tokens tests failed!" << endl;
        return 1;
    }
}