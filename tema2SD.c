#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	Ideea pe care am implementat-o in tema a fost aceea a creari unui vector de adrese,
in care retin adresa fiecarui nod din arbore. Apoi cu ajutorul functiei initTree si insertTree
creez legaturile dintre aceste noduri, practic creez arborii in sine.
	Ideea vectorului de adrese este aceea ca permite localizarea unui nod in cadrul arborilor creati
 mult mai usor, iar acest avantaj este folosit in cadrul comenzilor isS, E, S si D, atunci cand trebuie 
 identificata pozitia nodurilor date ca argument in cadrul arborilor. 	
*/

/* 	strucura pentru definirea unui nod din arbore contine un pointer spre nodul copil (campul next)
 si un vector de pointeri alocati dinamic (prev) in functie de cati parinti poate avea un nod. In campul 
 contor, este retinut numarul de parinti pentru fiecare nod in parte.
*/
typedef struct nod
{
	char *val;
	int contor;
	struct nod *next;
	struct nod **prev;
}nod;
// Functia "aparitii" numara cati parinti are un nod dat ca argument
int aparitii(char *curent)
{
        FILE *fisier;
        char *p;
        int n,i,contor=0;
        fisier=fopen("data.in","r");
        p=(char*)malloc(30*sizeof(char));
        fscanf(fisier,"%s",p);
        n=atoi(p);
        for (i=0;i<n;i++)
        {
                fscanf(fisier,"%s",p);
                fscanf(fisier,"%s",p);
                if (strcmp(p,curent)==0)
                        contor++;
        }
	if (contor==0)
		contor=1;
        fclose(fisier);
        free(p);
        return contor;
}
/*
	Cu functia initTree, initializez vectorul de adrese cu primele doua noduri din fisierul de intrare.
	Apoi, construiesc legaturile dintre aceste noduri.
*/
void initTree(nod **tree, char *p1, char *p2, int *elem)
{
	int i;
	tree[*elem]=(nod*)malloc(sizeof(nod));
	tree[(*elem)+1]=(nod*)malloc(sizeof(nod));	
	
	tree[*elem]->val=strdup(p1);
	tree[(*elem)+1]->val=strdup(p2);
	tree[*elem]->next=tree[(*elem)+1];
	tree[*elem]->contor=aparitii(p1);
	tree[*elem]->prev=(nod**)calloc(tree[*elem]->contor,sizeof(nod*));
	
	for (i=0;i<tree[*elem]->contor;i++)
		tree[*elem]->prev[i]=NULL;
	
	tree[(*elem)+1]->contor=aparitii(p2);
	tree[(*elem)+1]->prev=(nod**)calloc(tree[(*elem)+1]->contor,sizeof(nod*));

	for (i=0;i<tree[(*elem)+1]->contor;i++)
		tree[(*elem)+1]->prev[i]=NULL;

	tree[(*elem)+1]->prev[0]=tree[*elem];
	tree[(*elem)+1]->next=NULL;
	*elem=*elem+2;
	
}
//Cu ajutorul functie insertTree, inserez urmatoarele noduri in vectorul de adrese "tree",
//si creez legaturile intre aceste noduri
	
void insertTree(nod **tree, char *p1, char *p2, int *elem)
{
	int flag=0,i,j,k;
	
	for(i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p1)==0)
                {
                        flag=1;
                        break;
                }
	// flag e un indicator pentru a verifica daca nodul a fost deja introdus sau nu.
	if (flag==0)
        {
                tree[*elem]=(nod*)malloc(sizeof(nod));
                tree[*elem]->val=strdup(p1);
                tree[*elem]->contor=aparitii(p1);
		tree[*elem]->prev=(nod**)calloc(tree[*elem]->contor,sizeof(nod*));

		for (k=0;k<tree[*elem]->contor;k++)     
                	tree[*elem]->prev[k]=NULL;

                i=*elem;
                *elem=*elem+1;
        }
	flag=0;
	for (j=0;j<*elem;j++)
                if (strcmp(tree[j]->val,p2)==0)
                {
                        flag=1;
                        break;
                }
        if (flag==0)
        {
                tree[*elem]=(nod*)malloc(sizeof(nod));
                tree[*elem]->val=strdup(p2);
                tree[*elem]->contor=aparitii(p2);
		tree[*elem]->next=NULL;
                tree[*elem]->prev=(nod**)calloc(tree[*elem]->contor,sizeof(nod*));

		for (k=0;k<tree[*elem]->contor;k++)
                	tree[*elem]->prev[k]=NULL;	

                j=*elem;
                *elem=*elem+1;
        }
	//crearea legaturilor
	tree[i]->next=tree[j];
	// Localizez primul element din vectorul prev, ce nu contine adresa niciunui nod
	// pentru a face o noua legatura.
        for (k=0;k<tree[j]->contor;k++)
                if ((tree[j])->prev[k]==NULL)
                        break;
        tree[j]->prev[k]=tree[i];
}
// 	Cum am spus si la inceput, in cadrul comenziilor ce trebuie implementate, 
// ma folosesc de vectorul de adrese ce pointeaza spre nodurile din arbore, pentru a 
// localiza argumentele mai usor.
 
char* isScommand(nod **tree, char *p1, char *p2, int *elem)
{
        nod *aux;
        char *mesaj="false";
        int i;
        for (i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p1)==0)
                        break;
	//dupa ce am gasit nodul, ma plimb pe legaturile acestuia si 
	// testez conditia din cerinta
        aux=(tree[i])->next;	
        while(aux!=NULL)
        {
                if (strcmp(aux->val,p2)==0)
                {
                        mesaj="true";
                        break;
                }
                aux=aux->next;
        }
return mesaj;
}

char* Ecommand(nod **tree, char *p1, char *p2, int *elem)
{
	/*	Ca si la comanda isS, la fel am procedat si pentru comanda E.
		Variabilele aux1 si aux2 retin argumentele comenzii, si pentru
	fiecare in parte ma plimb pe legaturile next (campul next din structura 
	e folosit pentru a pointa spre nodurile fiu, iar prev spre nodurile parinte) 
	pentru a identifica nodul de pe ultimul nivel.
	*/ 
        nod *aux1;
        nod *aux2;
        char *mesaj="false";
        int i,j;

        for (i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p1)==0)
                        break;
        aux1=tree[i];	

        while(aux1->next!=NULL)
                aux1=aux1->next;

        for (i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p2)==0)
                        break;
        aux2=tree[i];

        while(aux2->next!=NULL)
                aux2=aux2->next;

        if (strcmp(aux1->val,aux2->val)==0)
                mesaj="true";
        else
                mesaj="false";
return mesaj;
}

void sort (char **v, int *cont)
{

	// Pentru sortarea alfabetica, am folosit Bubble Sort.
        char aux[100];
        int trecere=0,schimbat,i;
        trecere=0;
        do
        {
                schimbat=0;
                trecere++;
                for (i=0;i<*cont-trecere;i++)
                        if (strcmp(v[i],v[i+1])>0)
                        {
                                strcpy(aux,v[i]);
                                strcpy(v[i],v[i+1]);
                                strcpy(v[i+1],aux);
                                schimbat=1;
                        }
        } while (schimbat);
}

void S1command(nod **tree,char *p,int *elem,FILE *fisier)
{
	/* Stramosii unui nod ii retin intr-un vector de string-uri 
	alocat dinamic. */
        int i,cont=0;
        char **v;
        nod *aux;
        v=(char**)malloc(10000*sizeof(char*));
        for (i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p)==0)
                        break;
        aux=tree[i];
        S2command(aux,v,&cont);
	/* 	Dupa ce am retinut toti stramosii unui nod intr-un vector, 
	sortez vectorul in ordine alfabetica cu funtia "sort".		
	*/ 
        sort(v,&cont);

        fprintf(fisier,"%d\n",cont);
        for (i=0;i<cont;i++)
                fprintf(fisier,"%s\n",v[i]);
       

        for(i=0;i<cont;i++)
                free(v[i]);
        free(v);
}

int S2command(nod *cap, char **v, int *cont)
{
	/* cautarea stramosilor se face prin parcurgerea recursiva a legatuirlor prev, pentru 
	fiecare nod in parte */
        int i;
        for(i=0;i<cap->contor;i++)
        {
                if (cap->prev[i]!=NULL)
                {
                        v[(*cont)++]=strdup(cap->prev[i]->val);
                        S2command(cap->prev[i],v,cont);
                }
                else
                        return;
        }
}
/* 	Pentru afisarea descendentilor unui nod, localizez pozitia nodului in cadrul 
 arborelui si parcurg legaturile next. Conditia de oprire este aceaa ca nodul vizitat sa nu 
 pointeze spre NULL. */
void Dcommand(nod **tree, char *p, int *elem, FILE *fisier)
{
        int i,cont=0;
        char **v;
        nod *aux;
        v=(char**)malloc(10000*sizeof(char*));
        for (i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p)==0)
                        break;
        aux=tree[i]->next;
        while (aux!=NULL)
        {
                v[cont++]=strdup(aux->val);
                aux=aux->next;
        }
	sort(v,&cont);

        fprintf(fisier,"%d\n",cont);
        for (i=0;i<cont;i++)
                fprintf(fisier,"%s\n",v[i]);
  
	for (i=0;i<cont;i++)
		free(v[i]);
	free(v);

}



int main()
{
	char *p1,*p2,*comanda,*mesaj;
	int i,j,N,elem,contCommand,contorS=0;
	elem=0;
	nod **tree;
	
	tree=(nod**)calloc(20000,sizeof(nod*));	

	FILE *fisier, *fout;

        fisier=fopen("data.in","r");
        fout=fopen("data.out","w");

        p1=(char*)malloc(30*sizeof(char));
        p2=(char*)malloc(30*sizeof(char));
        comanda=(char*)malloc(30*sizeof(char));      

        fscanf(fisier,"%s",p1);
        N=atoi(p1);
	// In variabila N, retin numarul de relatii parinte fiu din fisierul de intrare.
        fscanf(fisier,"%s",p1);
        fscanf(fisier,"%s",p2);
	// Pentru prima linie, inserarea o fac cu o functie separata.
        initTree(tree,p1,p2,&elem);
	for(i=0;i<N-1;i++)
        {
                fscanf(fisier,"%s",p1);
                fscanf(fisier,"%s",p2);
                insertTree(tree,p1,p2,&elem);
        }
	
	fscanf(fisier,"%s",p1);
	contCommand=atoi(p1);
	// In variabila contCommand, retin numarul de comenzi.
	for (i=0;i<contCommand;i++)
	{
		fscanf(fisier,"%s",comanda);
		
		if (strcmp(comanda,"isS")==0)
		{
			fscanf(fisier,"%s",p1);
                        fscanf(fisier,"%s",p2);
			mesaj=isScommand(tree,p1,p2,&elem);
			fprintf(fout,"%s\n",mesaj);
                }
		if (strcmp(comanda,"E")==0)
                {
                        fscanf(fisier,"%s",p1);
                        fscanf(fisier,"%s",p2);

                        mesaj=Ecommand(tree,p1,p2,&elem);
                        fprintf(fout,"%s\n",mesaj);
		}
		if (strcmp(comanda,"S")==0)
                {
                        fscanf(fisier,"%s",p1);
                        S1command(tree,p1,&elem,fout);
                }
                if (strcmp(comanda,"D")==0)
                {
                        fscanf(fisier,"%s",p1);
                        Dcommand(tree,p1,&elem,fout);
                }
	}
	// Eliberare memorie
	free(p1);
	free(p2);
	free(comanda);
	for (i=0;i<elem;i++)
	{
		free(tree[i]->val);
		free(tree[i]->prev);
		free(tree[i]);
	}
	free(tree);
	fclose(fisier);
	fclose(fout);
return 0;	
}
