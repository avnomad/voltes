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
	int N,M,T;
	int startX,startY,stopX,stopY;
	int K;
	int tempX,tempY;
	bool *table;
	bool *p;
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
		in >> N >> M >> T >> startX >> startY >> stopX >> stopY >> K;	// read parameters from input.
		N += 2 , M += 2;	// adjust the number of rows and columns to accommodate the border.

		table = (bool*)calloc(N*M,sizeof(bool));	// allocate space for the table. initialize with zeros.
		while(K--)	// for each obstacle
		{
			in >> tempX >> tempY;	// read obstacle coordinates.
			*(table + M*tempX + tempY) = true;	// register obstacle
		} // end while

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

		// count paths
		int paths = count_paths(table,M,startX,startY,stopX,stopY,T);

		// calculate elapsed time
		t = CPUclock::currentTime() - t;

		// output results
		cout << paths << endl;
		cout << t << CPUclock::getUnit() << endl;
		out << t << endl;
		free(table);
		in.close();
	} // end for


	system("PAUSE");
	return 0;
} // end function main