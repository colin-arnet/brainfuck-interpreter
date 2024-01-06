#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "machine.h"
#include "program.h"

// machine config
const int size = 16;


void interp_file(char* filename){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("ERROR: file not found\n");
        return;
    }
    // put file content into a string
    char* source = 0;
    long length;
    fseek(fp, 0 , SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    source = malloc(length);
    if(source != 0){
        fread(source, 1, length, fp);
    }
    // interpret program
    struct Machine* machine = malloc(sizeof(struct Machine));
    machine_init(size, machine);
    int error = interpret(source, machine, length);
    machine_free(machine);
    fclose(fp);
}

void interp_interactive(){
    printf("STARTING INTERACTIVE BRAINFUCK SESSION\n");
    struct Machine* machine = malloc(sizeof(struct Machine));
    machine_init(size, machine);
    int error = 0;
    char source[24];
    while(error != -2){
        printf("--->");
        scanf( " %24[^\n]", source);
        // printf("\n");
        error = interpret(source, machine, 24);
    }
    machine_free(machine);
    return;
}


int main(int argc, char ** argv){
    // check number of arguments
    if(argc != 2){
        printf("ERROR: invalid number of arguments\n");
        return 1;
    }// get file name
    if(strcmp("--interactive", argv[1]) == 0 || strcmp("-i", argv[1]) == 0){
        interp_interactive();
    } else if(strcmp("--help", argv[1]) == 0 || strcmp("-h", argv[1]) == 0){
        printf("BRAINFUCK INTERPRETER BY Colin\n");
        printf("Flags:\n");
        printf("--help, -h: show this message\n");
        printf("--interactive, -i: run interpreter in interactive mode\n");
        printf("<brainfuck_program>.b: runs the brainfuck program\n");
    } else {
        interp_file(argv[1]);
    }
    

    
    return 0;
    
}