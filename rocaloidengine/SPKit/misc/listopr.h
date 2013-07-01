#ifndef LISTOPR_H
#define LISTOPR_H
template <class T> void leftShift(T* tArray, int index, int dest, int count, T fill)
{
	int i, amount;
	amount = dest - index + 1;
	for(i = 0;i < amount;i++)
		tArray[index + i - count] = tArray[index + i];
	for(i = dest - count + 1;i <= dest;i++)
		tArray[i] = fill;
}
template <class T> void rightShift(T* tArray, int index, int dest, int count, T fill)
{
	int i, amount;
	amount = dest - index;
	for(i = amount;i >= 0;i--)
		tArray[index + i + count] = tArray[index + i];
	for(i = index;i < index + count;i++)
		tArray[i] = fill;
}
template <class T> void leftShift(T* tArray, int index, int dest, int count)
{
	int i, amount;
	amount = dest - index + 1;
	for(i = 0;i < amount;i++)
		tArray[index + i - count] = tArray[index + i];
}
template <class T> void rightShift(T* tArray, int index, int dest, int count)
{
	int i, amount;
	amount = dest - index;
	for(i = amount;i >= 0;i--)
		tArray[index + i + count] = tArray[index + i];
}
#endif