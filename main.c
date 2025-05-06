#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper function to calculate factorial (used for memory allocation size)
int size(int n){
    if(n==1){
        return 1;
    }
    else{
        return n*size(n-1);
    }
}

// Helper function to copy a tree
struct TreeNode* cpy(struct TreeNode* node,struct TreeNode* new){
    new->val=node->val;
    if(node->left!=NULL){
        new->left=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        cpy(node->left,new->left);
    }
    else{
        new->left=NULL;
    }
    if(node->right!=NULL){
        new->right=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        cpy(node->right,new->right);
    }
    else{
        new->right=NULL;
    }
    return new;
}

// Helper function to insert a new root node
struct TreeNode* inserttop(struct TreeNode* node,int num){
    struct TreeNode* new=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    new->val=num;
    new->left=node;
    new->right=NULL;
    return new;
}

// Helper function to insert a node to the right
void insertright(struct TreeNode* node,struct TreeNode* head,struct TreeNode ***ans,int i,int *tmpsize){
    struct TreeNode* new=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    struct TreeNode* copy=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    copy->left=NULL;
    copy->right=NULL; 
    if(node->right!=NULL){
        new->left=node->right;
        new->right=NULL;
        new->val=i;
        node->right=new;
        ans[i][(*tmpsize)++]=cpy(head,copy);
        node->right=new->left;
        insertright(node->right,head,ans,i,tmpsize);
    }
    else{
        node->right=new;
        new->val=i;
        new->right=NULL;
        new->left=NULL;
        ans[i][(*tmpsize)++]=cpy(head,copy);
        node->right=NULL;
    }
    return;
}

// Helper function to generate trees for a given number of nodes
void func(struct TreeNode ***ans,int i,int *tmpsize,int lastsize){
    for(int j=0;j<lastsize;j++){
        ans[i][(*tmpsize)++]=inserttop(ans[i-1][j],i);
        insertright(ans[i-1][j],ans[i-1][j],ans,i,tmpsize);
    }
    return;
}

// Main function to generate all unique BSTs
struct TreeNode** generateTrees(int n, int* returnSize){
    struct TreeNode ***ans=(struct TreeNode***)malloc(sizeof(struct TreeNode**)*(n+1));
    ans[0]=NULL;
    for(int i=1;i<=n;i++){
        ans[i]=(struct TreeNode**)malloc(sizeof(struct TreeNode*)*size(i));
    }
    ans[1][0]=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    ans[1][0]->val=1;
    ans[1][0]->left=NULL;
    ans[1][0]->right=NULL;
    if(n==1){
        *returnSize=1;
        return ans[1];
    }
    int *tmpsize=(int *)malloc(sizeof(int));
    int lastsize=1;
    for(int i=2;i<=n;i++){
        *tmpsize=0;
        func(ans,i,tmpsize,lastsize);
        lastsize=*tmpsize;
    }
    *returnSize=lastsize;
    struct TreeNode **final=(struct TreeNode**)malloc(sizeof(struct TreeNode*)*lastsize);
    for(int i=0;i<lastsize;i++){
        final[i]=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        final[i]=ans[n][i];
    }
    return final;
}
