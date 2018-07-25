/*
二叉堆是完全二元树或者是近似完全二元树，它分为两种：最大堆和最小堆。
最大堆：父结点的键值总是大于或等于任何一个子节点的键值；最小堆：父结点的键值总是小于或等于任何一个子节点的键值。
*/
int heap[30];
int h_capacity = 30;//最大容量
int h_size = 0;//当前存储个数

int getDataIndex(int data)//简易循环 时间复杂度O(n)
{
	for(int i = 0;i < h_size; i++)
	{
		if(heap[i] == data)
			return i;
	}
	return -1;
}

/*最大堆向上调整算法
heap[0]表示根节点存储的数据
若子节点为x 则其父节点表示为 x/2 - 1
若父节点为x 则其左右子节点分别为 2x+1, 2(x+1)
*/
void maxheap_filterup(int start)
{
	if(start < 0)
	{
		printf("input start was err...\n");
		return;
	}
	int c = start;
	int p_index = (c - 1) / 2;
	if(p_index < 0)
		return;
	int tmp = heap[c];
	while(c > 0)
	{
		if(tmp <= heap[p_index])
			break;
		else
		{
			heap[c] = heap[p_index];
			c = p_index;
			p_index = (p_index - 1) / 2;
		}
	}
	heap[c] = tmp;
}
void maxheap_insert(int data)
{
	int index = getDataIndex(data);
	if(index != -1)
	{
		printf("the data was exist\n");
		return;
	}
	heap[h_size] = data;
	maxheap_filterup(h_size);
	h_size++;
}


/*最大堆向下调整算法
heap[0]表示根节点存储的数据
若子节点为x 则其父节点表示为 x/2 - 1
若父节点为x 则其左右子节点分别为 2x+1, 2(x+1)
*/
void maxheap_filterdown(int start, int end)
{
	if(start >= end || start < 0 || end < 0)
		return;
	int c = start;
	int left = 2 * c + 1;//当前节点的左子节点
	int tmp = heap[c];
	while(left <= end)
	{
		if(left < end && heap[left] < heap[left + 1])
			left++;
		if(tmp >= heap[left])
			break;
		else
		{
			heap[c] = heap[left];
			c = left;
			left = c * 2 + 1;
		}
	}
	heap[c] = tmp;
}
void maxheap_remove(int data)
{
	if(h_size == 0)
		return;
	int index = getDataIndex(data);
	if(index == -1)
		return;
	heap[index] = heap[--h_size];
	maxheap_filterdown(index,h_size);
}
void outputheap()
{
	for(int i = 0; i < h_size; i++)
	{
		printf("%d\t",heap[i]);
	}
}

void main()
{        
	maxheap_insert(10);
	maxheap_insert(40);
	maxheap_insert(30);
	maxheap_insert(60);
	maxheap_insert(90);
	maxheap_insert(70);
	maxheap_insert(20);
	maxheap_insert(50);
	maxheap_insert(80);
	maxheap_insert(15);
	maxheap_filterdown(0,h_size -1);
	outputheap();
	printf("\n");
	maxheap_remove(60);
	outputheap();
	printf("\n");
	maxheap_remove(90);
	outputheap();
	system("pause");
}
