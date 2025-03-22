
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

int lose=0;
#define X 25
#define Y 25
int f_x=0,f_y=0;
char last='a';
int x=X/2,y=Y/2;

int snake_len=1;
int snake[2][100];

char board[X][Y];

int check_fruit()
{

    for (int i=0;i<snake_len;i++)
    {
        if(f_x==snake[0][i])
        {
            f_x=(f_y+10)%X;
        }
        if(f_y==snake[1][i])
        {
            f_y=(f_x+10)%Y;
            
        }
    }
    
}
void fruit()
{
    int lower = 2, upper = X-2;
    
    srand(time(0));
    f_x=lower + rand() % (upper - lower + 1);
    f_y=lower + rand() % (upper - lower + 1);
    check_fruit();

    board[f_x][f_y]='@';
    
    printf("%d",snake_len);
}
void got_it(char c)
{
    snake_len++;
 
    switch(c){
    case 'a':

        snake[0][snake_len-1]=snake[0][snake_len-2];
        snake[1][snake_len-1]=snake[1][snake_len-2]+1;
        board[snake[0][snake_len-1]][snake[1][snake_len-1]]='o';
        break;
    case 'd':
        snake[0][snake_len-1]=snake[0][snake_len-2];
        snake[1][snake_len-1]=snake[1][snake_len-2]-1;
        board[snake[0][snake_len-1]][snake[1][snake_len-1]]='o';
        break;
    case 's':
        snake[0][snake_len-1]=snake[0][snake_len-2]-1;
        snake[1][snake_len-1]=snake[1][snake_len-2];
        board[snake[0][snake_len-1]][snake[1][snake_len-1]]='o';
        break;
    case 'w':
        snake[0][snake_len-1]=snake[0][snake_len-2]+1;
        snake[1][snake_len-1]=snake[1][snake_len-2];
        board[snake[0][snake_len-1]][snake[1][snake_len-1]]='o';
        break;
    default:
         break;
    }
    fruit();
    
  
}
void display(){
     system("cls");
    for(int i=0;i<X;i++)
    {
        for(int j=0;j<Y;j++)
        {
                printf("%c ",board[i][j]);
        }
        printf("\n");
           
    }
   
}

void swap()
{
    board[snake[0][snake_len-1]][snake[1][snake_len-1]]=' ';
    for (int i=snake_len-1;i>0;i--)
    {
        snake[0][i]=snake[0][i-1];
        snake[1][i]=snake[1][i-1];
        board[snake[0][i]][snake[1][i]]='o';
    }
}
void left()
{
    swap();
    y--;
    snake[0][0]=x;
    snake[1][0]=y;
    board[x][y]='O';
    
    
}
void right()
{
    swap();
    y++;
    snake[0][0]=x;
    snake[1][0]=y;
    board[x][y]='O';
}
void up()
{
    swap();
    x--;
    snake[0][0]=x;
    snake[1][0]=y;
    board[x][y]='O';


}
void down()
{
    swap();
    x++;
    snake[0][0]=x;
    snake[1][0]=y;
    board[x][y]='O';
}
void create_board()
{
        
    snake[0][0]=x;
    snake[1][0]=y;
    for(int i=0;i<X;i++)
    {
        for(int j=0;j<Y;j++)
        {
            if(i==0 || j==0 || j==Y-1 || i==X-1)
            {
                board[i][j]='*';
            }
            else if (i==x && j==y){
                board[i][j]='S';
            
            }
            else{
                board[i][j]=' ';
            }
        }
           
    }
    fruit();
    
}
void check(char c){
    if (x==f_x && y==f_y)
    {
        got_it(c);
    }
    else if(x==0 || y==0 || x== X-1 || y==Y-1)
    {
        lose=1;
    }
    else{
        for (int i=1;i<snake_len;i++)
        {
            if(snake[0][i]==x && snake[1][i]==y)
            {
                lose=1;
                break;
            }
        }
    }
    
}

void handle(char c)
{
        if(c=='a')
        {
            last='a';
            left(); 
        }
        else if(c=='w')
        {
            last='w';
            up();
        }
        else if(c=='s')
        {
            last='s';
            down();
        }
        else if(c=='d')
        {
            last='d';
            right();
        }
        else{
        
        }
}
int main()
{
    char c='a';
    create_board();
    display();
   
  while (lose==0)
    {
        if(kbhit()){
        c=getch();
        if(  c=='d' && last == 'a'){
            c='a';
        }
        else if( c=='w' && last =='s' ){
            c='s';
        }
        else if( c=='a' && last =='d' ){
            c='d';
        }
        else if (c =='s' && last =='w'){
            c='w';

        }
        else{

        }

        }
      
        handle(c);
        display();
        check(c);
        printf("Score: %d",snake_len);
        Sleep(100);
    }
   
  
    return 0;
}