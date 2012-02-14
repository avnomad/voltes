#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <cstdlib>
using std::calloc;

#include <CPU clock.h>
#include "count paths.h"

// prototypes
void intThrower(){throw 0;}


int main(int argc , char **argv)
{
	ifstream in;
#pragma region open output stream
	ofstream out("c:/output/stats leaf cut.txt");
	if(!out)
	{
		cerr << "cannot open output file!\n";
		return 0;
	}
#pragma endregion

	int N,M,T;
	int startX,startY,stopX,stopY;
	int K;
	int tempX,tempY;
	bool *table;
	bool *p;
	std::string name("c:/input/benchmark/test");

	for(int c = 1 ; c <= 4 ; ++c)
	{
		#pragma region open input stream
		in.open((name+(char)('0'+c)+".txt").c_str());
		if(!in)
		{
			cerr << "cannot open input file!\n";
			return 0;
		}
		in.clear();
		#pragma endregion
		double t = CPUclock::currentTime();
		#pragma region read from input
		in >> N >> M >> T >> startX >> startY >> stopX >> stopY >> K;	// read parameters from input.
		N += 2 , M += 2;	// adjust the number of rows and columns to accommodate the border.

		table = (bool*)calloc(N*M,sizeof(bool));	// allocate space for the table. initialize with zeros.
		while(K--)
		{
			in >> tempX >> tempY;	// read obstacle coordinates.
			*(table + M*tempX + tempY) = true;	// register obstacle
		} // end while
		#pragma endregion
		#pragma region generate border
		// generate border
		K = M;
		p = table;
		while(K--)
			*p++ = true;
		K = N-1;
		while(--K)
		{
			*p = true;
			p += M-1;
			*p++ = true;
		} // end while
		K = M;
		while(K--)
			*p++ = true;
		#pragma endregion

		// count paths
		int temp = count_paths(table,M,startX,startY,stopX,stopY,T);
		t = CPUclock::currentTime() - t;

		cout << temp << endl;
		cout << t << CPUclock::getUnit() << endl;
		out << t << endl;
		free(table);
		in.close();
	} // end for


	system("PAUSE");
	return 0;
} // end function main