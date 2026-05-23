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
    struct node* ptr = searchAKey(*rootNode, &st, key);

    if (ptr)
        printf ("%d already exists\n", key);
    else {
        struct node* parentNode = 0;
        struct node* siblingNode = 0;

        while(!isEmptyStack(st)) {
            struct node* poppedNode = pop(&st);
            int temp = key;
            
            if (poppedNode->data1 && poppedNode->data2) {
                siblingNode = createNode();

                if (!stackTop(st) || stackTop(st)->data2) {
                    parentNode = createNode(); 
                }
                
                if (key < poppedNode->data1) {
                    siblingNode->data1 = temp;

                }
                else if (key > poppedNode->data1 && key < poppedNode->data2) {
                    siblingNode->data1 = poppedNode->data2;
                    temp = key;
                }
                else if (key > poppedNode->data2) {
                    siblingNode->data1 = temp;
                    key = poppedNode->data2;
                    poppedNode->data2 = 0;

                }
            }
            else {
                if (poppedNode->data1)  
                    poppedNode->data2 = key;
                else {
                    poppedNode->data2 = poppedNode->data1;
                    poppedNode->data1 = key;
                }
            }
        }
    }

}

int main() {
    struct node* rootNode = 0;

    insertion(&rootNode, 20);
    
    return 0;
}