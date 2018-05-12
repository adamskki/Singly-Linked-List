#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <ctime>
using namespace std;

struct student
{
	string name;
	string surname;
	int index;
	student *next; //pointer to the next element
	student(); //constructor
};

student::student()
{
	next = 0;
}

class list
{
public:
	student *first; //pointer to the beginning of the list
	void add_student(string name, string surname, int index);
	void remove_student(int nr);
	void remove_last();
	void remove_student_index(int nr,int size);
	void find(int nr);
	int size();
	void display_student();
	list();
};

list::list()
{
	first = 0; //constructor
}

void list::add_student(string name, string surname, int index)
{
	student *nowy = new student; //create new list item

	//now we will fill new item with our data
	nowy->name = name;
	nowy->surname = surname;
	nowy->index =index;

	if (first == 0) //if this is our first item 
	{
		first = nowy; // our new item is our first item
	}

	else
	{
		student *temp = first;

		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nowy;
		nowy->next = 0;
	}
}

int list::size()
{
	int size = 0;
	student *temp = first;
	while (temp)
	{
		temp = temp->next;
		size++;
	}
	return size;
}

void list::remove_last()
{
	student *osoba = first;
	if (osoba)
	{
		if (osoba->next)
		{
			while (osoba->next->next)
				osoba = osoba->next;
			delete osoba->next;
			osoba->next = 0;
		}
		else
		{
			delete osoba;
			first = 0;
		}
	}
}

void list::remove_student_index(int nr,int size)
{
	int j = 0;
	bool remove = 1;
	student *osoba = new student;
	student *wskaznik = new student;
	osoba = first;
	if (osoba->index == nr)
	{
		first = osoba->next;
		delete osoba;
	}
	else
	{
		while (j++ < size)
		{
			if (osoba->next->index == nr)
			{
				if (j == size) remove_last();
				else
				{
					wskaznik = osoba->next;
					osoba->next = osoba->next->next;
					delete wskaznik;
					remove = 0;
					break;
				}
			}
			else osoba = osoba->next;
		}
		if (remove) cout << "Nie znaleziono elementu" << endl;

	}


}



void list::remove_student(int nr)
{
	if (nr == 1) //if this is the first item
	{
		student *temp = first;
		first = temp->next;
	}
	if (nr >= 2) //if this is not the first item
	{
		int j = 1;

		student *temp = first;

		while (temp)
		{
			if ((j + 1) == nr) break;

			temp = temp->next;
			j++;
		}

		if (temp->next->next == 0)
			temp->next = 0;

		else
			temp->next = temp->next->next;
	}
}

void list::find(int nr)
{
	student *osoba = new student;
	osoba = first;
	if (osoba->index == nr)
	{
		//cout << "Znalezione" << endl;

	}
	else
	{
		bool flaga = 1;
		while (osoba->next != NULL)
		{
			if (osoba->next->index == nr)
			{
				//cout << "Znalezione" << endl;
				flaga = 0;
				break;
			}
			osoba = osoba->next;
		}
	//	if (flaga) cout << "Nie znaleziono" << endl;
	}
}



/*
void list::find(int Nnr_indeksu)
{
student *osoba = new student;
osoba = glowa;
if (osoba->index == Nnr_indeksu)
{
//reutrn osoba
cout << "Osoba o indeksie: " << Nnr_indeksu << " to: " << osoba->name << " " << osoba->surname << endl;
}
else
{
bool flaga = 1;
while (osoba->next != NULL)
{
if (osoba->next->nr_indeksu == Nnr_indeksu)
{
//return osoba
cout << "Osoba o indeksie: " << Nnr_indeksu << " to: " << osoba->next->name << " " << osoba->next->surname << endl;
flaga = 0;
break;
}
osoba = osoba->next;
}
if (flaga) cout << "Nie znaleziono takiej osoby" << endl;
}
}
*/

void list::display_student()
{
	student *temp = first;

	while (temp)
	{
		cout << "imie:" << temp->name << " nazwisko:" << temp->surname << " nr:" << temp->index << endl;
		temp = temp->next;
	}

}

void wypelnij()
{
	ifstream wejscie;
	wejscie.open("dane10.txt");
	ifstream wejscie2;
	wejscie2.open("studenci10.txt");
	ofstream wynik;
	wynik.open("wypelnianieLista10.txt");
	ofstream wynik2;
	wynik2.open("usuwanieLista10.txt");
	auto begin = std::chrono::high_resolution_clock::now();
	list *baza = new list;
	for (int i = 0; i < 14000; i++)
	{
		string name;
		string surname;
		int index;
		wejscie >> name;
		wejscie >> surname;
		wejscie >> index;
		baza->add_student(name, surname, index);
	}
	int liczba = baza->size();
	auto end = std::chrono::high_resolution_clock::now();
	wynik << 14000 << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "\n";
	
	auto begin2 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i <14000; i++)
	{
		int indeks;
		wejscie2 >> indeks;
		baza->remove_student_index(indeks, liczba);
		liczba = baza->size();
	}
	auto end2 = std::chrono::high_resolution_clock::now();
	wynik2 <<14000 << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count() << "\n";
	
}

void szukanie()
{
	ifstream wejscie;
	wejscie.open("dane10.txt");
	ifstream wejscie2;
	wejscie2.open("studenci10.txt");
	ofstream wynik;
	wynik.open("szukanieLista10.txt");
	
	list *baza = new list;
	for (int i = 0; i < 14000; i++)
	{
		string name;
		string surname;
		int index;
		wejscie >> name;
		wejscie >> surname;
		wejscie >> index;
		baza->add_student(name, surname, index);
	}
	auto begin = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 14000; i++)
	{
		int indeks;
		wejscie2 >> indeks;
		baza->find(indeks);
	}
	auto end = std::chrono::high_resolution_clock::now();
	wynik << 14000 << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "\n";

}




int main()
{
	wypelnij();
	szukanie();
	system("pause");
	

}