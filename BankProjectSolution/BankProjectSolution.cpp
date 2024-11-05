#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const string ClientFileName = "Clients.txt";

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

enum enMainMenuOption
{
	eListClient = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eExit = 6
};

void ShowMainMenu();
bool ClientExistsByAccountNumber(string AccountNumber, string FileName);
vector<sClient> LoadClientsDataFromFile(string ClientFileName);

vector<string> SplitString(string Line, string delim = "#//#")
{
	vector<string> vWords;
	short pos = 0;
	string sWord;
	while ((pos = Line.find(delim)) != string::npos)
	{
		sWord = Line.substr(0, pos);

		if (sWord != "")
		{
			vWords.push_back(sWord);
		}
		Line.erase(0, pos + delim.length());
	}
	if (Line != "")
	{
		vWords.push_back(Line);
	}
	return vWords;
}

sClient ConvertLineToRecord(string Line)
{
	sClient Client;
	vector <string> vWords = SplitString(Line);
	Client.AccountNumber = vWords[0];
	Client.Phone = vWords[1];
	Client.Name = vWords[2];
	Client.Phone = vWords[3];
	Client.AccountBalance = stoi(vWords[4]);
	return Client;
}

string ConvertRecordToLine(sClient Client, string delim = "#//#")
{
	string Line;

	Line += Client.AccountNumber + delim;
	Line += Client.PinCode + delim;
	Line += Client.Name + delim;
	Line += Client.Phone + delim;
	Line += to_string(Client.AccountBalance);

	return Line;
}

short ReadMainMenuOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
	vector<sClient> vClients = LoadClientsDataFromFile(ClientFileName);

	cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s).";
	cout << "\n--------------------------------------------------";
	cout << "------------------------------------------\n";

	cout << "| " << left << setw(15) << "Account Number: ";
	cout << "| " << left << setw(15) << "Pin Code: ";
	cout << "| " << left << setw(15) << "Client Name: ";
	cout << "| " << left << setw(15) << "Phone: ";
	cout << "| " << left << setw(15) << "Balance: ";

	cout << "\n--------------------------------------------------";
	cout << "------------------------------------------\n";

	if (vClients.size() == 0)
		cout << "\n\n No Clients available In the system!";
	else
		for (sClient Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
}

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to main menu....";
	system("pause>0");
	ShowMainMenu();
}

sClient ReadNewClient()
{
	sClient Client;
	cin.ignore();
	cout << "Account Number: ";
	getline(cin, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientFileName))
	{
		cout << "This Number Already Exists\n";
		cout << "Account Number: ";
		getline(cin, Client.AccountNumber);
	}

	cout << "Name : ";
	getline(cin, Client.Name);

	cout << "Phone: ";
	getline(cin, Client.Phone);

	cout << "PIN: ";
	getline(cin, Client.PinCode);

	cout << "Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(ClientFileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

void AddDataLineToFile(string ClientFileName, string stDatLine )
{
	fstream MyFile;
	MyFile.open(ClientFileName, ios::out | ios::app);

	if (MyFile.is_open())
	{

	}
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding New Client: \n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? y/n";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

void ShowAddNewClientScreen()
{
	cout << "\n------------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n------------------------------------\n";

	AddNewClients();
}

vector<sClient> LoadClientsDataFromFile(string ClientFileName)
{
	fstream MyFile;
	MyFile.open(ClientFileName, ios::in);

	vector<sClient> vClients;
	vector<string> vWords;

	if (MyFile.is_open())
	{
		sClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

string ReadAccountNumber()
{
	string AccountNumber;

	cout << "Enter Account Number: ";
	cin >> AccountNumber;

	return AccountNumber;
}

void PrintClientCard(sClient Client)
{
	cout << "Account Number: " << Client.AccountNumber << endl;
	cout << "Name: " << Client.Name << endl;
	cout << "Phone: " << Client.Phone << endl;
	cout << "PIN: " << Client.PinCode << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
}

void ShowAllClients(vector<sClient> vClients)
{
	for (sClient Client : vClients)
	{
		cout << "\n----------------------------------------------------\n";
		PrintClientCard(Client);
		cout << "\n----------------------------------------------------\n";
	}
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient>& vClients, sClient& Client)
{
	if (AccountNumber == Client.AccountNumber)
	{
		return true;
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we only write records that are not marked for delete.
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want to delete this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientFileName);

			cout << "\n\nClient Deleted Succuessfully";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

void ShowDeleteClientScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n------------------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientFileName);
	string AccountNumber = ReadAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y / n?";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientFileName, vClients);
			cout << "Client Updated Successfully";
			return true;
		}
	}
}

void ShowUpdateClientScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\nUpdate Client Screen";
	cout << "\n------------------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientFileName);
	string AccountNumber = ReadAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\nFind Client Screen";
	cout << "\n------------------------------------------\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientFileName);
	sClient Client;
	string AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
	}
}

void PerformMainMenuOption(enMainMenuOption MainMenuOption)
{
	switch (MainMenuOption)
	{
	case enMainMenuOption::eListClient:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eAddNewClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	case enMainMenuOption::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	}

}

void ShowMainMenu()
{
	system("cls");
	cout << "======================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "======================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "======================================\n";
	PerformMainMenuOption((enMainMenuOption)ReadMainMenuOption());
}

int main()
{
	ShowMainMenu();
}