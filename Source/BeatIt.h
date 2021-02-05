/*
  ==============================================================================

    BeatIt.h
    Created: 4 Feb 2021 6:05:55pm
    Author:  Chase Durand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome
{
public:
    void prepareToPlay (double sampleRate);
    void countSamples (int bufferSize);
    void reset();
    
private:
    int mTotalSamples {0};
    double mSampleRate {0};
};
