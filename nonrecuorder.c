//先序、中序和后序非递归遍历算法
typedef struct 
{	BTNode *data[MaxSize];			//存放栈中的数据元素
	int top;						//存放栈顶指针，即栈顶元素在data数组中的下标
} SqStack;	

void PreOrder1(BTNode *b)			//先序非递归遍历算法1
{
	BTNode *p;
	SqStack *st;					//定义一个顺序栈指针st
	InitStack(st);					//初始化栈st
	Push(st,b);					//根节点进栈
	while (!StackEmpty(st))		//栈不为空时循环
	{
		Pop(st,p);				//退栈节点p并访问它
		printf("%c ",p->data);	//访问节点p
		if (p->rchild!=NULL)	//有右孩子时将其进栈
			Push(st,p->rchild);
		if (p->lchild!=NULL)	//有左孩子时将其进栈
			Push(st,p->lchild);
	}
	printf("\n");
	DestroyStack(st);				//销毁栈
}
void PreOrder2(BTNode *b)			//先序非递归遍历算法2
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
void InOrder1(BTNode *b)				//中序非递归遍历算法
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

void PostOrder1(BTNode *b)				//后序非递归遍历算法
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