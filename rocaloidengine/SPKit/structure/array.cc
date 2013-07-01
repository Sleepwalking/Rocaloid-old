#include "array.h"
#include <stdlib.h>
#include <string.h>
#include "../misc/listopr.h"
#include "../misc/memopr.h"
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