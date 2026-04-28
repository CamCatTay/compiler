#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

void program();
void statement();
void if_stmt();
void elif_stmt();
void else_block();
void block();
void named_expression();

void error(const char *msg) {
    printf("\nSyntax Error: %s at lexeme '%s'\n", msg, lexeme);
    exit(1);
}

void match(int expected_token) {
    if (next_token == expected_token) {
        lex(); // Advance to the next token
    } else {
        char err_msg[100];
        sprintf(err_msg, "Expected token %d, found %d", expected_token, next_token);
        error(err_msg);
    }
}

void match_pseudo_keyword(const char* expected_lexeme) {
    if (next_token == IDENTIFIER && strcmp(lexeme, expected_lexeme) == 0) {
        lex();
    } else {
        char err_msg[100];
        sprintf(err_msg, "Expected keyword '%s'", expected_lexeme);
        error(err_msg);
    }
}

void named_expression() {
    match(IDENTIFIER);

    if (next_token == UNKNOWN && strcmp(lexeme, "<") == 0) {
        lex();
        match(INT_LITERAL);
    }
    else if (next_token == ASSIGN_OPERATOR) {
        lex();
        match(ASSIGN_OPERATOR);
        match(INT_LITERAL);
    } else {
        error("Expected '<' or '==' in expression");
    }
}

void block() {
    while (next_token != END_OF_FILE) {
        if (next_token == IDENTIFIER && (strcmp(lexeme, "elif") == 0 || strcmp(lexeme, "else") == 0)) {
            break;
        }
        statement();
    }
}

void else_block() {
    match_pseudo_keyword("else");
    match(COLON);
    block();
}

void elif_stmt() {
    match_pseudo_keyword("elif");
    named_expression();
    match(COLON);
    block();

    if (next_token == IDENTIFIER && strcmp(lexeme, "elif") == 0) {
        elif_stmt();
    } else if (next_token == IDENTIFIER && strcmp(lexeme, "else") == 0) {
        else_block();
    }
}

void if_stmt() {
    match_pseudo_keyword("if");
    named_expression();
    match(COLON);
    block();

    if (next_token == IDENTIFIER && strcmp(lexeme, "elif") == 0) {
        elif_stmt();
    } else if (next_token == IDENTIFIER && strcmp(lexeme, "else") == 0) {
        else_block();
    }
}

void statement() {
    if (next_token == IDENTIFIER && strcmp(lexeme, "if") == 0) {
        if_stmt();
    }
    else if (next_token == KEYWORD_PRINT) {
        lex();
        match(LEFT_PARENTHESIS);
        match(STRING_LITERAL);
        match(RIGHT_PARENTHESIS);
    }
    else if (next_token == IDENTIFIER) {
        lex();
        match(ASSIGN_OPERATOR);
        match(INT_LITERAL);
    }
    else {
        error("Invalid statement structure");
    }
}

void program() {
    while (next_token != END_OF_FILE) {
        statement();
    }
    printf("\n>>> Parsing completed successfully! No syntax errors found. <<<\n");
}

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
    lex();

    program();

    fclose(fp);
    return 0;
}