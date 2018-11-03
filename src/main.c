#include <stdio.h>
#include "../include/BPlusTree.h"
#include "../include/Client.h"




int main(int argc, char const *argv[])
{
	BPlusTree tree;
	struct Client client = {.clientCode = 10, .name = "Deived"};
	int code;
	tree = newBPlusTree(sizeof(struct Client));

	do
	{
		scanf("%s", client.name);
		scanf(" %i", &client.clientCode);
		InsertBPlusTree(tree, &client);
	}while(getchar() != 'E');



	return 0;
}