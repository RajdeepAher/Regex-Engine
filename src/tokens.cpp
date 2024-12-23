#include <string>
#include <iostream>
#include <cassert>
using namespace std;

class Token{
    // A general token class
    public:
        Token() : char_("") {}

        string char_;

        virtual ~Token() {}
        
};

class ElementToken: public Token{
    // Token with no special meaning
    public:
        ElementToken(const string &ch){
            char_ = ch;
        }
};

class WildcardToken: public Token {
    //
    public:
        WildcardToken(const string &ch){
            char_ = ch;
        }
};

class Wildcard : public WildcardToken {
    public:
        // "Token using '.' as a wildcard"
        Wildcard() : WildcardToken(".") {} 

};


class SpaceToken: public Token {
    public:
        SpaceToken(char ch){
            char_ = ch;
            //can it be replaced by
            // char = " ";
            // Includes space, tab, newline, carriage return, form feed, and vertical tab
        }
};

class StartToken: public Token {
    //Parent Class of Start Token
    public:
        StartToken(const string &ch){
            char_ = ch;
        }
};

class Start : public StartToken {
    // "Token using '^' to match start"
    public:
        Start() : StartToken("^") {} 
};

class EndToken: public Token {
    //Parent Class of End Token
    public:
        EndToken(const string &ch){
            char_ = ch;
        }
};

class End: public EndToken{
    public:
        End() : EndToken("$") {}
};

class Escape: public Token {
    public:
        Escape(const string &ch){
            char_ = '\\';
        }
};

class Comma: public Token {
    public:
        Comma(){
            char_ = ',';
        }
};

//..................................

class Parenthesis: public Token {
    public:
        Parenthesis () {}
};

class LeftParenthesis: public Parenthesis{
    public:
        LeftParenthesis(){
            char_ = '(';
        }
};

class RightParenthesis: public Parenthesis{
    public:
        RightParenthesis(){
            char_ = ')';
        }
};

//......................................................

class CurlyBrace: public Token{
    public:
        CurlyBrace(){}
};

class LeftCurlyBrace: public CurlyBrace{
    public:
        LeftCurlyBrace(){
            char_ = '{';
        }
};

class RightCurlyBrace: public CurlyBrace{
    public:
        RightCurlyBrace(){
            char_ = '}';
        }
};

//.........................................................

class Bracket: public Token{
    public:
        Bracket(){}
};

class leftBracket: public Bracket{
    public:
        leftBracket(){
            char_ = '[';
        }
};

class RightBracket: public Bracket{
    public:
        RightBracket(){
            char_ = ']';
        }
};

//.........................................................

class Quantifier: public Token{
    public:
        Quantifier(const string &ch){
            char_ = ch;
        }
};

class ZeroOrMore : public Quantifier {
public:
    ZeroOrMore(const std::string& ch) : Quantifier(ch) {}
};

class OneOrMore : public Quantifier {
public:
    OneOrMore(const std::string& ch) : Quantifier(ch) {}
};

class ZeroOrOne : public Quantifier {
public:
    ZeroOrOne(const std::string& ch) : Quantifier(ch) {}
};

class Asterisk : public ZeroOrMore{
    public:
        Asterisk() : ZeroOrMore("*"){}
};

class Plus : public OneOrMore{
    public:
        Plus(): OneOrMore("+"){}
};

class QuestionMark: public ZeroOrOne{
    public:
        QuestionMark(): ZeroOrOne("?"){}
};

//...........................................................


class OrToken: public Token{
    public:
        OrToken(const string &ch){
            char_ = ch;
        }
};

class VerticalBar: public OrToken{
    public:
        VerticalBar(): OrToken("|") {}
};

class NotToken: public Token{
    public:
        NotToken(const string &ch){
            char_ = ch;
        }
};

class Circumflex: public NotToken{
    public:
        Circumflex(): NotToken("^") {}
};

//.........................................................

class Dash: public Token{
    public:
        Dash(){
            char_ = "-";
        }
};


