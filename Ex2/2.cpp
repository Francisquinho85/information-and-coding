#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[])
{
    ifstream    ifs(argv[1]);
    ofstream    ofs(argv[2]);

    ofs << ifs.rdbuf();
    ofs.close();
    return 0;
} 