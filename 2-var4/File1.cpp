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
#include <fstream>

struct Train
{
	char daytime[11];
	char destination[20];
	float deptime;
	int sites;
};

void stcreat(char destination[], Train* &strct)
{
	strct = new Train[7];
	for (int i = 0; i < 7; i++)
	{
		strct[i].daytime[0] = '2';
		strct[i].daytime[2] = '.';
		strct[i].daytime[3] = '0';
		strct[i].daytime[4] = '8';
		strct[i].daytime[5] = '.';
		strct[i].daytime[6] = '2';
		strct[i].daytime[7] = '0';
		strct[i].daytime[8] = '6';
		strct[i].daytime[9] = '1';
		strct[i].daytime[10] = '\0';
		for (int j = 0; j < 7; j++)
		{
			switch (j)
			{
				case 0:
				strct[j].daytime[1] = '1';break;
				case 1:
				strct[j].daytime[1] = '2';break;
				case 2:
				strct[j].daytime[1] = '3';break;
				case 3:
				strct[j].daytime[1] = '4';break;
				case 4:
				strct[j].daytime[1] = '5';break;
				case 5:
				strct[j].daytime[1] = '6';break;
				case 6:
				strct[j].daytime[1] = '7';break;
			}
		}
		strcpy(strct[i].destination, destination);
		switch (rand() % 6)
		{
			case 0: strct[i].sites = 10 ;break;
			case 1: strct[i].sites = 13;break;
			case 2: strct[i].sites = 15;break;
			case 3: strct[i].sites = 17;break;
			case 4: strct[i].sites = 19;break;
			case 5: strct[i].sites = 21;break;
			case 6: strct[i].sites = 23;break;
		}
		switch (rand() % 5)
		{
			case 0: strct[i].deptime = 17.15;break;
			case 1: strct[i].deptime = 18.35;break;
			case 2: strct[i].deptime = 19.35;break;
			case 3: strct[i].deptime = 20.15;break;
			case 4: strct[i].deptime = 21.15;break;
			case 5: strct[i].deptime = 22.35;break;
		}
	}
}

void filecr1(Train* &strct, int amount)
{
	ofstream outfile ("trainstart.txt");
	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			outfile << strct[i].daytime[j];
		}
		outfile << ' ';
		for (int j = 0; strct[i].destination[j] != '\0'; j++)
		{
			outfile << strct[i].destination[j];
		}
		outfile << ' ';
		outfile << strct[i].deptime;
		outfile << ' ';
		outfile << strct[i].sites << "\n";
	}
}

void strctdelete1(Train* &strct, int sub)
{
	int z = 0;
	Train* temp = new Train [7 - sub];
	for (int i = 0; i < 7 - sub; i++)
	{
		if (strct[i].deptime == 0)
		{
			continue;
		}
		else
		{
			strcpy(temp[z].daytime, strct[i].daytime);
			strcpy(temp[z].destination, strct[i].destination);
			temp[z].deptime = strct[i].deptime;
			temp[z].sites = strct[i].sites;
			z++;
		}
	}
	strct = temp;
	delete [] temp;
}

void filecr2(int helper, Train* &strct)
{
	ofstream outfile ("trainsend.txt");
	if (helper == 7)
	{
		outfile << "Sorry, but we cannot fulfill your order in full or we cannot fulfill it at all. Come back another time.";
	}
	else
	{
		outfile << strct[0].deptime;
	}
}

int sort1(Train* &strct, float udeptime, char daytime, int sites)
{
	int z = 0;
	Train* temp = new Train [7];
	int helper = 0; // ������� ����� ������� �� ������������� �������
	for (int i = 0; i < 7; i++)
	{
		if (udeptime >= strct[i].deptime &&  strct[i].daytime[1] == daytime && strct[i].sites <= sites)
		{
			strcpy(temp[z].daytime, strct[i].daytime);
			strcpy(temp[z].destination, strct[i].destination);
			temp[z].deptime = strct[i].deptime;
			temp[z].sites = strct[i].sites;
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

void strctchang(Train* &strct, char daynum, int usites)
{
	for (int i = 0; i < 7; i++)
	{
		if (strct[i].daytime[1] == daynum)
		{
			strct[i].sites -= usites;
		}
	}
}

Train* addstruct(Train* &strct, int amount)
{
	Train* addstrct = new Train [amount];
	for (int i = 0; i < amount; i++)
	{
		strcpy(addstrct[i].daytime, strct[i].daytime);
		strcpy(addstrct[i].destination, strct[i].destination);
		addstrct[i].deptime = strct[i].deptime;
		addstrct[i].sites = strct[i].sites;
	}
	strct = addstrct;
	delete [] addstrct;
	return strct;
}

int _tmain()
{
	srand(time(NULL));
	Train user;
	Train* train;
	printf("Hello, where are you going to go? ");
	scanf("%s", user.destination);
	stcreat(user.destination, train);
	filecr1(train, 7);
	printf("Please, check trainstart.txt file for extension reserving process.\n");
	printf("What day do you want to go? (21.08.2061 - 27.08.2061) ");
	scanf("%s", user.daytime);
	printf("What time do you want to go? (17.15 - 22.35) ");
	scanf("%e", &user.deptime);
	printf("How many sites do you want to reserve? ");
	scanf("%d", &user.sites);
	strctchang(train, user.daytime[1], user.sites);
	filecr1(train, 7);
	int helper = sort1(train, user.deptime, user.daytime[1], user.sites);
	strctdelete1(train, helper);
	filecr2(helper, train);
	printf("Thank you for using our system! Please check trainend.txt, and trainstart.txt if you want to check remaining trains.");
	cout << "\nDo you want to recommend any combination for future trips? 1/0 (Yes/No) ";
	int A;
	cin >> A;
	if (A == 1)
	{
		addstruct(train, 8);				//function for adding element of structure.
		printf("Daytime: ");
		scanf("%s",train[8].daytime);
		printf("Destination: ");
		scanf("%s", train[8].destination);
		printf("Deptime: ");
		scanf("%e", &train[8].deptime);
		printf("Sites: ");
		scanf("%d", &train[8].sites);
		printf("\nThank you very much for using our system and making it better!");
	}
	getch();
	return 0;
}
