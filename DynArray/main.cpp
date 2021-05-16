#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include "wbstring.hpp"

struct G {
	int i;
	char t;
	double f;
};

int main(void) {
	setlocale(LC_ALL, "Russian");

	//DynArray()
	DynArray<char> characters;
	characters.push_back('a');
	characters.push_back('b');
	characters.push_back('c');
	std::cout << "The vector abc holds: ";
	characters.print_me();

	//DynArray(count)
	DynArray<int> with_count(10);
	std::cout << "DynArray<int> with_count(10) with size: " << with_count.size() << " and capacity: " << with_count.capacity() << std::endl;

	//DynArray(iterator start, iterator end)
	DynArray<char> with_iter(characters.begin(), characters.end());
	std::cout << "After DynArray<char> with_iter(characters.begin(), characters.end()) holds: ";
	with_iter.print_me();

	//DynArray(DynArray)
	DynArray<char> copy(with_iter);
	std::cout << "after DynArray<char> copy(with_iter) copy holds: ";
	copy.print_me();

	//operator []
	copy[1] = 'z';
	std::cout << "after copy[1] = 'z' copy holds: ";
	copy.print_me();

	//assign
	characters.assign(5, 'r');
	std::cout << "The vector rrrrr holds: ";
	characters.print_me();
	char k = 'i';
	characters.assign(3, k);
	std::cout << "The vector iii holds: ";
	characters.print_me();

	//push_back
	std::cout << "After 4 push_backs characters1 holds: ";
	DynArray<char>character1;
	character1.push_back('i');
	character1.push_back('b');
	character1.push_back('k');
	character1.push_back('s');
	character1.print_me();
	character1.erase(character1.begin(), character1.end());

	//pop_back
	character1.push_back('i');
	character1.push_back('b');
	character1.push_back('k');
	character1.push_back('s');
	character1.pop_back();
	character1.pop_back();
	character1.pop_back();
	character1.pop_back();
	std::cout << "After 4 pop_backs characters1 is ";
	if (character1.empty())
		std::cout << "empty - that's right!" << std::endl;
	else
		std::cout << "not empty - FAIL!" << std::endl;

	//With struct
	DynArray<struct G> structures;
	struct G f = { 911, 'x', 13.37 };
	structures.push_back(f);
	structures.push_back(f);
	structures.push_back(f);
	for (int i = 0; i < structures.size(); ++i) std::cout << structures[i].i << " ";
	for (int i = 0; i < structures.size(); ++i) std::cout << structures[i].t << " ";
	for (int i = 0; i < structures.size(); ++i) std::cout << structures[i].f << " ";

	characters.clear();
	characters.push_back('a');
	characters.push_back('b');
	characters.push_back('c');
	characters.push_back('d');
	characters.push_back('e');
	characters.push_back('f');
	characters.push_back('g');
	std::cout << "The vector characters holds: ";
	characters.print_me();

	DynArray<char> characters2 = characters;
	std::cout << "The vector characters2 holds: ";
	characters2.print_me();

	//at
	DynArray<int> data;
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);
	data.push_back(4);
	data.at(1) = 88;

	// Read element 2
	std::cout << "Element at index 2 has value " << data.at(2) << '\n';
	data.print_me();

	//Operators == and !=
	if ((characters == characters2) && (!(characters != characters2)))
		std::cout << "It's equal" << std::endl;
	else 
		std::cout << "It's not equal" << std::endl;

	//Operator= with not empty DynArray
	DynArray<char> characters3 = characters;
	DynArray<char> characters4 = characters;
	DynArray<char> characters5 = characters;

	//Insert
	DynArray<char> nan;
	nan.insert(nan.begin(), 'k');
	nan.insert(nan.begin(), 'b');
	nan.insert(nan.end(), 's');
	nan.insert(nan.begin(), 'i');
	std::cout << "After 4 inserts in nan: ";
	nan.print_me();

	//front and back
	std::cout << "nan.front(): " << nan.front() << std::endl;
	std::cout << "nan.back(): " << nan.back() << std::endl;

	//Erase, size, begin, cbegin, end
	characters.erase(characters.begin() + 2);
	std::cout << "After characters.erase(characters.begin() + 2) characters holds: ";
	characters.print_me();

	characters2.erase(characters2.cbegin());
	std::cout << "After characters2.erase(characters2.cbegin()) characters2 holds: ";
	characters2.print_me();
	
	characters3.erase(characters3.begin(), characters3.end());
	if (characters3.empty())
		std::cout << "After characters3.erase(characters3.begin(), characters3.end()) vector is empty" << std::endl;
	else {
		std::cout << "After characters3.erase(characters3.begin(), characters3.end()) vector holds: ";
		for (auto& el : characters3) std::cout << el;
		std::cout << std::endl;
		std::cout << "size is " << characters3.size() << std::endl;
		if (characters3.size() == 1)
			std::cout << "That's right!" << std::endl;
		else
			std::cout << "It must be 1" << std::endl;
	}

	//Clear, empry, operator= with empty DynArray
	characters4.clear();
	if (characters4.empty())
		std::cout << "After characters4.clear() vector is empty" << std::endl;
	else {
		std::cout << "FAIL! After characters4.clear() vector isn't empty" << std::endl;
		for (auto& el : characters4) std::cout << el;
		std::cout << std::endl;
		std::cout << "size is " << characters4.size() << std::endl;
	}

	characters5 = characters4;
	if (characters5.empty())
		std::cout << "Char5 empty! Thats right" << std::endl;

	//capacity, shrink_to_fit, resize
	std::cout << "characters2 holds: ";
	characters2.print_me();
	std::cout << "char2 size: " << characters2.size() << " and capacity: " << characters2.capacity() << std::endl;
	characters2.shrink_to_fit();
	std::cout << "After characters2.shrink_to_fit() characters2 holds: ";
	characters2.print_me();
	std::cout << "char2 size: " << characters2.size() << " and capacity: " << characters2.capacity() << std::endl;
	characters2.resize(10, 'z');
	std::cout << "After characters2.resize(10) characters2 holds: ";
	characters2.print_me();
	std::cout << "char2 size: " << characters2.size() << " and capacity: " << characters2.capacity() << std::endl;

	BasicString a("some_string");
	std::cout << a << std::endl;
	std::cout << a.find("e") << std::endl;
	std::string insert_str = "_new_";
	//BasicString b(insert_str);
	std::cout << a << std::endl;

	////
	BasicString a1;
	std::cout << a1 << std::endl;
	BasicString a2({'a', 'b'});
	std::cout << a2 << std::endl;
	BasicString a3("abc");
	std::cout << a3 << std::endl;
	std::string for_constructor = "abcd";
	BasicString a4(for_constructor);
	std::cout << a4 << std::endl;
	BasicString a5("abcde", 5);
	std::cout << a5 << std::endl;
	BasicString a6(6, 'a');
	std::cout << a6 << std::endl;
	BasicString a7(a6);
	std::cout << a7 << std::endl;
	a7.append("asda");
	std::cout << a7 << std::endl;
	///////

	WideString b;
	WideString b1(L"абв");
	b1.insert(1, for_constructor, 3);
	std::wcout << b1 << std::endl;
	std::wcout << b1.substr(3) << std::endl;
	b1.erase(b1.begin(), b1.end());
	std::wcout << b1 << std::endl;

	//////////////
	WideString b2(L"Для конструктора");
	BasicString constr_test(b2);
	std::cout << constr_test << std::endl;

	WideString b3(constr_test);
	std::wcout << b3 << std::endl;

	b3.insert(2, L"_вставил_", 9);
	std::wcout << b3 << std::endl;

	constr_test = b3;
	std::cout << constr_test << std::endl;

	constr_test.insert(9, 5, 'z');
	std::cout << constr_test << std::endl;
	b3 = constr_test;
	std::wcout << b3 << std::endl;

	return 0;
}