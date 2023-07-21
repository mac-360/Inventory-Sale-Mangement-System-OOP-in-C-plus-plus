#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include <ctime>
#include <chrono>
#include<thread>
#include <string>
#include"Products.h"
#include"Ledger.h"
using namespace std;
int
main()
{
	int choice;
	Ledger L;
	string consumer;

	bool validInput = false;	// Initialize validInput here

	do
	{
		cout << "Press 1 for adding a new entry to the file:\n";
		cout << "Press 2 for removing an entry from the file:\n";
		cout << "Press 3 for updating an entry from the file:\n";
		cout <<"Press 4 for displaying an entry from the file according to your search criteria:\n";
		cout <<"Press 5 for displaying total sales done in a certain year/month/day:\n";
		cout << "Press 6 for displaying a certain consumer credit:\n";
		cout << "Press 7 for displaying the total credit:\n";
		cout << "Press 8 for adding a new sale:\n";
		cout <<"Press 9 for checking if a person has credit account with you :\n";
		cout << "Press 10 to exit the program:\n";
		cin >> choice;

		switch (choice)
		{
		case 1:
			L.AddData();
			break;
		case 2:
			L.removeData();
			break;
		case 3:
			L.updateData();
			break;
		case 4:
			L.Display();
			break;
		case 5:
			L.ChoiceSalesAnnuallyMonthlyDaily();
			break;
		case 6:
			cin.ignore(numeric_limits < streamsize >::max(), '\n');	// Clear input buffer

			validInput = false;	// Reset validInput for each iteration
			do
			{
				cout << "Kindly Enter the name of the consumer: ";
				getline(cin, consumer);
				consumer = L.ToUpperfunction(consumer);
				if (!L.PersonCredit(consumer))
				{
					cout << "Invalid consumer name. Please try again.\n";
				}
				else
				{
					validInput = true;
				}
			} while (!validInput);
			L.SleepFuntion(1);
			break;
		case 7:
			L.CalculateTotalCredit();
			break;
		case 8:
			L.Sale();
			L.SleepFuntion(1);

			break;
		case 9:
			cout <<
				"Enter the name of the consumer for checking credit existence : ";
			cin.ignore();
			getline(cin, consumer);
			consumer = L.ToUpperfunction(consumer);
			if (L.CheckCreditExist(consumer))
			{
				cout << "Mr/s " << consumer << " have an account with us \n";
			}
			else
			{
				cout << "Mr/s " << consumer <<
					" do mot have an account with us \n";
			}
			L.SleepFuntion(1);

			break;
		case 10:
			cout << "Exiting the program.\n";
			L.SleepFuntion(1);
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
			validInput = false;	// Initialize validInput to false for the default case
			L.SleepFuntion(1);
			break;
		}
	} while (choice != 10);

	return 0;
}
