#if !defined(NODE)
#define NODE


template <typename T>
class Node {
private:
	T value;
	Node<T> *next;
public:
	Node(T value);
	Node(T value, Node<T> *next);
	T getValue();
	void setValue(T value);
	Node<T> * getNext();
	void setNext(Node<T> *next);
	bool hasNext();
};

#endif
