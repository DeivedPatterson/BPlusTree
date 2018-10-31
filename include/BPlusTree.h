#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include <stdint.h>
#include "Typedefs.h"


typedef void* BPlusTree;


BPlusTree newBPlusTree(int sizeData);
void InsertBPlusTree(BPlusTree bpTree, Object obj);
Object SearchBPlusTree(BPlusTree bpTree, Object obj);
void DeleteBPlusTree(BPlusTree bpTree, Object obj);


#endif