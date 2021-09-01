#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node* next;
    int value;
};

struct linkedList {
    struct node* root;
    int size;
};

int print_list(struct linkedList* list){
    struct node* node = list->root;
    for (int i = 0; i < list->size; ++i){
        if (node == NULL){
            printf("ERROR: print_list: Node is null\n");
            return 1;
        }
        printf("%d", node->value);
        node = node->next;
        if (i != list->size - 1){
            printf(", ");
        }
    }
    printf("\n");
    return 0;
}

int insert_node(struct linkedList* list, int newval, int pos){
    if (pos < 0 || pos > list->size){
        printf("ERROR: insert_node: Invalid position argument\n");
        return 1;
    }
    list->size++;
    struct node* newnode = malloc(sizeof(struct node));
    newnode->value = newval;
    if (pos == 0){
        if (list->root != NULL){
            newnode->next = list->root;
        }
        list->root = newnode;
        return 0;
    }
    struct node* node = list->root;
    for (int i = 0; i < pos-1; ++i){
        node = node->next;
    }
    newnode->next = node->next;
    node->next = newnode;
    return 0;
}

int delete_node(struct linkedList* list, int pos){
    if (pos < 0 || pos > list->size-1){
        printf("ERROR: insert_node: Invalid position argument\n");
        return 1;
    }
    list->size--;
    struct node* to_free;
    if (pos == 0){
        to_free = list->root;
        if (list->root->next != NULL){
            list->root = list->root->next;
        }
        return 0;
    }
    struct node* node = list->root;
    for (int i = 0; i < pos-1; ++i){
        node = node->next;
    }
    to_free = node->next;
    if (node->next->next != NULL) {
        node->next = node->next->next;
    }
    free(to_free);
    return 0;
}


int main(int argc, char *argv[]){
    struct linkedList list1 = {NULL, 0};
    struct linkedList list2 = {NULL, 0};

    print_list(&list1);
    insert_node(&list1, 1, 0);
    insert_node(&list1, 4, 1);
    insert_node(&list1, -100, 0);
    print_list(&list1);

    delete_node(&list1, 2);
    print_list(&list1);

    insert_node(&list2, 22222, 0);
    delete_node(&list1, 0);
    delete_node(&list1, 0);
    print_list(&list1);
    print_list(&list2);

    return 0;
}
