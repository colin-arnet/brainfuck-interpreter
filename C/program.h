struct Element{
    int value;
    struct Element* next;
};

struct program_state{
    int position;
    struct Element* loop_stack;
};

void push(struct Element** head, int value);
int pop(struct Element** head);
int top(struct Element** head);

void program_init(int position, struct program_state* program);
void program_free(struct program_state* program);