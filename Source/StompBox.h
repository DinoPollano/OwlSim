#ifndef __StompBox_h__
#define __StompBox_h__

#include <string>

class PatchProcessor;

enum PatchParameterId {
  PARAMETER_A,
  PARAMETER_B,
  PARAMETER_C,
  PARAMETER_D,
  PARAMETER_E
};

class AudioInputBuffer {
public:
  virtual ~AudioInputBuffer(){}
  virtual void getSamples(int from, int length, float* data) = 0;
  virtual float* getSamples() = 0;
  virtual int getSize() = 0;
};

class AudioOutputBuffer {
public:    
  virtual ~AudioOutputBuffer(){}
  virtual void setSamples(int from, int length, float* data) = 0;
  virtual void setSamples(float* data) = 0;
  virtual float* getSamples() = 0;
  virtual int getSize() = 0;
};

class Patch {
public:
  Patch();
  virtual ~Patch();
  void registerParameter(PatchParameterId pid, const std::string& name, const std::string& description = "");
  float getParameterValue(PatchParameterId pid);
  int getBlockSize();
  double getSampleRate();
  virtual void processAudio(AudioInputBuffer &input, AudioOutputBuffer &output) = 0;
private:
  PatchProcessor* processor;
//   PatchProcessor* getPatchProcessor();
};

#endif // __StompBox_h__
