# Requirements


**Low level Requirements**


|ID	|description|
|---|------------|
|LL-01|	Two player with should be able enter the game by entering their respective name, and each they are represented as ‘*’ and ‘+’ symbols respectively|
 |LL-02|	Each player gets fair chances to reach 50 along with random obstructions of ladder and snakes.|
|LL-03|	Players should be able to quit game at any point of time along with the game log being stored in a kernel driver.|
|LL-04|	Each player having separate pawns to depict their position on the board. Where positions are depicted as ‘**’ and ‘++’ for player one and two respectively, and ‘*+’ symbol if both pawns are at same position.|
|LL-05|	Threads are maintained with mutex to lock the threads and semaphores to sync between each player threads.|
|LL-06|	A Kernel device driver is equipped with kernel linked list where on each move of player the data of their positions are stored in the linked list.|
|LL-07|	Snake and ladders are present at random spots where ladders make the pawn go 4 steps further and snakes make the pawn go back 4 steps.|
|LL-08|	Srand() function given a seed value of time variable so that the rand() function give a real random value each time called.|
|LL-09|	Kernel driver written with properties of read, write open, close, kfifo, kernel buffer and kernel linked list.|
|LL-10|	Giving each player chance to roll dice again if they get 6 as dice value. other players have to wait for their turn until the other player turns finishes.|
