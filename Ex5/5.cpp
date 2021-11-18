#include <iostream>
#include <fstream>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>

double log2( double number ) {
   return log( number ) / log( 2 ) ;
}

int main(int argc, char *argv[])
{
    std::ifstream ifs(argv[1]); 
    std::ofstream ofs("out.txt"); 
    std::string s; 
    std:: map<char, int> mymap;
    std::vector<int> value;
    double d;
    int numlen = 0;

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
    for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
        ofs << it->first << "=>" << it->second << '\n';
        numlen= numlen + (it->second);
    }
        
    ifs.close();
    ofs.close();
    
    double infocontent = 0 ;
    for ( std::pair<char , int> p : mymap ) {
      double freq = static_cast<double>( p.second ) / numlen ;
      infocontent -= freq * log2( freq ) ;
    }

    std::cout << "The information content of " << argv[1] 
      << " is " << infocontent << std::endl ;
    
    return 0;

}
// Examples:
// usage: ./5 thePictureOfDorianGray.txt
// or
// usage: ./5 lusiadas.txt
// Followed by:
// usage: python3 hist.py


