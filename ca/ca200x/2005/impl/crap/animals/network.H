// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#ifndef z_animals_network_H
#define z_animals_network_H


#include "../z.H"
#include "node.H"


namespace z {
  namespace animals {


    class network {
      vector<node*> _nodes;
      vector< vector<unsigned int> > _nodeParams;
      vector< vector<unsigned int> > _networkHistory;
    public:
      network();
      ~network();
      void addNode(animalDescriptor animalDescriptor_,
		   vector<unsigned int> parameterList_,
		   unsigned int initialValue_);
      void createHtmlSummary(unsigned int steps_, string filenamePrefix_);
      bool doesNotRepeat();
      bool doesNotRepeatMuch();
      void initCrackHausCA(unsigned int rule1Number_,
			   unsigned int rule2Number_, unsigned int width_);
      void initCrackHaus3CA(unsigned int rule1Number_,
			    unsigned int rule2Number_, unsigned int width_);
      void initCrackHausRainbowCA(unsigned int rule1Number_,
				  unsigned int rule2Number_,
				  unsigned int rule3Number_,
				  unsigned int width_);
      void initCrackHausRainbowXCA(unsigned int rule1Number_,
				   unsigned int rule2Number_,
				   unsigned int rule3Number_,
				   unsigned int width_);
      void initCrazyCow3CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyDuck4CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyFish4CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyFrog4CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyGoose7CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyGoose9CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyHorse2CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyHorse3CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyHorse5CA(unsigned int ruleNumber_, unsigned int width_);
      void initCrazyIguana3CA(unsigned int ruleMod_, unsigned int width_);
      void initMonkey5CA(unsigned int ruleNumber_, unsigned int width_);
      void initRedMonkey5CA(unsigned int ruleNumber_, unsigned int width_);
      void initXcCA(unsigned int ruleNumber_, unsigned int width_);
      void initXdCA(unsigned int ruleNumber_, unsigned int width_);
      void initXeCA(unsigned int ruleNumber_, unsigned int width_);
      void initWackyA5CA(unsigned int width_);
      void initWackyA5xibCA(unsigned int width_);
      void initWackyA5xicCA(unsigned int width_);
      void initWackyA5xidCA(unsigned int width_);
      void initWackyB5CA(unsigned int width_);
      void initWackyC5CA(unsigned int width_);
      void initWackyC3CA(unsigned int width_);
      void initWideWolframCA(unsigned int ruleNumber_, unsigned int width_);
      void initWolframCA(unsigned int ruleNumber_, unsigned int width_);
      void iterate();
    };


  }
}


#endif
