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
    if (!searchedNode) {

    }
    else  {
        printf ("Node with key = %d already exists\n", key);
    }
    return;
}

int main() {
    struct node* rootNode = 0;

    insertion(&rootNode, 20);
    
    return 0;
}