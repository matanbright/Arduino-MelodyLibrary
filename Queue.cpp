#include "Queue.h"
#include "Node.cpp"

#if !defined(NULL)
#define NULL 0
#endif


template <typename T>
Queue<T>::Queue() {
	this->firstNode = NULL;
	this->length = 0;
}

template <typename T>
void Queue<T>::insert(T value) {
	if (this->firstNode == NULL)
		this->firstNode = new Node<T>(value);
	else {
		Node<T> *p = this->firstNode;
		while (p->hasNext())
			p = p->getNext();
		p->setNext(new Node<T>(value));
	}
	this->length++;
}

template <typename T>
T Queue<T>::remove() {
	Node<T> *removedNode = this->firstNode;
	this->firstNode = this->firstNode->getNext();
	T value = removedNode->getValue();
	delete removedNode;
	removedNode = NULL;
	this->length--;
	return value;
}

template <typename T>
T Queue<T>::head() {
	return this->firstNode->getValue();
}

template <typename T>
bool Queue<T>::isEmpty() {
	return this->firstNode == NULL;
}

template <typename T>
int Queue<T>::getLength() {
	return this->length;
}

template <typename T>
Queue<T>::~Queue() {
	while (this->firstNode != NULL) {
		Node<T> *removedNode = this->firstNode;
		this->firstNode = this->firstNode->getNext();
		delete removedNode;
	}
}
