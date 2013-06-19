#ifndef __GainPatch_hpp__
#define __GainPatch_hpp__

#include "StompBox.h"

class GainPatch : public Patch {
public:
  void processAudio(AudioInputBuffer &input, AudioOutputBuffer &output){
    int size = input.getSize();
    float gain = getParameterValue(PARAMETER_D);
    float* buf = input.getSamples();
    for(int i=0; i<size; ++i)
      buf[i] = gain*buf[i];
    output.setSamples(buf);
  }
};

#endif // __GainPatch_hpp__
