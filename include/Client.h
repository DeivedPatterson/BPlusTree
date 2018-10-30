#ifndef CLIENT_H_
#define CLIENT_H_ 

#define MAX_NAME_LENGTH 32UL

typedef struct Client
{
	unsigned int clientCode;
	char name[MAX_NAME_LENGTH];
	union
	{
		unsigned int date;
		struct 
		{
			unsigned year:23;
			unsigned day:5;
			unsigned month:4;
		}field;
	}birth;
}*Client;


Client newClientStack(struct Client client);
Client newClient(const char* name, unsigned day, unsigned month, unsigned year);
void CreateAleatoryClient(Client client, int n);		



#endif	