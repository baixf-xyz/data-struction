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

void CreatInThread(ThreadNode *T)
{
    ThreadNode *pre=Null;
    if(T!=Null){           //对非空二叉树线索化
        InThread(T,pre);   //线索化二叉树
        pre->rchild=Null;  //处理遍历结束后的最后一个结点
        pre->rtag=1;
    }
}