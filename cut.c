#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//functie de citire si alocare de memorie
void read(char **line, int m)
{
	char tmp[201];
	
	for (int i = 0 ;i < m; i++){
		fgets(tmp, 201, stdin);
		line[i] = (char*) malloc( strlen(tmp) * sizeof(char) + 1 );
		strcpy(line[i], tmp);
		line[i][strcspn(line[i], "\n")] = 0; //scap de \n in linie
		
	}
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 


void bubbleSort(int a[], int n) 
{ 
   for (int i = 0; i < n-1; i++)         
       for (int j = 0; j < n-i-1; j++)  
           if (a[j] > a[j+1]) 
              swap(&a[j], &a[j+1]); 
}

//transforma sirul fields in intr-un vector int v_fields
void fields_transform(char *fields, char temp_fields[101][201], int *v_fields)
{
   	int k = 0;
   	int n = 0;
   	
   	//separa fields in cuvinte dupa delimitatori 
   	//insereaza cuvintele in vectorul temporar temp_fields
	for(int i = 0; i <= strlen(fields); i++){  
	    if(fields[i] ==',' || fields[i] == '\n' || fields[i] == '\0'){
	        temp_fields[n][k] = '\0';
	        n++; 
	        k = 0;    
	    }
	    else{
	        temp_fields[n][k] = fields[i];
	        k++;
	    }
    }	

	k = 0;
	//transform cuvantul in int si il inserez in v_fields
	for (int i = 0;i < n; i++)
		v_fields[k++] = atoi(temp_fields[i]); 	
}

//desparte linia in cuvinte
//verific daca cuvantul apartine fieldului si il afisez
void isWord(char *line, char *out_del, char *del, int *v_fields, int n)
{
   	int k = 1;
   	int count = 0;
    char delim[11]; 
    int true_fields=0;
    char* tok; 
    char *aux[100]; //pastreaza tokenurile
    char *output[101]; //pastreaza cuvintele care se vor afisa la final
    strcpy(delim, del);
     
    tok = strtok(line, delim); 
  	
    while (tok != 0) { 
        aux[k++] = tok; // inserez in aux cuvantul
        tok = strtok(0, delim); 
        count++;
    } 
    
	//verific cate fielduri o sa ramana 
    for(int i = 0; i < n; i++)
		for(int j = 1; j <= count; j++)
			if(j == v_fields[i] && v_fields[i] != v_fields[i+1]) true_fields++;
	
	
	//verific daca indexul cuvantului se afla in v_fields
	// si indecsii nu se repeta
	//inserez cuvantul gasit in output
	k=0;
	for(int i = 0;i < n; i++){	
		for(int j = 1; j <= count; j++){
			if (j == v_fields[i] && v_fields[i] != v_fields[i+1]) {	
				output[k++] = aux[j];	
			}
		}			
	}
	//afisez output daca exista cuvinte ramase pe linie
	if(true_fields != 0){
		for(int i = 0; i < true_fields-1; i++){
		printf("%s", output[i]);
		printf("%s", out_del);
	}
	printf("%s", output[true_fields-1]);
	}  
	printf("\n");
	free(line);	
}

int main()
{
	char del[11];
	int n, m;
	char fields[201];
	char out_del[11];
	char *line[201];
	char temp_fields[101][201];
	int v_fields[201];
//CITIRE VAR
	fgets(del, 11, stdin);
	scanf("%d", &n);
	scanf("%s", fields);
	scanf("%s", out_del);
	scanf("%d", &m);

	getchar();
	read(line, m);
	
//TRANSFORMA char fields IN int v_fields SI LE SORTEAZA CRESCATOR
	fields_transform(fields, temp_fields, v_fields);
	bubbleSort(v_fields, n);
	
	for(int i = 0;i < m; i++){	
		isWord(line[i], out_del, del, v_fields, n);
	}

	return 0;
}