#include <stdio.h>
#include <stdlib.h>

//定义单链表结构
struct Node {
    int data;
    struct Node* next;
};

//创建新节点函数
struct Node* createNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode -> data = data;
    newNode -> next = NULL;

    return newNode;
}

//逆置单链表
struct Node* reverse(struct Node* head){
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* nextNode;

    while(current != NULL){
        nextNode = current -> next;
        current -> next = prev;
        prev = current;
        current = nextNode;
    }

    return prev;
}

//删除单链表中值为key的所有节点
struct Node* delete_key(struct Node* head, int key){
    struct Node* dummy = createNode(0);
    dummy -> next = head;
    struct Node* current = dummy;

    while(current -> next != NULL){
        if(current -> next -> data == key){
            struct Node* temp = current -> next;
            current -> next = temp -> next;
            free(temp);
        }else{
            current = current -> next;
        }
    }

    return dummy -> next;
}

//删除单链表中所有重复点
struct Node* delete_repeat(struct Node* head){
    struct Node* current = head;

    while(current != NULL){
        struct Node* runner = current;
        while(runner -> next != NULL){
            if(runner -> next -> data == current -> data){
                struct Node* temp = runner -> next;
                runner -> next = temp -> next;
                free(temp);
            }else{
                runner = runner -> next;
            }
        }
        current = current -> next;
    }

    return head;
}

//打印单链表
void printLinkedlist(struct Node* head){
    struct Node* current = head;

    while(current != NULL){
        printf("%d -> ",current -> data);
        current = current -> next;
    }

    printf("NULL\n");
}

//主函数
int main(){
    struct Node* head = createNode(1);
    struct Node* current = head;
    for(int i = 1; i <= 5; i++){
        current -> next = createNode(i);
        current = current -> next;
    }

    printf("Original Linked List: ");
    printLinkedlist(head);

    head = reverse(head);
    printf("Reversed Linked List: ");
    printLinkedlist(head);

    head = delete_key(head, 2);
    printf("After deleting nodes with key 2: ");
    printLinkedlist(head);

    head = delete_repeat(head);
    printf("After deleting duplicates: ");
    printLinkedlist(head);

    return 0;
}