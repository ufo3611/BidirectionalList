#include <iostream>
using namespace std;

#define tab '\t'
#define delimiter "\n\n-----------------------------------------------\n\n"

class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "EConstructor:\t " << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t " << this << endl;
	}

	friend class List;

};

class List
{
	Element* Head;
	Element* Tail;
	int Size;

public:

	/////////////////////////////////// GetSet methods ////////////////////////////////

	int GetSize()
	{
		return Size;
	}

	///////////////////////////////////	Constructors ///////////////////////////////////

	List()
	{
		Head = Tail = nullptr;
		Size = 0;
		cout << "LConstructor:\t " << this << endl;
	}

	List(int n) : List()
	{
		for (int i = 0; i < n; i++) push_back(rand() % 100);
	}

	List(initializer_list<int> il) :List()
	{
		for (const int* it = il.begin(); it < il.end(); it++) push_back(*it);
	}

	~List()
	{
		Clear();
		cout << "LDestructor:\t " << this << endl;
	}

	////////////////////////////////// Operator overloading //////////////////////////////////////

	int& operator[](int Index)
	{
		if (Index < 0 || Index >= Size)
		{
			cout << "Error: Out of list\n";
			throw 0;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index; i++) Temp = Temp->pNext;
		return Temp->Data;
	}

	//////////////////////////////// Добавление элементов ///////////////////////////////////////

	void push_front(int Data)
	{
		if (Head == nullptr)
		{
			Tail = Head = new Element(Data);
			Size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		Size++;
	}

	void Insert(int Data, int Index)
	{
		if (valid_index(Index) == 1) return;
		Element* Temp;
		if (Index < Size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = Size - 1; i > Index; i--)Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		Size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			Tail = Head = new Element(Data);
			Size++;
			return;
		}
		Tail = Tail->pNext = new Element(Data, 0, Tail);
		Size++;
	}

	/////////////////////////////// Удаление элементов ///////////////////////////////////////////

	void del_last()
	{
		if (Head == Tail)
		{
			delete Head;
			Size--;
			Head = Tail = nullptr;
		}
	}

	void pop_front()
	{
		if (Head == nullptr) return;
		if (Head == Tail)
		{
			del_last();
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		Size--;
	}

	void Erase(int Index)
	{
		if (valid_index(Index) == 1) return;
		Element* Temp;
		if (Index < Size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = Size - 1; i > Index; i--)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		Size--;
	}

	void Erase(Element* &Temp)
	{
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		Size--;
		Temp = Temp->pPrev;
	}

	void pop_back()
	{
		if (Tail == nullptr) return;
		if (Head == Tail)
		{
			del_last();
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		Size--;

	}

	void remove_value(int value, char str = '\0', int counter = 0)
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext, counter++)
		{
			if ((Temp->Data == value && str == '\0') || (Temp->Data > value && str == 'm') || (Temp->Data < value && str == 'l'))
			{
				if (counter == 0)pop_front();
				else if (counter == Size - 1)pop_back();
				else Erase(Temp);
				return remove_value(value, str);
			}
		}
	}

	///////////////////////////////// Auxiliary methods //////////////////////////////////////////////////////

	void Print()
	{
		cout << delimiter << endl;
		cout << "Адрес начала списка: " << Head << endl;
		for (Element* Temp = Head; Temp != nullptr; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Адрес конца списка: " << Tail << endl;
		cout << "Размер списка: " << Size << endl;
		cout << delimiter << endl;
	}

	void Print_reverse()
	{
		cout << delimiter << endl;
		cout << "Адрес начала списка: " << Head << endl;
		for (Element* Temp = Tail; Temp != nullptr; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Адрес конца списка: " << Tail << endl;
		cout << "Размер списка: " << Size << endl;
		cout << delimiter << endl;
	}

	int valid_index(int index)
	{
		if (index >= Size || index < 0) return 1;
		else return 0;
	}

	void Clear()
	{
		while (Head != Tail) pop_front();
		del_last();
	}

	void Exchange(int& a, int& b)
	{
		int buffer = a;
		a = b;
		b = buffer;
	}

	void reverse()
	{
		for (int i = 0; i < Size / 2; i++) Exchange((*this)[i], (*this)[Size - 1 - i]);
	}

	void unique(int value)
	{
		int counter = 0;
		int index = -1;
		bool check = false;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext, counter++)
		{
			if (Temp->Data == value && check == false)
			{
				index = counter;
				check = true;
				continue;
			}
			if (Temp->Data == value && check == true && counter != index)
			{
				if (counter == 0)pop_front();
				else if (counter == Size - 1)pop_back();
				else Erase(counter);
				counter = 0;
				Temp = Head;
			}
		}
	}

	void unique()
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext) unique(Temp->Data);
	}

};




void main()
{
	setlocale(LC_ALL, "Russian");
	List list{ 3,3,3, 5,3, 8, 13,5, 21,21,0,21 };
	list.Print();
	list.unique();
	list.Print_reverse();
}

