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

        if (!ptrNode->data2 && key < ptrNode->data1) {
            ptrNode->data2 = ptrNode->data1;
            ptrNode->data1 = key;
        }

        else if (!ptrNode->data2 && key > ptrNode->data1)
            ptrNode->data2 = key;

        // in 2-3 trees the existing leaf nodes get filled first,
        // if already filled the nodes present above will be then filled, 
        // that is how the height increases from bottom to up  

        else if (ptrNode->data1 && ptrNode->data2) {

            while (!isEmptyStack(st) && (ptrNode->data1 && ptrNode->data2)) {

                if (!stackTop(st)->data2) {
                    stackTop(st)->data2 = stackTop(st)->data1;
                    stackTop(st)->data1 = ptrNode->data1;    
                }

                else {
                    struct node* parentNode = createNode();
                    struct node* siblingNode = createNode();

                    if (key < ptrNode->data1) {

                        parentNode->leftChild = ptrNode; 
                        parentNode->midChild = siblingNode;
                        parentNode->data1 = ptrNode->data1;
                        siblingNode->data1 = key;                       
                
                    }

                    else if (key > ptrNode->data1 && key < ptrNode->data2) {
                        
                        parentNode->leftChild = siblingNode;
                        parentNode->midChild = ptrNode;
                        parentNode->data1 = key;
                        siblingNode->data1 = ptrNode->data1;

                    }
                    
                    else if (key > ptrNode->data2) {

                        parentNode->rightChild = siblingNode;
                        parentNode->midChild = ptrNode;
                        parentNode->data1 = ptrNode->data2;
                        siblingNode->data1 = key;

                    }

                }
                ptrNode->data1 = ptrNode->data2;
                ptrNode->data2 = 0;    

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