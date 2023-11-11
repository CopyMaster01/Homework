#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//定义时间结构体
struct Time
{
    int arrival_h;
    int arrival_m;
    int leave_h;
    int leave_m;
};


// 定义停车场栈的结构
#define MAX_CAPACITY 10
typedef struct {
    int car_num;
    struct Time time;
} Car;//车结构
Car parking_lot[MAX_CAPACITY];
int top = -1;



//定义便道队列的结构
typedef struct QueueNode{
    Car car;
    struct QueueNode* next;
} QueueNode;
QueueNode* front = NULL;
QueueNode* rear = NULL;

//入栈操作
void push(Car car){
    if (top < MAX_CAPACITY - 1) {
        parking_lot[++top] = car;
        printf("%d 停在 %d 号车位\n", car.car_num, top + 1);
    } else {
        //如果车已经停满了，将车辆加入便道
        QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
        newNode -> car = car;
        newNode -> next = NULL;
        if (rear == NULL) {
            front = newNode;
            rear = newNode;
        } else {
            rear -> next = newNode;
            rear = newNode;
        }
        printf("%d 进入等候便道\n", car.car_num);
    }
}

//出栈操作
Car pop(int i) {
    top--;
    return parking_lot[i - 1];// 返回一个空车辆，表示停车场未空
}

//计算停车时间和费用
void calculateFee(Car parked_car, Car leaving_car) {
    int departure_time;
    departure_time = (leaving_car.time.leave_h - parked_car.time.arrival_h) * 60 + (leaving_car.time.leave_m - parked_car.time.arrival_m);
    double fee = departure_time * 0.1;
    printf("%d 一共停了 %d 分钟，停车费用为 %f 元\n", parked_car.car_num, departure_time, fee);
}

//主程序
int main() {
    char action[10];
    Car car, parked_car, leaving_car;

    while(1){
        printf("输入要进行的操作：     (进入：arrival - 离开：leave - 退出系统：exit)\n");
        scanf("%s",&action);
        if (strcmp(action, "exit") == 0) {
            break;
        } else if (strcmp(action, "arrival") == 0) {   
            printf("请输入车牌号、到达时间");
            scanf("%d %d %d", &car.car_num, &car.time.arrival_h, &car.time.arrival_m);
            push(car);
        } else if (strcmp(action, "leave") == 0) {
            printf("请输入车牌号、离开时间");
            scanf("%d %d %d", &leaving_car.car_num, &leaving_car.time.leave_h, &leaving_car.time.leave_m);
            if(top >= 0){
                int i = top + 1;
                for(i; i > 0; i--){
                    if(leaving_car.car_num == parking_lot[i - 1].car_num){ 
                        parked_car = pop(i);
                        calculateFee(parked_car, leaving_car);
                        for(int j = i;j <= top; j++){
                            parking_lot[j] = parking_lot[i + 1];
                        }
                        while(front != NULL){  //将便道上的车停入停车场内
                            push(front -> car);
                            QueueNode* temp = front;
                            front = front -> next;
                            free(temp);
                        }
                        break;
                    }
                }
                //停车场内没有此车
                if(i == -1){
                    printf("该车不在停车场内");
                }
                // QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
                // newNode -> car = parked_car;
                // newNode -> next = NULL;
                // if (rear == NULL) {
                //     front = newNode;
                //     rear = newNode;
                // } else {
                //     rear -> next = newNode;
                //     rear = newNode;
                // }
            }  
            //将便道上的车重新入栈

        } else {
            printf("输入错误，请重新输入\n");
        }
    }
    printf("退出系统\n");
    return 0;
}