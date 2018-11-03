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

#ifndef DATA_SIZE
	#define DATA_SIZE 64
#endif

#define M_KEY		(PAGE_SIZE*2)
#define	M_POINTER	(M_KEY+1)

#define CBTree(ptr) ((ptrBPlusTree)ptr)

typedef int32_t Page[M_KEY + M_POINTER];


typedef struct Leaf
{
	Address father;
	int items; 	
	Byte* dados;
}Leaf;

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
	FILE* fdata;
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
	Leaf dafultLeaf = {
		.father = -1,
		.items = 0,
		.dados = NULL
	};

	try
	{
		newTree = malloc(sizeof(struct __BPlusTree));
		dafultLeaf.dados = (Byte*)calloc(sizeData*M_KEY, sizeof(Byte));

		if((newTree != NULL) && dafultLeaf.dados != NULL)
		{
			FileOpen(newTree->metadata, "MetaData.bin", "w+b");
			FileOpen(newTree->index, "Index.bin", "w+b");
			FileOpen(newTree->fdata, "Data.bin", "w+b");
			newTree->pages = 0;
			newTree->datas = 0;
			newTree->sizeData = sizeData;

			for(i = 0; i < (M_POINTER + M_KEY); i++)
			{
				dpage.block[i] = None;
			}

			for(i = 0; i < (sizeData * M_KEY); i += sizeData)
			{
				dafultLeaf.dados[i] = None;
			}
			dpage.items = 0;
			dpage.leaf = true;
			mdata.nextAddressAvailable = None;
			mdata.stat = LEAF;

			FileWrite(&dpage, sizeof(BTreeNode), 1, newTree->index, res);
			FileWrite(&mdata, sizeof(MetaData), 1, newTree->metadata, res);

			
			FileWrite(&dafultLeaf.father, sizeof(Address), 1, newTree->fdata, res);
			FileWrite(&dafultLeaf.items, sizeof(int), 1, newTree->fdata, res);
			FileWrite(dafultLeaf.dados, sizeData, 1, newTree->fdata, res);
			//FileClose(newTree->data);
			//FileClose(newTree->metadata);

			free(dafultLeaf.dados);

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

Object SearchBPlusTree(BPlusTree bpTree, Object obj)
{
	Object res = NULL;




}

void InsertBPlusTree(BPlusTree bpTree, Object obj)
{
	uint32_t key;
	BTreeNode page;
	Leaf newLeaf = {
		.father = -1, 
		.dados = NULL, 
		.items = 0
	};
	MetaData mdata;
	int res = None;
	uint32_t i;
	uint32_t offset;


	key = *((uint32_t*)obj);
	offset = CBTree(bpTree)->sizeData;

	ReWind(CBTree(bpTree)->index);
	ReWind(CBTree(bpTree)->metadata);
	ReWind(CBTree(bpTree)->fdata);

	FileRead(&mdata, sizeof(MetaData), 1, CBTree(bpTree)->metadata, res);
	FileRead(&page, sizeof(BTreeNode), 1, CBTree(bpTree)->index, res);

	ReWind(CBTree(bpTree)->fdata);
	ReWind(CBTree(bpTree)->metadata);


	if(mdata.stat == LEAF && mdata.nextAddressAvailable == None)
	{
		printf("skey: %i\n", key);
		newLeaf.dados = (Byte*)calloc(offset*M_KEY, sizeof(Byte)); 
		FileRead(&newLeaf.father, sizeof(Address), 1, CBTree(bpTree)->fdata, res);
		FileRead(&newLeaf.items, sizeof(int), 1, CBTree(bpTree)->fdata, res);
		FileRead(newLeaf.dados, offset*M_KEY, 1, CBTree(bpTree)->fdata, res);

		if(newLeaf.items < M_KEY)
		{
			memcpy(&(newLeaf.dados[newLeaf.items*offset]), obj, CBTree(bpTree)->sizeData);
			newLeaf.items += 1;
			ReWind(CBTree(bpTree)->fdata);

			FileWrite(&newLeaf.father, sizeof(Address), 1, CBTree(bpTree)->fdata, res);
			FileWrite(&newLeaf.items, sizeof(int), 1, CBTree(bpTree)->fdata, res);
			FileWrite(newLeaf.dados, offset*M_KEY, 1, CBTree(bpTree)->fdata, res);
		}
		else
		{
			puts("página cheia!!!");
		}
	}

	else
	{

	}
}