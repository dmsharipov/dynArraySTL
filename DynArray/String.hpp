#ifndef _STRING_H_
#define _STRING_H_
#include "DynArray.hpp"
#include <string>

template <typename T>
class String : public DynArray<T> {
	using DynArray<T>::myCapacity;
	using DynArray<T>::mySize;
	using DynArray<T>::myData;

protected:
	static const size_t npos = -1;
	const size_t blockSize = 16 / sizeof(T);

	void change_capacity(size_t size)
	{
		while (myCapacity <= size)
			myCapacity += blockSize;
	}

	bool compare_char(const T* s, size_t pos) const {
		for (int i = 1; i < myStrlen(s); ++i) {
			if (myData[pos + i] != s[i])
				return false;
		}
		return true;
	}

	bool compare_string(std::string s, size_t pos) const
	{
		for (int i = 1; i < s.length(); ++i) {
			if (myData[pos + i] != T(s[i]))
				return false;
		}
		return true;
	}

	size_t myStrlen(const T* data) const {
		if (blockSize == 16)
			return strlen((char*)data);
		else
			return wcslen((wchar_t*)data);
	}

public:
	typedef T* iterator;
	typedef T* reverse_iterator;
	typedef const T* const_iterator;
	typedef const T* const_reverse_iterator;

	iterator begin() const { return myData; }
	const_iterator cbegin() const { return myData; }
	reverse_iterator rbegin() const { return myData; }
	const_reverse_iterator crbegin() const { return myData; }
	iterator end() const { return myData + mySize; }
	const_iterator cend() const { return myData + mySize; }
	reverse_iterator rend() const { return myData + mySize; }
	const_reverse_iterator crend() const { return myData + mySize; }

	String() {
		myCapacity = blockSize;
		myData = new T[myCapacity];
		mySize = 0;
	}

	String(const std::initializer_list<T>& il)
	{
		int i = 0;
		mySize = il.size();
		myCapacity = blockSize;
		change_capacity(mySize);
		myData = new T[myCapacity];
		for (auto& element : il) {
			myData[i] = element;
			++i;
		}
		myData[i] = '\0';
	}

	String(const T* s)
	{
		int i;
		mySize = myStrlen(s);
		myCapacity = blockSize;
		change_capacity(mySize);
		myData = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			myData[i] = s[i];
		myData[i] = '\0';
	}

	String(std::string s)
	{
		int i;
		mySize = s.length();
		myCapacity = blockSize;
		change_capacity(mySize);
		myData = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			myData[i] = s[i];
		myData[i] = '\0';
	}

	String(const T s[], int count)
	{
		int i;
		mySize = count;
		myCapacity = blockSize;
		change_capacity(mySize);
		myData = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			myData[i] = s[i];
		myData[i] = '\0';
	}

	String(int count, const T c)
	{
		int i;
		mySize = count;
		myCapacity = blockSize;
		change_capacity(mySize);
		myData = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			myData[i] = c;
		myData[i] = '\0';
	}

	String operator +(const String& s)
	{
		int i;
		size_t buf_len = mySize + s.mySize;
		T* data = new T[buf_len + 1];
		for (i = 0; i < mySize; ++i)
			data[i] = myData[i];
		for (i = 0; i < s.mySize; ++i)
			data[mySize + i] = s.myData[i];
		data[buf_len] = '\0';
		return String(data);
	}

	String& operator =(T c)
	{
		mySize = 1;
		delete[] myData;
		myCapacity = blockSize;
		myData = new T[2];
		myData[0] = c;
		myData[1] = '\0';
		return *this;
	}

	bool operator >(const String& s) const
	{
		int min_len = (mySize < s.mySize) ? mySize : s.mySize;
		for (int i = 0; i < min_len; ++i) {
			if ((int)this->myData[i] > (int)s.myData[i])
				return true;
		}
		return false;
	}

	bool operator <(const String& s) const
	{
		int min_len = (mySize < s.mySize) ? mySize : s.mySize;
		for (int i = 0; i < min_len; ++i) {
			if ((int)this->myData[i] < (int)s.myData[i])
				return true;
		}
		return false;
	}

	String operator +(const T* s)
	{
		int i;
		size_t buf_len = mySize + myStrlen(s);
		T* data = new T[buf_len + 1];
		for (i = 0; i < mySize; ++i)
			data[i] = myData[i];
		for (i = 0; i < myStrlen(s); ++i)
			data[mySize + i] = s[i];
		data[buf_len] = '\0';
		return String(data);
	}

	String operator +(std::string s)
	{
		int i;
		size_t buf_len = mySize + s.length();
		T* data = new T[buf_len + 1];
		for (i = 0; i < mySize; ++i)
			data[i] = myData[i];
		for (i = 0; i < s.length(); ++i)
			data[mySize + i] = s[i];
		data[buf_len] = '\0';
		return String(data);
	}

	String& operator +=(const T* s)
	{
		int i;
		size_t buf_len = mySize + myStrlen(s);
		change_capacity(buf_len);
		T* data = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			data[i] = myData[i];
		for (i = 0; i < myStrlen(s); ++i)
			data[mySize + i] = s[i];
		data[buf_len] = '\0';
		delete[] myData;
		myData = data;
		mySize = buf_len;
		return *this;
	}

	String& operator +=(std::string s)
	{
		int i;
		size_t buf_len = mySize + s.length();
		change_capacity(buf_len);
		T* data = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			data[i] = myData[i];
		for (i = 0; i < s.length(); ++i)
			data[mySize + i] = s[i];
		data[buf_len] = '\0';
		delete[] myData;
		myData = data;
		mySize = buf_len;
		return *this;
	}

	String& operator =(const T* s)
	{
		int i;
		mySize = myStrlen(s);
		delete[] myData;
		myCapacity = blockSize;
		change_capacity(mySize);
		myData = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			myData[i] = s[i];
		myData[i] = '\0';
		return *this;
	}

	String& operator =(std::string s)
	{
		int i;
		mySize = s.length();
		delete[] myData;
		myCapacity = blockSize;
		change_capacity(mySize);
		myData = new T[myCapacity];
		for (i = 0; i < mySize; ++i)
			myData[i] = s[i];
		myData[i] = '\0';
		return *this;
	}

	bool operator >=(const String& s) const
	{
		return !(*this < s);
	}

	bool operator <=(const String& s) const
	{
		return !(*this > s);
	}

	iterator insert(iterator pos, const T& value)
	{
		iterator temp = begin();
		size_t i = 0;
		while (temp != pos) {
			i++;
			temp++;
		}
		temp = nullptr;

		if (mySize + 1 > myCapacity) {
			DynArray<T>::reserveMemory(myCapacity + 1);
		}
		for (size_t j = mySize; j > i; --j) {
			myData[j] = myData[j - 1];
		}
		myData[i] = value;
		mySize++;

		return &myData[i];
	}

	iterator insert(const_iterator pos, const T& value) {
		iterator temp = begin();
		size_t i = 0;
		while (temp != pos) {
			i++;
			temp++;
		}
		temp = nullptr;

		if (mySize + 1 > myCapacity) {
			DynArray<T>::reserveMemory(myCapacity + 1);
		}
		for (size_t j = mySize; j > i; --j) {
			myData[j] = myData[j - 1];
		}
		myData[i] = value;
		mySize++;

		return &myData[i];
	}

	iterator erase(iterator pos)
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
		if (deletePos >= mySize) deletePos = mySize - 1;
		return &myData[deletePos];
	}

	iterator erase(const_iterator pos)
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

	iterator erase(iterator first, iterator last)
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

	iterator erase(const_iterator first, const_iterator last)
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

	size_t length(void) const
	{
		return mySize;
	}

	friend std::ostream& operator <<(std::ostream& ost, String& s)
	{
		for (int i = 0; i < s.length(); ++i)
			ost << s[i];
		return ost;
	}

	friend std::istream& operator >>(std::istream& ist, String& s)
	{
		T buf[1024];
		ist >> buf;
		s = buf;
		return ist;
	}

	String& append(int count, T c)
	{
		int i;
		T* buf = new T[count + 1];
		for (i = 0; i < count; ++i)
			buf[i] = c;
		buf[i] = '\0';
		return (*this += buf);
	}

	String& append(const T* s)
	{
		return (*this += s);
	}

	String& append(std::string s)
	{
		return (*this += s);
	}

	String& append(std::string s, int index, size_t count)
	{
		if (index + count > s.length())
			return *this;

		int i;
		T* buf = new T[count + 1];
		for (i = 0; i < count; ++i)
			buf[i] = s[index + i];
		buf[i] = '\0';
		return (*this += buf);
	}

	String& append(const T* s, int index, size_t count)
	{
		if (index + count > myStrlen(s))
			return *this;

		int i;
		T* buf = new T[count + 1];
		for (i = 0; i < count; ++i)
			buf[i] = s[index + i];
		buf[i] = '\0';
		return (*this += buf);
	}

	String& insert(int index, size_t count, T c)
	{
		if (index > mySize || index < 0)
			return *this;

		int i;
		T* buf = new T[count + 1];
		for (i = 0; i < count; ++i)
			buf[i] = c;
		buf[i] = '\0';
		T* buf_before = new T[index + 1];
		for (i = 0; i < index; i++)
			buf_before[i] = myData[i];
		buf_before[i] = '\0';
		T* buf_after = new T[mySize - index + 1];
		for (i = 0; i < mySize - index; i++)
			buf_after[i] = myData[index + i];
		buf_after[i] = '\0';
		*this = buf_before;
		*this += buf;
		return (*this += buf_after);
	}

	String& insert(int index, std::string s) 
	{
		if (index > mySize || index < 0)
			return *this;

		int i;
		T* buf_before = new T[index + 1];
		for (i = 0; i < index; i++)
			buf_before[i] = myData[i];
		buf_before[i] = '\0';
		T* buf_after = new T[mySize - index + 1];
		for (i = 0; i < mySize - index; i++)
			buf_after[i] = myData[index + i];
		buf_after[i] = '\0';
		*this = buf_before;
		*this += s;
		return (*this += buf_after);
	}

	String& insert(int index, std::string s, size_t count)
	{
		if (index > mySize || index < 0 || count > s.length())
			return *this;

		int i;
		T* buf = new T[count + 1];
		for (i = 0; i < count; ++i)
			buf[i] = s[i];
		buf[i] = '\0';
		T* buf_before = new T[index + 1];
		for (i = 0; i < index; i++)
			buf_before[i] = myData[i];
		buf_before[i] = '\0';
		T* buf_after = new T[mySize - index + 1];
		for (i = 0; i < mySize - index; i++)
			buf_after[i] = myData[index + i];
		buf_after[i] = '\0';
		*this = buf_before;
		*this += buf;
		return (*this += buf_after);
	}

	String& insert(int index, const T* s, size_t count)
	{
		if (index > mySize || index < 0 || count > myStrlen(s))
			return *this;

		int i;
		T* buf = new T[count + 1];
		for (i = 0; i < count; ++i)
			buf[i] = s[i];
		buf[i] = '\0';
		T* buf_before = new T[index + 1];
		for (i = 0; i < index; i++)
			buf_before[i] = myData[i];
		buf_before[i] = '\0';
		T* buf_after = new T[mySize - index + 1];
		for (i = 0; i < mySize - index; i++)
			buf_after[i] = myData[index + i];
		buf_after[i] = '\0';
		*this = buf_before;
		*this += buf;
		return (*this += buf_after);
	}

	String& erase(int index, size_t count)
	{
		if (index > mySize || index < 0 || (count + index) > mySize)
			return *this;

		int i;
		T* buf_before = new T[index + 1];
		for (i = 0; i < index; i++)
			buf_before[i] = myData[i];
		buf_before[i] = '\0';
		T* buf_after = new T[mySize - index - count + 1];
		for (i = 0; i < mySize - index - count; i++)
			buf_after[i] = myData[index + count + i];
		buf_after[i] = '\0';
		*this = buf_before;
		return (*this += buf_after);
	}

	String& replace(int index, size_t count, const T* s)
	{
		this->erase(index, count);
		this->insert(index, s);
		return *this;
	}

	String& replace(int index, size_t count, std::string s)
	{
		this->erase(index, count);
		this->insert(index, s);
		return *this;
	}

	const T* substr(int index) const
	{
		if (index > mySize)
			throw std::out_of_range("Out of range substr"); 
		int i;
		T* buf = new T[mySize - index + 1];
		for (i = 0; i < mySize - index; ++i)
			buf[i] = myData[i + index];
		buf[i] = '\0';
		return buf;
	}

	const T* substr(int index, size_t count) const
	{
		if (index > mySize || index < 0 || (count + index) > mySize)
			throw std::out_of_range("Out of range substr");
		int i;
		T* buf = new T[count + 1];
		for (i = 0; i < count; ++i)
			buf[i] = myData[i + index];
		buf[i] = '\0';
		return buf;
	}

	size_t find(const T* s) const
	{
		return find(s, 0);
	}

	size_t find(std::string s) const
	{
		return find(s, 0);
	}

	size_t find(const T* s, size_t pos) const
	{
		if (pos < 0 || pos > mySize)
			return npos;

		size_t ret = npos;
		for (; pos <= mySize - myStrlen(s); ++pos) {
			if (myData[pos] == s[0] && compare_char(s, pos)) {
				ret = pos;
				break;
			}
		}
		return ret;
	}

	size_t find(std::string s, size_t pos) const
	{
		if (pos < 0 || pos > mySize)
			return npos;

		size_t ret = npos;
		for (; pos <= mySize - s.length(); ++pos) {
			if (myData[pos] == s[0] && compare_string(s, pos)) {
				ret = pos;
				break;
			}
		}
		return ret;
	}

};

#endif _STRING_H_