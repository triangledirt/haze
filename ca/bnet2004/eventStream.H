#ifndef bnet_eventStream_H
#define bnet_eventStream_H


#include "bnet.H"
#include "event.H"


namespace z {
  namespace bnet {


    struct weightIndexPair {
      int weight;
      int index;
    };


    bool operator<(const weightIndexPair& a_, const weightIndexPair& b_);


    class eventStream {
    public:
      vector<event> events;
      vector<int> weights;
      vector<int> picks;

      eventStream();
      eventStream(const eventStream& stream_);
      ~eventStream();
      void append(event event_);
      void calcPicks();
      void calcWeights();
      eventStream& operator=(const eventStream& stream_);
    };


  }
}


#endif
