#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

FILE *fp;

int char_class;
char lexeme[MAX_LEXEME];
char next_char;
int lex_length;
int next_token;

void get_char();
void add_char();
void get_non_blank();
int lookup(char ch);
int lex();
int check_keyword(char *str);

int check_keyword(char *str) {
    if (strcmp(str, "public") == 0) return KEYWORD_PUBLIC;
    if (strcmp(str, "class") == 0) return KEYWORD_CLASS;
    if (strcmp(str, "static") == 0) return KEYWORD_STATIC;
    if (strcmp(str, "void") == 0) return KEYWORD_VOID;
    if (strcmp(str, "System") == 0) return KEYWORD_SYSTEM;
    if (strcmp(str, "out") == 0) return KEYWORD_OUT;
    if (strcmp(str, "def") == 0) return KEYWORD_FUNCTION;
    if (strcmp(str, "int") == 0) return KEYWORD_INT;
    if (strcmp(str, "String") == 0) return KEYWORD_STRING;
    if (strcmp(str, "println") == 0) return KEYWORD_PRINTLN;
    if (strcmp(str, "main") == 0) return KEYWORD_MAIN;
    if (strcmp(str, "print") == 0) return KEYWORD_PRINT;
    return IDENTIFIER;
}

void add_char() {
    if (lex_length < MAX_LEXEME - 1) {
        lexeme[lex_length++] = next_char;
        lexeme[lex_length] = '\0';
    }
}

void get_char() {
    int c = fgetc(fp);

    if (c == EOF) {
        char_class = END_OF_FILE;
        next_char = 0;
    } else {
        next_char = (char)c;
        if (isalpha(next_char) || next_char == '_')
            char_class = LETTER;
        else if (isdigit(next_char))
            char_class = DIGIT;
        else
            char_class = UNKNOWN;
    }
}

void get_non_blank() {
    while (isspace(next_char))
        get_char();
}

int lookup(char ch) {
    switch (ch) {
        case '(': add_char(); return LEFT_PARENTHESIS;
        case ')': add_char(); return RIGHT_PARENTHESIS;
        case '{': add_char(); return LEFT_BRACKET;
        case '}': add_char(); return RIGHT_BRACKET;
        case '[': add_char(); return LEFT_SQUARE_BRACKET;
        case ']': add_char(); return RIGHT_SQUARE_BRACKET;
        case '+': add_char(); return ADDITION_OPERATOR;
        case '-': add_char(); return SUBTRACTION_OPERATOR;
        case '*': add_char(); return MULTIPLICATION_OPERATOR;
        case '/': add_char(); return DIVISION_OPERATOR;
        case '=': add_char(); return ASSIGN_OPERATOR;
        case ';': add_char(); return SEMICOLON;
        case ',': add_char(); return COMMA;
        case '.': add_char(); return DOT;
        case ':': add_char(); return COLON;
        default:  add_char(); return UNKNOWN;
    }
}

int lex() {
    lex_length = 0;
    get_non_blank();

    switch (char_class) {
        case LETTER:
            add_char();
            get_char();
            while (char_class == LETTER || char_class == DIGIT || next_char == '_') {
                add_char();
                get_char();
            }
            next_token = check_keyword(lexeme);
            break;

        case DIGIT:
            add_char();
            get_char();
            while (char_class == DIGIT) {
                add_char();
                get_char();
            }

            if (next_char == '.') {
                add_char();
                get_char();
                while (char_class == DIGIT) {
                    add_char();
                    get_char();
                }
                next_token = FLOAT_LITERAL;
            } else {
                next_token = INT_LITERAL;
            }
            break;

        case UNKNOWN:
            if (next_char == '\'' || next_char == '"') {
                char quote = next_char;
                add_char();
                get_char();

                while (next_char != quote && char_class != END_OF_FILE) {
                    add_char();
                    get_char();
                }

                add_char();
                get_char();
                next_token = STRING_LITERAL;
                break;
            }

            next_token = lookup(next_char);
            get_char();
            break;

        case END_OF_FILE:
            next_token = END_OF_FILE;
            strcpy(lexeme, "EOF");
            break;
    }

    printf("Next token is: %d Next lexeme is %s\n", next_token, lexeme);
    return next_token;
}

/*
int main() {
    char file_path[256];

    printf("Enter file path: ");
    scanf("%255s", file_path);

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    get_char();

    do {
        lex();
    } while (next_token != END_OF_FILE);

    fclose(fp);
    return 0;
}
*/