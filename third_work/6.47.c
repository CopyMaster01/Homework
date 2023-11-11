#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 定义队列结点结构
struct QueueNode {
    struct TreeNode* data;
    struct QueueNode* next;
};

// 定义队列结构
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// 函数：创建队列
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// 函数：判断队列是否为空
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// 函数：入队
void enqueue(struct Queue* queue, struct TreeNode* data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 函数：出队
struct TreeNode* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    struct TreeNode* frontData = queue->front->data;
    struct QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    return frontData;
}

// 函数：按层次顺序遍历二叉树
void levelOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 创建一个空队列
    struct Queue* queue = createQueue();

    // 根结点入队
    enqueue(queue, root);

    // 循环遍历队列
    while (!isEmpty(queue)) {
        // 出队并访问结点
        struct TreeNode* current = dequeue(queue);
        printf("%d ", current->data);

        // 将左子树入队
        if (current->left != NULL) {
            enqueue(queue, current->left);
        }

        // 将右子树入队
        if (current->right != NULL) {
            enqueue(queue, current->right);
        }
    }
}

// 主函数
int main() {
    // 创建一个示例二叉树
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->data = 1;
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->data = 2;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->data = 3;
    root->right->left = NULL;
    root->right->right = NULL;

    // 调用按层次顺序遍历函数
    printf("Level Order Traversal: ");
    levelOrderTraversal(root);

    return 0;
}
