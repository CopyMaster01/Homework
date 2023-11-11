#include <stdio.h>
#include <stdlib.h>

//定义队列结构
struct Queue {
    int* array;    //存储元素的数组
    int capicity;  //队列容量
    int front;     //队列前端
    int rear;      //队列后端
    int size;      //队列当前大小
};

//创建队列
struct Queue* createQueue(){
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue -> capicity = 1;
    queue -> array = (int*)malloc(queue -> capicity * sizeof(int));
    queue -> front = 0;
    queue -> rear = -1;
    queue -> size = 0;

    return queue;
}

//判断队列是否为空
int isEmpty(struct Queue* queue){
    return queue -> size == 0;
}

//获取队列当前大小
int getSize(struct Queue* queue){
    return queue -> size;
}

//入队
void enqueue(struct Queue* queue, int item){
    if(queue -> size == queue -> capicity){
        queue -> capicity *= 2;
        queue -> array = (int*)realloc(queue -> array, queue -> capicity * sizeof(int));
    }

    queue -> rear = (queue -> rear + 1)% queue -> capicity;
    queue -> array[queue -> rear] = item;
    queue -> size ++;
}

//出队
int dequeue(struct Queue* queue){
    if(isEmpty(queue)){
        printf("队列为空，无法出队\n");
        return -1;
    }

    int item = queue -> array[queue -> front];
    queue -> front = (queue -> front + 1) % queue -> capicity;
    queue -> size --;

    return item;
}


int main(){
    struct Queue* queue = createQueue();

    for(int i = 1; i <= 3; i++){
        enqueue(queue, i);
    }

    printf("出队元素: %d\n", dequeue(queue));
    printf("出队元素: %d\n", dequeue(queue));

    enqueue(queue, 4);
    enqueue(queue, 5);

    printf("出队元素: %d\n", dequeue(queue));

    enqueue(queue, 6);

    printf("出队元素: %d\n", dequeue(queue));
    printf("出队元素: %d\n", dequeue(queue));

    free(queue->array);
    free(queue);

    return 0;
}