#include<stdio.h>
#include<time.h>
#include<stdlib.h>
float sum=0.0,number=0;
char check_winner(char matrix[][3])
{
	if(matrix[0][0]==matrix[0][1]&&matrix[0][1]==matrix[0][2]&&matrix[0][2]!='s')
		return matrix[0][0];
	if(matrix[1][0]==matrix[1][1]&&matrix[1][1]==matrix[1][2]&&matrix[1][2]!='s')
		return matrix[1][0];
	if(matrix[2][0]==matrix[2][1]&&matrix[2][1]==matrix[2][2]&&matrix[2][2]!='s')
		return matrix[2][0];

	if(matrix[0][0]==matrix[1][0]&&matrix[1][0]==matrix[2][0]&&matrix[2][0]!='s')
		return matrix[0][0];
	if(matrix[0][1]==matrix[1][1]&&matrix[1][1]==matrix[2][1]&&matrix[2][1]!='s')
		return matrix[0][1];
	if(matrix[0][2]==matrix[1][2]&&matrix[1][2]==matrix[2][2]&&matrix[2][2]!='s')
		return matrix[0][2];

	if(matrix[0][0]==matrix[1][1]&&matrix[1][1]==matrix[2][2]&&matrix[2][2]!='s')
		return matrix[0][0];
	if(matrix[0][2]==matrix[1][1]&&matrix[1][1]==matrix[2][0]&&matrix[2][0]!='s')
		return matrix[0][2];

	int x,y;
	for(x=0;x<3;x++)
	{
		for(y=0;y<3;y++)
		{
			if(matrix[x][y]=='s')
				return 's';
		}
	}

	return 't';
}

char check_win_main(char main_matrix[][3])
{
	char copy_main[3][3];

	int x,y;
	for(x=0;x<3;x++)
	{
		for(y=0;y<3;y++)
		{
			if(main_matrix[x][y]=='t')
			{
				copy_main[x][y]='s';
			}

			else
			{
				copy_main[x][y]=main_matrix[x][y];
			}
		}
	}

	if(check_winner(copy_main)=='o')
	{
		return 'o';
	}
	if(check_winner(copy_main)=='x')
	{
		return 'x';
	}

	int flag=0;

	for(x=0;x<3;x++)
	{
		for(y=0;y<3;y++)
		{
			if(main_matrix[x][y]=='s')
			{
				flag=1;
				break;
			}
		}
	}

	if(flag==0)
	{
		return 't';
	}

	return 's';
}

char random_moves(char matrix[][3][3][3],char main_matrix[][3],int firstmove[])
{
	int iplay=-1;
	int jplay=-1;
	int xrand,yrand;
	sum++;
	matrix[firstmove[0]][firstmove[1]][firstmove[2]][firstmove[3]]='o';

	if(check_winner(matrix[firstmove[0]][firstmove[1]])=='o')
	{
		main_matrix[firstmove[0]][firstmove[1]]='o';
		if(check_win_main(main_matrix)=='o')
		{
			return 'O';
		}
		
		else if(check_win_main(main_matrix)=='t')
		{
			return 't';
		}
	}

	else if(check_winner(matrix[firstmove[0]][firstmove[1]])=='t')
	{
		main_matrix[firstmove[0]][firstmove[1]]='t';
		if(check_win_main(main_matrix)=='t')
		{
			return 't';
		}
	}

	if(main_matrix[firstmove[2]][firstmove[3]]!='s')
	{
		iplay=-1;
		jplay=-1;
	}
	
	else
	{
		iplay=firstmove[2];
		jplay=firstmove[3];
	}

	//Division between firstmove and loop

	while(1)
	{
		if(iplay==-1 && jplay==-1)
		{
			do
			{
				iplay=rand()%3;
				jplay=rand()%3;
			}
			while(main_matrix[iplay][jplay]!='s');
		}

		do
		{
			xrand=rand()%3;
			yrand=rand()%3;
		}
		while(matrix[iplay][jplay][xrand][yrand]!='s');
		sum++;
		matrix[iplay][jplay][xrand][yrand]='x';
		if(check_winner(matrix[iplay][jplay])=='x')
		{
			main_matrix[iplay][jplay]='x';
			if(check_win_main(main_matrix)=='x')
			{
				return 'x';
			}
			else if(check_win_main(main_matrix)=='t')
			{
				return 't';
			}
		}

		else if(check_winner(matrix[iplay][jplay])=='t')
		{
			main_matrix[iplay][jplay]='t';
			if(check_win_main(main_matrix)=='t')
			{
				return 't';
			}
		}

		if(main_matrix[xrand][yrand]!='s')
		{
			iplay=-1;
			jplay=-1;
		}
		
		else
		{
			iplay=xrand;
			jplay=yrand;
		}

		//Division between first and second move

		if(iplay==-1 && jplay==-1)
		{
			do
			{
				iplay=rand()%3;
				jplay=rand()%3;
			}
			while(main_matrix[iplay][jplay]!='s');
		}

		do
		{
			xrand=rand()%3;
			yrand=rand()%3;
		}
		while(matrix[iplay][jplay][xrand][yrand]!='s');

		matrix[iplay][jplay][xrand][yrand]='o';
		if(check_winner(matrix[iplay][jplay])=='o')
		{
			main_matrix[iplay][jplay]='o';
			if(check_win_main(main_matrix)=='o')
			{
				return 'o';
			}
			else if(check_win_main(main_matrix)=='t')
			{
				return 't';
			}
		}

		else if(check_winner(matrix[iplay][jplay])=='t')
		{
			main_matrix[iplay][jplay]='t';
			if(check_win_main(main_matrix)=='t')
			{
				return 't';
			}
		}

		if(main_matrix[xrand][yrand]!='s')
		{
			iplay=-1;
			jplay=-1;
		}
		
		else
		{
			iplay=xrand;
			jplay=yrand;
		}

	}
}

int main()
{
	char inputloc[]="./data/matrixforai.txt";
	char outputloc[]="./data/aimove.txt";

	FILE *fpinput=fopen(inputloc,"r");
	FILE *fpoutput=fopen(outputloc,"w+");

	char matrix[3][3][3][3];
	char main_matrix[3][3];

	int iplay,jplay;
	char temp;

	fscanf(fpinput,"%d %d",&iplay,&jplay);
	fscanf(fpinput,"%c",&temp);

	//scanf("%d %d",&iplay,&jplay);
	//scanf("%c",&temp);

	int i,j,k,l;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				for(l=0;l<3;l++)
				{
					fscanf(fpinput,"%c",&matrix[i][k][j][l]);
					//scanf("%c",&matrix[i][k][j][l]);
					if(matrix[i][k][j][l]=='X')matrix[i][k][j][l]='x';
                                        else if(matrix[i][k][j][l]=='O')matrix[i][k][j][l]='o';
                                        else if(matrix[i][k][j][l]=='-')matrix[i][k][j][l]='s';
				}
			}
			fscanf(fpinput,"%c",&temp);
			//scanf("%c",&temp);
		}
	}

	for (i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			main_matrix[i][j]=check_winner(matrix[i][j]);
		}
	}

	int positions[81][4];
	int noofpositions=0;

	if(iplay!=-1 && jplay!=-1)
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(matrix[iplay][jplay][i][j]=='s')
				{
					positions[noofpositions][0]=iplay;
                                        positions[noofpositions][1]=jplay;
                                        positions[noofpositions][2]=i;
                                        positions[noofpositions][3]=j;
					noofpositions++;
				}
			}
		}
	}

	else
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(main_matrix[i][j]=='s')
				{
					for(k=0;k<3;k++)
					{
						for(l=0;l<3;l++)
						{
							if(matrix[i][j][k][l]=='s')
							{
								positions[noofpositions][0]=i;
                                                                positions[noofpositions][1]=j;
                                                                positions[noofpositions][2]=k;
                                                                positions[noofpositions][3]=l;
								noofpositions++;
							}
						}
					}
				}
			}
		}
	}

	double best_prob=0.0;
	int best_pos[4]={-1,-1,-1,-1};

	char copy_matrix[3][3][3][3];
	char copy_main[3][3];
	int currpos,flag=0;
	
	srand(time(NULL));
	
	double timepermove=1.0/noofpositions;

	for(currpos=0;currpos<noofpositions;currpos++)
	{
		int noofwins=0,nooflosses=0,noofties=0;

		struct timeval currtime,inittime;
		gettimeofday(&inittime,NULL);

		while(gettimeofday(&currtime,NULL),(double)((currtime.tv_sec-inittime.tv_sec)+(currtime.tv_usec-inittime.tv_usec)*1.0/1000000)<timepermove)
		{
			for(i=0;i<3;i++)
			{
				for(j=0;j<3;j++)
				{
					for(k=0;k<3;k++)
					{
						for(l=0;l<3;l++)
						{
							copy_matrix[i][j][k][l]=matrix[i][j][k][l];
						}

					}
				}
			}

			for(i=0;i<3;i++)
			{
				for(j=0;j<3;j++)
				{
					copy_main[i][j]=main_matrix[i][j];
				}
			}
			temp=random_moves(copy_matrix,copy_main,positions[currpos]);
			number++; 
			
			if(temp=='O')
				{
				noofwins++;
				flag=1;
				break;
				}	
			if(temp=='o')
				noofwins+=1;
			else if (temp=='x')
				nooflosses+=1;
			else
				noofties+=1;
		}
		
		double prob=(1.0*noofwins)/(noofwins+nooflosses+noofties);	
		if(flag==1)
			prob=2.0;
		if(prob>best_prob)
		{
			best_prob=prob;
			best_pos[0]=positions[currpos][0];
                        best_pos[1]=positions[currpos][1];
                        best_pos[2]=positions[currpos][2];
                        best_pos[3]=positions[currpos][3];
			if(flag==1)
				break;
		}	
	}
	
	sum/=number;
	printf("%f ",(flag==0)?(sum):(1.0));
	fprintf(fpoutput,"%d %d %d %d\n",best_pos[0],best_pos[1],best_pos[2],best_pos[3]);
        //printf("%d %d %d %d\n",best_pos[0],best_pos[1],best_pos[2],best_pos[3]);

	fclose(fpinput);
	fclose(fpoutput);
	return 0;
}
