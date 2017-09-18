#include <stdio.h>

#define OK 		1
#define ERROR 	0
#define TRUE	1
#define FALSE	0

typedef int Status;
//	Status是函数的类型，其值函数结果状态代码，如OK等

typedef int ElemType;
typedef struct Node
{
	ElemType data;
	Node* next;
}Node;

typedef struct Node* LinkList;

//	获取特定位置节点
LinkList GetNode(LinkList* L, int i)
{
	Node* currNode = *L;
	int index = 0;
	while (currNode && index < i)
	{
		currNode = currNode->next;
		++index;
	}

	return currNode;
}

//	获取元素
Status GetElem(LinkList L, int i, ElemType* e)
{
	Node* currNode = GetNode(&L, i);
	if (currNode == nullptr)
		return ERROR;

	*e = currNode->data;
	return OK;
}

//	插入元素
Status ListInsert(LinkList* L, int i, ElemType e)
{
	Node* preNode = GetNode(L, i-1);
	if (preNode == nullptr)
		return ERROR;

	Node* insNode = new Node;
	insNode->data = e;
	insNode->next = preNode->next;
	preNode->next = insNode;

	return OK;
}

//	删除元素
Status ListDelete(LinkList* L, int i, ElemType* e)
{
	Node* preNode = GetNode(L, i - 1);
	if (preNode == nullptr)
		return ERROR;

	Node* currNode = preNode->next;
	if (currNode == nullptr)
		return ERROR;

	preNode->next = currNode->next;
	*e = currNode->data;
	delete currNode;	//	之前new出来的对象
	currNode = nullptr;

	return OK;
}

//	随机产生n个元素的值，头插法
void CreateListHead(LinkList* L, int n)
{
	*L = new Node;
	(*L)->next = nullptr;
	srand(time(0));
	
	for (int i = 0; i != n; ++i)
	{
		Node* p = new Node;
		p->data = rand() % 100 + 1;
		p->next = (*L)->next;
		(*L)->next = p;
	}
}

//	随机产生n个元素的值，尾插法
void CreateListTail(LinkList* L, int n)
{
	*L = new Node;
	(*L)->next = nullptr;
	Node* currNode = *L;
	srand(time(nullptr));
	for (size_t i = 0; i < n; i++)
	{
		Node* p = new Node;
		p->data = rand() % 100 + 1;
		currNode->next = p;
		currNode = p;
	}
	currNode->next = nullptr;
}

//	清空表
Status ClearList(LinkList* L)
{
	Node* currNode = (*L)->next;
	while (currNode)
	{
		Node* nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	(*L)->next = nullptr;
	return OK;
}