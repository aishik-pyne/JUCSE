#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tree
{
        char ch;
        int pos;
        int nullable;
        int fpos[5];
        int lpos[5];
        struct tree * lc;
        struct tree * rc;
}node;
int dfaa[30],df=0;
typedef struct foll
{
        int follpos[10];
        char ch;
}follpos;
follpos folltab[100];
char inpt[10];
void follow(node *);
node* alloc(char ch)
{
        node * temp;
        temp=(node *)malloc(sizeof(node));
        temp->nullable=1;
        temp->lc=NULL;
        temp->rc=NULL;
        temp->ch=ch;
        temp->fpos[0]=-1;
        temp->lpos[0]=-1;
        return temp;
}
void unio(int [],int []);
void sort(int []);
int check(int[],int);
void print_follow(int n)
{
        printf("FOLLOWPOS\n");
        printf("POS\tNAME\tFOLLOWPOS\n");
        for(int i=1; i<=n; ++i)
        {
                printf("%d\t%c\t",i,folltab[i].ch);
                int j=0;
                while(folltab[i].follpos[j]!=-1)
                {
                        printf("%d ",folltab[i].follpos[j]);
                        j++;
                }
                printf("\n");
        }
}
void print_nullable(node *root)
{
        if(root!=NULL)
        {
                print_nullable(root->lc);
                print_nullable(root->rc);
                printf("%c\t",root->ch);
                int i=0;
                while(root->fpos[i]!=-1)
                {
                        printf("%d ",root->fpos[i]);
                        i++;
                }
                printf("\t");
                i=0;
                while(root->lpos[i]!=-1)
                {
                        printf("%d ",root->lpos[i]);
                        i++;
                }
                printf("\n");
        }
}
node * create(char str[],int *l)
{
        node * nw;
        nw=alloc(str[*l]);
        if(str[*l]=='*'||str[*l]=='|'||str[*l]=='.')
        {
                if(str[*l]!='*')
                {
                        (*l)--;
                        nw->nullable=0;
                        nw->rc=create(str,l);
                }
                (*l)--;
                nw->lc=create(str,l);
        }
        else
                nw->nullable=0;
        return nw;
}
void inorder(node *root)
{
        if(root!=NULL)
        {
                inorder(root->lc);
                printf("%c",root->ch);
                inorder(root->rc);
        }
}
void create_nullable(node * root,int *pos)
{
        if(root->lc!=NULL)
                create_nullable(root->lc,pos);
        if(root->rc!=NULL)
                create_nullable(root->rc,pos);
        if(root->lc==NULL && root->rc==NULL)
        {
                root->pos=(*pos);
                root->fpos[0]=root->lpos[0]=(*pos);
                root->fpos[1]=root->lpos[1]=-1;
                folltab[*pos].ch=root->ch;
                folltab[*pos].follpos[0]=-1;
                (*pos)++;
        }
        else
        {
                if(root->ch=='|')
                {
                        unio(root->fpos,root->lc->fpos);
                        unio(root->fpos,root->rc->fpos);
                        unio(root->lpos,root->lc->lpos);
                        unio(root->lpos,root->rc->lpos);
                }
                else if(root->ch=='*')
                {
                        unio(root->fpos,root->lc->fpos);
                        unio(root->lpos,root->lc->lpos);
                }
                else if(root->ch=='.')
                {
                        if(root->lc->nullable==1)
                        {
                                unio(root->fpos,root->rc->fpos);
                        }
                        unio(root->fpos,root->lc->fpos);
                        sort(root->fpos);
                        if(root->rc->nullable==1)
                        {
                                unio(root->lpos,root->lc->lpos);
                        }
                        unio(root->lpos,root->rc->lpos);
                        sort(root->lpos);
                }
                follow(root);
        }
}
void follow(node *root)
{
        int i=0;
        if(root->ch=='*')
        {
                while(root->lpos[i]!=-1)
                {
                        unio(folltab[root->lpos[i]].follpos,root->fpos);
                        i++;
                }
        }
        else if(root->ch=='.')
        {
                while(root->lc->lpos[i]!=-1)
                {
                        unio(folltab[root->lc->lpos[i]].follpos,root->rc->fpos);
                        i++;
                }
        }
}
void unio(int arr1[],int arr2[])
{
        int i=0;
        while(arr1[i]!=-1)
                i++;
        int j=0; int k=0;
        while(arr2[j]!=-1)
        {
                for(k=0; k<i; ++k) /*<br=""> */ {
                        if(arr2[j]==arr1[k])
                                break;
                }
                if(k==i)
                {
                        arr1[i]=arr2[j];
                        i++;
                }
                j++;
        }
        arr1[i]=-1;
}
void sort(int a[]) //insertion sort
{
        int i,j,temp;
        for(i=1; a[i]!=-1; i++)
        {
                temp=a[i];
                for(j=i-1; j>=0&&temp<a[j]; j--) /* <br=""> */ a[j+1]=a[j];
                a[j+1]=temp;
        }
}
int state[10][10];
void dfa()
{
        int j=0,k=0,temp[10],i;
        temp[0]=-1;
        int nos=1;
        for( i=0; i<10; ++i)
                state[i][0]=-1;
        i=0;    int m;
        unio(state[0],folltab[1].follpos);
        while(1)
        {
                for(i=0; inpt[i]!=NULL; ++i)
                {
                        for(j=0; state[k][j]!=-1; ++j)
                        {
                                if(folltab[state[k][j]].ch==inpt[i])
                                { unio(temp,folltab[state[k][j]].follpos);  }
                        }
                        m=check(temp,nos);
                        if(m==-1)
                        {
                                unio(state[nos++],temp);
                                m=nos-1;
                        }
                        dfaa[df++]=m;
                        temp[0]=-1;
                }
                if(k==nos-1)
                        break;
                k++;
        }
}
int check(int temp[],int nos)
{
        int i;
        for(i=0; i<nos; ++i)   {
                int j;
                for( j=0; temp[j]!=-1; ++j)
                {
                        if(temp[j]!=state[i][j])
                                break;
                }
                if(temp[j]==-1 && state[i][j]==-1)
                        return i;
        }
        return -1;
}
void display_dfa() //displaying DFA table
{
        int i,j,k;
        printf("\nDFA TABLE\n ");
        for(i=0; inpt[i]!=NULL; i++)
                printf("\t%c",inpt[i]);
        for(j=0; j<(df/i); j++)
        {
                printf("\n%c\t",j+65);
                for(k=j*i; k<(j*i)+i; k++)
                        printf("%c\t",dfaa[k]+65);
        }
        // getch();
}
int main()
{
        // clrscr();
        char str[50];
        inpt[0]=NULL;
        printf("Enter the postfix expression\n");
        scanf("%s",str);
        node * root;
        int l;
        strcat(str,"#.\0");
        l=strlen(str);
        l--;
        int j=0;
        for(int i=0; i<l-1; ++i)  {
                j=0;
                while(inpt[j]!=NULL)
                {
                        if(inpt[j]==str[i])
                                break;
                        j++;
                }
                if(inpt[j]!=str[i] && str[i]!='|' && str[i]!='*' && str[i]!='.')
                {
                        inpt[j]=str[i];
                        inpt[j+1]=NULL;
                }
        }
        int pos=1;
        root=create(str,&l);
        create_nullable(root,&pos);
        printf("NULLABLE TABLE\nElement\tFPOS\tLPOS\n");
        print_nullable(root->lc);
        print_follow(pos-2);
        dfa();
        display_dfa();
        printf("\n");
        return 0;
}
