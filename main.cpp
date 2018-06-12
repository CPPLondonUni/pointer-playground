#include <iostream>
#include <string>

//Welcome to the pointer playground. Run the program and see what it prints for each function.

//Try playing with the arguments to change the behaviour.

//takes a copy, basically does nothing.
void TakeACopy(std::string s) {
	s = "TakeACopy";
}

//takes a reference, caller will see this.
void TakeAReference(std::string& s) {
	s = "TakeAReference";
}

//takes a pointer, caller will also see this.
void TakeAPointer(std::string* s) {
	if (!s)
		std::cout << "oops, no pointer passed\n";
	else
		*s = "TakeAPointer";
}

//takes a reference to a pointer. helpfully fills it in if you don't give it one
//(NB: bad practice for real projects since it can cause ownership confusion and memory leaks!)
void TakeAPointerRef(std::string*& s) {
	if (!s) {
		static std::string defaultStr{"TakeAPointerRef - default"}; //created ONCE no matter how many times you call this function due to "static" keyword.
		s = &defaultStr; //s gets the address of defaultStr.
	} else
		*s = "TakeAPointerRef"; //*s could be substituted with s[0] as well but don't go higher unless you passed a real array!
}

//takes a pointer to a pointer. Basically the same as the previous, but this is what
//we would have to use in good (bad) old C. Though we wouldn't have std::string in C actually.
void TakeAPointerPointer(std::string** s) {
	if (!*s) {
		static std::string defaultStr{"TakeAPointerPointer - default"}; //also created ONCE.
		*s = &defaultStr; //since we have a std::string**, the result of *s is a std:string*&
	} else
		**s = "TakeAPointerPointer";
}

int main() {
	std::string mainStr{"String In Main"};

	std::cout << "Calling TakeACopy With mainStr result: ";
	TakeACopy(mainStr);
	std::cout << mainStr << '\n';

	std::cout << "Calling TakeAReference with mainStr result: ";
	TakeAReference(mainStr);
	std::cout << mainStr << '\n';

	std::cout << "Calling TakeAPointer with &mainStr result: ";
	TakeAPointer(&mainStr);
	std::cout << mainStr << '\n';

	std::cout << "Calling TakeAPointer with nullptr result: ";
	TakeAPointer(nullptr); //we know this prints an error for us.
	
	std::cout << "Calling TakeAPointerRef with mainStrPtr result: ";
	std::string* mainStrPtr = &mainStr;
	TakeAPointerRef(mainStrPtr);
	std::cout << *mainStrPtr << '\n'; //What if you print mainStr? Will it be the same output? Why?

	std::cout << "Calling TakeAPointerRef with an empty pointer result: ";
	std::string* emptyPtr = nullptr;
	TakeAPointerRef(emptyPtr);
	std::cout << *emptyPtr << '\n';

	std::cout << "Calling TakeAPointerPointer with a pointer to a pointer to mainStr result: ";
	mainStrPtr = &mainStr;
	TakeAPointerPointer(&mainStrPtr);
	std::cout << *mainStrPtr << '\n'; //You could also try using mainStr here, what do you think the result will be? why?

	std::cout << "Calling TakeAPointerPointer with &emptyPointer result: ";
	emptyPtr = nullptr;
	TakeAPointerPointer(&emptyPtr);
	std::cout << *emptyPtr << '\n';

	return 0;
}

