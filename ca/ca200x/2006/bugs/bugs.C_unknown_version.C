#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;


const unsigned int X(72);
const unsigned int Y(128);
const unsigned int Z(32);
const unsigned int T(256);


class q {
public:
	unsigned short v;
	q();
	~q();
	void init();
	unsigned short f(q q1, q q2, q q3, q q4, q q5, q q6);
};


q::q() {
	v = 0;
}


q::~q() {}


void q::init() {
	v = rand() % 2;
}


unsigned short q::f(q q1, q q2, q q3, q q4, q q5, q q6) {
	if (0 == q1.v) {
		v = q2.v ^ q6.v;
	} else {
		v = q2.v;
	}
	return v;
}


int main() {
	//for (unsigned int j = 0; j < 1024; j++) {
	//srand(j);
	unsigned int j(98);
	srand(j);
		const short a1((rand() % 3) - 1);
		const short a2((rand() % 3) - 1);
		const short a3((rand() % 3) - 1);
		const short a4((rand() % 3) - 1);
		const short a5((rand() % 3) - 1);
		const short a6((rand() % 3) - 1);
		const short a7((rand() % 3) - 1);
		const short a8((rand() % 3) - 1);
		const short a9((rand() % 3) - 1);
		const short a10((rand() % 3) - 1);
		const short a11((rand() % 3) - 1);
		const short a12((rand() % 3) - 1);
		const short a13((rand() % 3) - 1);
		const short a14((rand() % 3) - 1);
		const short a15((rand() % 3) - 1);
		const short a16((rand() % 3) - 1);
		const short a17((rand() % 3) - 1);
		const short a18((rand() % 3) - 1);

		vector< vector< vector<q> > > w;
		w.resize(X);
		for (unsigned int x = 0; x < X; x++) {
			w[x].resize(Y);
			for (unsigned int y = 0; y < Y; y++) {
				w[x][y].resize(Z);
				for (unsigned int z = 0; z < Z; z++) {
					w[x][y][z].init();
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
						q q1 = w[x + a1][y + a2][z + a3];
						q q2 = w[x + a4][y + a5][z + a1];
						q q3 = w[x + a12][y + a14][z + a11];
						q q4 = w[x + a5][y + a1][z + a2];
						q q5 = w[x + a3][y + a4][z + a5];
						q q6 = w[x + a15][y + a18][z + a17];
						//w[x][y][z].f(q1, q2, q3, q4, q5, q6);
						if ((q2.v == q5.v)
								^ (q3.v == w[x][y][z].f(q1, q2, q3, q4, q5, q6))) {
							w[x][y][z].v = w[x + a4][y + a5][z + a8].v;
							//w[x + 1][y][z - 1].v = w[x][y][z + 1].v;
						}
					}
				}
			}

			if (true) {
				//if (0 == (t % 4)) {
				ostringstream fname("");
				fname << "b";
				fname << j << "_" << t;
				fname << ".html";
				ofstream of(fname.str().c_str());
				of << "<html>";
				of << "<style type='text/css'>";
				of << "  td {";
				of << "    width: 4px;";
				of << "    height: 4px;";
				of << "  }";
				of << "</style>";
				of << "<body>";
				of << "<table cellspacing='0' cellpadding='0'>";
				for (unsigned int x = 0 + 0; x < (X - 0); x++) {
					of << "<tr>";
					for (unsigned int y = 0 + 0; y < (Y - 0); y++) {
						unsigned int composite(0);
						for (unsigned int z = 0 + 0; z < (Z - 0); z++) {
							//for (unsigned int z = 16; z < 17; z++) {
							//composite = composite ^ w[x][y][z].v;
							composite += w[x][y][z].v;
						}
						//if (0 == composite) {
						//	of << "<td><img src='black.gif'></td>";
						//} else {
						//	of << "<td><img src='white.gif'></td>";
						//}
						float perc = ((float) composite / (float) Z) * 10;
						unsigned short percShort = (unsigned short) perc;
						ostringstream ss("");
						for (unsigned short i = 0; i < 5; i++) {
							ss << percShort;
						}
						of << "<td bgcolor='#" << ss.str() << "'></td>";
					}
					of << "</tr>";
				}
				of << "</table>";
				of << "</body></html>";
			}
		}
		//}
}
