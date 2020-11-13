#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<semaphore.h>
#include<pthread.h>
#include<fcntl.h>


sem_t mutex;
char p1[20],p2[20];
char flag=0;
int l;
int pos1=0;
int pos2=0;
int dice1,dice2;
int fd;
unsigned char b[150]="50 ss 48 47 46\n45 44 43 42 41\n40 39 38 37 ll\n35 34 33 32 31\nss 29 28 27 26\n25 24 ss 22 21\n20 19 18 ll 16\n15 ss 13 12 11\n10 ll ss 07 06\n05 04 ll 02 01\n";
char c[150];




int dice(void)
{
time_t t;
srand((unsigned) time(&t));

int dice=((int)(rand()%6)+1);
return dice;

}





int check(int pos1,int pos2,int dice1, int dice2)
{
pos1+=dice1;
pos2+=dice2;

if(pos1>50 && pos2>50)
	{
	printf(" \n oops %s... u have to await for lucky number\n",p1);
	sleep(1);
	printf("\n oops %s... u have to await for lucky number\n",p2);
	sleep(1);
	return 0;
	}

if(pos1>50)
	{
	printf(" \n oops %s... u have to await for lucky number\n",p1);
	sleep(1);
	return 0;}
if(pos2>50)
	{
	printf("\n oops %s... u have to await for lucky number\n",p2);
	sleep(1);
	return 0;
	}
	
return 1;
}
