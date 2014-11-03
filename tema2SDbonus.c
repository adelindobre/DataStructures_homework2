#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
	char *val;
	int contor;
	int contor2;
	struct nod *next;
	struct nod **prev;
}nod;

typedef struct mark
{
	char *val;
	int nrApar;
}mark;


int aparitiiBonus(char *curent)
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
		if (strcmp(p,curent)==0)
			contor++;
		fscanf(fisier,"%s",p);
	}
	fclose(fisier);
	free(p);
	return contor;
}

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

void initTree(nod **tree, char *p1, char *p2, int *elem, mark **dup ,int *elemdup)
{
	int i;
	tree[*elem]=(nod*)malloc(sizeof(nod));
	tree[(*elem)+1]=(nod*)malloc(sizeof(nod));	
	
	tree[*elem]->val=strdup(p1);
	tree[(*elem)+1]->val=strdup(p2);

	tree[*elem]->contor2=aparitiiBonus(p1);
	
	dup[*elemdup]=(mark*)malloc(sizeof(mark));
	dup[*elemdup]->nrApar=tree[*elem]->contor2;
	dup[*elemdup]->val=strdup(p1);
	(*elemdup)++;

	
	tree[*elem]->contor=aparitii(p1);
	tree[*elem]->prev=(nod**)calloc(tree[*elem]->contor,sizeof(nod*));
	
	for (i=0;i<tree[*elem]->contor;i++)
		tree[*elem]->prev[i]=NULL;

	tree[(*elem)+1]->contor2=1;	
	tree[(*elem)+1]->contor=aparitii(p2);
	tree[(*elem)+1]->prev=(nod**)calloc(tree[(*elem)+1]->contor,sizeof(nod*));

	for (i=0;i<tree[(*elem)+1]->contor;i++)
		tree[(*elem)+1]->prev[i]=NULL;

	tree[*elem]->next=tree[(*elem)+1];
	tree[(*elem)+1]->prev[0]=tree[*elem];
	tree[(*elem)+1]->next=NULL;
	*elem=*elem+2;
	
}

void insertTree(nod **tree, char *p1, char *p2, int *elem, mark **dup, int *elemdup)
{
	int flag=0,i,j,k,gasit=0;


	for (k=0;k<*elemdup;k++)
		if (strcmp(dup[k]->val,p1)==0)
			if (dup[k]->nrApar!=1)
			{
				gasit=1;
				break;
			}
	
	for(i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p1)==0)
                {
          		flag=1;
			break;
		}
	if (gasit!=0)
		for(j=0;j<*elem;j++)
                	if (strcmp(tree[j]->val,p1)==0)
				if (dup[k]->nrApar==tree[j]->contor2)
				{
					tree[*elem]=(nod*)malloc(sizeof(nod));
					tree[*elem]->val=strdup(p1);
					tree[*elem]->contor2=dup[k]->nrApar-1;
					(dup[k]->nrApar)--;
					tree[*elem]->contor=1;
					tree[*elem]->prev=(nod**)calloc(tree[*elem]->contor,sizeof(nod*));
				
					for (k=0;k<tree[*elem]->contor;k++)
						tree[*elem]->prev[k]=NULL;
					i=*elem;
					*elem=*elem+1;
					break;
				}		
	if (flag==0)
        {
                tree[*elem]=(nod*)malloc(sizeof(nod));
                tree[*elem]->val=strdup(p1);
		tree[*elem]->contor2=aparitiiBonus(p1);
		if (tree[*elem]->contor2!=1)
		{
			dup[*elemdup]=(mark*)malloc(sizeof(mark));
			dup[*elemdup]->val=strdup(p1);
			dup[*elemdup]->nrApar=tree[*elem]->contor2;
			(*elemdup)++;
		}
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
		tree[*elem]->contor2=1;
                tree[*elem]->contor=aparitii(p2);
		tree[*elem]->next=NULL;
                tree[*elem]->prev=(nod**)calloc(tree[*elem]->contor,sizeof(nod*));

		for (k=0;k<tree[*elem]->contor;k++)
                	tree[*elem]->prev[k]=NULL;	

                j=*elem;
                *elem=*elem+1;
        }
	tree[i]->next=tree[j];
        for (k=0;k<tree[j]->contor;k++)
                if ((tree[j])->prev[k]==NULL)
                        break;
        tree[j]->prev[k]=tree[i];
}

char* isScommand(nod **tree, char *p1, char *p2, int *elem)
{
        nod *aux;
        char *mesaj="false",flag=0;
        int i;
        for (i=0;i<*elem;i++)
	{
                if (strcmp(tree[i]->val,p1)==0)
         	{
			if (tree[i]->contor2==1)
				flag=1;
        		aux=tree[i]->next;	
        		while(aux!=NULL)
        		{
                		if (strcmp(aux->val,p2)==0)
                		{
                        		mesaj="true";
                        		return mesaj;
                		}
                		aux=aux->next;
        		}
		}
		if (flag==1)	
			break;	
	}
return mesaj;
}

char* Ecommand(nod **tree, char *p1, char *p2, int *elem)
{
        nod *aux1;
        nod *aux2;
        char *mesaj="false";
        int i,j,flag1=0,flag2=0;

        for (i=0;i<*elem;i++)
	{
                if (strcmp(tree[i]->val,p1)==0)
		{
			if (tree[i]->contor2==1)
				flag1=1;
			aux1=tree[i];
			while (aux1->next!=NULL)
				aux1=aux1->next;
			for(j=0;j<*elem;j++)
			{
				if (strcmp(tree[j]->val,p2)==0)
				{
					if (tree[j]->contor2==1)
						flag2=1;
					
					aux2=tree[j];
				
					while(aux2->next!=NULL)
						aux2=aux2->next;
				
					if (strcmp(aux1->val,aux2->val)==0)
					{
						mesaj="true";
						return mesaj;
					}
				}
				if (flag2==1)
					break;
			}			
		}
		flag2=0;
		if (flag1==1)
			break;
	}	
return mesaj;
}


void sort (char **v, int *cont)
{
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
        int i,cont=0;
        char **v;
        nod *aux;
        v=(char**)malloc(10000*sizeof(char*));
        for (i=0;i<*elem;i++)
                if (strcmp(tree[i]->val,p)==0)
                        break;
        aux=tree[i];
        S2command(aux,v,&cont);

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
        int i;
        for (i=0;i<cap->contor;i++)
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

void Dcommand(nod **tree, char *p, int *elem, FILE *fisier)
{
        int i,cont=0, flag=0;
        char **v;
        nod *aux;
        v=(char**)malloc(10000*sizeof(char*));
        for (i=0;i<*elem;i++)
	{
                if (strcmp(tree[i]->val,p)==0)
                {
			if (tree[i]->contor2==1)
				flag=1;
	
        		aux=tree[i]->next;
        		while (aux!=NULL)
        		{
                		v[cont++]=strdup(aux->val);
                		aux=aux->next;
        		}
			sort(v,&cont);
		}
		if (flag==1)
			break;
	}
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
	int i,j,N,elem,contCommand,contorS=0, elemdup=0;
	elem=0;
	nod **tree;
	mark **dup;
	
	dup=(mark**)calloc(100,sizeof(mark*));
	tree=(nod**)calloc(10000,sizeof(nod*));	

	FILE *fisier, *fout;

        fisier=fopen("data.in","r");
        fout=fopen("data.out","w");

        p1=(char*)malloc(30*sizeof(char));
        p2=(char*)malloc(30*sizeof(char));
        comanda=(char*)malloc(30*sizeof(char));      

        fscanf(fisier,"%s",p1);
        N=atoi(p1);

        fscanf(fisier,"%s",p1);
        fscanf(fisier,"%s",p2);
	
        initTree(tree,p1,p2,&elem,dup, &elemdup);
	for(i=0;i<N-1;i++)
        {
                fscanf(fisier,"%s",p1);
                fscanf(fisier,"%s",p2);
                insertTree(tree,p1,p2,&elem,dup,&elemdup);
        }
	
	fscanf(fisier,"%s",p1);
	contCommand=atoi(p1);

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
	for (i=0;i<elemdup;i++)
	{
		free(dup[i]->val);
		free(dup[i]);
	}
	free(dup);
	fclose(fisier);
	fclose(fout);
return 0;	
}
