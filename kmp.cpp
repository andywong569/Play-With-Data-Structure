
/**
 *  \brief V1 计算返回子串的next数组
 *  
 *  \param [in] s 子串
 *  \param [out] next 返回next数组
 *  \return Return_Description
 *  
 *  \details next[0] = -1, next[1] = 0 ...
 */
void getNext(const string& s, int* next)
{
	int j = 0;
	int k = -1;
	next[0] = -1;
	while(j < s.length() - 1)
	{
		if(k == -1 || s[j] == s[k])  //	s[j]表示后缀的单个字符，s[k]表示前缀的单个字符
			next[++j] = ++k;
		else
			k = next[k];	/*	若字符不同，则k回溯	*/
	}
}


/**
 *  \brief V2 计算返回子串的next数组
 *  
 *  \param [in] s 子串
 *  \param [out] next 返回next数组
 *  \return Return_Description
 *  
 *  \details next[0] = -1, next[1] = 0 ...
 *  V1 版本的改进版
 *  s = "ABACBCDHI"
 *  t = "ABAB"
 *  显然，当V1 版本的算法得到的next数组应该是[-1, 0, 0, 1]
 *  所以下一步我们应该把j移动到第1个元素
 *  不难发现，这一步是完全没有意义的。因为后面的B已经不匹配了，那前面的B也一定是不匹配的。
 *  显然，发生问题的原因在于s[j] == s[next[j]]
 */
void getNext2(const string& s, int* next)
{
	int j = 0;
	int k = -1;
	next[0] = -1;
	while(j < s.length() - 1)
	{
		if(k == -1 || s[j] == s[k])  //	s[j]表示后缀的单个字符，s[k]表示前缀的单个字符
		{
			if(s[++j] == s[++k])
				next[j] = next[k];
			else
				next[j] = k;
		}
		else
			k = next[k];	/*	若字符不同，则k回溯	*/
	}
}


/**
 *  \brief 返回子串在主串中第pos位置开始查找的结果位置
 *  
 *  \param [in] s 主串
 *  \param [in] t 子串
 *  \param [in] pos 起始查找位置
 *  \return 若存在，返回起始位置；否则返回-1；
 *  
 *  \details 相对于朴素匹配算法增加的代码，改动不算大，关键是去掉了i值回溯的部分。
 *  对于getNext函数来说，若s的长度为m，因只涉及到简单的单循环，其时间复杂度为O(m)
 *  由于i值的不回溯，使得indexByKMP算法效率得到了提高，while循环的时间复杂度为O(n)
 *  因此，整个算法的时间复杂度为O(m+n)。相较于朴素模式匹配算法的O[(n-m+1)*m]来说，是要好一些。
 *  这里也需要强调，KMP算法仅当模式与主串之间存在需要“部分匹配”的情况下才体现它的优势，否则两者差异并不明显。
 */
int indexByKMP(const string& s, const string& t, int pos)
{
	int next[255];
	getNext(t, next);
	int i = pos;
	int j = 0;
	if(pos >= 0)
	{
		while(i < s.length() && j < t.length())
		{
			if(j == -1 || s[i] == t[j])	//	当j为-1时，说明之前最后一次比较是不相等的，要移动的是i，当然j也要归0
			{
				++i;
				++j;
			}
			else
			{
				j = next[j];
			}
		}
	}
	
	if(j >= t.length())
		return i - j;
	else
		return -1;
}