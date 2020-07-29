#include "butterflyNet.H"


namespace z {
  namespace bnet {


    butterflyNet::butterflyNet() {
      best = 0;
    }


    butterflyNet::~butterflyNet() {}


    void butterflyNet::createOutputInfo(int level_) {
      int prevLevel(level_ - 1);
      int pickCount(eventStreams[prevLevel].picks.size());
      outputNfo.resize(level_ + 1);

      outputInfo emptyNfo;
      emptyNfo.op = 0;
      emptyNfo.inA = 0;
      emptyNfo.inB = 0;
      outputNfo[level_].insert(outputNfo[level_].end(), emptyNfo);

      cout << "new outputs are: ";
      for (int op = 0; op <= 2; op++) {
	for (int pickX = 1; pickX < pickCount; pickX++) {
	  for (int pickY = 1; pickY < pickCount; pickY++) {
	    if (pickX < pickY) {
	      outputInfo nfo;
	      nfo.op = op;
	      nfo.inA = eventStreams[prevLevel].picks[pickX];
	      nfo.inB = eventStreams[prevLevel].picks[pickY];
	      outputNfo[level_].insert(outputNfo[level_].end(), nfo);
	      cout << "(" << nfo.inA << " " << getOperatorName(nfo.op)
		   << " " << nfo.inB << ") ";
	    }
	  }
	}
      }
      cout << endl;
    }


    float butterflyNet::getCorrectness(int level_, int output_) {
      int rightCount(0);
      for (int x = 0; x < eventStreams[level_].events.size(); x++) {
	if (eventStreams[level_].events[x].attribs[0]
	    == evaluate(level_, output_, x)) {
	  rightCount++;
	}
      }
      return float(rightCount) / float(eventStreams[0].events.size());
    }


    bool butterflyNet::evaluate(int level_, int output_, int event_) {
      return eventStreams[level_].events[event_].attribs[output_];
//      bool r;
//      if (1 == level_) {
//	r = operate(outputNfo[level_][output_].op,
//		    eventStreams[0]
//		    .events[event_].attribs[outputNfo[level_][output_].inA],
//		    eventStreams[0]
//		    .events[event_].attribs[outputNfo[level_][output_].inB]);
//      } else {
//	r = operate(outputNfo[level_][output_].op,
//		    evaluate(level_ - 1, outputNfo[level_][output_].inA,
//			     event_),
//		    evaluate(level_ - 1, outputNfo[level_][output_].inB,
//			     event_));
//      }
//      return r;
    }


    string butterflyNet::getOperatorName(int op_) {
      string r;
      if (false) {
      } else if (0 == op_) {
	r = "and";
      } else if (1 == op_) {
	r = "or";
      } else if (2 == op_) {
	r = "xor";
      } else if (3 == op_) {
	r = "nor";
      } else if (4 == op_) {
	r = "a";
      } else if (5 == op_) {
	r = "b";
      } else {
	r = "?";
      }
      return r;
    }


    void butterflyNet::go() {
      showEventStream(0);
      eventStreams[0].calcWeights();
      eventStreams[0].calcPicks();
      cout << endl;

      int level(0);
      bool goNextLevel(eventStreams[level].picks.size() >= 2);
      while (goNextLevel) {
	level++;
	createOutputInfo(level);
	eventStream eStream;
	for (int x = 0; x < eventStreams[0].events.size(); x++) {
	  event eventX;
	  bool decisionAttribVal(eventStreams[0].events[x].attribs[0]);
	  eventX.attribs.insert(eventX.attribs.end(), decisionAttribVal);
	  for (int y = 1; y < outputNfo[level].size(); y++) {
	    int op(outputNfo[level][y].op);
	    int
	      inA(eventStreams[0].events[x].attribs[outputNfo[level][y].inA]);
	    int
	      inB(eventStreams[0].events[x].attribs[outputNfo[level][y].inB]);
	    bool attribValue(operate(op, inA, inB));
	    eventX.attribs.insert(eventX.attribs.end(), attribValue);
	  }
	  eStream.append(eventX);
	}
	eventStreams.insert(eventStreams.end(), eStream);
	showEventStream(level);
	eventStreams[level].calcWeights();
	eventStreams[level].calcPicks();
	for (int x = 1; x < eventStreams[level].picks.size(); x++) {
	  float correctness
	    (getCorrectness(level, eventStreams[level].picks[x]));
	  if (correctness > best) {
	    best = correctness;
	  }
	  //	  if (correctness > 0.5) {
	    cout << "fz: " << correctness * 100 << "%   best=" << best * 100
		 << endl;
	    cout << correctness * 100 << "% (" << eventStreams[level].picks[x]
		 << "): ";
	    showNet(level, eventStreams[level].picks[x]);
	    //	  }
	}
	cout << endl;
	goNextLevel = (eventStreams[level].picks.size() >= 2);
      }
    }


    bool butterflyNet::operate(int operator_, bool inA_, bool inB_) {
      bool r;
      if (false) {

      } else if (0 == operator_) {  // and
	r = inA_ && inB_;

      } else if (1 == operator_) {  // or
	r = inA_ || inB_;

      } else if (2 == operator_) {  // xor
	r = inA_ ^ inB_;

      } else if (3 == operator_) {  // nor
	r = !inA_ && !inB_;

      } else if (4 == operator_) {  // a
	r = inA_;

      } else if (5 == operator_) {  // b
	r = inB_;

      } else {
	r = false;

      }
      return r;
    }


    void butterflyNet::registerInitialEventStream(eventStream stream_) {
      eventStreams.resize(0);
      eventStreams.insert(eventStreams.end(), stream_);
    }


    void butterflyNet::showEventStream(int level_) {
      cout << "event stream level " << level_ << endl;
      for (int x = 0; x < eventStreams[level_].events.size(); x++) {
	for (int y = 0; y < eventStreams[level_].events[x].attribs.size();
	     y++) {
	  cout << eventStreams[level_].events[x].attribs[y] << " ";
	}
	cout << endl;
      }
    }


    void butterflyNet::showNet(int level_, int output_) {
      cout << showNet_(level_, output_) << endl;
    }


    string butterflyNet::showNet_(int level_, int output_) {
      ostringstream r("");
      if (1 == level_) {
	r << "(" << outputNfo[level_][output_].inA << " "
	  << getOperatorName(outputNfo[level_][output_].op) << " "
	  << outputNfo[level_][output_].inB
	  << ")";
      } else {
	r << "(" << showNet_(level_ - 1, outputNfo[level_][output_].inA) << " "
	  << getOperatorName(outputNfo[level_][output_].op) << " "
	  << showNet_(level_ - 1, outputNfo[level_][output_].inB)
	  << ")";
      }
      return r.str();
    }


  }
}
