struct Machine
{
    unsigned char* tape;
    int head;
    int size;
};

void machine_init(const int size, struct Machine* machine);
void machine_free(struct Machine* machine);
