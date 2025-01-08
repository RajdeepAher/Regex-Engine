#ifndef TEST_REGEX_HH
#define TEST_REGEX_HH

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <tuple>
#include "../../src/regex/regex.hh"

using namespace std;

void check(bool condition, const std::string& message);
void testSimplest(RegexEngine& reng);
void testSimplestWithWildcard(RegexEngine& reng);
void testSimplestButLonger(RegexEngine& reng);
void testWildcard(RegexEngine& reng);
void testBacktracking(RegexEngine& reng);
void testOr(RegexEngine& reng);
void testOrNoMatch(RegexEngine& reng);
void testOrNoMatchWithBT(RegexEngine& reng);
void testBTNoMatch(RegexEngine& reng);
void testMatchGroupZeroOrMore(RegexEngine& reng);
void testFailGroupOneOrMore(RegexEngine& reng);
void testComplexMatch(RegexEngine& reng);
void testComplexMatch2(RegexEngine& reng);
void testMatchMailSimple(RegexEngine& reng);
void testBtIndexLeaf(RegexEngine& reng);
void testBtIndexOr(RegexEngine& reng);
void testBtIndexGroup(RegexEngine& reng);
void testMatchOrLeft(RegexEngine& reng);
void testMatchOrRight(RegexEngine& reng);
void testMatchOrRightAtStartEnd(RegexEngine& reng);
void testNoMatchAfterEnd(RegexEngine& reng);
void testMatchSequenceWithStartEndCorrectly(RegexEngine& reng);
void testComplexMatch3(RegexEngine& reng);
void testBitLessComplexMatch3(RegexEngine& reng);
void testUnescapedSpecialCh(RegexEngine& reng);
void testVariousEmails(RegexEngine& reng);
void testMatchEmpty(RegexEngine& reng);
void testMatchSpace(RegexEngine& reng);
void testMatchSpace2(RegexEngine& reng);
void testReturnMatchesSimple(RegexEngine& reng);
void testReturnMatchesTwo(RegexEngine& reng);
void testNonCapturingGroup(RegexEngine& reng);
void testContinueAfterMatchAndReturnMatchesSimple(RegexEngine& reng);
void testContinueAfterMatchAndReturnMatches2(RegexEngine& reng);
void testQuestionMark(RegexEngine& reng);
void testEngine1(RegexEngine& reng);
void testEngine2(RegexEngine& reng);
void testEngine3(RegexEngine& reng);
void testEngine4(RegexEngine& reng);
void testEngine5(RegexEngine& reng);
void testEngine6(RegexEngine& reng);
void testEngine7(RegexEngine& reng);
void testEngine8(RegexEngine& reng);
void testNamedGroup(RegexEngine& reng);
void testNamedGroupFail1(RegexEngine& reng);
void testNamedGroupFail2(RegexEngine& reng);
void testNamedGroupFailEmptyName(RegexEngine& reng);
void testMatchesIndexes(RegexEngine& reng);
void testReturnedMatchesIndexes(RegexEngine& reng);
void testReturnedGroups(RegexEngine& reng);
void testOnLongString(RegexEngine& reng);
void testEmptyTestStr(RegexEngine& reng);
void testEmptyRegexAndTestStr(RegexEngine& reng);
void testRegexWithRightEmptyGroup(RegexEngine& reng);
void testEmptyGroupQuantified(RegexEngine& reng);
void testNestedQuantifiers(RegexEngine& reng);
void testNestedQuantifiersWithOrNode(RegexEngine& reng);
void testMultipleNamedGroups(RegexEngine& reng);
void testOneNamedGroup(RegexEngine& reng);
void testTwoSeparatedNamedGroup(RegexEngine& reng);
void testMatchContiguousNamedGroups(RegexEngine& reng);
void testNamedGroupWithRangeElement(RegexEngine& reng);
void testNamedGroupWithRangeElementAndQuantifier(RegexEngine& reng);
void testBacktrackingOrNodeInsideGroupNode(RegexEngine& reng);
void testDoubleOrNodesWithWildcardInBetween(RegexEngine& reng);
void test1(RegexEngine& reng);

#endif // REGEX_HH