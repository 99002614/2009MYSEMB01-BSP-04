** Test Plan **


|Product|Description|	Expected Input|	Expected Output|	Actual Output|
|-------|-----------|---------------|----------------|----------------|
|H_02_L_01|	Dies should not give zero|	Random value is 1 to 6|	User should get dice value|	Same as expected O/P|
|H_02_L_02|If dice is 6.| Chance to play again|	Dice value should be 6|	Player pawn is moving to position|	Pawn move 6+ times as in dice|
|H_02_L_03|	if position is with snake	Dice value + position|	-4 positions from snake position|	If snake and ladder then +- position|
|H_02_L_04|	if position is with ladder|	Dice value + position|3+ positions from snake position|	If snake and ladder then +- position|
|H_02_L_05|	Position value should be in 0 to 50|	Dice value + position|	Should not exceed 50|	Value less than 50 and more than 0|
|H_02_L_06|	Board value should be updated|	Update the table by actual position|	Position number|	Position number|
|H_02_L_07|	Snake or ladder action displayed|	Dice value + pos + snake or ladder|	Printing the action|	Printing the value|
|H_02_L_08|	Board display| 	Updated board|	Printing reference board|	Printing the boards||

