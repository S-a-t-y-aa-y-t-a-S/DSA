#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* lchild;
    struct node* rchild;
    int height;
};

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

struct node* createNode(int data) {
    struct node* newNode = (struct node*) malloc (sizeof(struct node));
    newNode->data = data;
    newNode->lchild = 0;
    newNode->rchild = 0;
    newNode->height = 0;
    return newNode;
}


void avlRotation(struct node** parentNode, struct node** currentNode, int data) {
    
    if ((*currentNode && (*currentNode)->lchild) && ((*currentNode)->data > data && (*currentNode)->lchild->data > data)) {
        // LL rotation
        if (!*parentNode) {
            *parentNode = (*currentNode)->lchild;
            (*currentNode)->lchild = (*parentNode)->rchild;
            (*parentNode)->rchild = *currentNode;
            return;
        }   
        struct node* temp = 0;
        if ((*parentNode)->rchild == *currentNode) {
            (*parentNode)->rchild = (*currentNode)->lchild;
            (*currentNode)->lchild = temp;
            temp = (*parentNode)->rchild;
        }
        else if ((*parentNode)->lchild == *currentNode) {
            (*parentNode)->lchild = (*currentNode)->lchild;
            (*currentNode)->rchild = temp;
            temp = (*parentNode)->lchild;
        }
        
        (*currentNode)->lchild = temp->rchild;
        temp->rchild = *currentNode;
    }
    
    else if ((*currentNode && (*currentNode)->lchild) && ((*currentNode)->data > data && (*currentNode)->lchild->data < data)) {
        // LR rotation
        struct node* shiftedUpNode = (*currentNode)->lchild->rchild;
        
        (*currentNode)->lchild->rchild = shiftedUpNode->lchild;
        shiftedUpNode->lchild = (*currentNode)->lchild;
        (*currentNode)->lchild = shiftedUpNode->rchild;
        shiftedUpNode->rchild = *currentNode;
        
        if (!*parentNode)
            *parentNode = shiftedUpNode;
        else if ((*parentNode)->lchild == *currentNode)
            (*parentNode)->lchild = shiftedUpNode;
        else
            (*parentNode)->rchild = shiftedUpNode;
        
    }
    
    else if ((*currentNode && (*currentNode)->rchild) && ((*currentNode)->data < data && (*currentNode)->rchild->data > data)) {
        // RL rotation
        struct node* shiftedUpNode = (*currentNode)->rchild->lchild;
        
        (*currentNode)->rchild->lchild = shiftedUpNode->rchild;
        shiftedUpNode->rchild = (*currentNode)->rchild;
        (*currentNode)->rchild = shiftedUpNode->lchild;
        shiftedUpNode->lchild = *currentNode;
        
        if (!*parentNode)
            *parentNode = shiftedUpNode;             
        else if ((*parentNode)->lchild == *currentNode)
            (*parentNode)->lchild = shiftedUpNode;
        else
            (*parentNode)->rchild = shiftedUpNode;    
    }
    
    else if ((*currentNode && (*currentNode)->rchild) && ((*currentNode)->data < data && (*currentNode)->rchild->data < data)) {
        // RR rotation
        if (!*parentNode) {
            *parentNode = (*currentNode)->rchild;
            (*currentNode)->rchild = (*parentNode)->lchild;
            (*parentNode)->lchild = *currentNode;
            return;
        }   
        struct node *temp = 0;
        if ((*parentNode)->rchild == *currentNode) {
            (*parentNode)->rchild = (*currentNode)->rchild;
            temp = (*parentNode)->rchild;
        }
        else if ((*parentNode)->lchild == *currentNode) {
            (*parentNode)->lchild = (*currentNode)->rchild;
            (*parentNode)->lchild->lchild = *currentNode;
        }
        (*currentNode)->rchild = temp->lchild;
        temp->lchild = *currentNode;
        
    }
    
}


int getHeight(struct stack st, struct node* currentNode, int totalHeight) { // evaluates height
    int height = totalHeight-(st.top+1);
    
    if (height > currentNode->height)
        currentNode->height = height;
        
    return height;
}

int balanceFactor(struct node* currentNode) {
    int leftSubTreeHeight = 0;
    int rightSubTreeHeight = 0;
    
    if (currentNode->lchild)
        leftSubTreeHeight = currentNode->lchild->height+1;
    
    if (currentNode->rchild)
        rightSubTreeHeight = currentNode->rchild->height+1;
    
    return leftSubTreeHeight-rightSubTreeHeight;
}


void checkForRotation(
    struct node** rootNode, 
    struct node** parentNode, 
    struct node** currentNode, 
    struct stack* st, int totalHeight, 
    int data) {
    
    while (!isEmptyStack(*st)) {
        *currentNode = pop(st);
        if (!isEmptyStack(*st))
            *parentNode = stackTop(*st);
        else
            *parentNode = 0;
        
        (*currentNode)->height = getHeight(*st, *currentNode, totalHeight);
        int bf = balanceFactor(*currentNode);
        if (bf > 1 || bf < -1) {
            
            struct node* temp = *parentNode;
            
            avlRotation(parentNode, currentNode, data);
            (*currentNode)->height = getHeight(*st, *currentNode, totalHeight);
            
            if (!temp)
                *rootNode = *parentNode;
        }
    }
}

void inOrderSuccessor(struct node* currentNode, struct stack* st) {
    struct node* ptr = currentNode->rchild;
    
    while (ptr) {
        struct node* trail = ptr;
        ptr = ptr->lchild;
        
        push(st, trail);
    }
    return;
}


struct node* searchAKey(struct node* rootnode, struct stack* st, int key, char choice) {
    struct node* ptr = rootnode;
    struct node* trail = ptr;
    while (ptr) {
        
        trail = ptr;
        if (ptr->data == key)
            break;
        else if (ptr->data > key)
            ptr = ptr->lchild;
        else if (ptr->data < key)
            ptr = ptr->rchild;
        
        push(st, trail);
    }
    if (ptr) {
        if (choice == 'D') {
            push(st, ptr);
            inOrderSuccessor(ptr, st);
        }
    }
    return ptr;
}

void insertNode(struct node** rootNode, int data) {
    if (*rootNode) {
        
        struct node* ptr = *rootNode;
        struct stack st = createStack(20);
        struct node* trail = searchAKey(ptr, &st, data, 'I');
        
        if (!trail) {
            
            struct node* parentNewNode = stackTop(st);
            struct node* newNode = createNode(data);
            if (parentNewNode->data > data)
                parentNewNode->lchild = newNode;
            else
                parentNewNode->rchild = newNode;
            
            int totalHeight = st.top+1;
            
            struct node* currentNode = 0;
            struct node* parentNode = 0;
        
            checkForRotation(rootNode, &parentNode, &currentNode, &st, totalHeight, data);
        }
        else
            printf ("already exists!!\n");
    }
    else
        *rootNode = createNode(data);
}


void deleteNode(struct node** rootNode, int key) {
    struct stack st1 = createStack(20);

    struct node* currentNode = searchAKey(*rootNode, &st1, key, 'D');
    if (currentNode) {
        // fetching the successor node
        struct node* succNode = pop(&st1);
        // replace the data of currentnode with the successornode
        currentNode->data = succNode->data;
        if (succNode->rchild)
            stackTop(st1)->lchild = succNode->rchild;
        
        free(succNode);
        succNode = 0;
        printf ("need to complete this asap\n");
        printf ("adeded a aline\n");
    

        // need to fix this bug
        checkForRotation(rootNode, 0, pop(&st1), &st1, st1.top+1, 0);

    }
    
}

void displayInOrder(struct node* rootNode) {
    struct stack st = createStack(20);
    struct node* ptr = rootNode;
    
    printf ("in order traversal: ");
    while (!isEmptyStack(st) || ptr) {
        if (ptr) {
            push(&st, ptr);
            ptr = ptr->lchild;
        }
        else {
            ptr = pop(&st);
            printf ("%d ", ptr->data);
            ptr = ptr->rchild;
        }
    }
    printf ("\n");
}

void displayPreOrder(struct node* rootNode) {
    struct stack st = createStack(20);
    struct node* ptr = rootNode;
    
    printf ("pre order traversal: ");
    while (!isEmptyStack(st) || ptr) {
        if (ptr) {
            printf ("%d ", ptr->data);
            push(&st, ptr);
            ptr = ptr->lchild;
        }
        else {
            ptr = pop(&st);
            ptr = ptr->rchild;
        }
    }
    printf ("\n");
}


int main() {
    
    struct node* rootNode = 0;
    
    insertNode(&rootNode, 33);
    insertNode(&rootNode, 35);
    insertNode(&rootNode, 38);
    insertNode(&rootNode, 29);
    insertNode(&rootNode, 46);
    insertNode(&rootNode, 51);
    
    displayPreOrder(rootNode);
    displayInOrder(rootNode);
    
    deleteNode(&rootNode, 35);
    
    displayPreOrder(rootNode);
    displayInOrder(rootNode);
    
    return 0;
}

