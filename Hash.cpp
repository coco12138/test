typedef struct ListNode * ListNodePtr;
typedef struct ListNode 
{
	int data;
	struct ListNode * nextPtr;
}LIST;
typedef struct HashTable 
{
	int TableSize;
	ListNodePtr *List; 
}HashTbl;
typedef struct HashTable * HashTablePtr; 
int Hash(int key,int tablesize)
{  
    return key % tablesize;  
}  
int NextPrime(int x)
{
	int flag;
	while(1)
	{
		flag = 0;
		int i;
		int n = sqrt((float)x);
		for(i = 2; i <= n; i++)
		{
			if(x % i == 0)
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			return x;
		else
			x++;
	}
}
HashTablePtr InitalizeTable(int TableSize)
{
	if(TableSize <= 0)
	{
		printf("散列大小错误\n");
		return NULL;
	}
	HashTablePtr table = (HashTablePtr)malloc(sizeof(HashTable));
	if(table == NULL)
		printf("malloc table fail\n");
	table->TableSize = NextPrime(TableSize);
	table->List = (ListNodePtr *)malloc(sizeof(ListNodePtr) * table->TableSize);
	if(table->List == NULL)
		printf("malloc list fail\n");
	table->List[0] = (ListNodePtr)malloc(table->TableSize * sizeof(LIST));
	if(table->List[0] == NULL)
		printf("malloc list[0] fail\n");
	int i;
	for(i = 0; i < table->TableSize; i++)
	{
		table->List[i] = table->List[0] + i;
		table->List[i]->nextPtr = NULL;
	}
	return table;

}
ListNodePtr Find(int key, HashTablePtr H)
{
	ListNodePtr p;
	ListNodePtr L = H->List[Hash(key,H->TableSize)];
	p = L->nextPtr;
	while(p != NULL && p->data != key)
		p = p->nextPtr;
	if(p == NULL)
		return L;
	else
		return p;
}
void Insert(int key, HashTablePtr H)
{
	ListNodePtr p, NewCell;
	p = Find(key,H);
	if(p->data != key)
	{
		NewCell = (ListNodePtr)malloc(sizeof(ListNode));
		if(NewCell == NULL)
			printf("malloc fail\n");
		else
		{
			p = H->List[Hash(key,H->TableSize)];//该组的链表头 链表头不储存数据 把新的数据插入链表头后
			NewCell->nextPtr = p->nextPtr;
			p->nextPtr = NewCell;
			NewCell->data = key;
		}
	}
	else
		printf("the data has exist\n");
}
void Delete(int key,HashTablePtr H)
{
	ListNodePtr p, NewCell;
	p = Find(key, H);
	if(p->data == key)
	{
		NewCell = H->List[Hash(key,H->TableSize)];
		while(NewCell->nextPtr != p)
			NewCell = NewCell->nextPtr;
		NewCell->nextPtr = p->nextPtr;
		free(p);
	}
	else
		printf("no data\n");
}
void main()
{
	HashTablePtr table = InitalizeTable(5);
	ListNodePtr p =NULL;
	p = Find(11,table);
	printf("%d\n",p->data);
	Insert(55,table);  
  Insert(90,table);  
  Insert(35,table);  
  Insert(33,table);  
	p = Find(55,table);  
  printf("%d\n",p->data);
	Delete(55,table);
	p = Find(55,table);  
	printf("%d\n",p->data);
	system("pause");
}
