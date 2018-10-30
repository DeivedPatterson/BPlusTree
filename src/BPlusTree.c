#include "../include/BPlusTree.h"
#include "../include/Exception.h"
#include <stdint.h>

#ifndef PAGE_SIZE
	#define PAGE_SIZE 3
#endif

#define M_KEY		(PAGE_SIZE*2)
#define	M_POINTER	(M_KEY+1)



typedef uint32_t Page[M_KEY + M_POINTER];


typedef struct BTreePage
{
	Page page;
	int size;
}BTreePage;


typedef struct __BPlusTree
{
	FILE* metadata;
	FILE* index;
	int pages;
	int datas;
}*ptrBPlusTree;



ptrBPlusTree newBPlusTree(void)
{
	ptrBPlusTree newTree = NULL;

	try
	{
		newTree = malloc(sizeof(struct __BPlusTree));
		if(newTree != NULL)
		{
			FileOpen(newTree->metadata, "MetaData.bin", "w+b");
			FileOpen(newTree->index, "Index.bin", "w+b");
			newTree->pages = 0;
			newTree->datas = 0;
		}
		else
		{
			throw(__MemoryAllocationException__);
		}
	}
	catch(MemoryAllocationException)
	{
		PrintExceptionStdOut(MemoryAllocationException);
	}
}

