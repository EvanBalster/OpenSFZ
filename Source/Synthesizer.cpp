//
//  Synthesizer.cpp
//  OpenSFZ
//
//  Created by David Wallin on 4/22/13.
//  Copyright (c) 2013 David Wallin. All rights reserved.
//

#include "Synthesizer.h"

SynthesiserSound::SynthesiserSound()
{
}

SynthesiserSound::~SynthesiserSound()
{
}

/////////////////////////////////////////////////////////////////////////////////////

SynthesizerVoice::SynthesizerVoice()
{
    sampleRate = 44100.0f;
    
    currentlyPlayingNote = -1;
    noteOnTime = 0;
    currentlyPlayingSound = 0;
    keyIsDown = false; // the voice may still be playing when the key is not down (i.e. sustain pedal)
    sostenutoPedalDown = false;
}

void SynthesizerVoice::setCurrentPlaybackSampleRate (double newRate)
{
	sampleRate = newRate;
    
}

void SynthesizerVoice::clearCurrentNote()
{
    currentlyPlayingNote = -1;
    currentlyPlayingSound = nullptr;
}


/////////////////////////////////////////////////////////////////////////////////////

Synthesizer::Synthesizer()
{
	sampleRate = 44100.0f;
}

Synthesizer::~Synthesizer()
{
	clearVoices();
	clearSounds();
}

void Synthesizer::addVoice (SynthesizerVoice* newVoice)
{
	voices.push_back(newVoice);
}

void Synthesizer::clearVoices()
{
	for(int i=0; i<voices.size(); i++)
		delete voices[i];

	voices.clear();
}
	
SynthesizerVoice* getVoice (int index) const
{
	if(index < 0 || index >= voices.size())
		return NULL;

	return voices[i];
}

    
void Synthesizer::clearSounds()
{
	for(int i=0; i<sounds.size(); i++)
		delete sounds[i];

	voices.clear();
}

void Synthesizer::noteOn (int midiChannel,
                        int midiNoteNumber,
                        float velocity)
{	
	for(int i=0; i<sounds.size(); i++)
	{
		SynthesizerSound *sound = sounds[i];


            // If hitting a note that's still ringing, stop it first (it could be
            // still playing because of the sustain or sostenuto pedal).
            for (int j = 0; j<voices.size(); j++)
            {
                SynthesiserVoice* const voice = voices.getUnchecked (j);

                if (voice->getCurrentlyPlayingNote() == midiNoteNumber
                     && voice->isPlayingChannel (midiChannel))
                    stopVoice (voice, true);
            }

            startVoice (findFreeVoice (sound, shouldStealNotes),
                        sound, midiChannel, midiNoteNumber, velocity);
	}

}
    
void Synthesizer::noteOff (int midiChannel,
                        int midiNoteNumber,
                        bool allowTailOff)
{
	// not worth it since we override this
}
    
void Synthesizer::allNotesOff (int midiChannel,
                            bool allowTailOff)
{

    for (int i = 0; i<voices.size(); )
    {
        SynthesiserVoice* const voice = voices[i];

        if (midiChannel <= 0 || voice->isPlayingChannel (midiChannel))
            voice->stopNote (allowTailOff);
    }
}
    
void Synthesizer::handlePitchWheel (int midiChannel,
                                int wheelValue)
{

    for (int i=0; i<voices.size(); i++)
    {
        SynthesiserVoice* const voice = voices[i];

        if (midiChannel <= 0 || voice->isPlayingChannel (midiChannel))
            voice->pitchWheelMoved (wheelValue);
    }
}

void Synthesizer::handleController (int midiChannel,
                                int controllerNumber,
                                int controllerValue)
{
    switch (controllerNumber)
    {
        //case 0x40:  handleSustainPedal   (midiChannel, controllerValue >= 64); break;
        //case 0x42:  handleSostenutoPedal (midiChannel, controllerValue >= 64); break;
        //case 0x43:  handleSoftPedal      (midiChannel, controllerValue >= 64); break;
        default:    break;
    }


    for (int i=0; i<voices.size(); i++)
    {
        SynthesiserVoice* const voice = voices[i];

        if (midiChannel <= 0 || voice->isPlayingChannel (midiChannel))
            voice->controllerMoved (controllerNumber, controllerValue);
    }
}

void Synthesizer::setCurrentPlaybackSampleRate (double sampleRate_)
{
	sampleRate = sampleRate_;
}

SynthesizerVoice* Synthesizer::findFreeVoice (SynthesizerSound* soundToPlay,
                                            const bool stealIfNoneAvailable) const
{
	for(int i=0; i<voices.size(); i++)
	{
		if(voices[i]->getCurrentlyPlayingNote() == -1)
		{
			return voices[i];
		}
	}
    if (stealIfNoneAvailable)
    {
		SynthesizerVoice *oldest = NULL;
		for(int i=0; i<voices.size(); i++)
		{
            SynthesiserVoice* const voice = voices[i];
            
            if(oldest == nullptr || oldest->noteOnTime < voice->noteOnTime)
                oldest = voice;
		}

		if(oldest)
			return oldest;
	}

	return NULL;
}

void Synthesizer::startVoice (SynthesizerVoice* voice,
                    SynthesizerSound* sound,
                    int midiChannel,
                    int midiNoteNumber,
                    float velocity)
{

}
    
void Synthesizer::renderNextBlock (SFZAudioBuffer& outputAudio,
                        int startSample,
                        int numSamples)
{

}