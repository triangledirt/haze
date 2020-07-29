// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#ifndef z_core_core_H
#define z_core_core_H


#include "../z.H"


namespace z {
  namespace core {


    unsigned int BinaryToDecimal(vector<unsigned int> binary_);
    vector<unsigned int> DecimalToBinary(unsigned int decimal_);
    vector<unsigned int> PadBinary(vector<unsigned int> binary_,
				   unsigned int totalWidth_);
    vector<unsigned int> ReverseBinary(vector<unsigned int> binary_);


  }
}


#endif
