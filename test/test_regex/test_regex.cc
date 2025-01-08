#include "test_regex.hh"

// Utility function to print [PASS] or [FAIL] messages
void check(bool condition, const string& message) {
    if (condition) {
        cout << "[PASS] " << message << endl;
    } else {
        string err = " [FAIL] " + message;
        throw runtime_error(err);
    }
}



void testSimplest(RegexEngine& reng) {
    auto result = reng.match("a", "a");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testSimplest - matched");
    check(consumed == 1, "testSimplest - consumed");
}

void testSimplestWithWildcard(RegexEngine& reng) {
    auto result = reng.match(".", "a");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testSimplestWithWildcard - matched");
    check(consumed == 1, "testSimplestWithWildcard - consumed");
}

void testSimplestButLonger(RegexEngine& reng) {
    auto result = reng.match("a.c", "abc");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testSimplestButLonger - matched");
    check(consumed == 3, "testSimplestButLonger - consumed");
}

void testWildcard(RegexEngine& reng) {
    auto result = reng.match(".*a", "aa");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testWildcard - matched");
    check(consumed == 2, "testWildcard - consumed");
}

void testBacktracking(RegexEngine& reng) {
    auto result = reng.match("a*a", "aaaa");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testBacktracking - matched");
    check(consumed == 4, "testBacktracking - consumed");
}

void testOr(RegexEngine& reng) {
    auto result = reng.match("a.*|b", "b");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testOr - matched");
    check(consumed == 1, "testOr - consumed");
}

void testOrNoMatch(RegexEngine& reng) {
    auto result = reng.match("^a|b$", "c");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == false, "testOrNoMatch - matched");
}

void testOrNoMatchWithBT(RegexEngine& reng) {
    auto result = reng.match("a|b", "c");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == false, "testOrNoMatchWithBT - matched");
}

void testBTNoMatch(RegexEngine& reng) {
    auto result = reng.match("a{5}a", "aaaaa");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == false, "testBTNoMatch - matched");
}

void testMatchGroupZeroOrMore(RegexEngine& reng) {
    auto result = reng.match("(a)*", "aa");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testMatchGroupZeroOrMore - matched");
    check(consumed == 2, "testMatchGroupZeroOrMore - consumed");
}

void testFailGroupOneOrMore(RegexEngine& reng) {
    auto result = reng.match("^(a)+", "b");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == false, "testFailGroupOneOrMore - matched");
}

void testComplexMatch(RegexEngine& reng) {
    auto result = reng.match("^(a|b+c)?[n-z]{2}", "axx");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testComplexMatch - matched");
}

void testComplexMatch2(RegexEngine& reng) {
    auto result = reng.match("^(a|b+c)?[n-z]{2}", "xx");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testComplexMatch2 - matched");
}

void testMatchMailSimple(RegexEngine& reng) {
    auto result = reng.match(R"((.*@.*\.(com|it)))", "vr@gmail.com");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testMatchMailSimple - matched");
}

void testBtIndexLeaf(RegexEngine& reng) {
    auto result = reng.match(R"(^aaaa.*a$)", "aaaaa");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testBtIndexLeaf - matched");
}

void testBtIndexOr(RegexEngine& reng) {
    auto result = reng.match(R"(^x(a|b)?bc$)", "xbc");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testBtIndexOr - matched");
}

void testBtIndexGroup(RegexEngine& reng) {
    auto result = reng.match(R"(^x(a)?ac$)", "xac");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testBtIndexGroup - matched");
}

void testMatchOrLeft(RegexEngine& reng) {
    auto result = reng.match("na|nb", "na");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testMatchOrLeft - matched");
}

void testMatchOrRight(RegexEngine& reng) {
    auto result = reng.match("na|nb", "nb");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testMatchOrRight - matched");
}

void testMatchOrRightAtStartEnd(RegexEngine& reng) {
    auto result = reng.match("^na|nb$", "nb");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testMatchOrRightAtStartEnd - matched");
}

void testNoMatchAfterEnd(RegexEngine& reng) {
    auto result = reng.match("^na|nb$", "nb ");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == false, "testNoMatchAfterEnd - matched");
}

void testMatchSequenceWithStartEndCorrectly(RegexEngine& reng) {
    // Test case 1: Match 'a' at the start
    {
        auto result = reng.match("^a|b$", "a  ");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSequenceWithStartEndCorrectly - Test case 1: Match 'a' at the start");
    }

    // Test case 2: No match due to leading space
    {
        auto result = reng.match("^a|b$", " a  ");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == false, "testMatchSequenceWithStartEndCorrectly - Test case 2: No match due to leading space");
    }

    // Test case 3: Match 'b' at the end
    {
        auto result = reng.match("^a|b$", "  b");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSequenceWithStartEndCorrectly - Test case 3: Match 'b' at the end");
    }

    // Test case 4: No match due to trailing space after 'b'
    {
        auto result = reng.match("^a|b$", "  b ");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == false, "testMatchSequenceWithStartEndCorrectly - Test case 4: No match due to trailing space after 'b'");
    }
}

void testComplexMatch3(RegexEngine& reng) {
    auto result = reng.match("a(b|[c-n])+b{3}.{2}", "ahhbbbbbb");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testComplexMatch3 - matched");
}

void testBitLessComplexMatch3(RegexEngine& reng) {
    auto result = reng.match("a(b|[c-n])+b{3}", "ahhbbbbbb");
    bool matched;
    int consumed;
    vector<deque<Match>> all_matches;
    tie(matched, consumed, all_matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testBitLessComplexMatch3 - matched");
}

void testUnescapedSpecialCh(RegexEngine& reng) {
    try {
        auto result = reng.match("$a^", "aa");
        // If no exception is thrown, the test fails
        check(false, "testUnescapedSpecialCh - No exception was thrown for unescaped special characters");
    } catch (const exception& e) {
        // Expected behavior: an exception is thrown
        check(true, "testUnescapedSpecialCh - Exception thrown for unescaped special characters");
    } catch (...) {
        // Unexpected exception type
        check(false, "testUnescapedSpecialCh - Unexpected exception type caught");
    }
}

void testVariousEmails(RegexEngine& reng) {
    // Test case 1: Valid Hotmail.it email
    {
        auto result = reng.match(".*@(gmail|hotmail)\\.(com|it)", "baa.aa@hotmail.it");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testVariousEmails - Test case 1: Valid Hotmail.it email");
    }

    // Test case 2: Valid Gmail.com email
    {
        auto result = reng.match(".*@(gmail|hotmail)\\.(com|it)", "baa.aa@gmail.com");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testVariousEmails - Test case 2: Valid Gmail.com email");
    }

    // Test case 3: Invalid email with an extra character in the domain
    {
        auto result = reng.match(".*@(gmail|hotmail)\\.(com|it)", "baa.aa@hotmaila.com");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == false, "testVariousEmails - Test case 3: Invalid email with an extra character in the domain");
    }
}

void testMatchEmpty(RegexEngine& reng) {
    // Test case 1: Matching an empty string with '^$'
    {
        auto result = reng.match("^$", "");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchEmpty - Test case 1: '^$' matches an empty string");
    }

    // Test case 2: Matching an empty string with '$'
    {
        auto result = reng.match("$", "");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchEmpty - Test case 2: '$' matches an empty string");
    }

    // Test case 3: Matching an empty string with '^'
    {
        auto result = reng.match("^", "");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchEmpty - Test case 3: '^' matches an empty string");
    }
}

void testMatchSpace(RegexEngine& reng) {
    // Test case 1: Matching space character
    {
        auto result = reng.match("\\s", " ");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSpace - Test case 1: '\\s' matches space");
    }

    // Test case 2: Matching tab character
    {
        auto result = reng.match("\\s", "\t");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSpace - Test case 2: '\\s' matches tab");
    }

    // Test case 3: Matching carriage return
    {
        auto result = reng.match("\\s", "\r");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSpace - Test case 3: '\\s' matches carriage return");
    }

    // Test case 4: Matching form feed
    {
        auto result = reng.match("\\s", "\f");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSpace - Test case 4: '\\s' matches form feed");
    }

    // Test case 5: Matching new line
    {
        auto result = reng.match("\\s", "\n");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSpace - Test case 5: '\\s' matches new line");
    }

    // Test case 6: Matching vertical tab
    {
        auto result = reng.match("\\s", "\v");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSpace - Test case 6: '\\s' matches vertical tab");
    }
}

void testMatchSpace2(RegexEngine& reng) {
    // Test case 1: Matching one or more whitespace characters
    {
        auto result = reng.match("\\s+", "\r\t\n \f \v");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == true, "testMatchSpace2 - Test case 1: '\\s+' matches one or more whitespace characters");
    }

    // Test case 2: Matching exactly one whitespace character (with boundaries)
    {
        auto result = reng.match("^\\s$", "\r\t");
        bool matched;
        int consumed;
        vector<deque<Match>> all_matches;
        tie(matched, consumed, all_matches) = result;

        check(matched == false, "testMatchSpace2 - Test case 2: '^\\s$' does not match multiple whitespace characters");
    }
}

void testReturnMatchesSimple(RegexEngine& reng) {
    // Test case 1: Matching 'a' followed by a whitespace character and returning the matches
    {
        auto result = reng.match("a\\s", "a ", true); // Assuming return_matches is implemented in your match function
        bool matched;
        int consumed;
        vector<deque<Match>> matches;
        tie(matched, consumed, matches) = result;

        check(matched == true, "testReturnMatchesSimple - Test case 1: Matched 'a' followed by whitespace");
        check(matches.size() == 1, "testReturnMatchesSimple - Test case 1: One match should be found");
        check(matches[0].size() == 1, "testReturnMatchesSimple - Test case 1: The first match should have only one group");
    }
}

void testReturnMatchesTwo(RegexEngine& reng) {
    // Test case 1: Matching 'a' followed by one or more 'b' characters and ending with 'a'
    {
        auto result = reng.match("a(b)+a", "abba", true); // Assuming return_matches is implemented in your match function
        bool matched;
        int consumed;
        vector<deque<Match>> matches;
        tie(matched, consumed, matches) = result;

        check(matched == true, "testReturnMatchesTwo - Test case 1: Matched 'a' followed by one or more 'b' characters and ending with 'a'");
        check(matches.size() == 1, "testReturnMatchesTwo - Test case 1: One match should be found");
        check(matches[0].size() == 2, "testReturnMatchesTwo - Test case 1: The match should have two groups: 'b' and the entire match");
    }
}

void testNonCapturingGroup(RegexEngine& reng) {
    // Test case 1: Matching 'a' followed by one or more 'b' characters in a non-capturing group and ending with 'a'
    {
        auto result = reng.match("a(?:b)+a", "abba", true); // Assuming return_matches is implemented in your match function
        bool matched;
        int consumed;
        vector<deque<Match>> matches;
        tie(matched, consumed, matches) = result;

        check(matched == true, "testNonCapturingGroup - Test case 1: Matched 'a' followed by one or more 'b' characters in a non-capturing group and ending with 'a'");
        check(matches.size() == 1, "testNonCapturingGroup - Test case 1: One match should be found");
        check(matches[0].size() == 1, "testNonCapturingGroup - Test case 1: The match should have one group, excluding the non-capturing group");
    }
}

void testContinueAfterMatchAndReturnMatchesSimple(RegexEngine& reng) {
    string str = "abba";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with continue_after_match set to true and return_matches set to true
    auto result = reng.match("a", str, true, true);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testContinueAfterMatchAndReturnMatchesSimple - Matched 'a' in 'abba'");
    check(consumed == str.length(), "testContinueAfterMatchAndReturnMatchesSimple - The entire string should be consumed");
    check(matches.size() == 2, "testContinueAfterMatchAndReturnMatchesSimple - Two matches should be found");
    check(matches[0].size() == 1, "testContinueAfterMatchAndReturnMatchesSimple - The first match should have one group");
    check(matches[1].size() == 1, "testContinueAfterMatchAndReturnMatchesSimple - The second match should have one group");
    check(matches[0][0].match == "a", "testContinueAfterMatchAndReturnMatchesSimple - The first match should be 'a'");
    check(matches[1][0].match == "a", "testContinueAfterMatchAndReturnMatchesSimple - The second match should be 'a'");
}

void testContinueAfterMatchAndReturnMatches2(RegexEngine& reng) {
    string str = "abbai";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with continue_after_match set to true and return_matches set to true
    auto result = reng.match("a", str, true, true);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(consumed == str.length() - 1, "testContinueAfterMatchAndReturnMatches2 - The string should be consumed up to the second-to-last character");
    check(matches.size() == 2, "testContinueAfterMatchAndReturnMatches2 - Two matches should be found");
    check(matches[0].size() == 1, "testContinueAfterMatchAndReturnMatches2 - The first match should have one group");
    check(matches[1].size() == 1, "testContinueAfterMatchAndReturnMatches2 - The second match should have one group");
    check(matches[0][0].match == "a", "testContinueAfterMatchAndReturnMatches2 - The first match should be 'a'");
    check(matches[1][0].match == "a", "testContinueAfterMatchAndReturnMatches2 - The second match should be 'a'");
}

void testQuestionMark(RegexEngine& reng) {
    string str1 = "http://";
    string str2 = "https://";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Test case 1: Matching "http://" using the regex "https?://"
    auto result1 = reng.match("https?://", str1, true, true);
    tie(matched, consumed, matches) = result1;
    check(matched == true, "testQuestionMark - Test case 1: Matched 'http://' using 'https?://'");

    // Test case 2: Matching "https://" using the regex "https?://"
    auto result2 = reng.match("https?://", str2, true, true);
    tie(matched, consumed, matches) = result2;
    check(matched == true, "testQuestionMark - Test case 2: Matched 'https://' using 'https?://'");
}

void testEngine1(RegexEngine& reng) {
    try {
        // Attempting to match an invalid regex pattern
        string str = "";
        auto result = reng.match("$^", str, true, true);
        bool matched;
        int consumed;
        vector<deque<Match>> matches;
        tie(matched, consumed, matches) = result;

        // If no exception is thrown, fail the test
        check(false, "testEngine1 - Exception was not thrown for invalid regex pattern");
    } catch (const exception& e) {
        // Expected exception caught, the test passes
        check(true, "testEngine1 - Exception caught for invalid regex pattern");
    }
}

void testEngine2(RegexEngine& reng) {
    string regex = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";  // Email regex pattern

    // Test case 1: Valid email address
    string mail1 = "lorenzo.felletti@mail.com";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;
    auto result1 = reng.match(regex, mail1);
    tie(matched, consumed, matches) = result1;
    check(matched == true, "testEngine2 - Test case 1: Valid email address matched");
    check(consumed == mail1.length(), "testEngine2 - Test case 1: Entire email address should be consumed");

    // Test case 2: Invalid email address (wrong domain part)
    string mail2 = "lorenzo.felletti@mail.c";
    auto result2 = reng.match(regex, mail2);
    tie(matched, consumed, matches) = result2;
    check(matched == false, "testEngine2 - Test case 2: Invalid email address (wrong domain part) should not match");

    // Test case 3: Invalid email address (missing @ symbol)
    string mail3 = "lorenzo.fellettimail.com";
    auto result3 = reng.match(regex, mail3);
    tie(matched, consumed, matches) = result3;
    check(matched == false, "testEngine2 - Test case 3: Invalid email address (missing @ symbol) should not match");

    // Test case 4: Invalid email address (contains invalid characters)
    string mail4 = "lorenz^^o.felletti@mymail.com";
    auto result4 = reng.match(regex, mail4);
    tie(matched, consumed, matches) = result4;
    check(matched == false, "testEngine2 - Test case 4: Invalid email address (contains invalid characters) should not match");

    // Test case 5: Another valid email address
    string mail5 = "lorenz0.%+-@mymail.com";
    auto result5 = reng.match(regex, mail5);
    tie(matched, consumed, matches) = result5;
    check(matched == true, "testEngine2 - Test case 5: Another valid email address matched");
}

void testEngine3(RegexEngine& reng) {
    string str = "lorem ipsum";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Test matching the character 'm' in the string "lorem ipsum"
    auto result = reng.match("m", str, true, true);  // continue_after_match set to true
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testEngine3 - Matched 'm' in 'lorem ipsum'");
    check(consumed == str.length(), "testEngine3 - The entire string should be consumed");
}

void testEngine4(RegexEngine& reng) {
    string str = "lorem ipsum";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Test matching the character 'm' in the string "lorem ipsum"
    auto result = reng.match("m", str, true, true);  // continue_after_match and return_matches set to true
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testEngine4 - Matched 'm' in 'lorem ipsum'");
    check(consumed == str.length(), "testEngine4 - The entire string should be consumed");
    check(matches.size() == 2, "testEngine4 - Two matches should be found");
    check(matches[0][0].match == "m", "testEngine4 - The first match should be 'm'");
    check(matches[1][0].match == "m", "testEngine4 - The second match should be 'm'");
}

void testEngine5(RegexEngine& reng) {
    string match_1 = "lor.fel@ah.ha";
    string match_2 = "fel.log@ha.ah";
    string str = match_1 + " " + match_2;
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Test matching email-like patterns in the string
    auto result = reng.match("[a-z.]+@[a-z]+\\.[a-z]{2}", str, true, true); // continue_after_match and return_matches set to true
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testEngine5 - Matched email-like patterns in the string");
    check(consumed == str.length(), "testEngine5 - The entire string should be consumed");
    check(matches.size() == 2, "testEngine5 - Two matches should be found");
    check(matches[0][0].match == match_1, "testEngine5 - The first match should be 'lor.fel@ah.ha'");
    check(matches[1][0].match == match_2, "testEngine5 - The second match should be 'fel.log@ha.ah'");
}

void testEngine6(RegexEngine& reng) {
    bool matched;
    int consumed;

    // Test case 1: Matching with an escaped backslash in character class
    {
        auto result = reng.match("[\\abc]", "\\");
        tie(matched, consumed, ignore) = result;  // Ignore matches as they aren't used in this case
        check(matched == false, "testEngine6 - Test case 1: No match for escaped backslash in character class");
        check(consumed == 0, "testEngine6 - Test case 1: No characters should be consumed");
    }

    // Test case 2: Correct matching with properly escaped backslash in the regex
    {
        auto result = reng.match("[\\\\abc]", "\\"); // Escaping backslash in C++ requires double \\ in the string
        tie(matched, ignore, ignore) = result;      // Ignore matches and consumed as they aren't tested here
        check(matched == true, "testEngine6 - Test case 2: Matched properly escaped backslash");
    }
}

void testEngine7(RegexEngine& reng) {
    bool matched;

    // Test case: Complex regex with groups, optional and repeated patterns
    {
        auto result = reng.match("(a)+(a)?(a{2}|b)+", "aaabbaa");
        tie(matched, ignore, ignore) = result; // Ignore consumed and matches as they aren't tested here
        check(matched == true, "testEngine7 - Matched complex regex with groups, optional and repeated patterns");
    }
}

void testEngine8(RegexEngine& reng) {
    bool matched;

    // Test case 1: Pattern '(a){2}' with input 'a'
    {
        auto result = reng.match("(a){2}", "a");
        tie(matched, ignore, ignore) = result; // Ignore consumed and matches
        check(matched == false, "testEngine8 - Test case 1: No match for '(a){2}' with input 'a'");
    }

    // Test case 2: Pattern '(aa){1,2}' with input 'aa'
    {
        auto result = reng.match("(aa){1,2}", "aa");
        tie(matched, ignore, ignore) = result; // Ignore consumed and matches
        check(matched == true, "testEngine8 - Test case 2: Matched '(aa){1,2}' with input 'aa'");
    }
}

void testNamedGroup(RegexEngine& reng) {
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulate match call with return_matches set to true
    auto result = reng.match("(?<fancy>clancy)", "clancy", true, false); 
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testNamedGroup - Matched named group 'fancy'");
    check(matches.size() == 1, "testNamedGroup - One match group should be found");
    check(matches[0].size() > 1, "testNamedGroup - There should be more than one group in the match");
    check(matches[0][1].name == "fancy", "testNamedGroup - The second group should have the name 'fancy'");
}

void testNamedGroupFail1(RegexEngine& reng) {
    try {
        bool matched;
        int consumed;
        vector<deque<Match>> matches;

        // Attempt to match with an invalid regex pattern
        auto result = reng.match("(?<)", "", false, false);
        tie(matched, consumed, matches) = result;

        // If no exception is thrown, fail the test
        check(false, "testNamedGroupFail1 - Expected an exception to be thrown for invalid regex pattern");
    } catch (const std::exception& e) {
        // Exception was correctly thrown
        check(true, "testNamedGroupFail1 - Exception thrown as expected for invalid regex pattern");
    }
}

void testNamedGroupFail2(RegexEngine& reng) {
    try {
        bool matched;
        int consumed;
        vector<deque<Match>> matches;

        // Attempt to match with an invalid regex pattern
        auto result = reng.match("(?<abb)", "", false, false);
        tie(matched, consumed, matches) = result;

        // If no exception is thrown, fail the test
        check(false, "testNamedGroupFail2 - Expected an exception to be thrown for invalid regex pattern");
    } catch (const std::exception& e) {
        // Exception was correctly thrown
        check(true, "testNamedGroupFail2 - Exception thrown as expected for invalid regex pattern");
    }
}

void testNamedGroupFailEmptyName(RegexEngine& reng) {
    try {
        bool matched;
        int consumed;
        vector<deque<Match>> matches;

        // Attempt to match with an invalid regex pattern (empty group name)
        auto result = reng.match("(?<>asf)", "", false, false);
        tie(matched, consumed, matches) = result;

        // If no exception is thrown, fail the test
        check(false, "testNamedGroupFailEmptyName - Expected an exception to be thrown for empty named group");
    } catch (const std::exception& e) {
        // Exception was correctly thrown
        check(true, "testNamedGroupFailEmptyName - Exception thrown as expected for empty named group");
    }
}

void testMatchesIndexes(RegexEngine& reng) {
    string test_str = "abbabbab";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with continue_after_match set to true and return_matches set to true
    auto result = reng.match("a", test_str, true, true);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testMatchesIndexes - Matched 'a' in 'abbabbab'");
    check(consumed == test_str.length() - 1, "testMatchesIndexes - The entire string should be consumed except for the last match");
    check(matches.size() == 3, "testMatchesIndexes - Three matches should be found");
    check(matches[0].size() == 1, "testMatchesIndexes - The first match should have one group");
    check(matches[1].size() == 1, "testMatchesIndexes - The second match should have one group");
    check(matches[2].size() == 1, "testMatchesIndexes - The third match should have one group");
    check(matches[0][0].start_idx == 0 && matches[0][0].end_idx == 1, "testMatchesIndexes - First match at index 0-1");
    check(matches[1][0].start_idx == 3 && matches[1][0].end_idx == 4, "testMatchesIndexes - Second match at index 3-4");
    check(matches[2][0].start_idx == 6 && matches[2][0].end_idx == 7, "testMatchesIndexes - Third match at index 6-7");
}

void testReturnedMatchesIndexes(RegexEngine& reng) {
    string regex = "(a)(a)(a)(a)(a)(a)";
    string test_str = "aaaaaaaaaacccaaaaaac";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with continue_after_match set to true and return_matches set to true
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testReturnedMatchesIndexes - Matched regex in the string");
    check(consumed == test_str.length() - 1, "testReturnedMatchesIndexes - The match consumes all but one character");
    check(matches.size() == 2, "testReturnedMatchesIndexes - Two matches should be found");
    check(matches[0].size() == 7, "testReturnedMatchesIndexes - The first match should contain 7 groups");
    check(matches[1].size() == 7, "testReturnedMatchesIndexes - The second match should contain 7 groups");
    check(matches[0][0].start_idx == 0 && matches[0][0].end_idx == 6, "testReturnedMatchesIndexes - First match from 0 to 6");
    check(matches[0][1].start_idx == 5 && matches[0][1].end_idx == 6, "testReturnedMatchesIndexes - Second match from 5 to 6");
    check(matches[0][2].start_idx == 4 && matches[0][2].end_idx == 5, "testReturnedMatchesIndexes - Third match from 4 to 5");
    check(matches[0][3].start_idx == 3 && matches[0][3].end_idx == 4, "testReturnedMatchesIndexes - Fourth match from 3 to 4");
    check(matches[0][4].start_idx == 2 && matches[0][4].end_idx == 3, "testReturnedMatchesIndexes - Fifth match from 2 to 3");
    check(matches[0][5].start_idx == 1 && matches[0][5].end_idx == 2, "testReturnedMatchesIndexes - Sixth match from 1 to 2");
    check(matches[0][6].start_idx == 0 && matches[0][6].end_idx == 1, "testReturnedMatchesIndexes - Seventh match from 0 to 1");
    check(matches[1][0].start_idx == 13 && matches[1][0].end_idx == 19, "testReturnedMatchesIndexes - First match from 13 to 19");
    check(matches[1][1].start_idx == 18 && matches[1][1].end_idx == 19, "testReturnedMatchesIndexes - Second match from 18 to 19");
    check(matches[1][2].start_idx == 17 && matches[1][2].end_idx == 18, "testReturnedMatchesIndexes - Third match from 17 to 18");
    check(matches[1][3].start_idx == 16 && matches[1][3].end_idx == 17, "testReturnedMatchesIndexes - Fourth match from 16 to 17");
    check(matches[1][4].start_idx == 15 && matches[1][4].end_idx == 16, "testReturnedMatchesIndexes - Fifth match from 15 to 16");
    check(matches[1][5].start_idx == 14 && matches[1][5].end_idx == 15, "testReturnedMatchesIndexes - Sixth match from 14 to 15");
    check(matches[1][6].start_idx == 13 && matches[1][6].end_idx == 14, "testReturnedMatchesIndexes - Seventh match from 13 to 14");
}

void testReturnedGroups(RegexEngine& reng) {
    string regex = R"(a(b).*(e)?c(c)(c)c)";
    string test_str = "abxxecccc";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with continue_after_match set to true and return_matches set to true
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testReturnedGroups - Matched regex in the string");
    check(consumed == test_str.length(), "testReturnedGroups - The entire string should be consumed");
    check(matches.size() == 1, "testReturnedGroups - One match should be found");
    check(matches[0].size() == 4, "testReturnedGroups - The match should contain 4 groups");
    check(matches[0][0].match == test_str, "testReturnedGroups - The full match should be the entire string");
    check(matches[0][1].match == "c" && matches[0][1].start_idx == test_str.length() - 2, "testReturnedGroups - Second group: 'c' at index len(test_str) - 2");
    check(matches[0][2].match == "c" && matches[0][2].start_idx == test_str.length() - 3, "testReturnedGroups - Third group: 'c' at index len(test_str) - 3");
    check(matches[0][3].match == "b" && matches[0][3].start_idx == 1, "testReturnedGroups - Fourth group: 'b' at index 1");
}

void testOnLongString(RegexEngine& reng) {
    string regex = R"(a(b)?.{0,10}c(d))";
    string test_str = "abcd dcvrsbshpeuigjAAwdew ac abc vcsweacscweflllacd";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with continue_after_match set to true and return_matches set to true
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testOnLongString - Matched regex in the long string");
    check(matches.size() == 2, "testOnLongString - Two matches should be found");
    check(matches[0].size() == 3, "testOnLongString - The first match should contain 3 groups");
    check(matches[0][0].start_idx == 0 && matches[0][0].end_idx == 4, "testOnLongString - Full match: 'abcd'");
    check(matches[0][1].start_idx == 3 && matches[0][1].end_idx == 4, "testOnLongString - Group 1: 'b'");
    check(matches[0][2].start_idx == 1 && matches[0][2].end_idx == 2, "testOnLongString - Group 2: 'b'");
    check(matches[1].size() == 2, "testOnLongString - The second match should contain 2 groups");
    check(matches[1][1].start_idx == test_str.length() - 1 && matches[1][1].end_idx == test_str.length(), "testOnLongString - Group 1: 'd'");
}

void testEmptyTestStr(RegexEngine& reng) {
    string regex = "a";
    string test_str = "";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call
    auto result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == false, "testEmptyTestStr - No match for empty string");
}

void testEmptyRegexAndTestStr(RegexEngine& reng) {
    string regex = "";  // Empty regex
    string test_str = "";  // Empty test string
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with empty regex and empty string
    auto result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testEmptyRegexAndTestStr - Empty regex matches empty string");
}

void testRegexWithRightEmptyGroup(RegexEngine& reng) {
    string regex = "a|";  // Regex with a right empty group
    string test_str = "ab";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with the provided regex and string
    auto result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testRegexWithRightEmptyGroup - Matched 'a' in the string");
}

void testEmptyGroupQuantified(RegexEngine& reng) {
    string regex = "()+";
    string test_str = "ab";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Simulating match call with the provided regex and string
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    // Use the check function to validate the results
    check(matched == true, "testEmptyGroupQuantified - Matched empty group quantified");
    check(matches.size() == 1, "testEmptyGroupQuantified - One match group should be found");
}

void testNestedQuantifiers(RegexEngine& reng) {
    string regex = "(a*)+ab";
    string test_str = "aab";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // First test case: Match the pattern (a*)+ab with the string 'aab'
    auto result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;
    check(matched == true, "testNestedQuantifiers - Test case 1: Matched (a*)+ab with 'aab'");

    // Second test case: Match the pattern (a+)+ab with the string 'ab'
    regex = "(a+)+ab";
    test_str = "ab";
    result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;
    check(matched == false, "testNestedQuantifiers - Test case 2: No match for (a+)+ab with 'ab'");
}

void testNestedQuantifiersWithOrNode(RegexEngine& reng) {
    string regex = "(a*|b*)*ab";
    string test_str = "ab";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // First test case: Match the pattern (a*|b*)*ab with the string 'ab'
    auto result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;
    check(matched == true, "testNestedQuantifiersWithOrNode - Test case 1: Matched (a*|b*)*ab with 'ab'");

    // Second test case: Match the pattern (a*|b*)+ab with the string 'ab'
    regex = "(a*|b*)+ab";
    result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;
    check(matched == true, "testNestedQuantifiersWithOrNode - Test case 2: Matched (a*|b*)+ab with 'ab'");

    // Third test case: Match the pattern (a+|b+)+ab with the string 'ab'
    regex = "(a+|b+)+ab";
    result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;
    check(matched == false, "testNestedQuantifiersWithOrNode - Test case 3: No match for (a+|b+)+ab with 'ab'");
}

void testMultipleNamedGroups(RegexEngine& reng) {
    string regex = "(?<first>[a-z]+)(?<second>i)(?<third>l)";
    string test_str = "nostril";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Match the regex with the string 'nostril', checking named groups
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testMultipleNamedGroups - Matched regex with multiple named groups");
}

void testOneNamedGroup(RegexEngine& reng) {
    string regex = "[a-z]+(?<last>l)";
    string test_str = "nostril";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Match the regex with the string 'nostril', checking the named group
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testOneNamedGroup - Matched regex with one named group");
    check(matches[0][1].name == "last" && matches[0][1].match == "l", "testOneNamedGroup - Named group 'last' matches 'l'");
}

void testTwoSeparatedNamedGroup(RegexEngine& reng) {
    string regex = "(?<first>n)[a-z]+(?<last>l)";
    string test_str = "nostril";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Match the regex with the string 'nostril', checking the named groups 'first' and 'last'
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testTwoSeparatedNamedGroup - Matched regex with two separated named groups");
    check(matches.size() == 1, "testTwoSeparatedNamedGroup - One match should be found");
    check(matches[0].size() == 3, "testTwoSeparatedNamedGroup - Three groups should be matched");
    check(matches[0][0].match == "nostril", "testTwoSeparatedNamedGroup - Full match should be 'nostril'");
    check(matches[0][1].match == "l", "testTwoSeparatedNamedGroup - Named group 'last' should match 'l'");
    check(matches[0][2].match == "n", "testTwoSeparatedNamedGroup - Named group 'first' should match 'n'");
}

void testMatchContiguousNamedGroups(RegexEngine& reng) {
    string regex = "(?<first>n)(?<last>l)";
    string test_str = "nl";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Match the regex with the string 'nl', checking the named groups 'first' and 'last'
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testMatchContiguousNamedGroups - Matched regex with contiguous named groups");
    check(matches.size() == 1, "testMatchContiguousNamedGroups - One match should be found");
    check(matches[0].size() == 3, "testMatchContiguousNamedGroups - Three groups should be matched");
    check(matches[0][0].match == "nl", "testMatchContiguousNamedGroups - Full match should be 'nl'");
    check(matches[0][1].match == "l", "testMatchContiguousNamedGroups - Named group 'last' should match 'l'");
    check(matches[0][2].match == "n", "testMatchContiguousNamedGroups - Named group 'first' should match 'n'");
}

void testNamedGroupWithRangeElement(RegexEngine& reng) {
    string regex = "(?<first>[a-z])(?<last>l)";
    string test_str = "nl";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Match the regex with the string 'nl', checking the named groups 'first' and 'last'
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testNamedGroupWithRangeElement - Matched regex with named groups and range element");
    check(matches.size() == 1, "testNamedGroupWithRangeElement - One match should be found");
    check(matches[0].size() == 3, "testNamedGroupWithRangeElement - Three groups should be matched");
    check(matches[0][0].match == "nl", "testNamedGroupWithRangeElement - Full match should be 'nl'");
    check(matches[0][1].match == "l", "testNamedGroupWithRangeElement - Named group 'last' should match 'l'");
    check(matches[0][2].match == "n", "testNamedGroupWithRangeElement - Named group 'first' should match 'n'");
}

void testNamedGroupWithRangeElementAndQuantifier(RegexEngine& reng) {
    string regex = "(?<first>[a-z]+)(?<last>l)";
    string test_str = "nl";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Match the regex with the string 'nl', checking the named groups 'first' and 'last'
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testNamedGroupWithRangeElementAndQuantifier - Matched regex with named groups and quantifier");
    check(matches.size() == 1, "testNamedGroupWithRangeElementAndQuantifier - One match should be found");
    check(matches[0].size() == 3, "testNamedGroupWithRangeElementAndQuantifier - Three groups should be matched");
    check(matches[0][0].match == "nl", "testNamedGroupWithRangeElementAndQuantifier - Full match should be 'nl'");
    check(matches[0][1].match == "l", "testNamedGroupWithRangeElementAndQuantifier - Named group 'last' should match 'l'");
    check(matches[0][2].match == "n", "testNamedGroupWithRangeElementAndQuantifier - Named group 'first' should match 'n'");
}

void testBacktrackingOrNodeInsideGroupNode(RegexEngine& reng) {
    string regex = "(?<first>b{1,2}|[a-z]+)(?<last>l)";
    string test_str = "bnl";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Match the regex with the string 'bnl'
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testBacktrackingOrNodeInsideGroupNode - Matched regex with backtracking or node inside group node");
    check(matches.size() == 1, "testBacktrackingOrNodeInsideGroupNode - One match should be found");
    check(matches[0].size() == 3, "testBacktrackingOrNodeInsideGroupNode - Three groups should be matched");
    check(matches[0][0].start_idx == 0 && matches[0][0].end_idx == test_str.length(), "testBacktrackingOrNodeInsideGroupNode - Full match should cover the entire string");
    check(matches[0][1].start_idx == 2 && matches[0][1].end_idx == test_str.length(), "testBacktrackingOrNodeInsideGroupNode - Named group 'last' should match 'l'");
    check(matches[0][2].start_idx == 0 && matches[0][2].end_idx == 2, "testBacktrackingOrNodeInsideGroupNode - Named group 'first' should match 'bn'");

    // Second regex with different order of alternatives
    regex = "(?<first>[a-z]+|b{1,2})(?<last>l)";
    result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "testBacktrackingOrNodeInsideGroupNode - Matched regex with different order of alternatives");
    check(matches.size() == 1, "testBacktrackingOrNodeInsideGroupNode - One match should be found");
    check(matches[0].size() == 3, "testBacktrackingOrNodeInsideGroupNode - Three groups should be matched");
    check(matches[0][0].start_idx == 0 && matches[0][0].end_idx == test_str.length(), "testBacktrackingOrNodeInsideGroupNode - Full match should cover the entire string");
    check(matches[0][1].start_idx == 2 && matches[0][1].end_idx == test_str.length(), "testBacktrackingOrNodeInsideGroupNode - Named group 'last' should match 'l'");
    check(matches[0][2].start_idx == 0 && matches[0][2].end_idx == 2, "testBacktrackingOrNodeInsideGroupNode - Named group 'first' should match 'bn'");
}

void testDoubleOrNodesWithWildcardInBetween(RegexEngine& reng) {
    string regex = R"(@(gm|ho).(com|it))";
    string test_str = "@hoa.com";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Attempt to match the regex against the string '@hoa.com'
    auto result = reng.match(regex, test_str);
    tie(matched, consumed, matches) = result;

    check(matched == false, "testDoubleOrNodesWithWildcardInBetween - No match for '@hoa.com' with regex '@(gm|ho).(com|it)'");
}

void test1(RegexEngine& reng) {
    string regex = R"((ad+a)*a)";
    string test_str = "adaa";
    bool matched;
    int consumed;
    vector<deque<Match>> matches;

    // Attempt to match the regex against the string 'adaa'
    auto result = reng.match(regex, test_str, true, true);
    tie(matched, consumed, matches) = result;

    check(matched == true, "test1 - Matched regex '(ad+a)*a' with 'adaa'");
    check(consumed == test_str.length(), "test1 - The entire string should be consumed");
    check(matches.size() == 1, "test1 - One match group should be found");
}



int main() {
    RegexEngine reng;

    // Run individual test cases
    testSimplest(reng);
    testSimplestWithWildcard(reng);
    testSimplestButLonger(reng);
    testWildcard(reng);
    testBacktracking(reng);
    testOr(reng);
    testOrNoMatch(reng);
    testOrNoMatchWithBT(reng);
    testBTNoMatch(reng);
    testMatchGroupZeroOrMore(reng);
    testFailGroupOneOrMore(reng);
    testComplexMatch(reng);
    testComplexMatch2(reng);
    testMatchMailSimple(reng);
    testBtIndexLeaf(reng);
    testBtIndexOr(reng);
    testBtIndexGroup(reng);
    testMatchOrLeft(reng);
    testMatchOrRight(reng);
    testMatchOrRightAtStartEnd(reng);
    testNoMatchAfterEnd(reng);
    testMatchSequenceWithStartEndCorrectly(reng);
    testComplexMatch3(reng);
    testBitLessComplexMatch3(reng);
    testUnescapedSpecialCh(reng);
    testVariousEmails(reng);
    testMatchEmpty(reng);
    testMatchSpace(reng);
    testMatchSpace2(reng);
    testReturnMatchesSimple(reng);
    testReturnMatchesTwo(reng);
    testNonCapturingGroup(reng);
    testContinueAfterMatchAndReturnMatchesSimple(reng);
    testContinueAfterMatchAndReturnMatches2(reng);
    testQuestionMark(reng);
    testEngine1(reng);
    testEngine2(reng);
    testEngine3(reng);
    testEngine4(reng);
    testEngine5(reng);
    testEngine6(reng);
    testEngine7(reng);
    testEngine8(reng);
    testNamedGroup(reng);
    testNamedGroupFail1(reng);
    testNamedGroupFail2(reng);
    testNamedGroupFailEmptyName(reng);
    testMatchesIndexes(reng);
    testReturnedMatchesIndexes(reng);
    testReturnedGroups(reng);
    testOnLongString(reng);
    testEmptyTestStr(reng);
    testEmptyRegexAndTestStr(reng);
    testRegexWithRightEmptyGroup(reng);
    testEmptyGroupQuantified(reng);
    testNestedQuantifiers(reng);
    testNestedQuantifiersWithOrNode(reng);
    testMultipleNamedGroups(reng);
    testOneNamedGroup(reng);
    testTwoSeparatedNamedGroup(reng);
    testMatchContiguousNamedGroups(reng);
    testNamedGroupWithRangeElement(reng);
    testNamedGroupWithRangeElementAndQuantifier(reng);
    testBacktrackingOrNodeInsideGroupNode(reng);
    testDoubleOrNodesWithWildcardInBetween(reng);
    test1(reng);

    
    cout << "All Regex Tests Passed!" << endl;

    return 0;
}