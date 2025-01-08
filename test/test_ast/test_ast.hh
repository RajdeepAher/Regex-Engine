#ifndef TEST_AST_HH
#define TEST_AST_HH

#include <iostream>
#include <memory>
#include <variant>
#include "../../src/ast/ast.hh" // Include the AST-related headers

// Test function declarations
void test_ASTNode();
void test_RE();
void test_LeafNode();
void test_WildcardElement();
void test_SpaceElement();
void test_RangeElement_positive_logic();
void test_RangeElement_negative_logic();

#endif // TEST_AST_HH