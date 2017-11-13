#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 31
typedef struct a
{
    char *name;
    int id;
    int laps;
    float *times;
    float avg;
} athlete;

athlete *load(int *);
void List(athlete *, int);
void search(athlete *,int);
void Best(athlete *,int);
int main(void)
{
    int cmd,n;
    athlete *athletes;
    athletes=load(&n);
    do
    {
        printf("what do you want to do?\n");
        printf("1:List-2:Detail-3:Best-4:Stop \n");
        scanf("%d", &cmd);
        if(cmd==1)
            List(athletes,n);
        if(cmd==2)
            search(athletes,n);
        if(cmd==3)
            Best(athletes,n);
        if(cmd==4)
            printf("This is the end!\n");
    }
    while(cmd!=4);
    return 0;
}

athlete *load(int *n)
{
    athlete *athletes;
    FILE *fp;
    int id,laps,i,j;
    char fileName[MAX],name[MAX];
    printf("Insert file name:");
    scanf("%s",fileName);
    fp=fopen(fileName,"r");
    if(fp==NULL)
    {
        printf("error in file opening!");
        exit (0);
    }
    fscanf(fp,"%d",n);
    athletes=(athlete *)malloc(*n*sizeof(athlete));
    if(athletes==NULL)
    {
        printf("error in allocation!\n");
        exit(0);
    }
    i=0;
    while(i<*n && fscanf(fp,"%s %d %d",name,&id,&laps)!=EOF)
    {
        athletes[i].name=(char *)malloc((strlen(name)+1)*sizeof(char));
        athletes[i].times=(float *)malloc(laps*sizeof(float));
        if(athletes[i].times==NULL || athletes[i].name==NULL)
        {
            printf("error in allocation!\n");
            exit(0);
        }
        strcpy(athletes[i].name,name);
        athletes[i].id=id;
        athletes[i].laps=laps;
        athletes[i].avg=0;

        for(j=0; j<laps; j++)
        {
            fscanf(fp,"%f",&athletes[i].times[j]);
            athletes[i].avg+=athletes[i].times[j];
        }
        athletes[i].avg/=laps;
        i++;
    }
    fclose(fp);
    return athletes;
}
void List(athlete *athletes, int n)
{
    int i;
    printf("Number : %d\n",n);
    for(i=0; i<n; i++)
    {
        printf("Name:%s Id:%d Laps:%d\n", athletes[i].name,athletes[i].id,athletes[i].laps);
    }
    return;
}

void search(athlete *athletes,int n)
{
    int i,j;
    char wanted[MAX];
    printf("who do you want to know more about?\n");
    scanf("%s",wanted);
    for(i=0; i<n; i++)
    {
        if(strcmp(athletes[i].name,wanted)==0)
        {
            printf("Id:%d Laps:%d ",athletes[i].id,athletes[i].laps);
            for(j=0; j<athletes[i].laps; j++)
            {
                printf("Times:%.2f ", athletes[i].times[j]);
            }
            printf("\n");
        }
    }
    return;
}

void Best(athlete *athletes, int n){
    int i,ind,j;
    float best=1000;
    for(i=0;i<n;i++){
        if(athletes[i].avg<best){
            best=athletes[i].avg;
            ind=i;
        }
    }
    printf("Name: %s Id:%d Laps:%d Avg:%f ",athletes[ind].name,athletes[ind].id,athletes[ind].laps,athletes[ind].avg);
    printf("Times: ");
    for(j=0;j<athletes[ind].laps;j++){
        printf("%f ",athletes[ind].times[j]);
    }
    return;
}
