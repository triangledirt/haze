#ifndef bnet_butterflyNet_H
#define bnet_butterflyNet_H


#include "bnet.H"
#include "eventStream.H"


namespace z {
  namespace bnet {


    struct outputInfo {
      int op;
      int inA;
      int inB;
    };


    class butterflyNet {
    public:
      float best;
      vector<eventStream> eventStreams;
      vector< vector<outputInfo> > outputNfo;

      butterflyNet();
      ~butterflyNet();
      void createOutputInfo(int level_);
      bool evaluate(int level_, int output_, int event_);
      float getCorrectness(int level_, int output_);
      string getOperatorName(int op_);
      void go();
      bool operate(int operator_, bool inA_, bool inB_);
      void registerInitialEventStream(eventStream stream_);
      void showEventStream(int level_);
      void showNet(int level_, int output_);
      string showNet_(int level_, int output_);
    };


  }
}


#endif
