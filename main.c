#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "defs.h"


FILE *Openfile(char *name, char *mode);



int main(int argc, char **argv){
	
	int map = 0, prob = 0, i = 0;
	char *probsname = argv[2], *mapsname = argv[3], *saida;
	FILE *mapfile, *probfile, *out;
	
	
	if (argc == 4){
		
	if(argv[1][1]== 'o')	prob = 0;
	
	else if(argv[1][1]== 'a') prob = 1;
	
	if(argv[1][2] == 'o') map = 0;
	
	else if(argv[1][2] == 'a')  map = 1;
	}
	else if (argc!=4) exit(1);
	
	i=0;
	while (i <= (strlen(probsname)-5)){ /*verificação da extensão do ficheiro prbs(possivelmente desnecessário)*/
		if(i == (strlen(probsname)-5)){
			if(probsname[i] != '.' || probsname[i+1] != 'p' || probsname[i+2] != 'r' || probsname[i+3] != 'b' || probsname[i+4] != 's') {
				printf("Extensão errada\n");
				exit(1);
			}
		}
		i++;
	}
	
	i=0;
	while (i <= (strlen(mapsname)-5)){  /*verificação da extensão do ficheiro maps(possivelmente desnecessário)*/
		if(i == (strlen(mapsname)-5)){
			if(mapsname[i] != '.' || mapsname[i+1] != 'm' || mapsname[i+2] != 'a' || mapsname[i+3] != 'p' || mapsname[i+4] != 's') {
				printf("Extensão errada\n");
				exit(1);
			}
		}
		i++;
	}
	
	mapfile = Openfile(mapsname, "r");
	
	probfile = Openfile(probsname, "r");
	
	saida = (char*) malloc(strlen(mapsname)+3);
	saida = strcat((strncpy(saida, mapsname, (strlen(mapsname)-5))), ".routes");
	
	out = Openfile(saida, "w+");
	
	free(saida);
	
	fprintf(out, "Hello world \n");
	
	fclose(out);
	fclose(probfile);
	fclose(mapfile);
	
	return 0;
}
	
FILE *Openfile(char *name, char *mode)
{
   FILE *fp;
	
   fp = fopen(name, mode);
   
   if (fp == NULL) {
      fprintf(stderr, "Error: Unable to open file '%s'\n.", name);
      exit(1);
   }
   return fp;
   }
