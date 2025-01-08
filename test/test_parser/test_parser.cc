#include "test_parser.hh"

bool test_simple_regex(Parser& parser) {
    auto ast = parser.parse("a");
    if (dynamic_cast<RE*>(ast.get()) == nullptr) return false;
    if (dynamic_cast<GroupNode*>(ast->child.get()) == nullptr) return false;
    if (dynamic_cast<Element*>((dynamic_cast<GroupNode*>(ast->child.get()))->children[0].get()) == nullptr) return false;
    return true;
}

bool test_grouping(Parser& parser) {
    auto ast = parser.parse("a(b)c");
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 3) return false;
    if (dynamic_cast<Element*>(groupNode->children[0].get()) == nullptr) return false;
    if (dynamic_cast<GroupNode*>(groupNode->children[1].get()) == nullptr) return false;
    if (dynamic_cast<Element*>(groupNode->children[2].get()) == nullptr) return false;
    return true;
}

bool test_curly_braces_1(Parser& parser) {
    auto ast = parser.parse("a{5}b");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 2) return false;
    if (dynamic_cast<Element*>(groupNode->children[0].get()) == nullptr) return false;
    if (dynamic_cast<Element*>(groupNode->children[1].get()) == nullptr) return false;
    return true;
}

bool test_fail_no_closing_par(Parser& parser) {
    try {
        parser.parse("a[d]((vfw)");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_match_start_end(Parser& parser) {
    auto ast = parser.parse("^aaaa.*a$");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 8) return false;
    return true;
}

bool test_complex_regex(Parser& parser) {
    auto ast = parser.parse(R"(^[a-zA-Z]{1,20}@[a-zA-Z]\.[a-z]{1,3}$)");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 7) return false;
    if (!dynamic_cast<StartElement*>(groupNode->children[0].get())) return false;
    auto rangeElement1 = dynamic_cast<RangeElement*>(groupNode->children[1].get());
    if (!rangeElement1) return false;
    if (!std::holds_alternative<int>(rangeElement1->min) || std::get<int>(rangeElement1->min) != 1) return false;
    if (!(holds_alternative<int>(rangeElement1->max) && get<int>(rangeElement1->max) == 20)) return false;
    if (!dynamic_cast<Element*>(groupNode->children[2].get())) return false;
    if (!dynamic_cast<RangeElement*>(groupNode->children[3].get())) return false;
    if (!dynamic_cast<Element*>(groupNode->children[4].get())) return false;
    auto rangeElement2 = dynamic_cast<RangeElement*>(groupNode->children[5].get());
    if (!rangeElement2) return false;
    if (!std::holds_alternative<int>(rangeElement2->min) || std::get<int>(rangeElement2->min) != 1) return false;
    if (!(holds_alternative<int>(rangeElement2->max) && get<int>(rangeElement2->max) == 3)) return false;
    if (!dynamic_cast<EndElement*>(groupNode->children[6].get())) return false;
    return true;
}

bool test_space_element(Parser& parser) {
    auto ast = parser.parse(R"(\s)");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    if (!dynamic_cast<SpaceElement*>(groupNode->children[0].get())) return false;
    return true;
}

bool test_range_1(Parser& parser) {
    auto ast = parser.parse(R"([^a-z])");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto rangeElement = dynamic_cast<RangeElement*>(groupNode->children[0].get());
    if (rangeElement == nullptr) return false;
    if (rangeElement->is_match("a")) return false;
    return true;
}

bool test_range_2(Parser& parser) {
    auto ast = parser.parse(R"([^a-z-\s-])");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto rangeElement = dynamic_cast<RangeElement*>(groupNode->children[0].get());
    if (rangeElement == nullptr) return false;
    if (rangeElement->is_match("a")) return false;
    if (rangeElement->is_match("-")) return false;
    if (rangeElement->is_match(" ")) return false;
    return true;
}

bool test_range_3(Parser& parser) {
    auto ast = parser.parse(R"([a-z-\s-])");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto rangeElement = dynamic_cast<RangeElement*>(groupNode->children[0].get());
    if (rangeElement == nullptr) return false;
    if (!rangeElement->is_match("a")) return false;
    if (!rangeElement->is_match("-")) return false;
    if (!rangeElement->is_match(" ")) return false;
    return true;
}

bool test_range_4(Parser& parser) {
    auto ast = parser.parse(R"([\]])");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto rangeElement = dynamic_cast<RangeElement*>(groupNode->children[0].get());
    if (rangeElement == nullptr) return false;
    if (!rangeElement->is_match("]")) return false;
    return true;
}

bool test_parse_curly_1(Parser& parser) {
    auto ast = parser.parse(R"(a{2})");
    if (ast->child == nullptr) return false;
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto element = dynamic_cast<Element*>(groupNode->children[0].get());
    if (element == nullptr) return false;
    if (!element->is_match("a")) return false;
    if (std::holds_alternative<int>(element->max) && std::get<int>(element->max) != 2) return false;
    if (std::holds_alternative<int>(element->min) && std::get<int>(element->min) != 2) return false;
    return true;
}

bool test_parse_curly_2(Parser& parser) {
    auto ast = parser.parse("a{,2}");
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto element = dynamic_cast<Element*>(groupNode->children[0].get());
    if (element == nullptr) return false;
    if (!element->is_match("a")) return false;
    if (!(std::holds_alternative<int>(element->min) && std::get<int>(element->min) == 0)) return false;
    if (!(std::holds_alternative<int>(element->max) && std::get<int>(element->max) == 2)) return false;
    return true;
}

bool test_parse_curly_3(Parser& parser) {
    auto ast = parser.parse("a{2,}");
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto element = dynamic_cast<Element*>(groupNode->children[0].get());
    if (element == nullptr) return false;
    if (!element->is_match("a")) return false;
    if (!(std::holds_alternative<int>(element->min) && std::get<int>(element->min) == 2)) return false;
    if (!(std::holds_alternative<int>(element->max) && std::get<int>(element->max) == std::numeric_limits<int>::max())) return false;
    return true;
}

bool test_parse_curly_4(Parser& parser) {
    auto ast = parser.parse("a{,}");
    auto groupNode = dynamic_cast<GroupNode*>(ast->child.get());
    if (groupNode == nullptr) return false;
    if (groupNode->children.size() != 1) return false;
    auto element = dynamic_cast<Element*>(groupNode->children[0].get());
    if (element == nullptr) return false;
    if (!element->is_match("a")) return false;
    if (!(std::holds_alternative<int>(element->min) && std::get<int>(element->min) == 0)) return false;
    if (!(std::holds_alternative<int>(element->max) && std::get<int>(element->max) == std::numeric_limits<int>::max())) return false;
    return true;
}

bool test_parse_fail_empty_curly(Parser& parser) {
    try {
        parser.parse("a{}");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_fail_quantifier_unescaped(Parser& parser) {
    try {
        parser.parse("?");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_missing_closing_bracket(Parser& parser) {
    try {
        parser.parse("a[abc");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_unescaped_closing_bracket(Parser& parser) {
    try {
        parser.parse("abc]");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_unescaped_closing_parenthesis(Parser& parser) {
    try {
        parser.parse("a)");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_unescaped_start(Parser& parser) {
    try {
        parser.parse("^^");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_unescaped_end(Parser& parser) {
    try {
        parser.parse("$$");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_swapped_range(Parser& parser) {
    try {
        parser.parse("[z-a]");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_non_capturing_group(Parser& parser) {
    try {
        parser.parse("(?");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_fail_non_closed_range(Parser& parser) {
    try {
        parser.parse("[a");
        return false; // Expected exception, but none was thrown
    } catch (const std::exception& e) {
        return true; // Caught expected exception
    } catch (...) {
        return false; // Caught unexpected exception type
    }
}

bool test_parse_ornode_groups_names(Parser& parser) {
    auto ast = parser.parse(R"(a|b)");
    if (ast->child == nullptr) return false;
    auto orNode = dynamic_cast<OrNode*>(ast->child.get());
    if (!orNode) return false;
    auto leftGroupNode = dynamic_cast<GroupNode*>(orNode->left.get());
    if (!leftGroupNode) return false;
    auto rightGroupNode = dynamic_cast<GroupNode*>(orNode->right.get());
    if (!rightGroupNode) return false;
    if (leftGroupNode->group_name != rightGroupNode->group_name) return false;
    if (leftGroupNode->group_id != rightGroupNode->group_id) return false;
    return true;
}

bool test_groups_names_double_ornode(Parser& parser) {
    auto ast = parser.parse(R"(a|b|c)");
    if (ast->child == nullptr) return false;
    auto orNode = dynamic_cast<OrNode*>(ast->child.get());
    if (!orNode) return false;
    auto leftmostGroupNode = dynamic_cast<GroupNode*>(orNode->left.get());
    if (!leftmostGroupNode) return false;
    int leftmost_gid = leftmostGroupNode->group_id;
    std::string leftmost_gname = leftmostGroupNode->group_name;
    auto centralOrNode = dynamic_cast<OrNode*>(orNode->right.get());
    if (!centralOrNode) return false;
    auto centralGroupNode = dynamic_cast<GroupNode*>(centralOrNode->left.get());
    if (!centralGroupNode) return false;
    int central_gid = centralGroupNode->group_id;
    std::string central_gname = centralGroupNode->group_name;
    auto rightmostGroupNode = dynamic_cast<GroupNode*>(centralOrNode->right.get());
    if (!rightmostGroupNode) return false;
    int rightmost_gid = rightmostGroupNode->group_id;
    std::string rightmost_gname = rightmostGroupNode->group_name;
    if (leftmost_gid != central_gid || central_gid != rightmost_gid) return false;
    if (leftmost_gname != central_gname || central_gname != rightmost_gname) return false;
    return true;
}

int main() {
    Parser parser;
    bool all_passed = true;

    auto run_test = [&](const string& name, auto test_func) {
        bool result = test_func(parser);
        cout << (result ? "[PASS] " : "[FAIL] ") << name << endl;
        if (!result) all_passed = false;
    };

    run_test("test_simple_regex", test_simple_regex);
    run_test("test_grouping", test_grouping);
    run_test("test_curly_braces_1", test_curly_braces_1);
    run_test("test_fail_no_closing_par", test_fail_no_closing_par);
    run_test("test_parse_match_start_end", test_parse_match_start_end);
    run_test("test_complex_regex", test_complex_regex);
    run_test("test_space_element", test_space_element);
    run_test("test_range_1", test_range_1);
    run_test("test_range_2", test_range_2);
    run_test("test_range_3", test_range_3);
    run_test("test_range_4", test_range_4);
    run_test("test_parse_curly_1", test_parse_curly_1);
    run_test("test_parse_curly_2", test_parse_curly_2);
    run_test("test_parse_curly_3", test_parse_curly_3);
    run_test("test_parse_curly_4", test_parse_curly_4);
    run_test("test_parse_fail_empty_curly", test_parse_fail_empty_curly);
    run_test("test_fail_quantifier_unescaped", test_fail_quantifier_unescaped);
    run_test("test_parse_fail_missing_closing_bracket", test_parse_fail_missing_closing_bracket);
    run_test("test_parse_fail_unescaped_closing_bracket", test_parse_fail_unescaped_closing_bracket);
    run_test("test_parse_fail_unescaped_closing_parenthesis", test_parse_fail_unescaped_closing_parenthesis);
    run_test("test_parse_fail_unescaped_start", test_parse_fail_unescaped_start);
    run_test("test_parse_fail_unescaped_end", test_parse_fail_unescaped_end);
    run_test("test_parse_fail_swapped_range", test_parse_fail_swapped_range);
    run_test("test_parse_fail_non_capturing_group", test_parse_fail_non_capturing_group);
    run_test("test_parse_fail_non_closed_range", test_parse_fail_non_closed_range);
    run_test("test_parse_ornode_groups_names", test_parse_ornode_groups_names);
    run_test("test_groups_names_double_ornode", test_groups_names_double_ornode);

    cout << "All  parser tests completed! " << (all_passed ? "All PARSER TESTS PASSED !" : "Some FAILED") << endl;
    return all_passed ? 0 : 1;
}