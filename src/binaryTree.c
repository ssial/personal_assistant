#include "binaryTree.h"
#include <stdlib.h>

TreeNode* createTreeNode(TreeDataPtr data) {
	TreeNode *node = malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree * createBinTree(CompareFunc compare, DeleteFunc del) {
	Tree *tree = malloc(sizeof(Tree));
	tree->root = NULL;
	tree->compareFunc = compare;
	tree->deleteFunc = del;
	return tree;
}

Rule* createRule(double userRating, double systemRating, int occurences, char *response, char *key) {
	Rule* r = malloc(sizeof(Rule));
	strcpy(r->keyword,key);
	strcpy(r->response,response);
	r->occurences = occurences;
    r->userRating = userRating;
	r->systemRating = systemRating;
	r->occurences = occurences;
	return r;
}

TreeDataPtr getRootData(Tree * theTree) {
	if (theTree->root == NULL) {
		return NULL;
	}
	return theTree->root->data;
}

void addToTree(Tree * theTree, TreeDataPtr data) {
	theTree->root = insert(theTree->root,data,theTree);
}

TreeNode *insert (TreeNode* root, TreeDataPtr data, Tree *theTree) {
	if (root==NULL) {
		return createTreeNode(data);
	}
	//if data less than root
	//else if (theTree->compareFunc(root->data,data)==1) {
	else if(theTree->compareFunc(data,root->data)<0) {//if data is less than root data
		//printf("hee\n");
		root->left = insert(root->left,data,theTree);
	}
	//else if (theTree->compareFunc(root->data,data)==-1) {
	else {//if data is greater than root data
		//printf("hee2\n");
		root->right = insert(root->right,data,theTree);
	}
	return root;
}

int isTreeEmpty(Tree* theTree) {
	if (theTree->root==NULL) {
		return 1;
	}
	return 0;
}

TreeDataPtr findInTree( Tree* theTree, TreeDataPtr data ) {
	
	find(theTree->root,data);

}

TreeNode *find (TreeNode *root, TreeDataPtr data) {
	if (root==NULL) {
		return NULL;
	}
	else if(compareKey(data,root->data)==0) {
		return root->data;
	}
	else if(compareKey(data,root->data)<0) {
		return find(root->left,data);
	}
	else {
		return find(root->right,data);
	}

}

int Search (TreeNode *root, TreeDataPtr data, Tree *theTree) {
	if (root==NULL) {
		return NULL;
	}
	
	else if(theTree->compareFunc(data,root->data)==0) {
		return 1;
	}

	else if(theTree->compareFunc(data,root->data)<0) {
		return Search(root->left,data, theTree);
	}
	else {
		return Search(root->right,data, theTree);
	}
}

int searchKeyWord (TreeNode *root, TreeDataPtr data) {
	if (root==NULL) {
		return NULL;
	}

	else if(compareKey(data,root->data)==0) {
		return 1;
	}

	else if(compareKey(data,root->data)<0) {
		return searchKeyWord(root->left,data);
	}
	else {
		return searchKeyWord(root->right,data);
	}

}


void printPreOrder(Tree * theTree, PrintFunc printData) {
	printf("Keyword\tRating\t\tSystem\t\tOccurences\n");
	preOrder(theTree->root,printData);

}

void preOrder (TreeNode *root, PrintFunc printData) {
	if (root==NULL) {
		return;
	}
	printData(root);
	preOrder(root->left,printData);
	preOrder(root->right,printData);
}

void printInOrder(Tree * theTree, PrintFunc printData) {
	printf("Keyword\tRating\t\tSystem\t\tOccurences\n");
	inOrder(theTree->root,printData);
}


void inOrder (TreeNode *root, PrintFunc printData) {
	if (root==NULL) {
		return;
	}
	inOrder(root->left,printData);
	printData(root);
	inOrder(root->right,printData);
}


void printPostOrder (Tree * theTree, PrintFunc printData) {
	printf("Keyword\tRating\t\tSystem\t\tOccurences\n");
	postOrder(theTree->root,printData);

}

void postOrder (TreeNode *root, PrintFunc printData) {
	if (root==NULL) {
		return;
	}
	postOrder(root->left,printData);
	postOrder(root->right,printData);
	printData(root);
}

void removeFromTree(Tree * theTree, TreeDataPtr data) {
	Delete(theTree->root,data,theTree);
}

TreeNode *Delete(TreeNode *root, TreeDataPtr data, Tree * theTree) {
	if (root==NULL) {
		return NULL;
	}
	else if (compareKey(data,root->data)<0) {//if data less than root data
		root->left = Delete(root->left,data,theTree);
	}
	else if (compareKey(data,root->data)>0) {//if data greater than root data
		root->right = Delete(root->right,data,theTree);
	}
	else {//NODE TO BE DELETED FOUND
		//case 1: no child
		if (isLeaf(root)==1) {
			free(root);
			root = NULL;
		}
		//case 2: only has right child
		else if (root->left==NULL) {
			TreeNode *temp = root;
			root = root->right;
			free(temp);
		}
		//case 3: only has left child
		else if (root->right==NULL) {
			TreeNode *temp = root;
			root = root->left;
			free(temp);
		}
		//case 4: two children
		else {
			TreeNode *temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right,temp->data,theTree);
		}
	}
	return root;
}

TreeNode* FindMin(TreeNode* root)
{
	while(root->left != NULL) root = root->left;
	return root;
}

int isLeaf( TreeNode * treeNode) {
	if (treeNode->left==NULL && treeNode->right==NULL) {
		return 1;
	}
	return 0;
}

int hasTwoChildren( TreeNode *treeNode) {
	if (treeNode->left!=NULL && treeNode->right!=NULL) {
		return 1;
	}
	return 0;
}

int compare (TreeDataPtr first, TreeDataPtr second) {
	char a[50];// = *(char *)(first);
	char b[50];// = *(char *)(second);

	strcpy(a,(char *)(((Rule*)(first))->keyword));
	strcpy(b,(char *)(((Rule*)(second))->keyword));

	return strcmp(a,b);
}

int compareKey (TreeDataPtr first, TreeDataPtr second) {
	char a[50];// = *(char *)(first);
	char b[50];// = *(char *)(second);

	strcpy(a,first);
	strcpy(b,(char *)(((Rule*)(second))->keyword));

	return strcmp(a,b);
}

void printNode (TreeNode *root) {
	printf("%s\t%lf\t%lf\t%d\n",(char *)(((Rule*)(root->data))->keyword),((Rule*)(root->data))->userRating,((Rule*)(root->data))->systemRating,((Rule*)(root->data))->occurences);
}

void deleteNode (TreeDataPtr ptr){
	printf("hi\n");
}

int getHeight( TreeNode* treeNode ) {
	int rHeight = 0;
	int lHeight = 0;
	if (treeNode==NULL) {
		return -1;
	}
	rHeight = getHeight (treeNode->right);
	lHeight = getHeight (treeNode->left);

	if (rHeight > lHeight) {
		return rHeight++;
	}
	else {
		return lHeight++;
	}
}

