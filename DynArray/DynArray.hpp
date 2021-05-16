#ifndef _DYNARRAY_H_
#define _DYNARRAY_H_
#include <cstdlib>
#include <iostream>
#include <memory>
#include <algorithm>

template<typename T>
class DynArray
{
protected:
	size_t mySize;
	size_t myCapacity;
	T* myData;

private:
	void reserveMemory(size_t newCapacity);

public:
	typedef T* iterator;
	typedef T* reverse_iterator;
	typedef const T* const_iterator;
	typedef const T* const_reverse_iterator;

	DynArray() : mySize(0), myCapacity(0), myData(nullptr) {};
	DynArray(size_t count);
	DynArray(iterator start, iterator end);
	DynArray(const DynArray& dynArr);
	~DynArray();

	//Operators
	DynArray& operator=(const DynArray& dynArr);
	bool operator==(const DynArray& dynArr) const;
	bool operator!=(const DynArray& dynArr) const;
	T& operator[](size_t index) const;

	//getters
	size_t size(void) const { return mySize; }
	size_t capacity(void) const { return myCapacity; }
	bool empty(void) const { return mySize == 0; }
	T* data(void) const { return myData; }
	T front(void) const;
	T back(void) const;

	//methods
	iterator insert(iterator pos, const T& value);
	iterator insert(const_iterator pos, const T& value);
	iterator erase(iterator pos);
	iterator erase(const_iterator pos);
	iterator erase(iterator first, iterator last);
	iterator erase(const_iterator first, const_iterator last);
	void clear(void);
	void resize(size_t count);
	void resize(size_t count, const T& value);
	void assign(const std::size_t n, const T& val) noexcept;
	T& at(size_t index) const;
	void push_back(const T& value);
	void push_back(T&& value);
	void pop_back(void);
	void shrink_to_fit(void);

	//iterators
	iterator begin() const { return myData; } 
	const_iterator cbegin() const { return myData; }
	reverse_iterator rbegin() const{ return myData; }
	const_reverse_iterator crbegin() const { return myData; }
	iterator end() const { return myData + mySize; }
	const_iterator cend() const { return myData + mySize; }
	reverse_iterator rend() const { return myData + mySize; }
	const_reverse_iterator crend() const { return myData + mySize; }

	void print_me() { //For tests only
		for (int i = 0; i < this->size(); ++i) {
			std::cout << this->at(i) << " ";
		}
		std::cout << '\n';
	}
};

template <typename T>
DynArray<T>::~DynArray() {
	delete[] myData;
}

template <typename T>
DynArray<T>::DynArray(size_t count) {
	mySize = 0;
	myCapacity = count;
	myData = new T[myCapacity];
}

template <typename T>
DynArray<T>::DynArray(iterator start, iterator end) {
	auto dist = std::distance(start, end);
	mySize = myCapacity = dist;
	myData = new T[mySize];
	std::uninitialized_copy_n(start, mySize, myData);
}

template <typename T>
DynArray<T>::DynArray(const DynArray<T>& dynArr) {
	mySize = myCapacity = dynArr.mySize;
	myData = new T[mySize];
	std::uninitialized_copy_n(dynArr.myData, mySize, myData);
}

template <typename T>
DynArray<T>& DynArray<T>::operator=(const DynArray& dynArr) {
	if (this != &dynArr) {
		delete[] myData;
		myCapacity = dynArr.myCapacity;
		mySize = dynArr.mySize;
		myData = new T[mySize];
		std::uninitialized_copy_n(dynArr.myData, mySize, myData);
	}
	return *this;
}

template <typename T>
bool DynArray<T>::operator==(const DynArray& dynArr) const {
	return std::equal(begin(), end(), dynArr.begin(), dynArr.end());
}

template <typename T>
bool DynArray<T>::operator!=(const DynArray& dynArr) const {
	return !operator==(dynArr);
}

template <typename T>
T& DynArray<T>::operator[](size_t index) const {
	return myData[index];
}

template <typename T>
T& DynArray<T>::at(size_t index) const {
	if (index > mySize)
		throw std::out_of_range("Out of range!");
	return operator[](index);
}

template <typename T>
T DynArray<T>::front(void) const {
	return myData[0];
}

template <typename T>
T DynArray<T>::back(void) const {
	return myData[mySize - 1];
}

template <typename T>
typename DynArray<T>::iterator DynArray<T>::insert(iterator pos, const T& value)
{
	iterator temp = begin();
	size_t i = 0;
	while (temp != pos) {
		i++;
		temp++;
	}
	temp = nullptr;

	if (mySize + 1 > myCapacity) {
		reserveMemory(myCapacity+1);
	}
	for (size_t j = mySize; j > i; --j) {
		myData[j] = myData[j - 1];
	}
	myData[i] = value;
	mySize++;

	return &myData[i];
}

template<typename T>
typename DynArray<T>::iterator DynArray<T>::insert(const_iterator pos, const T& value) {
	iterator temp = begin();
	size_t i = 0;
	while (temp != pos) {
		i++;
		temp++;
	}
	temp = nullptr;

	if (mySize + 1 > myCapacity) {
		reserveMemory(myCapacity+1);
	}
	for (size_t j = mySize; j > i; --j) {
		myData[j] = myData[j - 1];
	}
	myData[i] = value;
	mySize++;

	return &myData[i];
}

template<typename T>
typename  DynArray<T>::iterator DynArray<T>::erase(iterator pos)
{
	if (this->empty()) 
		return myData;
	size_t deletePos = 0;
	for (size_t i = 0; i < mySize; ++i) {
		if (&myData[i] == pos) {
			deletePos = i;
		}
	}
	for (size_t i = deletePos; i < mySize; ++i) {
		myData[i] = myData[i + 1];
	}
	myData[mySize].~T();
	mySize = mySize - 1;
	if (deletePos >= mySize) deletePos = mySize-1;
	return &myData[deletePos];
}

template<typename T>
typename  DynArray<T>::iterator DynArray<T>::erase(const_iterator pos)
{
	if (this->empty()) 
		return myData;
	size_t deletePos = 0;
	for (size_t i = 0; i < mySize; ++i) {
		if (&myData[i] == pos) {
			deletePos = i;
		}
	}
	for (size_t i = deletePos; i < mySize; ++i) {
		myData[i] = myData[i + 1];
	}
	myData[mySize].~T();
	mySize--;
	if (deletePos >= mySize) deletePos = mySize - 1;
	return &myData[deletePos];
}

template<typename T>
typename  DynArray<T>::iterator DynArray<T>::erase(iterator first, iterator last)
{
	size_t firstPos = 0;
	size_t lastPos = 0;
	size_t i;
	for (i=0; i < mySize; ++i) {
		if (&myData[i] == first) {
			firstPos = i;
			break;
		}
	}
	for (i; i < mySize; ++i) {
		if (&myData[i] == last - 1) {
			if (i != 0) lastPos = i;
			else return last;
		}
	}

	if (lastPos - firstPos <= 0 ) return last;

	for (size_t i = firstPos; i <= lastPos; i++) {
		int z = 1;
		if (lastPos + z < mySize) {
			myData[i] = myData[lastPos + z];
			myData[lastPos + z].~T();
		}
		else {
			myData[i].~T();
		}
		z++;
	}
	mySize = mySize - (lastPos - firstPos + 1);
	return &myData[firstPos];
}

template<typename T>
typename  DynArray<T>::iterator DynArray<T>::erase(const_iterator first, const_iterator last)
{
	size_t firstPos = 0;
	size_t lastPos = 0;
	size_t i;
	for (i = 0; i < mySize; ++i) {
		if (&myData[i] == first) {
			firstPos = i;
			break;
		}
	}
	for (i; i < mySize; ++i) {
		if (&myData[i] == last - 1) {
			if (i != 0) lastPos = i;
			else return last;
		}
	}

	if (lastPos - firstPos <= 0) return last;

	for (size_t i = firstPos; i <= lastPos; i++) {
		int z = 1;
		if (lastPos + z < mySize) {
			myData[i] = myData[lastPos + z];
			myData[lastPos + z].~T();
		}
		else {
			myData[i].~T();
		}
		z++;
	}
	mySize = mySize - (lastPos - firstPos + 1);
	return &myData[firstPos];
}

template<typename T>
void DynArray<T>::clear(void)
{
	this->erase(this->begin(), this->end());
}

template<typename T>
void DynArray<T>::resize(size_t count)
{
	if (count < 0) {
			throw std::out_of_range( "DynArray in function resize" );
	}

	T* tmp = new T[count];

	if (count > myCapacity) {
		std::uninitialized_copy_n(myData, mySize, tmp);
		std::fill_n(tmp + mySize, count - mySize, T());
		myCapacity = count;
		delete[] myData;
	} 
	else if (count == myCapacity) {
		std::uninitialized_copy_n(myData, mySize, tmp);
		delete[] myData;
	}
	if (count < mySize) {
		std::uninitialized_copy_n(myData, count, tmp);
	}
	
	mySize = count;
	myData = tmp;
	tmp = nullptr;
}

template<typename T>
void DynArray<T>::resize(size_t count, const T& value)
{

	if (count < 0) {
		throw std::out_of_range( "DynArray in function resize");
	}
	T* tmp = new T[count];

	if (count > myCapacity) {
		std::uninitialized_copy_n(myData, mySize, tmp);
		std::fill_n(tmp + mySize, count - mySize, T(value));
		myCapacity = count;
		delete[] myData;
	}
	else if (count == myCapacity) {
		std::uninitialized_copy_n(myData, mySize, tmp);
		std::fill_n(tmp + mySize, count - mySize, T(value));
		delete[] myData;
	}
	if (count < mySize) {
		std::uninitialized_copy_n(myData, count, tmp);
	}
	
	mySize = count;
	myData = tmp;
	tmp = nullptr;
}

template<typename T>
void DynArray<T>::assign(size_t n, const T& val) noexcept
{
	if (n >= myCapacity) {
		this->clear();
		reserveMemory(n);
		std::fill_n(myData, n, T(val));
	}
	else {
		this->clear();
		std::fill_n(myData, n, T(val));
	}	
	mySize = n;
}

template <typename T>
void DynArray<T>::push_back(const T& value) {
	if (myCapacity == 0) {
		mySize++;
		myData = new T[++myCapacity];
		myData[0] = value;
	}
	else {
		if (mySize >= myCapacity)
			reserveMemory(myCapacity * 2);
		myData[mySize++] = value;
	}
}

template <typename T>
void DynArray<T>::push_back(T&& value) {
	if (myCapacity == 0) {
		mySize++;
		myData = new T[++myCapacity];
		myData[0] = value;
	}
	else {
		if (mySize >= myCapacity)
			reserveMemory(myCapacity * 2);
		myData[mySize++] = value;
	}
}

template <typename T>
void DynArray<T>::pop_back(void) {
	if (mySize == 0)
		throw std::out_of_range("pop_back - Out of range!");
	myData[mySize - 1].~T();
	mySize--;
}

template <typename T>
void DynArray<T>::shrink_to_fit(void) {
	if (myCapacity > mySize) {
		T* tmp = new T[mySize];
		std::uninitialized_copy_n(myData, mySize, tmp);
		delete[] myData;
		myData = tmp;
		myCapacity = mySize;
	}
}

template <typename T>
void DynArray<T>::reserveMemory(size_t newCapacity) {
	if (newCapacity > myCapacity) {
		T* tmp = new T[newCapacity];
		std::uninitialized_copy_n(myData, mySize, tmp);
		delete[] myData;
		myData = tmp;
		myCapacity = newCapacity;
	}
}

#endif _DYNARRAY_H_