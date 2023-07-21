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
using namespace std;

class Products
{


protected:
	unsigned int NoOfItems;
	//for keeping in check the total number of items
	string ProductName;

	string TypeofProduct;	//for checking whick type of thing is required
	float saleprice;

	float purchaseprice;

	bool CheckForProductName(unsigned int& NoOfItemsneeded,
		string productname = " ")
	{

		ifstream filerdr("Inventory.txt");

		string line;

		string nameofproduct;

		string skip;

		int NoofItems;

		bool found = false;

		if (!filerdr.is_open())
		{

			cout << "Error in opening the file.\n";

		}

		if (filerdr.is_open())
		{

			while (getline(filerdr, line))
			{

				istringstream ss(line);

				ss >> nameofproduct;

				ss >> skip;

				ss >> NoofItems;

				if (nameofproduct == productname)
				{

					cout << "Product Exists \n";

					while (NoOfItemsneeded > NoofItems)
					{

						cout << "The inventory is short : \n";

						cout << "Max Items of product " << nameofproduct <<
							" are " << NoofItems << endl;

						cin >> NoOfItemsneeded;

					}

					found = true;

					return found;

				}

			}

		}

		filerdr.close();

		return found;

	}

	void UpdateItemNo(string productname, int itemno)
	{

		string filename = "Inventory.txt";

		string nameofproduct, skip, Pprice, Sprice, profit;

		int NoofItems;


		ifstream filerdr("Inventory.txt");

		if (filerdr.is_open())
		{

			ofstream fileoutputrdr("temp.txt");

			if (fileoutputrdr.is_open())
			{

				string line;

				while (getline(filerdr, line))
				{

					istringstream ss(line);

					ss >> nameofproduct;

					ss >> skip;

					ss >> NoofItems;

					ss >> Pprice;

					ss >> Sprice;

					ss >> profit;

					if (nameofproduct == productname)
					{

						int modifiedNoofItems = NoofItems - itemno;

						fileoutputrdr << nameofproduct << " " << skip << " " <<
							to_string(modifiedNoofItems) << " " << Pprice << " " <<
							Sprice << " " << profit << endl;

					}

					else
					{

						fileoutputrdr << nameofproduct << " " << skip << " " <<
							to_string(NoofItems) << " " << Pprice << " " << Sprice
							<< " " << profit << endl;

					}

				}

			}

			fileoutputrdr.close();

		}

		filerdr.close();

		remove(filename.c_str());

		rename("temp.txt", filename.c_str());

		cout << "Updated successfully\n";


	}

public:
	//Default constructor
	Products()
	{

		this->NoOfItems = 0;

		this->TypeofProduct = '\0';

		this->ProductName = '\0';

		this->saleprice = 0;

		this->purchaseprice = 0;

	}

	//Parmetrized Constructor
	Products(int NoOfItems, string TypeofProduct, string ProductName,
		float saleprice, float purchaseprice)
	{

		this->NoOfItems = NoOfItems;

		this->TypeofProduct = TypeofProduct;

		this->ProductName = ProductName;

		this->saleprice = saleprice;

		this->purchaseprice = purchaseprice;

	}
	//for adding new data for items
	void AddData(void)
	{


		bool check = true;

		cin.ignore();

		while (check)
		{

			cout << "Enter the name of the product :";


			getline(cin, this->ProductName);

			this->ProductName = ToUpperfunction(this->ProductName);

			unsigned int settle = 0;	//for removing Severity Code    Description     Project File    Line    Suppression State
			//Error(active) E0434   a reference of type "unsigned int &" (not const - qualified) cannot be initialized with a value of type "std::string"   Project168      C : \Users\Akhyar\source\repos\Project168\Source.cpp    303

			check = CheckForProductName(settle, this->ProductName);

		}

		cout << "Enter the Number of Items : ";

		cin >> this->NoOfItems;

		cout << "Enter the Type of Product: ";

		cin >> this->TypeofProduct;

		this->TypeofProduct = ToUpperfunction(this->TypeofProduct);

		cout << "Enter the Purchase Price of the Product: ";

		cin >> this->purchaseprice;

		cout << "Enter the Sale Price of the Product: ";

		cin >> this->saleprice;

		ofstream fileoutput("Inventory.txt", ios::app);

		if (fileoutput.is_open())
		{

			fileoutput << this->ProductName << " " << this->
				TypeofProduct << " " << this->
				NoOfItems << " " << to_string(purchaseprice) << " " <<
				to_string(saleprice) << " " << to_string(saleprice -
					purchaseprice) << endl;

			cout << "Record Added successfully \n";

		}

		else
		{

			cout << "Failed to open file ! \n";

		}

		fileoutput.close();

		SleepFuntion(2);


	}				//for adding new data
	  //FOR DISPLAYING
	void Display(string searchCriteria = " ", bool check = false)
	{

		bool found = false;

		cin.ignore();

		do
		{

			if (!check)
			{

				cout << "Enter the Search Criteria: ";

				getline(cin, searchCriteria);


				string displaySearchCriteria = searchCriteria;

				searchCriteria = ToUpperfunction(searchCriteria);

				ifstream fileReader("Inventory.txt");

				if (fileReader.is_open())
				{

					string line;

					while (getline(fileReader, line))
					{

						// Split the line into separate fields
						istringstream iss(line);

						string productName, productType, itemNo, Saleprice,
							PurchasePrice, Profit;

						iss >> productName >> productType >> itemNo >>
							PurchasePrice >> Saleprice >> Profit;


						// Check if any of the fields match the search criteria
						if (itemNo == searchCriteria
							|| productName == searchCriteria
							|| productType == searchCriteria
							|| PurchasePrice == searchCriteria
							|| Saleprice == searchCriteria
							|| Profit == searchCriteria)
						{

							std::cout << std::fixed << std::setprecision(2);

							found = true;

							cout << productName << " " << productType << " " <<
								itemNo << " " << PurchasePrice << " " << Saleprice
								<< " " << Profit << endl;

						}

					}

					fileReader.close();

				}


				if (!found)
				{

					cout << "Can not find anything with the search criteria " <<
						displaySearchCriteria << endl;

				}

			}

		} while (!found);

	}


	//FOR REMOVINGmo
	void removeData()
	{

		std::string searchAttribute;

		bool found = false;


		std::cout << "Enter the attribute value to remove: ";

		std::cin >> searchAttribute;

		searchAttribute = ToUpperfunction(searchAttribute);

		std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');


		std::string filename = "Inventory.txt";

		std::ifstream file(filename);

		std::ofstream tempFile("temp.txt");


		if (file.is_open() && tempFile.is_open())
		{

			std::string line;

			while (std::getline(file, line))
			{

				std::istringstream iss(line);

				std::string productName;

				// Extract the attributes from the line
				iss >> productName;


				if (productName != searchAttribute)
				{

					tempFile << line << '\n';

				}

				else
				{

					found = true;

				}

			}


			file.close();

			tempFile.close();


			remove(filename.c_str());

			rename("temp.txt", filename.c_str());

			while (!found)
			{

				cout << "No records found with the specified attribute value.\n";

				cout << "Kindly Enter the correct data \n";

				removeData();

			}

		}


		if (found)
		{

			std::
				cout <<
				"Records with the specified attribute value removed successfully.\n";

		}


		SleepFuntion(1);

		std::cout << "Press any key to go back to the menu.\n";

		getchar();


	}

	//FOR UPDATING
	void updateData()
	{

		std::string searchName;

		bool found = false;

		cin.ignore();

		std::cout << "Enter the product name to update: ";

		std::getline(std::cin, searchName);

		searchName = ToUpperfunction(searchName);

		std::string filename = "Inventory.txt";

		std::ifstream file(filename);

		std::ofstream tempFile("temp.txt");


		if (file.is_open() && tempFile.is_open())
		{

			std::string line;

			while (std::getline(file, line))
			{

				std::istringstream iss(line);

				std::string productName, productType, itemNo, Purchaseprice,
					SalePrice;

				iss >> productName >> productType >> itemNo >> Purchaseprice >>
					SalePrice;


				if (productName == searchName)
				{

					found = true;


					std::
						cout <<
						"What attribute would you like to change? (1. Product Name, 2. Product Type, 3. Item Number, 4. Purchase Price, 5. SalePrice): ";

					int choice;

					std::cin >> choice;

					std::cin.ignore();


					std::string newProductName = productName;

					std::string newProductType = productType;

					std::string newItemNo = itemNo;

					std::string newPurchaseprice = Purchaseprice;

					std::string newSalePrice = SalePrice;

					bool check = true;


					switch (choice)
					{

					case 1:


						while (check)
						{

							std::cout << "Enter the new product name: ";

							std::getline(std::cin, newProductName);

							newProductName = ToUpperfunction(newProductName);

							unsigned int settle = 0;

							check = CheckForProductName(settle, newProductName);

						}
						break;

					case 2:

						std::cout << "Enter the new product type: ";

						std::getline(std::cin, newProductType);

						newProductType = ToUpperfunction(newProductType);

						break;

					case 3:

						std::cout << "Enter the new item number: ";

						std::getline(std::cin, newItemNo);

						break;


					case 4:

						std::cout << "Enter the new purchase price: ";

						std::getline(std::cin, newPurchaseprice);

						break;

					case 5:

						std::cout << "Enter the new purchase price: ";

						std::getline(std::cin, newSalePrice);

						break;

					default:

						std::cout << "Invalid choice!" << std::endl;

						break;

					}

					tempFile << newProductName << " " << newProductType << " " <<
						newItemNo << " " << newPurchaseprice << " " << newSalePrice
						<< " " << to_string(stof(newSalePrice) -
							stof(newPurchaseprice)) << std::endl;


					std::cout << "Product data updated successfully!" << std::
						endl;

				}

				else
				{

					tempFile << line << std::endl;

				}

			}


			file.close();

			tempFile.close();


			if (!found)
			{

				std::
					cout << "Product with name '" << searchName << "' not found!\n"
					<< std::endl;

				updateData();

			}

			else
			{

				std::remove(filename.c_str());

				std::rename("temp.txt", filename.c_str());

			}

		}

		else
		{

			std::cout << "Error opening file!" << std::endl;

		}

		SleepFuntion(1);

	}

	void SleepFuntion(int s)
	{

		std::chrono::seconds sleepDuration(s);

		std::this_thread::sleep_for(sleepDuration);

		system("cls");

	}
	string ToUpperfunction(string str)
	{

		for (char& c : str)
		{

			c = toupper(c);

		}
		return str;

	}


};


