#include <string>
#include "conio.h"
#include "iostream"
#include "fstream"
#include "vector"
#include <locale>
#include <algorithm> 
#include <windows.h>
using namespace std;

struct Advertisement
{
	string disc;
	double prices;
	string link;
	bool photo;
};
bool operator<(const Advertisement& a1, const Advertisement& a2)
{
	return (a1.prices < a2.prices) ? true : false;
}
void ReadText(vector <Advertisement>* V)
{
	string teg_line = "item_table";
	string teg_price = "about";
	string teg_link = "photo-wrapper js-photo-wrapper";
	string teg_photo = "photo-count-show";
	string teg_valet = "руб.";
	string teg_discr = "title item-description-title";
	ifstream fin;
	fin.open("avito.html");
	string temp;
	if (!fin.is_open())
	{
		cout << "[-] Could't open file!";
		exit(EXIT_FAILURE);
	}
	int n = 0;
	Advertisement A;
	bool flag = true;
	while (!fin.eof())
	{
		getline(fin, temp);
		size_t found = temp.find(teg_line);
		if (found != string::npos) {
			cout << "Ad # " << n << endl;
			++n;
			if (flag == true)
				flag = false;
			else
			{
					V->push_back(A);
					A.prices = 0;
					A.disc = "";
					A.link = "";
					A.photo = false;
			}
		}
		size_t found_1 = temp.find(teg_link);
		size_t found_2 = temp.find(teg_photo);
		size_t found_3 = temp.find(teg_discr);
		size_t found_4 = temp.find(teg_price);
		if ((found_1 != string::npos) || (found_2 != string::npos) || (found_3 != string::npos) || (found_4 != string::npos))
		{
			if (found_1 != string::npos)
			{
				string result = "";
				for (unsigned int i = 57; i < temp.length(); ++i)
				{
					result += temp[i];
				}
				A.link = result;
				cout << " Link: " << A.link << endl;
			}
			if (found_2 != string::npos)
			{
				cout << "Photo [+]" << endl;
				A.photo = true;
			}
			if (found_3 != string::npos) {
				getline(fin, temp);
				A.disc = temp;
				cout << "Description: " << A.disc << endl;
			}
			if (found_4 != string::npos)
			{
				getline(fin, temp);
				size_t found = temp.find(teg_valet);
				if (found != string::npos)
				{
					while (temp.find(' ') != string::npos)
						temp.erase(temp.find(' '), 1);
					A.prices = atoi(temp.c_str());
					cout << "Price: " << A.prices << endl << endl;
				}
			}
		}
	}
	if (flag == false)
		V->push_back(A);
	fin.close();
};
void Print(vector <Advertisement> *v, int i)
{
	cout << "Description: " << v->at(i).disc << endl << "Link: " << v->at(i).link << endl << "Photo existing :" << v->at(i).photo << endl << "Price: " << v->at(i).prices << endl;
};
void PrintText(vector <Advertisement> *v)
{
	for (int i = 0; i < v->size(); ++i)
		Print(v, i);
};
void  Price(vector <Advertisement> *v)
{
	sort(v->begin(), v->end());
};
void SearchWord(vector <Advertisement> *v)
{
	string w;
	cout << "Put your search word: " << endl;
	cin >> w;
	
	for (int i = 0; i < v->size(); ++i)
	{
		size_t found = v->at(i).disc.find(w);
		if(found != string :: npos)
		Print(v, i);
	}
};
void SearchEng(vector <Advertisement> *v)
{
	for (int i = 0; i < v->size(); ++i)
	{
		size_t found = v->at(i).disc.find_first_of("qwertyuiopljhgfdsazxcvbnm");
		if (found != string::npos)
			Print(v, i);
	}
};
void SearchPhoto(vector <Advertisement> *v)
{
	for (int i = 0; i < v->size(); ++i)
	{
		size_t found = v->at(i).photo;
		if (found == true)
			Print(v, i);
	}
};
void SearchPrice(vector <Advertisement> *v)
{
	int min, max;
	cout << "¬ведите нижнюю границу ";
	cin >> min;
	cout << "¬ведите верхнюю границу ";
	cin >> max;
	for (int i = 0; i < v->size(); i++)
		if (min <= v->at(i).prices && max >= v->at(i).prices)
			Print(v, i);
};
int main()
{
	vector <Advertisement> v;
	int choice;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	while (1)
	{
		system("cls");
		cout << "  Advertisements  " << endl;
		cout << "  -----------------------------  " << endl;
		cout << "  1. Print list  ";
		cout << "  2. Sort price  ";
		cout << "  3. Search word ";
		cout << "  4. Search eng symbol ";
		cout << "  5. Photo existing ";
		cout << "  6. Search price ";
		cout << "  0. Exit    " << endl;
		cout << "  Enter your choice :  ";
		cin >> choice;
		switch (choice)
		{
		case 1: cout << "  Advertisements list :  " << endl;

			ReadText(&v);
			_getch();
			break;
			case 2:
				cout << "  ------------------- " << endl;
				Price(&v);
				PrintText(&v);
				_getch();
				break;
			case 3: 
				cout << "  ------------------- " << endl;
				SearchWord(&v);
				_getch();
				break;
			case 4: cout << endl;
				cout << "  ------------------- " << endl;
				SearchEng(&v);
				_getch();
				break;
			case 5: cout << endl;
				cout << "  ------------------- " << endl;
				SearchPhoto(&v);
				_getch();
				break;
			case 6: cout << endl;
				cout << "  ------------------- " << endl;
				SearchPrice(&v);
				_getch();
				break;
		case 0:
			return 0;
			break;
		}
	}
	system("pause");
};