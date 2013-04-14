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
#include "stdlib.h"


	/************************************************************************************************
	*																								*
	*	Note: The solution is recursive. But some initialization and tests should be done only once	*
	*	so the count_paths function in fact calls the search4way function to do the actual			*
	*	recursion. The idea is that the number of paths of length s from a square A to a square B	*
	*	is the sum of the numbers of paths of length s-1 from the neighbors of A to B.				*
	*		There are 3	main application-specific ways to avoid redundant computations. First, no	*
	*	instance of the function should be called on a square that is an obstacle. Second, no		*
	*	instance of the	function should be called on a square with a Manhattan distance greater		*
	*	than the number of steps left. Third, when the number of paths for a triple (i,j,s) is		*
	*	computed, it is saved so that the next time we need it, we won't have to compute it again.	*
	*		The first two conditions along with the requirement that no instance of the function	*
	*	should be called outside the bounds of the array, are checked with a single comparison,		*
	*	thanks to a smart initialization of the array. The last condition is the one that makes the	*
	*	solution linear with respect to T.															*
	*		There are also a number of impovements that can be made in recursive functions in		*
	*	general (or recursive functions that call themselves at least twice) and, unfortunately,	*
	*	are not done by (my) compiler. Firstly, arguments that are always passed with no change		*
	*	from the recursive function to its children, should not be copied each time to the stack,	*
	*	but	instead stored in a (static) global variable. In fact, if we were writing in assembly	*
	*	we would probably be able to but these in registers once in the "prelude" function and use	*
	*	them throughout the actual recursion.														*
	*		Secondly, the test for whether the recursion should continue or stop, should be moved	*
	*	from just after the call, to just before it, to avoid a substantial overhead from the		*
	*	function calls, but I won't put a more detailed explanation inside the code.					*
	*		The time complexity should be something like O((N*M-K)*T) (though since I haven't done	*
	*	a strict proof, I can be mistaken and of course there may be a better bound).				*
	*		The memory complexity should be O(N*M*T). It also uses O(1) processors. ;p				*
	*																								*
	************************************************************************************************/


// shared variables to be initialized by count_paths and used by search4way.
static uint *target;	// it's more efficient to save and test a pointer to the target square, than it-s coordinates.
static uint column;	// will be needed to navigate up and down.
static uint D;	// for depth. will be needed to navigate right and left.

// search4way is static since it's part of the implementation of count_paths.
// only 2 arguments and no return value need to be passed on the stack. 
static void search4way(uint *current , uint steps);																// search4way


	/************************************************************************************************
	*	Function:																					*
	*		count_paths																				*
	*	Parameters:																					*
	*		map is the base address of an array initialized as explained in main.					*
	*		columns is the number of columns of that array.											*
	*		pi and pj are the row and column of the starting square.								*
	*		ti and tj are the row and column of the target square.									*
	*		steps is T, the lenght of the paths we are to count. It is also assumed that the 3rd	*
	*		dimension of the array is steps+1. This can be changed by adding an 8th parameter D.	*
	*	Return value:																				*
	*		the number of paths of length steps from (pi,pj) to (ti,tj)								*
	*	Limitations:																				*
	*		steps and the return value cannot be equal to UINT_MAX.									*
	*	Side effects:																				*
	*		any location map[i][j][s] with s != 0 might change to the number of paths of length		*
	*		s from (i,j) to the target.	In fact only a subset of those can change, but anyway.		*
	************************************************************************************************/

uint count_paths(uint *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps)					// count_paths
{
	// look for trivial instance of the problem
	::D = steps+1;	// if p == &map[i][j][s] then p + D == &map[i][j+1][s].
	uint *current = map+(pi*columns+pj)*D;	// address of the current square.

	if(*current > steps || (steps-*current) & 0x1)	// if the Manhattan distance between the current square and  the
		return 0;			// target square is greater than steps, or (steps-*current) is odd, then there are no paths.
	
	// initialize global variables
	::target = map+(ti*columns+tj)*D;	// the address of the target square.
	::column = columns * ::D;	// if p == &map[i][j][s] then p + colunm == &map[i+1][j][s].

	// commence search
	if(steps)	// if steps > 0
	{
		search4way(current,steps);	// call search4way to find the number of paths.
		return *(current+steps);	// return the number of paths.
	} // end if
	else if(current == target)	// if steps == 0 and the current square is the target square
		return 1;	// there is exactly 1 path.
	else	// if steps == 0 and the current square is not the target square
		return 0;	// there are no paths.
} // end function count_paths


	/************************************************************************************************
	*	Function:																					*
	*		search4way																				*
	*	Parameters:																					*
	*		current is the address of the current square.											*
	*		steps is the number of steps left.														*
	*	Return value:																				*
	*		none.																					*
	*	Limitations:																				*
	*		steps cannot be equal to UINT_MAX.														*
	*	Prerequisites:																				*
	*		0 < steps < UINT_MAX. *current <= steps. current pointing to a location in a properly	*
	*		initialized array. *(current+steps) == UINT_MAX (current not visited).					*
	*	Side effects:																				*
	*		*(current+steps) will be the number of paths of length steps from current to target.	*
	*		If map is the array in which current points, then elements map[i][j][s] with 0<s<steps	*
	*		and might also change.																	*
	************************************************************************************************/

static void search4way(uint *current , uint steps)															// search4way
{
	uint *temp;	// temporary variable for the addresses of the neighbours. The optimizer would
				// have created a variable like that anyway but I believe this is clearer too.
	*(current+steps) = 0;	// mark the current (square,steps) pair as visited.
							// (if there are more paths they will be added later)
	--steps;	// the number of steps with which search4way will
				// be called for our neighbours (if it's called).

	if(steps)	// if our neighbours' steps > 0
	{
		temp = current-D;	// for the neighbour to the left.
		if(*temp <= steps)	// if the neighbour is not too far from target and not an obstacle
		{
			if(*(temp+steps) == UINT_MAX)	// if the neighbour has not been visited before
				search4way(temp,steps);	// visit it.
			*(current+steps+1) += *(temp+steps);	// add to our number of paths, those of our neighbour.
		} // end if


		temp = current+D;	// same for the neighbour to the right.
		if(*temp <= steps)
		{
			if(*(temp+steps) == UINT_MAX)
				search4way(temp,steps);
			*(current+steps+1) += *(temp+steps);
		} // end if

		temp = current-column;	// same for the neighbour above.
		if(*temp <= steps)
		{
			if(*(temp+steps) == UINT_MAX)
				search4way(temp,steps);
			*(current+steps+1) += *(temp+steps);
		} // end if

		temp = current+column;	// same for the neighbour below.
		if(*temp <= steps)
		{
			if(*(temp+steps) == UINT_MAX)
				search4way(temp,steps);
			*(current+steps+1) += *(temp+steps);
		} // end if
	} // end if
	else	// if our neighbours' steps == 0
	{	
		if(current-D == target || current+D == target || 
			current-column == target || current+column == target) // if a neighbour is the target.
		{								// (there is only 1 target so only one of these can be true)
			*(current+1) = 1;	// there is exactly 1 path of length 1 from there to the target.
		} // end if				
	} // end else
} // end function search4way
