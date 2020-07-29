#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <pngwriter.h>
#include <sys/stat.h>
#include "animal.H"
#include "animalDescriptor.H"
#include "core.H"


using namespace std;


//const unsigned int X(128);
//const unsigned int Y(72);
//const unsigned int Z(32);

const unsigned int X(32);
const unsigned int Y(18);
const unsigned int Z(32);

const unsigned int T(256);
const unsigned int O(7);
const unsigned int Oz(128);


void saveNetworkPNG(string name_,
										vector< vector< vector<unsigned int> > >& frame_) {
  ostringstream filename("");
	filename << "pngs/" << name_ << ".png";

  pngwriter png((X - 2), (Y - 2), 0, filename.str().c_str());

  float r;
  float g;
  float b;

	for (unsigned int x = 0 + 1; x < (X - 1); x++) {
		for (unsigned int y = 0 + 1; y < (Y - 1); y++) {
			unsigned int composite(0);
			for (unsigned int z = 0 + 1; z < (Z - 1); z++) {
				composite += frame_[x][y][z];
			}
			double perc = (double) composite / (double) (Z - 2);
			r = perc;
			g = perc;
			b = perc;
			png.plot(x, y, r, g, b);
		}
	}

  png.close();
}


int main() {
	for (unsigned int j = 0; j < 1024; j++) {
		cout << j << endl;

		ostringstream dirName("");
		dirName << "pngs/" << j;
		mkdir(dirName.str().c_str(), S_IRWXU);

		vector<unsigned int> an;
		for (unsigned int i = 0; i < Oz; i++) {
			unsigned int b(rand() % 2);
			an.insert(an.end(), b);
			cout << b;
		}
		cout << endl;
		z::animals::animal a(O, an);

		cout << "init w" << endl;
		vector< vector< vector<unsigned int> > > w;
		w.resize(X);
		for (unsigned int x = 0; x < X; x++) {
			w[x].resize(Y);
			for (unsigned int y = 0; y < Y; y++) {
				w[x][y].resize(Z);
				for (unsigned int z = 0; z < Z; z++) {
					w[x][y][z] = rand() % 2;
				}
			}
		}

		cout << "init wx" << endl;
		vector< vector< vector<unsigned int> > > wx;
		wx.resize(X);
		for (unsigned int x = 0; x < X; x++) {
			wx[x].resize(Y);
			for (unsigned int y = 0; y < Y; y++) {
				wx[x][y].resize(Z);
				for (unsigned int z = 0; z < Z; z++) {
					wx[x][y][z] = rand() % 2;
				}
			}
		}

		for (unsigned int t = 0; t < T; t++) {
			if (0 == (t % 32)) {
				cout << t << endl;
			}
			for (unsigned int x = 0 + 1; x < (X - 1); x++) {
				for (unsigned int y = 0 + 1; y < (Y - 1); y++) {
					for (unsigned int z = 0 + 1; z < (Z - 1); z++) {
						unsigned int pA = w[x][y][z];
						unsigned int pB = w[x + 1][y][z];
						unsigned int pC = w[x - 1][y][z];
						unsigned int pD = w[x][y + 1][z];
						unsigned int pE = w[x][y - 1][z];
						unsigned int pF = w[x][y][z + 1];
						unsigned int pG = w[x][y][z - 1];

						vector<unsigned int> rule;
						rule.insert(rule.end(), pA);
						rule.insert(rule.end(), pB);
						rule.insert(rule.end(), pC);
						rule.insert(rule.end(), pD);
						rule.insert(rule.end(), pE);
						rule.insert(rule.end(), pF);
						rule.insert(rule.end(), pG);
						unsigned int ruleInt(z::core::BinaryToDecimal(rule));
						unsigned int newValue(a.getValueForRule(ruleInt));

						wx[x][y][z] = newValue;
					}
				}
			}
			for (unsigned int x = 0; x < X; x++) {
				for (unsigned int y = 0; y < Y; y++) {
					for (unsigned int z = 0; z < Z; z++) {
						w[x][y][z] = wx[x][y][z];
					}
				}
			}

			ostringstream name("");
			name << j << "/" << t;
			saveNetworkPNG(name.str(), w);
		}
		cout << endl;
	}
}
