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
        int flag = 0;

        while(!isEmptyStack(st)) {
            
            struct node* currentNode = pop(&st);
            if (!isEmptyStack(st) && stackTop(st)->data2) {
                // meaning if no parent node exists or the parent node is full
                // create a new parent node
                parentNode = createNode();
                push(&st, parentNode);
            }
            if (currentNode->data1 && currentNode->data2) {
                // meaning  the no space to insert the key in the current node
                // popped out from the stack, representing the traversal
                if (!siblingNode)
                    siblingNode = createNode();
                
                if (parentNode) {
                    // the newly created parent node is assigned its child and the value
                    // the value can be the key or the already existing value shifted up depending 
                    // upon the condition applied
                    if (stackTop(st)->leftChild == currentNode) {
                        stackTop(st)->leftChild = 0;
                    }   
                    else if (stackTop(st)->midChild == currentNode) {
                        stackTop(st)->midChild = 0;
                    } 
                    else if (stackTop(st)->rightChild == currentNode) {
                        stackTop(st)->rightChild = 0;
                    }
                    if (key < currentNode->data1) {
                        parentNode->data1 = currentNode->data1;
                        parentNode->leftChild = siblingNode;
                        parentNode->midChild = currentNode;
                        siblingNode->data1 = key;
                        currentNode->data1 = currentNode->data2;
                        currentNode->data2 = 0;
                    }
                    else if (key > currentNode->data1 && key < currentNode->data2) {
                        parentNode->data1 = key;
                        parentNode->leftChild = currentNode;
                        parentNode->midChild = siblingNode;
                        siblingNode->data1 = currentNode->data2;
                        currentNode->data2 = 0;
                    }
                    else if (key > currentNode->data2) {
                        parentNode->data1 = currentNode->data2;
                        parentNode->leftChild = currentNode;
                        parentNode->midChild = siblingNode;
                        siblingNode->data1 = key;
                        currentNode->data2 = 0;
                    }
                    key = parentNode->data1;
                }
                else {
                    // need to fix the issue/bug
                    // need to apply the sibling node over here
                    int temp = 0;
                    // ##make some changes in how does the stack top shall now be connected to the current node
                    if (key < currentNode->data1) {
                        currentNode->data1 = key;
                        temp = currentNode->data1;
                        siblingNode->data1 = currentNode->data2;
                        
                    }
                    else if (key > currentNode->data1 && key < currentNode->data2) {
                        temp = key;
                        siblingNode->data1 = currentNode->data2;
                    }
                    else if (key > currentNode->data2) {
                        siblingNode->data1 = key;
                        temp = currentNode->data2;
                    }
                    currentNode->data2 = 0;
                    stackTop(st)->data2 = temp;
                    
                    flag = 1;
                }
                // need to transfer the child node of the newly created node to the immediate parent node
                // newly created node then becomes the root node or the parent of the immediate parent or the thing will keep 
                // on repeating
            }
            else {
                if (key < currentNode->data1) {
                    currentNode->data2 = currentNode->data1;
                    currentNode->data1 = key;
                }
                else
                    currentNode->data2 = key;
                flag = 1;
            }
            if (flag)
                break;
        }
    }

}

int main() {
    struct node* rootNode = 0;

    insertion(&rootNode, 20);
    
    return 0;
}