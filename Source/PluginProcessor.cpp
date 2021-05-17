/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PMFProject0AudioProcessor::PMFProject0AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
                        //shouldPlaySound("ShouldPlaySoundParam", "shouldPlaySound", false)

{   // let the host know that you've changed a parameter so it can be recorded as automation. Also note that you've changed the plugin settings so the DAW can ask you wish to save your changes when you quit. V. IMPORTANT function
    // For this to work, we need to register the parameter with the plugin
    //shouldPlaySound.setValueNotifyingHost();
    // 1. Declare shouldPlaySound as pointer to AudioParameterBool in class
    // 2. Implement, allocating memory on the heap using new
    // 3. Pass in arguments using parameters from the APBool constructor
    // 4. Use addParameter to add a parameter to the processor. See above. We register with the plugin
    shouldPlaySound = new juce::AudioParameterBool("ShouldPlaySoundParam", "shouldPlaySound", false);
    addParameter(shouldPlaySound);
}

PMFProject0AudioProcessor::~PMFProject0AudioProcessor()
{
}

//==============================================================================
const juce::String PMFProject0AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PMFProject0AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PMFProject0AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PMFProject0AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PMFProject0AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PMFProject0AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PMFProject0AudioProcessor::getCurrentProgram()
{
    return 0;
}

void PMFProject0AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PMFProject0AudioProcessor::getProgramName (int index)
{
    return {};
}

void PMFProject0AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PMFProject0AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PMFProject0AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PMFProject0AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PMFProject0AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            // get() returns the parameters current boolean value
            if (shouldPlaySound->get())
            {
                // implicit 'this' for r member variable
                buffer.setSample(channel, i, r.nextFloat());
            }
            else
            {
                buffer.setSample(channel, i, 0);                
            }
        }
    }
}

//==============================================================================
bool PMFProject0AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}


// Pointer lecture 28:06 below returns a pointer
// Ch3 6 this,pointers,references,new conclusion - 
// See that it's the AudioProcessor who creates the Editor. Whatever is requested from the host, the AudioProcessor is the one who creates it.
juce::AudioProcessorEditor* PMFProject0AudioProcessor::createEditor()
{
    // this is pointing to the active instance of the plugin processor. this is dereferenced, giving is the actual instance, which is passed to the plugin editor constructor as a reference

    return new PMFProject0AudioProcessorEditor (*this);
}

//==============================================================================
void PMFProject0AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PMFProject0AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PMFProject0AudioProcessor();
}
