#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
char input(char[][3] ,int );
void display(char [][3]);
char check(char [][3]);
char cpuinput(char [][3]);
int cpucheck(char [][3]);
void append(char* ,char);
int main()
{
    int count,chk,limit;
    char tic[3][3],tmp[20],p2[20],ch='N',cch='m';
    do{
    char p1[20]="cpu";
    printf("Single Player (s) or Multi Player (m):  ");
    scanf(" %c",&cch);
    char tic[3][3]={{'.','.','.'},{'.','.','.'},{'.','.','.'}};
    count=0;chk=0;limit=9;
    if(cch=='s'){
    printf("X PLAYER : CPU \n");
    }
    else{
        printf("ENTER A NAME FOR X PLAYER :  ");
        scanf("%s",p1);
    }
    printf("ENTER A NAME FOR O PLAYER :  ");
    scanf("%s",p2);
    while(1){
    printf("Who plays first,%s or %s?\n",p1,p2);
    scanf("%s",tmp);
    if( strcmp(tmp, p1) == 0)
        break;
    else if( strcmp(tmp, p2) == 0){
        count=-1;
        limit=8;
        break;}
        printf("%s is not a registered player.\n",tmp);
    }
    while(count<limit)
    {
        if(count%2==0){
            printf("Player of current turn : %s\n",p1);
            if(cch=='s')
                chk=cpuinput(tic);
            else
                chk=input(tic,1);
        }
        else{
            printf("Player of current turn : %s\n",p2);
            chk=input(tic,2);}
        if(chk=='s')
            count++;
        else if(chk=='f')
            printf("Place already taken !!!\n Input again. \n");
        display(tic);
        chk=check(tic);
        if(chk=='X'||chk=='O')
            break;
    }
    printf("game is over :\n");
    if(chk=='X')
        printf("%s wins !\n",p1);
    else if(chk=='O')
        printf("%s wins !\n",p2);
    else
        printf("ITS A TIE !\n ");
    do{
        printf("Would you like to play again? (Y/N)\n");
        scanf(" %c",&ch);
        if(ch=='Y' || ch=='N')
            break;
        printf("%c is not a valid answer.\n",ch);
      }while(1);
   }while(ch!='N');
   printf("bye!");
    return 0;
}
char input(char tic[][3],int x)
{
    int i,j;
    do{
    printf("Choose a row number (0 to 2): \n");
    scanf("%d",&i);
    if(i>=0&&i<3)
        break;
    printf("%d is not a valid row.\n",i);
    }while(1);
    do{
    printf("Choose a column number (0 to 2): \n");
    scanf("%d",&j);
    if(j>=0&&j<3)
        break;
    printf("%d is not a valid column.\n",j);
    }while(1);
    if(tic[i][j]!='.')
        return('f');
    else
    {
        if(x==1)
            tic[i][j]='X';
        else
            tic[i][j]='O';
        return('s');
    }
}
void display(char tic[][3])
{
    printf("\n");
    printf("\t %c | %c | %c \n",tic[0][0],tic[0][1],tic[0][2]);
    printf("\t-----------\n");
    printf("\t %c | %c | %c \n",tic[1][0],tic[1][1],tic[1][2]);
    printf("\t-----------\n");
    printf("\t %c | %c | %c \n",tic[2][0],tic[2][1],tic[2][2]);

}
char check(char tic[][3])
{
    if(tic[0][0]==tic[1][1]&&tic[1][1]==tic[2][2])
        return(tic[0][0]);
    else if(tic[0][2]==tic[1][1]&&tic[1][1]==tic[2][0])
        return(tic[0][2]);
    else if(tic[0][0]==tic[0][1]&&tic[0][1]==tic[0][2])
        return(tic[0][2]);
    else if(tic[1][0]==tic[1][1]&&tic[1][1]==tic[1][2])
        return(tic[1][0]);
    else if(tic[2][0]==tic[2][1]&&tic[2][1]==tic[2][2])
        return(tic[2][0]);
    else if(tic[0][0]==tic[1][0]&&tic[1][0]==tic[2][0])
        return(tic[0][0]);
    else if(tic[0][1]==tic[1][1]&&tic[1][1]==tic[2][1])
        return(tic[0][1]);
    else if(tic[0][2]==tic[1][2]&&tic[1][2]==tic[2][2])
        return(tic[0][2]);
    else
        return('f');
}

char cpuinput(char tic[][3])
{
    int i=0,j;
    i=cpucheck(tic);
    if(i==1)
        return('s');
    else{
    srand(time(0));
        do{
            i=rand()%3;
            j=rand()%3;
        }while(tic[i][j]!='.');
        tic[i][j]='X';
        return('s');
    }
}

int cpucheck(char tic[][3]){
     int i,j,k=0;
     char ch,row[3],col[3];
     //Check for row formation
    for(i=0;i<3;i++){
        row[0]='\0';
        for(j=0;j<3;j++){
           append(row,tic[i][j]);
        }
        if(strcmp(row,"X.X")==0 || strcmp(row,"O.O")==0){
            tic[i][1]='X';k=1;
            break;
        }
        if(strcmp(row,"XX.")==0 || strcmp(row,"OO.")==0){
            tic[i][2]='X';k=1;
            break;
        }
        if(strcmp(row,".XX")==0 || strcmp(row,".OO")==0){
            tic[i][0]='X';k=1;
            break;
        }
    }
    //Check for Column formation
    if(k!=1){
    for(i=0;i<3;i++){
        col[0]='\0';
        for(j=0;j<3;j++){
            append(col,tic[j][i]);
        }
        if(strcmp(col,"X.X")==0 || strcmp(col,"O.O")==0){
            tic[1][i]='X';k=1;
            break;
        }
        if(strcmp(col,"XX.")==0 || strcmp(col,"OO.")==0){
            tic[2][i]='X';k=1;
            break;
        }
        if(strcmp(col,".XX")==0 || strcmp(col,".OO")==0){
            tic[0][i]='X';k=1;
            break;
        }
    }
    }
    if(k!=1){
    //Check for primary diagonal formation
    row[0]='\0';
    col[0]='\0';
    for(i=0;i<3;i++){
        append(row,tic[i][i]);
    }
    if(strcmp(row,".XX")==0){
            tic[0][0]='X';k=1;
        }
    if(strcmp(row,"X.X")==0){
            tic[1][1]='X';k=1;
        }
    if(strcmp(row,"XX.")==0){
            tic[2][2]='X';k=1;
        }
    for(i=0;i<3;i++){
        append(col,tic[i][i]);
    }
    if(strcmp(col,".OO")==0){
            tic[0][0]='X';k=1;
        }
    if(strcmp(col,"O.O")==0){
            tic[1][1]='X';k=1;
        }
    if(strcmp(col,"OO.")==0){
            tic[2][2]='X';k=1;
        }
    //Check for secondary diagonal formation
    row[0]='\0';
    col[0]='\0';
    for(i=0;i<3;i++){
        append(col,tic[i][2-i]);
    }
    if(strcmp(col,".OO")==0){
            tic[0][2]='X';k=1;
        }
    if(strcmp(col,"O.O")==0){
            tic[1][1]='X';k=1;
        }
    if(strcmp(col,"OO.")==0){
            tic[2][0]='X';k=1;
        }
     for(i=0;i<3;i++){
        append(row,tic[i][2-i]);
    }
    if(strcmp(row,".XX")==0){
            tic[0][2]='X';k=1;
        }
    if(strcmp(row,"X.X")==0){
            tic[1][1]='X';k=1;
        }
    if(strcmp(row,"XX.")==0){
            tic[2][0]='X';k=1;
        }
    }
     if(k==1)
        return 1;
     else
        return 0;
}

void append(char* s, char c){
    int len=strlen(s);
    s[len]=c;
    s[len+1]='\0';
}
