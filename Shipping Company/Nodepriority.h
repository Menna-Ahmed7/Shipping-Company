#pragma once
template <class T>
class Nodepriority
{
	int Key;
	Nodepriority<T>* next;
	T data;
public:
	Nodepriority(T newentry, int key);
	int getKey();
	T getData();
	void setNext(Nodepriority<T>* temp);
	Nodepriority<T>* getNext();
};

template<class T>
inline Nodepriority<T>::Nodepriority(T newentry, int key)
{
	Key = key;
	data = newentry;
}

template<class T>
inline int Nodepriority<T>::getKey()
{
	return Key;
}

template<class T>
inline T Nodepriority<T>::getData()
{
	return data;
}

template<class T>
inline void Nodepriority<T>::setNext(Nodepriority<T>* temp)
{
	next = temp;
}

template<class T>
inline Nodepriority<T>* Nodepriority<T>::getNext()
{
	return next;
}
