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