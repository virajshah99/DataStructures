#include<stdio.h>
char a[3][3]={'1','2','3','4','5','6','7','8','9'};

void prnt()
{
int i,j;
for(i=0;i<3;i++)
    {
	    printf(" %c | %c | %c \n",a[i][0],a[i][1],a[i][2]);
	    if(i!=2)
		printf("___|___|___");
	    printf("\n");
    }
}
void main()
{
    int k=0,p,m,x,y,w=0;
    clrscr();
    prnt();
    printf("Enter the value where you want to put the value in matrix form \neg:1 3/1 2,etc");
    while(k!=9)
    {
    l1:	p= (k%2)>0 ? 2:1;
	printf("Player %d\nEnter place where the value is to be entered:\t",p);
	scanf("%d%d",&x,&y);
	x--;
	y--;
	if(a[x][y]=='X' || a[x][y]=='O'|| x>=3 || y>=3)
	{
		printf("Please enter valid no!\n");
		goto l1;
	}
	else
	{
		if(k%2==0)
			a[x][y]='O';
		else
			a[x][y]='X';
	}
	clrscr();
	prnt();
	k++;
	//coloumns
	for(m=0;m<3;m++)
	{
		if((a[0][m]==a[1][m])&&(a[1][m]==a[2][m]))
		{
			printf("C Player %d wins!\n",p);
			w=1;
		}

	}
	//rows
	for(m=0;m<3;m++)
	{
		if((a[m][0]==a[m][1])&&(a[m][1]==a[m][2]))
		{
			printf("R Player %d wins!\n",p);
			w=1;
		}
	}
	if((a[0][0]==a[1][1])&&(a[1][1]==a[2][2]))
	{
	      printf("D Player %d wins!\n",p);
	      w=1;
	}
	if((a[0][2]==a[1][1])&&(a[1][1]==a[2][0]))
	{
		printf("RD Player %d wins!\n",p);
		w=1;
	}
	if(w==1)
		break;
    }
    getch();
}
