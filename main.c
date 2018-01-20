#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define MAXLEN 200
#define MAXWIDTH 200

typedef struct node{
    int x;
    int y;
    struct node *next;
    }Node;

int m=0,n=0,stacklen=0;
int maze[MAXLEN][MAXWIDTH];
//int maze1[3][4]={{0,0,0,1},{1,1,0,1},{1,1,1,0}};
bool isempty()
{
    if(stacklen)
        return false;
    else
        return true;
    }

Node* push_stack(Node* head,int x,int y)
{
    Node *temp,*ini;
    if(!head)
    {
     head=(Node*)malloc(sizeof(Node));
     head->x=x;
     head->y=y;
     head->next=NULL;
     stacklen+=1;
     return head;
        }
    else{
       ini=head;
       while(head->next)
      {
       head=head->next;
        }

    temp=(Node*)malloc(sizeof(Node));
    temp->x=x;
    temp->y=y;
    temp->next=NULL;
    head->next=temp;
    stacklen+=1;
    return ini;
   }

    }

Node* pop_stack(Node* ptr,int* x ,int *y) {
    Node *tmp,*ini;
    if(!ptr)
    {    printf("ptr is not valid\n");
         exit(-1);
    }
    else if(!ptr->next)
    {
        *x=ptr->x;
        *y=ptr->y;
        free(ptr);
        stacklen-=1;
        return NULL;
        }
    else
    {
       ini=ptr;
        while(ptr->next)
      {

        tmp=ptr;
         ptr=ptr->next;
        }

        *x=ptr->x;
        *y=ptr->y;
        tmp->next=ptr->next;
        free(ptr);
        stacklen-=1;
        return ini;
    }

    }


void top_stack(Node* ptr,int* x ,int *y) {

        if(!ptr)
        {    printf("ptr is not valid\n");
             exit(-1);
        }
        else if(!ptr->next)
        {
            *x=ptr->x;
            *y=ptr->y;
            return;
            }
        else
        {
            while(ptr->next)
          {
             ptr=ptr->next;
            }

            *x=ptr->x;
            *y=ptr->y;
            return;

        }
        }





bool check_in_path(Node* ptr,int x,int y) {
   printf("begin to check %d ,%d in path or not\n",x,y);
   while(ptr)
   {
    if(ptr->x==x && ptr->y==y)
    { printf("%d,%d in the path\n",x,y);
      return true;}
    ptr=ptr->next;
       }

   printf("%d,%d not in the path\n",x,y);
   return false;

    }

void initmaze(int m,int n)
{
  int number;
  srand((unsigned)time(NULL));
  for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
      {
         number=rand()%100;
         if(number>30)
             maze[i][j]=0;
         else
             maze[i][j]=1;

          }
          maze[0][0]=0;
          maze[m-1][n-1]=9;
          printf("maze initialize is done\n");
    }

    void showpath(Node *ptr)
    {
      int x,y;
      if(!ptr)
      {
          printf("path is empty\n");
          }
      else{
      while(ptr)
      {   x=ptr->x;
          y=ptr->y;
          printf("(%d,%d) ==> ",x,y);
          ptr=ptr->next;
          }
          putchar('\n');
      }
      printf("showpath func ended well \n");
    }


int pass(Node* ptr,int i,int j)
{
  printf("show path before search,begin to check %d,%d ,its value is %d\n",i,j,maze[i][j]);
  showpath(ptr);
  printf("m:%d,n:%d\n",m,n);
  if(maze[i][j]==9)
     return maze[i][j];
  if( j<n-1 && maze[i][j+1]!=1 && maze[i][j+1]!=7 && !check_in_path(ptr,i,j+1))
      maze[i][j]=2;
  else if(i<m-1 && maze[i+1][j]!=1 && maze[i+1][j]!=7 && !check_in_path(ptr,i+1,j))
      maze[i][j]=3;
  else if(j>0 && maze[i][j-1]!=1 && maze[i][j-1]!=7 && !check_in_path(ptr,i,j-1))
      maze[i][j]=4;
  else if( i>0 && maze[i-1][j]!=1 && maze[i-1][j]!=7 && !check_in_path(ptr,i-1,j))
      maze[i][j]=5;
  else
    {
      printf("block %d,%d\n",i,j);
      maze[i][j]=7;
}
  printf("return with %d\n",maze[i][j]);
  return maze[i][j];

    }

void setpath(Node *ptr)
{
 if(!ptr)
 {
     printf("no path found\n");
     }
 else{
 while(ptr)
 {
     maze[ptr->x][ptr->y]=7;
     ptr=ptr->next;
     }
 }
}



void drawmaze()
{
   printf("begin to draw maze\n");
   for(int i=0;i<m;i++)
    {   for(int j=0;j<n;j++)
     {
        if(maze[i][j]==1 || maze[i][j]==7)
            putchar('x');
        else if(maze[i][j]==7)
            putchar('r');
        else if(maze[i][j]==9)
            putchar('T');
        else
            putchar('o');
        putchar(' ');
         }
         putchar('\n');
     }

    }

Node* findpath()
{
   int i=0,j=0,flag=0;
   int num;
   int *x=(int*)malloc(sizeof(int));
   int *y=(int*)malloc(sizeof(int));
   Node* ptr=NULL;
   do
    {
       if(maze[i][j]==9)
       {
         ptr=push_stack(ptr,i,j);
         flag=1;
         break;
       }
       else if(maze[i][j]!=1 && !check_in_path(ptr,i,j))
           ptr=push_stack(ptr,i,j);

       num=pass(ptr,i,j);
       printf("num is %d \n",num);
       switch(num)
       {
         case 2:
           j+=1;
           break;
         case 3:
           i+=1;
           break;
         case 4:
           j-=1;
           break;
         case 5:
           i-=1;
           break;
         case 7:
            printf("start block in findpath %d,%d\n",i,j);
            printf("block at path:\n");
            showpath(ptr);
      //     if(ptr)
            top_stack(ptr,x,y);
            printf("begin to pop back %d,%d",*x,*y);

            ptr=pop_stack(ptr,x,y);
            if(isempty())
            {  printf("There is no solution exist\n");
               return NULL;
            }
            else
            {
              top_stack(ptr,x,y);
              i=*x;
              j=*y;
            }

            break;
        }
      printf("searching for solution\n");
      printf("current path is: \n");
      showpath(ptr);

    }while(!isempty() && flag!=1);
   if(flag==1)
   {  setpath(ptr);
     printf("Find a path\n");
     showpath(ptr);
     return ptr;
   }else
    { printf("No path found\n");
      return NULL;
     }
}

int main()
{
    char c;
    Node* res;
    printf("Maze game start: \nPlease imput the row of the maze :");
    scanf("%d",&m);
    printf("Please input the column of the maze : ");
    scanf("%d",&n);
    initmaze(m,n);
    printf("The maze is :\n");
    drawmaze();
    printf("draw maze done\n");
    res=findpath();
    if(res)
   {
      printf("solution found:\n");
      setpath(res);
      drawmaze();
        }
   else
       printf("no solution found\n");

    return 0;

    }
