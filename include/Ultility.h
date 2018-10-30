#ifndef UTILITY_H_
#define UTILITY_H_ 

#include <stdio.h>
#include <stdlib.h>
#include "Exception.h"

#define foreachFile(addressOut,file) 		           						\
 																			\
	while(fread(&addressOut,sizeof(addressOut),1,file) > 0)

	
#define Get_mRegisters(vector, file, m, type)								\
	{																		\
		int i = 0;															\
		while((fread(&(vector[i]),sizeof(type), 1,file) > 0) && (i < m))	\
			i++;															\
	}

#define foreach_mRegisters(output, file, m)									\
	for(int i = 0; ((i < m) && (fread(&output, sizeof(output),1,file) > 0)); i++)


#define foreachVectorWithN(addressOut,vector,n)								\
	for(int i = 0; i < n; addressOut = vector[i], i++)




#endif		