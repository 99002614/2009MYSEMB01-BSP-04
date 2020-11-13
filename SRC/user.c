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
int win(int posi1,int posi2)
{

if(posi1==50)
{
printf("\n CONGRATUALTIONS \" %s \" U WON THE MATCH... \n ",p1);
printf(" \n *	*	*	*	*	*	* 	*\n");
return(1);
}
if(posi2==50)
{
printf("\n CONGRATUALTIONS \" %s \" U WON THE MATCH... \n ",p2);
printf(" \n +	+	+	+	+	+	+	+\n");
return(1);
}
return 0;
}
void *player_one(void *vargp) 
{ 
    sem_wait(&mutex);    
    sleep(1); 
    printf("\nplayer %s playing\n",p1);
    flag=getchar();
    
    again:
    dice1=dice();
    
	if(dice1==6)
	{if(check(pos1,0,dice1,0)){pos1+=dice1;printf("\ndice of %s is %d\n",p1,dice1);printf("\n%s letss go again \n\n",p1);sleep(2);goto again;}}
	else
	{if(check(pos1,pos2,dice1,dice2)){pos1+=dice1;printf("\n\ndice of %s is %d\n",p1,dice1);sleep(1);}}
	
	
	if(pos1==pos2)
	{

	if(b[l-(pos1*3)]=='l')
	{pos1=pos1+3;printf("\n******yeahhhh %s found a ladder .. go 4 step further******\n",p1);sleep(1);}
	else if(b[l-(pos1*3)]=='s')
	{pos1=pos1-4;printf("\n******uffff %s got bitten by a snake ,,go 4 step back******\n",p1);sleep(1);}
	
	/*if(b[l-(pos2*3)]=='l')
	{pos2=pos2+3;printf("\n++++++yeahhhh %s found a ladder .. go 4 step further++++++\n",p2);sleep(1);}
else if(b[l-(pos2*3)]=='s')
	{pos2=pos2-4;printf("\n++++++uffff %s got bitten by a snake ,, go 4 step back+++++++\n",p2);sleep(1);}*/	


	b[(l-(pos1*3))]='+';
	b[(l-(pos2*3)+1)]='*';
	}
	
	else if(pos1!=pos2)
	{

	/*if(b[l-(pos1*3)]=='l')
	{pos1=pos1+4;printf("\n*****yeahhhh %s found a ladder ..  go 4 step furthure*****\n",p1);sleep(1);}
	else if(b[l-(pos1*3)]=='s')
	{pos1=pos1-4;printf("\n*****uffff %s got bitten by a snake ,, go 4 step back*****\n",p1);sleep(1);}*/

	if(b[l-(pos2*3)]=='l')
	{pos2=pos2+4;printf("\n+++++yeahhhh %s found a ladder ..  go 4 step furthure+++++\n",p2);sleep(1);}
	else if(b[l-(pos2*3)]=='s')
	{pos2=pos2-4;printf("\n+++++uffff %s got bitten by a snake ,,  go 4 step back+++++\n",p2);sleep(1);}

	b[(l-(pos1*3))]='*';b[(l-(pos1*3))+1]='*';
	}
	
printf("\n%s\n",b);

	/*int oldpos1=pos1;
	int oldpos2=pos2;

	
	if(oldpos1==oldpos2)
	{
	b[(l-(oldpos2*3))]=c[(l-(oldpos2*3))];b[(l-(oldpos1*3))+1]=c[(l-(oldpos1*3))+1];
	}
	else
	{
	b[(l-(oldpos1*3))]=c[(l-(oldpos1*3))];b[(l-(oldpos1*3))+1]=c[(l-(oldpos1*3))+1];
	b[(l-(oldpos2*3))]=c[(l-(oldpos2*3))];b[(l-(oldpos2*3))+1]=c[(l-(oldpos2*3))+1];
	}*/



    
    sem_post(&mutex);
    printf("\nplayer two chance\n");
    return NULL; 
}
void *player_two(void *vargp) 
{ 
    sem_wait(&mutex);    
    sleep(1); 
    printf("\nplayer %s playing \n",p2); 
    flag=getchar();
    again:
    dice2=dice();



if(dice2==6)
	{if(check(0,pos2,0,dice2)){pos2+=dice2;printf("\ndice of %s is %d\n",p2,dice2);printf("\n%s letss go again \n\n",p2);sleep(2);goto again;}}
	else
	{if(check(pos1,pos2,dice1,dice2)){pos2+=dice2;printf("\ndice of %s is %d\n",p2,dice2);sleep(1);}}

printf("\n%s\n",b);
write(fd,b,152);
read(fd,b,152);




    
    if(pos1==pos2)
{

/*if(b[l-(pos1*3)]=='l')
	{pos1=pos1+3;printf("\n******yeahhhh %s found a ladder .. go 4 step further******\n",p1);sleep(1);}
else if(b[l-(pos1*3)]=='s')
	{pos1=pos1-4;printf("\n******uffff %s got bitten by a snake ,,go 4 step back******\n",p1);sleep(1);}*/
	
if(b[l-(pos2*3)]=='l')
	{pos2=pos2+3;printf("\n++++++yeahhhh %s found a ladder .. go 4 step further++++++\n",p2);sleep(1);}
else if(b[l-(pos2*3)]=='s')
	{pos2=pos2-4;printf("\n++++++uffff %s got bitten by a snake ,, go 4 step back+++++++\n",p2);sleep(1);}	


b[(l-(pos2*3))]='+';b[(l-(pos2*3)+1)]='*';
}



else if(pos1!=pos2)
{

/*if(b[l-(pos1*3)]=='l')
	{pos1=pos1+4;printf("\n*****yeahhhh %s found a ladder ..  go 4 step furthure*****\n",p1);sleep(1);}
else if(b[l-(pos1*3)]=='s')
	{pos1=pos1-4;printf("\n*****uffff %s got bitten by a snake ,, go 4 step back*****\n",p1);sleep(1);}*/

if(b[l-(pos2*3)]=='l')
	{pos2=pos2+4;printf("\n+++++yeahhhh %s found a ladder ..  go 4 step furthure+++++\n",p2);sleep(1);}
else if(b[l-(pos2*3)]=='s')
	{pos2=pos2-4;printf("\n+++++uffff %s got bitten by a snake ,,  go 4 step back+++++\n",p2);sleep(1);}

b[(l-(pos2*3))]='+';b[(l-(pos2*3))+1]='+';
}
    


	/*int oldpos1=pos1;
	int oldpos2=pos2;

	
	if(oldpos1==oldpos2)
	{
	b[(l-(oldpos2*3))]=c[(l-(oldpos2*3))];b[(l-(oldpos1*3))+1]=c[(l-(oldpos1*3))+1];
	}
	else
	{
	b[(l-(oldpos1*3))]=c[(l-(oldpos1*3))];b[(l-(oldpos1*3))+1]=c[(l-(oldpos1*3))+1];
	b[(l-(oldpos2*3))]=c[(l-(oldpos2*3))];b[(l-(oldpos2*3))+1]=c[(l-(oldpos2*3))+1];
	}*/

printf("\n%s\n",b);
write(fd,b,152);
read(fd,b,152);

    
    sem_post(&mutex);
    printf("\nplayer one chance\n");
    return NULL; 
} 
int main()
{
strcpy(c,b);
l=strlen(b);
fd=open("/dev/mad",O_RDWR);

sem_init(&mutex, 0, 1);
pthread_t thread_id1, thread_id2; 
system("clear");
printf("welcome to snake & ladder game\n");
printf("enter 1st player name\n");
gets(p1);
printf("enter 2nd player name\n");
gets(p2);
printf("hello %s and %s here the game begins\n\n",p1,p2);
sleep(2);




while(flag!='q' && pos1<=50 && pos2<=50)
{
system("clear");
printf("///////////////////////////////////////////////////////////////////////////////\n");
printf("\nplease press \" ENTER \" key to roll dice or \" KEY-- \' q \' \" to quit this game\n\n");

flag=getchar();
printf("%s",c);
printf("\n....................................................\n");

pthread_create(&thread_id1, NULL, player_one, NULL); 
pthread_join(thread_id1, NULL);
sleep(1);



pthread_create(&thread_id2, NULL, player_two, NULL); 
pthread_join(thread_id2, NULL);

printf("\nposition of %s is %d \nposition of %s is %d\n\n",p1,pos1,p2,pos2);
	
	int oldpos1=pos1;
	int oldpos2=pos2;

	
	if(oldpos1==oldpos2)
	{
	b[(l-(oldpos2*3))]=c[(l-(oldpos2*3))];b[(l-(oldpos1*3))+1]=c[(l-(oldpos1*3))+1];
	}
	
	else
	{
	b[(l-(oldpos1*3))]=c[(l-(oldpos1*3))];b[(l-(oldpos1*3))+1]=c[(l-(oldpos1*3))+1];
	b[(l-(oldpos2*3))]=c[(l-(oldpos2*3))];b[(l-(oldpos2*3))+1]=c[(l-(oldpos2*3))+1];
	}

printf("///////////////////////////////////////////////////////////////////////////////\n");
if(win(pos1,pos2))
{
break;
}
flag=getchar();
}
printf("Game OVER (-_-)\n"); 
sem_destroy(&mutex);
}
