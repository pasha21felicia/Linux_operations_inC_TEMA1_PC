#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//functia de citire si alocare
void read_and_alloc(char **line, int n, char *s)
{
    char tmp[200];
    int i;
    for (i = 0; i < n; i++){
        fgets(tmp, 200, stdin);
        line[i] = (char*) malloc(strlen(tmp) * sizeof(char) + 1);
        strcpy(line[i], tmp);
    }
}

//inserez un string instr-un alt string
void strins (char *d, char *s) {
    char aux[200];
    strcpy(aux, d); // creare copie şir care începe la adresa d
    strcpy(d, s); // adauga şirul s la adresa d
    strcat(d, aux); // concatenează la noul şir vechiul şir
}

//numar aparitiile a sirului cautat in fiecare linie
int countFreq(char *line, char *s) 
{ 
    int len_s = strlen(s); 
    int len_line = strlen(line); 
    int count = 0;
   
    for (int i = 0; i < len_line; i++){  
        int j;
        for (j = 0; j < len_s; j++) 
            if (line[i+j] != s[j]) 
                break; 
        if (j == len_s){    
            count++;
            j = 0; 
            
        } 
        
    } 
    return count;
}

//gaseste indecsii aparitiei sirului pe linie
//coloreaza sirul de la indexul gasit
void color_string(char *line, char *s, int count)
{

    line = (char *) realloc(line, sizeof(char) * strlen(line) * count *10);
     
    int len_s = strlen(s); 
    int k = 0;
    int indice[100]; 
    // gasesc indexul primului caracter din sir s
    for (int i = 0; i < strlen(line); i++){  
        int j;
        for (j = 0; j < len_s; j++) 
            if (line[i+j] != s[j]) 
                break; 
        if (j == len_s){      
           j = 0;
           indice[k++]=i; //inserez indecsii in vectori
               
        }
    }
    
    //colorez sirul s la pozitia gasita in indice[i]
    for (int j = 0; j < count; j++){
        for (int i = 0; i < strlen(line); i++){
            if (i == indice[j]) {
                strins(line + i, "\e[0;31m");
            } 
            if (i == indice[j] + len_s + 7){  
                strins(line + i, "\e[m");
            }

        }
         indice[j+1] += (j+1) * 10; //updatez indicii
    }
    printf("%s", line);
    free(line);
    
}

int main()
{
    char s[31];
    int n;
    fgets(s,31,stdin);
    //sterg \n din s
    int poz = strcspn(s,"\n");
    strcpy(s + poz, "\0"); 

    scanf("%d", &n);
    char *line[n+1];

    getchar();
    read_and_alloc(line, n, s);

    int count;
    for (int i = 0; i < n; i++){
        count=countFreq(line[i], s);
        if (count!=0){
            count=countFreq(line[i], s);
            color_string(line[i], s, count);
      }          
    }
    
    return 0;
}