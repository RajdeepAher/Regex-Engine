#ifndef TEST_PARSER_HH
#define TEST_PARSER_HH

#include <iostream>
#include <stdexcept>
#include <limits>
#include "../../src/parser/parser.hh"

// Test function declarations
bool test_simple_regex(Parser& parser);
bool test_grouping(Parser& parser);
bool test_curly_braces_1(Parser& parser);
bool test_fail_no_closing_par(Parser& parser);
bool test_parse_match_start_end(Parser& parser);
bool test_complex_regex(Parser& parser);
bool test_space_element(Parser& parser);
bool test_range_1(Parser& parser);
bool test_range_2(Parser& parser);
bool test_range_3(Parser& parser);
bool test_range_4(Parser& parser);
bool test_parse_curly_1(Parser& parser);
bool test_parse_curly_2(Parser& parser);
bool test_parse_curly_3(Parser& parser);
bool test_parse_curly_4(Parser& parser);
bool test_parse_fail_empty_curly(Parser& parser);
bool test_fail_quantifier_unescaped(Parser& parser);
bool test_parse_fail_missing_closing_bracket(Parser& parser);
bool test_parse_fail_unescaped_closing_bracket(Parser& parser);
bool test_parse_fail_unescaped_closing_parenthesis(Parser& parser);
bool test_parse_fail_unescaped_start(Parser& parser);
bool test_parse_fail_unescaped_end(Parser& parser);
bool test_parse_fail_swapped_range(Parser& parser);
bool test_parse_fail_non_capturing_group(Parser& parser);
bool test_parse_fail_non_closed_range(Parser& parser);
bool test_parse_ornode_groups_names(Parser& parser);
bool test_groups_names_double_ornode(Parser& parser);

#endif // TEST_PARSER_HH