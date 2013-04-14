//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
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
static uint *target;
static uint columns;
static uint D;	// depth, or something :)

static void search4way(uint *current , uint steps);															// search4way

uint count_paths(uint *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps)					// count_paths
{	/* now steps must be less than UINT_MAX which is of course no problem almost all cases. */
	// look for trivial instance of the problem
	::D = steps+1;
	uint *current = map+(pi*columns+pj)*D;
	uint dist = *current;
	if(dist > steps || (steps-dist) & 0x1)
		return 0;
	
	// initialize global variables
	::target = map+(ti*columns+tj)*D;
	::columns = columns;

	// commence search
	if(steps)
	{
		uint *temp;
		*(current+steps) = 0;	// mark the (node,step) for entrance
		--steps;

		if(steps)
		{
			temp = current-D;
			if(*temp <= steps)
			{
				if(*(temp+steps) == UINT_MAX)
					search4way(temp,steps);
				*(current+steps+1) += *(temp+steps);
			} // end if


			temp = current+D;
			if(*temp <= steps)
			{
				if(*(temp+steps) == UINT_MAX)
					search4way(temp,steps);
				*(current+steps+1) += *(temp+steps);
			} // end if

			temp = current-columns*D;
			if(*temp <= steps)
			{
				if(*(temp+steps) == UINT_MAX)
					search4way(temp,steps);
				*(current+steps+1) += *(temp+steps);
			} // end if

			temp = current+columns*D;
			if(*temp <= steps)
			{
				if(*(temp+steps) == UINT_MAX)
					search4way(temp,steps);
				*(current+steps+1) += *(temp+steps);
			} // end if
		} // end if
		else
		{
			if(current-D == target || current+D == target || // there is only 1 target so only
				current-columns*D == target || current+columns*D == target) // one of these can be true
			{
				*(current+1) = 1;
			} // end if				
		} // end else
		return *(current+steps+1);
	} // end if
	else if(current == target)
	{
		//*(current+0) = 1;
		//return *(current+0);
		return 1;
	} // end else if
	else
		return 0;
} // end function count_paths


static void search4way(uint *current , uint steps)															// search4way
{	/* 0 < steps < UINT_MAX *current not an obstacle and not too far */
	uint *temp;
	*(current+steps) = 0;	// mark the (node,step) for entrance
	--steps;

	if(steps)
	{
		temp = current-D;
		if(*temp <= steps)
		{
			if(*(temp+steps) == UINT_MAX)
				search4way(temp,steps);
			*(current+steps+1) += *(temp+steps);
		} // end if


		temp = current+D;
		if(*temp <= steps)
		{
			if(*(temp+steps) == UINT_MAX)
				search4way(temp,steps);
			*(current+steps+1) += *(temp+steps);
		} // end if

		temp = current-columns*D;
		if(*temp <= steps)
		{
			if(*(temp+steps) == UINT_MAX)
				search4way(temp,steps);
			*(current+steps+1) += *(temp+steps);
		} // end if

		temp = current+columns*D;
		if(*temp <= steps)
		{
			if(*(temp+steps) == UINT_MAX)
				search4way(temp,steps);
			*(current+steps+1) += *(temp+steps);
		} // end if
	} // end if
	else
	{
		if(current-D == target || current+D == target || // there is only 1 target so only
			current-columns*D == target || current+columns*D == target) // one of these can be true
		{
			*(current+1) = 1;
		} // end if				
	} // end else
} // end function search4way
