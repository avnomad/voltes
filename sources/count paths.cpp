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
static Node *target;
static uint columns;

static void search4way(Node *current , uint steps);															// search4way

uint count_paths(Node *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps)					// count_paths
{	/* now steps must be less than UINT_MAX which is of course no problem almost all cases. */
	// look for trivial instance of the problem
	Node *current = map+pi*columns+pj;
	uint D = current->dist;
	if(D > steps || (steps-D) & 0x1)
		return 0;
	
	// initialize global variables
	::target = map+ti*columns+tj;
	::columns = columns;

	// commence search
	if(steps)
	{
		Node *temp;
		current->paths[steps] = 0;	// mark the (node,step) for entrance
		--steps;

		if(steps)
		{
			temp = current-1;
			if(temp->dist <= steps)
			{
				if(temp->paths[steps] == UINT_MAX)
					search4way(temp,steps);
				current->paths[steps+1] += temp->paths[steps];
			} // end if


			temp = current+1;
			if(temp->dist <= steps)
			{
				if(temp->paths[steps] == UINT_MAX)
					search4way(temp,steps);
				current->paths[steps+1] += temp->paths[steps];
			} // end if

			temp = current-columns;
			if(temp->dist <= steps)
			{
				if(temp->paths[steps] == UINT_MAX)
					search4way(temp,steps);
				current->paths[steps+1] += temp->paths[steps];
			} // end if

			temp = current+columns;
			if(temp->dist <= steps)
			{
				if(temp->paths[steps] == UINT_MAX)
					search4way(temp,steps);
				current->paths[steps+1] += temp->paths[steps];
			} // end if
		} // end if
		else
		{
			if(current-1 == target || current+1 == target || // there is only 1 target so only
				current-columns == target || current+columns == target) // one of these can be true
			{
				current->paths[1] = 1;
			} // end if				
		} // end else
		return current->paths[steps+1];
	} // end if
	else if(current == target)
	{
		current->paths[steps] = 1;
		return current->paths[steps];
	} // end else
} // end function count_paths


static void search4way(Node *current , uint steps)															// search4way
{	/* 0 < steps < UINT_MAX *current not an obstacle and not too far */
	Node *temp;
	current->paths[steps] = 0;	// mark the (node,step) for entrance
	--steps;

	if(steps)
	{
		temp = current-1;
		if(temp->dist <= steps)
		{
			if(temp->paths[steps] == UINT_MAX)
				search4way(temp,steps);
			current->paths[steps+1] += temp->paths[steps];
		} // end if


		temp = current+1;
		if(temp->dist <= steps)
		{
			if(temp->paths[steps] == UINT_MAX)
				search4way(temp,steps);
			current->paths[steps+1] += temp->paths[steps];
		} // end if

		temp = current-columns;
		if(temp->dist <= steps)
		{
			if(temp->paths[steps] == UINT_MAX)
				search4way(temp,steps);
			current->paths[steps+1] += temp->paths[steps];
		} // end if

		temp = current+columns;
		if(temp->dist <= steps)
		{
			if(temp->paths[steps] == UINT_MAX)
				search4way(temp,steps);
			current->paths[steps+1] += temp->paths[steps];
		} // end if
	} // end if
	else
	{
		if(current-1 == target || current+1 == target || // there is only 1 target so only
			current-columns == target || current+columns == target) // one of these can be true
		{
			current->paths[1] = 1;
		} // end if				
	} // end else
} // end function search4way
