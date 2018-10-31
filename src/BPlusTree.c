#include "../include/BPlusTree.h"
#include "../include/Exception.h"
#include "../include/Typedefs.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef PAGE_SIZE
	#define PAGE_SIZE 3
#endif

#define M_KEY		(PAGE_SIZE*2)
#define	M_POINTER	(M_KEY+1)

#define CBTree(ptr) ((ptrBPlusTree)ptr)

typedef int32_t Page[M_KEY + M_POINTER];

static enum State
{
	LEAVE,
	ROOT
}STATE;

typedef struct BTreePage
{
	Page block;
	int size;
}BTreePage;


typedef struct __BPlusTree
{
	FILE* metadata;
	FILE* index;
	FILE* data;
	int pages;
	int datas;
	int sizeData;
}*ptrBPlusTree;



BPlusTree newBPlusTree(int sizeData)
{
	ptrBPlusTree newTree = NULL;
	BTreePage dpage;
	unsigned i;
	uint32_t res = None;

	try
	{
		newTree = malloc(sizeof(struct __BPlusTree));
		if(newTree != NULL)
		{
			FileOpen(newTree->metadata, "MetaData.bin", "w+b");
			FileOpen(newTree->index, "Index.bin", "w+b");
			FileOpen(newTree->data, "Data.bin", "w+b");
			newTree->pages = 0;
			newTree->datas = 0;
			newTree->sizeData = sizeData;

			for(i = 0; i < (M_POINTER + M_KEY); i++)
			{
				dpage.block[i] = None;
			}
			dpage.size = 0;

			FileWrite(&dpage, sizeof(BTreePage), 1, newTree->data, res);
			FileWrite(&STATE, sizeof(enum State), 1, newTree->metadata, res);

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

	return newTree;
}

void InsertBPlusTree(BPlusTree bpTree, Object obj)
{
	Byte *data;
	uint32_t key;
	BTreePage page;
	int res = None;
	uint32_t i;


	data = (Byte*)calloc(CBTree(bpTree)->sizeData, sizeof(Byte));

	memcpy(data, obj, CBTree(bpTree)->sizeData);

	key = *((uint32_t*)obj);

	ReWind(CBTree(bpTree)->data);
	FileRead(&page, sizeof(BTreePage), 1, CBTree(bpTree)->data, res);

	printf("key: %i\n", key);
	for(i = 0; i < (M_KEY + M_POINTER); i++)
	{
		printf("%i\n", page.block[i]);
	}
}