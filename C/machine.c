#include <stdio.h>
#include <stdlib.h>
#include "machine.h"
#include "program.h"

void machine_init(const int size, struct Machine* machine){
    machine->tape = malloc(size);
    machine->head = 0;
    machine->size = size;
    for(int i = 0; i < size; i++){
        machine->tape[i] = 0;
    }
}

void machine_free(struct Machine* machine){
    free(machine->tape);
    free(machine);
}
