#ifndef A
#define A

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <ctype.h>

#define REGISTER_COUNT 4
#define MAX_LEXEME_LENGTH 30
#define BUFFER_SIZE 128
#define MAX_TOKENS 400
#define MAX_LABELS 50
#define INSTRUCTIONS 5
#define DIRECTIVE 3

typedef enum { 
    TOKEN_INSTRUCTION, 
    TOKEN_REGISTER, 
    TOKEN_IMMEDIATE, 
    TOKEN_LABEL_DEF, 
    TOKEN_LABEL_REF, 
    TOKEN_SEPARATOR, 
    TOKEN_DIRECTIVE,
    TOKEN_SECTION,
    TOKEN_NEW_LINE
} TokenType;

typedef struct {
    TokenType type;
    char *lexeme;
    int line_number;
} Token;

typedef struct  {
    char *label;
}Labels;

void lexical_analyzer(FILE *asm_file,FILE *error_file,Token *token, Labels *label);
void syntax_error(FILE *asm_file, FILE *error_file,Labels *label);

#endif // A
