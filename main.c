#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int catalan(int n) {
    if (n <= 1) return 1;
    int res = 0;
    for (int i = 0; i < n; i++)
        res += catalan(i) * catalan(n - i - 1);
    return res;
}

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode** generateTreesHelper(int start, int end, int* returnSize) {
    *returnSize = 0;
    if (start > end) {
        struct TreeNode** result = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
        result[0] = NULL;
        *returnSize = 1;
        return result;
    }

    int max_size = catalan(end - start + 1);
    struct TreeNode** result = (struct TreeNode**)malloc(sizeof(struct TreeNode*) * max_size);

    for (int i = start; i <= end; i++) {
        int leftSize, rightSize;
        struct TreeNode** leftTrees = generateTreesHelper(start, i - 1, &leftSize);
        struct TreeNode** rightTrees = generateTreesHelper(i + 1, end, &rightSize);

        for (int j = 0; j < leftSize; j++) {
            for (int k = 0; k < rightSize; k++) {
                struct TreeNode* root = newNode(i);
                root->left = leftTrees[j];
                root->right = rightTrees[k];
                result[(*returnSize)++] = root;
            }
        }

        free(leftTrees);
        free(rightTrees);
    }

    return result;
}

struct TreeNode** generateTrees(int n, int* returnSize) {
    if (n == 0) {
        *returnSize = 0;
        return NULL;
    }
    return generateTreesHelper(1, n, returnSize);
}

void serializeTree(struct TreeNode* root, char* buffer, int* pos) {
    if (!root) {
        strcpy(buffer + *pos, "null");
        *pos += 4;
        return;
    }

    *pos += sprintf(buffer + *pos, "%d", root->val);

    if (root->left || root->right) {
        buffer[(*pos)++] = ',';
        serializeTree(root->left, buffer, pos);
        buffer[(*pos)++] = ',';
        serializeTree(root->right, buffer, pos);
    }
}

void formatOutput(char* buffer) {
    int len = strlen(buffer);
    while (len >= 4 && strcmp(buffer + len - 4, "null") == 0) {
        len -= 4;
        if (len > 0 && buffer[len-1] == ',') len--;
        buffer[len] = '\0';
    }
}

void printResult(struct TreeNode** trees, int count) {
    printf("[");
    for (int i = 0; i < count; i++) {
        printf("[");
        char buffer[1000] = {0};
        int pos = 0;
        serializeTree(trees[i], buffer, &pos);
        formatOutput(buffer);
        printf("%s", buffer);
        printf("]");
        if (i < count - 1) printf(",");
    }
    printf("]\n");
}

void freeTree(struct TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int returnSize;
    
    printf("Input: n = 3\n");
    struct TreeNode** trees3 = generateTrees(3, &returnSize);
    printf("Output: ");
    printResult(trees3, returnSize);
    
    for (int i = 0; i < returnSize; i++) {
        freeTree(trees3[i]);
    }
    free(trees3);

    printf("Input: n = 1\n");
    struct TreeNode** trees1 = generateTrees(1, &returnSize);
    printf("Output: ");
    printResult(trees1, returnSize);
    
    for (int i = 0; i < returnSize; i++) {
        freeTree(trees1[i]);
    }
    free(trees1);

    return 0;
}
