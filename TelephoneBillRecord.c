#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct subscriber
{
	char phonenumber[20];
	char name[50];
	float amount;
} s;

void addrecords();
void listrecords();
void deleterecords();
void searchrecords();

int main()
{
	int phonenumber;
	char choice;

	system("cls");
	printf("****************************************************************");
	printf("\n  ------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM------");
	printf("\n****************************************************************");
	printf("\n\n\n Press Any Key To Continue. . ");
	getch();
	system("cls");

	printf("\n\nTELECOM BILLING SYSTEM");

	while (1)
	{
		printf(" \n\n 1 : Add New Records.\n\n 2 : List Of Records");
		printf("\n\n 3 : Search Records.");
		printf("\n\n 4 : Delete Records.\n\n 5 : Exit\n");
		printf("\n Enter Your Choice:-");
		choice = getche();

		switch (choice)
		{
		case '1':
			addrecords();
			break;
		case '2':
			listrecords();
			break;	
		case '3':
			searchrecords();
			break;
		case '4':
			deleterecords();
			break;
		case '5':
			system("cls");
			printf("Thank you");
			getch();
			exit(0);
			break;
		default:
			system("cls");
			printf("Incorrect Input \n");
			printf("Press Any key to continue");
			getch();
		}
	}
}

void addrecords()
{
	FILE *f;
	char test;
	f = fopen("pro.txt", "ab+");
	if (f == 0)
	{
		f = fopen("pro.txt", "wb+");
		system("cls");
		printf("Please wait while we configure your computer");
		printf("\npress any key to continue");
		getch();
	}
	while (1)
	{
		system("cls");
		printf("\n Enter phone number: ");
		scanf("%s", &s.phonenumber);
		printf("\n Enter name: ");
		fflush(stdin);
		scanf("%s", &s.name);
		printf("\n Enter amount: ");
		scanf("%f", &s.amount);
		fwrite(&s, sizeof(s), 1, f);
		fflush(stdin);
		printf("\n\n Record Is Successfully Added");
		printf("\n Press esc Key to exit or Press any other key to add other record:");
		test = getche();
		if (test == 27)
			break;
	}
	fclose(f);
	system("cls");
}
void listrecords()
{
	FILE *f;
	int i;
	if ((f = fopen("pro.txt", "rb")) == NULL)
		exit(0);
	system("cls");
	printf("Phone Number\t\tUser Name\tAmount\n");
	for (i = 0; i < 79; i++)
		printf("-");
	while (fread(&s, sizeof(s), 1, f) == 1)
	{
		printf("\n%s\t\t%s\t\tRs. %.2f /-", s.phonenumber, s.name, s.amount);
	}
	printf("\n");
	for (i = 0; i < 79; i++)
		printf("-");

	fclose(f);
	printf("\n\nPress Any Key To Go Back");
	getch();
	system("cls");
}
void deleterecords()
{
	FILE *f, *t;
	char phonenumber[20];
	system("cls");	
	f = fopen("pro.txt", "rb+");
	t = fopen("pro1.txt", "wb+");
	do
	{
		rewind(f);
		printf("Enter the phone number to be deleted from the Database: ");
		scanf("%s", phonenumber);
		while (fread(&s, sizeof(s), 1, f) == 1)
		{
			if (strcmp(s.phonenumber, phonenumber) != 0)
			{
				fwrite(&s, sizeof(s), 1, t);
			}
			else
				printf("Record deleted successfully.");
		}

		fclose(f);
		fclose(t);
		remove("pro.txt");
		rename("pro1.txt", "pro.txt");

		f = fopen("pro.txt", "rb+");
		t = fopen("pro1.txt", "wb+");
		printf("\nDo you want to delete another record (y/n):");
		fflush(stdin);
	} while (getche() == 'y' || getche() == 'Y');
	fclose(f);
	getch();
	system("cls");
}
void searchrecords()
{
	FILE *f;
	char phonenumber[20];
	int flag = 1;
	f = fopen("pro.txt", "rb+");

	fflush(stdin);
	system("cls");
	printf("Enter Phone Number to search in our database: ");
	scanf("%s", phonenumber);
	while (fread(&s, sizeof(s), 1, f) == 1)
	{
		if (strcmp(s.phonenumber, phonenumber) == 0)
		{
			system("cls");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n", s.phonenumber, s.name, s.amount);
			flag = 0;
			break;
		}
		else if (flag == 1)
		{
			system("cls");
			printf("Requested Phone Number Not found in our database");
		}
	}
	getch();
	fclose(f);
	system("cls");
}
