#if !defined(QUEUE)
#define QUEUE

#include "Node.h"


template <typename T>
class Queue {
private:
	Node<T> *firstNode;
	int length;
public:
	Queue();
	void insert(T value);
	T remove();
	T head();
	bool isEmpty();
	int getLength();
	~Queue();
};

#endif
