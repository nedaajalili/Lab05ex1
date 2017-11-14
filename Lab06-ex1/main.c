#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 21
typedef struct str
{
    char *word;
    int freq;
    struct str *next;
} word;

FILE *fileopen(char *,char *);
word *load1(FILE *);
word *load2(FILE *);
word *sorted(FILE *);
word *createNode();
void filter(char *);
int updatefreq(word *,char *);
void display(FILE *fout,word *);
/*word *reverse(word *);*/

int main(int argc, char *argv[])
{
    word *head;
    FILE *fin,*fout;
    int n;
    if(argc!=3)
    {
        printf("error in passing command line parameters!\n");
        exit(0);
    }

    fin=fileopen(argv[1],"r");
    fout=fileopen(argv[2],"w");
    printf("1:head insertion, 2:tail insertion, 3:sorted \n");
    scanf("%d", &n);
    if(n==1)
    {
        head=load1(fin);
        display(fout,head);
    }
    if(n==2)
    {
        head=load2(fin);
        display(fout,head);
    }
    if(n==3)
    {
        head=sorted(fin);
        display(fout,head);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
FILE *fileopen(char *fn, char *mode)
{
    FILE *fp;
    fp=fopen(fn,mode);
    if(fp==NULL)
    {
        printf("error in opening file!\n");
        exit(0);
    }
    return fp;
}
word *load1(FILE *fp)
{
    word *head,*newS;
    char tmp[MAX];
    int found;

    head=NULL;
    while(fscanf(fp,"%s",tmp)!=EOF)
    {
        filter(tmp);
        found=updatefreq(head,tmp);
        if(!found)
        {
            newS=createNode();
            newS->word=(char *)malloc((strlen(tmp)+1)*sizeof(char));
            if(newS->word==NULL)
            {
                printf("Unable to allocate memory for new string\n");
                exit(0);
            }
            strcpy(newS->word,tmp);
            newS->freq=1;
            if(head==NULL)
            {
                newS->next=NULL;
                head=newS;
            }
            else
            {
                newS->next=head;
                head=newS;
            }
        }

    }
    return head;
}
word *load2(FILE *fp)
{
    word *head,*newS,*buff;
    char tmp[MAX];
    int found;

    head=NULL;
    while(fscanf(fp,"%s",tmp)!=EOF)
    {
        filter(tmp);
        found=updatefreq(head,tmp);
        if(!found)
        {
            newS=createNode();
            newS->word=(char *)malloc((strlen(tmp)+1)*sizeof(char));
            if(newS->word==NULL)
            {
                printf("Unable to allocate memory for new string\n");
                exit(0);
            }
            strcpy(newS->word,tmp);
            newS->freq=1;
            buff=head;
            if(head==NULL)
            {
                newS->next=NULL;
                head=newS;
            }
            else
            {
                while(buff->next!=NULL)
                    buff=buff->next;
                buff->next=newS;
            }
        }

    }
    return head;
}
word *createNode()
{
    word *ptr;
    ptr=(word *)malloc(sizeof(word));
    if(ptr==NULL)
    {
        printf("error in allocation for new element!\n");
        exit(0);
    }
    return ptr;
}
void filter(char *tmp)
{
    int i;
    for(i=0; i<strlen(tmp); i++)
    {
        tmp[i]=tolower(tmp[i]);
    }
    return;
}
int updatefreq(word *head,char *wanted)
{
    int found=0;
    while(head!=NULL && !found)
    {
        if(!strcmp(head->word,wanted))
        {
            found=1;
            head->freq++;
        }
        else
        {
            head=head->next;
        }
    }
    return found;
}
void display(FILE *fout,word *head)
{
    while(head!=NULL)
    {
        fprintf(fout,"%s %d \n",head->word,head->freq);
        head=head->next;
    }
    return;
}
word *sorted(FILE *fp)
{
    word *head,*newS,*prev,*next;
    char tmp[MAX];
    int found;

    head=NULL;
    while(fscanf(fp,"%s",tmp)!=EOF)
    {
        filter(tmp);
        found=updatefreq(head,tmp);
        if(!found)
        {
            newS=createNode();
            newS->word=(char *)malloc((strlen(tmp)+1)*sizeof(char));
            if(newS->word==NULL)
            {
                printf("Unable to allocate memory for new string\n");
                exit(0);
            }
            strcpy(newS->word,tmp);
            newS->freq=1;
            if(head==NULL)
            {
                head=newS;
            }
            else
            {
                prev = NULL;
                next = head;
                while(next!=NULL && strcmp(next->word,newS->word)<0)
                {
                    prev = next;
                    next = next->next;
                }
                if(next==NULL)
                {
                    prev->next = newS;
                }
                else
                {
                    if(prev!=NULL)
                    {
                        newS->next = prev->next;
                        prev-> next = newS;
                    }
                    else
                    {
                        newS->next = head;
                        head = newS;
                    }
                }
            }
        }
    }
            return head;
            /*if(head==NULL)
            {
                newS->next=NULL;
                head=newS;
            }
            else
            {*/
            /*temp=head->next;
            prev=head;
            while(temp!=NULL && strcmp(temp->word,newS->word)<0){
                prev=temp;
                temp=temp->next;
            }
            newS->next=temp;
            prev->next=newS;

            }

            }
            return head;*/



    }

        /*word *reverse(word *head)
        {
            word *prev,*next,*curr;
            curr=head;
            prev=NULL;
            while(curr!=NULL)
            {
                next=curr->next;
                curr->next=prev;
                prev=curr;
                curr=next;
            }
            head=prev;
            return head;
        }*/
