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

#include "count paths.h"
#include "cstdlib"

// shared variables
static bool *map;
static uint columns;
static uint ti,tj;
static uint paths;

static void search4way(uint pi , uint pj , uint steps);															// search4way

uint count_paths(bool *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps)					// count_paths
{
	// look for trivial instance of the problem
	if(*(map+pi*columns+pj))
		return 0;

	unsigned int D = abs((int)(pi-ti)) + abs((int)(pj-tj));
	if(D > steps || (steps-D) & 0x1)
		return 0;
	
	// initialize global variables
	::map = map;
	::columns = columns;
	::ti = ti;
	::tj = tj;
	::paths = 0;

	// commence search
	if(steps)
	{
		uint temp;
		--steps;

		if(steps)
		{
			temp = pi+1;
			if(!*(map+temp*columns+pj) && steps >= (uint)(abs((int)(temp-ti)) + abs((int)(pj-tj))))
				search4way(temp,pj,steps);

			temp = pi-1;
			if(!*(map+temp*columns+pj) && steps >= (uint)(abs((int)(temp-ti)) + abs((int)(pj-tj))))
				search4way(temp,pj,steps);

			temp = pj+1;
			if(!*(map+pi*columns+temp) && steps >= (uint)(abs((int)(pi-ti)) + abs((int)(temp-tj))))
				search4way(pi,temp,steps);

			temp = pj-1;
			if(!*(map+pi*columns+temp) && steps >= (uint)(abs((int)(pi-ti)) + abs((int)(temp-tj))))
				search4way(pi,temp,steps);
		} // end if
		else
		{
			if(pi+1 == ti && pj == tj)
				++paths;
			if(pi-1 == ti && pj == tj)
				++paths;
			if(pi == ti && pj+1 == tj)
				++paths;
			if(pi == ti && pj-1 == tj)
				++paths;
		} // end else
	} // end if
	else if(pi == ti && pj == tj)
		++paths;
	return paths;
} // end function count_paths

	/************************************************************************
	* note that this is not strictly equivalent to the cut leaf 1.			*
	* if the destination is an obstacle the cut leaf 1 will return 0		*
	* while cut leaf 2 will find paths. could have made equivalent though.	*
	************************************************************************/


static void search4way(uint pi , uint pj , uint steps)															// search4way
{	/* steps > 0 (pi,pj) not an obstacle and not too far */
	uint temp;
	--steps;

	if(steps)
	{
		temp = pi+1;
		if(!*(map+temp*columns+pj) && steps >= (uint)(abs((int)(temp-ti)) + abs((int)(pj-tj))))
			search4way(temp,pj,steps);

		temp = pi-1;
		if(!*(map+temp*columns+pj) && steps >= (uint)(abs((int)(temp-ti)) + abs((int)(pj-tj))))
			search4way(temp,pj,steps);

		temp = pj+1;
		if(!*(map+pi*columns+temp) && steps >= (uint)(abs((int)(pi-ti)) + abs((int)(temp-tj))))
			search4way(pi,temp,steps);

		temp = pj-1;
		if(!*(map+pi*columns+temp) && steps >= (uint)(abs((int)(pi-ti)) + abs((int)(temp-tj))))
			search4way(pi,temp,steps);
	} // end if
	else
	{
		if(pi+1 == ti && pj == tj)
			++paths;
		if(pi-1 == ti && pj == tj)
			++paths;
		if(pi == ti && pj+1 == tj)
			++paths;
		if(pi == ti && pj-1 == tj)
			++paths;
	} // end else
} // end function search4way
