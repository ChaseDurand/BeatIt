#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    mPlayButton.setRadioGroupId(1);
    mPlayButton.setToggleState(false, NotificationType::dontSendNotification);
    mPlayButton.onClick = [this]() {play();} ;
    addAndMakeVisible(mPlayButton);
    
    mStopButton.setRadioGroupId(1);
    mPlayButton.setToggleState(true, NotificationType::dontSendNotification);
    mStopButton.onClick = [this]() { stop(); };
    addAndMakeVisible(mStopButton);
    
    setSize (200, 200);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::play()
{
    mPlayState = PlayState::Playing;
}

void MainComponent::stop()
{
    mPlayState = PlayState::Stopped;
    mMetronome.reset();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mMetronome.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    bufferToFill.clearActiveBufferRegion();
    
    if (mPlayState == PlayState::Playing)
    {
        mMetronome.getNextAudioBlock(bufferToFill);
    }
    else
    {
        
    }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    Rectangle<int> bounds = getLocalBounds();
    
    FlexBox flexBox;
    flexBox.items.add(FlexItem(100, 100, mPlayButton));
    flexBox.items.add(FlexItem(100, 100, mStopButton));
    flexBox.performLayout(bounds);
    
}
