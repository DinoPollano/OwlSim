#ifndef __PatchRegistry_h__
#define __PatchRegistry_h__
#include <map>
#include <string>

#include "StompBox.h"
#include "../JuceLibraryCode/JuceHeader.h"

class PatchRegistry {
  typedef Patch* PatchCreator(); // function pointer to create Patch
public:
  PatchRegistry();
  StringArray getNames();
  Patch* create(const std::string& name);
  void registerPatch(const std::string& name, PatchCreator creator);
  template<class T> struct Register {
    static Patch* construct() {
      return new T();
    };
    static PatchCreator* init_creator(std::string& name) {
      return getCreators()[name] = create;
    }
    static PatchCreator* creator;
  };
private:
  typedef std::map<std::string, PatchCreator*> Creators; // map from id to creator
  static Creators& getCreators() { 
    static Creators creators; 
    return creators; 
  }
};

/* #define REGISTER_PATCH(T, STR) template<> PatchRegistry::PatchCreator* PatchRegistry::Register<T>::creator = PatchRegistry::Register<T>::init_creator(STR) */

#endif // __PatchRegistry_h__
