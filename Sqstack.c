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