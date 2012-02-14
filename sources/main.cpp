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
	ofstream out("c:/output/stats unreadable.txt");
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
	uint *table;
	uint *p,*q,*sp,*sq;
	uint distanceBase,distance;
	std::string name("c:/input/benchmark/test");
	uint D;
	double t;

	for(int c = 1 ; c <= 5 ; ++c)
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
		D = T+1;
		table = new uint[N*M*D];	// allocate space for the table.

		tempI = M*D;
		tempJ = tempI-D;

		distanceBase = 0;
		for(p = table+tempI*stopI ; p > table ; p -= tempI)
		{
			distance = distanceBase;
			for(q = p + stopJ*D ; q > p ; q -= D)
				*q = distance++;
			distance = ++distanceBase;
			sq = p + tempJ;
			for(q = p + stopJ*D+D ; q < sq ; q += D)
				*q = distance++;
		} // end p for

		distanceBase = 1;
		sp = table+(N-1)*tempI;
		for(p = table+tempI*stopI+tempI ; p < sp ; p += tempI)
		{
			distance = distanceBase;
			for(q = p + stopJ*D ; q > p ; q -= D)
				*q = distance++;
			distance = ++distanceBase;
			sq = p + tempJ;
			for(q = p + stopJ*D+D ; q < sq ; q += D)
				*q = distance++;
		} // end p for
		#pragma endregion
		#pragma region read obstacles
		while(K--)
		{
			in >> tempI >> tempJ;	// read obstacle coordinates.
			*(table + (M*tempI + tempJ)*D) = UINT_MAX;	// register obstacle
		} // end while
		#pragma endregion
		#pragma region generate border
		// generate border
		K = M;
		p = table;
		while(K--)
		{
			*p = UINT_MAX;
			p += D;
		} // end while
		K = N-1;
		while(--K)
		{
			*p = UINT_MAX;
			p += (M-1)*D;
			*p = UINT_MAX;
			p += D;
		} // end while
		K = M;
		while(K--)
		{
			*p = UINT_MAX;
			p += D;
		} // end while
		#pragma endregion
		/*t = CPUclock::currentTime() - t;
		cout << t << CPUclock::getUnit() << '\t';
		t = CPUclock::currentTime();*/
		#pragma region attach lists to nodes
		tempI = M*D;
		tempJ = tempI-D;
		sp = table+(N-1)*tempI;
		for(p = table + tempI ; p < sp ; p += tempI)
		{
			sq = p + tempJ;
			for(q = p + D ; q < sq ; q += D)
				if(*q != UINT_MAX)
					for(uint c = 1 ; c <= T ; ++c)
						*(q + c) = UINT_MAX;
		} // end p for
		#pragma endregion
		/*t = CPUclock::currentTime() - t;
		cout << t << CPUclock::getUnit() << '\t';
		t = CPUclock::currentTime();*/
		#pragma region count paths
		uint temp = count_paths(table,M,startI,startJ,stopI,stopJ,T);
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