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

//环形顺序队列

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