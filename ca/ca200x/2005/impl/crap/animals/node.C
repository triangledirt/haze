// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#include "node.H"
#include "../core/core.H"


namespace z {
  namespace animals {


    node::node() {
      _animal = 0;
      _value = rand() % 2;
    }


    node::node(animalDescriptor animalDescriptor_,
	       unsigned int initialValue_) {
      _animal = new animal(animalDescriptor_);
      _value = initialValue_;
    }


    node::~node() {
      if (_animal) {
	delete _animal;
      }
    }


    animalDescriptor node::getAnimalDescriptor() {
      unsigned int order(0);
      unsigned int name(0);
      if (_animal) {
	order = _animal->getOrder();
	name = _animal->getName();
      }
      return animalDescriptor(order, name);
    }


    unsigned int node::getNextValue(vector<unsigned int> parameters_) {
      if (!_animal) {
	return 0;
      }
      unsigned int decimalRuleName(core::BinaryToDecimal(parameters_));
      return _animal->getValueForRule(decimalRuleName);
    }


    unsigned int node::getValue() {
      return _value;
    }


    void node::mutate(vector<unsigned int> parameters_) {
      if (!_animal) {
	return;
      }
      unsigned int decimalRuleName(core::BinaryToDecimal(parameters_));
      _value = _animal->getValueForRule(decimalRuleName);
    }


    void node::setAnimal(animalDescriptor animalDescriptor_) {
      if (_animal) {
	delete _animal;
      }
      _animal = new animal(animalDescriptor_);
    }


    void node::setValue(unsigned int value_) {
      _value = value_;
    }


  }
}
