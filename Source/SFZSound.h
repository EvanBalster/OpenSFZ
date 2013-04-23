#ifndef SFZSound_h
#define SFZSound_h

#include "OpenSFZ.h"
#include "SFZRegion.h"

class SFZSample;


class SFZSound : public SynthesizerSound {
	public:
		SFZSound(const File& file);
		~SFZSound();

		bool	appliesToNote(const int midiNoteNumber);
		bool	appliesToChannel(const int midiChannel);

		void	addRegion(SFZRegion* region); 	// Takes ownership of the region.
		SFZSample*	addSample(String path, String defaultPath = String::empty);
		void	addError(const String& message);
		void	addUnsupportedOpcode(const std::string& opcode);

		virtual void	loadRegions();
		virtual void	loadSamples(
			AudioFormatManager* formatManager,
			double* progressVar = NULL, Thread* thread = NULL);

		SFZRegion*	getRegionFor(
			int note, int velocity, SFZRegion::Trigger trigger = SFZRegion::attack);
		int	getNumRegions();
		SFZRegion*	regionAt(int index);

		String	getErrorsString();

		virtual int	numSubsounds();
		virtual String	subsoundName(int whichSubsound);
		virtual void	useSubsound(int whichSubsound);
		virtual int 	selectedSubsound();

		void	dump();

	protected:
		File 	file;
		Array<SFZRegion*>	regions;
		HashMap<String, SFZSample*>	samples;
		StringArray      	errors;
		HashMap<String, String>	unsupportedOpcodes;
	};



#endif 	// SFZSound_h

