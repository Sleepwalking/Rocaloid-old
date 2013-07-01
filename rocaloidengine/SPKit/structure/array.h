#ifndef ARRAY_H
#define ARRAY_H
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "../defs.h"
#include "../misc/listopr.h"
#include "../misc/memopr.h"
template <class T> class array
{
	public:
		array();
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

		int pointer;
		bool objectType;
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
	objectType = false;
	setUbound(1);
}
template <class T> array<T>::~array()
{
	if(baseptr != 0)
	{
		delete []baseptr;
	}
}
template <class T> inline int array<T>::getUbound()
{
	return ubound;
}
template <class T> bool array<T>::setUbound(int newUbound)
{
	int allocSize = newUbound - size + 100;
	if(allocSize >= 100)
	{
		int i;
		T* newptr = new T[allocSize + size];
		if(newptr == 0)
			return false;
		for(i = 0;i < ubound;i ++)
			newptr[i] = baseptr[i];
		delete []baseptr;
		baseptr = (T*)newptr;
		size += allocSize;
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
template <class T> inline T& array<T>::operator [](int index)
{
	return ((T*)baseptr)[index];
}
template <class T> void array<T>::remove(int index)
{
	leftShift((T*)baseptr, index + 1, ubound, 1);
	ubound -= 1;
}
template <class T> void array<T>::remove(int index, int dest)
{
	leftShift((T*)baseptr, dest + 1, ubound, dest - index + 1);
	ubound -= dest - index + 1;
}
template <class T> void array<T>::insert(int index, T entity)
{
	setUbound(ubound + 1);
	rightShift((T*)baseptr, index, ubound - 1, 1);
	operator[](index) = entity;
}
template <class T> void array<T>::insertEmpty(int index, int count)
{
	setUbound(ubound + count);
	rightShift((T*)baseptr, index, ubound - count, count);
}
template <class T> void array<T>::copyTo(array<T>& target, int myindex, int mydest, int targetindex)
{
	int i, count;
	count = mydest - myindex + 1;
	target.setUbound(targetindex + count - 2);
	for(i = 0; i < count; i++)
		target[targetindex + i] = operator[](myindex + i);
}
template <class T> void array<T>::fill(int index, int dest, T entity)
{
	int i;
	for(i = index;i <= dest;i ++)
		operator[](i) = entity;
}
template <class T> void array<T>::reverse(int index, int dest)
{
	int i;
	int half = (dest - index + 1) / 2;
	T tmp;
	for(i = 0;i < half;i ++)
	{
		tmp = operator[](dest - i);
		operator[](dest - i) = operator[](index + i);
		operator[](index + i) = tmp;
	}
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

#endif