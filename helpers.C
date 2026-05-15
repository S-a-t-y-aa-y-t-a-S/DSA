#include<stdio.h>


struct stack {
    int size;
    int top;
    struct node** arr;
};


int isEmptyStack(struct stack st) {
    return st.top == -1;
}

int isFullStack(struct stack st) {
    return st.size == st.top+1;
}


void push(struct stack* st, struct node* ptr) {
    if (!isFullStack(*st)) {
        st->top ++;
        st->arr[st->top] = ptr;
    }
    else
        printf ("Stack overflow\n");
}


struct node* pop(struct stack* st) {
    struct node* ptr = 0;
    if (!isEmptyStack(*st)) {
        ptr = st->arr[st->top];
        st->top --;
    }
    else
        printf ("Stack underflow\n");
    return ptr;
}


struct node* stackTop(struct stack st) {
    if (!isEmptyStack(st))
        return st.arr[st.top];
    return 0;
}

struct stack createStack(int size) {
    struct stack st;
    st.top = -1;
    st.size = size;
    st.arr = (struct node**) malloc (size*sizeof(struct node*));
    return st;
}
