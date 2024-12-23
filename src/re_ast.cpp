#include <deque>
#include <vector>
#include <memory>
#include <string>
#include <variant>
#include <cctype>
#include <algorithm>
#include <iostream>

using namespace std;

class ASTNode {
    // AST NODE Base Class
public:
    ASTNode() = default;
};


class RE: public ASTNode{
public:
    bool __capturing__;
    string group_name;
    int group_id;
    shared_ptr<ASTNode> child;
    deque<shared_ptr<ASTNode>> children;

    RE (shared_ptr<ASTNode> child,
    bool capturing = false,
    string group_name = "RegEx"):
        __capturing__(capturing),
        group_name(group_name),
        group_id(-1),
        child(child){
            children.push_back(child);
        }


    bool is_capturing () const {
        return __capturing__;
    }

};


class LeafNode : public ASTNode {
public:
    // Constructor
    LeafNode() : ASTNode() {}

    // Method to check for match
    virtual bool is_match(const std::string& ch = "",
                          int str_i = -1,
                          int str_len = -1) const {
        /**
         * Returns whether the passed inputs match with the node.
         *
         * For example, if the node matches the character "a" and the passed ch is
         * "b", the method will return false. If the passed ch was "a", then the
         * result would be true.
         *
         * param ch: the char you want to match
         * param str_i: the string index you are considering
         * param str_len: the test string length
         *
         * return bool: represents whether there is a match between the node
         *               and the passed parameters or not.
         */
        return false;
    }
};

class Element : public LeafNode {
public:
    // Constructor
    Element(const std::string& match_ch = "")
        : LeafNode(), match(match_ch), min(1), max(1) {}

    // Override is_match
    bool is_match(const std::string& ch = "",
                  int str_i = 0,
                  int str_len = 0) const override {
        return match == ch;
    }
    std::string match;
    std::variant<int, double> min;
    std::variant<int, double> max;
};


class WildcardElement : public Element {
public:
    // Constructor
    WildcardElement() : Element("anything") {}

    // Override is_match
    bool is_match(const std::string& ch = "",
                  int str_i = 0,
                  int str_len = 0) const override {
        return ch != "\n";
    }
};


class SpaceElement : public Element {
public:
    // Constructor
    SpaceElement() : Element("") {
        match = ""; // Equivalent to `self.match = None` in Python
    }

    // Override is_match
    bool is_match(const std::string& ch = "",
                  int str_i = 0,
                  int str_len = 0) const override {
        return ch.length() == 1 && std::isspace(ch[0]);
    }
};

class RangeElement : public LeafNode {

public:
    std::string match;
    std::variant<int, double> min;
    std::variant<int, double> max;
    bool is_positive_logic;
    // Constructor
    RangeElement(const std::string& match_str, bool is_positive_logic = true)
        : LeafNode(), match(match_str), min(1), max(1), is_positive_logic(is_positive_logic) {}

    // Override is_match
    bool is_match(const std::string& ch = "",
                  int str_i = 0,
                  int str_len = 0) const override {
        // XNOR logic: if (ch is in match) is XOR with is_positive_logic
        bool ch_in_match = std::find(match.begin(), match.end(), ch[0]) != match.end();
        return !(ch_in_match ^ is_positive_logic);
    }
};


class StartElement : public LeafNode {
public:
    std::string match;
    std::variant<int, double> min;
    std::variant<int, double> max;
    // Constructor
    StartElement() : LeafNode() {
        match = "";
        min = 1;
        max = 1;
    }

    // Override is_match
    bool is_match(const std::string& ch = "",
                  int str_i = 0,
                  int str_len = 0) const override {
        return str_i == 0;
    }
};

class EndElement : public LeafNode {
public:
    std::string match;
    std::variant<int, double> min;
    std::variant<int, double> max;
    // Constructor
    EndElement() : LeafNode() {
        match = "";  // match is specific to EndElement
        min = 1;     // min is specific to EndElement
        max = 1;     // max is specific to EndElement
    }

    // Override is_match
    bool is_match(const std::string& ch = "",
                  int str_i = 0,
                  int str_len = 0) const override {
        return str_i == str_len;  // Matches when the string index is equal to the string length
    }
};


class OrNode : public ASTNode {
public:
    ASTNode* left;              // Left child node (pointer)
    ASTNode* right;             // Right child node (pointer)
    std::vector<ASTNode*> children; // List of child nodes
    std::variant<int, double> min;
    std::variant<int, double> max;
    // Constructor
    OrNode(ASTNode* left, ASTNode* right) : ASTNode() {
        this->left = left;         // Initialize left child node
        this->right = right;       // Initialize right child node
        this->children.push_back(left);  // Add left to children vector
        this->children.push_back(right); // Add right to children vector
        this->min = 1;             // Initialize min to 1
        this->max = 1;             // Initialize max to 1
}};


class GroupNode : public ASTNode {
    
public:
    bool __capturing__;
    string group_name;
    int group_id;
    deque<shared_ptr<ASTNode>> children;
    variant<int, double> min;
    variant<int, double> max;

    // Constructor with optional parameters
    GroupNode(deque<shared_ptr<ASTNode>> children,
              bool capturing = false,
              string group_name = "",
              int group_id = -1)
        : __capturing__(capturing), group_id(group_id), min(1), max(1) {
        // Set group_name based on group_id if not provided
        this->group_name = (group_name.empty()) ? "Group" + to_string(this->group_id) : group_name;
        this->children = children;
    }

    // Method to check if this group is capturing
    bool is_capturing() const {
        return __capturing__;
    }

};

/////////////////////TEST///////////////////////////////////



