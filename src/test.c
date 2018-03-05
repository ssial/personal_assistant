#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

int main() {
	Tree* tree = createBinTree(&compare, &deleteNode);
	char a[50] = "happy";
	char aResponse[50] = "why are you happy";
    char b[50] = "weather";
    char bResponse[50] = "it is sunny";
    char c[50] = "sad";
    char cResponse[50] = "why are you sad";
    char d[50] = "cool";
    char dResponse[50] = "too cool for school";
    char e[50] = "sauce";
    char eResponse[50] = "too much sauce";
    char f[50] = "bug";
    char fResponse[50] = "eww";
    Rule *r;
    printf("\n\n");
    printf("Test 1: Check if tree empty\n");
    if (isTreeEmpty(tree)==1) {
    	printf("Test 1 passed!\n");
    }
    printf("\n\n");
    printf("Test 2: Add data to binary tree\n");
    printf("Expected result: Binary tree root not pointing to NULL\n");
    r = createRule(0.5, 0.5, 0, aResponse, a);
	addToTree(tree, r);
	r = createRule(0.5, 0.5, 0, bResponse, b);
	addToTree(tree, r);
	r = createRule(0.5, 0.5, 0, cResponse, c);
	addToTree(tree, r);
	r = createRule(0.5, 0.5, 0, dResponse, d);
	addToTree(tree, r);
	r = createRule(0.5, 0.5, 0, eResponse, e);
	addToTree(tree, r);
	r = createRule(0.5, 0.5, 0, fResponse, f);
	addToTree(tree, r);
	if (tree->root!=NULL) {
		printf("Test 2 passed!\n");
	}
	else {
		printf("Test 2 failed!\n");
	}
	printf("\n\n");
	printf("Test 3: Print binary tree pre order\n");
	printPreOrder(tree,&printNode);
	printf("\n\n");
	printf("Test 4: Print binary tree in order\n");
	printInOrder(tree,&printNode);
	printf("\n\n");
	printf("Test 5: Print binary tree post order\n");
	printPostOrder(tree,&printNode);
	char word[50];
	char dword[30];
	printf("\n\n");
	printf("Test 6: Search for sauce and print response\n");
	printf("Expected result: too much sauce\n");
	strcpy(word,"sauce");
	if (findInTree(tree,word)!=NULL) {
		printf("Response: %s\n", ((Rule*)(find(tree->root,word)))->response);
	}
	else {
		printf("Could not find word\n");
	}
	printf("\n\n");
	printf("Test 7: Delete bug from tree\n");
	strcpy(dword,"bug");
	removeFromTree(tree,dword);
	printf("\n");
	printInOrder(tree,&printNode);
	printf("\n\n");
	printf("Test 8: Get Root Data\n");
	printf("Expected result: happy\n");
	if(getRootData(tree)!=NULL) {
		printf("keyword: %s\n", ((Rule*)(getRootData(tree)))->keyword);
	}
	printf("\n\n");
	printf("Test 9: Test if root node is a leaf\n");
	printf("Expected result: Root node is not a leaf\n");
	if(isLeaf(tree->root)==0) {
		printf("Root node is not a leaf\n");
	}
	else {
		printf("Root node is leaf\n");
	}
	printf("\n\n");
	printf("Test 10: Test if root node is has two children\n");
	printf("Expected result: Root node has two children\n");
	if(hasTwoChildren(tree->root)==0) {
		printf("Root node does not have two children\n");
	}
	else {
		printf("Root node has two children\n");
	}
	
}

