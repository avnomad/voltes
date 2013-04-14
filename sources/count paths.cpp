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
static uint column;
static uint D;	// depth, or something :)
static uint steps;
static uint *current;

static void search4way();															// search4way

uint count_paths(uint *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint T)					// count_paths
{	/* now steps must be less than UINT_MAX which is of course no problem almost all cases. */
	// look for trivial instance of the problem
	steps = T;
	::D = steps+1;
	current = map+(pi*columns+pj)*D;
	uint dist = *current;
	if(dist > steps || (steps-dist) & 0x1)
		return 0;
	
	// initialize global variables
	::target = map+(ti*columns+tj)*D;
	::column = columns*::D;

	// commence search
	if(steps)
	{
		*(current+steps) = 0;	// mark the (node,step) for entrance
		--steps;

		if(steps)
		{
			current -= D;
			if(*current <= steps)
			{
				if(*(current+steps) == UINT_MAX)
					search4way();
				*(current+steps+D+1) += *(current+steps);
			} // end if


			current += D << 1;
			if(*current <= steps)
			{
				if(*(current+steps) == UINT_MAX)
					search4way();
				*(current+steps-D+1) += *(current+steps);
			} // end if

			current -= D;
			current -= column;
			if(*current <= steps)
			{
				if(*(current+steps) == UINT_MAX)
					search4way();
				*(current+steps+column+1) += *(current+steps);
			} // end if

			current += column << 1;
			if(*current <= steps)
			{
				if(*(current+steps) == UINT_MAX)
					search4way();
				*(current+steps-column+1) += *(current+steps);
			} // end if

			current -= column;
		} // end if
		else
		{
			if(current-D == target || current+D == target || // there is only 1 target so only
				current-column == target || current+column == target) // one of these can be true
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


static void search4way()															// search4way
{	/* 0 < steps < UINT_MAX *current not an obstacle and not too far */
	*(current+steps) = 0;	// mark the (node,step) for entrance
	--steps;

	if(steps)
	{
		current -= D;
		if(*current <= steps)
		{
			if(*(current+steps) == UINT_MAX)
				search4way();
			*(current+steps+D+1) += *(current+steps);
		} // end if


		current += D << 1;
		if(*current <= steps)
		{
			if(*(current+steps) == UINT_MAX)
				search4way();
			*(current+steps-D+1) += *(current+steps);
		} // end if

		current -= D;
		current -= column;
		if(*current <= steps)
		{
			if(*(current+steps) == UINT_MAX)
				search4way();
			*(current+steps+column+1) += *(current+steps);
		} // end if

		current += column << 1;
		if(*current <= steps)
		{
			if(*(current+steps) == UINT_MAX)
				search4way();
			*(current+steps-column+1) += *(current+steps);
		} // end if

		current -= column;
	} // end if
	else
	{
		if(current-D == target || current+D == target || // there is only 1 target so only
			current-column == target || current+column == target) // one of these can be true
		{
			*(current+1) = 1;
		} // end if				
	} // end else
	++steps;
} // end function search4way
