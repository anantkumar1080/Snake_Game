#include<iostream>
#include<stdlib.h>
using namespace std;
#define M 20
#define N 30
struct food{
    int x;
    int y;
    char value;
};
struct snake{
    int x;
    int y;
    char value;
    struct snake *next;
};
/*
void initialfood(struct food *f)
{
    f->x=10;
    f->y=10;
    f->value='*';
}
*/
void createsnake(struct snake **head)
{
    int a=5;
    int b=15;
    struct snake * ptr=*head,*n;
     n=new snake;
     n->next=NULL;
    if(*head==NULL)
    {
        n->x=a;
        n->y=b;
        n->value='H';
        *head=n;
    }
    else
    {
        ptr=*head;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
            ptr->value='@';
        }
        ptr->next=n;
        n->value='T';
        n->x=ptr->x+1;
        n->y=ptr->y;
    }
}
struct snake * creategameover(struct snake **head,char c)
{
    int a=9;
    int b=10;
    struct snake * ptr=*head,*n;
     n=new snake;
     n->next=NULL;
    if(*head==NULL)
    {
        n->x=a;
        n->y=b;
        n->value=c;
        *head=n;
    }
    else
    {
        ptr=*head;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=n;
        n->value=c;
        n->x=ptr->x;
        n->y=ptr->y+1;
    }
    return *head;
}
void setBoard(char board[M][N],struct snake *head,struct food *f)
{
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            board[i][j]=' ';
        }
    }
    struct snake *ptr=head;
    while(ptr!=NULL)
    {
        board[ptr->x][ptr->y]=ptr->value;
        ptr=ptr->next;
    }
    board[f[0].x][f[0].y]=f[0].value;
}
void printBoard(char board[M][N])
{
    
    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(i==0 || j==0 || i==19 || j== 29)
            {
                cout<<". ";
            }
            else
            {
              cout<<board[i][j]<<" ";  
            }
         
        }cout<<endl;
    }
}
int valid(char choice,struct snake *head)
{
    if(choice=='w')
    {
        int i,j;
        i=head->x;
        j=head->y;
        int i1=i-1,j1=j;
        if(head->next->x==i1&&head->next->y==j1)
            return 0;
        return 1;
    }
    if(choice=='a')
    {
        int i,j;
        i=head->x;
        j=head->y;
        int i1=i,j1=j-1;
        if(head->next->x==i1&&head->next->y==j1)
            return 0;
        return 1;
    }
    if(choice=='s')
    {
        int i,j;
        i=head->x;
        j=head->y;
        int i1=i+1,j1=j;
        if(head->next->x==i1&&head->next->y==j1)
            return 0;
        return 1;
    }
    if(choice='d')
    {
        int i,j;
        i=head->x;
        j=head->y;
        int i1=i,j1=j+1;
        if(head->next->x==i1&&head->next->y==j1)
            return 0;
        return 1;
    }
    return 0;
}
void writetofile(snake *start,food *f,int *m)
{
  FILE *fptr;
    fptr=fopen("gamedata.txt","w");
  while(start!=NULL)
  {
    fprintf(fptr,"%d,%d,%c\n",start->x,start->y,start->value);
    start=start->next;
  }
  // char ch='$';
  // fprintf(fptr,"%c\n",ch);
     fprintf(fptr,"%d,%d,%c\n",f[0].x,f[0].y,f[0].value);
     fprintf(fptr,"score=%d\n",*m);
     char str='$';
     fprintf(fptr,"%c",str);
  fclose(fptr);
}
// void readfile(snake **start,food *f)
// {
//     FILE *fptr;
//     fptr=fopen("gamedata.txt","r");
//     char ch;
//     ch=fgetc(fptr);

//     snake *ptr=NULL;
//   while(ch!='$')
//   {
//     int n=ch-'0';
  
//     ch=fgetc(fptr);
//     ch=fgetc(fptr);
//     int x=ch-'0';
//     sert(&ptr,n,x);
//   }
//   *start=ptr;
// }
void movement(char choice,snake **head,food *f,char board[M][N],int *m)
{
    struct snake *ptr=*head,*prev,*n;
    int i,j,i1,j1,getfood=0;
    i=ptr->x;
    j=ptr->y;
    if(choice=='w')
    {
        i1=i-1;
        j1=j;
        if(i==1)
        {
            i1=18;
        }
        if(f[0].x==i1&&f[0].y==j1)
        {
            getfood=1;
        }
    }
    if(choice=='a')
    {
        i1=i;
        j1=j-1;
        if(j==1)
        {
            j1=28;
        }
        if(f[0].x==i1&&f[0].y==j1)
        {
            getfood=1;
        }
    }
    if(choice=='s')
    {
        i1=i+1;
        j1=j;
        if(i==18)
        {
            i1=1;
        }
        if(f[0].x==i1&&f[0].y==j1)
        {
            getfood=1;
        }
    }
    if(choice=='d')
    {
        i1=i;
        j1=j+1;
        if(j==28)
        {
            j1=1;
        }
        if(f[0].x==i1&&f[0].y==j1)
        {
            getfood=1;
        }
    }
    n=new snake;
    n->x=i1;
    n->y=j1;
    n->value='H';
    n->next=*head;
    ptr=*head;
    ptr->value='@';
    if(getfood==0)
    {
        while(ptr->next!=NULL)
        {
            prev=ptr;
            ptr=ptr->next;
        }
        board[ptr->x][ptr->y]=' ';
        ptr->value=' ';
        prev->value='T';
        prev->next=NULL;
    }
    
    if(getfood==1)
    {
        *m=*m+10;
        f[0].x=rand()%19;
        f[0].y=rand()%29;
        f[0].value='F';
        board[f[0].x][f[0].y]=f[0].value;
    }
    *head=n;
}
int main()
{
    struct food f[2];
    f[0].x=8;
    f[0].y=12;
    f[0].value='F';
    struct snake *head=NULL;
    char board[M][N];
   //initialfood(f);
    int n = 5;
    while(n--)
    createsnake(&head);
    
    //setBoard(board,head,f);
    //printBoard(board);
    int point=0;
    int m=0;
    char choice;
     do
    {   cout<<"Score: "<<point<<endl;
        setBoard(board,head,f);
        printBoard(board);
        cout<<"Enter movement\n";
        cin>>choice;
        if(choice=='q')
        {
            m=1;
            break;
        }
       if(valid(choice,head))
       {
            movement(choice,&head,f,board,&point);
            if(board[head->x][head->y]=='@'||board[head->x][head->y]=='T')
            {
                m=2;
                break;
            }
            setBoard(board,head,f);
       }
       system("cls");
       printBoard(board);
    }while(choice!='q');
    cout<<"Score: "<<point<<endl;
    if(m==1||m==2)
    {
            for(int i=0;i<M;i++)
            {
                for(int j=0;j<N;j++)
                {
                    board[i][j]=' ';
                }
            }

        struct snake *head1=NULL;
        char str[10]={'G','A','H','E',' ','O','F','E','R'};
        int k=0;
        while(k<9)
        {
            head1=creategameover(&head1,str[k]);
            k++;
        }
        struct snake *ptr=head1;
        while(ptr!=NULL)
        {
            board[ptr->x][ptr->y]=ptr->value;
            ptr=ptr->next;
        }
        printBoard(board);
        char ch;
        if(m==1)
        {
            cout<<"Do you want to save the game(y/n)\n";
            cin>>ch;
        }
        if(ch=='y')
        {
            writetofile(head,f,&point);
            cout<<"data has saved\n";
        }
        else
            cout<<"All data lost\n";
    }

    return 0;
}
