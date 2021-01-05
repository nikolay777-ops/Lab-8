#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif
using namespace std;
#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>

struct Bustrip
{
	int number;
	char typeofbus[7];
	char destination[20];
	float departure;
	float arrive;
};

void stcreat(int amount, char destination[], Bustrip* &strct)  //struct creation with random
{
	strct = new Bustrip[amount];
	for (int i = 0; i < amount; i++)
	{
		strct[i].number = i+1;
		switch (rand() % 3)
		{
			case 0:
			strct[i].typeofbus[0] = 'L';
			strct[i].typeofbus[1] = 'u';
			strct[i].typeofbus[2] = 'x';
			strct[i].typeofbus[3] = 'u';
			strct[i].typeofbus[4] = 'r';
			strct[i].typeofbus[5] = 'y';
			strct[i].typeofbus[6] = '\0';break;
			case 1:
			strct[i].typeofbus[0] = 'B';
			strct[i].typeofbus[1] = 'i';
			strct[i].typeofbus[2] = 'g';
			strct[i].typeofbus[3] = '\0';break;
			case 2:
			strct[i].typeofbus[0] = 'S';
			strct[i].typeofbus[1] = 'm';
			strct[i].typeofbus[2] = 'a';
			strct[i].typeofbus[3] = 'l';
			strct[i].typeofbus[4] = 'l';
			strct[i].typeofbus[5] = '\0';break;
			case 3:
			strct[i].typeofbus[0] = 'F';
			strct[i].typeofbus[1] = 'a';
			strct[i].typeofbus[2] = 's';
			strct[i].typeofbus[3] = 't';
			strct[i].typeofbus[4] = '\0';break;
		}
		strcpy(strct[i].destination, destination);
		switch (rand() % 5)
		{
			case 0: strct[i].departure = float(11.00);break;
			case 1: strct[i].departure = 11.40;break;
			case 2: strct[i].departure = 12.30;break;
			case 3: strct[i].departure = 13.30;break;
			case 4: strct[i].departure = 13.50;break;
			case 5: strct[i].departure = 14.40;break;
		}
		switch (rand() % 5)
		{
			case 0: strct[i].arrive = 16.00;break;
			case 1: strct[i].arrive = 16.30;break;
			case 2: strct[i].arrive = 17.00;break;
			case 3: strct[i].arrive = 17.30;break;
			case 4: strct[i].arrive = 18.00;break;
			case 5: strct[i].arrive = 18.30;break;
		}
	}
}

Bustrip* addstruct(Bustrip* strct, int amount) // function for addition struct
{
	Bustrip* addstrct = new Bustrip [amount+1];
	for (int i = 0; i < amount + 1; i++)
	{
		addstrct[i].number = strct[i].number;
		strcpy(addstrct[i].typeofbus, strct[i].typeofbus);
		strcpy(addstrct[i].destination, strct[i].destination);
		addstrct[i].departure = strct[i].departure;
		addstrct[i].arrive = strct[i].arrive;
	}
	strct = addstrct;
	delete [] addstrct;
	return strct;
}

int sort1(Bustrip* &strct, float uarrive, int amount)  // sort1 for deleting fields which doesn't satisfy the condition
{
	int z = 0;
	Bustrip* temp = new Bustrip [amount];
	int helper = 0; // counter of fields which doesn't not satisfy the condition
	for (int i = 0; i < amount; i++)
	{
		if (uarrive >= strct[i].arrive)
		{
			temp[z].number = strct[i].number;
			strcpy(temp[z].typeofbus, strct[i].typeofbus);
			strcpy(temp[z].destination, strct[i].destination);
			temp[z].departure = strct[i].departure;
			temp[z].arrive = strct[i].arrive;
			z++;
		}
		else
		{
			helper++;
		}
	}
	strct = temp;
	delete[] temp;
	return helper;
}

void sort2(Bustrip* &strct, int amount)   // sorting by choice
{
	Bustrip* helper = new Bustrip [1];
	for (int i = 0; i < amount - 1; i++)
	{
		int min = i;
		for (int j = i+1 ; j < amount; j++)
		{
			if (strct[j].arrive > strct[min].arrive)
			{
				min = j;
			}
		}
		strcpy(helper[0].typeofbus, strct[i].typeofbus);
		strcpy(helper[0].destination, strct[i].destination);
		helper[0].departure = strct[i].departure;
		helper[0].arrive = strct[i].arrive;
		strcpy(strct[i].typeofbus, strct[min].typeofbus);
		strcpy(strct[i].destination,strct[min].destination);
		strct[i].departure = strct[min].departure;
		strct[i].arrive = strct[min].arrive;
		strcpy(strct[min].typeofbus, helper[0].typeofbus);
		strcpy(strct[min].destination, helper[0].destination);
		strct[min].departure = helper[0].departure;
		strct[min].arrive = helper[0].arrive;
	}
}

void strctdelete1(Bustrip* &strct, int amount, int sub)  // delete fields which doesn't satisfy the condition
{
	int z = 0;
	Bustrip* newstrct = new Bustrip [amount - sub];
	for (int i = 0; i < amount - sub; i++)
	{
		newstrct[z].number = strct[i].number;
		strcpy(newstrct[z].typeofbus, strct[i].typeofbus);
		strcpy(newstrct[z].destination, strct[i].destination);
		newstrct[z].departure = strct[i].departure;
		newstrct[z].arrive = strct[i].arrive;
		z++;
	}
	strct = newstrct;
	delete [] newstrct;
}

void strctdelete2(Bustrip* &strct, int amount, int Var)    // delete the selected element of the structure array
{
	Bustrip* newstrct = new Bustrip [amount - 1];
	for (int i = 0; i < amount; i++)
	{
		if (strct[i].number == Var)
		{
			continue;
		}
		else
		{
			newstrct[i].number = strct[i].number;
			strcpy(newstrct[i].typeofbus, strct[i].typeofbus);
			strcpy(newstrct[i].destination, strct[i].destination);
			newstrct[i].departure = strct[i].departure;
			newstrct[i].arrive = strct[i].arrive;
		}
	}
	strct = newstrct;
	delete [] newstrct;
}

void putout1(Bustrip* strct, int amount) // function for showing structure
{
	for (int i = 0; i < amount; i++)
	{
		printf("Number: %d \n", strct[i].number);
		cout << "Bus: " << strct[i].typeofbus << endl;
		printf("Destination: %s \n", strct[i].destination);
		printf("Departure: %.2f\n", strct[i].departure);
		printf("Arrive: %.2f\n\n", strct[i].arrive);
	}
}

void putout2(Bustrip* strct, int amount, int Var)
{
	for (int i = 0; i < amount; i++)
	{
		if (strct[i].number == 0)
		{
			continue;
		}
		else
		{
			printf("Number: %d \n", strct[i].number);
			cout << "Bus: " << strct[i].typeofbus << endl;
			printf("Destination: %s \n", strct[i].destination);
			printf("Departure: %.2f\n", strct[i].departure);
			printf("Arrive: %.2f\n\n", strct[i].arrive);
		}
	}
}

int main()
{
	srand(time(NULL));
	Bustrip user;
	Bustrip* trip = nullptr;
	int N = 0;
	printf("Hello, Where are you going to go? ");
	scanf("%s",user.destination);  // Структурные переменные user - данные которые ввёл пользователь
	printf("What time would you like to arrive? ");
	scanf("%e",&user.arrive);
	printf("How many variants you want to consider? ");
	scanf("%d",&N);
	stcreat(N, user.destination, trip);
	printf("All variants: \n\n");
	putout1(trip,N); // function for showing structure
	int K = sort1(trip, user.arrive, N);
	strctdelete1(trip, N, K); // delete fields which doesn't satisfy the condition
	int B = N - K;
	sort2(trip, N-K); // descending sorting by choice
	printf("You can select such variants of trip, please enter the number of your future trip: \n\n");
	putout1(trip, B); // function for showing structure
	int Var = 0;
	scanf("%d", &Var);
	printf("\n");
	strctdelete2(trip, B, Var); // delete the selected element of the structure array
	printf("Remaining trips: \n \n");
	putout2(trip, B, Var);
	cout << "Do you want to recommend any combination for future trips? 1/0 (Yes/No) ";
	int A;
	cin >> A;
	if (A == 1)
	{
		addstruct(trip, B);		//function for adding element of structure.
		printf("Number: ");
		scanf("%d",&trip[B].number);
		printf("Bus: ");
		scanf("%s",trip[B].typeofbus);
		printf("Destination: ");
		scanf("%s", trip[B].destination);
		printf("Departure: ");
		scanf("%e", &trip[B].departure);
		printf("Arrive: ");
		scanf("%e", &trip[B].arrive);
		printf("\nThank you very much for using our system and making it better!");
	}
	else
	{
		printf("Thank you very much for using our system! ");
	}
	getch();
	return 0;
}
