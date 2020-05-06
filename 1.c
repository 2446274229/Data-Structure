#include <stdio.h>
#include <stdlib.h>
#define smax 30 //定义元素空间 
typedef int datatype;
typedef struct Inode
{
	int i,j;
	struct Inode *rptr,*cptr;
	union
	{
		struct Inode *next;
		datatype v;
	}uval;
}link;//十字链表
typedef struct
{
	int i,j;
	datatype v;
}node;
typedef struct
{
	int m,n,t;
	node data[smax];
}spmatrix;//三元组存储

spmatrix *creatseqmat(void); 
link *createlinkmat(void);
void printlinkmat(link *h);
spmatrix *changemat(link *h);
void printmat(spmatrix *a);
spmatrix *transmat(spmatrix *b);


int main()
{
	link *h;
	spmatrix *a,*b;
/*	
	//创建三元组矩阵 
	a=creatseqmat();
	//打印三元组矩阵
	printmat(a); 
*/
	//建立十字链矩阵
	h=createlinkmat();
	//输出十字矩阵
	printlinkmat(h);
	//把十字矩阵转换为三元组矩阵
	a=changemat(h);
	//打印三元组矩阵
	printmat(a);
	//转置三元组矩阵
	b=transmat(a);
	//输出转置后的矩阵
	printmat(b);
} 
//建立十字链矩阵
link *createlinkmat(void)
{
	link *p,*a,*b,*cp[smax];
	int i,j,v,m,n,t=0,max,k;
	printf("创建十字链矩阵:\n");
	printf("Please input 总行m,总列n:\n");
	scanf("%d,%d",&m,&n);
	if(m*n>smax || m<=0 || n<=0)
	{
		printf("输入无效\n");
		return NULL;
	}
	if(m>n)max=m;
	else max=n;
	p=(link*)malloc(sizeof(link));
	p->i=m;
	p->j=n;
	cp[0]=p;
	for(k=1;k<=max;k++)
	{
		cp[k]=(link*)malloc(sizeof(link));
 		cp[k]->i=0;
		cp[k]->j=0;
		cp[k]->rptr=cp[k];
		cp[k]->cptr=cp[k];
		cp[k-1]->uval.next=cp[k]; 
	}
	cp[max]->uval.next=p;
	printf("Please input 行i,列j,元素v:(不要超界)\n");
	scanf(" %d,%d,%d",&i,&j,&v);
	while(v!=0)
	{
		if(t>=smax)
		{
			printf("储存空间已满\n");
			break; 
		}
		t++;
		a=(link*)malloc(sizeof(link));
		a->i=i;
		a->j=j;
		b=cp[i];
		while(b->rptr!=cp[i]&&b->rptr->j<j)//最后，之间(的元素为基准)
			b=b->rptr;
		a->rptr=b->rptr;	//当前 -> 后 
		b->rptr=a;			  //前 -> 当前 
		b=cp[j];
		while(b->cptr!=cp[j]&&b->cptr->i<i)
			b=b->cptr;
		a->cptr=b->cptr;
		b->cptr=a;
		a->uval.v=v; 
		scanf(" %d,%d,%d",&i,&j,&v);
	}
	return p;
}
//输出十字矩阵
void printlinkmat(link *h)
{
	int i=1,n,k;
	link *p,*q,*a;
	printf("打印十字矩阵:\n");
	n=h->j;
	
	p=h->uval.next;
	while(p!=h && i<=h->i)
	{
		a=p->rptr;//row 行
		q=p;
		while(a!=p)
		{
			//插入同一行两非零元素间的“0”和 第一个非零元素之前的零 
			for(k=1;k<(a->j)-(q->j);k++)  
				printf("0 ");
			printf("%d ",a->uval.v);	
			q=a; 		//记录当前元素，直至同行最后一个非零值 
			a=a->rptr;
		}
		for(k=q->j;k<n;k++)   //插入同一行中最后一个非零元素后面的“0” 
			printf("0 ");
		printf("\n");
		i++;
		p=p->uval.next;
	}
}

//把十字矩阵转换为三元组矩阵
spmatrix *changemat(link *h)
{
	int m,n,t=1;
	link *p,*q;
	spmatrix *l;
	printf("十字矩阵转换为三元组矩阵:\n");
	m=h->i;
	n=h->j;
	l=(spmatrix*)malloc(sizeof(spmatrix));
	l->m=m;
	l->n=n;
	p=h->uval.next;
	while(p!=h)
	{
		q=p->rptr; //行   以下为同一行的查找、赋值 
		while(q!=p)
		{
			l->data[t].i=q->i;
			l->data[t].j=q->j;
			l->data[t].v=q->uval.v;	
			t++;
			q=q->rptr;
		}
		p=p->uval.next;
	}
	l->t=t-1;
	return l;
}
//转置三元组矩阵
spmatrix *transmat(spmatrix *b)
{
	int k,i,j;
	spmatrix *p;
	p=(spmatrix*)malloc(sizeof(spmatrix));
	p->m=b->n;
	p->n=b->m;
	p->t=b->t; 
	printf("转置三元组矩阵:\n");

	for(k=1;k<=b->t;k++)
	{
		i=b->data[k].i;
		j=b->data[k].j;
		p->data[k].i=j;
		p->data[k].j=i;
		p->data[k].v=b->data[k].v;
		//printf("i=%d,j=%d,data[%d]:%d\n",i,j,k,b->data[k].v);
	}
	return p;
} 
//创建三元组矩阵
spmatrix *creatseqmat(void)
{
	int i,j,n,m,t=0,v;
	spmatrix *p;
	printf("创建三元组矩阵:\n");
	p=(spmatrix*)malloc(sizeof(spmatrix));
	printf("Please input 总行m,总列n:\n");
	scanf("%d,%d",&m,&n);
	if(m*n>smax || m<=0 || n<=0)
	{
		printf("输入无效\n");
		return NULL;
	}
	printf("Please input 行i,列j,元素v:\n");
	scanf(" %d,%d,%d",&i,&j,&v);
	p->m=m;
	p->n=n;
	p->t=t;
	p->data[t].i=i;
	p->data[t].j=j;
	p->data[t].v=v;	//防止刚开始输入 x,y,0 这类情况发生后导致死循环现象 
	while(v!=0)
	{
		if(t>=smax)
		{
			printf("储存空间已满\n");
			break; 
		}
		t+=1;
		p->t=t;
		p->data[t].i=i;
		p->data[t].j=j;
		p->data[t].v=v;
		scanf(" %d,%d,%d",&i,&j,&v);
	}
	return p;
}
//打印三元组矩阵
void printmat(spmatrix *a)
{
	int i,j,k,t;
	printf("打印三元组矩阵:\n");
	for(i=1;i<=a->m;i++)
	{
		for(j=1;j<=a->n;j++)
		{
			t=0;	
			/*
				在每一轮列的循环中查找匹配的非零元素
			 	否则出现一些漏输的现象
			 	（因为之前的行列查找已经找过后一个非零元素，
				 但是与当前非零元素的行列不匹配） 
			*/
			for(k=1;k<=a->t;k++) 
				if((a->data[k].i==i)&&(a->data[k].j==j))
				{
					printf("%d ",a->data[k].v);
					t++;
					break;
				}
				if(t==0)
					printf("0 ");
				
		}
		printf("\n");
	}
} 
