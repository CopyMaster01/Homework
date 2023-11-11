#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 定义栈结构
struct StackNode {
    struct TreeNode* data;
    struct StackNode* next;
};

// 函数：创建栈
struct StackNode* createStack() {
    return NULL;
}

// 函数：判断栈是否为空
int isEmpty(struct StackNode* root) {
    return root == NULL;
}

// 函数：入栈
void push(struct StackNode** root, struct TreeNode* data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = *root;
    *root = newNode;
}

// 函数：出栈
struct TreeNode* pop(struct StackNode** root) {
    if (isEmpty(*root)) {
        return NULL;
    }
    struct TreeNode* popped = (*root)->data;
    struct StackNode* temp = *root;
    *root = (*root)->next;
    free(temp);
    return popped;
}

// 函数：先序遍历（非递归）
void iterativePreorder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 创建一个空栈
    struct StackNode* stack = createStack();

    // 将根结点入栈
    push(&stack, root);

    // 循环遍历栈
    while (!isEmpty(stack)) {
        // 出栈并访问结点
        struct TreeNode* current = pop(&stack);
        printf("%d ", current->data);

        // 先将右子树入栈，再将左子树入栈（因为栈是先进后出）
        if (current->right != NULL) {
            push(&stack, current->right);
        }
        if (current->left != NULL) {
            push(&stack, current->left);
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

    // 调用先序遍历（非递归）函数
    printf("Iterative Preorder Traversal: ");
    iterativePreorder(root);

    return 0;
}
