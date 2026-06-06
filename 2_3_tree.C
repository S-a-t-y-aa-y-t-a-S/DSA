#include<stdio.h>
#include<limits.h>
#include "helpers.C"

struct node {
    struct node* leftChild;
    struct node* midChild;
    struct node* rightChild;
    int data1;
    int data2;
    int state;
};

struct node* createNode() {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->leftChild = newNode->midChild = newNode->rightChild = 0;
    newNode->data1 = 0;//INT_MAX;
    newNode->data2 = 0;//INT_MIN;
    newNode->state = 0;
    return newNode;
}

int searchAKey(struct node* ptr, struct stack* st, int key) {
    
    struct node* trail = 0;
    if (ptr) {
        trail = ptr;
        if (key < ptr->data1)
            ptr = ptr->leftChild;
        else if (key > ptr->data1 && (key < ptr->data2 || !ptr->data2))
            ptr = ptr->midChild;
        else if (key > ptr->data2)   
            ptr = ptr->rightChild; 
        else
            return key;
        push(st, trail);
    }
    return 0;
}


void insertion(struct node** rootNode, int key, int* count) {

    struct stack st = createStack(20);
    int flag = searchAKey(*rootNode, &st, key);

    if (flag)
        printf ("%d already exists\n", key);
    else {
        // printf ("%d does not exist\n", key);
        (*count) ++;
        if (!*rootNode) {
            *rootNode = createNode();
            (*rootNode)->data1 = key;
        }
        else {
            struct node* sib1 = 0;
            struct node* sib2 = 0;
            struct node* siblingNode = 0;
            flag = 0;

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
                    else if (key > poppedNode->data2) {
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
                if (key > sib2->data1 || key > sib2->data2) {
                    (*rootNode)->leftChild=sib2;
                    (*rootNode)->midChild=sib1;
                }
                else {
                    (*rootNode)->leftChild=sib1;
                    (*rootNode)->midChild=sib2;
                }
                
            }
        }
    }
    // printf ("-----END OF INSERTION-----\n");
}

// NEED TO FIX IT
void inOrderTraversal(struct node* rootNode, int count) {
    struct stack st = createStack(20);
    struct node* ptr = rootNode;
    int ind = 0;
    
    push(&st, ptr);
    (ptr->state) ++;
    ptr = ptr->leftChild;

    while (!isEmptyStack(st)) {

        if (ptr) {
            if (!ptr->state) {
                push(&st, ptr);
                (ptr->state) ++;
                ptr = ptr->leftChild;
            }
            else {
                ptr = pop(&st);
                if (ptr->state == 1) {
                    printf("%d ", ptr->data1);
                    // ind ++;
                    (ptr->state) ++;
                    // if (ptr->data2)
                    push(&st, ptr);
                    ptr = ptr->midChild;
                }
                else if (ptr->state == 2 && ptr->data2) {
                    printf("%d ", ptr->data2);
                    // ind ++;
                    push(&st, ptr);
                    (ptr->state) ++;
                    ptr = ptr->rightChild;
                }
            } 
        }
        else {
            ptr = pop(&st);
            printf("%d ", ptr->data1);
            if (ptr->data2) {
                printf ("%d ", ptr->data2);
                // ind ++;
            } 
        }
    }
    // printf ("%d is to be inserted", key);
    printf("\n");
}


int main() {
    struct node* rootNode = 0;
    int count = 0;

    insertion(&rootNode, 20, &count);
    insertion(&rootNode, 30, &count);
    insertion(&rootNode, 40, &count);

    insertion(&rootNode, 50, &count);
    insertion(&rootNode, 60, &count);
    insertion(&rootNode, 10, &count);
    // insertion(&rootNode, 15, &count);
    // insertion(&rootNode, 70, &count);
    // insertion(&rootNode, 80, &count);
    // insertion(&rootNode, 90, &count);
    

    printf("in order traversal: ");
    inOrderTraversal(rootNode, count);
    
    return 0;
}