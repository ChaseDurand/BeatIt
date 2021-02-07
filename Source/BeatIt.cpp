/*
  ==============================================================================

    BeatIt.cpp
    Created: 4 Feb 2021 6:05:55pm
    Author:  Chase Durand

  ==============================================================================
*/

#include "BeatIt.h"

Metronome::Metronome()
{
    mFormatManager.registerBasicFormats();
    
    File myFile { File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory)};
    auto mySamples = myFile.findChildFiles(File::TypesOfFileToFind::findFiles, false, "*.wav"); // Grabs the first wav file from the desktop lol
    
    jassert(mySamples[0].exists());
    
    auto formatReader = mFormatManager.createReaderFor(mySamples[0]);
    
    pMetronomeSample.reset(new AudioFormatReaderSource (formatReader, true));
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
}

void Metronome::prepareToPlay(int samplesPerBlock, double sampleRate)
{
    mSampleRate = sampleRate;
    mUpdateInterval = 60.0 / mBpm * mSampleRate;
    
    if (pMetronomeSample != nullptr){
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
        DBG("File loaded");
    }
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    const auto bufferSize = bufferToFill.numSamples;
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mUpdateInterval;
    
    if ((mSamplesRemaining + bufferSize) >= mUpdateInterval)
    {
        const auto timeToStartPlaying = mUpdateInterval - mSamplesRemaining;
        pMetronomeSample->setNextReadPosition(0);
        
        for (auto sample = 0; sample < bufferSize; sample++)
        {
            if (sample == timeToStartPlaying)
            {
                pMetronomeSample->getNextAudioBlock(bufferToFill);
            }

        }
        
    }
    if (pMetronomeSample->getNextReadPosition() != 0)
    {
        pMetronomeSample->getNextAudioBlock(bufferToFill);
    }
    
}

void Metronome::reset()
{
    mTotalSamples = 0;
}
