#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>

struct node
{
	int value;
	node* left;
	node* right;
};

node* createNode(int value)
{
	node* returnNode = (node*) calloc(sizeof(node), 1);
	returnNode->value = value;
	return returnNode;
}

void sleep()
{
	Sleep(2000);
}

void insertElement(node* newNode, node** root)
{
	if (*root == NULL)
	{
		// printf("Inserting.\n");
		*root = newNode; // "root" is local copy.
	}
	else
	{
		if ((*root)->value == newNode->value)
		{
			printf("\nKey [%d] already exists.\n", (*root)->value);
			sleep();
		}

		else if ((*root)->value > newNode->value)
		{
			// printf("Key smaller than [%d], visiting left subtree.\n", (*root)->value);
			insertElement(newNode, &((*root)->left));
		}

		else
		{
			// printf("Key greater than [%d], visiting right subtree.\n", (*root)->value);
			insertElement(newNode, &((*root)->right));
		}
	}

	return;
}

void writeInorder(node* root)
{
	if (root == NULL)
		return;

	writeInorder(root->left);
	printf("%d ", root->value);
	writeInorder(root->right);

	return;
}

void writePreorder(node* root)
{
	if (root == NULL)
		return;

	printf("%d ", root->value);
	writePreorder(root->left);
	writePreorder(root->right);

	return;
}

int maxDepth(node* node)
{
	if (node == NULL)
		return 0;

	else
	{
		int leftDepth = maxDepth(node->left);
		int rightDepth = maxDepth(node->right);

		if (leftDepth > rightDepth)
			return (leftDepth + 1);
		else
			return (rightDepth + 1);
	}
}

int isBalanced(node* root)
{
	if (root == NULL)
		return 1;

	if (fabs(maxDepth(root->left) - maxDepth(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right))
		return 1;

	return 0;
}

void deleteNode(int value, node* root)
{
	node* p = root;
	node* q = NULL;
	node* rp = NULL;
	node* f = NULL;
	node* s = NULL;

	while (p != NULL && p->value != value)
	{
		q = p;
		if (value < p->value)
			p = p->left;
		else
			p = p->right;
	}

	if (p == NULL)
		printf("\nKey doesn't exist.\n");

	if (p->left == NULL)
		rp = p->right;

	else
	{
		if (p->right == NULL)
			rp = p->left;

		else
		{
			f = p;
			rp = p->right;
			s = rp->left;
			while (s != NULL)
			{
				f = rp;
				rp = s;
				s = rp->left;
			}

			if (f != p)
			{
				f->left = rp->right;
				rp->right = p->right;
			}
			rp->left = p->left;
		}
	}

	if (q == NULL)
		*root = *rp;
	else if (p = q->left)
		q->left = rp;
	else
		q->right = rp;

	printf("\nPreorder after removing [%d]: ", value);
	writePreorder(root);
	printf("\n");
	system("PAUSE");
	printf("\n");
}

void deleteLoop(node* root)
{
	char answer[256] = {};
	char value[256] = {};

	do
	{
		printf("Do you want to delete the node:\n\n[1] - Yes.\n[2] - No.\n\nPlease specify: ");
		fgets(answer, 256, stdin);

		if (atoi(answer) == 1)
		{
			printf("\nPlease enter value: ");
			fgets(value, 256, stdin);
			deleteNode(atoi(value), root);
		}

		else if (atoi(answer) == 2)
		{
			system("clear");
			break;
		}

		else
		{
			printf("\nPlease enter [1] or [2].\n");
			sleep();
		}

		system("clear");

	} while (true);
}

node* searchBST(node* root, int value)
{
	if (root == NULL || root->value == value)
		return root;

	else if (root->value > value)
		return searchBST(root->left, value);

	else
		return searchBST(root->right, value);
}

void getInput(node** root)
{
	char answer[256] = {};
	char value[256] = {};
	
	do
	{
		printf("Do you want to create a new node:\n\n[1] - Yes.\n[2] - No.\n\nPlease specify: ");
		fgets(answer, 256, stdin);

		if (atoi(answer) == 1)
		{
			printf("\nPlease enter value: ");
			fgets(value, 256, stdin);
			insertElement(createNode(atoi(value)), root);
		}

		else if (atoi(answer) == 2)
		{
			system("clear");
			break;
		}

		else
		{
			printf("\nPlease enter [1] or [2].\n");
			sleep();
		}
		
		system("clear");

	} while (true);


	return;
}

int main()
{
	node* treeRoot = NULL;
	getInput(&treeRoot);

	printf("\nInorder: ");
	writeInorder(treeRoot);
	
	printf("\nPreorder: ");
	writePreorder(treeRoot);

	printf("\n");

	if (isBalanced(treeRoot))
		printf("\nBST is balanced.\n");

	else
		printf("\nBST is not balanced.\n"); 

	deleteLoop(treeRoot);

	return 0;
}