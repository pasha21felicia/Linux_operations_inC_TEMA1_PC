#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//fucntia de citire a matricei si alocare/realocare mem
void read(int cap, int nl, int *v_col, int **mat){
	int ncol;
	int nr;
	int k = 0;
	
	for(int i = 0; i < nl; i++){
		ncol = 0;
		mat[i] = malloc(cap * sizeof(int));

		scanf("%d", &nr);
		//adaug nr in matrice si nr coloanele 
		while (nr != 0){
			if (cap == ncol){
				cap += 3;
				mat[i] = realloc(mat[i], cap * sizeof(int));
			}
			mat[i][ncol++] = nr;
			scanf("%d", &nr);
		}
		v_col[k++] = ncol; //adaug nr de coloane pe linie intr-un vector

	}
}

//functie care calculeaza media pe fiecare linie
void media_line(int nl, int **mat, int *v_col, float * medii){

	float media;
	int sum = 0;
	int k = 0;

	for (int aux = 0; aux < nl; aux++){
		sum = 0;
		media = 0;
		for (int i = 0; i < nl; i++){
			for (int j = 0; j < v_col[aux]; j++)
				if (aux == i){
					sum += mat[i][j];
				}
		}
		media = (float)sum / v_col[aux];   //calculez media pe fiecare linie
		medii[k++] = media; //adaug media de pe linie intr-un vector medii[]

	}
	
}

//functie care copie mediile calculate intr-un vector special
//numit medii_nesortate
void copy_medii(int nl, float *medii_nesortate, float *medii)
{
	for(int i = 0; i < nl; i++)
		medii_nesortate[i] = medii[i];
}

//sortare
void swap(float *xp, float *yp) 
{ 
    float temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 


void bubbleSort(float a[], int n) 
{ 
    
   for (int i = 0; i < n-1; i++)         
       for (int j = 0; j < n-i-1; j++)  
           if (a[j] < a[j+1]) 
              swap(&a[j], &a[j+1]); 
} 

//functie ce calculeaza indicele la care s-a aflat media nesortata 
//inainte de a fi sortata
void indici(int nl, float *medii_nesortate, float *medii, int *indice)
{
	int k = 0;
	int count = 0;
	for(int i = 0; i < nl; i++){
		for(int j = 0; j < nl; j++){
			if (medii_nesortate[j] == medii[i] && medii[i+1] != medii[i])
				indice[k++] = j;
		}
	}

}

//functie care printeaza mediile si liniile 
void print(int nl, float *medii, int *indice, int **mat, int *v_col)
{
	for (int aux = 0; aux < nl; aux++){
		printf("%-10.3f", medii[aux]);
		for(int i = 0; i < nl; i++){
			for (int j = 0; j < v_col[indice[aux]]-1; j++){
				if (indice[aux] == i)
					printf("%d ", mat[i][j]);
			}
			if(indice[aux] == i)
					printf("%d", mat[i][v_col[indice[aux]]-1]);
		}
		printf("\n");
		//free(mat[i]);
	}
	
}
int main()
{
	int nl, cap=3;
	scanf("%d", &nl);
	int **mat = (int **)malloc(nl * sizeof(int *));

//DECLARARE VECTORI UTILIZATI
	int v_col[nl+1];
	float medii[nl+1];
	float medii_nesortate[nl+1];
	int indice[nl+1];
	
	read(cap, nl, v_col, mat);
	media_line(nl, mat, v_col, medii);
	copy_medii(nl, medii_nesortate, medii);
	bubbleSort(medii, nl);
	indici(nl, medii_nesortate, medii, indice);
	print(nl, medii, indice, mat, v_col);

	for(int i = 0; i < nl; i++)
			free(mat[i]);
	
	free(mat);

	return 0;
}