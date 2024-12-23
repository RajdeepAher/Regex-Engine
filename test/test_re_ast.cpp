#include "../src/re_ast.cpp"
#pragma once

void test_ASTNode() {
    std::shared_ptr<ASTNode> ast_node = std::make_shared<ASTNode>();
    if (ast_node != nullptr) {
        std::cout << "test_ASTNode passed!" << std::endl;
    } else {
        std::cout << "test_ASTNode failed!" << std::endl;
    }
}

void test_RE() {
    std::shared_ptr<RE> re = std::make_shared<RE>(std::make_shared<Element>("e"));
    if (re != nullptr && re->child != nullptr && re->children.size() > 0 && re->child == re->children[0]) {
        std::cout << "test_RE passed!" << std::endl;
    } else {
        std::cout << "test_RE failed!" << std::endl;
    }
}

// void test_NotNode() {
//     std::shared_ptr<NotNode> not_node = std::make_shared<NotNode>();
//     // NotNode has no 'child' or 'children', so you might adjust this test accordingly
//     if (not_node != nullptr) {
//         std::cout << "test_NotNode passed!" << std::endl;
//     } else {
//         std::cout << "test_NotNode failed!" << std::endl;
//     }
// }

void test_LeafNode() {
    std::shared_ptr<LeafNode> ln = std::make_shared<LeafNode>();
    if (ln != nullptr && ln->is_match() == false) {
        std::cout << "test_LeafNode passed!" << std::endl;
    } else {
        std::cout << "test_LeafNode failed!" << std::endl;
    }
}

void test_WildcardElement() {
    std::shared_ptr<WildcardElement> we = std::make_shared<WildcardElement>();
    if (we != nullptr) {
        std::cout << "test_WildcardElement passed!" << std::endl;
    } else {
        std::cout << "test_WildcardElement failed!" << std::endl;
    }
}

void test_SpaceElement() {
    std::shared_ptr<SpaceElement> se = std::make_shared<SpaceElement>();
    if (se != nullptr) {
        bool space_match = se->is_match(" ") && se->is_match("\t") && se->is_match("\n")
                           && se->is_match("\f") && se->is_match("\r") && !se->is_match("t");
        if (space_match) {
            std::cout << "test_SpaceElement passed!" << std::endl;
        } else {
            std::cout << "test_SpaceElement failed!" << std::endl;
        }
    } else {
        std::cout << "test_SpaceElement failed!" << std::endl;
    }
}

void test_RangeElement_positive_logic() {
    std::shared_ptr<RangeElement> re = std::make_shared<RangeElement>("abc", true);
    if (re != nullptr && re->is_positive_logic == true && re->is_match("a") == true && re->is_match("x") == false) {
        std::cout << "test_RangeElement_positive_logic passed!" << std::endl;
    } else {
        std::cout << "test_RangeElement_positive_logic failed!" << std::endl;
    }
}

void test_RangeElement_negative_logic() {
    std::shared_ptr<RangeElement> nre = std::make_shared<RangeElement>("abc", false);
    if (nre != nullptr && nre->is_positive_logic == false && nre->is_match("a") == false && nre->is_match("x") == true) {
        std::cout << "test_RangeElement_negative_logic passed!" << std::endl;
    } else {
        std::cout << "test_RangeElement_negative_logic failed!" << std::endl;
    }
}
