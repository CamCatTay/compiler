#include <stdio.h>
#include <ctype.h>

int char_class;
char lexeme[100];
char next_char;
int lex_length;
int token;
int next_token;

enum Token {

    // char classes
    END_OF_FILE = -1,
    UNKNOWN = 0,
    LETTER = 1,
    DIGIT = 2,
    TAB = 3,

    // literals
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,   // double-quoted  "..."
    CHAR_LITERAL,     // single-quoted  '...'

    // identifiers
    IDENTIFIER,

    // operators
    ASSIGN_OPERATOR,
    ADDITION_OPERATOR,
    SUBTRACTION_OPERATOR,
    MULTIPLICATION_OPERATOR,
    DIVISION_OPERATOR,

    // grouping
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET,
    LEFT_BRACKET,
    RIGHT_BRACKET,

    // separators
    DOT,
    COMMA,
    APOSTROPHE,
    QUOTATION,
    SEMICOLON,
    COLON,

    // modifier keywords
    KEYWORD_PUBLIC,
    KEYWORD_CLASS,
    KEYWORD_STATIC,
    KEYWORD_VOID,
    KEYWORD_SYSTEM,
    KEYWORD_OUT,
    KEYWORD_FUNCTION, // def

    // extra keywords needed for the Java file
    KEYWORD_INT,
    KEYWORD_STRING,
    KEYWORD_PRINTLN,
    KEYWORD_MAIN,
};

KEYWORDS = {
    "public":   Token.KEYWORD_PUBLIC,
    "class":    Token.KEYWORD_CLASS,
    "static":   Token.KEYWORD_STATIC,
    "void":     Token.KEYWORD_VOID,
    "System":   Token.KEYWORD_SYSTEM,
    "out":      Token.KEYWORD_OUT,
    "def":      Token.KEYWORD_FUNCTION,
    "int":      Token.KEYWORD_INT,
    "String":   Token.KEYWORD_STRING,
    "println":  Token.KEYWORD_PRINTLN,
    "main":     Token.KEYWORD_MAIN,
}