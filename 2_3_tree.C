#include<stdio.h>
#include "helpers.C"

struct node {
    struct node* leftChild;
    struct node* midChild;
    struct node* rightChild;
    int data1;
    int data2;
};

struct node* createNode() {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->leftChild = newNode->midChild = newNode->rightChild = 0;
    newNode->data1 = newNode->data2 = 0;
    return newNode;
}

struct node* searchAKey(struct node* ptr, struct stack* st, int key) {
    
    struct node* trail = 0;
    if (ptr) {
        trail = ptr;
        if (key == ptr->data1 || key == ptr->data2)
            return ptr;
        else if (key < ptr->data1)
            ptr = ptr->leftChild;
        else if (key > ptr->data1 && key < ptr->data2)
            ptr = ptr->midChild;
        else if (key > ptr->data2)   
            ptr = ptr->rightChild; 
        push(st, trail);
    }
    return ptr;
}


void insertion(struct node** rootNode, int key) {

    struct stack st = createStack(20);
    struct node* ptr = searchAKey(*rootNode, &st, key);

    if (ptr)
        printf ("%d already exists\n", key);
    else {
        if (!*rootNode) {
            *rootNode = createNode();
            (*rootNode)->data1 = key;
        }
        else {
            struct node* sib1 = 0;
            struct node* sib2 = 0;
            struct node* siblingNode = 0;
            int flag = 0;

            while(!isEmptyStack(st)) {
                // need to work on the sibling node and the temp node
                struct node* poppedNode = pop(&st);
                if (!poppedNode->data2) {
                    if (key < poppedNode->data1) {
                        poppedNode->data2 = poppedNode->data1;
                        poppedNode->data1 = key;
                    }
                    else 
                        poppedNode->data2 = key;
                    flag = 1;
                    key = 0;
                }
                else {
                    siblingNode = createNode();
                    if (key < poppedNode->data1) {
                        siblingNode->data1 = key;
                        key = poppedNode->data1;
                        poppedNode->data1 = poppedNode->data2;
                        poppedNode->data2 = 0;
                        if (sib1 && sib2) {
                            siblingNode->leftChild = sib1;
                            siblingNode->midChild = sib2;
                            poppedNode->leftChild = poppedNode->midChild;
                            poppedNode->midChild = poppedNode->rightChild;
                            poppedNode->rightChild = 0;
                        }
                    }
                    else if (key > poppedNode->data1 && key < poppedNode->data2) {
                        siblingNode->data1 = poppedNode->data2;
                        poppedNode->data2 = 0;
                        if (sib1 && sib2) {
                            poppedNode->midChild = sib1;
                            siblingNode->leftChild = sib2;
                            siblingNode->midChild = siblingNode->rightChild;
                            siblingNode->rightChild = 0;
                        }
                    }
                    else {
                        siblingNode->data1 = key;
                        key = poppedNode->data2;
                        poppedNode->data2 = 0;
                        if (sib1 && sib2) {
                            siblingNode->leftChild = sib2;
                            siblingNode->midChild = sib1;
                            poppedNode->rightChild = 0;
                        }
                    }
                    sib1 = siblingNode;
                    sib2 = poppedNode;
                }
                if (flag)
                    break;
            }
            if (key) {
                *rootNode = createNode();
                (*rootNode)->data1 = key;
                (*rootNode)->leftChild=sib1;
                (*rootNode)->midChild=sib2;
            }
        }
    }
    printf ("-----END OF INSERTION-----\n");
}

// NEED TO FIX IT
void inOrderTraversal(struct node* rootNode) {
    struct stack st = createStack(20);
    struct node* ptr = rootNode;
    push(&st, ptr);
    // will be stuck in a loop
    // make some correction in the loop
    ptr = ptr->leftChild;
    while (!ptr && !isEmptyStack(st)) {
        if (ptr->leftChild) {
            push(&st, ptr);
            ptr = ptr->leftChild;
        }
        else {
            ptr = pop(&st);
            printf ("%d ", ptr->data1);
            if (ptr->data2)
                printf ("%d ", ptr->data2);

            ptr = pop(&st);
            printf ("%d ", ptr->data1);
            if (ptr->midChild) {
                // printf ("%d ", ptr->data1);
                ptr = ptr->midChild;
                push(&st, ptr);
            }
            else {
                ptr = pop(&st);
                printf("%d ", ptr->data2);
                if (ptr->rightChild) {
                    ptr = ptr->rightChild;
                    push(&st, ptr);
                }
            }
        }
    }
    printf("\n");
}


int main() {
    struct node* rootNode = 0;

    insertion(&rootNode, 20);
    insertion(&rootNode, 30);
    insertion(&rootNode, 40);
    // insertion(&rootNode, 50);
    // insertion(&rootNode, 60);

    printf("in order traversal: ");
    inOrderTraversal(rootNode);
    
    return 0;
}