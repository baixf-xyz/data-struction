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

//改进的KMP算法(本质上只是修改了求 nextval数组)
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
