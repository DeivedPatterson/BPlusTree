#include "../include/BPlusTree.h"
#include "../include/Exception.h"
#include "../include/Typedefs.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef PAGE_SIZE
	#define PAGE_SIZE 3
#endif

#define M_KEY		(PAGE_SIZE*2)
#define	M_POINTER	(M_KEY+1)

#define CBTree(ptr) ((ptrBPlusTree)ptr)

typedef int32_t Page[M_KEY + M_POINTER];

typedef enum State
{
	LEAF,
	ROOT
}STATE;

typedef struct BTreeNode
{
	Page block;
	int items;
	bool leaf;
}BTreeNode;


typedef struct __BPlusTree
{
	FILE* metadata;
	FILE* index;
	FILE* data;
	int pages;
	int datas;
	int sizeData;
}*ptrBPlusTree;

typedef struct MetaData
{
	Address nextAddressAvailable;
	STATE stat;
}MetaData;

static BTreeNode newEmptyNode(void)
{
	unsigned i;
	BTreeNode newNode;

	for(i = 0; i < (M_POINTER + M_KEY); i++)
	{
		newNode.block[i] = None;
	}
	newNode.leaf = true;
	newNode.items = 0;

	return newNode;
}

BPlusTree newBPlusTree(int sizeData)
{
	ptrBPlusTree newTree = NULL;
	MetaData mdata;
	BTreeNode dpage;
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
			dpage.items = 0;
			dpage.leaf = true;
			mdata.nextAddressAvailable = None;
			mdata.stat = LEAF;

			FileWrite(&dpage, sizeof(BTreeNode), 1, newTree->index, res);
			FileWrite(&mdata, sizeof(MetaData), 1, newTree->metadata, res);

			//FileClose(newTree->data);
			//FileClose(newTree->metadata);

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
	BTreeNode page;
	BTreeNode newPage;
	MetaData mdata;
	int res = None;
	uint32_t i;


	data = (Byte*)calloc(CBTree(bpTree)->sizeData, sizeof(Byte));

	memcpy(data, obj, CBTree(bpTree)->sizeData);

	key = *((uint32_t*)obj);

	ReWind(CBTree(bpTree)->index);
	ReWind(CBTree(bpTree)->metadata);
	ReWind(CBTree(bpTree)->data);

	FileRead(&mdata, sizeof(MetaData), 1, CBTree(bpTree)->metadata, res);
	FileRead(&page, sizeof(BTreeNode), 1, CBTree(bpTree)->index, res);

	ReWind(CBTree(bpTree)->data);
	ReWind(CBTree(bpTree)->metadata);

	if(mdata.stat == LEAF && mdata.nextAddressAvailable == None)
	{
		printf("skey: %i\n", key);
		for(i = 1; i < (M_KEY + M_POINTER); i += 2)
		{
			if(page.block[i] == None)
			{
				page.block[i] = key;
				FileWrite(data, CBTree(bpTree)->sizeData, 1, CBTree(bpTree)->data, res);
				GetCurrentPStream(CBTree(bpTree)->data, mdata.nextAddressAvailable);
				mdata.stat = ROOT;

				FileWrite(&mdata, sizeof(MetaData), 1, CBTree(bpTree)->metadata, res);
				break;
			}
		}
	}
	else
	{
		
	}	
}