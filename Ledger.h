#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include <ctime>
#include <chrono>
#include<thread>
#include <string>
#include <limits>
#include"Products.h"
using namespace std;



class Ledger :public Products
{

protected:
	float sales;	//total sales
	float CashRecovery;		//CashRecovery
	string ConsumerCashRecovery;	//from which user cash is recived
	unsigned int production;	//for adding a product
	vector < float >VectorPurchasePrice;

	vector < float >VectorSalePrice;

	vector < string > VectorConsumerName;

	vector < string > VectorProductName;

	vector < int >VectorNoOfItems;

public:
	Ledger(float sales = 0.0, float CashRecovery =
		0.0, string ConsumerCashRecovery = " ", int production =
		0)
	{

		this->sales = sales;

		this->CashRecovery = CashRecovery;

		this->ConsumerCashRecovery = ConsumerCashRecovery;

		this->production = production;

	}
	void Sale()
	{

		static bool namein = false;


		string consumer;		//for consumer name
		if (!namein)
		{

			cout << "The name of the consumer : ";

			cin.ignore();

			getline(cin, consumer);

			consumer = ToUpperfunction(consumer);

			namein = true;

		}


		string ProductToBuy;

		bool check = false;

		char Exit;

		while (!check)
		{

			cout << "What do you want to buy : \n";

			cin >> ProductToBuy;

			ProductToBuy = ToUpperfunction(ProductToBuy);

			unsigned int settle = 0;

			check = CheckForProductName(settle, ProductToBuy);

			if (!check)
			{

				cout << "Enter a valid Product name : \n";

				char choice;

				cout << "Do you want to search by product type : ";

				cin >> choice;

				if (choice == 'Y' || choice == 'y')
				{

					string producttype;

					cout << "Enter product type : ";

					cin.ignore();

					getline(cin, producttype);

					producttype = ToUpperfunction(producttype);

					Display(producttype, true);

				}


			}



		}

		unsigned int neededmat;

		float Pprice, Sprice;

		cout << "Enter how much material do you need of product " << ProductToBuy
			<< endl;

		cin >> neededmat;

		CheckForProductName(neededmat, ProductToBuy);

		UpdateItemNo(ProductToBuy, neededmat);

		float TotalBill =
			CalculateSales(consumer, ProductToBuy, neededmat, Pprice, Sprice);

		VectorNoOfItems.push_back(neededmat);

		AddDatatoVectors(ProductToBuy, VectorProductName, VectorSalePrice,
			VectorPurchasePrice);

		cout << "Do you want to quit press E : ";

		cin >> Exit;

		while (Exit != 'E' && Exit != 'e')

		{

			Sale();

		}

		if (Exit == 'E' || Exit == 'e')
		{

			RemoveDuplicatesfromVectors(VectorProductName, VectorSalePrice,
				VectorNoOfItems);

			GenerateBill(consumer, VectorProductName, VectorSalePrice,
				VectorNoOfItems);

			FileOuputforSales(consumer, VectorProductName, VectorSalePrice,
				VectorNoOfItems, VectorPurchasePrice);

			char PaymentChoice;

			float Payment = 0;

			cout << "Enter C/c for Credit or P/p for Payment : ";

			cin >> PaymentChoice;

			while (PaymentChoice != 'C' && PaymentChoice != 'c'
				&& PaymentChoice != 'P' && PaymentChoice != 'p')

			{

				cout <<
					"Invalid choice. Please enter C/c for Credit or P/p for Payment: ";

				cin >> PaymentChoice;

			}

			if (PaymentChoice == 'P' || PaymentChoice == 'p')
			{

				cout << "How much would you like to pay : ";

				cin >> Payment;

				while (Payment < 0)
				{

					cout << "Enter Payment Again : ";

					cin >> Payment;

				}


			}

			if (Payment < TotalBill || PaymentChoice == 'C'
				|| PaymentChoice == 'c')
			{

				float finalBill = TotalBill - Payment;

				std::chrono::system_clock::time_point now =
					std::chrono::system_clock::now();


				// Convert the time to a time_t object (seconds since epoch)
				std::time_t now_time_t =
					std::chrono::system_clock::to_time_t(now);


				// Convert time_t to a string representation
				char time_str[100];

				struct tm time_info;

				if (localtime_s(&time_info, &now_time_t) == 0)
				{

					std::strftime(time_str, sizeof(time_str), "%Y-%m-%d",
						&time_info);

				}

				if (!CheckCreditExist(consumer))
				{

					ofstream outputfile("Credit.txt", ios::app);

					if (outputfile.is_open())
					{

						outputfile << consumer << " " << to_string(finalBill) <<
							" " << time_str << endl;

					}


				}

				else
				{

					UpdateConsumerCredit(consumer, finalBill, time_str);

				}


			}

			return;


		}

	}

	void UpdateConsumerCredit(string consumername, float final_bill,
		string time)
	{

		ifstream filerdr("Credit.txt");

		ofstream outputfile("Temp.txt");

		string line;

		string consumer, date, credit;

		float FloatCredit;

		if (filerdr.is_open())
		{

			while (getline(filerdr, line))
			{

				istringstream ss(line);

				ss >> consumer;

				ss >> credit;

				ss >> date;

				FloatCredit = stof(credit);

				if (consumer == consumername)
				{

					FloatCredit = FloatCredit + final_bill;

					outputfile << consumer << " " << to_string(FloatCredit) <<
						" " << time << endl;

				}

				else
				{

					outputfile << consumer << " " << credit << " " << date <<
						endl;

				}

			}

			filerdr.close();

			outputfile.close();

			remove("Credit.txt");

			rename("Temp.txt", "Credit.txt");

		}

		else
		{

			cout << "Unable to Open file\n";

		}

	}

	void RemoveDuplicatesfromVectors(vector < string >& NameofProductsBought,
		vector < float >& SalePrice,
		vector < int >& NofItemsBought)
	{

		// Create vectors to store unique products and their corresponding quantities
		vector < string > uniqueProducts;

		vector < int >uniqueQuantities;


		// Iterate through the original vectors
		for (size_t i = 0; i < NameofProductsBought.size(); ++i)

		{

			// Check if the product is already in the uniqueProducts vector
			auto it =
				find(uniqueProducts.begin(), uniqueProducts.end(),
					NameofProductsBought[i]);

			if (it != uniqueProducts.end())

			{

				// If the product is already in the uniqueProducts vector, update the quantity
				size_t index = distance(uniqueProducts.begin(), it);

				uniqueQuantities[index] += NofItemsBought[i];

			}

			else

			{

				// If the product is not in the uniqueProducts vector, add it with its quantity
				uniqueProducts.push_back(NameofProductsBought[i]);

				uniqueQuantities.push_back(NofItemsBought[i]);

			}

		}


		// Update the original vectors with the non-duplicate elements and their quantities
		NameofProductsBought = uniqueProducts;

		NofItemsBought = uniqueQuantities;

	}

	void AddDatatoVectors(string ProductName,
		vector < string >& NameofProductsBought,
		vector < float >& SalePrice,
		vector < float >& PurshasePrice)
	{

		ifstream filerdr("Inventory.txt");

		string line;

		string skip;

		string sp;

		string ps;

		string product;

		if (filerdr.is_open())
		{

			while (getline(filerdr, line))
			{

				istringstream ss(line);

				ss >> product;

				ss >> skip;

				ss >> skip;

				ss >> ps;

				ss >> sp;

				ss >> skip;

				if (product == ProductName)
				{

					NameofProductsBought.push_back(product);

					SalePrice.push_back(stof(sp));

					PurshasePrice.push_back(stof(ps));

					return;

				}

			}

			filerdr.close();

		}

		else
		{

			cerr << "Unable to open the file ! \n";

		}

	}

	float CalculateSales(string consumer, string product, int mat,
		float& Pprice, float& Sprice)
	{

		ifstream filerdr("Inventory.txt");

		string nameofproduct;

		string skip;

		string line;

		string Purschaseprice, Saleprice;

		if (filerdr.is_open())
		{


			while (getline(filerdr, line))
			{

				istringstream ss(line);

				ss >> nameofproduct;

				ss >> skip;

				ss >> skip;

				ss >> Purschaseprice;

				ss >> Saleprice;

				if (nameofproduct == product)
				{

					Pprice = stof(Purschaseprice);

					Sprice = stof(Saleprice);

					return stof(Saleprice) * mat;

				}

			}

		}

	}

	void FileOuputforSales(string consumer,
		vector < string >& NameofProductsBought,
		vector < float >& SalePrice,
		vector < int >& NofItemsBought,
		vector < float >PurchasePrice)
	{

		ofstream fileout("Sales.txt", ios::app);

		std::chrono::system_clock::time_point now =
			std::chrono::system_clock::now();


		// Convert the time to a time_t object (seconds since epoch)
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);


		// Convert time_t to a string representation
		char time_str[100];

		struct tm time_info;

		if (localtime_s(&time_info, &now_time_t) == 0)
		{

			std::strftime(time_str, sizeof(time_str), "%Y-%m-%d", &time_info);

		}

		if (fileout.is_open())
		{

			fileout << consumer << " ";

			for (int i = 0; i < NameofProductsBought.size(); i++)
			{

				fileout << NameofProductsBought[i] << " " << NofItemsBought[i] <<
					" " << PurchasePrice[i] << " " << SalePrice[i] << " " <<
					SalePrice[i] * NofItemsBought[i] << " " << time_str << endl;

			}
		}




	}
	void GenerateBill(string consumer,
		vector < string >& NameofProductsBought,
		vector < float >& SalePrice,
		vector < int >& NofItemsBought)
	{

		std::chrono::system_clock::time_point now =
			std::chrono::system_clock::now();


		// Convert the time to a time_t object (seconds since epoch)
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);


		// Convert time_t to a string representation
		char time_str[100];

		struct tm time_info;

		if (localtime_s(&time_info, &now_time_t) == 0)
		{

			std::strftime(time_str, sizeof(time_str), "%H:%M:%S", &time_info);

		}

		cout << "Mr/s  " << consumer << endl;

		cout << time_str << endl;

		cout << "Product\t\tNo Items\tUnit Price\tPrice\n";

		float TotalBill = 0;

		for (int i = 0; i < NameofProductsBought.size(); i++)
		{

			cout << NameofProductsBought[i] << "\t\t" << NofItemsBought[i] <<
				"\t\t" << SalePrice[i] << "\t\t" << SalePrice[i] *
				NofItemsBought[i] << endl;

			TotalBill += SalePrice[i] * NofItemsBought[i];

		}
		cout << endl << endl;

		cout << "--------------------------------\n";

		cout << "Total Bill is $: " << TotalBill << endl;

		cout << "--------------------------------\n";

	}
	bool CheckCreditExist(string Consumer)
	{


		ifstream filerdr("Credit.txt");

		string line;

		string consumer;

		string credit;

		string date;

		if (filerdr.is_open())
		{

			while (getline(filerdr, line))
			{

				istringstream ss(line);

				ss >> consumer;

				ss >> credit;

				ss >> date;

				if (Consumer == consumer)
				{

					return true;

				}

			}

		}

		if (!filerdr)
		{

			cout << "Unable to open file \n";

		}

		return false;

	}

	bool PersonCredit(string consumer)
	{

		ifstream filerdr("Credit.txt");

		string line;

		string name, credit, date;


		if (filerdr.is_open())
		{

			while (getline(filerdr, line))
			{

				istringstream ss(line);

				ss >> name;

				ss >> credit;

				ss >> date;

				if (name == consumer)
				{

					cout << "Mr/s " << consumer << " your credit of $ " << credit
						<< " is left \n";

					cout << "Last Account updated on " << date << endl;

					return true;

				}

			}

		}

		filerdr.close();

		cout << "Unable to find any credit for Mr/s " << consumer << endl;

		return false;



	}

	bool CalculateSalesYMD(const string& YorMorD, char choice)
	{

		ifstream filerdr("Sales.txt");

		string line;

		float totalSales = 0.0f;

		bool found = false;


		if (filerdr.is_open())
		{

			while (getline(filerdr, line))
			{

				istringstream ss(line);

				string skip;


				// Skip the first five fields
				for (int i = 0; i < 5; ++i)
				{

					ss >> skip;

				}

				string amount;

				string date;

				ss >> amount;

				ss >> date;


				// Extract the year, month, and day from the date string
				string yearStr = date.substr(0, 4);

				string monthStr = date.substr(5, 2);

				string dayStr = date.substr(8, 2);


				// Check if the date matches the given YorMorD based on the choice
				switch (choice)
				{

				case 'a':

					if (yearStr == YorMorD)
					{

						found = true;

						totalSales += stof(amount);

					}

					break;

				case 'm':

					if (yearStr + monthStr == YorMorD)
					{

						found = true;

						totalSales += stof(amount);

					}

					break;

				case 'd':

					if (yearStr + monthStr + dayStr == YorMorD)
					{

						found = true;

						totalSales += stof(amount);

					}

					break;

				default:

					cout <<
						"Error: Invalid choice. Please use 'a', 'm', or 'd'.\n";

					filerdr.close();

					return false;

				}

			}


			filerdr.close();

		}

		else
		{

			cout << "Error: Could not open file Sales.txt\n";

		}


		if (found)
		{

			cout << "The sales " << choice << " are: " << totalSales << endl;

		}

		else
		{

			cout << "No sales found for the specified input." << endl;

		}


		return found;

	}

	void ChoiceSalesAnnuallyMonthlyDaily()
	{

		char choice;

		bool found = false;


		do
		{

			cout <<
				"Enter whether you want to see annual(A/a), monthly(M/m), or daily sale(D/d): ";

			cin >> choice;


			// Convert the input to lowercase for case-insensitive comparison
			choice = tolower(choice);


			// Validate the input
			if (choice != 'a' && choice != 'm' && choice != 'd')
			{

				cout <<
					"Invalid choice. Please enter 'A/a' for annual, 'M/m' for monthly, or 'D/d' for daily sale."
					<< endl;

			}

		} while (choice != 'a' && choice != 'm' && choice != 'd');


		switch (choice)
		{

		case 'a':

			unsigned int year;

			cout << "Which year: ";

			cin >> year;

			found = CalculateSalesYMD(to_string(year), 'a');

			break;

		case 'm':

			int yearAndMonth;

			cout << "Enter year and month in format 'YYYYMM': ";

			cin >> yearAndMonth;

			found = CalculateSalesYMD(to_string(yearAndMonth), 'm');

			break;

		case 'd':

			int yearMonthAndDate;

			cout << "Enter year, month, and date in format 'YYYYMMDD': ";

			cin >> yearMonthAndDate;

			found = CalculateSalesYMD(to_string(yearMonthAndDate), 'd');

			break;

		default:

			cout << "Wrong choice\n";

			break;

		}

	}

	void CalculateTotalCredit()
	{

		ifstream filerdr("Credit.txt");

		string line;

		string name;

		string credit;

		string date;

		float Total_Credit = 0.0;

		if (filerdr.is_open())
		{

			while (getline(filerdr, line))
			{

				istringstream ss(line);

				ss >> name;

				ss >> credit;

				ss >> date;

				Total_Credit += stof(credit);

			}

		}

		filerdr.close();

		cout << "The Total Credit is : $ " << Total_Credit << endl;

		SleepFuntion(3);

	}

};
