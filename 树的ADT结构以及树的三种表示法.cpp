/**
 *  \brief 树的ADT结构以及树的三种表示法（双亲、孩子和孩子兄弟）
 */
class Tree
{
public:
	void InitTree(T* t);
	void DestroyTree(T* t);
	void ClearTree(T* t);
	void CreateTree(T* t, definition);
	bool TreeEmpty(T);
	int TreeDepth(T);
	RootNode* Root(T*);
	Value(T, cur_e);
	Assign(T, cur_e, value);
	Parent(T, cur_e);
	LeftChild(T, cur_e);
	RightSilbing(T, cur_e);
	InsertChild(T*, p*, i, c);
	DeleteChild(T*, p*, i);
};


/**
 *  树的双亲表示法
 *  获取结点的双亲结点的时间复杂度为O(1)
 *  获取结点的孩子结点的时间复杂度为O(n)
 */
#define MAX_TREE_SIZE 100
typedef int TElemType;		//	树结点的数据类型，目前暂定为整型

/* 结点结构 */
typedef struct PTNode	
{
	TElemType data;		//	结点数据
	int parent;			//	双亲位置
} PTNode;

/* 树结构 */
typedef struct
{
	PTNode nodes[MAX_TREE_SIZE];
	int r, n;	//	根的位置和结点数
}PTree;
/**
 *  end
 */



/**
 *  树的孩子表示法
 *  把每个结点的孩子结点排列起来，以单链表作存储结构，则n个结点有n个孩子链表
 *  如果是叶子结点则此单链表为空。然后n个头指针又组成一个线性表，采用顺序存储结构，存放进一个数组中。
 *  
 *  这样的结构对于查找某个结点的某个孩子，或者找某个结点的兄弟，只需查找这个结点的孩子单链表即可。
 *  对于遍历整棵树也是很方便的，对头结点的数组循环即可。
 *  但是，这也存在问题，如何知道某个结点的双亲是谁呢？比较麻烦，需要整棵树遍历才行。
 */
/* 孩子结点 */
typedef struct CTNode
{
	int child;
	CTNode* next;
} *ChildPtr;

/* 表头结构 */
typedef struct
{
	TElemType data;
	ChildPtr firstChild;
} CTBox;

/* 树结构 */
typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];		//	结点数组
	int r, n;		//	根的位置和结点数
} CTree;
/**
 *  end
 */
 
 
 
 
/**
 *  孩子兄弟表示法
 *  任何一棵树，它的结点的第一个孩子如果存在就是唯一的，它的右兄弟如果存在也是唯一的。
 *  因此，设置两个指针，分别指向该结点的第一个孩子和此结点的右兄弟。
 *  data	firstChild	rightSib
 *  数据域	  指针域	 指针域	
 *  
 *  这种表示法，给查找某个结点的某个孩子带来了方便，只需要通过firstChild找到此结点的长子，
 *  然后再通过长子结点的rightSib找到它的二弟，接着一直找下去，直到找到具体的孩子。
 *  当然，如果想找某个结点的双亲，这个表示法也是有缺陷的。
 *  如果真的有必要，完全可以再增加一个parent指针域来解决快速查找双亲的问题。
 *  其实这个表示法最大的好处是它把一颗复杂的树变成了一棵二叉树。
 */
typedef struct CSNode
{
	TElemType data;
	CSNode* firstChild;
	CSNode* rightSib;
} CSNode, *CSTree;
/**
 *  end
 */