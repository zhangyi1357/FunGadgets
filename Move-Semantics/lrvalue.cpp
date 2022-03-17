#include <iostream>
#include <string>

int GetValue() {
    return 5;
}

int& GetLValue() {
    static int value = 10;
    return value;
}

void SetValue(int value) {}

void SetLValue(int& value) {}

void SetConstValue(const int& value) {}

void PrintName(const std::string& name) {
    std::cout << "[lvalue] " << name << std::endl;
}
void PrintName(const std::string&& name) {
    std::cout << "[rvalue] " << name << std::endl;
}


int main(int argc, const char* argv[]) {
    // basic part
    int i = 10; // rvalue can be assigned to lvalue
    // 10 = i;  // but reverse can't

    int a = i;  // lvalue can be assigned to lvalue

    // reference
    // int& b = 5;  // can't reference rvalue
    int& c = i;     // allowed

    // return value of function
    i = GetValue();     // return value of function can be rvalue
    // GetValue() = i;  // you can't assign any value to rvalue

    i = GetLValue();    // return value of function can also be lvalue
    GetLValue() = i;    // lvalue can be assigned

    // parameter of function
    SetValue(i);        // lvalue can be assigned
    SetValue(5);        // rvalue can be assigned
    SetLValue(i);       // lvalue can be used for &
    // SetLValue(5);    // rvalue can't

    // const reference
    const int& d = 5;
    SetConstValue(i);   // accept lvalue
    SetConstValue(5);   // accept rvalue

    std::string firstName = "Yan";
    std::string lastName = "Chernikov";

    std::string fullName = firstName + lastName;

    PrintName(fullName);
    PrintName(firstName + lastName);

    return 0;
}