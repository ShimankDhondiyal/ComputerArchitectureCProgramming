#include <stdio.h>
#include <stdlib.h>


//define Node
typedef struct Node {
    int value;
    struct Node *next;
} Node;

//method declarations
void insert(Node **front, Node *temp);
void delete(int valueArg, Node **front);
void freeList(Node *front);

int main(int argc, char** argv) {
    //command line does not pass fileName :: should we print error?
    if(argc < 2) {
        printf("error");
        //return 0;
    }

    FILE *f;
    f = fopen(argv[1], "r");
    
    //if file DNE, print "error" and nothing else
    if(f == NULL) {
        printf("error");
        //no need to free front bc not yet declared
        //return 0;
    }
    
    //FILE FOUND
    
    //check if file is blank
    fseek(f, 0, SEEK_END);
    long fileSize = ftell(f);   //int fileSize
    if(fileSize == 0) {
        printf("%d\n\n", 0);  //print 0 and blank line, IF FORMATTING ERROR, REPLACE WITH SINGLE \n
        return 0;
    }
    //reset fseek pointer to beginning of file so that fscanf will work properly
    fseek(f, 0, 0);

    char c;
    int value;
    int count = 0;
    Node *front = NULL;
    int ret = fscanf(f, "%c\t%d\n", &c, &value);

    while(ret != EOF) {
        if(ret == 2) {
            //insert
            if(c == 'i') {
                //make new node, insert into list
                Node *temp = (Node*) malloc(sizeof(Node));
                temp->value = value;
                temp->next = NULL;
                insert(&front, temp);
            } else if(c == 'd') {   //delete
                delete(value,&front);
            }
        } else {
            printf("error\n");
            freeList(front);
            return 0;
        }
        //replace value of a after each iteration
        ret = fscanf(f, "%c\t%d\n", &c, &value);
    }

    //print first line (number of nodes)
    Node *current = front;
    while(current != NULL){
        count++;
        current = current->next;
    }
    if(count != 0) {
        printf("%d\n", count);

        current = front;
        while(current->next != NULL) {
            printf("%d\t", current->value);
            current = current->next;
        }
        printf("%d", current->value);
        printf("\n");
    }
    else {
        //if there are no nodes, print 0 followed by blank line
        printf("%d\n\n", 0);
    }
    
    //free all nodes in linked list
    freeList(front);
    fclose(f);
    return 0;
}

//use double pointer to modify pointer to front
void insert(Node** front, Node* temp){
    Node *current;
    current = *front;
    if(*front == NULL){
        temp->next = *front;
        *front = temp;
    }
    else if((*front)->value > temp->value){
        temp->next = *front;
        *front = temp;
    }
    else{
        while(current->next!=NULL && current->next->value< temp->value){
            current = current->next;
        }
        temp->next = current->next;
        current->next = temp;
    }
}

void delete (int valueArg, Node **front) {
    
    // If linked list is empty
     if (*front == NULL) {
        return;
    }
     // Store head node
     Node* current = *front;
    
      // If head needs to be removed
      if ((*front)->value == valueArg) {
          *front = current->next;   // Change head
          free(current);               // free old head
          return;
      }
    
      // Find previous node of the node to be deleted
    while(current->next != NULL && current->next->value != valueArg) {
        current = current->next;
    }
    // If position is more than number of ndoes
    if (current == NULL || current->next == NULL) {
        return;
    }
    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    Node *next = current->next->next;

    // Unlink the node from linked list
    free(current->next);  // Free memory

    current->next = next;  // Unlink the deleted node from list
    return;
}


void freeList(Node *front) {
    //iterate through linked list and free every node
    Node *current;
    while(front != NULL) {
        current = front;
        front = front->next;
        free(current);
    }
    return;
}
