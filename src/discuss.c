#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "binaryTree.h"

int main (int argc, char **argv) {
	FILE *fptr;
	char buffer[110];
	char keyword[50];
	char response[110];
	char filename[50];
	double uRating;
	double sRating;
	int occurences;
	Rule *r;

	Tree* tree = createBinTree(&compare, &deleteNode);

	if(argc!=2) {
		printf("Error: wrong number of arguments\n");
		return 0;
	}	
	strcpy(filename, argv[1]);
	fptr = fopen(filename, "r");
	if (fptr==NULL ) {
		printf("Error: file does not exist\n");
		return 0;
	}

	while (fgets(buffer, 100, fptr) != NULL) {
		strcpy(keyword,buffer);
		keyword[strcspn(keyword,"\r\n")] = '\0';
		fgets(buffer, 100, fptr);
		strcpy(response,buffer);
		response[strcspn(response,"\r\n")] = '\0';
		r = createRule(0.5, 0.5, 0, response, keyword);
		addToTree(tree, r);
	}

	fclose(fptr);

	char input;

	while (input != '9') {
		printf("1) Add a new rule\n");
		printf("2) Remove a rule\n");
		printf("3) Display rules\n");
		printf("4) Modify rule rating\n");
		printf("5) Discuss\n");
		printf("9) Quit\n");
		printf("choice: ");
		scanf(" %c", &input);
		char response[110];
		Rule *r2;
		TreeNode *node;
		char *token;
		char saveKeywords[5][40];
		int i = 0;
		double maxImportance = 0;
		double importance = 0;
		char save[50];
		int flag = 0;
		int occ;
		char feedBack[10];
		bool invalid = true;
		double sysRate;
		
		switch (input) {
			case '1':
				printf("Please enter a keyword: ");
				scanf("%s",keyword);
				getchar();
				while (searchKeyWord(tree->root,keyword)==1) {
					printf("Error: keyword already exists!\n");
					printf("Please enter a new keyword: ");
					scanf("%s",keyword);
					getchar();
				} 
				printf("Please enter a response: ");
				fgets(response, 80, stdin);
				printf("Please enter a rating: ");
				scanf("%lf",&uRating);
				getchar();

				while(uRating<0 || uRating>1) {
					printf("Error: Rating must be between 0 - 1\n");
					printf("Please enter a rating: ");
					scanf("%lf",&uRating);
					getchar();
				}
				r2 = createRule(uRating, uRating, 0, response, keyword);
				addToTree(tree, r2);
				break;
			case '2':
				printf("Please enter a keyword: ");
				scanf("%s",keyword);
				getchar();
				//if (searchKeyWord(tree->root,keyword)!=1) {
				if (find(tree->root,keyword)!=NULL) {
					printf("The rule you wish to delete does not exist!\n");
				}
				else {
					removeFromTree(tree, keyword);
					if (searchKeyWord(tree->root,keyword)==1) {
						printf("Deletion unsuccesful!\n");
					}
					else {
						printf("Deletion succesful!\n");
					}
				}
				break;
			case '3':
				printInOrder(tree,&printNode);
				break;
			case '4':
				printf("Please enter a keyword: ");
				scanf("%s",keyword);
				getchar();
				if (find(tree->root,keyword)!=NULL) {
					printf("Current rating: %lf\n",((Rule*)(find(tree->root,keyword)))->userRating);
					printf("Please enter a rating: ");
					scanf("%lf",&uRating);
					getchar();
					while(uRating<0 || uRating>1) {
						printf("Error: Rating must be between 0 - 1\n");
						printf("Please enter a rating: ");
						scanf("%lf",&uRating);
						getchar();
					}
					((Rule*)(find(tree->root,keyword)))->userRating = uRating;
					printf("Updated rating: %lf\n",((Rule*)(find(tree->root,keyword)))->userRating);
				}
				else {
					printf("Sorry could not find the keyword\n");
				}
				break;
			case '5':
				getchar();
				printf("Please enter your question: ");
				fgets(response, 80, stdin);
				response[strcspn(response,"\r\n")] = '\0';
				token = strtok(response, " ");
				while(token!=NULL) {
					node = find(tree->root,token);
					if (node!=NULL) {
						importance = ((Rule*)(node))->userRating + ((Rule*)(node))->systemRating;
						if (importance>maxImportance) {
							maxImportance = importance;
							strcpy(save, ((Rule*)(node))->keyword);
							flag++;
						}
					}
					token = strtok(NULL, " ");
				}
				if (flag>0) {
					node = find(tree->root,save);
					occ = ((Rule*)(node))->occurences;
					occ++;
					((Rule*)(node))->occurences = occ;
					printf("\nResponse: %s\n\n", ((Rule*)(node))->response);
					printf("Was this feedback helpful? (y or n)\n");
					scanf("%s",feedBack);
					getchar();
					if (strcmp(feedBack,"y")==0) {
						sysRate = ((Rule*)(node))->systemRating;
						printf("Old system rating: %lf\n",sysRate);
						//printf("%lf + (%lf * 0.05) / %lf\n",sysRate,sysRate,(double)occ);
						sysRate = sysRate + ((sysRate*0.05)/(double)occ);
						//printf("= %lf\n", sysRate);
						((Rule*)(node))->systemRating = sysRate;
						printf("Updated system rating: %lf\n",((Rule*)(node))->systemRating);
					}
					else if (strcmp(feedBack,"n")==0) {
						sysRate = ((Rule*)(node))->systemRating;
						printf("Old system rating: %lf\n",sysRate);
						//printf("%lf + (%lf * 0.05) / %lf\n",sysRate,sysRate,(double)occ);
						sysRate = sysRate - ((sysRate*0.05)/(double)occ);
						//printf("= %lf\n", sysRate);
						((Rule*)(node))->systemRating = sysRate;
						printf("Updated system rating: %lf\n",((Rule*)(node))->systemRating);
					}
					else {
						printf("Please make sure you enter y for yes and n for no.\n");
					}
				}
				else {
					printf("\nResponse: Sorry I did not understand the question\n\n");
				}

				break;
			case '9':
				return 0;
				
			default:
				printf("Error: Invalid input\n");

		}
	}
	

	return 0;
	
}

