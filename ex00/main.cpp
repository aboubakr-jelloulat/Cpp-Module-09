#include <iostream>



int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: ./btc [file.txt]" << std::endl; 
        return 0;
    }

    (void) av;

    return 0;
}
