OBJS = src/*.c
CC = gcc
OBJ_NAME = main


all:$(OBJS) 
	$(CC) $(OBJS)  -o $(OBJ_NAME)  #-DDEBUG_PRINT_HASH_OP 