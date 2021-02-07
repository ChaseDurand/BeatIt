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
    
    File myFile { File::getSpecialLocation(File::SpecialLocationType::userDesktopDirectory) };
    auto mySamples = myFile.findChildFiles(File::TypesOfFileToFind::findFiles, false, "click1.aif"); //Need to change path to custom sample path in Source folder
    
    jassert(mySamples[0].exists());
    
    auto formatReader = mFormatManager.createReaderFor(mySamples[0]);
    
    pMetronomeSample.reset(new AudioFormatReaderSource (formatReader, true));
}

void Metronome::prepareToPlay(int samplesPerBlock, double sampleRate)
{
    mSampleRate = sampleRate;
    mInterval = 60.0 / mBpm * mSampleRate;
    HighResolutionTimer::startTimer(60);
    
    if (pMetronomeSample != nullptr){
        pMetronomeSample->prepareToPlay(samplesPerBlock, sampleRate);
        DBG("File loaded");
    }
}

void Metronome::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    auto bufferSize = bufferToFill.numSamples;
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mInterval;
    
    DBG("Samples Remaining: " << mSamplesRemaining);
    DBG("Beat Interval: " << mInterval);
    
    if ((mSamplesRemaining + bufferSize) >= mInterval)
    {
        DBG("CLICK");
        DBG("Total Samples: " << mTotalSamples);
    }
    
    //pMetronomeSample->getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill));
}

void Metronome::reset()
{
    mTotalSamples = 0;
}

void Metronome::hiResTimerCallback()
{
    mInterval = 60.0 / mBpm * mSampleRate;
}
