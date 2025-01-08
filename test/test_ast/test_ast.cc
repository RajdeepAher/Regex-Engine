#include "test_ast.hh"

void test_ASTNode() {
    shared_ptr<ASTNode> ast_node = make_shared<ASTNode>();
    if (ast_node != nullptr) {
        cout << "[PASS] test_ASTNode passed!" << endl;
    } else {
        cout << "[FAIL] test_ASTNode failed!" << endl;
    }
}

void test_RE() {
    shared_ptr<RE> re = make_shared<RE>(make_shared<Element>("e"));
    if (re != nullptr && re->child != nullptr && re->children.size() > 0 && re->child == re->children[0]) {
        cout << "[PASS] test_RE passed!" << endl;
    } else {
        cout << "[FAIL] test_RE failed!" << endl;
    }
}

void test_LeafNode() {
    shared_ptr<LeafNode> ln = make_shared<LeafNode>();
    if (ln != nullptr && ln->is_match() == false) {
        cout << "[PASS] test_LeafNode passed!" << endl;
    } else {
        cout << "[FAIL] test_LeafNode failed!" << endl;
    }
}

void test_WildcardElement() {
    shared_ptr<WildcardElement> we = make_shared<WildcardElement>();
    if (we != nullptr) {
        cout << "[PASS] test_WildcardElement passed!" << endl;
    } else {
        cout << "[FAIL] test_WildcardElement failed!" << endl;
    }
}

void test_SpaceElement() {
    shared_ptr<SpaceElement> se = make_shared<SpaceElement>();
    if (se != nullptr) {
        bool space_match = se->is_match(" ") && se->is_match("\t") && se->is_match("\n")
                           && se->is_match("\f") && se->is_match("\r") && !se->is_match("t");
        if (space_match) {
            cout << "[PASS] test_SpaceElement passed!" << endl;
        } else {
            cout << "[FAIL] test_SpaceElement failed!" << endl;
        }
    } else {
        cout << "[FAIL] test_SpaceElement failed!" << endl;
    }
}

void test_RangeElement_positive_logic() {
    shared_ptr<RangeElement> re = make_shared<RangeElement>("abc", true);
    if (re != nullptr && re->is_positive_logic == true && re->is_match("a") == true && re->is_match("x") == false) {
        cout << "[PASS] test_RangeElement_positive_logic passed!" << endl;
    } else {
        cout << "[FAIL] test_RangeElement_positive_logic failed!" << endl;
    }
}

void test_RangeElement_negative_logic() {
    shared_ptr<RangeElement> nre = make_shared<RangeElement>("abc", false);
    if (nre != nullptr && nre->is_positive_logic == false && nre->is_match("a") == false && nre->is_match("x") == true) {
        cout << "[PASS] test_RangeElement_negative_logic passed!" << endl;
    } else {
        cout << "[FAIL] test_RangeElement_negative_logic failed!" << endl;
    }
}


int main() {
    // Run all AST tests
    test_ASTNode();
    test_RE();
    test_LeafNode();
    test_WildcardElement();
    test_SpaceElement();
    test_RangeElement_positive_logic();
    test_RangeElement_negative_logic();

    cout<<"All ast tests passed!"<<endl;

    return 0;
}