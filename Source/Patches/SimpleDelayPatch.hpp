#ifndef __SimpleDelayPatch_hpp__
#define __SimpleDelayPatch_hpp__

#include "StompBox.h"
#include "CircularBuffer.hpp"

#define DELAY_BUFFER_LENGTH 16384 // must be a power of 2

class SimpleDelayPatch : public Patch {
private:
  CircularBuffer <float, DELAY_BUFFER_LENGTH> delayBuffer;
  float delayTime, feedback, wetDry;

public:
  SimpleDelayPatch(){
    registerParameter(PARAMETER_A, "Delay");
    registerParameter(PARAMETER_B, "Feedback");
    registerParameter(PARAMETER_C, "Dry/Wet");
  }
  void processAudio(AudioInputBuffer &input, AudioOutputBuffer &output) {        
    const int size = input.getSize();           // samples in block
    float* x = input.getSamples();              // arrays to hold sample data
    float y;
        
    delayTime = getParameterValue(PARAMETER_A); // delay time
    feedback  = getParameterValue(PARAMETER_B); // delay feedback
    wetDry    = getParameterValue(PARAMETER_C); // wet/dry balance
        
    float delaySamples = delayTime * (DELAY_BUFFER_LENGTH-1);        
    for (int n = 0; n < size; n++){             // for each sample            
      y = x[n] + feedback * delayBuffer.read(delaySamples);
      x[n] = wetDry * y + (1.f - wetDry) * x[n];  // crossfade for wet/dry balance
      delayBuffer.write(x[n]);
    }
    output.setSamples(x);
  }    
};

#endif   // __SimpleDelayPatch_hpp__
