/*
  ==============================================================================

    BeatIt.h
    Created: 4 Feb 2021 6:05:55pm
    Author:  Chase Durand

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome : public HighResolutionTimer
{
public:
    void prepareToPlay (double sampleRate);
    void countSamples (int bufferSize);
    void reset();
    
    void hiResTimerCallback() override;
    
private:
    int mTotalSamples {0};
    double mSampleRate {0};
    int mInterval {0};
    int mBpm {90};
    int mSamplesRemaining;
};
