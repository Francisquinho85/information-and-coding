#include <iostream>
#include <math.h>
#include "../Ex3/AudioFile.h"

using namespace std;

int main(int argc, char ** argv)
{
	AudioFile<double> originalAudio,reducedAudio;
	originalAudio.load(argv[1]);
    reducedAudio.load(argv[2]);
    int maxErrorPerSample = 0;
    int tmp,originalSample,reducedSample;
    int numChannels = originalAudio.getNumChannels();
    int numSamples = originalAudio.getNumSamplesPerChannel();
    double snr = 0;

    for(int c = 0; c < numChannels; c++)
    {
        for(int i = 0; i < numSamples; i++)
        {
            originalSample = originalAudio.samples[c][i] * 32768;
            reducedSample = reducedAudio.samples[c][i] * 32768;
            tmp = abs(originalSample - reducedSample);
            
            if(tmp > maxErrorPerSample){
                maxErrorPerSample = tmp;
            }
        }
    }
    cout << "MAX ERROR: " << maxErrorPerSample << endl;
}
