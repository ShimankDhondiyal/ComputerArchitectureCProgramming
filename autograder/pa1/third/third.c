#include<stdio.h>
#include<stdlib.h>

//define structures
typedef struct Node {
    int data;
    struct Node *next;
} Node;
typedef struct hTable {
  int size;
  struct Node **row;
} hTable;

//method declarationsd
Node *createNode(int data, Node *head);
hTable *createTable(int size);
int search(hTable *table, int num);
int insert(hTable *table, Node *new);

int main(int argc, char **argv) {
    //command line check
    if(argc < 2) {
        printf("error\n");
        return 0;
    }
    //create hash table
    hTable *table = createTable(10000);

    //open and read file
    FILE *f;

    f = fopen(argv[1], "r");
    if(f == NULL ){
      printf("error\n");
      return 0;
    }

    int num;
    char c;
    Node *temp = NULL;
    //track number of chaining events
    int chainCount = 0;
    //track number of searches (succesful and unseccesful)
    int searches = 0;

    while(fscanf(f, "%c\t%d\n", &c, &num) != EOF) {
        if(c == 'i') {
            //create new node and store in hTable
            //reset temp to null
            temp = NULL;
            temp = createNode(num, temp);
            //if chain occurs, note in chain var
            int chain = insert(table, temp);
            if(chain == 1) {
                chainCount++;
            }
        } else if(c == 's') {
            int succseful = search(table, num);
            if(succseful == 0) {
                //search was succesful, track to be printed
                searches++;
            }
        }
    }
    
    //print chaining count
    printf("%d\n", chainCount);
    printf("%d\n", searches);
    fclose(f);
    return 0;
}

hTable *createTable(int size) {
  hTable *table = (hTable*) malloc(sizeof(hTable));
    table->size = size;
    table->row = malloc(size*sizeof(Node*));
    int i;
    for (i = 0; i < size; i++) {
        //set values of entire table to NULL
        table->row[i] = NULL;
    }
    return table;
}

int search(hTable *table,int num) {
    //return 0 succesful
    //return 1 unsuccesful
    int key;
    if(num < 0) {
        key = (num*-1) % table->size;
    } else {
        key = num % table->size;
    }

    if(table->row[key] == NULL) {
        //not found, return 1
        return 1;
    }
    if(table->row[key]->data == num) {
        //found, return 0
        return 0;
    }

    Node *ptr = table->row[key];
    while(ptr->next != NULL) {
        if(ptr->next->data == num) {
            //found, return 0
            return 0;
        }
        ptr = ptr->next;
    }
    //not found, return 1
    return 1;
}

int insert(hTable *table, Node *new) {
    //return 0 if no chaining
    //return 1 if chaining
    int data = new->data;
    int key;
    if(data < 0) {
        key = (data*-1) % table->size;
    } else {
        key = data % table->size;
    }

    Node *ptr;
    //there is not node
    if(table->row[key] == NULL) {
        table->row[key] = new;
        //inserted succesfully
        return 0;
    }
    //chaining needed, traverse linked list
    ptr = table->row[key];
    while(ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = new;
    //added with chaining
    return 1;
}

Node *createNode(int data, Node *head) {
  Node *temp = (Node*) malloc(sizeof(Node));
  temp->data = data;
  temp->next = head;
  head = temp;
  return head;
}
