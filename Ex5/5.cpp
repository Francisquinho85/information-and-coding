#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <vector>

int main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]); 
    std::ofstream ofs("out.txt"); 
    std::string s; 
    std:: map<char, int> mymap;
    double d;

    while (std::getline(ifs,s)){
        for (int i = 0; i < s.size(); i++){
            if (!std::isalpha(s[i])){
                continue;
            }
            if ( mymap.find(s[i]) == mymap.end() ){
                mymap[s[i]] = 1; 
            }else{
                mymap[s[i]]++; 
            }
        }
    }

    // show content into file:
    for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
        ofs << it->first << "=>" << it->second << '\n';
    ifs.close();
    ofs.close();

    return 0;

}
// Examples:
// usage: ./5 thePictureOfDorianGray.txt
// or
// usage: ./5 lusiadas.txt
// Followed by:
// usage: python3 hist.py


