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