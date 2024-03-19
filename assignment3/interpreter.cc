#include <iostream>
#include <fstream>
#include <string>
#include "StackMachine.h"

using namespace std;

int main(int argc, char *argv[])
{
    string filename;

    if (argc == 1)
    {
        filename = "bytecode.class"; // Default filename
    }
    else if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    StackMachine SM;
    SM.init(filename);

    // cout << "Executing..." << endl;
    SM.execute();

    return 0;
}