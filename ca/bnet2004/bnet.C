#include "butterflyNet.H"
#include "event.H"
#include "eventStream.H"


int main() {
  //                   a  b  c  d
//  z::bnet::event e0(1, 0, 1, 1, 1, 0, 0);
//  z::bnet::event e1(0, 0, 0, 0, 1, 1, 1);
//  z::bnet::event e2(0, 0, 0, 0, 1, 0, 1);
//  z::bnet::event e3(0, 1, 1, 1, 0, 0, 1);
//  z::bnet::event e4(0, 0, 1, 0, 1, 1, 1);
//  z::bnet::event e5(1, 0, 0, 1, 1, 0, 0);
//  z::bnet::event e6(1, 1, 1, 1, 1, 0, 0);
//  z::bnet::event e7(1, 0, 0, 1, 1, 0, 1);

  z::bnet::eventStream eStream;
//  eStream.append(e0);
//  eStream.append(e1);
//  eStream.append(e2);
//  eStream.append(e3);
//  eStream.append(e4);
//  eStream.append(e5);
//  eStream.append(e6);
//  eStream.append(e7);
  for (int x = 0; x <= 255; x++) {
    z::bnet::event e;
    for (int y = 0; y <= 31; y++) {
      bool c(rand() % 2);
      e.attribs.insert(e.attribs.end(), c);
    }
    eStream.append(e);
  }

  z::bnet::butterflyNet bNet;
  bNet.registerInitialEventStream(eStream);
  bNet.go();
}
