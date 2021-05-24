/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/

/*
 TODO: 
 Click anywhere on the window to play a note. 
 If you click and drag, it'll change the pitch of the note.
 save plugin state when exiting DAW
 load plugin state whrn loading a session
*/
class PMFProject0AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PMFProject0AudioProcessor();
    ~PMFProject0AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    // Audio parameter objects are the objects you see when you go to edit automation in the DAW. What your presets save and load
    juce::AudioParameterBool* shouldPlaySound = nullptr; // = false;

    static void UpdateAutomatableParameter(juce::RangedAudioParameter*, float value);

private:
    juce::Random r;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PMFProject0AudioProcessor)
};
