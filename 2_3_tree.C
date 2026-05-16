#include<stdio.h>
#include<helpers.C>

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
    struct node* searchedNode = searchAKey(*rootNode, &st, key);
    if (!searchedNode) { // the node with that value is not found
        struct node* ptrNode = pop(&st);
        while (!isEmptyStack(st)) {
        
            if (!ptrNode->data2 && key < ptrNode->data1) {
                ptrNode->data2 = ptrNode->data1;
                ptrNode->data1 = key;
            }

            else if (!ptrNode->data2 && key > ptrNode->data1)
                ptrNode->data2 = key;
            
            else if (ptrNode->data1 && ptrNode->data2) {

                struct node* parentNode = createNode();
                struct node* siblingNode = createNode();

                if (key < ptrNode->data1) {
                    parentNode->leftChild = ptrNode;
                    parentNode->midChild = siblingNode;
                    parentNode->data1 = ptrNode->data1;
                    siblingNode->data1 = key;
                    ptrNode->data1 = ptrNode->data2;
                    ptrNode->data2 = 0;
                }

                else if (key > ptrNode->data1 && key < ptrNode->data2) {
                    parentNode->data1 = key;
                    parentNode->leftChild = ptrNode;
                    parentNode->midChild = siblingNode;
                    siblingNode->data1 = ptrNode->data2;
                    ptrNode->data2 = 0;
                }

                else if (key > ptrNode->data2) {
                    parentNode->rightChild = siblingNode;
                    parentNode->midChild = ptrNode;
                    parentNode->data1 = ptrNode->data2;
                    siblingNode->data1 = key;
                    ptrNode->data2 = 0;
                }

                if (stackTop(st)->leftChild == ptrNode)
                    stackTop(st)->leftChild = parentNode;
                else if (stackTop(st)->midChild == ptrNode)
                    stackTop(st)->midChild = parentNode;
                else if (stackTop(st)->rightChild == ptrNode)
                    stackTop(st)->rightChild = parentNode;
                
                ptrNode = pop(&st);

            }
        }
        
    }
    else  { // the node is found
        printf ("Node with key = %d already exists\n", key);
    }
    return;
}

int main() {
    struct node* rootNode = 0;

    insertion(&rootNode, 20);
    
    return 0;
}