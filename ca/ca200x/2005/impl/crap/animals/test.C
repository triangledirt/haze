// Copyright 2005 Inhaesio Zha.  All Rights Reserved.


#include "animal.H"
#include "animalDescriptor.H"
#include "network.H"


int main() {
  using namespace z::animals;

  //srand(7609);
  //net.initWolframCA(131, 23);  // I like rules 131, 85

  // wide wolframs
  if (false) {
  for (unsigned int rule = 9722; rule <= 9722; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/widewolfram/widewolfram_" << rule;

    cout << rule << endl;
    network net;
    net.initWideWolframCA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // wolframs
  if (false) {
  for (unsigned int rule = 0; rule < 256; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wolfram/wolfram_" << rule;

    cout << rule << endl;
    network net;
    net.initWolframCA(rule, 51);
    net.createHtmlSummary(110, ruleStr.str());
  }
  }

  // CrackHaus s
  if (false) {
  for (unsigned int rule1 = 0; rule1 < 256; rule1++) {
    for (unsigned int rule2 = 0; rule2 < 256; rule2++) {
    ostringstream ruleStr("");
    ruleStr << "play/crackhaus/crackhaus_" << rule1 << "_" << rule2;

    cout << rule1 << "_" << rule2 << endl;
    network net;
    net.initCrackHausCA(rule1, rule2, 127);
    net.createHtmlSummary(255, ruleStr.str());
    }
  }
  }

  // CrackHaus3 s
  if (false) {
  for (unsigned int rule1 = 0; rule1 < 256; rule1++) {
    for (unsigned int rule2 = 0; rule2 < 256; rule2++) {
    ostringstream ruleStr("");
    ruleStr << "play/crackhaus3/crackhaus3_" << rule1 << "_" << rule2;

    cout << rule1 << "_" << rule2 << endl;
    network net;
    net.initCrackHaus3CA(rule1, rule2, 127);
    net.createHtmlSummary(255, ruleStr.str());
    }
  }
  }

  // CrackHausRainbow s
  if (false) {
  for (unsigned int rule1 = 0; rule1 < 16; rule1++) {
    for (unsigned int rule2 = 0; rule2 < 16; rule2++) {
      for (unsigned int rule3 = 0; rule3 < 16; rule3++) {
	ostringstream ruleStr("");
	ruleStr << "play/crackhausRainbow/crackhausRainbow_" << rule1
		<< "_" << rule2 << "_" << rule3;

	cout << rule1 << "_" << rule2 << "_" << rule3 << endl;
	network net;
	net.initCrackHausRainbowCA(rule1, rule2, rule3, 127);
	net.createHtmlSummary(255, ruleStr.str());
      }
    }
  }
  }

  // CrackHausRainbowX s
  if (false) {
  for (unsigned int rule1 = 0; rule1 < 16; rule1++) {
    for (unsigned int rule2 = 0; rule2 < 16; rule2++) {
      for (unsigned int rule3 = 0; rule3 < 16; rule3++) {
	ostringstream ruleStr("");
	ruleStr << "play/crackhausRainbowX/crackhausRainbowX_" << rule1
		<< "_" << rule2 << "_" << rule3;

	cout << rule1 << "_" << rule2 << "_" << rule3 << endl;
	network net;
	net.initCrackHausRainbowXCA(rule1, rule2, rule3, 127);
	net.createHtmlSummary(255, ruleStr.str());
      }
    }
  }
  }

  // crazyhorse2 s
  if (false) {
  srand(19);
  for (unsigned int rule = 0; rule < 16; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyhorse2/seed19/crazyhorse2_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyHorse2CA(rule, 51);
    net.createHtmlSummary(110, ruleStr.str());
  }
  }

  // crazyhorse3 s
  if (false) {
  srand(2);
  for (unsigned int rule = 0; rule < 256; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyhorse3/seed2/crazyhorse3_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyHorse3CA(rule, 51);
    net.createHtmlSummary(110, ruleStr.str());
  }
  }

  // crazyhorse5 s
  if (false) {
  srand(2);
  for (unsigned int rule = 0; rule < 1000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyhorse5/seed2/crazyhorse5_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyHorse5CA(rule, 51);
    net.createHtmlSummary(110, ruleStr.str());
  }
  }

  // wackyA5 s
  if (false) {
  srand(0);
  for (unsigned int rule = 0; rule < 1000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wackyA5/seed0/wackyA5_" << rule;

    cout << rule << endl;
    network net;
    net.initWackyA5CA(127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // wackyA5xib s
  if (false) {
  srand(0);
  for (unsigned int rule = 0; rule < 1000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wackyA5xib/seed0/wackyA5xib_" << rule;

    cout << rule << endl;
    network net;
    net.initWackyA5xibCA(127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // wackyA5xic s
  if (false) {
  srand(0);
  for (unsigned int rule = 0; rule <= 262; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wackyA5xic/seed0/wackyA5xic_" << rule;

    cout << rule << endl;
    network net;
    net.initWackyA5xicCA(383);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // wackyA5xid s
  if (false) {
  srand(800);
  for (unsigned int rule = 1777223; rule < 2000000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wackyA5xid/seed800/wackyA5xid_" << rule;

    cout << rule << endl;
    network net;
    net.initWackyA5xidCA(127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // wackyB5 s
  if (false) {
  srand(742);
  for (unsigned int rule = 0; rule < 1000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wackyB5/seed742/wackyB5_" << rule;

    cout << rule << endl;
    network net;
    net.initWackyB5CA(51);
    net.createHtmlSummary(110, ruleStr.str());
  }
  }

  // wackyC5 s
  if (false) {
  srand(742);
  for (unsigned int rule = 0; rule < 1000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wackyC5/seed742/wackyC5_" << rule;

    cout << rule << endl;
    network net;
    net.initWackyC5CA(51);
    net.createHtmlSummary(110, ruleStr.str());
  }
  }

  // wackyC3 s
  if (false) {
  srand(7);
  for (unsigned int rule = 0; rule < 256; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/wackyC3/seed7/wackyC3_" << rule;

    cout << rule << endl;
    network net;
    net.initWackyC3CA(51);
    net.createHtmlSummary(110, ruleStr.str());
  }
  }

  // crazyCow3 s
  if (false) {
  srand(7);
  for (unsigned int rule = 0; rule < 256; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyCow3/seed7/crazyCow3_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyCow3CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // crazyDuck4 s
  if (false) {
  for (unsigned int rule = 6900; rule < 7900; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyDuck4/crazyDuck4_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyDuck4CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // crazyFish4 s
  if (false) {
  for (unsigned int rule = 3000; rule < 4000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyFish4/crazyFish4_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyFish4CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // crazyFrog4 s
  if (false) {
  for (unsigned int rule = 300000; rule < 400000; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyFrog4/crazyFrog4_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyFrog4CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // crazyGoose9 s
  if (false) {
    //for (unsigned int rule = 16384; rule < 32768; rule++) {
  while (true) {
    unsigned int rule(rand() % 900000000);
    ostringstream ruleStr("");
    ruleStr << "play/crazyGoose9/crazyGoose9_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyGoose9CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // crazyGoose7 s
  if (false) {
    //for (unsigned int rule = 900638400; rule < 901276800; rule++) {
  while (true) {
    unsigned int rule(rand() % 900000000);
    ostringstream ruleStr("");
    ruleStr << "play/crazyGoose7/crazyGoose7_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyGoose7CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // monkey5 s
  if (false) {
    srand(0);
    //for (unsigned int rule = 900638400; rule < 901276800; rule++) {
  while (true) {
    unsigned int rule(rand() % 900000000);
    ostringstream ruleStr("");
    ruleStr << "play/monkey5/s0/monkey5_" << rule;

    cout << rule << endl;
    network net;
    net.initMonkey5CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // redMonkey5 s
  if (false) {
    srand(0);
    //for (unsigned int rule = 900638400; rule < 901276800; rule++) {
  while (true) {
    unsigned int rule(rand() % 900000000);
    ostringstream ruleStr("");
    ruleStr << "play/redMonkey5/s0/redMonkey5_" << rule;

    cout << rule << endl;
    network net;
    net.initRedMonkey5CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // xc s
  if (false) {
    srand(0);
    //for (unsigned int rule = 900638400; rule < 901276800; rule++) {
  while (true) {
    unsigned int rule(rand() % 900000000);
    ostringstream ruleStr("");
    ruleStr << "play/xc/s0/xc_" << rule;

    cout << rule << endl;
    network net;
    net.initXcCA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // xd s
  if (false) {
    srand(0);
    //for (unsigned int rule = 900638400; rule < 901276800; rule++) {
  while (true) {
    unsigned int rule(rand() % 900000000);
    ostringstream ruleStr("");
    ruleStr << "play/xd/s0/xd_" << rule;

    cout << rule << endl;
    network net;
    net.initXdCA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // xe s
  if (true) {
    srand(0);
    //for (unsigned int rule = 900638400; rule < 901276800; rule++) {
  while (true) {
    unsigned int rule(rand() % 900000000);
    ostringstream ruleStr("");
    ruleStr << "play/xe/s0/xe_" << rule;

    cout << rule << endl;
    network net;
    net.initXeCA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  // crazyIguana3 s
  if (false) {
  for (unsigned int rule = 0; rule < 256; rule++) {
    ostringstream ruleStr("");
    ruleStr << "play/crazyIguana3/crazyIguana3_" << rule;

    cout << rule << endl;
    network net;
    net.initCrazyIguana3CA(rule, 127);
    net.createHtmlSummary(255, ruleStr.str());
  }
  }

  if (false) {
    network net;
    net.initWideWolframCA(6901, 31);
    net.createHtmlSummary(128, "play/wide_wolfram_6901");
  }
}
