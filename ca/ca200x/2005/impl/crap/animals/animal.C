// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#include "animal.H"
#include "../core/core.H"


namespace z {
  namespace animals {


    animal::animal() {
      _order = 0;
      _name = 0;
      init();
    }


    animal::animal(animalDescriptor animalDescriptor_) {
      _order = animalDescriptor_.order;
      _name = animalDescriptor_.name;
      init();
    }


    animal::~animal() {}


    void animal::coutRules() {
      unsigned int ruleCount(_rules.size());

      vector<unsigned int> tempBinary(core::DecimalToBinary(ruleCount - 1));
      unsigned int binaryWidth(tempBinary.size());

      for (unsigned int ruleIndex = 0; ruleIndex < ruleCount; ruleIndex++) {
	vector<unsigned int> binary(core::DecimalToBinary(ruleIndex));
	binary = core::PadBinary(binary, binaryWidth);
	binary = core::ReverseBinary(binary);
	vector<unsigned int>::iterator it;
	for (it = binary.begin(); it != binary.end(); it++) {
	  cout << *it << " ";
	}
	cout << "| " << _rules[ruleIndex] << endl;
      }
    }


    unsigned int animal::getName() {
      return _name;
    }


    unsigned int animal::getOrder() {
      return _order;
    }


    unsigned int animal::getValueForRule(unsigned int rule_) {
      return _rules[rule_];
    }


    void animal::init() {
      // make sure _order and _name jive with each other
      unsigned int maxNameForOrder((unsigned int) pow(2, pow(2, _order)));
      if (_name > maxNameForOrder) {
	_name = maxNameForOrder;
      }

      // set up rule table (indexed by unsigned int, with unsigned int)
      unsigned int ruleCount;
      ruleCount = (unsigned int) pow(2, _order);
      _rules.resize(ruleCount);
      vector<unsigned int> ruleBinary;
      ruleBinary = core::DecimalToBinary(_name);
      unsigned int ruleBinarySize(ruleBinary.size());
      for (unsigned int rule = 0; rule < ruleCount; rule++) {
	if (rule < ruleBinarySize) {
	  _rules[rule] = ruleBinary[rule];
	} else {
	  _rules[rule] = 0;
	}
      }
    }


  }
}
