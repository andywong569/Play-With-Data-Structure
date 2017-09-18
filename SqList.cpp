#include <stdio.h>

#define OK 		1
#define ERROR 	0
#define TRUE	1
#define FALSE	0

typedef int Status;
//	Status是函数的类型，其值函数结果状态代码，如OK等

#define MAXSIZE	20
typedef int ElemType;
typedef struct
{
	ElemType data[MAXSIZE];
	int length;
}SqList;

//	获取元素
Status GetElem(SqList L, int i, ElemType* e)
{
	if(L.length == 0 || i < 1 || i > L.length)
		return ERROR;
	
	*e = L.data[i];
	return OK;
}

//	插入元素
Status ListInsert(SqList* L, int i, ElemType e)
{
	if(L.length == MAXSIZE)		//	顺序线性表已满
		return ERROR;
	
	if(i < 1 || i > L->length + 1)	//	不在范围内
		return ERROR;
		
	int j = L->length - 1;
	while(i <= (j+1))
	{
		L->data[j+1] = L->data[j];
		--j;
	}
	L->data[i-1] = e;
	L->length++;
	return OK;
}

//	删除操作
Status ListDelete(SqList* L, int i, ElemType* e)
{
	if(L->length == 0)		//	线性表为空
		return ERROR;
	
	if(i < 1 || i > L->length)		//	不在范围内
		return ERROR;
	
	*e = L->data[i-1];
	int j = i;
	while(j < L->length)
		L->data[j-1] = L->data[j];
	
	L->length--;
	
	return OK;
}