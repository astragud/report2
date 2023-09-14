#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define SIZE 100

// 트리 노드 구조체 정의
typedef struct TreeNode
{
    int data;
    struct TreeNode* left, * right;
} TreeNode;

// 스택을 위한 노드 구조체 정의
typedef struct StackNode
{
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// 스택 구조체 정의
typedef struct Stack
{
    StackNode* top;
} Stack;

// 스택 초기화 함수
Stack* createStack()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack)
    {
        stack->top = NULL;
    } 
    return stack;
}

// 스택에 노드를 푸시하는 함수
void push(Stack* stack, TreeNode* treeNode)
{
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode)
    {
        newNode->treeNode = treeNode;
        newNode->next = stack->top;
    }
    
    stack->top = newNode;
}

// 스택에서 노드를 팝하는 함수
TreeNode* pop(Stack* stack)
{
    if (stack->top == NULL)
    {
        return NULL; // 스택이 비어있을 경우
    }

    StackNode* topNode = stack->top;
    TreeNode* treeNode = topNode->treeNode;
    stack->top = topNode->next;
    free(topNode);
    return treeNode;
}

// 전위 순회 함수
void preorderTraversal(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    Stack* stack = createStack();
    push(stack, root);

    // 노드를 스택에 푸시할 때 오른쪽 자식부터 처리하도록 변경
    while (stack->top != NULL)
    {
        TreeNode* currentNode = pop(stack);
        printf("%d ", currentNode->data);

        // 왼쪽 자식을 먼저 푸시하여 오른쪽 자식이 먼저 팝되도록 함
        if (currentNode->left != NULL)
        {
            push(stack, currentNode->left);
        }

        if (currentNode->right != NULL)
        {
            push(stack, currentNode->right);
        }
    }

    free(stack);
}

// 중위 순회 함수
void inorderTraversal(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    Stack* stack = createStack();
    TreeNode* currentNode = root;

    while (currentNode != NULL || stack->top != NULL)
    {
        while (currentNode != NULL)
        {
            push(stack, currentNode);
            currentNode = currentNode->right; // 오른쪽 자식부터 처리하도록 변경
        }

        currentNode = pop(stack);
        printf("%d ", currentNode->data);
        currentNode = currentNode->left; // 왼쪽 자식으로 이동
    }

    free(stack);
}

// 후위 순회 함수
void postorderTraversal(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    Stack* stack = createStack();
    TreeNode* currentNode = root;
    TreeNode* lastVisitedNode = NULL;

    while (currentNode != NULL || stack->top != NULL)
    {
        while (currentNode != NULL)
        {
            push(stack, currentNode);
            currentNode = currentNode->right; // 오른쪽 자식부터 처리하도록 변경
        }
        TreeNode* topNode = stack->top->treeNode;

        if (topNode->left == NULL || topNode->left == lastVisitedNode) 
        {
            pop(stack);
            printf("%d ", topNode->data);
            lastVisitedNode = topNode;
        }

        else
        {
            currentNode = topNode->left; // 왼쪽 자식으로 이동
        }
    }

    free(stack);
}

TreeNode n1 = { 11, NULL, NULL };
TreeNode n2 = { 10, NULL, NULL };
TreeNode n3 = { 5, NULL, NULL };
TreeNode n4 = { 4, NULL, NULL };
TreeNode n5 = { 9, &n1, &n2 };
TreeNode n6 = { 8, NULL, NULL };
TreeNode n7 = { 6, NULL, NULL };
TreeNode n8 = { 3, &n3, &n4 };
TreeNode n9 = { 7, &n5, &n6 };
TreeNode n10 = { 2, &n7, &n8 };
TreeNode n11 = { 1, &n9, &n10 };
TreeNode* root = &n11;

int main()
{
    printf("<Traversal with Stack>\n");
    printf("1. 전위 순회\n");
    preorderTraversal(root);
    printf("\n\n");

    printf("2. 중위 순회\n");
    inorderTraversal(root);
    printf("\n\n");

    printf("3. 후위 순회\n");
    postorderTraversal(root);
    printf("\n");

    return 0;
}