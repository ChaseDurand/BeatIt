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
}

void Metronome::countSamples (int bufferSize)
{
    mTotalSamples+=bufferSize;
    DBG(mTotalSamples);
}

void Metronome::reset()
{
    mTotalSamples = 0;
}
