#include "ArrayList.h"

#if !defined(NULL)
#define NULL 0
#endif


template <typename T>
ArrayList<T>::ArrayList() {
	this->arr = NULL;
	this->length = 0;
}

template <typename T>
T ArrayList<T>::getAt(int index) {
	return this->arr[index];
}

template <typename T>
void ArrayList<T>::add(T value) {
	T *previousArr = this->arr;
	this->arr = new T[this->length + 1];
	for (int i = 0; i < this->length; i++)
		this->arr[i] = previousArr[i];
	this->arr[this->length] = value;
	delete [] previousArr;
	previousArr = NULL;
	this->length++;
}

template <typename T>
void ArrayList<T>::addAt(int index, T value) {
	T *previousArr = this->arr;
	this->arr = new T[this->length + 1];
	for (int i = 0; i < index; i++)
		this->arr[i] = previousArr[i];
	this->arr[index] = value;
	for (int i = index + 1; i < this->length + 1; i++)
		this->arr[i] = previousArr[i - 1];
	delete [] previousArr;
	previousArr = NULL;
	this->length++;
}

template <typename T>
T ArrayList<T>::remove() {
	T *previousArr = this->arr;
	this->arr = new T[this->length - 1];
	for (int i = 0; i < this->length - 1; i++)
		this->arr[i] = previousArr[i];
	T value = previousArr[this->length - 1];
	delete [] previousArr;
	previousArr = NULL;
	this->length--;
	return value;
}

template <typename T>
T ArrayList<T>::removeAt(int index) {
	T *previousArr = this->arr;
	this->arr = new T[this->length - 1];
	for (int i = 0; i < index; i++)
		this->arr[i] = previousArr[i];
	for (int i = index + 1; i < this->length; i++)
		this->arr[i - 1] = previousArr[i];
	T value = previousArr[index];
	delete [] previousArr;
	previousArr = NULL;
	this->length--;
	return value;
}

template <typename T>
void ArrayList<T>::replaceAt(int index, T value) {
	this->arr[index] = value;
}

template <typename T>
int ArrayList<T>::getLength() {
	return this->length;
}

template <typename T>
ArrayList<T>::~ArrayList() {
	delete [] this->arr;
	this->arr = NULL;
}
