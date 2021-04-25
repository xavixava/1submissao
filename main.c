#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main(int argc, char **argv){
	
	Graph *g;
	int map, prob, i = 0, l, edge1=0, edge2=0;
	char *probsname = argv[2], *mapsname = argv[3], *saida, *modo;
	FILE *mapfile, *probfile, *out;
	double b;
	
	modo = (char*) malloc(3*sizeof(char));

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

	if ((map==1) && (prob==1)){
		do{
			g = readmaps(mapfile);
			do{
				modo = readprbs(probfile, g, out, modo);
				switch(modo[0]){
				case 'D':
					fscanf(probfile, " %d %d", &edge1, &edge2);
					if((edge1<=0)||(edge1 > getV(g)))l=-1;
					else
					{
						if((edge2>=0)){
						printf("%s %d %d\n", modo, edge1, edge2);
						l = modoD0(g, edge1, edge2);
						}
						else{
						l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", getV(g), getE(g), modo, edge1, edge2, l);
				break;
				case 'A':
					l=modoA0(g, edge1);
					fprintf(out, "\n%d %d %s %d %d\n", getV(g), getE(g), modo, edge1, l);
				break;
				case 'B':
					b = modoB0(g, edge1, edge2);
					fprintf(out, "\n%d %d %s %d %d %lf\n", getV(g), getE(g), modo, edge1, edge2, b);
				break;
				case 'C':
					if((edge1<=0)||(edge1 > getV(g)))l=-1;
					else
					{
						if((edge2>=0) && ((edge1<0)||(edge1 > getV(g)))){
							l = modoC0(g, edge1, edge2);
						}
						else{
							l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", getV(g), getE(g), modo,edge1, edge2, l);
				break;
			}
			}while(feof(probfile)==0);
			fseek(probfile, 0, SEEK_SET);
			if(g!=NULL)GRAPHdestroy(g);
		}while(feof(mapfile)==0);
	}
	else{
		do
		{
			if(map!=-1)g = readmaps(mapfile);
			if(g==NULL) break;
			
			if(prob!=-1)modo = readprbs(probfile, g, out, modo);
			if(feof(probfile) !=0 || prob == 0)prob = -1;

			switch(modo[0]){
				case 'D':
					fscanf(probfile, " %d %d", &edge1, &edge2);
					if((edge1<=0)||(edge1 > getV(g)))l=-1;
					else
					{
						if((edge2>=0)){
						printf("%s %d %d\n", modo, edge1, edge2);
						l = modoD0(g, edge1, edge2);
						}
						else{
						l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", getV(g), getE(g), modo, edge1, edge2, l);
				break;
				case 'A':
					fscanf(probfile, " %d", &edge1);
					l = modoA0(g, edge1);
					fprintf(out, "\n%d %d %s %d %d\n", getV(g), getE(g), modo, edge1, l);
				break;
				case 'B':
					fscanf(probfile, " %d %d", &edge1, &edge2);
					b = modoB0(g, edge1, edge2);
					fprintf(out, "\n%d %d %s %d %d %lf\n", getV(g), getE(g), modo, edge1, edge2, b);
				break;
				case 'C':
					fscanf(probfile, " %d %d", &edge1, &edge2);
					if((edge1<=0)||(edge1 > getV(g)))l=-1;
					else
					{
						if((edge2>=0) && ((edge1<0)||(edge1 > getV(g)))){
							l = modoC0(g, edge1, edge2);
						}
						else{
							l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", getV(g), getE(g), modo,edge1, edge2, l);
				break;
			}
			
			if (map==1)GRAPHdestroy(g);
			if(map==0)map = -1;

		}while((map!=-1) || (prob!=-1));
	}
	if(g != NULL)GRAPHdestroy(g);
	
	free(modo);
	
	fclose(out);
	fclose(probfile);
	fclose(mapfile);

	return 0;
}

/*
 *  Function:
 *    Openfile
 *
 *  Description:
 *    Opens a file and exits if it can´t open it.
 *
 *  Arguments:
 *    char *filename keeping the name of the file
 *	  char *mode 
 *
 *  Return value:
 *    Returns a pointer to the opened file.
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

/*
 *  Function:
 *    readprbs
 *
 *  Description:
 *    Reads the problems file and returns the problem.
 *
 *  Arguments:
 *    fpprobs, pointer to the problems file
 *	  g, pointer to the graph
 *    out, pointer to the file we are writing include
 *	  modo, NULL, pointer to problem string
 *
 *  Return value:
 *    pointer to problem string
 */

char *readprbs(FILE* fpprobs, Graph *g, FILE *out, char *modo){

	fscanf(fpprobs, "%s", modo);
	fprintf(out, "\n%d %d %s ", getV(g), getE(g), modo);
	return modo;
}
