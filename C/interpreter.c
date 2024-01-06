#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
#include "program.h"


int interp_plus(struct Machine* machine, struct program_state* program){
    machine->tape[machine->head]++;
    program->position++;
    return 0;
}

int interp_minus(struct Machine* machine, struct program_state* program){
    machine->tape[machine->head]--;
    program->position++;
    return 0;
}

int interp_right(struct Machine* machine, struct program_state* program){
    int new_head = machine->head + 1;
    if(new_head >= machine->size){
        printf("PROGRAM ERROR: TAPE OVERFLOW\n");
        return -1;
    }
    machine->head = new_head;
    program->position++;
    return 0;
}

int interp_left(struct Machine* machine, struct program_state* program){
    int new_head = machine->head - 1;
    if(new_head < 0){
        printf("PROGRAM ERROR: TAPE UNDERFLOW\n");
        return -1;
    }
    machine->head = new_head;
    program->position++;
    return 0;
}

int interp_input(struct Machine* machine, struct program_state* program){
    char input;
    printf("input: ");
    scanf(" %c", &input);
    printf("\n");
    machine->tape[machine->head] = input;
    program->position++;
    return 0;
}

int interp_output(struct Machine* machine, struct program_state* program){
    char output = machine->tape[machine->head];
    printf("%c", output);
    program->position++;
    return 0;
}

int interp_open(struct Machine* machine, struct program_state* program){
    push(&program->loop_stack, program->position);
    program->position++;
    return 0;
}

int interp_close(struct Machine* machine, struct program_state* program){
    if(machine->tape[machine->head] == 0){
        pop(&program->loop_stack);
        program->position++;
    } else {
        int new_pos = top(&program->loop_stack);
        program->position = new_pos + 1;
    }
    return 0;
}


int interp_state(struct Machine* machine, struct program_state* program){
    printf("MACHINE STATE:\nTAPE:\n");
    for(int i = 0; i < machine->size; i++){
        if(i == machine->head){
            printf(" ->%d<- ", machine->tape[i]);
        } else {
            printf(" %d ", machine->tape[i]);
        }
    }
    printf("\n\n");
    program->position++;
    return 0;
}

int interp_exit(struct program_state* program){
    program->position++;
    return -2;
}

int interp_help(struct program_state* program){
    printf("BRAINFUCK INTERACTIVE SESSION HELP:\n");
    printf("Brainfuck Lanugage:\n");
    printf("> : Increment the data pointer (to point to the next cell to the right).\n");
    printf("< : Decrement the data pointer (to point to the next cell to the left).\n");
    printf("+ : Increment (increase by one) the byte at the data pointer.\n");
    printf("- : Decrement (decrease by one) the byte at the data pointer.\n");
    printf(". : Output the byte at the data pointer.\n");
    printf(", : Accept one byte of input, storing its value in the byte at the data pointer.\n");
    printf("[ : If the byte at the data pointer is zero, then instead of moving\n the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.\n");
    printf("] : If the byte at the data pointer is nonzero, then instead of moving\n the instruction pointer forward to the next command, jump it back to the command after the matching [ command.\n");
    printf("\n");
    printf("Session features:\n");
    printf("h : print this message\n");
    printf("s : show state of tape and position of data pointer\n");
    printf("q : leave interactive session\n");
    printf("\n");
    program->position++;
    return 0;
}




int interpret(char* source, struct Machine* machine, long length){
    // open file and check if it exists
    struct program_state* program = malloc(sizeof(struct program_state));
    program_init(0, program);
    int error;
    while(program->position < length){
        char e = source[program->position];
        switch (e)
        {
        case '+':
            error = interp_plus(machine, program);
            break;
        case '-':
            error = interp_minus(machine, program);
            break;
        case '>':
            error = interp_right(machine, program);
            break;
        case '<':
            error = interp_left(machine, program);
            break;
        case ',':
            error = interp_input(machine, program);
            break;
        case '.':
            error = interp_output(machine, program);
            break;
        case '[':
            error = interp_open(machine, program);
            break;
        case ']':
            error = interp_close(machine, program);
            break;
        case 's':
            error = interp_state(machine, program);
            break;
        case 'q':
            error = interp_exit(program);
            break;
        case 'h':
            error = interp_help(program);
            break;     
        default:
            program->position++;
            break;
        }
        if(error == -1){
            printf("ERROR: EXIT PROGRAM\n");
            return -1;
        }
        if(error == -2){
            printf("EXIT INTERACTIVE SESSION\n");
            return -2;
        }
    }
    return error;
    program_free(program);
    printf("\n");
}