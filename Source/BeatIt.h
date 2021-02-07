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
    Metronome();
    
    void prepareToPlay (int samplesPerBlock, double sampleRate);
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);
    void reset();
    
    void hiResTimerCallback() override;
    
private:
    int mTotalSamples {0};
    double mSampleRate {0};
    int mInterval {0};
    int mBpm {90};
    int mSamplesRemaining;
    
    AudioFormatManager mFormatManager;
    std::unique_ptr <AudioFormatReaderSource> pMetronomeSample {nullptr};
};
