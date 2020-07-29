// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#ifndef z_animals_node_H
#define z_animals_node_H


#include "../z.H"
#include "animal.H"
#include "animalDescriptor.H"


namespace z {
  namespace animals {


    class node {
      animal* _animal;
      unsigned int _value;
    public:
      node();
      node(animalDescriptor animalDescriptor_, unsigned int initialValue_);
      ~node();
      unsigned int getNextValue(vector<unsigned int> parameters_);
      animalDescriptor getAnimalDescriptor();
      unsigned int getValue();
      void mutate(vector<unsigned int> parameters_);
      void setAnimal(animalDescriptor animalDescriptor_);
      void setValue(unsigned int value_);
    };


  }
}


#endif
