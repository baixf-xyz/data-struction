## 数据结构

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

1. BF（Brute-Force）算法/朴素模式匹配算法

```c
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

2. KMP算法

```c
// 求next数组
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

3. 王道版KMP算法

```c
// 求next数组
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

// KMP算法
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

4. 改进的KMP算法

```c
// 求nextval数组
void GetNextval(SqString t,int nextval[])  //由模式串t求出nextval值
{
	int j=0,k=-1;
	nextval[0]=-1;
   	while (j<t.length) 
	{
       	if (k==-1 || t.data[j]==t.data[k]) 
		{	
			j++;k++;
			if (t.data[j]!=t.data[k]) 
				nextval[j]=k;
           	else  
				nextval[j]=nextval[k];
       	}
       	else  k=nextval[k];    	
	}

}

//修正的KMP算法
int KMPIndex1(SqString s,SqString t)    
{
	int nextval[MaxSize],i=0,j=0;
	GetNextval(t,nextval);
	while (i<s.length && j<t.length) 
	{
		if (j==-1 || s.data[i]==t.data[j]) 
		{	
			i++;j++;	
		}
		else j=nextval[j];
	}
	if (j>=t.length)  
		return(i-t.length);
	else
		return(-1);
}
```
