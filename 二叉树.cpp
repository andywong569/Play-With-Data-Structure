/**
 *  二叉树性质
 *  1、在二叉树的第i层上至多有2^(i-1)个结点(i>=1)
 *  2、深度为k的二叉树至多有2^(k) - 1个结点(k>=1)
 *  3、对任何一棵二叉树T，如果其终端（叶子）结点为n0，度为2的结点数为n2，则n0 = n2 + 1
 *     总结点数为n=n0+n1+n2，总线数=n-1=2*n2+n1，则n0+n1+n2-1=2*n2+n1，从而得到上述结论；
 *  4、具有n个结点的完全二叉树的深度为[log2(n)]+1
 *  5、如果对一课有n个结点的完全二叉树的结点按层序编号，对于任一结点i(1<=i<=n)有：
 *  	1）如果i=1，则结点i是二叉树的根，无双亲；如果i>1，则其双亲是结点[i/2]。
 *  	2）如果2i>n，则结点i无左孩子(结点i为叶子结点)；否则其左孩子是结点2i。
 *  	3）如果2i+1>n，则结点i无右孩子；否则其右孩子是结点2i+1.
 */
 
 
/**
 *  存储结构
 *  1、顺序存储结构：用一维数组存储二叉树中的结点，并且结点的存储位置，
 *  	也就是数组的下标要能体现结点之间的逻辑关系。一般只用于完全二叉树；
 *  2、二叉链表
 *  3、三叉链表：在二叉链表的基础上再增加一个指向其双亲的指针；
 */
typedef struct BiTNode	//	二叉树的二叉链表结点结构定义
{
	TElemType data;		//	结点数据
	BiTNode* lchild;	//	左孩子指针
	BiTNode* rchild;	//	右孩子指针
} BiTNode, *BiTree;



/**
 *  遍历
 *  1、前序遍历：根节点-前序遍历左子树-前序遍历右子树
 *  2、中序遍历：根节点开始(并不是先访问根节点)-中序遍历根节点的左子树-根节点-中序遍历右子树
 *  3、后序遍历：从左到右先叶子后结点的方式遍历访问左右子树-访问根节点
 *  4、层序遍历：根节点开始访问，从上而下逐层遍历，同一层从左至右的顺序对结点逐个访问
 */
void PreOrderTraverse(BiTree T)		//	二叉树的前序遍历递归算法
{
	if(T == nullptr)
		return;
	
	printf("%c", T->data);	//	显示结点数据，可以更改为其他对结点操作
	PreOrderTraverse(T->lchild);	//	再先序遍历左子树
	PreOrderTraverse(T->rchild);	//	最后先序遍历右子树
}

void InOrderTraverse(BiTree T)	//	二叉树的中序遍历递归算法
{
	if(T == nullptr)
		return;
	
	InOrderTraverse(T->lchild);		//	中序遍历左子树
	printf("%c", T->data);		//	显示结点数据，可以更改为其他对结点操作
	InOrderTraverse(T->rchild);		//	最后中序遍历右子树
}

void PostOrderTraverse(BiTree T)	//	二叉树的后序遍历递归算法
{
	if(T == nullptr)
		return;
	
	PostOrderTraverse(T->lchild);		//	后序遍历左子树
	PostOrderTraverse(T->rchild);		//	最后后序遍历右子树
	printf("%c", T->data);		//	显示结点数据，可以更改为其他对结点操作
}


/**
 *  生成二叉树
 *  按前序输入二叉树中结点的值（一个字符）
 *  #表示空树，构造二叉链表表示二叉树T
 */
void CreateBiTree(BiTree* T)
{
	TElemType ch;
	scanf("%c", &ch);
	if(ch == '#')
	{
		*T = nullptr;
	}
	else
	{
		*T = new BiTNode;
		if(!*T)
			exit(OVERFLOW);
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}



/**
 *  线索二叉树
 *  对于一个有n个结点的二叉链表，每个结点有指向左右孩子的两个指针域，一共是2n个指针域。
 *  而n个结点的二叉链表一共有n-1条分支线，也就是说，其实是存在2n-(n-1)=n+1个空指针域。
 *  可以利用这些空地址，存放指向结点在某种遍历次序下的前驱和后继结点的地址。
 *  这种指向前驱和后继的指针称为线索，加上线索的二叉链表称为线索链表
 *  相应的二叉树称为线索二叉树(Threaded Binary Tree)
 *  对二叉树以某种次序遍历使其变为线索二叉树的过程称作是线索化
 */
typedef enum { Link, Thread } PointerTag;	//	Link == 0表示指向左右孩子指针
											//	Thread == 1表示指向前驱或后继的线索
typedef struct BiThrNode	//	二叉线索存储结点结构
{
	TElemType data;		//	结点数据
	BiThrNode* lchild;	//	左孩子指针
	BiThrNode* rchild;	//	右孩子指针
	PointerTag ltag;	//	左孩子标志
	PointerTag rtag;	//	右孩子标志
} BiThrNode, *BiThrTree;


/**
 *  中序遍历线索化的递归函数
 *  线索化的过程就是在遍历的过程中修改空指针的过程
 */
BiThrTree pre = nullptr;		//	全局变量，始终指向刚刚访问过的结点
void InThreading(BiThrTree p)	//	中序遍历进行中序线索化
{
	if(p == nullptr)
		return;
	
	InThreading(p->lchild);		//	递归左子树线索化
	if(p->lchild == nullptr)	//	没有左孩子
	{
		p->ltag = Thread;
		p->lchild = pre;		//	左孩子指针指向前驱
	}
	if(pre->rchild == nullptr)	//	前缀没有右孩子
	{
		pre->rtag = Thread;
		pre->rchild = p;		//	前驱右孩子指针指向后继（当前结点p）
	}
	pre = p;					//	保持pre指向p的前驱
	InThreading(p->rchild);		//	递归右子树线索化
}

/**
 *  T指向头结点，头结点lchild指向根结点，头结点rchild指向中序遍历的最后一个结点。
 *  中序遍历二叉线索链表表示的二叉树T
 *  时间复杂度为O(n)
 */
Status InOrderTraverse_Thr(BiThrTree T)
{
	BiThrTree p = T->lchild;	//	p指向根节点
	while(p != T)	//	空树或遍历结束时，p == T
	{
		while(p->ltag == Link)	//	当ltag == 0时循环到中序序列第一个结点
		{
			p = p->lchild;
		}
		printf("%c", p->data);
		
		while(p->rtag == Thread && p->rchild != T)
		{
			p = p->rchild;
			printf("%c", p->data);
		}
		p = p->rchild;	//	p进至其右子树根
	}
	
	return OK;
}