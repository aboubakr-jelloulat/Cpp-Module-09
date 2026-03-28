#include <sstream>
#include <string>
#include <iostream>

int main() 
{


    std::string data = "2147483648 3.14 hello";
    std::istringstream iss(data);
    int i;
    double d;
    std::string s;
    iss >> i >> d >> s;
    std::cout << i << " " << d << " " << s << std::endl; // Output: 42 3.14 hello
    return 0;
}
