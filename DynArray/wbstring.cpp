#define _CRT_SECURE_NO_WARNINGS
#include "wbstring.hpp"

WideString:: WideString(const WideString& s)
{
	int i;
	mySize = s.mySize;
	myCapacity = blockSize;
	change_capacity(mySize);
	myData = new wchar_t[myCapacity];
	for (i = 0; i < mySize; ++i)
		myData[i] = s.myData[i];
	myData[i] = '\0';
}

WideString::WideString(const BasicString& b) {
	myCapacity = b.myCapacity;
	if (myData != nullptr)
		delete[] myData;
	myData = new wchar_t[myCapacity];
	//mySize = 0;//new
	mySize = mbstowcs(myData, b.myData, myCapacity);
	if (mySize != -1)
		myData[mySize] = '\0';
	else
		throw std::out_of_range("mbstowcs returned -1");
}

WideString WideString::operator +(const WideString& s)
{
	int i;
	size_t buf_len = mySize + s.mySize;
	wchar_t* data = new wchar_t[buf_len + 1];
	for (i = 0; i < mySize; ++i)
		data[i] = myData[i];
	for (i = 0; i < s.mySize; ++i)
		data[mySize + i] = s.myData[i];
	data[buf_len] = '\0';
	return WideString(data);
}

WideString& WideString::operator =(wchar_t c)
{
	mySize = 1;
	delete[] myData;
	myCapacity = blockSize;
	myData = new wchar_t[2];
	myData[0] = c;
	myData[1] = '\0';
	return *this;
}

WideString& WideString::operator =(const BasicString& s)
{
	myCapacity = s.myCapacity;
	if (myData != nullptr)
		delete[] myData;
	myData = new wchar_t[myCapacity];
	//mySize = 0;//new
	mySize = mbstowcs(myData, s.myData, myCapacity);
	if (mySize != -1)
		myData[mySize] = '\0';
	else
		throw std::out_of_range("mbstowcs returned -1");
	return *this;
}

bool WideString::operator >(const WideString& s) const
{
	int min_len = (mySize < s.mySize) ? mySize : s.mySize;
	for (int i = 0; i < min_len; ++i) {
		if ((int)this->myData[i] > (int)s.myData[i])
			return true;
	}
	return false;
}

bool WideString::operator <(const WideString& s) const
{
	int min_len = (mySize < s.mySize) ? mySize : s.mySize;
	for (int i = 0; i < min_len; ++i) {
		if ((int)this->myData[i] < (int)s.myData[i])
			return true;
	}
	return false;
}

WideString WideString::operator +(const wchar_t* s)
{
	int i;
	size_t buf_len = mySize + myStrlen(s);
	wchar_t* data = new wchar_t[buf_len + 1];
	for (i = 0; i < mySize; ++i)
		data[i] = myData[i];
	for (i = 0; i < myStrlen(s); ++i)
		data[mySize + i] = s[i];
	data[buf_len] = '\0';
	return WideString(data);
}

WideString WideString::operator +(std::string s)
{
	int i;
	size_t buf_len = mySize + s.length();
	wchar_t* data = new wchar_t[buf_len + 1];
	for (i = 0; i < mySize; ++i)
		data[i] = myData[i];
	for (i = 0; i < s.length(); ++i)
		data[mySize + i] = s[i];
	data[buf_len] = '\0';
	return WideString(data);
}

WideString& WideString::operator +=(const wchar_t* s)
{
	int i;
	size_t buf_len = mySize + myStrlen(s);
	change_capacity(buf_len);
	wchar_t* data = new wchar_t[myCapacity];
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

WideString& WideString::operator +=(std::string s)
{
	int i;
	size_t buf_len = mySize + s.length();
	change_capacity(buf_len);
	wchar_t* data = new wchar_t[myCapacity];
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

WideString& WideString::operator =(const wchar_t* s)
{
	int i;
	mySize = myStrlen(s);
	delete[] myData;
	myCapacity = blockSize;
	change_capacity(mySize);
	myData = new wchar_t[myCapacity];
	for (i = 0; i < mySize; ++i)
		myData[i] = s[i];
	myData[i] = '\0';
	return *this;
}

WideString& WideString::operator =(std::string s)
{
	int i;
	mySize = s.length();
	delete[] myData;
	myCapacity = blockSize;
	change_capacity(mySize);
	myData = new wchar_t[myCapacity];
	for (i = 0; i < mySize; ++i)
		myData[i] = s[i];
	myData[i] = '\0';
	return *this;
}

bool WideString::operator >=(const WideString& s) const
{
	return !(*this < s);
}

bool WideString::operator <=(const WideString& s) const
{
	return !(*this > s);
}

std::wostream& operator <<(std::wostream& ost, WideString& s)
{
	for (int i = 0; i < s.length(); ++i)
		ost << s[i];
	return ost;
}

std::wistream& operator >>(std::wistream& ist, WideString& s)
{
	wchar_t buf[1024];
	ist >> buf;
	s = buf;
	return ist;
}


const char*
BasicString::c_str(void) const
{
	return myData;
}

BasicString::BasicString(const BasicString& s)
{
	int i;
	mySize = s.mySize;
	myCapacity = blockSize;
	change_capacity(mySize);
	myData = new char[myCapacity];
	for (i = 0; i < mySize; ++i)
		myData[i] = s.myData[i];
	myData[i] = '\0';
}

BasicString::BasicString(const WideString& s) {
	myCapacity = s.myCapacity;
	if (myData != nullptr)
		delete[] myData;
	myData = new char[myCapacity];
	mySize = wcstombs(myData, s.myData, myCapacity);
	if (mySize != -1)
		myData[mySize] = '\0';
	else
		throw std::out_of_range("wcstombs returned -1");
}

BasicString BasicString::operator +(const BasicString& s)
{
	int i;
	size_t buf_len = mySize + s.mySize;
	char* data = new char[buf_len + 1];
	for (i = 0; i < mySize; ++i)
		data[i] = myData[i];
	for (i = 0; i < s.mySize; ++i)
		data[mySize + i] = s.myData[i];
	data[buf_len] = '\0';
	return BasicString(data);
}

BasicString& BasicString::operator =(char c)
{
	mySize = 1;
	delete[] myData;
	myCapacity = blockSize;
	myData = new char[2];
	myData[0] = c;
	myData[1] = '\0';
	return *this;
}

BasicString& BasicString::operator =(const WideString& s)
{
	myCapacity = s.myCapacity;
	if (myData != nullptr)
		delete[] myData;
	myData = new char[myCapacity];
	mySize = wcstombs(myData, s.myData, myCapacity);
	if (mySize != -1)
		myData[mySize] = '\0';
	else
		throw std::out_of_range("wcstombs returned -1");
	return *this;
}

bool BasicString::operator >(const BasicString& s) const
{
	int min_len = (mySize < s.mySize) ? mySize : s.mySize;
	for (int i = 0; i < min_len; ++i) {
		if ((int)this->myData[i] > (int)s.myData[i])
			return true;
	}
	return false;
}

bool BasicString::operator <(const BasicString& s) const
{
	int min_len = (mySize < s.mySize) ? mySize : s.mySize;
	for (int i = 0; i < min_len; ++i) {
		if ((int)this->myData[i] < (int)s.myData[i])
			return true;
	}
	return false;
}

BasicString BasicString::operator +(const char* s)
{
	int i;
	size_t buf_len = mySize + myStrlen(s);
	char* data = new char[buf_len + 1];
	for (i = 0; i < mySize; ++i)
		data[i] = myData[i];
	for (i = 0; i < myStrlen(s); ++i)
		data[mySize + i] = s[i];
	data[buf_len] = '\0';
	return BasicString(data);
}

BasicString BasicString::operator +(std::string s)
{
	int i;
	size_t buf_len = mySize + s.length();
	char* data = new char[buf_len + 1];
	for (i = 0; i < mySize; ++i)
		data[i] = myData[i];
	for (i = 0; i < s.length(); ++i)
		data[mySize + i] = s[i];
	data[buf_len] = '\0';
	return BasicString(data);
}

BasicString& BasicString::operator +=(const char* s)
{
	int i;
	size_t buf_len = mySize + myStrlen(s);
	change_capacity(buf_len);
	char* data = new char[myCapacity];
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

BasicString& BasicString::operator +=(std::string s)
{
	int i;
	size_t buf_len = mySize + s.length();
	change_capacity(buf_len);
	char* data = new char[myCapacity];
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

BasicString& BasicString::operator =(const char* s)
{
	int i;
	mySize = myStrlen(s);
	delete[] myData;
	myCapacity = blockSize;
	change_capacity(mySize);
	myData = new char[myCapacity];
	for (i = 0; i < mySize; ++i)
		myData[i] = s[i];
	myData[i] = '\0';
	return *this;
}

BasicString& BasicString::operator =(std::string s)
{
	int i;
	mySize = s.length();
	delete[] myData;
	myCapacity = blockSize;
	change_capacity(mySize);
	myData = new char[myCapacity];
	for (i = 0; i < mySize; ++i)
		myData[i] = s[i];
	myData[i] = '\0';
	return *this;
}

bool BasicString::operator >=(const BasicString& s) const
{
	return !(*this < s);
}

bool BasicString::operator <=(const BasicString& s) const
{
	return !(*this > s);
}

std::ostream& operator <<(std::ostream& ost, BasicString& s)
{
	for (int i = 0; i < s.length(); ++i)
		ost << s[i];
	return ost;
}

std::istream& operator >>(std::istream& ist, BasicString& s)
{
	char buf[1024];
	ist >> buf;
	s = buf;
	return ist;
}