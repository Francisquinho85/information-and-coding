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
    double snr;
    unsigned long noise,mse = 0;

    for(int c = 0; c < numChannels; c++)
    {
        for(int i = 0; i < numSamples; i++)
        {
            originalSample = originalAudio.samples[c][i] * 32768;
            reducedSample = reducedAudio.samples[c][i] * 32768;
            noise = pow(abs(originalSample - reducedSample),2);
            mse += noise;
        }
    }
    mse = mse / (numChannels * numSamples);
    snr = (20 * log10(32768)) - 10 * log10(mse);
    cout << "SNR: " << snr << " dB" << endl;
}
