#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

// Token definitions from your lexer
enum Token {
    END_OF_FILE = -1,
    UNKNOWN = 0,
    LETTER = 1,
    DIGIT = 2,
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,
    IDENTIFIER,
    ASSIGN_OPERATOR,
    ADDITION_OPERATOR,
    SUBTRACTION_OPERATOR,
    MULTIPLICATION_OPERATOR,
    DIVISION_OPERATOR,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    DOT,
    COMMA,
    SEMICOLON,
    COLON,
    KEYWORD_PUBLIC,
    KEYWORD_CLASS,
    KEYWORD_STATIC,
    KEYWORD_VOID,
    KEYWORD_SYSTEM,
    KEYWORD_OUT,
    KEYWORD_FUNCTION,
    KEYWORD_INT,
    KEYWORD_STRING,
    KEYWORD_PRINTLN,
    KEYWORD_MAIN,
    KEYWORD_PRINT
};

#define MAX_LEXEME 100

// External variables shared from your lexer
extern FILE *fp;
extern char lexeme[MAX_LEXEME];
extern int next_token;

// Functions shared from your lexer
extern void get_char();
extern int lex();

#endif