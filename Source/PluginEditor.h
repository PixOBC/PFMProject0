/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PMFProject0AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public: 
    PMFProject0AudioProcessorEditor (PMFProject0AudioProcessor&);
    ~PMFProject0AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it in Processor.h.
    PMFProject0AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PMFProject0AudioProcessorEditor)
};
