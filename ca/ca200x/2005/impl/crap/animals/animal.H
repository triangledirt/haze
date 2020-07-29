// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#ifndef z_animals_animal_H
#define z_animals_animal_H


#include "../z.H"
#include "animalDescriptor.H"


namespace z {
  namespace animals {


    class animal {
      unsigned int _order;
      unsigned int _name;
      vector<unsigned int> _rules;

      void init();
    public:
      animal();
      animal(animalDescriptor animalDescriptor_);
      ~animal();
      void coutRules();
      unsigned int getName();
      unsigned int getOrder();
      unsigned int getValueForRule(unsigned int rule_);
    };


  }
}


#endif
