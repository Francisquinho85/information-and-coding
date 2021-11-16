#include <iostream>
#include "../Ex3/AudioFile.h"

using namespace std;

int main(int argc, char ** argv)
{
	AudioFile<double> audioIn,audioOut;
	audioIn.load(argv[1]);
	
	int numChannels = audioIn.getNumChannels();
	int numSamples = audioIn.getNumSamplesPerChannel();
	int sample;
	int bitsToDrop = atoi(argv[3]);
	audioOut.setNumChannels(numChannels);
	audioOut.setNumSamplesPerChannel(numSamples);

	for(int c = 0; c < numChannels; c++)
	{
		for(int i = 0; i < numSamples; i++)
		{
			sample = audioIn.samples[c][i] * 32768; // 2¹⁵ = 32768
			for(int j = 0; j < bitsToDrop; j++)
			{
				sample = sample / 2;
			}
			for(int k = 0; k < bitsToDrop; k++)
			{
				sample = sample * 2;
			}
			audioOut.samples[c][i] = sample;
		}
	}
	audioOut.save(argv[2], AudioFileFormat::Wave);
	
	//how to run example:
	// ./8 ../samples/sample.wav ../samples/out.wav 10
	// ./8 <audio file in> <audio file out> <number of bits to discard>
}
