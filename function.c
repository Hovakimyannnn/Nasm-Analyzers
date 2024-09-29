#include "includes/include.h"

int line_count = 0;
int tokens_count = 0;
int labels_count = 0;
int max_tokens = 2;
int max_labels = 2;
char *nams_inst_with_jmp[] = {"mov", "add", "sub", "cmp","jmp"};
char *nasm_instructions[] = {"mov", "add", "sub", "cmp"};
char *registers[] = {"eax", "ebx", "ecx", "edx","esi","edi"};
char *registers_comma[] = {"eax,", "ebx,", "ecx,", "edx,","esi,","edi,"};
char *registers_comma_new_line[] = {"eax,\n", "ebx,\n", "ecx,\n", "edx,\n","esi,\n","edi,\n"};
char *directives[] = {".data\n", ".text\n", ".bss\n"}; 
char global_label[128];


//-------------------------Start-Syntax-Functions---------------------------//
int is_label_syntax(char *buffer, char *global_label) {
    return strcmp(buffer, global_label) == 0;
}

int is_register_comma_syntax(char *buffer) {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        if (strcmp(buffer, registers_comma[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_instruction_syntax(char *buffer) {
    for (int i = 0; i < INSTRUCTIONS; i++) {
        if (strcmp(buffer, nasm_instructions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_number_comma_syntax(char *buffer) {
    for (int i = 0; i < strlen(buffer) - 1; i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            if(buffer[i] == '-') {
                continue;
            }
            return 0;
        }
    }
    return buffer[strlen(buffer) - 3] != ',';
}

int is_number_syntax(char *buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            if(buffer[i] == '-') {
                continue;
            }
            return 0;
        }
    }
    return 1;
}

int is_register_syntax(char *buffer) {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        if (strcmp(buffer, registers[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_register_comma_new_line(char *buffer) {
    for (int i = 0; i < INSTRUCTIONS; i++) {
        if (strcmp(buffer, registers_comma_new_line[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
//---------------------------------End-Syntax-Functions----------------------------------//


//---------------------------------Start-Analyze-Functions----------------------------------//
int is_register(char *buffer, Token *obj) {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        if (strncmp(buffer, registers[i], strlen(registers[i])) == 0) {
            obj[tokens_count].type = TOKEN_REGISTER;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, buffer);
            tokens_count++;
            if (buffer[strlen(registers[i])] == ',') { 
                obj[tokens_count].type = TOKEN_SEPARATOR;
                obj[tokens_count].line_number = line_count + 1;
                strcpy(obj[tokens_count].lexeme, ",");
                tokens_count++;
            }
            return 1;
        }
    }
    return 0;
}


int is_instruction(char *buffer, Token *obj) {
    for (int i = 0; i < INSTRUCTIONS; i++) {
        if (strcmp(buffer, nams_inst_with_jmp[i]) == 0) {
            obj[tokens_count].type = TOKEN_INSTRUCTION;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, buffer);
            tokens_count++;
            return 1;
        }
    }
    return 0;
}

int is_number(char *buffer, Token *obj) {
    int is_number(char *buffer, Token *obj) {
    if (buffer[0] == '-' && strlen(buffer) == 1) return 0;
    for (int i = (buffer[0] == '-' ? 1 : 0); i < strlen(buffer); i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            return 0;
        }
    }
    obj[tokens_count].type = TOKEN_IMMEDIATE;
    obj[tokens_count].line_number = line_count + 1;
    strcpy(obj[tokens_count].lexeme, buffer);
    tokens_count++;
    return 1;
}
}

int is_label(char *buffer, Token *obj, Labels *label) {
    int location = strlen(buffer);
    if (buffer[location - 1] == ':') { 
        obj[tokens_count].type = TOKEN_LABEL_DEF;
        obj[tokens_count].line_number = line_count + 1;
        buffer[location - 1] = '\0'; 
        strcpy(obj[tokens_count].lexeme, buffer);
        tokens_count++;
        return 1;
    }
    return 0;
}


int is_directive(char *buffer, Token *obj) {
       if(strcmp(buffer, ".data\n") == 0) {
            obj[tokens_count].type = TOKEN_DIRECTIVE;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, buffer);
            tokens_count++;
            return 1;
       }else if(strcmp(buffer, ".text\n") == 0) {
            obj[tokens_count].type = TOKEN_DIRECTIVE;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, buffer);
            tokens_count++;
            return 1;
       }else if(strcmp(buffer,".bss\n") == 0) {
            obj[tokens_count].type = TOKEN_DIRECTIVE;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, buffer);
            tokens_count++;
            return 1;
       }
    return 0;
}
int is_ref_label(char *buffer, Token *obj,Labels *label) {
    for (int i = 0; i < labels_count; i++) {
        if (strcmp(label[i].label, buffer) == 0) {
            obj[tokens_count].type = TOKEN_LABEL_REF;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, buffer);
            tokens_count++;
            return 1;
        }
    }
    return 0;
}
int find_character_in_last_place(const char *str, char ch) {
    int length = strlen(str);

    if (str[length - 1] == ch) {
        return length - 1; 
    }

    return -1; 
}
int is_instruction_label(char *buffer) {
    for(int i = 0; i < INSTRUCTIONS; i++) {
        if(strcmp(buffer,nams_inst_with_jmp[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//------------------------------End--Analyzer-Functions-----------------------------//


void analyzer(char *buffer, FILE *error_file, Token *obj, Labels *label) {
    int index = 0, args_count = 0;
    char *args[256];
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        args[index++] = token;
        token = strtok(NULL, " ");
    }
    int flag = 0;
    /*if (tokens_count + 1 == max_tokens) {
        
        Token *temp = realloc(obj, sizeof(Token) * (max_tokens * 2));  
         if (temp == NULL) {
            printf("Reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        printf("Tokens Malloc");
        obj = temp;  
        max_tokens *= 2;  
    }*/
    /*if(labels_count + 1 == max_labels) {
        Labels *temp = realloc(label, sizeof(Labels) * (max_labels * 2));
        if(temp == NULL) {
            printf("Reallocation failed\n");
            exit(EXIT_FAILURE);
        }
        label = temp;  
        max_tokens *= 2; 
    }*/
    if(*buffer == '\n') {
        fprintf(error_file, "Line %d: NewLine\n", line_count + 1);
        obj[tokens_count].type = TOKEN_NEW_LINE;
        obj[tokens_count].line_number = line_count + 1;
        strcpy(obj[tokens_count].lexeme, buffer);
        tokens_count++;
        return;
    }

    while (args_count != index) {
        if(index == 1) {
            if(is_instruction_syntax(args[args_count]) || is_register_syntax(args[args_count]) || is_number_syntax(args[args_count])) {
                fprintf(error_file,"Line %d: Successfully\n",line_count + 1);
                return;
            }
            int res = find_character_in_last_place(args[args_count],':');
            if(res != -1) {
                fprintf(error_file, "Line %d: Unknown Symbol\n",line_count + 1);
                return;
            }else {
                fprintf(error_file,"Line %d: Successfully\n",line_count + 1);
                obj[tokens_count].type = TOKEN_LABEL_DEF;
                obj[tokens_count].line_number = line_count + 1;
                strcpy(obj[tokens_count].lexeme, buffer);
                tokens_count++;
                strcpy(label[labels_count].label,args[args_count]);
                labels_count++;
                return;
            }
        }
        if (strcmp(args[args_count], "section") == 0) {
            obj[tokens_count].type = TOKEN_SECTION;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, args[args_count]);
            tokens_count++;
            //printf("%s\n", args[args_count]);
            args_count++;
            
            continue;
        } else if (strcmp(args[args_count], "global") == 0) {
            obj[tokens_count].type = TOKEN_LABEL_DEF;
            obj[tokens_count].line_number = line_count + 1;
            strcpy(obj[tokens_count].lexeme, args[args_count]);
            tokens_count++;
            //printf("Global %s\n", args[args_count]);
            args_count++;
            strcpy(label[labels_count].label ,args[args_count]);
            //printf("Label global  %s\n", label[labels_count].label);
            labels_count++;
            break;
        } else if (is_directive(args[args_count], obj)) {
            //printf(" %s\n", args[args_count]);
            args_count++;
            continue;
        } else if (is_register(args[args_count], obj)) {
            //printf(" %s\n", args[args_count]);
            args_count++;
            continue;
        } else if (is_instruction(args[args_count], obj)) {
            //printf(" %s\n", args[args_count]);
            // if(strcmp(args[args_count], "jmp") == 0) {
            //     args_count++;
            //     strcpy(label[labels_count].label,args[args_count]); 
            //     labels_count++;
            // }else {
            //     args_count++;
            // }
            args_count++;
            continue;
        } else if (is_number(args[args_count], obj)) {
            //printf("%s\n", args[args_count]);
            args_count++;
            continue;
        } else if (is_label(args[args_count], obj,label)) {
            args_count++;
            strcpy(label[labels_count].label, buffer);
            label[labels_count].label[strcspn(label[labels_count].label, "\n")] = ':';
            printf("Is label function %d\n",label[labels_count].label);
            labels_count++;
            continue;
        } /*else if(is_ref_label(args[args_count], obj,label)) {
            printf("Href Label %s\n", args[args_count]);
            args_count++;
            continue;
        }*/else {
            flag = 1;
            args_count++;
        }
    }

    if (flag == 0) {
        fprintf(error_file, "Line %d: Successfully\n", line_count + 1);
        return;
    }else {
        fprintf(error_file, "Line %d: Error Unknown token '%s'\n",line_count + 1, args[args_count - 1], line_count + 1);
        return;
    }
}

void lexical_analyzer(FILE *file_asm, FILE *file_error, Token *token,Labels *label) {
    fprintf(file_error, "Lexical Analyze\n");
    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, sizeof(buffer), file_asm) != NULL) {
        analyzer(buffer, file_error, token,label);
        line_count++;
    }
    for(int i = 0; i < labels_count; i++) {
        printf("%s", label[i].label);
    }
}

void syntax_analyzer(char *buffer, FILE *file_error, Labels *label) {
    if(*buffer == '\n') {
        fprintf(file_error, "Line %d: Success NewLine\n", line_count + 1);
        return;
    }
    
    int index = 0, args_count = 0;
    char *args[256];
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        args[index++] = token;
        token = strtok(NULL, " ");
    }
    if (index >= 4) {
        fprintf(file_error, "Line %d: Error Too Many Arguments Main\n", line_count + 1);
        return;
    }
    if (index == 1) {
        if(is_instruction_label(args[args_count])) {
            fprintf(file_error,"Line %d: Instruction Cant Be Label\n",line_count + 1);
            return;
        }else if(is_register_syntax(args[args_count]) ) {
            fprintf(file_error, "Line %d: Register Cant be Label\n",line_count + 1);
            return;
        }else if(is_number_syntax(args[args_count])) {
            fprintf(file_error, "Line %d: Number  Cant be Label\n",line_count + 1);
            return;
        }
        int flag = 0;
        for (int i = 0; i < labels_count; i++) {
            if (strcmp(label[i].label, args[args_count]) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            fprintf(file_error, "Line %d: Success Label\n", line_count + 1);
        } else {
            fprintf(file_error, "Line %d: Unknown Label\n", line_count + 1);
        }
        return;
    }else if(strcmp(args[args_count],"jmp") == 0){
        args_count++;
        int flag = 0;
        for(int i = 0; i < labels_count; i++) {
            if(strcmp(label[i].label,args[args_count]) == 0) {
                flag = 1;
            }
        }
        if(flag == 1) {
            fprintf(file_error, "Line %d: Success Href Label\n", line_count + 1);
            return;
        }else {
            fprintf(file_error, "Line %d: Unknow Href Label\n", line_count + 1);
            return;
        }
    }if (strncmp(args[args_count], "section", 7) == 0) {
        if (index != 2) {
            fprintf(file_error, "Line %d: Error Too Many Arguments Section\n",line_count + 1);
            return;
        }
        args_count++;
        if (strcmp(args[args_count], ".data\n") == 0 || strcmp(args[args_count], ".text\n") == 0 || strcmp(args[args_count], ".bss\n") == 0) {
            fprintf(file_error, "Line %d: Success Section\n", line_count + 1);
            return;
        }else {
            fprintf(file_error, "Line %d: Unknown Section\n",line_count + 1);
            return;
        }
    }else if (strncmp(args[args_count], "global", 6) == 0) {
        if (index != 2) {
            fprintf(file_error, "Line %d: Error Too Many Arguments Global \n", line_count + 1);
            return;
        } else {
            int flag = 1;
            args_count++;
            for(int i = 0; i < labels_count; i++) {
                if(strcmp(label[i].label,args[args_count]) == 0) {
                    flag = 1;
                }
            }
            if(flag == 1) {
                fprintf(file_error, "Line %d: Success Label\n", line_count + 1);
                return;
            }else {
                fprintf(file_error, "Line %d: Unknow Label\n", line_count + 1);
                return;
            }
        }
    }else if (is_instruction_syntax(args[args_count])) {
        if (index != 3) {
            fprintf(file_error, "Line %d: Error Too Many Or Qi Arguments Instruction\n", line_count + 1);
            return;
        }

        if(strncmp(args[args_count], "mov", 3) == 0) {
            args_count++;
            if(is_number_comma_syntax(args[args_count]) || is_number_syntax(args[args_count])) {
                fprintf(file_error, "Line %d: Semantic Error - Cannot use immediate value as destination\n",line_count + 1);
                return;
            }else if(is_register_comma_syntax(args[args_count]) == 1) {
                fprintf(file_error, "Line %d: Syntax Error Missing Comma\n", line_count + 1);
                return;
            }
            args_count++;
            if(is_register_comma_new_line(args[args_count]) || is_number_comma_syntax(args[args_count]))  {
                fprintf(file_error, "Line %d: Syntax Error Source Comma\n",line_count + 1);
                return;
            }else {
                fprintf(file_error, "Line %d: Success Mov\n", line_count + 1);
                return;
            }
        } 
        else if(strncmp(args[args_count], "add",3) == 0) {
            args_count++;
            if(is_number_comma_syntax(args[args_count]) || is_number_comma_syntax(args[args_count])) {
                fprintf(file_error, "Line %d: Semantic Error - Cannot use immediate value as destination\n",line_count + 1);
                return;
            }
            else if(is_register_syntax(args[args_count])) {
                fprintf(file_error, "Line %d: Syntax Error\n", line_count + 1);
                return;
            }
            args_count++;
            if(is_register_syntax(args[args_count]) || is_number_syntax(args[args_count])) {
                fprintf(file_error, "Line %d: Syntax Error\n", line_count + 1);
                return;
            }
            else {
                fprintf(file_error, "Line %d: Success Add Instruction\n", line_count + 1);
                return;
            }
        }else if(strncmp(args[args_count], "sub",3) == 0) {
            args_count++;
            if(is_number_comma_syntax(args[args_count]) || is_number_comma_syntax(args[args_count])) {
                fprintf(file_error, "Line %d: Semantic Error - Cannot use immediate value as destination\n",line_count + 1);
                return;
            }else if(is_register_syntax(args[args_count]) == 1  && args_count == 1) {
                fprintf(file_error, "Line %d: Syntax Error Missing Comma\n", line_count + 1);
                return;
            }
            args_count++;
            if(is_register_comma_syntax(args[args_count]))  {
                fprintf(file_error, "Line %d: Syntax Error Source Comma\n",line_count + 1);
                return;
            }else if(is_number_comma_syntax(args[args_count])) {
                fprintf(file_error, "Line %d: Syntax Error Source Number Coma\n",line_count + 1);
                return;
            }
            else {
                fprintf(file_error, "Line %d: Success Sub\n", line_count + 1);
                return;
            }
        }  else if (strncmp(args[args_count], "cmp", 3) == 0) {
            if((is_number_syntax(buffer) == 1 || is_register_syntax(buffer) == 1) && args_count == 2) {
                fprintf(file_error, "Line %d: Syntax Error\n", line_count + 1);
                return;
            }else if(is_number_comma_syntax(args[args_count]) == 1|| is_register_comma_syntax(buffer) == 1) {
                fprintf(file_error, "Line %d: Syntax Error\n",line_count + 1);
                return;
            }else if(is_number_comma_syntax(args[args_count]) == 0 && is_register_comma_syntax(args[args_count]) == 0 && is_number_syntax(args[args_count]) == 0 && is_register_syntax(args[args_count]) == 0) {
                fprintf(file_error, "Line %d: Syntax Error\n");
                return;
            }else {
                fprintf(file_error, "Line %d: Success\n",line_count + 1);
            }
        }
    }
}

void syntax_error(FILE *file_asm, FILE *file_error, Labels *label) {
    fprintf(file_error, "Syntax Analyze and Semantic\n");
    line_count = 0;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file_asm) != NULL) {
        syntax_analyzer(buffer, file_error,label);
        line_count++;
    }
}