#if !defined(ARRAY_LIST)
#define ARRAY_LIST


template <typename T>
class ArrayList {
private:
	T *arr;
	int length;
public:
	ArrayList();
	T getAt(int index);
	void add(T value);
	void addAt(int index, T value);
	T remove();
	T removeAt(int index);
	void replaceAt(int index, T value);
	int getLength();
	~ArrayList();
};

#endif
