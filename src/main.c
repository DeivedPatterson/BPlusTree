#include <stdio.h>
#include "../include/BPlusTree.h"
#include "../include/Client.h"




int main(int argc, char const *argv[])
{
	BPlusTree tree;
	struct Client client = {.clientCode = 10, .name = "Deived"};

	tree = newBPlusTree(sizeof(struct Client));


	InsertBPlusTree(tree, &client);



	return 0;
}