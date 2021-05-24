/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PMFProject0AudioProcessorEditor::PMFProject0AudioProcessorEditor (PMFProject0AudioProcessor& p)
    // a reference to our processor initialises &audioProcessor with a reference to our processor
    : AudioProcessorEditor (&p),
      audioProcessor (p),
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

PMFProject0AudioProcessorEditor::~PMFProject0AudioProcessorEditor()
{
/*    audioProcessor.shouldPlaySound->beginChangeGesture();
    audioProcessor.shouldPlaySound->setValueNotifyingHost(false);
    audioProcessor.shouldPlaySound->endChangeGesture();  */  
    PMFProject0AudioProcessor::UpdateAutomatableParameter(audioProcessor.shouldPlaySound, false);
}


//==============================================================================
void PMFProject0AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PMFProject0AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void PMFProject0AudioProcessorEditor::mouseUp(const juce::MouseEvent& e)
{
    //audioProcessor.shouldPlaySound->beginChangeGesture();
    //audioProcessor.shouldPlaySound->setValueNotifyingHost(!audioProcessor.shouldPlaySound->get());
    //audioProcessor.shouldPlaySound->endChangeGesture();
    PMFProject0AudioProcessor::UpdateAutomatableParameter(audioProcessor.shouldPlaySound, !audioProcessor.shouldPlaySound->get());
}

void PMFProject0AudioProcessorEditor::mouseDown(const juce::MouseEvent& e)
{
    /*audioProcessor.shouldPlaySound = true;*/
}
