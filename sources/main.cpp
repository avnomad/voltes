#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <iomanip>
using std::setw;
using std::setprecision;


#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <cstdlib>
using std::calloc;

#include <climits>

#include <CPU clock.h>
#include "count paths.h"


// prototypes
void intThrower(){throw 0;}


int main(int argc , char **argv)
{
	ifstream in;
#pragma region open output stream
	ofstream out("c:/output/stats linear.txt");
	if(!out)
	{
		cerr << "cannot open output file!\n";
		return 0;
	}
#pragma endregion

	uint N,M,T;
	uint startI,startJ,stopI,stopJ;
	uint K;
	uint tempI,tempJ;
	Node *table;
	Node *p;
	uint distanceBase,distance;
	std::string name("c:/input/benchmark/test");

	double t;
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
		t = CPUclock::currentTime();
		#pragma region read from input
		in >> N >> M >> T >> startI >> startJ >> stopI >> stopJ >> K;	// read parameters from input.
		#pragma endregion
		#pragma region create the table
		N += 2 , M += 2;	// adjust the number of rows and columns to accommodate the border.
		table = new Node[N*M];	// allocate space for the table.

		distanceBase = 0;
		for(tempI = stopI ; tempI > 0 ; --tempI)
		{
			distance = distanceBase;
			for(tempJ = stopJ ; tempJ > 0 ; --tempJ)
				(table + M*tempI + tempJ)->dist = distance++;
			distance = ++distanceBase;
			for(tempJ = stopJ+1 ; tempJ <=  M-2 ; tempJ++)
				(table + M*tempI + tempJ)->dist = distance++;
		} // end first outer for

		distanceBase = 1;
		for(tempI = stopI+1 ; tempI <=  N-2 ; ++tempI)
		{
			distance = distanceBase;
			for(tempJ = stopJ ; tempJ > 0 ; --tempJ)
				(table + M*tempI + tempJ)->dist = distance++;
			distance = ++distanceBase;
			for(tempJ = stopJ+1 ; tempJ <=  M-2 ; tempJ++)
				(table + M*tempI + tempJ)->dist = distance++;
		} // end second outer for
		#pragma endregion
		#pragma region read obstacles
		while(K--)
		{
			in >> tempI >> tempJ;	// read obstacle coordinates.
			(table + M*tempI + tempJ)->dist = UINT_MAX;	// register obstacle
		} // end while
		#pragma endregion
		#pragma region generate border
		// generate border
		K = M;
		p = table;
		while(K--)
			p++->dist = UINT_MAX;
		K = N-1;
		while(--K)
		{
			p->dist = UINT_MAX;
			p += M-1;
			p++->dist = UINT_MAX;
		} // end while
		K = M;
		while(K--)
			p++->dist = UINT_MAX;
		#pragma endregion
		//t = CPUclock::currentTime() - t;
		//cout << t << CPUclock::getUnit() << '\t';
		//t = CPUclock::currentTime();
		#pragma region attach lists to nodes
		for(tempI = 1 ; tempI < N-1 ; ++tempI)
			for(tempJ = 1 ; tempJ < M-1 ; ++tempJ)
				if((table + M*tempI + tempJ)->dist != UINT_MAX)
				{
					(table + M*tempI + tempJ)->paths = new uint[T+1];
					for(int c = 0 ; c <= T ; ++c)
						(table + M*tempI + tempJ)->paths[c] = UINT_MAX;
				} // if
		#pragma endregion
		//t = CPUclock::currentTime() - t;
		//cout << t << CPUclock::getUnit() << '\t';
		//t = CPUclock::currentTime();
		#pragma region count paths
		int temp = count_paths(table,M,startI,startJ,stopI,stopJ,T);
		#pragma endregion
		#pragma region free memory
		for(tempI = 1 ; tempI < N-1 ; ++tempI)
			for(tempJ = 1 ; tempJ < M-1 ; ++tempJ)
				if((table + M*tempI + tempJ)->dist != UINT_MAX)
					delete (table + M*tempI + tempJ)->paths;
		#pragma endregion
		t = CPUclock::currentTime() - t;
		cout << t << CPUclock::getUnit() << '\n';

		cout << setw(60) << temp << " paths" << endl;
		out << t << endl;
		delete table;
		in.close();
	} // end for


	system("PAUSE");
	return 0;
} // end function main