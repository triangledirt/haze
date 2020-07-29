#include "event.H"


namespace z {
  namespace bnet {


    event::event() {}


    event::event(const event& event_) {
      attribs.resize(0);
      for (int x = 0; x < event_.attribs.size(); x++) {
	attribs.insert(attribs.end(), event_.attribs[x]);
      }
    }


    event::event(bool a_, bool b_, bool c_, bool d_, bool e_, bool f_,
		 bool g_) {
      attribs.resize(7);
      attribs[0] = a_;
      attribs[1] = b_;
      attribs[2] = c_;
      attribs[3] = d_;
      attribs[4] = e_;
      attribs[5] = f_;
      attribs[6] = g_;
    }


    event::~event() {}


    event& event::operator=(const event& event_) {
      attribs.resize(0);
      for (int x = 0; x < event_.attribs.size(); x++) {
	attribs.insert(attribs.end(), event_.attribs[x]);
      }
    }


  }
}
