#include "Matrix.h"
#include <exception>
#include <stdexcept>


Matrix::Matrix(int nrLines, int nrCols) {

	this->Lines = nrLines;
	this->Cols = nrCols;
	this->values = new Tuple[1];
	this->size = 0;
	this->capacity = 1;
}

Matrix::~Matrix()
{
	delete[] this->values;
}

Matrix::Matrix(const Matrix& m) // : Lines(m.lines)
{
	this->Lines = m.Lines;
	this->Cols = m.Cols;
	this->values = new Tuple[m.capacity];
	for (int i = 0; i < m.size; i++)
	{
		this->values[i] = m.values[i];
	}
	this->capacity = m.capacity;
	this->size = m.size;

}

int Matrix::nrLines() const {
	return this->Lines;
}


int Matrix::nrColumns() const {
	return this->Cols;
}


TElem Matrix::element(int i, int j) const {
	if (i < 0 or i >= this->Lines or j < 0 or j >= this->Cols)
	{
		throw out_of_range("Out of range cell in matrix");
	}
	//incearca cu cautare binara 
	for (int k = 0; k < this->size; k++) //O(size)
	{
		
		if (get<0>(this->values[k]) == i && get<1>(this->values[k]) == j) return get<2>(this->values[k]);
	}
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 or i >= this->Lines or j < 0 or j >= this->Cols)
	{
		throw out_of_range("Out of range cell in matrix");
	}
	for (int k = 0; k < this->size; k++) //O(size)
	{
		if (get<0>(this->values[k]) == i && get<1>(this->values[k]) == j)
		{
			TElem prev = get<2>(this->values[k]);//acceseaza valoarea de pe poz i j si o retine in prev 
			this->values[k] = Tuple(i, j, e);
			return prev;
		}
	}
	Tuple nou(i, j, e);//Tuple nou = Tuple(i,j,e);
	if (this->size == this->capacity) {
		this->capacity = this->capacity * 2;
		Tuple* new_vector = new Tuple[capacity];
		for (int k = 0; k < this->size; k++)
		{
			new_vector[k] = values[k];
		}
		delete[] this->values;
		this->values = new_vector;
	}
	//cauti ultimu care e mai mic retii pozitia il pui acolo si muti restu tot in dreapta si dupa returnezi prev value care e null telem
	return NULL_TELEM;
}


