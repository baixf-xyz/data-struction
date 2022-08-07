## 数据结构c/c++伪码

玩玩各种算法：[Data Structure Visualizations](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html)

### 一、线性表

```c
// InitList(SqList *&L):初始化顺序表
// DestroyList(SqList *&L):释放顺序表L
// ListEmpty(SqList *&L)：判断顺序表L是否为空表
// ListLength(SqList *&L)：返回顺序表L的元素个数
// DispList(SqList *&L)：输出顺序表L
// GetElem(SqList *&L,int i,ElemType &e)：获取顺序表L中的第I个元素
// LocateElem(SqList *&L,ElemType e):在顺序表L中查找元素e
// ListInsert(SqList *&L,int i,ElemType e):在顺序表L中第i个位置插入元素e
// ListDelete(SqList *&L,ElemType &e):从顺序表中删除第i个元素
```

#### 1.顺序表

```c
//顺序表
#include<stdio.h>
#include<malloc.h>
#define MaxSize 50

typedef char ElemType;

typedef struct{
    ElemType data[MaxSize];//存放顺序表元素
    int length;//存放顺序表长度
}SqList;//声明顺序表的类型

void CreateList(SqList *&L,ElemType a[],int n)//整体建立顺序表
{
    L=(SqList *)malloc(sizeof(SqList));
    for(int i=0;i<n;i++)
    	L->data[i]=a[i];
   	L->length=n;
}

void InitList(SqList *&L)//初始化线性表
{
    L=(SqList *)malloc(sizeof(SqList));//分配存放线性表的空间
    L->length=0;
}

void DestroyList(SqList *&L)//销毁线性表
{
    free(L);
}

bool ListEmpty(SqList *L)//判断线性表是否为空表
{
    return(L->length==0);
}

int ListLength(SqList *L)//求线性表的长度
{
    return(L->length);
}

void DispList(SqList *L)//输出线性表
{
    for(int i = 0;i<L->length;i++)
        printf("%c",L->data[i]);
    printf("\n");
}

bool GetElem(SqList *L,int i,ElemType &e)//求线性表中第i个元素值
{
    if(i<1 || i>L->length)//※稳健性
        return false;
    e=L->data[i-1];
    return true;
}

int LocateElem(SqList *L,ElemType e)//查找第一个元素值为e的元素序号
{
    int i=0;
    while(i<L->length && L->data[i]!=e)
        i++;
    if(i>L->length)
        return 0;
    else
        return i+1;
}

bool ListInsert(SqList *&L,int i,ElemType e)//插入第i个元素
{
    int j;
    if(i<1 || i>L->length+1)//※稳健性
        return false;
    i--;//将顺序表位序转化为data下标
    for(j=L->length;j>i;j--)//将data[i]及后面元素后移一个位置
        L->data[j]=L->data[j-1];
    L->data[i]=e;
    L->length++;//顺序表长度增1
    return true;
}

bool ListDelete(SqList *&L,int i,ElemType &e)//删除第i个元素
{
    int j;
    if(i<1 || i>L->length)//※稳健性
        return false;
    i--;//将顺序表转换为data下标
    e=L->data[i];
    for(j=i;j<L->length-1;j++)//将data[i]之后的元素前移一个位置
        L->data[j]=L->data[j+1];
    L->length--;//顺序表长度减1
    return true;
}
```

#### 2.单链表

```c
//单链表
#include<stdio.h>
#include<malloc.h>

typedef char ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;//指向后继结点
}LinkNode;//声明单链表节点类型

void CreateListF(LinkNode *&L,ElemType a[],int n)//头插法建立单链表
{
    LinkNode *s;
    L=(LinkNode *)malloc(sizeof(LinkNode));//创建头节点
    L->next=NULL;
    for(int i=0;i<n;i++){
        s=(LinkNode*)malloc(sizeof(LinkNode));//创建新节点
        s->data=a[i];
        s->next=L->next;//将结点s插在原开始结点之前，头结点之后
        L->next=s;
    }
}

void CreateListR(LinkNode *&L,ElemType a[],int n)//尾插法创建单链表
{
    LinkNode *s,*r;
    L=(LinkNode *)malloc(sizeof(LinkNode));//创建头节点
    L->next=NULL;
    r=L;//r始终指向尾结点，开始时指向头节点
    for(int i=0;i<n;i++){
        s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点s
        s->data=a[i];
        r->next=s;//将结点s插入r结点之后
        r=s;
    }
    r->next=NULL;//尾结点next域置为空表
}

void InitList(LinkNode *&L)//初始化线性表
{
    L=(LinkNode *)malloc(sizeof(LinkNode));//创建头节点
    L->next=NULL;//将单链表置为空表
}

void DestroyList(LinkNode *&L)//销毁线性表
{
    LinkNode *pre=L,*p=pre->next;
    while(p!=NULL){
        free(pre);
        pre=p;//pre、p后移一个节点
        p=pre->next;
    }
    free(pre);//此时p为NULL，pre指向尾结点，释放它
}

bool ListEmpty(LinkNode *L)//判断线性表是否为空表
{
    return(L->next==NULL);
}

int ListLength(LinkNode *L)//求线性表的长度
{
    int i=0;
    LinkNode *p=L ;//p指向头节点，i置为0（即头结点的序号为0）
    while (p->next!=NULL)
    {
        i++;
        p=p->next;
    }
    return(i);//循环结束，p指向尾结点，其序号i为结点个数
}

void DispList(LinkNode *L)//输出线性表
{
    LinkNode *p=L->next;//p指向首结点
    while (p!=NULL)//p不为null，输出p结点的data域
    {
        printf("%c",p->data);
        p=p->next;//p指向下一个结点
    }
    printf("\n");
}

bool GetElem(LinkNode *L,int i,ElemType &e)//求线性表中第i个元素值
{
    int j=0;
    LinkNode *p =L;//p指向头节点，j置为0（即头节点的序号为0）
    if(i<=0) return false;////※稳健性 i错误返回假
    while (j<i&&p!=NULL)//找第i个结点p
    {
        j++;
        p=p->next;
    }
    if(p==NULL)////※稳健性 不存在第i个数据结点，返回false
        return false;
    else//存在第i个数据结点，返回true
        {
            e=p->data;
            return true;
        }
}

int LocateElem(LinkNode *L,ElemType e)//查找第一个值为e的元素序号
{
    int i=1;
    LinkNode *p=L->next;//p指向首结点，i置为1（即首结点的序号为1）
    while(p!=NULL&&p->data!=e)//查找data值为e的结点，其序号为i
    {
        p=p->next;
        i++;
    }
    if(p==NULL)////※稳健性 不存在值为e的结点，返回0
        return(0);
    else//存在值为e的结点，返回其逻辑序号i
        return(i);
}

bool ListInsert(LinkNode *&L,int i,ElemType e)//插入第i个元素
{
    int j=0;
    LinkNode *p=L,*s;//p指向头结点，j置为0（即首结点的序号为0）
    if(i<=0) return false;////※稳健性 i错误返回假
    while(j<i-1&&p!=NULL)//查找第i-1个结点p
    {
        j++;
        p=p->next;
    }
    if(p==NULL)////※稳健性 未找到第i-1个结点，返回false
        return false;
    else//找到第i-1个结点p，插入新节点并返回true
        {
            s=(LinkNode *)malloc(sizeof(LinkNode));//※易考点 顺序不可乱
            s->data=e;//创建新结点s，其data域置为e
            s->next=p->next;//将结点s插入到结点p之后
            p->next=s;
            return true;
        }
}

bool ListDelete(LinkNode *&L,int i,ElemType &e)//删除第i个元素
{
    int j=0;
    LinkNode *p=L,*q;//p指向头节点，j置为0（即头结点的序号为0）
    if(i<=0) return false;////※稳健性 i错误返回false
    while (j<i-1&&p!=NULL)//查找第i-1个结点
    {
        j++;
        p=p->next;
    }
    if(p==NULL)////※稳健性 未找到第i-1个结点返回false
        return false;
    else//找到第i-1个结点
    {
        q=p->next;//q指向第i个结点
        if(q==NULL)////※稳健性 若不存在第i个结点，返回false
            return false;
        e=q->data;
        p->next=q->next;//从单链表中删除q结点
        free(q);//释放q结点
        return true;//返回true表示成功删除第i个结点
    }
}
```

#### 3.双链表

```c
#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct DNode		//定义双链表结点类型
{
	ElemType data;
	struct DNode *prior;	//指向前驱结点
	struct DNode *next;		//指向后继结点
} DLinkNode;

void CreateListF(DLinkNode *&L,ElemType a[],int n)
//头插法建双链表
{
	DLinkNode *s;
	L=(DLinkNode *)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior=L->next=NULL;
	for (int i=0;i<n;i++)
	{	
		s=(DLinkNode *)malloc(sizeof(DLinkNode));//创建新结点
		s->data=a[i];
		s->next=L->next;			//将结点s插在原开始结点之前,头结点之后
		if (L->next!=NULL) L->next->prior=s;
		L->next=s;s->prior=L;
	}
}

void CreateListR(DLinkNode *&L,ElemType a[],int n)
//尾插法建双链表
{
	DLinkNode *s,*r;
	L=(DLinkNode *)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior=L->next=NULL;
	r=L;					//r始终指向终端结点,开始时指向头结点
	for (int i=0;i<n;i++)
	{	
		s=(DLinkNode *)malloc(sizeof(DLinkNode));//创建新结点
		s->data=a[i];
		r->next=s;s->prior=r;	//将结点s插入结点r之后
		r=s;
	}
	r->next=NULL;				//尾结点next域置为NULL
}

void InitList(DLinkNode *&L)
{
	L=(DLinkNode *)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior=L->next=NULL;
}

void DestroyList(DLinkNode *&L)
{
	DLinkNode *pre=L,*p=pre->next;
	while (p!=NULL)
	{
		free(pre);
		pre=p;
		p=pre->next;
	}
	free(pre);
}

bool ListEmpty(DLinkNode *L)
{
	return(L->next==NULL);
}

int ListLength(DLinkNode *L)
{
	DLinkNode *p=L;
	int i=0;
	while (p->next!=NULL)
	{
		i++;
		p=p->next;
	}
	return(i);
}

void DispList(DLinkNode *L)
{
	DLinkNode *p=L->next;
	while (p!=NULL)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}

bool GetElem(DLinkNode *L,int i,ElemType &e)
{
	int j=0;
	DLinkNode *p=L;
	if (i<=0) return false;		//i错误返回假
	while (j<i && p!=NULL)
	{
		j++;
		p=p->next;
	}
	if (p==NULL)
		return false;
	else
	{
		e=p->data;
		return true;
	}
}

int LocateElem(DLinkNode *L,ElemType e)
{
	int n=1;
	DLinkNode *p=L->next;
	while (p!=NULL && p->data!=e)
	{
		n++;
		p=p->next;
	}
	if (p==NULL)
		return(0);
	else
		return(n);
}

bool ListInsert(DLinkNode *&L,int i,ElemType e)
{
	int j=0;
	DLinkNode *p=L,*s;
	if (i<=0) return false;		//i错误返回假
	while (j<i-1 && p!=NULL)
	{
		j++;
		p=p->next;
	}
	if (p==NULL)				//未找到第i-1个结点
		return false;
	else						//找到第i-1个结点p
	{
		s=(DLinkNode *)malloc(sizeof(DLinkNode));	//创建新结点s
		s->data=e;	
		s->next=p->next;		//将结点s插入到结点p之后
		if (p->next!=NULL) 
			p->next->prior=s;
		s->prior=p;
		p->next=s;
		return true;
	}
}

bool ListDelete(DLinkNode *&L,int i,ElemType &e)
{
	int j=0;
	DLinkNode *p=L,*q;
	if (i<=0) return false;		//i错误返回假
	while (j<i-1 && p!=NULL)
	{
		j++;
		p=p->next;
	}
	if (p==NULL)				//未找到第i-1个结点
		return false;
	else						//找到第i-1个结点p
	{
		q=p->next;				//q指向要删除的结点
		if (q==NULL) 
			return false;		//不存在第i个结点
		e=q->data;
		p->next=q->next;		//从单链表中删除*q结点
		if (p->next!=NULL) p->next->prior=p;
		free(q);				//释放q结点
		return true;
	}
}
```

#### 4.循环单链表

```c
#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct LNode		//定义单链表结点类型
{
	ElemType data;
    struct LNode *next;
} LinkNode;

void CreateListF(LinkNode *&L,ElemType a[],int n)
//头插法建立循环单链表
{
	LinkNode *s;int i;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	for (i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点
		s->data=a[i];
		s->next=L->next;			//将结点s插在原开始结点之前,头结点之后
		L->next=s;
	}
	s=L->next;	
	while (s->next!=NULL)			//查找尾结点,由s指向它
		s=s->next;
	s->next=L;						//尾结点next域指向头结点

}

void CreateListR(LinkNode *&L,ElemType a[],int n)
//尾插法建立循环单链表
{
	LinkNode *s,*r;int i;
	L=(LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next=NULL;
	r=L;					//r始终指向终端结点,开始时指向头结点
	for (i=0;i<n;i++)
	{	
		s=(LinkNode *)malloc(sizeof(LinkNode));//创建新结点
		s->data=a[i];
		r->next=s;			//将结点s插入结点r之后
		r=s;
	}
	r->next=L;				//尾结点next域指向头结点
}

void InitList(LinkNode *&L)
{
	L=(LinkNode *)malloc(sizeof(LinkNode));	//创建头结点
	L->next=L;
}

void DestroyList(LinkNode *&L)
{
	LinkNode *p=L,*q=p->next;
	while (q!=L)
	{
		free(p);
		p=q;
		q=p->next;
	}
	free(p);
}

bool ListEmpty(LinkNode *L)
{
	return(L->next==L);
}

int ListLength(LinkNode *L)
{
	LinkNode *p=L;int i=0;
	while (p->next!=L)
	{
		i++;
		p=p->next;
	}
	return(i);
}

void DispList(LinkNode *L)
{
	LinkNode *p=L->next;
	while (p!=L)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}

bool GetElem(LinkNode *L,int i,ElemType &e)
{
	int j=0;
	LinkNode *p;
	if (L->next!=L)		//单链表不为空表时
	{
		if (i==1)
		{
			e=L->next->data;
			return true;
		}
		else			//i不为1时
		{
			p=L->next;
			while (j<i-1 && p!=L)
			{
				j++;
				p=p->next;
			}
			if (p==L)
				return false;
			else
			{
				e=p->data;
				return true;
			}
		}
	}
	else				//单链表为空表时
		return false;
}

int LocateElem(LinkNode *L,ElemType e)
{
	LinkNode *p=L->next;
	int n=1;
	while (p!=L && p->data!=e)
	{
		p=p->next;
		n++;
	}
	if (p==L)
		return(0);
	else
		return(n);
}

bool ListInsert(LinkNode *&L,int i,ElemType e)
{
	int j=0;
	LinkNode *p=L,*s;
	if (p->next==L || i==1)		//原单链表为空表或i==1时
	{
		s=(LinkNode *)malloc(sizeof(LinkNode));	//创建新结点s
		s->data=e;								
		s->next=p->next;		//将结点s插入到结点p之后
		p->next=s;
		return true;
	}
	else
	{
		p=L->next;
		while (j<i-2 && p!=L)
		{
			j++;
			p=p->next;
		}
		if (p==L)				//未找到第i-1个结点
			return false;
		else					//找到第i-1个结点p
		{
			s=(LinkNode *)malloc(sizeof(LinkNode));	//创建新结点s
			s->data=e;								
			s->next=p->next;						//将结点s插入到结点p之后
			p->next=s;
			return true;
		}
	}
}

bool ListDelete(LinkNode *&L,int i,ElemType &e)
{
	int j=0;
	LinkNode *p=L,*q;
	if (p->next!=L)					//原单链表不为空表时
	{
		if (i==1)					//i==1时
		{
			q=L->next;				//删除第1个结点
			e=q->data;
			L->next=q->next;
			free(q);
			return true;
		}
		else						//i不为1时
		{
			p=L->next;
			while (j<i-2 && p!=L)
			{
				j++;
				p=p->next;
			}
			if (p==L)				//未找到第i-1个结点
				return false;
			else					//找到第i-1个结点p
			{
				q=p->next;			//q指向要删除的结点
				e=q->data;
				p->next=q->next;	//从单链表中删除q结点
				free(q);			//释放q结点
				return true;
			}
		}
	}
	else return false;
}
```

#### 5.循环双链表

```c
#include <stdio.h>
#include <malloc.h>

typedef int ElemType;

typedef struct DNode		//定义双链表结点类型
{
	ElemType data;
	struct DNode *prior;	//指向前驱结点
	struct DNode *next;		//指向后继结点
} DLinkNode;

void CreateListF(DLinkNode *&L,ElemType a[],int n)
//头插法建立循环双链表
{
	DLinkNode *s;int i;
	L=(DLinkNode *)malloc(sizeof(DLinkNode));  	//创建头结点
	L->next=NULL;
	for (i=0;i<n;i++)
	{	
		s=(DLinkNode *)malloc(sizeof(DLinkNode));//创建新结点
		s->data=a[i];
		s->next=L->next;			//将结点s插在原开始结点之前,头结点之后
		if (L->next!=NULL) L->next->prior=s;
		L->next=s;s->prior=L;
	}
	s=L->next;	
	while (s->next!=NULL)			//查找尾结点,由s指向它
		s=s->next;
	s->next=L;						//尾结点next域指向头结点
	L->prior=s;						//头结点的prior域指向尾结点

}

void CreateListR(DLinkNode *&L,ElemType a[],int n)
//尾插法建立循环双链表
{
	DLinkNode *s,*r;int i;
	L=(DLinkNode *)malloc(sizeof(DLinkNode));  //创建头结点
	L->next=NULL;
	r=L;					//r始终指向尾结点,开始时指向头结点
	for (i=0;i<n;i++)
	{	
		s=(DLinkNode *)malloc(sizeof(DLinkNode));//创建新结点
		s->data=a[i];
		r->next=s;s->prior=r;	//将结点s插入结点r之后
		r=s;
	}
	r->next=L;				//尾结点next域指向头结点
	L->prior=r;				//头结点的prior域指向尾结点
}

void InitList(DLinkNode *&L)
{
	L=(DLinkNode *)malloc(sizeof(DLinkNode));  	//创建头结点
	L->prior=L->next=L;
}

void DestroyList(DLinkNode *&L)
{
	DLinkNode *p=L,*q=p->next;
	while (q!=L)
	{
		free(p);
		p=q;
		q=p->next;
	}
	free(p);
}

bool ListEmpty(DLinkNode *L)
{
	return(L->next==L);
}

int ListLength(DLinkNode *L)
{
	DLinkNode *p=L;
	int i=0;
	while (p->next!=L)
	{
		i++;
		p=p->next;
	}
	return(i);
}

void DispList(DLinkNode *L)
{
	DLinkNode *p=L->next;
	while (p!=L)
	{
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}

bool GetElem(DLinkNode *L,int i,ElemType &e)
{
	int j=0;
	DLinkNode *p;
	if (L->next!=L)		//双链表不为空表时
	{
		if (i==1)
		{
			e=L->next->data;
			return true;
		}
		else			//i不为1时
		{
			p=L->next;
			while (j<i-1 && p!=L)
			{
				j++;
				p=p->next;
			}
			if (p==L)
				return false;
			else
			{
				e=p->data;
				return true;
			}
		}
	}
	else				//双链表为空表时
		return 0;
}

int LocateElem(DLinkNode *L,ElemType e)
{
	int n=1;
	DLinkNode *p=L->next;
	while (p!=NULL && p->data!=e)
	{
		n++;
		p=p->next;
	}
	if (p==NULL)
		return(0);
	else
		return(n);
}

bool ListInsert(DLinkNode *&L,int i,ElemType e)
{
	int j=0;
	DLinkNode *p=L,*s;
	if (p->next==L)					//原双链表为空表时
	{	
		s=(DLinkNode *)malloc(sizeof(DLinkNode));	//创建新结点s
		s->data=e;
		p->next=s;s->next=p;
		p->prior=s;s->prior=p;
		return true;
	}
	else if (i==1)					//原双链表不为空表但i=1时
	{
		s=(DLinkNode *)malloc(sizeof(DLinkNode));	//创建新结点s
		s->data=e;
		s->next=p->next;p->next=s;	//将结点s插入到结点p之后
		s->next->prior=s;s->prior=p;
		return true;
	}
	else
	{	
		p=L->next;
		while (j<i-2 && p!=L)
		{	j++;
			p=p->next;
		}
		if (p==L)				//未找到第i-1个结点
			return false;
		else					//找到第i-1个结点*p
		{
			s=(DLinkNode *)malloc(sizeof(DLinkNode));	//创建新结点s
			s->data=e;	
			s->next=p->next;	//将结点s插入到结点p之后
			if (p->next!=NULL) p->next->prior=s;
			s->prior=p;
			p->next=s;
			return true;
		}
	}
}

bool ListDelete(DLinkNode *&L,int i,ElemType &e)
{
	int j=0;
	DLinkNode *p=L,*q;
	if (p->next!=L)					//原双链表不为空表时
	{	
		if (i==1)					//i==1时
		{	
			q=L->next;				//删除第1个结点
			e=q->data;
			L->next=q->next;
			q->next->prior=L;
			free(q);
			return true;
		}
		else						//i不为1时
		{	
			p=L->next;
			while (j<i-2 && p!=NULL)		
			{
				j++;
				p=p->next;
			}
			if (p==NULL)				//未找到第i-1个结点
				return false;
			else						//找到第i-1个结点p
			{
				q=p->next;				//q指向要删除的结点
				if (q==NULL) return 0;	//不存在第i个结点
				e=q->data;
				p->next=q->next;		//从单链表中删除q结点
				if (p->next!=NULL) p->next->prior=p;
				free(q);				//释放q结点
				return true;
			}
		}
	}
	else return false;					//原双链表为空表时
}
```

### 二、栈

#### 1.顺序栈

```c
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100

typedef char ElemType;

typedef struct 
{	
	ElemType data[MaxSize];  //存放栈中的数据元素
	int top;				//栈顶指针，即存放栈顶元素在data数组中的下标
} SqStack;					//顺序栈类型

void InitStack(SqStack *&s) //初始化栈
{
	s=(SqStack *)malloc(sizeof(SqStack)); //分配一个顺序栈空间，首地址存放在s中
	s->top=-1; //栈顶指针置为-1
} 

void DestroyStack(SqStack *&s) //销毁栈
{
	free(s); //释放指针
}

bool StackEmpty(SqStack *s) //判断栈是否为空
{
	return(s->top==-1);
}

bool Push(SqStack *&s,ElemType e) //进栈
{
	if (s->top==MaxSize-1)    //栈满的情况，即栈上溢出
		return false;
	s->top++; //栈顶指针增加1
	s->data[s->top]=e; //元素e放在栈顶指针处
	return true;
}

bool Pop(SqStack *&s,ElemType &e) //出栈
{
	if (s->top==-1)		//栈为空的情况，即栈下溢出
		return false;
	e=s->data[s->top]; //取栈顶元素
	s->top--; //栈顶指针减1
	return true;
}

bool GetTop(SqStack *s,ElemType &e) //取栈顶元素
{
	if (s->top==-1) 		//栈为空的情况，即栈下溢出
		return false;
	e=s->data[s->top]; //取栈顶元素
	return true;
}
```

#### 2.链栈

```c
#include <stdio.h>
#include <malloc.h>

typedef char ElemType;

typedef struct linknode
{	
	ElemType data;				//数据域
	struct linknode *next;		//指针域
} LinkStNode;					//链栈结点类型

void InitStack(LinkStNode *&s) //初始化栈
{
	s=(LinkStNode *)malloc(sizeof(LinkStNode));
	s->next=NULL;
}

void DestroyStack(LinkStNode *&s) //销毁栈
{
	LinkStNode *pre=s,*p=s->next; //pre指向头结点，p指向首结点
	while (p!=NULL) //循环到p为空
	{	
		free(pre); //释放pre结点
		pre=p; //pre p同步后移
		p=p->next;
	}
	free(pre);	//pre指向尾结点,释放其空间
}

bool StackEmpty(LinkStNode *s) //判断栈是否为空
{
	return(s->next==NULL);
}

void Push(LinkStNode *&s,ElemType e) //进栈
{	LinkStNode *p;
	p=(LinkStNode *)malloc(sizeof(LinkStNode)); //新建元素e对应的结点p
	p->data=e;				//存放元素e
	p->next=s->next;		//插入p结点作为首结点
	s->next=p;
}

bool Pop(LinkStNode *&s,ElemType &e) //出栈
{	LinkStNode *p;
	if (s->next==NULL)		//栈空的情况
		return false;
	p=s->next;				//p指向首结点
	e=p->data;              //提取首结点
	s->next=p->next;		//删除首结点，建立新链
	free(p);				//释放被删结点的存储空间
	return true;
}

bool GetTop(LinkStNode *s,ElemType &e) //取栈顶元素
{	if (s->next==NULL)		//栈空的情况
		return false;
	e=s->next->data;        //提取首结点值
	return true;
}
```

#### 3.栈的应用-求解简单表达式 \*

```c
//求简单表达式的值
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
//---------------------------------------------------------
//--运算符栈基本运算---------------------------------------
//---------------------------------------------------------
typedef struct 
{	char data[MaxSize];			//存放运算符
	int top;					//栈顶指针
} SqStack;
void InitStack(SqStack *&s)		//初始化栈
{	s=(SqStack *)malloc(sizeof(SqStack));
	s->top=-1;
}
void DestroyStack(SqStack *&s)	//销毁栈
{
	free(s);
}
bool StackEmpty(SqStack *s)		//判断栈是否为空
{
	return(s->top==-1);
}
bool Push(SqStack *&s,char e)	//进栈元素e
{	if (s->top==MaxSize-1)
		return false;
	s->top++;
	s->data[s->top]=e;
	return true;
}
bool Pop(SqStack *&s,char &e)	//出栈元素e
{	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	s->top--;
	return true;
}
bool GetTop(SqStack *s,char &e)	//取栈顶元素e
{	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	return true;
}
//---------------------------------------------------------

void trans(char *exp,char postexp[])	//将算术表达式exp转换成后缀表达式postexp
{
	char e;
	SqStack *Optr;						//定义运算符栈
	InitStack(Optr);					//初始化运算符栈
	int i=0;							//i作为postexp的下标
	while (*exp!='\0')					//exp表达式未扫描完时循环
	{	switch(*exp)
		{
		case '(':						//判定为左括号
			Push(Optr,'(');				//左括号进栈
			exp++;						//继续扫描其他字符
			break;
		case ')':						//判定为右括号
			Pop(Optr,e);				//出栈元素e
			while (e!='(')				//不为'('时循环
			{
				postexp[i++]=e;			//将e存放到postexp中
				Pop(Optr,e);			//继续出栈元素e
			}
			exp++;						//继续扫描其他字符
			break;
		case '+':						//判定为加或减号
		case '-':
			while (!StackEmpty(Optr))	//栈不空循环
			{
				GetTop(Optr,e);			//取栈顶元素e
				if (e!='(')				//e不是'('
				{
					postexp[i++]=e;		//将e存放到postexp中
					Pop(Optr,e);		//出栈元素e
				}
				else					//e是'(时退出循环
					break;
			}
			Push(Optr,*exp);			//将'+'或'-'进栈
			exp++;						//继续扫描其他字符
			break;
		case '*':						//判定为'*'或'/'号
		case '/':
			while (!StackEmpty(Optr))	//栈不空循环
			{
				GetTop(Optr,e);			//取栈顶元素e
				if (e=='*' || e=='/')	//将栈顶'*'或'/'运算符出栈并存放到postexp中
				{
					postexp[i++]=e;		//将e存放到postexp中
					Pop(Optr,e);		//出栈元素e
				}
				else					//e为非'*'或'/'运算符时退出循环
					break;
			}
			Push(Optr,*exp);			//将'*'或'/'进栈
			exp++;						//继续扫描其他字符
			break;
		default:				//处理数字字符
			while (*exp>='0' && *exp<='9') //判定为数字
			{	postexp[i++]=*exp;
				exp++;
			}
			postexp[i++]='#';	//用#标识一个数值串结束
		}
	}
	while (!StackEmpty(Optr))	//此时exp扫描完毕,栈不空时循环
	{
		Pop(Optr,e);			//出栈元素e
		postexp[i++]=e;			//将e存放到postexp中
	}
	postexp[i]='\0';			//给postexp表达式添加结束标识
	DestroyStack(Optr);			//销毁栈		
}
//---------------------------------------------------------
//--操作数栈基本运算---------------------------------------
//---------------------------------------------------------
typedef struct 
{	double data[MaxSize];			//存放数值
	int top;						//栈顶指针
} SqStack1;
void InitStack1(SqStack1 *&s)		//初始化栈
{	s=(SqStack1 *)malloc(sizeof(SqStack1));
	s->top=-1;
}
void DestroyStack1(SqStack1 *&s)	//销毁栈
{
	free(s);
}
bool StackEmpty1(SqStack1 *s)		//判断栈是否为空
{
	return(s->top==-1);
}
bool Push1(SqStack1 *&s,double e)	//进栈元素e
{	if (s->top==MaxSize-1)
		return false;
	s->top++;
	s->data[s->top]=e;
	return true;
}
bool Pop1(SqStack1 *&s,double &e)	//出栈元素e
{	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	s->top--;
	return true;
}
bool GetTop1(SqStack1 *s,double &e)	//取栈顶元素e
{	if (s->top==-1)	
		return false;
	e=s->data[s->top];
	return true;
}
//---------------------------------------------------------

double compvalue(char *postexp)	//计算后缀表达式的值
{
	double d,a,b,c,e;
	SqStack1 *Opnd;				//定义操作数栈
	InitStack1(Opnd);			//初始化操作数栈
	while (*postexp!='\0')		//postexp字符串未扫描完时循环
	{	
		switch (*postexp)
		{
		case '+':				//判定为'+'号
			Pop1(Opnd,a);		//出栈元素a
			Pop1(Opnd,b);		//出栈元素b
			c=b+a;				//计算c
			Push1(Opnd,c);		//将计算结果c进栈
			break;
		case '-':				//判定为'-'号
			Pop1(Opnd,a);		//出栈元素a
			Pop1(Opnd,b);		//出栈元素b
			c=b-a;				//计算c
			Push1(Opnd,c);		//将计算结果c进栈
			break;
		case '*':				//判定为'*'号
			Pop1(Opnd,a);		//出栈元素a
			Pop1(Opnd,b);		//出栈元素b
			c=b*a;				//计算c
			Push1(Opnd,c);		//将计算结果c进栈
			break;
		case '/':				//判定为'/'号
			Pop1(Opnd,a);		//出栈元素a
			Pop1(Opnd,b);		//出栈元素b
			if (a!=0)
			{
				c=b/a;			//计算c
				Push1(Opnd,c);	//将计算结果c进栈
				break;
			}
			else
		    {	
				printf("\n\t除零错误!\n");
				exit(0);		//异常退出
			}
			break;
		default:				//处理数字字符
			d=0;				//将连续的数字字符转换成对应的数值存放到d中
			while (*postexp>='0' && *postexp<='9')   //判定为数字字符
			{	
				d=10*d+*postexp-'0';  
				postexp++;
			}
			Push1(Opnd,d);		//将数值d进栈

			break;
		}
		postexp++;				//继续处理其他字符
	}
	GetTop1(Opnd,e);			//取栈顶元素e
	DestroyStack1(Opnd);		//销毁栈		
	return e;					//返回e
}
int main()
{
	char exp[]="(56-20)/(4+2)";
	char postexp[MaxSize];
	trans(exp,postexp);
	printf("中缀表达式:%s\n",exp);
	printf("后缀表达式:%s\n",postexp);
	printf("表达式的值:%g\n",compvalue(postexp));
	return 1;
}
```

### 三、队列

#### 1.顺序队列

```c
//非环形顺序队列
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100

typedef char ElemType;

typedef struct 
{	
	ElemType data[MaxSize];
	int front,rear;						//队头和队尾指针
} SqQueue;

void InitQueue(SqQueue *&q)
{	q=(SqQueue *)malloc (sizeof(SqQueue));
	q->front=q->rear=-1;
}

void DestroyQueue(SqQueue *&q)			//销毁队列
{
	free(q);
}

bool QueueEmpty(SqQueue *q)				//判断队列是否为空
{
	return(q->front==q->rear);
}

bool enQueue(SqQueue *&q,ElemType e)	//进队
{	if (q->rear==MaxSize-1)				//队满上溢出
		return false;					//返回假
	q->rear++;							//队尾增1
	q->data[q->rear]=e;					//rear位置插入元素e
	return true;						//返回真
}

bool deQueue(SqQueue *&q,ElemType &e)	//出队
{	if (q->front==q->rear)				//队空下溢出
		return false;
	q->front++;
	e=q->data[q->front];
	return true;
}
```

```c
//环形顺序队列(循环队列)

#include <stdio.h>
#include <malloc.h>
#define MaxSize 100

typedef char ElemType;

typedef struct 
{	
	ElemType data[MaxSize]; //存放队中元素
	int front,rear;		//队首和队尾指针
} SqQueue; //顺序队类型

void InitQueue(SqQueue *&q) //初始化队列
{	q=(SqQueue *)malloc (sizeof(SqQueue));
	q->front=q->rear=0;
}

void DestroyQueue(SqQueue *&q) //销毁队列
{
	free(q);
}

bool QueueEmpty(SqQueue *q) //判断队列是否为空
{
	return(q->front==q->rear);
}

bool enQueue(SqQueue *&q,ElemType e) //环形队列进队列
{	if ((q->rear+1)%MaxSize==q->front)	//队满真溢出
		return false;
	q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=e;
	return true;
}

bool deQueue(SqQueue *&q,ElemType &e) //环形队列出队列
{	if (q->front==q->rear)		//队空下溢出
		return false;
	q->front=(q->front+1)%MaxSize;
	e=q->data[q->front];
	return true;
}
```

#### 2.链队

```c
#include <stdio.h>
#include <malloc.h>

typedef char ElemType;

typedef struct DataNode
{	
	ElemType data; //存放元素
	struct DataNode *next; //下一个结点指针
} DataNode;				//链队数据结点类型

typedef struct
{	
	DataNode *front; //指向队首结点
	DataNode *rear; //指向队尾结点
} LinkQuNode;			//链队结点的类型

void InitQueue(LinkQuNode *&q) //初始化队列
{	
	q=(LinkQuNode *)malloc(sizeof(LinkQuNode));
	q->front=q->rear=NULL;
}

void DestroyQueue(LinkQuNode *&q) //销毁队列
{
	DataNode *pre=q->front,*p;//pre指向队首结点
	if (pre!=NULL)			
	{	p=pre->next; //p指向结点pre的后继节点
		while (p!=NULL) //p不空时循环
		{	free(pre); //释放pre结点
			pre=p;p=pre->next; //pre 和 p 同步后移
		}
	}
	free(pre); //释放最后一个数据节点
	free(q); //释放链队结点占用空间
}

bool QueueEmpty(LinkQuNode *q) //判断队列是否为空
{
	return(q->rear==NULL);
}

void enQueue(LinkQuNode *&q,ElemType e)
{	DataNode *p;
	p=(DataNode *)malloc(sizeof(DataNode)); //创建新结点
	p->data=e;
	p->next=NULL;
	if (q->rear==NULL)		//若链队为空,则新结点是队首结点又是队尾结点
		q->front=q->rear=p;
	else                    //若队列不空
	{	q->rear->next=p;	//将p结点链到队尾,并将rear指向它
		q->rear=p;
	}
}

bool deQueue(LinkQuNode *&q,ElemType &e) //出队列
{	DataNode *t;
	if (q->rear==NULL)		//队列为空
		return false;
	t=q->front;				//t指向首结点
	if (q->front==q->rear)  //队列中只有一个数据结点时
		q->front=q->rear=NULL;
	else					//队列中有多个数据结点时
		q->front=q->front->next;
	e=t->data;
	free(t);
	return true;
}
```

### 四、串

#### 1.顺序串

```c
#include <stdio.h>
#define MaxSize 100

typedef struct
{	
	char data[MaxSize];
	int length;			//串长
} SqString;

void StrAssign(SqString &s,char cstr[])	//字符串常量赋给串s
{
	int i;
	for (i=0;cstr[i]!='\0';i++)
		s.data[i]=cstr[i];
	s.length=i;
}

void DestroyStr(SqString &s)
{  }

void StrCopy(SqString &s,SqString t)	//串复制
{
	int i;
	for (i=0;i<t.length;i++)
		s.data[i]=t.data[i];
	s.length=t.length;
}

bool StrEqual(SqString s,SqString t)	//判串相等
{
	bool same=true;
	int i;
	if (s.length!=t.length)				//长度不相等时返回0
		same=false;
	else 
		for (i=0;i<s.length;i++)
			if (s.data[i]!=t.data[i])	//有一个对应字符不相同时返回0
			{	same=false;
				break;
			}
	return same;
}

int StrLength(SqString s)	//求串长
{
	return s.length;
}

SqString Concat(SqString s,SqString t)	//串连接
{
	SqString str;
	int i;
	str.length=s.length+t.length;
	for (i=0;i<s.length;i++)	//将s.data[0..s.length-1]复制到str
		str.data[i]=s.data[i];
	for (i=0;i<t.length;i++)	//将t.data[0..t.length-1]复制到str
		str.data[s.length+i]=t.data[i];
	return str;
}

SqString SubStr(SqString s,int i,int j)	//求子串
{
	SqString str;
	int k;
	str.length=0;
	if (i<=0 || i>s.length || j<0 || i+j-1>s.length)
		return str;					//参数不正确时返回空串
	for (k=i-1;k<i+j-1;k++)  		//将s.data[i..i+j]复制到str
		str.data[k-i+1]=s.data[k];
	str.length=j;
	return str;
} 

SqString InsStr(SqString s1,int i,SqString s2)	//插入串
{
	int j;
	SqString str;
	str.length=0;
	if (i<=0 || i>s1.length+1)  //参数不正确时返回空串
		return str;
	for (j=0;j<i-1;j++)      		//将s1.data[0..i-2]复制到str
		str.data[j]=s1.data[j];
	for (j=0;j<s2.length;j++)		//将s2.data[0..s2.length-1]复制到str
		str.data[i+j-1]=s2.data[j];
	for (j=i-1;j<s1.length;j++)		//将s1.data[i-1..s1.length-1]复制到str
		str.data[s2.length+j]=s1.data[j];
	str.length=s1.length+s2.length;
	return str;
}

SqString DelStr(SqString s,int i,int j)		//串删去
{
	int k;
	SqString str;
	str.length=0;
	if (i<=0 || i>s.length || i+j>s.length+1) //参数不正确时返回空串
		return str;
	for (k=0;k<i-1;k++)       		//将s.data[0..i-2]复制到str
		str.data[k]=s.data[k];
	for (k=i+j-1;k<s.length;k++)	//将s.data[i+j-1..s.length-1]复制到str
		str.data[k-j]=s.data[k];
	str.length=s.length-j;
	return str;
}

SqString RepStr(SqString s,int i,int j,SqString t)	//子串替换
{
	int k;
	SqString str;
	str.length=0;
	if (i<=0 || i>s.length || i+j-1>s.length) //参数不正确时返回空串
		return str;
	for (k=0;k<i-1;k++)				//将s.data[0..i-2]复制到str
		str.data[k]=s.data[k];
	for (k=0;k<t.length;k++)   		//将t.data[0..t.length-1]复制到str
		str.data[i+k-1]=t.data[k];
	for (k=i+j-1;k<s.length;k++)	//将s.data[i+j-1..s.length-1]复制到str
		str.data[t.length+k-j]=s.data[k];
	str.length=s.length-j+t.length;
	return str;
}

void DispStr(SqString s)	//输出串s
{
	int i;
	if (s.length>0)
	{	for (i=0;i<s.length;i++)
			printf("%c",s.data[i]);
		printf("\n");
	}
}
```
#### 2.链串

```c
#include <stdio.h>
#include <malloc.h>

typedef struct snode 
{	
	char data;
	struct snode *next;
} LinkStrNode;

void StrAssign(LinkStrNode *&s,char cstr[])	//字符串常量cstr赋给串s
{
	int i;
	LinkStrNode *r,*p;
	s=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=s;						//r始终指向尾结点
	for (i=0;cstr[i]!='\0';i++) 
	{	p=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		p->data=cstr[i];
		r->next=p;r=p;
	}
	r->next=NULL;
}

void DestroyStr(LinkStrNode *&s)
{	LinkStrNode *pre=s,*p=s->next;	//pre指向结点p的前驱结点
	while (p!=NULL)					//扫描链串s
	{	free(pre);					//释放pre结点
		pre=p;						//pre、p同步后移一个结点
		p=pre->next;
	}
	free(pre);						//循环结束时,p为NULL,pre指向尾结点,释放它
}

void StrCopy(LinkStrNode *&s,LinkStrNode *t)	//串t复制给串s
{
	LinkStrNode *p=t->next,*q,*r;
	s=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=s;						//r始终指向尾结点
	while (p!=NULL)				//将t的所有结点复制到s
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
}

bool StrEqual(LinkStrNode *s,LinkStrNode *t)	//判串相等
{
	LinkStrNode *p=s->next,*q=t->next;
	while (p!=NULL && q!=NULL && p->data==q->data) 
	{	p=p->next;
		q=q->next;
	}
	if (p==NULL && q==NULL)
		return true;
	else
		return false;
}

int StrLength(LinkStrNode *s)	//求串长
{
	int i=0;
	LinkStrNode *p=s->next;
	while (p!=NULL) 
	{	i++;
		p=p->next;
	}
	return i;
}

LinkStrNode *Concat(LinkStrNode *s,LinkStrNode *t)	//串连接
{
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=str;
	while (p!=NULL)				//将s的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	p=t->next;
	while (p!=NULL)				//将t的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}

LinkStrNode *SubStr(LinkStrNode *s,int i,int j)	//求子串
{
	int k;
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;						//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
		return str;				//参数不正确时返回空串
	for (k=0;k<i-1;k++)
		p=p->next;
	for (k=1;k<=j;k++) 			//将s的第i个结点开始的j个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}

LinkStrNode *InsStr(LinkStrNode *s,int i,LinkStrNode *t)		//串插入
{
	int k;
	LinkStrNode *str,*p=s->next,*p1=t->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;								//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s)+1)		//参数不正确时返回空串
		return str;
	for (k=1;k<i;k++)					//将s的前i个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	while (p1!=NULL)					//将t的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p1->data;
		r->next=q;r=q;
		p1=p1->next;
	}
	while (p!=NULL)						//将结点p及其后的结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}

LinkStrNode *DelStr(LinkStrNode *s,int i,int j)	//串删去
{
	int k;
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;						//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
		return str;				//参数不正确时返回空串
	for (k=0;k<i-1;k++)			//将s的前i-1个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	for (k=0;k<j;k++)				//让p沿next跳j个结点
		p=p->next;
	while (p!=NULL)					//将结点p及其后的结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}

LinkStrNode *RepStr(LinkStrNode *s,int i,int j,LinkStrNode *t)	//串替换
{
	int k;
	LinkStrNode *str,*p=s->next,*p1=t->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;
	r=str;							//r指向新建链表的尾结点
	if (i<=0 || i>StrLength(s) || j<0 || i+j-1>StrLength(s))
		return str;		 			//参数不正确时返回空串
	for (k=0;k<i-1;k++)  			//将s的前i-1个结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;q->next=NULL;
		r->next=q;r=q;
		p=p->next;
	}
	for (k=0;k<j;k++)				//让p沿next跳j个结点
		p=p->next;
	while (p1!=NULL)				//将t的所有结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p1->data;q->next=NULL;
		r->next=q;r=q;
		p1=p1->next;
	}
	while (p!=NULL)					//将结点p及其后的结点复制到str
	{	q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;q->next=NULL;
		r->next=q;r=q;
		p=p->next;
	}
	r->next=NULL;
	return str;
}

void DispStr(LinkStrNode *s)	//输出串
{
	LinkStrNode *p=s->next;
	while (p!=NULL)
	{	printf("%c",p->data);
		p=p->next;
	}
	printf("\n");
}
```

#### 3.串的模式匹配

```c
//BF（Brute-Force）算法/朴素模式匹配算法
int index(SqString s,SqString t)
{
	int i=0,j=0;
	while (i<s.length && j<t.length) 
	{
		if (s.data[i]==t.data[j])  	//继续匹配下一个字符
		{	
			i++;				//主串和子串依次匹配下一个字符
			j++;  
		}
		else          			//主串、子串指针回溯重新开始下一次匹配
		{	
			i=i-j+1;			//主串从下一个位置开始匹配
			j=0; 				//子串从头开始匹配
		}
	}
	if (j>=t.length)   
		return(i-t.length);  		//返回匹配的第一个字符的下标
	else  
		return(-1);        		//模式匹配不成功
}
```

```c
//KMP算法求next数组
void GetNext(SqString t,int next[])	
{
	int j,k;
	j=0;k=-1;next[0]=-1;
	while (j<t.length-1) 
	{	
		if (k==-1 || t.data[j]==t.data[k]) 	//k为-1或比较的字符相等时
		{	
			j++;k++;
			next[j]=k;
			//printf("(1) j=%d,k=%d,next[%d]=%d\n",j,k,j,k);
       	}
       	else
		{
			k=next[k];
			//printf("(2) k=%d\n",k);
		}
	}
}

//KMP算法
int KMPIndex(SqString s,SqString t) 
{
	int next[MaxSize],i=0,j=0;
	GetNext(t,next);
	while (i<s.length && j<t.length) 
	{
		if (j==-1 || s.data[i]==t.data[j]) 
		{
			i++;j++;  			//i,j各增1
		}
		else j=next[j]; 		//i不变,j后退
    }
    if (j>=t.length)
		return(i-t.length);  	//返回匹配模式串的首字符下标
    else  
		return(-1);        		//返回不匹配标志
}
```

```c
//王道版KMP算法求next数组
void GetNext(SqString t,int next[])	
{
	int j=0,k=0;
	next[1]=0;
	while (j<t.length) 
	{	
		if (k==0 || t.data[j]==t.data[k]) 	//k为0或比较的字符相等时
		{	
			j++;k++;
			next[j]=k;
			//printf("(1) j=%d,k=%d,next[%d]=%d\n",j,k,j,k);
       	}
       	else
		{
			k=next[k];
			//printf("(2) k=%d\n",k);
		}
	}
}

//王道版KMP算法
int KMPIndex(SqString s,SqString t，int next[])    
{
	int i=1,j=1;
	while (i<=s.length && j<=t.length) 
	{
		if (j==0 || s.data[i]==t.data[j]) 
		{	
			i++;j++;	
		}
		else j=next[j];
	}
	if (j>t.length)  
		return(i-t.length);
	else
		return 0;
}
```

 ### 五、树

 #### 1. 二叉树

```c
#include <stdio.h>
#include <malloc.h>

#define MaxSize 100
typedef char ElemType;

typedef struct node //二叉链中结点类型BTNode
{	
	ElemType data;			//数据元素
	struct node *lchild;	//指向左孩子节点
	struct node *rchild;	//指向右孩子节点
} BTNode;

//理解算法原理即可，不需掌握
void CreateBTree(BTNode * &b,char *str)	//创建二叉树：A(B(D,E),C(,F))
{
	BTNode *St[MaxSize],*p=NULL;
	int top=-1,k,j=0;  
	char ch;
	b=NULL;				//建立的二叉树初始时为空
	ch=str[j];
	while (ch!='\0')  	//str未扫描完时循环
	{
   	   	switch(ch) 
		{
		case '(':top++;St[top]=p;k=1; break;		//为左孩子节点
		case ')':top--;break;
		case ',':k=2; break;                      		//为孩子节点右节点
		default:p=(BTNode *)malloc(sizeof(BTNode));
				p->data=ch;p->lchild=p->rchild=NULL;
				if (b==NULL)                    	 	//*p为二叉树的根节点
					b=p;
				else  								//已建立二叉树根节点
				{	
					switch(k) 
					{
					case 1:St[top]->lchild=p;break;
					case 2:St[top]->rchild=p;break;
					}
				}
		}
		j++;
		ch=str[j];
	}
}

void DestroyBTree(BTNode *&b) //销毁二叉树
{	if (b!=NULL)  //若b==null
	{	DestroyBTree(b->lchild); //递归调用
		DestroyBTree(b->rchild);
		free(b);
	}
}

BTNode *FindNode(BTNode *b,ElemType x) //查找结点
{
	BTNode *p;
	if (b==NULL)  //若b==null
		return NULL;
	else if (b->data==x) //找到b了
		return b;
	else  
	{
		p=FindNode(b->lchild,x);  //p=f(b->lchild,x)且p!=null
		if (p!=NULL) 
			return p;
		else //p==null,f(b->rchild)
			return FindNode(b->rchild,x);
	}
}

BTNode *LchildNode(BTNode *p)  //返回结点p的左孩子指针
{
    return p->lchild;
}

BTNode *RchildNode(BTNode *p)  //返回结点p的右孩子指针
{
    return p->rchild;
}

int BTHeight(BTNode *b)   //求树高
{
   	int lchildh,rchildh;
   	if (b==NULL) return(0); 				//空树的高度为0
   	else  
	{
		lchildh=BTHeight(b->lchild);	//求左子树的高度为lchildh
		rchildh=BTHeight(b->rchild);	//求右子树的高度为rchildh
		return (lchildh>rchildh)? (lchildh+1):(rchildh+1);
   	}
}

void DispBTree(BTNode *b) //A(B(D,E),C(,F))
{
	if (b!=NULL)
	{	printf("%c",b->data);
		if (b->lchild!=NULL || b->rchild!=NULL)
		{	printf("(");						//有孩子节点时才输出(
			DispBTree(b->lchild);				//递归处理左子树
			if (b->rchild!=NULL) printf(",");	//有右孩子节点时才输出,
			DispBTree(b->rchild);				//递归处理右子树
			printf(")");						//有孩子节点时才输出)
		}
	}
}
```

#### 2.树的遍历

```c
//树的队列层次遍历算法：A(B(D(,G)),C(E,F))
#define MaxSize 100

void LevelOrder(BTNode *b)
{
	BTNode *p;
	SqQueue *qu;
	InitQueue(qu);					//初始化队列
	enQueue(qu,b);					//根结点指针进入队列
	while (!QueueEmpty(qu))			//队不为空循环
	{
		deQueue(qu,p);				//出队节点p
		printf("%c ",p->data);		//访问节点p
		if (p->lchild!=NULL)		//有左孩子时将其进队
			enQueue(qu,p->lchild);
		if (p->rchild!=NULL)		//有右孩子时将其进队
			enQueue(qu,p->rchild);
	} 
}
```

```c
//先序、中序和后序递归遍历算法：A(B(D(,G)),C(E,F))
void PreOrder(BTNode *b)  		//先序遍历的递归算法
{
	if (b!=NULL)  
	{
		printf("%c ",b->data);	//访问根结点
		PreOrder(b->lchild);	//先序遍历左子树
		PreOrder(b->rchild);	//先序遍历右子树
	}
}

void InOrder(BTNode *b)   		//中序遍历的递归算法
{
	if (b!=NULL)  
	{	
		InOrder(b->lchild);		//中序遍历左子树
		printf("%c ",b->data);	//访问根结点
		InOrder(b->rchild);		//中序遍历右子树
	}
}

void PostOrder(BTNode *b) 		//后序遍历的递归算法
{
	if (b!=NULL)  
	{
		PostOrder(b->lchild);	//后序遍历左子树
		PostOrder(b->rchild);	//后序遍历右子树
		printf("%c ",b->data);	//访问根结点
	}
}
```

```c
//先序、中序和后序非递归遍历算法
void PreOrder(BTNode *b)			//先序非递归遍历算法
{
	BTNode *p;
	SqStack *st;					//定义一个顺序栈指针st
	InitStack(st);					//初始化栈st
	p=b;
	while (!StackEmpty(st) || p!=NULL)
	{
		while (p!=NULL)				//访问节点p及其所有左下节点并进栈
		{
			printf("%c ",p->data);	//访问节点p
			Push(st,p);				//节点p进栈
			p=p->lchild;			//移动到左孩子
		}
		if (!StackEmpty(st))		//若栈不空
		{
			Pop(st,p);				//出栈节点p
			p=p->rchild;			//转向处理其右子树
		}
	}
	printf("\n");
	DestroyStack(st);				//销毁栈
}
void InOrder(BTNode *b)				//中序非递归遍历算法
{
	BTNode *p;
	SqStack *st;						//定义一个顺序栈指针st
	InitStack(st);						//初始化栈st
	if (b!=NULL)
	{
		p=b;
		while (!StackEmpty(st) || p!=NULL)
		{
			while (p!=NULL)				//扫描节点p的所有左下节点并进栈
			{
				Push(st,p);				//节点p进栈
				p=p->lchild;			//移动到左孩子
			}
			if (!StackEmpty(st))		//若栈不空
			{
				Pop(st,p);				//出栈节点p
				printf("%c ",p->data);	//访问节点p
				p=p->rchild;			//转向处理其右子树
			}
		}
		printf("\n");
	}
	DestroyStack(st);				//销毁栈
}

void PostOrder(BTNode *b)				//后序非递归遍历算法
{
	BTNode *p,*r;
	bool flag;
	SqStack *st;						//定义一个顺序栈指针st
	InitStack(st);						//初始化栈st
	p=b;
	do
	{
		while (p!=NULL)					//扫描节点p的所有左下节点并进栈
		{
			Push(st,p);					//节点p进栈
			p=p->lchild;				//移动到左孩子
		}
		r=NULL;							//r指向刚刚访问的节点，初始时为空
		flag=true;						//flag为真表示正在处理栈顶节点
		while (!StackEmpty(st) && flag)
		{
			GetTop(st,p);				//取出当前的栈顶节点p
			if (p->rchild==r)			//若节点p的右孩子为空或者为刚刚访问过的节点	
			{
				printf("%c ",p->data);	//访问节点p
				Pop(st,p);
				r=p;					//r指向刚访问过的节点
			}
			else
			{	
				p=p->rchild;			//转向处理其右子树
				flag=false;				//表示当前不是处理栈顶节点
			}
		}
	} while (!StackEmpty(st));			//栈不空循环
	printf("\n");
	DestroyStack(st);				//销毁栈
}
```

#### 3.线索二叉树

```c
typedef char ElemType;
typedef struct node //线索二叉树结点类型声明
{
	ElemType data;
	int ltag,rtag;      //增加的线索标记
	struct node *lchild; //左孩子或线索指针
	struct node *rchild; //右孩子或线索指针
} ThreadNode;

//中序线索二叉树的算法
void InThread(TBTNode *&p,ThreadNode *&pre)
{
	if (p!=NULL)	
	{	
		InThread(p->lchild);    		//左子树线索化
		if (p->lchild==NULL)		//前驱线索
		{
			p->lchild=pre;        	//建立当前节点的前驱线索
			p->ltag=1;
		}
		else p->ltag=0;
		if (pre->rchild==NULL)		//后继线索
		{	
			pre->rchild=p;     		//建立前驱节点的后继线索
		   	pre->rtag=1;
		}
		else pre->rtag=0;
	    pre=p;
	   	InThread(p->rchild);  		//右子树线索化
	}
}
```

### 六、图

```c
Adjacent(G,x,y):判断图G是否存在边<x,y>或者(x,y)。
Neighbor(G,x):列出图G中与结点x邻接的边。
InsertVertex(G,x):在图G中插入顶点x。
DeleteVertex(G,x):从图G中删除顶点x。
AddEdge(G,x,y):若无向边(x,y)或有向边<x,y>不存在，则往图中添加该边。
RemoveEdge(G,x,y):若无向边(x,y)或有向边<x,y>不存在，则从图G中删除该边。
FirstNeighbor(G,x,y):从图G中顶点x的第一个邻接点，若有则返回顶点号。若x没有邻接边或图中不存在x，则返回-1。
NextNeighbor(G,x,y):假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号，若y是x的最后一个邻接点，则返回-1。
Get_edge_value(G,x,y):获取图G中边(x,y)或<x,y>对应的权值。
Set_edge_value(G,x,y,v):设置图G中边(x,y)或<x,y>对应的权值为v。
```

#### 1.图的两种存储结构

```c
#define INF 32767				//定义∞
#define	MAXV 100				//最大顶点个数
typedef char InfoType;

//以下定义邻接矩阵类型
typedef struct
{	int no;						//顶点编号
	InfoType info;				//顶点其他信息
} VertexType;					//顶点类型
typedef struct
{	int edges[MAXV][MAXV];		//邻接矩阵数组
	int n,e;					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
} MatGraph;						//完整的图邻接矩阵类型

//以下定义邻接表类型
typedef struct ANode
{	int adjvex;					//该边的邻接点编号
	struct ANode *nextarc;		//指向下一条边的指针
	int weight;					//该边的相关信息，如权值（用整型表示）
} ArcNode;						//边结点类型
typedef struct Vnode
{	InfoType info;				//顶点其他信息
	int count;					//存放顶点入度,仅仅用于拓扑排序
	ArcNode *firstarc;			//指向第一条边
} VNode;						//邻接表头结点类型
typedef struct 
{	VNode adjlist[MAXV];		//邻接表头结点数组
	int n,e;					//图中顶点数n和边数e
} AdjGraph;						//完整的图邻接表类型
```

#### 2.图的遍历

```c
typedef int ElemType;
void BFS(AdjGraph *G,int v)  //广度优先遍历算法
{
	int w,i;
	ArcNode *p;
	SqQueue *qu;							//定义环形队列指针
	InitQueue(qu);							//初始化队列
	int visited[MAXV];            			//定义顶点访问标志数组
	for (i=0;i<G->n;i++) visited[i]=0;		//访问标志数组初始化
	printf("%2d",v); 						//输出被访问顶点的编号
	visited[v]=1;              				//置已访问标记
	enQueue(qu,v);
	while (!QueueEmpty(qu))       			//队不空循环
	{	
		deQueue(qu,w);						//出队一个顶点w
		p=G->adjlist[w].firstarc; 			//指向w的第一个邻接点
		while (p!=NULL)						//查找w的所有邻接点
		{	
			if (visited[p->adjvex]==0) 		//若当前邻接点未被访问
			{
				printf("%2d",p->adjvex);  	//访问该邻接点
				visited[p->adjvex]=1;		//置已访问标记
				enQueue(qu,p->adjvex);		//该顶点进队
           	}
           	p=p->nextarc;              		//找下一个邻接点
		}
	}
	printf("\n");
}
```

```c
int visited[MAXV]={0};
void DFS(AdjGraph *G,int v)  //深度优先遍历算法
{
	ArcNode *p;
	visited[v]=1;                   //置已访问标记
	printf("%d  ",v); 				//输出被访问顶点的编号
	p=G->adjlist[v].firstarc;      	//p指向顶点v的第一条弧的弧头结点
	while (p!=NULL) 
	{
		if (visited[p->adjvex]==0)	//若p->adjvex顶点未访问,递归访问它
			DFS(G,p->adjvex);    
		p=p->nextarc;              	//p指向顶点v的下一条弧的弧头结点
	}
}
```

#### 3.最小生成树问题

```c
void Prim(MatGraph g,int v)  //Prim算法
{
	int lowcost[MAXV];			//顶点i是否在U中
	int min;
	int closest[MAXV],i,j,k;
	for (i=0;i<g.n;i++)          //给lowcost[]和closest[]置初值
	{	
		lowcost[i]=g.edges[v][i];
		closest[i]=v;
	}
	for (i=1;i<g.n;i++)          //找出n-1个顶点
	{
		min=INF;
		for (j=0;j<g.n;j++)       //在(V-U)中找出离U最近的顶点k
			if (lowcost[j]!=0 && lowcost[j]<min) 
			{
				min=lowcost[j];
				k=j;			//k记录最近顶点的编号
			}
		printf(" 边(%d,%d)权为:%d\n",closest[k],k,min);
		lowcost[k]=0;         	//标记k已经加入U
		for (j=0;j<g.n;j++)   	//修改数组lowcost和closest
			if (g.edges[k][j]!=0 && g.edges[k][j]<lowcost[j]) 
			{
				lowcost[j]=g.edges[k][j];
				closest[j]=k; 
			}
	}
}
```

```c
//Kruskal算法
#include "graph.cpp"
#define MaxSize 100
typedef struct 
{	
	int u;			//边的起始顶点
    int v;			//边的终止顶点
    int w;			//边的权值
} Edge;

void Kruskal(MatGraph g)
{
	int i,j,u1,v1,sn1,sn2,k;
	int vset[MAXV];
	Edge E[MaxSize];				//存放所有边
	k=0;							//E数组的下标从0开始计
	for (i=0;i<g.n;i++)				//由g产生的边集E
		for (j=0;j<=i;j++)
		{
			if (g.edges[i][j]!=0 && g.edges[i][j]!=INF)
			{
				E[k].u=i;E[k].v=j;E[k].w=g.edges[i][j];
				k++;
			}
		}
	InsertSort(E,g.e);				//采用直接插入排序对E数组按权值递增排序
	for (i=0;i<g.n;i++) 			//初始化辅助数组
		vset[i]=i;
	k=1;                 			//k表示当前构造生成树的第几条边,初值为1
	j=0;                 			//E中边的下标,初值为0
	while (k<g.n)       			//生成的边数小于n时循环
	{	
		u1=E[j].u;v1=E[j].v;        //取一条边的头尾顶点
		sn1=vset[u1];
		sn2=vset[v1]; 				//分别得到两个顶点所属的集合编号
		if (sn1!=sn2)     	  		//两顶点属于不同的集合,该边是最小生成树的一条边
		{	
			printf("  (%d,%d):%d\n",u1,v1,E[j].w);
			k++;                    //生成边数增1
			for (i=0;i<g.n;i++)     //两个集合统一编号
				if (vset[i]==sn2)  	//集合编号为sn2的改为sn1
				    vset[i]=sn1;
		}
		j++;   						//扫描下一条边
	}
}
```

#### 4.最短路径问题

```c
void Dijkstra(MatGraph g,int v)	  //Dijkstra算法
{	int dist[MAXV],path[MAXV];
	int S[MAXV];				//S[i]=1表示顶点i在S中, S[i]=0表示顶点i在U中
	int Mindis,i,j,u;
	for (i=0;i<g.n;i++)
	{	dist[i]=g.edges[v][i];	//距离初始化
		S[i]=0;					//S[]置空
		if (g.edges[v][i]<INF)	//路径初始化
			path[i]=v;			//顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i]=-1;			//顶点v到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[v]=1;path[v]=0;			//源点编号v放入S中
	for (i=0;i<g.n-1;i++)		//循环直到所有顶点的最短路径都求出
	{	Mindis=INF;				//Mindis置最大长度初值
		for (j=0;j<g.n;j++)		//选取不在S中（即U中）且具有最小最短路径长度的顶点u
			if (S[j]==0 && dist[j]<Mindis) 
			{	u=j;
				Mindis=dist[j];
			}
		S[u]=1;					//顶点u加入S中
		for (j=0;j<g.n;j++)		//修改不在S中（即U中）的顶点的最短路径
			if (S[j]==0)
				if (g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j])
				{	dist[j]=dist[u]+g.edges[u][j];
					path[j]=u;
				}
	}
	Dispath(g,dist,path,S,v);	//输出最短路径
}
```

```c
void Floyd(MatGraph g)							//Floyd算法
{	int A[MAXV][MAXV],path[MAXV][MAXV];
	int i,j,k;
	for (i=0;i<g.n;i++)
		for (j=0;j<g.n;j++) 
		{	A[i][j]=g.edges[i][j];
			if (i!=j && g.edges[i][j]<INF)
				path[i][j]=i;					//顶点i到j有边时
			else
				path[i][j]=-1;				//顶点i到j没有边时
		}
	for (k=0;k<g.n;k++)						//依次考察所有顶点
	{	for (i=0;i<g.n;i++)
			for (j=0;j<g.n;j++)
				if (A[i][j]>A[i][k]+A[k][j])
				{	A[i][j]=A[i][k]+A[k][j];	//修改最短路径长度
					path[i][j]=path[k][j];		//修改最短路径
				}
	}
	Dispath(g,A,path);							//输出最短路径
}
```

#### 5.拓朴排序

```c
//拓扑排序算法
#include "graph.cpp"
void TopSort(AdjGraph *G)			//拓扑排序算法
{	int i,j;
	int St[MAXV],top=-1;			//栈St的指针为top
	ArcNode *p;
	for (i=0;i<G->n;i++)			//入度置初值0
		G->adjlist[i].count=0;
	for (i=0;i<G->n;i++)			//求所有顶点的入度
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	G->adjlist[p->adjvex].count++;
			p=p->nextarc;
		}
	}
	for (i=0;i<G->n;i++)			//将入度为0的顶点进栈
		if (G->adjlist[i].count==0)
		{	top++;
			St[top]=i;
		}
	while (top>-1)					//栈不空循环
	{	i=St[top];top--;			//出栈一个顶点i
		printf("%d ",i);			//输出该顶点
		p=G->adjlist[i].firstarc;	//找第一个邻接点
		while (p!=NULL)				//将顶点i的出边邻接点的入度减1
		{	j=p->adjvex;
			G->adjlist[j].count--;
			if (G->adjlist[j].count==0)//将入度为0的邻接点进栈
			{	top++;
				St[top]=j;
			}
			p=p->nextarc;			//找下一个邻接点
		}
	}
}
```

#### 6.关键路径

```c
typedef struct
{	int ino;			//起点
	int eno;			//终点
} KeyNode;				//关键活动类型

bool KeyPath(AdjGraph *G,int &inode,int &enode,KeyNode keynode[],int &d)
//从图邻接表G中求出从源点inode到汇点enode的关键活动keynode[0..d]
{	int topseq[MAXV];						//topseq用于存放拓扑序列
	int i,w;
	ArcNode *p;
	if (!TopSort(G,topseq))
		return false;						//不能产生拓扑序列时返回false
	inode=topseq[0];						//求出源点
	enode=topseq[G->n-1];					//求出汇点
	int ve[MAXV];							//事件的最早开始时间
	int vl[MAXV];							//事件的最迟开始时间
	for (i=0;i<G->n;i++) ve[i]=0;			//先将所有事件的ve置初值为0
	for (i=0;i<G->n;i++)					//从左向右求所有事件的最早开始时间
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)						//遍历每一条边即活动
		{	w=p->adjvex;
			if (ve[i]+p->weight>ve[w])		//求最大者
				ve[w]=ve[i]+p->weight;
			p=p->nextarc;
		}
	 }
	for (i=0;i<G->n;i++)					//先将所有事件的vl值置为最大值
		vl[i]=ve[enode];
	for (i=G->n-2;i>=0;i--)					//从右向左求所有事件的最迟开始时间
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	w=p->adjvex;
			if (vl[w]-p->weight<vl[i])		//求最小者
				vl[i]=vl[w]-p->weight; 
			p=p->nextarc;
		}
	}
	d=-1;									//d存放keynode中的关键活动下标,置初置为-1
	for (i=0;i<G->n;i++)					//求关键活动
	{	p=G->adjlist[i].firstarc;
		while (p!=NULL)
		{	w=p->adjvex;
			if (ve[i]==vl[w]-p->weight)		//(i→w)是一个关键活动
			{
				d++; keynode[d].ino=i; keynode[d].eno=w;
			}
			p=p->nextarc;
		}
	}
	return true;
}
```

### 七、查找

#### 1.顺序查找

```c
//顺序查找算法

int SeqSearch(RecType R[],int n,KeyType k)
{
    int i=0;
    while (i<n && R[i].key!=k)	//从表头往后找
		i++;
    if (i>=n) 
		return 0;
    else 
		return i+1;
}

int SeqSearch1(RecType R[],int n,KeyType k)
{
	int i=0;
	R[n].key=k;
	while (R[i].key!=k)	//从表头往后找
		i++;
	if (i==n)				//未找到返回0
		return 0;
	else 
		return i+1;			//找到返回逻辑序号i+1
}
```

#### 2.折半查找

```c
//折半查找算法

int BinSearch(RecType R[],int n,KeyType k) //折半查找算法
{	int low=0,high=n-1,mid;
	while (low<=high)			//当前区间存在元素时循环
	{	mid=(low+high)/2;
		if (k==R[mid].key)		//查找成功返回其逻辑序号mid+1
			return mid+1;
		if (k<R[mid].key)		//继续在R[low..mid-1]中查找
			high=mid-1;
		else					//k>R[mid].key
			low=mid+1;			//继续在R[mid+1..high]中查找
	}
	return 0;					//未找到时返回0（查找失败）
}
```

#### 3.分块查找

```c
//分块查找算法
#define MAXI 20			//索引表的最大长度

typedef struct 
{
	KeyType key;	//KeyType为关键字的类型
	int link;		//指向对应块的起始下标
} IdxType;			//索引表元素类型

int IdxSearch(IdxType I[],int b,RecType R[],int n,KeyType k) //分块查找
{	
	int s=(n+b-1)/b;			//s为每块的元素个数，应为n/b的向上取整
	int low=0,high=b-1,mid,i;
	while (low<=high)			//在索引表中进行折半查找，找到的位置为high+1
	{	mid=(low+high)/2;
		if (I[mid].key>=k)
			high=mid-1;
		else 
			low=mid+1;
	}
	//应在索引表的high+1块中，再在主数据表中进行顺序查找
	i=I[high+1].link;
	while (i<=I[high+1].link+s-1 && R[i].key!=k)
		i++;
	if (i<=I[high+1].link+s-1)
		return i+1;			//查找成功，返回该元素的逻辑序号
	else
		return 0;			//查找失败，返回0
}
```

#### 4.二叉排序树

```c
//二叉排序树算法
#include <stdio.h>
#include <malloc.h>

typedef int KeyType;
typedef char InfoType[10];

typedef struct node
{
	KeyType key;              		//关键字项
	InfoType data;             		//其他数据域
	struct node *lchild,*rchild;	//左右孩子指针
} BSTNode;           				//二叉排序树结点类型

bool InsertBST(BSTNode *&bt,KeyType k)	
//在二叉排序树bt中插入一个关键字为k的结点。插入成功返回真，否则返回假
{	if (bt==NULL)						//原树为空，新插入的结点为根结点
	{	bt=(BSTNode *)malloc(sizeof(BSTNode));
		bt->key=k; bt->lchild=bt->rchild=NULL;
		return true;
	}
	else if (k==bt->key) 				//树中存在相同关键字的结点，返回假
		return false;
	else if (k<bt->key) 
		return InsertBST(bt->lchild,k);	//插入到左子树中
	else
		return InsertBST(bt->rchild,k);	//插入到右子树中
}

BSTNode *CreateBST(KeyType A[],int n)		//创建二叉排序树
//返回BST树根结点指针
{	BSTNode *bt=NULL;				//初始时bt为空树
	int i=0;
	while (i<n)
	{	InsertBST(bt,A[i]);			//将关键字A[i]插入二叉排序树bt中
		i++;
	}
	return bt;						//返回建立的二叉排序树的根指针
}

void DispBST(BSTNode *bt)		//输出一棵排序二叉树
{
	if (bt!=NULL)
	{	printf("%d",bt->key);
		if (bt->lchild!=NULL || bt->rchild!=NULL)
		{	printf("(");						//有孩子结点时才输出(
			DispBST(bt->lchild);				//递归处理左子树
			if (bt->rchild!=NULL) printf(",");	//有右孩子结点时才输出,
			DispBST(bt->rchild);				//递归处理右子树
			printf(")");						//有孩子结点时才输出)
		}
	}
}

BSTNode *SearchBST(BSTNode *bt,KeyType k)
{ 
    if (bt==NULL || bt->key==k)      	//递归终结条件
		return bt;
	if (k<bt->key)
       	return SearchBST(bt->lchild,k);  //在左子树中递归查找
    else
     	return SearchBST(bt->rchild,k);  //在右子树中递归查找
}

BSTNode *SearchBST1(BSTNode *bt,KeyType k,BSTNode *f1,BSTNode *&f)	
/*在bt中查找关键字为k的结点,若查找成功,该函数返回该结点的指针,
f返回其双亲结点;否则,该函数返回NULL。
其调用方法如下:
	         SearchBST(bt,x,NULL,f);
这里的第3个参数f1仅作中间参数,用于求f,初始设为NULL*/
{ 
	if (bt==NULL)
	{	
		f=NULL;
		return(NULL);
	}
	else if (k==bt->key) 
	{	
		f=f1;
		return(bt);
	}
	else if (k<bt->key)
       	return SearchBST1(bt->lchild,k,bt,f);  //在左子树中递归查找
    else
     	return SearchBST1(bt->rchild,k,bt,f);  //在右子树中递归查找
}

void Delete1(BSTNode *p,BSTNode *&r)  //当被删p结点有左右子树时的删除过程
{
	BSTNode *q;
	if (r->rchild!=NULL)
		Delete1(p,r->rchild);	//递归找最右下结点r
	else						//找到了最右下结点r
	{	p->key=r->key;			//将*结点的值赋给结点p
		q=r;					
		r=r->lchild;			//直接将其左子树的根结点放在被删结点的位置上
		free(q);				//释放原结点r的空间
	}
}

void Delete(BSTNode *&p)		//从二叉排序树中删除p结点
{
	BSTNode *q;
	if (p->rchild==NULL)		//p结点没有右子树的情况
	{
		q=p;
		p=p->lchild;			//直接将其右子树的根结点放在被删结点的位置上
		free(q);  
	}
	else if (p->lchild==NULL)	//p结点没有左子树的情况
	{
		q=p;
		p=p->rchild;			//将p结点的右子树作为双亲结点的相应子树
		free(q);  
	}
	else Delete1(p,p->lchild);	//p结点既没有左子树又没有右子树的情况
}

int DeleteBST(BSTNode *&bt,KeyType k)	//在bt中删除关键字为k的结点
{
	if (bt==NULL) 
		return 0;				//空树删除失败
	else 
	{	
		if (k<bt->key) 
			return DeleteBST(bt->lchild,k);	//递归在左子树中删除为k的结点
		else if (k>bt->key) 
			return DeleteBST(bt->rchild,k);	//递归在右子树中删除为k的结点
		else 
		{
			Delete(bt);		//调用Delete(bt)函数删除*bt结点
			return 1;
		}
	}
}

void DestroyBST(BSTNode *&bt)		//销毁二叉排序树bt
{
	if (bt!=NULL)
	{
		DestroyBST(bt->lchild);
		DestroyBST(bt->rchild);
		free(bt);
	}
}
```

### 八、排序

#### 1.插入排序

```c
//直接插入排序算法

void InsertSort(RecType R[],int n) //对R[0..n-1]按递增有序进行直接插入排序
{	int i, j; RecType tmp;
	for (i=1;i<n;i++) 
	{
		if (R[i].key<R[i-1].key)	//反序时 
		{	
			tmp=R[i];
			j=i-1; 
			do					//找R[i]的插入位置 
			{
				R[j+1]=R[j];   	//将关键字大于R[i].key的记录后移
				j--;
			}  while  (j>=0 && R[j].key>tmp.key);
			R[j+1]=tmp;      		//在j+1处插入R[i]
		}
		printf("  i=%d: ",i); DispList(R,n);
	}
}
```

```c
//折半插入排序算法

void BinInsertSort(RecType R[],int n)
{	int i, j, low, high, mid;
	RecType tmp;
	for (i=1;i<n;i++) 
	{
		if (R[i].key<R[i-1].key)		//反序时 
		{
			tmp=R[i];		  			//将R[i]保存到tmp中
	     	low=0;  high=i-1;
			while (low<=high)	  		//在R[low..high]中查找插入的位置
			{
				mid=(low+high)/2;		//取中间位置
				if (tmp.key<R[mid].key)
					high=mid-1;			//插入点在左半区
				else 
					low=mid+1;			//插入点在右半区
			}                          	//找位置high
			for (j=i-1;j>=high+1;j--)	//集中进行元素后移
				R[j+1]=R[j];
			R[high+1]=tmp;				//插入tmp 
		}
		printf("  i=%d: ",i);
		DispList(R,n);
	} 
}
```

```c
//Shell排序算法

void ShellSort(RecType R[],int n) //希尔排序算法
{	int i,j,d;
	RecType tmp;
	d=n/2;					//增量置初值
	while (d>0)
	{	for (i=d;i<n;i++) 	//对所有组采用直接插入排序
		{	tmp=R[i];		//对相隔d个位置一组采用直接插入排序
			j=i-d;
			while (j>=0 && tmp.key<R[j].key)
			{	R[j+d]=R[j];
				j=j-d;
			}
			R[j+d]=tmp;
		}
		printf("  d=%d: ",d); DispList(R,n);
		d=d/2;				//减小增量
	}
}
```

#### 2.交换排序

```c
//冒泡排序算法

void BubbleSort(RecType R[],int n)
{
	int i,j,k;
	RecType tmp;
	for (i=0;i<n-1;i++) 
	{
		for (j=n-1;j>i;j--)	//比较,找出本趟最小关键字的记录
			if (R[j].key<R[j-1].key)   
			{
				tmp=R[j];  //R[j]与R[j-1]进行交换,将最小关键字记录前移
				R[j]=R[j-1];
				R[j-1]=tmp;
			}
		printf("  i=%d: ",i);
		DispList(R,n);
	}
} 

//改进的冒泡排序算法

void BubbleSort1(RecType R[],int n)
{	int i,j;
	bool exchange;
	RecType tmp;
	for (i=0;i<n-1;i++) 
	{	exchange=false;					//一趟前exchange置为假
		for (j=n-1;j>i;j--)				//归位R[i],循环n-i-1次
			if (R[j].key<R[j-1].key)	//相邻两个元素反序时
			{	tmp=R[j];				//将这两个元素交换
				R[j]=R[j-1];
				R[j-1]=tmp;
				exchange=true;			//一旦有交换，exchange置为真
			}
		printf("  i=%d: ",i);
		DispList(R,n);
		if (!exchange)					//本趟没有发生交换，中途结束算法
			return;
	}
}
```

```c
//快速排序算法

int count=0;
int partition(RecType R[],int s,int t)	//一趟划分
{
	int i=s,j=t;
	RecType tmp=R[i];			//以R[i]为基准
	while (i<j)  				//从两端交替向中间扫描,直至i=j为止
	{	while (j>i && R[j].key>=tmp.key)
			j--;				//从右向左扫描,找一个小于tmp.key的R[j]
		R[i]=R[j];				//找到这样的R[j],放入R[i]处
		while (i<j && R[i].key<=tmp.key)
			i++;				//从左向右扫描,找一个大于tmp.key的R[i]
		R[j]=R[i];				//找到这样的R[i],放入R[j]处
	}
	R[i]=tmp;
	return i;
}

void QuickSort(RecType R[],int s,int t) //对R[s..t]的元素进行快速排序
{	int i;
	RecType tmp;
	if (s<t) 					//区间内至少存在两个元素的情况
	{	count++;
		i=partition(R,s,t);
		DispList(R,10);			//调试用
		QuickSort(R,s,i-1);		//对左区间递归排序
		QuickSort(R,i+1,t);		//对右区间递归排序
	}
}
```

#### 3.选择排序

```c
//简单选择排序算法

void SelectSort(RecType R[],int n)
{
	int i,j,k;
	RecType temp;
	for (i=0;i<n-1;i++)    	 	//做第i趟排序
	{
		k=i;
		for (j=i+1;j<n;j++)  	//在当前无序区R[i..n-1]中选key最小的R[k]
			if (R[j].key<R[k].key)
				k=j;           	//k记下目前找到的最小关键字所在的位置
			if (k!=i)          		//交换R[i]和R[k]
			{
				temp=R[i];
				R[i]=R[k];
				R[k]=temp;  
			}
		printf("  i=%d: ",i); DispList(R,n);
	}
}
```

```c
//堆排序算法

void sift(RecType R[],int low,int high)
{
	int i=low,j=2*i;     					//R[j]是R[i]的左孩子
	RecType temp=R[i];
	while (j<=high) 
	{
		if (j<high && R[j].key<R[j+1].key) 	//若右孩子较大,把j指向右孩子
			j++;    						//变为2i+1
		if (temp.key<R[j].key) 
		{
			R[i]=R[j];              		//将R[j]调整到双亲结点位置上
			i=j;                    		//修改i和j值,以便继续向下筛选
			j=2*i;
		}
		else break;                 		//筛选结束
	}
	R[i]=temp;                      		//被筛选结点的值放入最终位置
}

void HeapSort(RecType R[],int n)
{
	int i;
	RecType tmp;
	for (i=n/2;i>=1;i--)	//循环建立初始堆,调用sift算法 n/2 次
		sift(R,i,n); 
	printf("初始堆:"); DispList1(R,n);
	for (i=n;i>=2;i--)		//进行n-1趟完成推排序,每一趟堆排序的元素个数减1
	{	tmp=R[1];			//将最后一个元素与根R[1]交换
		R[1]=R[i];
		R[i]=tmp;
		printf("第%d趟: ",n-i+1); DispList1(R,n);
		sift(R,1,i-1);		//对R[1..i-1]进行筛选,得到i-1个节点的堆
		printf("筛选为:"); DispList1(R,n);
	}
}
```

#### 4.归并排序

```c
//自底向上的二路归并排序算法
#include <malloc.h>
#include "seqlist.cpp"

void Merge(RecType R[],int low,int mid,int high) 
{
	RecType *R1;
	int i=low,j=mid+1,k=0; //k是R1的下标,i、j分别为第1、2段的下标
	R1=(RecType *)malloc((high-low+1)*sizeof(RecType));  //动态分配空间
	while (i<=mid && j<=high)     	//在第1段和第2段均未扫描完时循环
		if (R[i].key<=R[j].key)    	//将第1段中的记录放入R1中
		{
			R1[k]=R[i];
			i++;k++; 
		}
		else                       		//将第2段中的记录放入R1中
		{
			R1[k]=R[j];
			j++;k++; 
		}
	while (i<=mid)          	       	//将第1段余下部分复制到R1
	{ 
		R1[k]=R[i];
		i++;k++; 
	}
    while (j<=high)                	//将第2段余下部分复制到R1
	{
		R1[k]=R[j];
		j++;k++;  
	}
    for (k=0,i=low;i<=high;k++,i++) //将R1复制回R中
	    R[i]=R1[k];
} 
void MergePass(RecType R[],int length,int n)	//对整个数序进行一趟归并
{
	int i;
	for (i=0;i+2*length-1<n;i=i+2*length) 	//归并length长的两相邻子表
		Merge(R,i,i+length-1,i+2*length-1);
	if (i+length-1<n-1)                		//余下两个子表,后者长度小于length
		Merge(R,i,i+length-1,n-1);  		//归并这两个子表
	printf("length=%d: ",length);
	DispList(R,n);
}
void MergeSort(RecType R[],int n)			//自底向上的二路归并算法
{
	int length;
	for (length=1;length<n;length=2*length)//进行log2n趟归并
		MergePass(R,length,n);
}
```

