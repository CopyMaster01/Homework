#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//结构体定义：学生信息（可自行添加）
typedef struct Student{
    char name[50];
    struct Student* next;
}Student;

//栈结构定义
typedef struct Stack{
    Student* data;
    struct Stack* next;
}Stack;

//全局链表头和栈顶指针
Student* studentList = NULL;
Stack* undoStack = NULL;

//添加学生信息到链表
void addStudent(const char* name){
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent -> name, name);
    newStudent -> next = studentList;
    studentList = newStudent;
}

//显示学生信息
void displayStudents(){
    Student* current = studentList;
    while(current != NULL){
        printf("Student Name: %s\n", current -> name);
        current = current -> next;
    }
}

//删除学生信息
void deleteStudent(const char* name){
    Student* current = studentList;
    Student* prev = NULL;
    
    while(current != NULL){
        if(strcmp(current -> name, name) == 0){
            //学生信息匹配，从链表中删除
            if(prev != NULL){
                prev -> next = current -> next;
            }else{
                studentList = current -> next;
            }

            //将删除的信息添加到栈种
            Stack* undoEntry = (Stack*)malloc(sizeof(Stack));
            undoEntry -> data = current;
            undoEntry -> next = undoStack;
            undoStack  = undoEntry;

            free(current);
            printf("Student % was deleted.\n",name);
            return;
        }
        prev = current;
        current = current -> next;
    }
    printf("Student %s not found.\n");
}

//撤销删除操作(仅撤销一步)
void undoDelete(){
    if(undoStack == NULL){
        printf("Undo stack is empty.\n");
        return;
    }else{
        Stack* undoEntry = undoStack;
        undoStack = undoStack -> next;
        Student* deletedStudent = undoEntry -> data;

        //将学生信息重新添加到链表中
        deletedStudent -> next = studentList;
        studentList = deletedStudent;

        printf("Undo: Restored student %s.\n", deletedStudent -> name);

        free(undoEntry);
    }
}

int main() {
    int choice;
    char name[50];

    while (1) {
        printf("\n1. Add Student\n2. Display Students\n3. Delete Student\n4. Undo Delete\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter student name: ");
                scanf("%s", name);
                addStudent(name);
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                printf("Enter student name to delete: ");
                scanf("%s", name);
                deleteStudent(name);
                break;
            case 4:
                undoDelete();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}