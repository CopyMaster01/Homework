/*                  简陋的个人学生成绩管理系统                           */

//头文件导入

#include <stdio.h>
#include <stdlib.h>


//单个节点的信息组成（内容）:课程名称、课程编号、课程成绩
typedef struct{
    char name[10];
    char nummber[20];
    double score;
}class;

//定义节点结构
typedef struct{
    class data;
    struct Node* next;
}Node, *linklist;


//相关函数声明
linklist creatlinklist();
int get_data(linklist l, int i, class sd);
int input(class* sd);
void out_data(class* sd);
int listinsert(linklist l, int i, class sd);
int listdelete(linklist l, int i);
void menu();
void operation(linklist l);
//主函数
int main(){

    linklist l = creatlinklist();
    menu();
    operation(l);

    return 0;
}


//创建链表
linklist creatlinklist(){
    linklist l = (linklist)malloc(sizeof(Node));
    if (l != NULL)
        l -> next = NULL;
    return l;
}
//输入节点信息
int get_data(linklist l, int i, class sd){
    linklist p;
    p = l -> next;
    int j = 1;
    while(p && j != 1){
        p = p -> next;
        j++;
    }
    if(p != NULL || j > 1){
        return 0;
    }
    sd = p -> data;
    return 1;
}
//输入节点信息
int input(class* sd){
    printf("课程名称：");
    scanf("%s",&sd->name);
    printf("课程编号:");
    scanf("%s",&sd->nummber);
	printf("课程成绩:");
    scanf("%lf",&sd->score);
	printf("输入完成!");
}
//输出节点信息
void out_data(class* sd){
    printf("课程名称：%s \n",sd -> name);
    printf("课程编号：%s \n",sd -> nummber);
    printf("课程名称：%f \n",sd -> score);
}
//在第i个位置插入节点
int listinsert(linklist l, int i, class sd){
    int j = 0;
    linklist p = l;
    while(p != NULL && j < i - 1){
        p = p -> next;
        j ++;
    }
    if (p == NULL && j > j - 1){
        return 0;
    }
    linklist s = (linklist)malloc(sizeof(Node));
    s -> data = sd;
    s -> next = p -> next;
    p -> next = s;
    return 1;
}
//删除第i个节点
int listdelete(linklist l, int i){
    linklist p = l;
    int j = 0;
    while(p -> next != NULL && j < i - 1){
        p = p -> next;
        j ++;
    }
    if (!p -> next ||  j > j - 1){
        return 0;
    }
    linklist q = p -> next;
    p -> next = q -> next;
    free(q);
    return 1;
}

//系统界面
void menu(){
    printf("\n--------------------------------\n\n");
	printf("1. 录入课程信息");
	printf("2. 显示课程信息");
	printf("3. 在指定位置插入课程信息");
	printf("4. 在指定位置删除课程信息");
	printf("\n--------------------------------\n\n");
}
//系统菜单
void operation(linklist l){
    int choose,x,cd;
    class sd;
    while(1){
        printf("请输入功能选项1~4(输入0将退出系统)");
        scanf("%d",&choose);
        switch(choose){
            case 0:
                //退出系统，释放链表内存
                while(l -> next != NULL){
                    listdelete(l, 1);
                }
                free(l);
                return;
            case 1:
                printf("请输入所需要记录的课程数(小于20)");
                scanf("%d",x);
                for(int i = 1; i <= x; i ++){
                    input(&sd);
                    listinsert(l,i,sd);
                }
                break;
            case 2:
                for(int i = 1; i <= x; i ++){
                    get_data(l,i,sd);
                    out_data(&sd);
                }
                break;
            case 3:
                printf("请输入要插入的位置：");
                scanf("%d",&cd);
                printf("请输入你想要插入的课程信息：");
                input(&sd); 
                if(listinsert(l,cd,sd)){
                    printf("插入成功\n\n");
                    x++;
                }else{
                    printf("插入失败\n\n");
                }
                break;
            case 4:
                printf("请输入要删除的位置：");
                scanf("%d",&cd);
                printf("请输入你想要删除的课程信息：");
                input(&sd); 
                if(listdelete(l,cd)){
                    printf("删除成功\n\n");
                    x--;
                }else{
                    printf("删除失败\n\n");
                }
                break;	                
        }
    }
}