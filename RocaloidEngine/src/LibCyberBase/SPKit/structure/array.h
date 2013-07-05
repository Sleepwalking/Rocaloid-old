#ifndef ARRAY_H
#define ARRAY_H
#include "../defs.h"
//#include "../misc/memopr.h"
//#include <stdlib.h>
//#include <stdio.h>
enum arraySpace
{
	onDemand = 5,
	tiny = 20,
	small = 80,
	medium = 320,
	large = 1280,
	huge = 5120,
};
template <class T> class array
{
	public:
		array();
		array(int _preservedSpace);
		~array();
		inline int getUbound();
		bool setUbound(int newUbound);
		inline T& operator [](int index);
		
		void remove(int index);
		void remove(int index, int dest);
		void insert(int index, T entity);
		void insertEmpty(int index, int count);
		void copyTo(array<T>& target, int myindex, int mydest, int targetindex);
		void fill(int index, int dest, T entity);
		void reverse(int index, int dest);

		inline void push(T entity);
		inline T pop();
		inline void pushf(T entity);
		inline T popf();

		array<T>& operator =(array<T>& source);
		int pointer;
		int preservedSpace;
	private:
		T* baseptr;
		int size;
		int ubound;
		int sizePerT;
};
template <class T> array<T>::array()
{
	size = 0;
	ubound = 0;
	sizePerT = sizeof(T);
	baseptr = 0;
	pointer = -1;
	preservedSpace = small;
	setUbound(1);
}
template <class T> array<T>::array(int _preservedSpace)
{
	size = 0;
	ubound = 0;
	sizePerT = sizeof(T);
	baseptr = 0;
	pointer = -1;
	preservedSpace = _preservedSpace;
	setUbound(1);
}
template <class T> array<T>::~array()
{
	if(baseptr != 0)
	{
		delete []baseptr;
	}
}
template <class T> bool array<T>::setUbound(int newUbound)
{
	int allocSize = newUbound - size;
	if(allocSize > 0)
	{
		T* newptr = new T[newUbound + preservedSpace];
		if(newptr == 0)
			return false;

		if(baseptr == 0)
		{
			baseptr = newptr;
			size = newUbound + preservedSpace;
			ubound = newUbound;
			return true;
		}
		int i;
		for(i = 0;i < size;i ++)
		{
			newptr[i] = baseptr[i];
		}
		
		delete []baseptr;

		baseptr = newptr;
		size = newUbound + preservedSpace;
		
		ubound = newUbound;
		return true;
	}
	if(newUbound < ubound)
	{
		return false;
	}else
	{
		ubound = newUbound;
	}
	return true;
}
template <class T> inline int array<T>::getUbound()
{
	return ubound;
}
template <class T> inline T& array<T>::operator [](int index)
{
	return ((T*)baseptr)[index];
}
template <class T> inline void array<T>::push(T entity)
{
	setUbound(ubound + 1);
	operator[](++ pointer) = entity;
}
template <class T> inline T array<T>::pop()
{
	ubound -= 1;
	return operator[](pointer --);
}
template <class T> inline void array<T>::pushf(T entity)
{
	insert(0, entity);
	pointer ++;
}
template <class T> inline T array<T>::popf()
{
	T ret = operator[](0);
	remove(0);
	pointer --;
	return ret;
}
template <class T> array<T>& array<T>::operator =(array<T>& source)
{
	int i;
	size = source.size;
	pointer = source.pointer;
	preservedSpace = source.preservedSpace;
	setUbound(source.ubound);
	for(i = 0;i <= ubound;i ++)
		baseptr[i] = source[i];
	return *this;
}

#endif