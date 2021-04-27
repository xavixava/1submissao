#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "graph.h"

FILE *Openfile(char *name, char *mode);

char *readprbs(FILE* fpprobs, Graph *g, FILE *out, char *modo);

/******************************************************************************
 * CreateOutputNameX0 ()
 *
 * Arguments: filename - name of file with extension
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: creates filename for output (mode X0)
 ******************************************************************************/
 
char *CreateOutputNameX0(char *filename)
{
	char *ftraveler, *ze;
	ze = NULL;
	ze = (char*) malloc((strlen(filename)+4)*sizeof(char));
	ze = strcpy(ze, filename);
	ftraveler = strrchr(ze, '.');
	*ftraveler = '\0';
	strcat(ze, ".queries");
	return ze;
}

int main(int argc, char **argv){
	
	Graph *g;
	int map=0, prob=0, i = 0, l=0, edge1=0, edge2=0, scan=0, v, a;
	char *probsname = argv[2], *mapsname = argv[3], *modo, *saida;
	FILE *mapfile, *probfile, *out;
	double b;
	
	if (argc!=4) exit(1);
	
	modo = (char*) malloc(3*sizeof(char));
	modo[0] = '\0';

	g = NULL;

	switch(argv[1][2]){
		case 'o':
			prob=0;
		break;
		case'a':
			prob=1;
		break;
	}
	switch(argv[1][3]){
		case 'o':
			map=0;
		break;
		case'a':
			map=1;
		break;
	}

	while (i <= (strlen(probsname)-6)){ /*verificação da extensão do ficheiro prbs(possivelmente desnecessário) */
	if(i == (strlen(probsname)-6)){
			if(probsname[i] != '.' || probsname[i+1] != 'p' || probsname[i+2] != 'r' || probsname[i+3] != 'b' || probsname[i+4] != 's' || probsname[i+5] != '1') {
				exit(1);
			}
		}
		i++;
	}

	i=0;
	while (i <= (strlen(mapsname)-5)){ /* verificação da extensão do ficheiro maps(possivelmente desnecessário) */
		if(i == (strlen(mapsname)-5)){
			if(mapsname[i] != '.' || mapsname[i+1] != 'm' || mapsname[i+2] != 'a' || mapsname[i+3] != 'p' || mapsname[i+4] != 's') {
				exit(1);
			}
		}
		i++;
	}

    mapfile = Openfile(mapsname, "r");
	probfile = Openfile(probsname, "r");
	
	saida=CreateOutputNameX0(mapsname);
	
	out = Openfile(saida, "w+");
	
	fprintf(out, "%s %s %s\n", argv[1], argv[2], argv[3]);
	
	free(saida);


	if ((map==1) && (prob==1)){
		do{
			g = readmaps(mapfile);
			v = getV(g);
			a = getE(g);
			if(g==NULL)break;
			do{
				modo = readprbs(probfile, g, out, modo);
				switch(modo[0]){
				case 'D':
					scan=fscanf(probfile, " %d %d", &edge1, &edge2);
					if(scan!=2)break;
					if((edge1<=0)||(edge1 > v)){
						l=-1;
						}
					else
					{
						if((edge2>=0)){
						l = modoD0(g, edge1, edge2);
						}
						else{
						l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", v, a, modo, edge1, edge2, l);
				break;
				case 'A':
					scan=fscanf(probfile, " %d", &edge1);
					if (scan!=1)break;
						l = modoA0(g, edge1);
						fprintf(out, "\n%d %d %s %d %d\n", v, a, modo, edge1, l);	
				break;
				case 'B':
					scan=fscanf(probfile, " %d %d", &edge1, &edge2);
					if(scan!=2)break;
					b = modoB0(g, edge1, edge2);
					if(b==-1){
						fprintf(out, "\n%d %d %s %d %d -1\n", v, a, modo, edge1, edge2);
                    }else{
						fprintf(out, "\n%d %d %s %d %d %.2lf\n", v, a, modo, edge1, edge2, b);
                    }
				break;
				case 'C':
					scan=fscanf(probfile, " %d %d", &edge1, &edge2);
					if(scan!=2)break;
					if((edge1<=0)||(edge1 > v))l=-1;
					else
					{
						if(edge2>=0){
							l = modoC0(g, edge1, edge2);
						}
						else{
							l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", v, a, modo,edge1, edge2, l);
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
			v = getV(g);
			a = getE(g);
			if(prob!=-1)modo = readprbs(probfile, g, out, modo);
			if((feof(probfile)!=0)||(prob == 0))prob = -1;
			switch(modo[0]){
				case 'D':
					scan=fscanf(probfile, " %d %d", &edge1, &edge2);
					if(scan!=2)break;
					if((edge1<=0)||(edge1 > v)){
						l=-1;
						}
					else
					{
						if((edge2>=0)){
						l = modoD0(g, edge1, edge2);
						}
						else{
						l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", v, a, modo, edge1, edge2, l);
				break;
				case 'A':
					scan=fscanf(probfile, " %d", &edge1);
					if(scan!=1)break;
					l = modoA0(g, edge1);
					fprintf(out, "\n%d %d %s %d %d\n", v, a, modo, edge1, l);
				break;
				case 'B':
					scan=fscanf(probfile, " %d %d", &edge1, &edge2);
					if(scan!=2)break;
					b = modoB0(g, edge1, edge2);
					if(b==-1){
						fprintf(out, "\n%d %d %s %d %d -1\n", v, a, modo, edge1, edge2);
                    }else{
						fprintf(out, "\n%d %d %s %d %d %.2lf\n", v, a, modo, edge1, edge2, b);
                    }
				break;
				case 'C':
					scan=fscanf(probfile, " %d %d", &edge1, &edge2);
					if(scan!=2)break;
					if((edge1<=0)||(edge1 > v))l=-1;
					else
					{
						if(edge2>=0){
							l = modoC0(g, edge1, edge2);
						}
						else{
							l = 0;
						}
					}
					fprintf(out, "\n%d %d %s %d %d %d\n", v, a, modo,edge1, edge2, l);
				break;
			}
			
			if (g != NULL)GRAPHdestroy(g);
			if(map==0)map = -1;
		}while((map!=-1) || (prob!=-1));
	}
	
	if(g != NULL)GRAPHdestroy(g);
	
	fprintf(out, "\n");
	
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
       exit(0);
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

	int k;
	k=fscanf(fpprobs, "%s", modo);
	if(k<=0)modo[0]='z';
	return modo;
}
