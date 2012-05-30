//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of voltes.
 *
 *	voltes is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	voltes is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with voltes.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;

#include <cstdlib>
using std::calloc;

#include <climits>

#include <CPU clock.h>
#include "count paths.h"


int main(int argc , char **argv)
{
	ifstream in;

	// open output stream
	ofstream out("../stats.txt");
	if(!out)
	{
		cerr << "cannot open output file!\n";
		return 0;
	}

	// variables to store the input
	uint N,M,T;
	uint startI,startJ,stopI,stopJ;
	uint K;
	uint tempI,tempJ;
	uint *table;
	uint *p;
	uint distanceBase,distance;
	std::string name("../../../sample inputs/test");

	// for each input file
	for(int c = 1 ; c <= 4 ; ++c)
	{
		// open input stream
		in.open((name+(char)('0'+c)+".txt").c_str());
		if(!in)
		{
			cerr << "cannot open input file!\n";
			return 0;
		}
		in.clear();

		// store current time
		double t = CPUclock::currentTime();

		// read from input
		in >> N >> M >> T >> startI >> startJ >> stopI >> stopJ >> K;	// read parameters from input.
		N += 2 , M += 2;	// adjust the number of rows and columns to accommodate the border.

		table = new uint[N*M];	// allocate space for the table.

		// initialize distances from destination
		distanceBase = 0;
		for(tempI = stopI ; tempI > 0 ; --tempI)
		{
			distance = distanceBase;
			for(tempJ = stopJ ; tempJ > 0 ; --tempJ)
				*(table + M*tempI + tempJ) = distance++;
			distance = ++distanceBase;
			for(tempJ = stopJ+1 ; tempJ <=  M-2 ; tempJ++)
				*(table + M*tempI + tempJ) = distance++;
		} // end first outer for

		distanceBase = 1;
		for(tempI = stopI+1 ; tempI <=  N-2 ; ++tempI)
		{
			distance = distanceBase;
			for(tempJ = stopJ ; tempJ > 0 ; --tempJ)
				*(table + M*tempI + tempJ) = distance++;
			distance = ++distanceBase;
			for(tempJ = stopJ+1 ; tempJ <=  M-2 ; tempJ++)
				*(table + M*tempI + tempJ) = distance++;
		} // end second outer for

		while(K--)	// for each obstacle
		{
			in >> tempI >> tempJ;	// read obstacle coordinates.
			*(table + M*tempI + tempJ) = UINT_MAX;	// register obstacle
		} // end while

		// generate border
		K = M;
		p = table;
		while(K--)
			*p++ = UINT_MAX;
		K = N-1;
		while(--K)
		{
			*p = UINT_MAX;
			p += M-1;
			*p++ = UINT_MAX;
		} // end while
		K = M;
		while(K--)
			*p++ = UINT_MAX;

		// count paths
		int paths = count_paths(table,M,startI,startJ,stopI,stopJ,T);

		// calculate elapsed time
		t = CPUclock::currentTime() - t;

		// output results
		cout << paths  << endl;
		cout << t << CPUclock::getUnit() << endl;
		out << t << endl;
		delete table;
		in.close();
	} // end for


	system("PAUSE");
	return 0;
} // end function main