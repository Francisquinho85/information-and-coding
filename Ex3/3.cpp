#include <iostream>
#include "AudioFile.h"

int main(int argc, char *argv[])
{

    AudioFile<double> audioIn, audioOut;
    
    audioIn.load(argv[1]);

    int channels = audioIn.getNumChannels();
    audioOut.setNumChannels(channels);

    int numSamplesPerChannel = audioIn.getNumSamplesPerChannel();
    audioOut.setNumSamplesPerChannel(numSamplesPerChannel);

    for (int c = 0; c < channels; c++){
        for (int n = 0; n < numSamplesPerChannel; n++){
            audioOut.samples[c][n] = audioIn.samples[c][n];
        }
    }

    audioIn.save(argv[2], AudioFileFormat::Wave);

    return 0;
} 