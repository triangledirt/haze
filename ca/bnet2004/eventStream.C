#include "eventStream.H"


namespace z {
  namespace bnet {


    eventStream::eventStream() {}


    eventStream::eventStream(const eventStream& stream_) {
      events.resize(0);
      for (int x = 0; x < stream_.events.size(); x++) {
	events.insert(events.end(), stream_.events[x]);
      }
    }


    eventStream::~eventStream() {}


    void eventStream::append(event event_) {
      events.insert(events.end(), event_);
    }


    void eventStream::calcPicks() {
      if (weights.size() < 2) {
	return;
      }

      cout << "picks: ";

      picks.insert(picks.end(), 0);
      int pickFindCount(32);  // 32  ... actually...as high as possible?
      vector<weightIndexPair> w2;
      w2.resize(weights.size());
      for (int x = 1; x < weights.size(); x++) {
	w2[x].weight = weights[x];
	w2[x].index = x;
      }
      sort(w2.begin(), w2.end());
      if ((w2.size() - 1) >= pickFindCount) {
	for (int x = (w2.size() - 1); x >= (w2.size() - pickFindCount); x--) {
	  int pickIdx(w2[x].index);
	  picks.insert(picks.end(), pickIdx);
	  cout << pickIdx << "(" << w2[x].weight << ") ";
	}
      } else {
	for (int x = 1; x < weights.size(); x++) {
	  picks.insert(picks.end(), x);
	  cout << x << "(" << w2[x].weight << ") ";
	}
      }

      cout << endl;
    }


    void eventStream::calcWeights() {
      if (events.size() < 1) {
	return;
      }
      int attribCount(events[0].attribs.size());
      if ((attribCount - 1) < 2) {
	return;
      }

      cout << "weights: ";
      weights.resize(attribCount);
      for (int x = 1; x <= (attribCount - 1); x++) {
	weights[x] = 0;
      }

      for (int eventX = 0; eventX <= events.size() - 1; eventX++) {
	for (int eventY = 0; eventY <= events.size() - 1; eventY++) {
	  if (eventX != eventY) {
	    for (int attribX = 1; attribX <= (attribCount - 1); attribX++) {
	      if ((events[eventX].attribs[0] == events[eventY].attribs[0])
		  == (events[eventX].attribs[attribX]
		      == events[eventY].attribs[attribX])) {
		weights[attribX]++;
	      }
	    }
	  }
	}
      }

      for (int x = 1; x <= (attribCount - 1); x++) {
	cout << weights[x] << " ";
      }
      cout << endl;
    }


    eventStream& eventStream::operator=(const eventStream& stream_) {
      events.resize(0);
      for (int x = 0; x < stream_.events.size(); x++) {
	events.insert(events.end(), stream_.events[x]);
      }
    }


    bool operator<(const weightIndexPair& a_, const weightIndexPair& b_) {
      return a_.weight < b_.weight;
    }


  }
}
