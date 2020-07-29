// Copyright 2004 Inhaesio Zha.  All Rights Reserved.


#include "animalDescriptor.H"


namespace z {
  namespace animals {


    animalDescriptor::animalDescriptor() {
      order = 0;
      name = 0;
    }


    animalDescriptor::animalDescriptor(unsigned int order_,
				       unsigned int name_) {
      order = order_;
      name = name_;
    }


    animalDescriptor::~animalDescriptor() {}


  }
}
