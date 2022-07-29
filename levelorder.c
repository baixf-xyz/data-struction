//树的队列层次遍历算法：A(B(D(,G)),C(E,F))
#include "btree.cpp"
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