#include <iostream>
#include "AudioFile.h"
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <cmath>

int main(int argc, char *argv[])
{

    AudioFile<double> audioIn;
    
    audioIn.load(argv[1]);

    int channels = audioIn.getNumChannels();
    int numSamplesPerChannel = audioIn.getNumSamplesPerChannel();
    
    std:: map<int, int> mymapC1;
    std:: map<int, int> mymapC2;
    int d;
    for (int i=-32768; i < 32768;i++){
        mymapC1[i]=0;
        mymapC2[i]=0;
    }

    for (int n = 0; n < numSamplesPerChannel; n++){
        
        // -2¹⁵ to 2¹⁵
        d = audioIn.samples[0][n] * 32768;
        ;
        if (mymapC1.find(d) == mymapC1.end() ){
            mymapC1[d] = 1;
        }
        else{
            mymapC1[d]++;
        }   
    }
    for (int n = 0; n < numSamplesPerChannel; n++){
        
        // -2¹⁵ to 2¹⁵
        d = audioIn.samples[1][n] * 32768;
        ;
        if (mymapC2.find(d) == mymapC2.end() ){
            mymapC2[d] = 1;
        }
        else{
            mymapC2[d]++;
        }   
    }
    

    double probC1[65536];
    double probC2[65536];
    for (int i=0; i < 65536;i++){
        if (mymapC1[i-3278] != 0)
            probC1[i] = mymapC1[i-3278]*1.0/numSamplesPerChannel;
        else
            probC1[i] = 0;
        if (mymapC2[i-3278] != 0)
            probC2[i] = mymapC2[i-3278]*1.0/numSamplesPerChannel;
        else
            probC2[i] = 0;
    }
     
    double entropyC1 = 0;
    double entropyC2 = 0;
    for (int i=0;i<65536;i++){
        if (probC1[i] != 0)
            entropyC1 = entropyC1 + (probC1[i]*log(probC1[i]/log(2)));
        if (probC2[i] != 0)
            entropyC2 = entropyC2 + (probC2[i]*log(probC2[i]/log(2)));
    }
    std::cout << "The channel 1 entropy of " << argv[1] 
      << " is : " << -entropyC1 << std::endl ;
    
    std::cout << "The channel 2 entropy of " << argv[1] 
      << " is : " << -entropyC2 << std::endl ;

    std:: ofstream ofsC1("outC1.txt");
    std:: ofstream ofsC2("outC2.txt");
    // show content:
    for (std::map<int,int>::iterator it=mymapC1.begin(); it!=mymapC1.end(); ++it)
        ofsC1 << it->first << "=>" << it->second << '\n';
    ofsC1.close();

    for (std::map<int,int>::iterator it=mymapC2.begin(); it!=mymapC2.end(); ++it)
        ofsC2 << it->first << "=>" << it->second << '\n';
    ofsC2.close();

    return 0;

}