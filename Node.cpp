#include "Node.h"

#if !defined(NULL)
#define NULL 0
#endif


template <typename T>
Node<T>::Node(T value) {
	this->value = value;
	this->next = NULL;
}

template <typename T>
Node<T>::Node(T value, Node<T> *next) {
	this->value = value;
	this->next = next;
}

template <typename T>
T Node<T>::getValue() {
	return this->value;
}

template <typename T>
void Node<T>::setValue(T value) {
	this->value = value;
}

template <typename T>
Node<T> * Node<T>::getNext() {
	return this->next;
}

template <typename T>
void Node<T>::setNext(Node<T> *next) {
	this->next = next;
}

template <typename T>
bool Node<T>::hasNext() {
	return this->next != NULL;
}
