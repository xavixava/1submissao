#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

#define MAX_LINHA 30

int main(int argc, char **argv){
	
	Graph *g;
	int map, prob, i = 0;
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
	}void solve();

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
	
	readprbs(probfile, prob, map);
	
    g = readmaps(mapfile, prob, map);

    saida = NULL;
    saida = (char*) malloc((strlen(mapsname)+4)*sizeof(char));
	saida = strcat((strncpy(saida, mapsname, (strlen(mapsname)-5))), ".queries");

	out = Openfile(saida, "w+");

	fprintf(out, "Hello world \n");

	free(saida);

	GRAPHdestroy(g);
	
	fclose(out);
	fclose(probfile);
	fclose(mapfile);

	return 0;
}

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


void readprbs(FILE* fpprobs, int prob, int map){

    char modo[2];
    int edge1=0, edge2=0, variante=0, k;


    while(!feof(fpprobs)){

       if (fscanf(fpprobs, "%s %d %d", modo, &edge1, &edge2)==2){

           variante=1;
           printf("%s %d %d\n", modo, edge1, edge2);

        }else if(fscanf(fpprobs, "%s %d %d", modo, &edge1, &edge2)==3){


            if(!strcmp("B0",modo)){

                variante=2;
                printf("%s %d %d\n", modo, edge1, edge2);

            }else if(!strcmp("C0",modo)){

                k=edge2;
                variante=3;
                printf("%s %d %d\n", modo, edge1, edge2);

            }else if(!strcmp("D0",modo)){

                k=edge2;
                variante=4;
                printf("%s %d %d\n", modo, edge1, edge2);
            }
        }
        /* */

        if(prob==1) break;
    }

    return;
}

Graph *readmaps(FILE* fpmaps, int prob, int map){

	Graph *g;
    int n_vertices, n_arestas, countv=0, counta=0;
    float custos;
    char auxc[MAX_LINHA], *classificador;
    int edge1, edge2;

    while(!feof(fpmaps)){

		
        if(fscanf(fpmaps, "%d %d", &n_vertices, &n_arestas)==2) ;
		
		g = GRAPHinit(n_vertices);
		
        printf(" ** %d %d \n", n_vertices , n_arestas);

         while(countv!=n_vertices){

            fscanf(fpmaps, "%d %s", &edge1, auxc);


            if(!strcmp("-",auxc)){

                classificador=NULL;

            }else{

                classificador = (char*) malloc((strlen(auxc)+1)*sizeof(char));
                strcpy(classificador, auxc);
                }
			GRAPHaddV(g, edge1, classificador);
            countv++;
            printf("%d %s\n", edge1, classificador);
         }

         while(counta!=n_arestas){

            fscanf(fpmaps, "%d %d %f", &edge1, &edge2, &custos);
            counta++;
			GRAPHinsertE(g, edge1, edge2, custos);
			GRAPHinsertE(g, edge2, edge1, custos);
            printf("%d %d %f\n", edge1, edge2, custos);

         }

    if(map==0)  break;

    }
	return g;
}
