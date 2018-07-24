#include <stdio.h>
#include <string>


typedef struct TreeNode* TreeNodePtr;

struct TreeNode
{
	TreeNode*	leftPtr;
	int data;
	TreeNode*	rightPtr;
};
void insertNode(TreeNodePtr * treePtr,int value)
{
	if(*treePtr == NULL)
	{
		*treePtr = (TreeNode *)malloc(sizeof(TreeNode));
		if(*treePtr != NULL)
		{
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
	}
	else
	{
		if(value < (*treePtr)->data)
			insertNode(&((*treePtr)->leftPtr),value);
		else
		{
			insertNode(&((*treePtr)->rightPtr),value);
		}

	}
}

TreeNode *binaryTreeSereach(TreeNode * const treePtr, int value)
{
	TreeNode *tempPtr = treePtr;
	while(tempPtr != NULL && tempPtr->data != value)
	{
		if(value < tempPtr->data)
			tempPtr = tempPtr->leftPtr;
		else
			tempPtr = tempPtr->rightPtr;
	}
	return tempPtr;
}
/*
二叉树的删除
1.删除节点是叶节点，即没有子节点，只要把删除节点的父节点中对应的指针指向NULL，并释放空间
2.删除节点有一个子节点，把删除节点的父节点中对应的指针指向删除节点的子节点即可。然后释放掉删除节点的空间
3.删除节点有两个子节点，需要找到一个替代其父节点的节点，并且保持树的排序，
替换的键值分别在删除节点的左子树中最右边的节点，删除节点右子树中最左边的节点。
该算法采用左子树最右边的节点
*/
void deleteNode(TreeNode **treePtrP, int value)
{
	TreeNode *deleteNodePtr = *treePtrP;
	TreeNode *parentNodeOfDeletePtr = *treePtrP;
	TreeNode *substituteNodePtr;
	TreeNode *parentNodeOfSubstitutePtr;
	//find deleNode and its parentNode
	while(deleteNodePtr != NULL && value != deleteNodePtr->data)
	{
		parentNodeOfDeletePtr = deleteNodePtr;
		if(deleteNodePtr->data > value)
		{
			deleteNodePtr = deleteNodePtr->leftPtr;
		}
		else
		{
			deleteNodePtr = deleteNodePtr->rightPtr;
		}
	}
	//case that can't find such Node
	if(deleteNodePtr == NULL)
	{
		printf("no such Node,delete fail\n");
		return;
	}
	//delete a leafNode
	if(deleteNodePtr->leftPtr == NULL && deleteNodePtr->rightPtr == NULL)
	{
		//delete Node is root
		if(parentNodeOfDeletePtr == NULL)
		{
			*treePtrP = NULL;
		}
		else if(parentNodeOfDeletePtr->leftPtr == deleteNodePtr)
		{
			parentNodeOfDeletePtr->leftPtr = NULL;
		}
		else
		{
			parentNodeOfDeletePtr->rightPtr = NULL;
		}
	}
	//delete a Node which has a left child Node 
	else if(deleteNodePtr->leftPtr != NULL && deleteNodePtr->rightPtr == NULL)
	{
		//delete Node is root
		if(parentNodeOfDeletePtr == NULL)
		{
			*treePtrP = deleteNodePtr->leftPtr;
		}
		else if(parentNodeOfDeletePtr->rightPtr == deleteNodePtr)
		{
			parentNodeOfDeletePtr->rightPtr = deleteNodePtr->leftPtr;
		}
		else
		{
			parentNodeOfDeletePtr->leftPtr = deleteNodePtr->leftPtr;
		}
	}
	//delete a Node which has a right child Node 
	else if(deleteNodePtr->leftPtr == NULL && deleteNodePtr->rightPtr != NULL)
	{
		//delete Node is root
		if(parentNodeOfDeletePtr == NULL)
		{
			*treePtrP = deleteNodePtr->rightPtr;
		}
		else if(parentNodeOfDeletePtr->rightPtr == deleteNodePtr)
		{
			parentNodeOfDeletePtr->rightPtr = deleteNodePtr->rightPtr;
		}
		else
		{
			parentNodeOfDeletePtr->leftPtr = deleteNodePtr->rightPtr;
		}
	}
	//delete a Node which has a left and a right child Node
	else
	{
		parentNodeOfSubstitutePtr = deleteNodePtr;
        substituteNodePtr = deleteNodePtr->leftPtr;

        //search down and right
        while (substituteNodePtr->rightPtr != NULL)
        {
            parentNodeOfSubstitutePtr = substituteNodePtr;
            substituteNodePtr = substituteNodePtr->rightPtr;

        }

        if (parentNodeOfSubstitutePtr->leftPtr == substituteNodePtr)
        {
            parentNodeOfSubstitutePtr->leftPtr = substituteNodePtr->leftPtr;
        }
        else
        {
            parentNodeOfSubstitutePtr->rightPtr = substituteNodePtr->leftPtr;
        }

        deleteNodePtr->data = substituteNodePtr->data;//替换数值不替换节点方式
        deleteNodePtr = substituteNodePtr;

    }

	free(deleteNodePtr);
}
void outputTree(TreeNode *treePtr, int spaces)
{

	int loop;

    while (treePtr != NULL) {
		outputTree(treePtr->rightPtr, spaces + 4);
		
       

        for (loop = 1; loop <= spaces; loop++) {
            printf(" ");
        } 

        printf("%d\n", treePtr->data);
		outputTree(treePtr->leftPtr, spaces + 4);
        
        treePtr = NULL;
    } 
}
void main()
{
	int arr[] = { 45, 83, 28, 97, 71, 40, 18, 77};
    int i;                      /* loop counter */
    int item;                   /* value to deal with */
    int totalSpaces = 0;        /* spaces preceding output */
    TreeNode *rootPtr = NULL; /* points to the tree root */

    printf("The numbers being placed in the tree are:\n\n");
	
    for (i = 0; i < sizeof(arr) / sizeof(int); i++) {
        item = arr[i];
        printf("%3d", item);
        insertNode(&rootPtr, item);
    }
	printf("\n\n\nnow the tree is:\n\n");
	if (rootPtr == NULL)
        printf("empty tree\n");
    else
        outputTree(rootPtr, totalSpaces);
	deleteNode(&rootPtr,83);
	printf("\n\n\nnow the tree is:\n\n");
	 outputTree(rootPtr, totalSpaces);
	system("pause");
}
