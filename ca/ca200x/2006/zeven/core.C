// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#include "core.H"


namespace z {
  namespace core {


    unsigned long int BinaryToDecimal(vector<unsigned int> binary_) {
      unsigned long int decimal(0);
      unsigned int binarySize(binary_.size());
      unsigned long int placeValue(1);  // i.e. 1, 2, 4, 8, ...
      for (unsigned int j = 0; j < binarySize; j++) {
				decimal += (placeValue * binary_[j]);
				placeValue *= 2;
      }
      return decimal;
    }


    vector<unsigned int> DecimalToBinary(unsigned int decimal_) {
      list<unsigned int> binary;

      unsigned int decimalChopping(decimal_);
      unsigned int decimalPlace(1);

      while (decimalChopping > 0) {
				unsigned int binaryPiece(decimalChopping % (decimalPlace * 2));
				if (binaryPiece == 0) {
					binary.insert(binary.end(), 0);
				} else {
					binary.insert(binary.end(), 1);
					decimalChopping -= (decimalPlace);
				}
				decimalPlace *= 2;
      }

      vector<unsigned int> binaryVector;
      binaryVector.resize(binary.size());
      list<unsigned int>::iterator it;
      unsigned int index(0);
      for (it = binary.begin(); it != binary.end(); it++) {
				binaryVector[index] = *it;
				index++;
      }

      return binaryVector;
    }


    vector<unsigned int> PadBinary(vector<unsigned int> binary_,
																	 unsigned int totalWidth_) {
      vector<unsigned int> binary(binary_);
      while (binary.size() < totalWidth_) {
				binary.insert(binary.end(), 0);
      }
      return binary;
    }


    vector<unsigned int> ReverseBinary(vector<unsigned int> binary_) {
      vector<unsigned int> binary;
      vector<unsigned int>::reverse_iterator it;
      for (it = binary_.rbegin(); it != binary_.rend(); it++) {
				binary.insert(binary.end(), *it);
      }
      return binary;
    }


  }
}
