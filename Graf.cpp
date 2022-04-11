#include "Graf.h"

Graf::Graf() : size(0), node(nullptr), matricaSusjednosti(nullptr)
{
}

Graf::Graf(int size, std::string* node, int* matricaSusjednosti) : size(size), node(new std::string[size]), matricaSusjednosti(new int[size*size])
{
	for (int i = 0; i < size; i++)
	{
		this->node[i] = node[i];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			this->matricaSusjednosti[i * size + j] = matricaSusjednosti[i * size + j];
		}
	}
}

void Graf::pisiMatricuSusjednosti()
{
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (this->matricaSusjednosti[i * size + j] == 1)
			{
				std::cout << this->matricaSusjednosti[i * size + j] << " ";
			}
			else
			{
				std::cout << 0 << " ";
			}
		}
		std::cout << std::endl;
	}
}

std::string Graf::getNode(int i)
{
	return this->node[i];
}

int Graf::getSize()
{
	return this->size;
}

int Graf::getClanMatrice(int i, int j)
{
	return this->matricaSusjednosti[i*this->size + j];
}


void Graf::floyd(int d[], int t[])
{
	int i, j, k;
	for (k = 0; k < this->size; k++)
		for (i = 0; i < this->size; i++)
			for (j = 0; j < this->size; j++)
				if (d[i*this->size + j] > d[i * this->size + k] + d[k * this->size + j]) {
					d[i * this->size + j] = d[i * this->size + k] + d[k * this->size + j];
					t[i*this->size +j] = t[k*this->size + j];
				}

}

void Graf::putanja(int i, int j, int t[], int& duzina, int dest)
{
	if (i == j)
	{
		duzina++;
		std::cout << this->node[j] << "->";
	}
	else if (t[i*this->size + j] == -1)
	{
		std::cout << "Nema putanje" << std::endl;
	}
	else
	{
		duzina++;
		this->putanja(i, t[i * this->size + j], t, duzina, dest);
		std::cout << this->node[j] << "";
		dest != j ? std::cout<<"->" : std::cout<<"";
	}
}

void Graf::init(int t[])
{
	int i, j;
	for (i = 0; i < this->size; i++)
		for (j = 0; j < this->size; j++)
			if (i == j || this->matricaSusjednosti[i*this->size + j] == 0)
				t[i*this->size + j] = -1;
			else
				t[i * this->size + j] = i;

}

bool Graf::rowEmpty(int row)
{
	int param = 0;
	for (int i = 0; i < this->size; i++)
	{
		if (this->matricaSusjednosti[row * this->size + i] == 1)
		{
			return false;
		}
	}
	return true;
}

Graf::~Graf()
{
	delete[] this->node;
	delete[] this->matricaSusjednosti;
}
