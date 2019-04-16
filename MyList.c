#include "../../OSUtils/OSU.h"
#include "../MiniList.h"

void MiniList_Init(TMiniList *pList)
{
	pList->pHead = NULL;
	pList->pTail = NULL;
	pList->iLength = 0;
}

void MiniList_AddTail(TMiniList *pList, TMiniListNode *pNode)
{
	pNode->pNext = NULL;
	if (pList->pHead == NULL)
	{
		pList->pHead = pNode;
		pList->pTail = pNode;
	}
	else
	{
		pList->pTail->pNext = pNode;
		pList->pTail = pNode;
	}
	pList->iLength ++;
}

TMiniListNode * MiniList_ShowHead(TMiniList *pList)
{
	return pList->pHead;
}

TMiniListNode * MiniList_ShowNext(TMiniList *pList, TMiniListNode *pNode)
{
	return pNode->pNext;
}

TMiniListNode * MiniList_RemoveHead(TMiniList *pList)
{
	TMiniListNode *pNode;
	pNode = pList->pHead;
	if (pNode == NULL)
	{
		return NULL;
	}
	if (pList->pHead == pList->pTail)
	{
		pList->pHead = NULL;
		pList->pTail = NULL;
	}
	else
	{
		pList->pHead = pList->pHead->pNext;
	}
	pList->iLength --;
	return pNode;
}

void MiniList_RemoveNode(TMiniList *pList, TMiniListNode *pNode)
{
	TMiniListNode *pFindNode;
	pFindNode = pList->pHead;
	if (pFindNode == pNode)
	{
		pList->pHead = pList->pHead->pNext;
		pList->iLength --;
		if (pList->pHead == NULL)
		{
			pList->pTail = NULL;
		}
	}
	else
	{
		if (pFindNode == NULL)
		{
			return ;
		}
		while (pFindNode->pNext != NULL)
		{
			if (pFindNode->pNext == pNode)
			{
				pFindNode->pNext = pNode->pNext;
				pList->iLength --;
				if (pFindNode->pNext == NULL)
				{
					pList->pTail = pFindNode;
				}
				break;
			}
			pFindNode = pFindNode->pNext;
		}
	}
}

void MiniList_DeleteNode(TMiniList *pList, TMiniListNode *pNode)
{
	MiniList_RemoveNode(pList, pNode);
	if (pNode != NULL)
	{
		free(pNode);
	}
}

void MiniList_DeleteNodeWithClose(TMiniList *pList, TMiniListNode *pNode, void (*pCLOSE)(void *p))
{
	MiniList_RemoveNode(pList, pNode);
	if (pNode != NULL)
	{
		pCLOSE(pNode);
	}
}

TMiniListNode * MiniList_ShowNode(TMiniList *pList, TMiniListNode *pNode)
{
	TMiniListNode *pNodeTemp;
	pNodeTemp = MiniList_ShowHead(pList);
	while (pNodeTemp != NULL)
	{
		if (pNodeTemp == pNode)
		{
			return pNodeTemp;
		}
		pNodeTemp = MiniList_ShowNext(pList, pNodeTemp);
	}
	return NULL;
}

TMiniListNode * MiniList_FindNode(TMiniList *pList, unsigned int uiKey)
{
	TMiniListNode *pNode;
	pNode = MiniList_ShowHead(pList);
	while (pNode != NULL)
	{
		if (pNode->uiKey == uiKey)
		{
			return pNode;
		}
		pNode = MiniList_ShowNext(pList, pNode);
	}
	return NULL;
}

TMiniListNode * MiniList_FindNodeByIdx(TMiniList *pList, int iIdx)
{
	int i = 0;
	TMiniListNode *pNode;
	pNode = MiniList_ShowHead(pList);
	while (pNode != NULL)
	{
		if (i == iIdx)
		{
			return pNode;
		}
		i ++;
		pNode = MiniList_ShowNext(pList, pNode);
	}
	return NULL;
}

char MiniList_IsEmpty(TMiniList *pList)
{
	return (pList->pHead == NULL);
}

int MiniList_Length(TMiniList *pList)
{
	return pList->iLength;
}

void MiniList_Clear(TMiniList *pList)
{
	while (pList->pHead != NULL)
	{
		TMiniListNode *pNode;
		pNode = pList->pHead;
		pList->pHead = pList->pHead->pNext;
		free(pNode);
	}
	pList->pTail = NULL;
	pList->iLength = 0;
}

void MiniList_ClearWithClose(TMiniList *pList, void (*pCLOSE)(void *p))
{
	while (pList->pHead != NULL)
	{
		TMiniListNode *pNode;
		pNode = pList->pHead;
		pList->pHead = pList->pHead->pNext;
		pCLOSE(pNode);
	}
	pList->pTail = NULL;
	pList->iLength = 0;
}
