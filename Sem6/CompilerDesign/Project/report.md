

## Regular Expressions for identifying
1. Integers
2. Floats
3. Identifiers   

## Regular Expressions to DFA (Directly)

Modules required
* Parse Tree  
* First Pos  
* Last Pos  
* Follow Pos

#### Parse tree

```cpp
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
```

#### Follow pos

```cpp
// Datastructure
typedef struct foll
{
        int follpos[10];
        char ch;
}follpos;
// Followpos of a node
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
```

#### Some of the auxillaxry functions used:

```cpp
void unio(int [], int []); // Union of two arrays
void sort(int []); // Sorting an array
node* alloc(char ch); // Initialize a new node with char ch
void display_dfa(); //displaying DFA table

```
