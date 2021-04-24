#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main(int argc, char **argv){
	
	Graph *g;
	int map, prob, i = 0, l;
	char *probsname = argv[2], *mapsname = argv[3], *saida;
	FILE *mapfile, *probfile, *out;

	if (argc == 4){

	if(argv[1][2]== 'o')	prob = 0;

	else if(argv[1][2]== 'a') prob = 1;

	if(argv[1][3] == 'o') map = 0;

	else if(argv[1][3] == 'a')  map = 1;
	}
	else if (argc!=4) exit(1);

	while (i <= (strlen(probsname)-6)){ /*verificação da extensão do ficheiro prbs(possivelmente desnecessário) */
	if(i == (strlen(probsname)-6)){
			if(probsname[i] != '.' || probsname[i+1] != 'p' || probsname[i+2] != 'r' || probsname[i+3] != 'b' || probsname[i+4] != 's' || probsname[i+5] != '1') {
				printf("Extensão errada\n");
				exit(1);
			}
		}
		i++;
	}

	i=0;
	while (i <= (strlen(mapsname)-5)){ /* verificação da extensão do ficheiro maps(possivelmente desnecessário) */
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
	
	saida = (char*) malloc((strlen(mapsname)+4)*sizeof(char));
	/*if (saida == NULL)
	{
		printf("Não foi possivel alocar memoria\n");
		exit(1);
	}*/
	
	l=strlen(mapsname)-5;
	strncpy(saida, mapsname, (strlen(mapsname)-5));
    saida[l]='\0';

	saida = strcat(saida, ".queries");

	out = Openfile(saida, "w+");
	free(saida);
	fprintf(out, "%s %s %s\n", argv[1], argv[2], argv[3]);

	do
	{
	
		g = readmaps(mapfile);
		
		do
		{
	
			readprbs(probfile, g, out, prob);
	
		}while((prob==1) && (!feof(probfile)));
		
		GRAPHdestroy(g);
		
	}while((map==1) && (!feof(mapfile)));

	fclose(out);
	fclose(probfile);
	fclose(mapfile);

	return 0;
}

/*
 *  Function:
 *    initList
 *
 *  Description:
 *    Initializes a new linked list.
 *
 *  Arguments:
 *    None
 *
 *  Return value:
 *    Returns the pointer to a new linked list.
 */

FILE *Openfile(char *filename, char *mode)
{
   FILE *fp;
	
   fp = fopen(filename, mode);

   if (fp == NULL) {
      fprintf(stderr, "Error: Unable to open file '%s'\n", filename);
       exit(1);
   }

   return fp;
}


void readprbs(FILE* fpprobs, Graph *g, FILE *out, int prob){

    char modo[2];
    int edge1=0, edge2=0, k;

	k=fscanf(fpprobs, "%s %d %d", modo, &edge1, &edge2);
	if (k==2){
		/*modoA0();*/     /*Chama aqui a funçao*/
        printf("%s %d %d\n", modo, edge1, edge2);

    }else if(k==3){

        if((strcmp("B0",modo))==0){
			/*modoB0();*/     /*Chama aqui a funçao*/
            printf("%s %d %d\n", modo, edge1, edge2);

        }else if((strcmp("C0", modo))==0){
			if((edge1<=0)||(edge1 > getV(g)))k=-1;
			else
			{
				if((edge2>=0) && ((edge1<0)||(edge1 > getV(g)))){
					printf("%s %d %d\n", modo, edge1, edge2);
					k = modoC0(g, edge1, edge2);
					printf(" %d", k);
				}
				else{
					k = 0;
				}
			}
				fprintf(out, "\n%d %d %s %d %d %d", getV(g), getE(g), modo, edge1, edge2, k);
        }else if((strcmp("D0",modo))==0){
			if((edge1<=0)||(edge1 > getV(g)))k=-1;
			else
			{
				if(edge2>=0){
					printf("%s %d %d\n", modo, edge1, edge2);
					k = modoD0(g, edge1, edge2);
					printf(" %d", k);
				}
				else{
					k = 0;
				}
			}
			fprintf(out, "\n%d %d %s %d %d %d \n", getV(g), getE(g), modo, edge1, edge2, k);
		}
    }
        /* */

    return;
}
