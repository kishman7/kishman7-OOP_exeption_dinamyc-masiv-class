#include<iostream> 
#include<windows.h>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>
#include <cmath>

using namespace std;

// Робота з динамічним масивом в класі

class DinamycMasiv 
{
private:
	int size;
	int* mas;

public:
	DinamycMasiv(int size)
	{
		this->size = size;
		this->mas = new int[size];
	}
	void Fill() {
		for (int i = 0; i < this->size; i++)
		{
			this->mas[i] = rand() % 20 + 1;
		}
	}
	void Print() {
		for (int i = 0; i < this->size; i++)
		{
			cout << this->mas[i] << "\t";
		}
	}
	void AddMas() { // функція по додавання елементу в масив
		int addElem = rand() % 20 + 1; // створюємо додатковий новий елемент
		int* temp; // створюємо тимчасовий динамічний масив
		temp = new int[this->size + 1]; // виділяємо під тимчасовий масив місце на 1 елемент більше від старого
		for (int i = 0; i < this->size; i++)
		{
			temp[i] = mas[i]; // заміщаємо створений масив елементами старого масиву
		}
		temp[this->size] = addElem; // додаємо в останній елемент створеного масиву новий додатковий елемент
		delete[] mas; // видаляємо елементи старого масив
		mas = temp; // передаємо адресу створеного масиву в старий масив
		this->size++; // розмір старого масиву збільшуємо на 1, так як ми створений масив збільшили(додали) на 1.
	}

	void DeleteMas() { // функція по видаленню елементу з масиву
		int* temp; // створюємо тимчасовий динамічний масив
		temp = new int[this->size - 1]; // виділяємо під тимчасовий масив місце на 1 елемент менше від старого
		for (int i = 0; i < this->size-1; i++) // розмір ітерацій зменшуємо також на 1
		{
			temp[i] = mas[i]; // заміщаємо створений масив елементами старого масиву
		}
		delete[] mas; // видаляємо елементи старого масив
		mas = temp; // передаємо адресу створеного масиву в старий масив
		this->size--; // розмір старого масиву зменшуємо на 1, так як ми створений масив зменшили(видалили) на 1.
	}

	void MaxElement() {
		int max = mas[0];
		int maxindex = 0;
		for (int i = 0; i < this->size; i++)
		{
			if (max < mas[i])
			{
				max = mas[i];
				maxindex = i;
			}
		}
		cout << "Max element = " << max << endl;
		cout << "Max index = " << maxindex << endl;
	}

	void SortMas() { // сортування "бульбашкою"
		for (int i = 0; i < this->size; i++)
		{
			for (int j = this->size - 1; j > i; j--)
			{
				if (mas[j] > mas[j-1])
				{
					swap(mas[j - 1], mas[j]);
				}
			}
		}
		for (int i = 0; i < this->size; i++)
		{
			cout << mas[i] << "\t";
		}
	}
	void WriteFile() {
		string path = "array.txt";
		ofstream fout;
		fout.open(path);
		if (fout.is_open())
		{
			for (int i = 0; i < this->size; i++)
			{
				fout << mas[i] << "\n";
			}
		}
		fout.close();
	}
	void ReadFile() 
	{
		string path = "array.txt";
		ifstream fin;
		//fin.exceptions(ifstream::badbit | ifstream::failbit);
			fin.open(path);
			if (!fin.is_open())
			{
				throw exception("File error!!!");
			}
			
				if (fin.is_open())
				{
					string* temp;
					temp = new string[this->size];
					for (int i = 0; i < this->size; i++)
					{
						while (getline(fin, temp[i]))
						{
							mas[i] = stoi(temp[i]);
							cout << mas[i] << "\t";
						}
					}
					delete[] temp;
				}
		
		fin.close();
	}

	~DinamycMasiv() {
		delete[] mas;
	}
	
};

int main() {
	srand(unsigned(time(NULL)));
	int size; // кількість елементів масиву
	cout << "Enter the number of elements in the array: " ;
	cin >> size;
	DinamycMasiv dinamycMasiv(size);
	//dinamycMasiv.Fill();
	//dinamycMasiv.Print();

	
	int action = 1;
	while (action)
	{
		cout << "\n=====MENU=====" << endl;
		cout << "1.Fill." << endl;
		cout << "2.Show." << endl;
		cout << "3.Add." << endl;
		cout << "4.Delete." << endl;
		cout << "5.Max element and max index." << endl;
		cout << "6.Sort." << endl;
		cout << "7.Write to file." << endl;
		cout << "8.Read from file." << endl;
		cout << "0.Exit." << endl;
		cout << "\nEnetr item menu: ";
		cin >> action;
		cout << endl;
		switch (action)
		{
			case 1:
			{
				dinamycMasiv.Fill();
				break;
			}
			case 2:
			{
				dinamycMasiv.Print();
				break;
			}
			case 3:
			{
				dinamycMasiv.AddMas();
				break;
			}
			case 4:
			{
				dinamycMasiv.DeleteMas();
				break;
			}
			case 5:
			{
				dinamycMasiv.MaxElement();
				break;
			}
			case 6:
			{
				dinamycMasiv.SortMas();
				break;
			}
			case 7:
			{
				dinamycMasiv.WriteFile();
				break;
			}
			case 8:
			{
				try
				{
					dinamycMasiv.ReadFile();
				}
				catch (const std::exception&ex)
				{
					cout << ex.what();
				}
				break;
			}
			case 0:
			{
				break;
			}
			default:
				cout << "Incorrect menu item. Choice again." << endl;
		}

	}

	
	return 0;
}
