#include "includes/include.h"

int main (int argc, char **argv) {
    if(argc != 2) {
        printf("Invalid format, usage: %s <asm_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    Token tokens[MAX_TOKENS];
   // Token *tokens = (Token*)malloc(sizeof(Token) * 2);


    Labels label[MAX_LABELS];
    FILE *file_asm = fopen(argv[1], "r");
    if(file_asm == NULL) {
        printf("Cannot open %s file\n", argv[1]);            
        exit(EXIT_FAILURE);
    }


    FILE *file_error = fopen("errors_file.txt", "w");
    if(file_error == NULL) {
        printf("Cannot open 'errors_file.txt' file\n");
        fclose(file_asm);      
        exit(EXIT_FAILURE);
    }


    lexical_analyzer(file_asm, file_error, tokens,label);
    rewind(file_asm);
    syntax_error(file_asm, file_error,label);

    fclose(file_asm);
    fclose(file_error);
 

    return 0;
}
