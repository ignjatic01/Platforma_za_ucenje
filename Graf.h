#pragma once
#include <iostream>
#include <list>
#include <limits>

class Graf
{
private:
	int size;
	std::string *node;
	int *matricaSusjednosti;
public:
	Graf();
	Graf(int size, std::string* node, int *matricaSusjednosti);
	void pisiMatricuSusjednosti();
	std::string getNode(int i);
	int getSize();
	int getClanMatrice(int i, int j);
	void floyd(int d[], int t[]);
	void putanja(int i, int j, int t[], int& duzina, int dest);
	void init(int t[]);
	bool rowEmpty(int row);
	~Graf();
};

/*
void Vector2DArray::realloc()
	{
		this->realloc(this->capacity > 0 ? this->capacity * 2 : 1);
	}

	void Vector2DArray::realloc(int newCapacity)
	{
		Vector2D* newArr = new Vector2D[newCapacity]();
		this->capacity = newCapacity;
		this->numElements = this->capacity > this->numElements ? this->numElements : this->capacity;

		for (int i = 0; i < this->numElements; i++)
			newArr[i] = this->arr[i];

		delete[] this->arr;
		this->arr = newArr;
	}
*/