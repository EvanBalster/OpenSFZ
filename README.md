OpenSFZ
=======

An Open SFZ player & SF2 (Sampler) based on SFZero, without the Juce dependency

Note, this is still in development and only has minimal functionality right now. 
Contributions to handle additional SFZ opcodes, more file formats, better resampling etc, are welcome.

Documentation and examples are coming soon.

License
=======

This project is available under the MIT license. You may use it in commercial projects.

Simple Example
==============



    #include "OpenSFZ.h"
    
    ....
    // initialization:
    
        synth = new SFZSynth();
        
        SFZSound *testSound = new SFZSound(std::string("/Users/dwallin/Downloads/FM-House-Bass/FM-House-Bass.sfz"));
    
        synth->addSound(testSound);

        testSound->loadRegions();
        testSound->loadSamples();

        testSound->dump();    // print out debug info
        
        synth->setCurrentPlaybackSampleRate(SongInfo::getSampleRate());
    
  
    // just handle midi events and call the appropriate functions on the SFZSynth class. 
    // OpenSFZ doesn't have any midi specific code or classes. This is purely for example purposs.
    
        if(e->eventType == Event::EVENT_NOTEON)
        {
            synth->noteOn(1, e->iData[0], e->rData[0]);
        } else if(e->eventType == Event::EVENT_NOTEOFF)
        {
            synth->noteOff(1, e->iData[0], true);
        } else if(e->eventType == Event::EVENT_ALLNOTESOFF)
        {
            synth->allNotesOff(1, false);
        } else if(e->eventType == Event::EVENT_CC)
        {
            if(e->iData[0] == 121 || e->iData[0] == 123)
            {
                synth->allNotesOff(1, true);
            }
        }
    
    // Audio processing. Call something like this in your audio processing callback loop: 
        // Note: audio buffers should be filled with zeros first
    
        SFZAudioBuffer buffer((int)numSamples,
                              audioOutLeftChannelPointer,
                              audioOutRightChannelPointer);
        
        synth->renderNextBlock(buffer, 0, (int)numSamples);
        
    // that's it
