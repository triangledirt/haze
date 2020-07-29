// Copyright 2004 Inhaesio Zha.  All Rights Reserved.


#ifndef z_animals_animalDescriptor_H
#define z_animals_animalDescriptor_H


#include "../z.H"


namespace z {
  namespace animals {


    class animalDescriptor {
    public:
      unsigned int order;
      unsigned int name;
      animalDescriptor();
      animalDescriptor(unsigned int order_, unsigned int name_);
      ~animalDescriptor();
    };


  }
}


#endif
