#ifndef bnet_event_H
#define bnet_event_H


#include "bnet.H"


namespace z {
  namespace bnet {


    class event {
    public:
      // attrib[0] is the decision attribute
      vector<bool> attribs;

      event();
      event(const event& event_);
      event(bool a_, bool b_, bool c_, bool d_, bool e_, bool f_, bool g_);
      ~event();
      event& operator=(const event& event_);
    };


  }
}


#endif
