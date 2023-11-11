#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 递归函数：交换二叉树中每个节点的左右子树
void mirror(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // 递归交换左右子树
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    // 递归处理左子树
    mirror(root->left);

    // 递归处理右子树
    mirror(root->right);
}

// 辅助函数：创建一个新的二叉树结点
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 辅助函数：先序遍历打印二叉树
void preorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 主函数
int main() {
    // 创建一个示例二叉树
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    // 打印原始二叉树
    printf("Original Binary Tree: ");
    preorderTraversal(root);
    printf("\n");

    // 调用 mirror 函数交换左右子树
    mirror(root);

    // 打印交换后的二叉树
    printf("Binary Tree after Mirroring: ");
    preorderTraversal(root);
    printf("\n");

    return 0;
}
