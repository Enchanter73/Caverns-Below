#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* This is a game where you need to defeat 7 main boss to finish. In order to do that
you need strenghten your character, buy items, and do the battles correctly */
int ch,Maxhealth,Health,Attack,Maxmana,Mana,Skill;
int Level=1,Day=1,Gold=0,EXP=0,Floor=1;
int EnemyAttack,EnemyHealth;
int healthpotion=0,manapotion=0;
bool CavernEnemy,win,gamefinished=false,WhichCharacter,WinCavern;
bool GlovesOfThief=false,ShoesOfHermes=false;

void gainingEXPandGold()    //You gain your rewards here after a win
{
	int EXPneeded,money,money2;
	
	if(GlovesOfThief=false) //An item you buy from market increases your rewards
	{
		money=25;
		money2=5;
	}
	else
	{
		money=30;
		money2=6;		
	}
	EXPneeded=Level*50;    //Decides the needed exp for you to level up
	switch(CavernEnemy)    //Decides which enemy you fight against
	{
		case true:		   
			printf("You Gained %d EXP!\n",(Floor*25));
			printf("You Gained %d Gold!\n",(Floor*money));
			EXP=EXP+(Floor*30);
			Gold=Gold+(Floor*money);			
			break;
		case false:
			printf("You Gained %d EXP!\n",(Level*16));
			printf("You Gained %d Gold!\n",(Level*money2));
			EXP=EXP+(Level*16);
			Gold=Gold+(Level*money2);						
			break;
	}	
	if(EXP>EXPneeded)   //Checks if you gained enough Exp to upgrade your level
	{
		printf("\nLEVEL UP! \n");
		switch(WhichCharacter)  //It increases your stats depending on our chaarcter choice
		{
			case true:
				printf("Your Attack: +25\n");
				printf("Your Health: +60\n");
				Attack=Attack+25;
				Maxhealth=Maxhealth+60;
				Health=Maxhealth;
				Mana=Maxmana;							
				break;
			case false:
				printf("Your Attack: +15\n");
				printf("Your Health: +120\n");
				Attack=Attack+15;
				Maxhealth=Maxhealth+120;
				Health=Maxhealth;
				Mana=Maxmana;				
				break;
		}		
		EXP=EXP-EXPneeded;
		Level++;
	}	
}
void BattleResult()  //Show you what happened depending on your victory or defeat
{
	if(win==true)    //This is what happens when you win
	{
		printf("You won the fight!\n");
		if(CavernEnemy)   //Checks if you win against a Cavern Enemy
		{
			WinCavern=true;  //It saves as true so that you can fight against the next enemy
			Floor++;     //Your enemy's stats depends on which floor you are at
		}		
		gainingEXPandGold();  	
	}
	else
	{
		if(CavernEnemy)
		{
			WinCavern=false;
		}
		printf("You lost, but you managed to survive!\n");
		printf("and you spent three days to recover. \n");
		Health=Maxhealth;   //Recovers your health and mana in a defeat situation
		Mana=Maxmana;
		Day+=2;
	}
	Day++;
}
int Attacking()  //This is where you make your attack during fights
{
	int damage;
	printf("---------------------------------------------------------------\n");
	printf("Your Remaining Health: %d ------- Enemy's Remaining Health: %d \n",Health,EnemyHealth);
	printf("Your Remaining Mana: %d \n",Mana);
	printf("---------------------------------------------------------------\n");
	scanf("%d",&Skill);   //Asks you which attack are you going to do
	switch(Skill)
	{
		case 1:         
			damage=rand()%20+(Attack-10);
			EnemyHealth=EnemyHealth-damage;	
			printf("You hit for %d!\n",damage);			
			break;
		case 2:
			if(Mana<25)      //Checks if you have enough mana to do this attack
			{
				printf("You don't have enough mana to use this attack! \n\n");
				Attacking();    //if not, it returns to choosing attack again
				return 0;
			}
			damage=rand()%20+(Attack);
			EnemyHealth=EnemyHealth-damage;
			printf("You hit for %d!\n",damage);
			Mana=Mana-25;
			break;
		case 3:
			if(Mana<50)     //Checks if you have enough mana to do this attack
			{
				printf("You don't have enough mana to use this attack! \n");
				Attacking();       //if not, it returns to choosing attack again
				return 0;
			}
			damage=rand()%40+(Attack);
			EnemyHealth=EnemyHealth-damage;
			printf("You hit for %d!\n",damage);
			Mana=Mana-50;
			break;
		case 4:
			printf("1-Use a Health potion \n");
			printf("2-Use a Mana potion \n");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					if(healthpotion>0)
					{
						Health+=(Maxhealth/2);
						if(Health>Maxhealth) Health=Maxhealth;
						healthpotion--;
						printf("You still have %d Health potion\n",healthpotion);
					}
					else
					{
						printf("You don't have any Health potion\n");
						Attacking();
					}
					break;
				case 2:
					if(manapotion>0)
					{
						Mana+=(Maxmana/2);
						if(Mana>Maxmana) Mana=Maxmana;
						manapotion--;
						printf("You still have %d Mana potion\n",manapotion);
					}
					else
					{
						printf("You don't have any Mana potion\n");
						Attacking();
					}
					break;
			}
	}	
}
int Battle()    //This where battle begins
{
	int twiceattack,enemydamage;
	printf("1-Normal Attack \n");
	printf("2-Powerful Attack - Requires 25 Mana \n");
	printf("3-Ultimate Attack - Requires 50 Mana \n");
	printf("4-Use a potion \n\n");
	
	while(Health>0 && EnemyHealth>0)  //You and your enemy attack in a loop
	{
		Attacking();    			//You always attack first
		if(EnemyHealth<=0)          //Checks if you killed your enemy
		{
			win=true;				
			BattleResult();			
			return 0;				//if you win the fight, finishes the battle
		}
		if(ShoesOfHermes==true)     //An item that works in battles
		{
			twiceattack=rand()%100;   //it gives you a chance to attack twice
			if(twiceattack>70)
			{
				printf("You get to attack again! Thanks to Shoes of Hermes!\n");
				Attacking();
				if(EnemyHealth<=0)          //Checks if you killed your enemy
				{
					win=true;				
					BattleResult();			
					return 0;				
				}
			}
		}
		enemydamage=rand()%20+(EnemyAttack-10);    //decides how much damage your enemy will deal
		Health=Health-enemydamage;
		printf("Your enemy hit for %d!\n",enemydamage);
	}
	win=false;
	BattleResult();	
	return 0;
}
int Attackincrease=0,Healthincrease=0;
int NewEnemyAttack=15,NewEnemyHealth=75;
void createnemyforCavern()     //Decides the power of your enemies in Caverns
{	
	CavernEnemy=true;	
	EnemyAttack=NewEnemyAttack;		//Saves your enemies attack point and health so tht	
	EnemyHealth=NewEnemyHealth;		//it can increase them when you move on the next battle
	
	if(Floor>1 && WinCavern)		
	{
		Attackincrease=10+((Floor-1)*5);	//increasing oppenents attack and health when you
		EnemyAttack+=Attackincrease;		//move on the next battle
		Healthincrease=50+((Floor-1)*25);
		EnemyHealth+=Healthincrease;
	}	
	NewEnemyAttack=EnemyAttack;
	NewEnemyHealth=EnemyHealth;				
	Battle();						//Goes to battle after it creats your enemy
}
void createnemyforJungle()          //This is for other enemy that you fight in order to
{									//level up your character
	CavernEnemy=false;
	EnemyAttack=Level*20;			//That's why it's power depends on your level
	EnemyHealth=(Level*50)+30;
	Battle();
}
void Market()					//This is where you buy items for your character
{
	printf("1.Health potion |Cost 30| When used, recovers half of your Health (Can be used during battles) \n");
	printf("2.Mana potion |Cost 30| When used, fully recovers your Mana (Can be used during battles) \n");
	if(GlovesOfThief==false) printf("3.Gloves of Thief |Cost 125| You earn %20 more gold from battles (Can be bought only once!)\n");
	if(ShoesOfHermes==false) printf("4.Shoes of Hermes |Cost 300| Gives %30 chance to attack twice in a row (Can be bought only once!)\n");
	printf("0 - Go back to main menu\n");
	
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			if(Gold<30)			//Checks if you have enough gold to buy the item
			{
				printf("you don't have enough Gold \n");
				Market();
			}
			printf("You bought a Health potion \n");			
			healthpotion++;
			printf("You have %d Health potion now\n",healthpotion);
			Gold=Gold-30;
			break;
		case 2:
			if(Gold<30)
			{
				printf("you don't have enough Gold \n");
				Market();
			}
			printf("You bought a Mana potion \n");
			manapotion++;
			printf("You have %d Mana potion now\n",manapotion);
			Gold=Gold-30;
			break;
		case 3:
			if(Gold<125)
			{
				printf("you don't have enough Gold \n");
				Market();
			}
			printf("You bought the Gloves of Thief \n");
			GlovesOfThief=true;
			Gold=Gold-125;
			break;
		case 4:
			if(Gold<300)
			{
				printf("you don't have enough Gold \n");
				Market();
			}
			printf("You bought the Shoes of Hermes \n");
			ShoesOfHermes=true;
			Gold=Gold-300;
			break;
	}		
}
void MainMenu()			//This is where you decide what you do
{
	printf("----------------\n");
	printf("Your Level: %d \nYour Health: %d/%d \nYour Mana: %d/%d \nYour Attack: %d \nGold: %d \n"
	,Level,Health,Maxhealth,Mana,Maxmana,Attack,Gold);	
	printf("--------------------------------------------------------------------------------------------------------------\n");
	printf("Day %d \n",Day);
	printf("1.Go to the Caverns --- 2.Go to the Jungle to strenghten your hero --- 3.Rest for a day --- 4.Go to the Market\n");
	printf("--------------------------------------------------------------------------------------------------------------\n");
	
	scanf("%d",&ch);	
	switch(ch)
	{
		case 1:
			printf("FLOOR %d \n",Floor);
			createnemyforCavern();
			break;
		case 2:
			createnemyforJungle();
			break;
		case 3:
			printf("You rest for a day, your health and mana are full now\n");
			Health=Maxhealth;
			Mana=Maxmana;
			Day++;
			break;
		case 4:
			Market();
			break;		
	}		
}
int main()
{	
	srand((unsigned) time(NULL));
	
	printf("Welcome to The Caverns Below! \n");
	printf("Before you start your run, choose a character! \n");
	printf("1.Assassin (Has low health, but high attack damage! Ideal to finish battles faster.) \n");
	printf("2.Warrior (Has less attack damage, but very high health! Good for players who like playing safe!) \n");
	
	scanf("%d",&ch);	//You choose your character here
	switch(ch)
	{
		case 1:
			WhichCharacter=true;		
			Maxhealth=50;
			Health=Maxhealth;
			Attack=30;
			Maxmana=100;
			Mana=Maxmana;
			break;
		case 2:
			WhichCharacter=false;
			Maxhealth=130;
			Health=Maxhealth;
			Attack=15;
			Maxmana=100;
			Mana=Maxmana;
			break;				
	}	
	while(gamefinished==false) 		//This loop goes forever until you finish the game
	{
		MainMenu();
		if(Floor==8)			//Checks if you finished the game
		{
			gamefinished=true;
		}
	}
	printf("CONGURALATIONS!!! YOU FINISHED THE GAME!!!");
	printf("You score is: %d \n",150-Day);		//Decides your score depending on how fast you finished the game
	
	system("pause");
	return 0;
}											//SELIM CESUR          B1605.010003
