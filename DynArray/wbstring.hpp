#ifndef _WBSTRING_H_
#define _WBSTRING_H_

#include "DynArray.hpp"
#include "String.hpp"

class BasicString;

class WideString : public String<wchar_t> {
	using DynArray<wchar_t>::myCapacity;
	using DynArray<wchar_t>::mySize;
	using DynArray<wchar_t>::myData;
	using String<wchar_t>::blockSize;

public:
	friend class BasicString;

	WideString(const WideString& s);
	WideString(const BasicString& b);
	WideString() :String() { };
	WideString(const wchar_t* s) :String(s) { };
	WideString(const std::initializer_list<wchar_t>& il) :String(il) { };
	WideString(std::string s) :String(s) { };
	WideString(const wchar_t s[], int count) :String(s, count) { };
	WideString(int count, const wchar_t c) :String(count, c) { };

	WideString operator +(const WideString& s);
	WideString& operator =(wchar_t c);
	WideString& operator =(const BasicString& s);
	bool operator >(const WideString& s) const;
	bool operator <(const WideString& s) const;
	WideString operator +(const wchar_t* s);
	WideString operator +(std::string s);
	WideString& operator +=(const wchar_t* s);
	WideString& operator +=(std::string s);
	WideString& operator =(const wchar_t* s);
	WideString& operator =(std::string s);
	bool operator >=(const WideString& s) const;
	bool operator <=(const WideString& s) const;

	friend std::wostream& operator <<(std::wostream& ost, WideString& s);
	friend std::wistream& operator >>(std::wistream& ist, WideString& s);
};

class BasicString : public String<char> {
	using DynArray<char>::myCapacity;
	using DynArray<char>::mySize;
	using DynArray<char>::myData;

public:
	friend class WideString;

	//Only in BasicString
	const char* c_str(void) const;

	BasicString(const BasicString& s);
	BasicString(const WideString& s);
	BasicString() :String() { };
	BasicString(const char* s) :String(s) { };
	BasicString(const std::initializer_list<char>& il) :String(il) { };
	BasicString(std::string s) :String(s) { };
	BasicString(const char s[], int count) :String(s, count) { };
	BasicString(int count, const char c) :String(count, c) { };

	BasicString operator +(const BasicString& s);
	BasicString& operator =(char c);
	BasicString& operator =(const WideString& s);
	bool operator >(const BasicString& s) const;
	bool operator <(const BasicString& s) const;
	BasicString operator +(const char* s);
	BasicString operator +(std::string s);
	BasicString& operator +=(const char* s);
	BasicString& operator +=(std::string s);
	BasicString& operator =(const char* s);
	BasicString& operator =(std::string s);
	bool operator >=(const BasicString& s) const;
	bool operator <=(const BasicString& s) const;

	friend std::ostream& operator <<(std::ostream& ost, BasicString& s);
	friend std::istream& operator >>(std::istream& ist, BasicString& s);
};

#endif _WBSTRING_H_