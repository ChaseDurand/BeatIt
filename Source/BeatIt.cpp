/*
  ==============================================================================

    BeatIt.cpp
    Created: 4 Feb 2021 6:05:55pm
    Author:  Chase Durand

  ==============================================================================
*/

#include "BeatIt.h"

void Metronome::prepareToPlay(double sampleRate)
{
    mSampleRate = sampleRate;
    mInterval = 60.0 / mBpm * mSampleRate;
    HighResolutionTimer::startTimer(60);
}

void Metronome::countSamples (int bufferSize)
{
    mTotalSamples+=bufferSize;
    
    mSamplesRemaining = mTotalSamples % mInterval;
    
    DBG("Samples Remaining: " << mSamplesRemaining);
    DBG("Beat Interval: " << mInterval);
    
    if ((mSamplesRemaining + bufferSize) >= mInterval)
    {
        DBG("CLICK");
        DBG("Total Samples: " << mTotalSamples);
    }
    
    DBG(mTotalSamples);
}

void Metronome::reset()
{
    mTotalSamples = 0;
}

void Metronome::hiResTimerCallback()
{
    mInterval = 60.0 / mBpm * mSampleRate;
}
