# NASM Assembly Language Assembler (Analyzer)

## Introduction

The NASM Assembly Language Assembler is a project aimed at developing a simplified assembler for a subset of the NASM (Netwide Assembler) assembly language. Implemented in the C programming language, this project serves as an educational tool to understand the processes involved in assembling assembly code into machine code. It encompasses the fundamental phases of compilation: lexical analysis, syntax analysis, and semantic analysis. By implementing these phases, the assembler can read NASM code, validate it, and report any errors found during the compilation process. Optionally, it can also generate machine code for correctly written assembly instructions.

## Project Overview

### Objectives

- **Read and Process NASM Assembly Code:** The assembler reads assembly code written in a specific subset of NASM instructions from a file.
- **Perform Compilation Phases:** 

    - **Lexical Analysis:** Tokenize the input code into meaningful symbols.

    - **Syntax Analysis** Check the code against grammatical rules of the assembly language.

    - **Semantic Analysis:** Validate the logical correctness of the code.

- **Error Reporting** Identify and report errors at each stage with clear messages.
- **Optional Code Generation:** Compile error-free assembly code into machine code (binary format).

## Supported NASM Instructions
The assembler supports a subset of NASM instructions commonly used in basic assembly programming:

- **MOV:** Move data from a source to a destination.

    - **Syntax:**  mov destination, source

    - **Operands:** 
        - **Destination**  Register or memory location.

        - **Source** Register, immediate value, or memory location.

    - **Example** mov eax, ebx

- **MOV:** Move data from a source to a destination.

    - **Syntax:**  mov destination, source

    - **Operands:** 
        - **Destination**  Register or memory location.

        - **Source** Register, immediate value, or memory location.

    - **Example** mov eax, ebx

- **ADD:**Add two operands and store the result in the destination.

    - **Syntax:** add destination, source

    - **Operands:** 
        - **Destination**  Register or memory location.

        - **Source** Register or immediate value

    - **Example** add eax, ebx

- **SUB:** Subtract the source operand from the destination operand.

    - **Syntax:**  sub destination, source

    - **Operands:** 
        - **Destination**  Register or memory location.

        - **Source** Register or immediate value

    - **Example** sub eax, ebx

- **CMP:**  Compare two operands.

    - **Syntax:**  cmp operand1, operand2

    - **Operands:** 
        - **Operand1**  Register or memory location.

        - **Operand2** Register or memory location.

    - **Example** cmp eax, ebx

- **JMP:**  Unconditionally jump to a label.

    - **Syntax:**  jmp label or jmp label:

    - **Operands:** 
        - **Labels**  A defined label in the code.

    - **Example** jmp start_loop

- **LABELS:**  Define a location in the code that can be referenced.

    - **Syntax:**  label_name:

    - **Example** start_loop:

### Note: 
The assembler handles registers (eax, ebx, ecx, edx), immediate values (numeric constants), and labels. Memory addressing (e.g., [eax]) can be included as an extension

# Assembler Phases

The assembler processes assembly code in three main phases: **Lexical Analysis**, **Syntax Analysis**, and **Semantic Analysis**

## 1. Lexical Analysis (Scanning)
**Objective**: Convert the input code into a sequence of tokens.

### Process:
1. Read the input file line by line.
2. Break each line into tokens: identifiers, keywords, numbers, and symbols.
3. Classify tokens into categories:
    - **Instructions**: `mov`, `add`, `sub`, etc.
    - **Registers**: `eax`, `ebx`, `ecx`, `edx`.
    - **Immediate Values**: Numeric constants (e.g., `1`, `0x80`).
    - **Labels**: User-defined identifiers followed by a colon (e.g., `loop_start:`).
    - **Operators and Separators**: Commas, colons, etc.

### Output:
A list of tokens for each line to be used in syntax analysis.

---

## 2. Syntax Analysis (Parsing)
**Objective**: Ensure that the sequence of tokens conforms to the grammatical rules of the assembly language.

### Process:
1. For each line, construct a parse tree or use recursive descent parsing.
2. Check the structure against defined syntax patterns:
    - **Instruction format**: Verify the correct number and type of operands.
    - **Label definitions**: Check for correct placement and naming conventions.
    - **Separators**: Ensure proper use of commas and other separators.

### Common Syntax Rules:
- Instructions must have the correct number of operands.
- Operands must be separated by commas.
- Labels must be unique and end with a colon.

### Output:
Confirmation of correct syntax or a list of syntax errors.

---

## 3. Semantic Analysis
**Objective**: Validate the logical correctness of the code.

### Process:
1. Check operand compatibility:
    - Ensure that operations use valid operand types (e.g., cannot move a register into an immediate value).
2. Validate label references:
    - Ensure that all referenced labels are defined.
3. Check for other semantic rules:
    - Register constraints.
    - Immediate value limitations.

### Output:
Confirmation of semantic correctness or a list of semantic errors.


# Error Handling in Assembler Phases

## 1. Lexical Errors
**Detection**: Occurs when unrecognized tokens are encountered during tokenization.

### Examples:
- **Misspelled Instructions**: 
    - Incorrect: `moov eax, ebx`
    - Correct: `mov eax, ebx`
- **Invalid Characters**: 
    - Incorrect: `mov eax, @ebx`
    - Correct: `mov eax, ebx`

### Reporting:
- **Line number** and a description of the invalid token are provided.

---

## 2. Syntax Errors
**Detection**: Occurs when the structure of the instructions does not match the expected syntax.

### Examples:
- **Incorrect Number of Operands**:
    - Incorrect: `add eax`
    - Correct: `add eax, ebx`
- **Missing Commas between Operands**:
    - Incorrect: `mov eax ebx`
    - Correct: `mov eax, ebx`
- **Misplaced Labels or Directives**:
    - Incorrect placement of a label or directive within the code.

### Reporting:
- **Line number** and a description of the syntax issue are provided.

---

## 3. Semantic Errors
**Detection**: Occurs when there is an invalid use of operands or undefined references.

### Examples:
- **Using an Immediate Value as a Destination Operand**:
    - Incorrect: `mov 5, eax`
    - Correct: `mov eax, 5`
- **Referencing an Undefined Label**:
    - Incorrect: `jmp undefined_label`
    - Correct: Ensure the label is defined before using it.

### Reporting:
- **Line number** and a detailed explanation of the semantic error are provided.




