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

	unsigned int D = abs(pi-ti) + abs(pj-tj);
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

		temp = pi+1;
		if(!*(map+temp*columns+pj) && steps >= abs(temp-ti) + abs(pj-tj))
			search4way(temp,pj,steps);

		temp = pi-1;
		if(!*(map+temp*columns+pj) && steps >= abs(temp-ti) + abs(pj-tj))
			search4way(temp,pj,steps);

		temp = pj+1;
		if(!*(map+pi*columns+temp) && steps >= abs(pi-ti) + abs(temp-tj))
			search4way(pi,temp,steps);

		temp = pj-1;
		if(!*(map+pi*columns+temp) && steps >= abs(pi-ti) + abs(temp-tj))
			search4way(pi,temp,steps);
	} // end if
	else if(pi == ti && pj == tj)
		++paths;
	return paths;
} // end function count_paths


static void search4way(uint pi , uint pj , uint steps)															// search4way
{
	if(steps)
	{
		uint temp;
		--steps;

		temp = pi+1;
		if(!*(map+temp*columns+pj) && steps >= abs(temp-ti) + abs(pj-tj))
			search4way(temp,pj,steps);

		temp = pi-1;
		if(!*(map+temp*columns+pj) && steps >= abs(temp-ti) + abs(pj-tj))
			search4way(temp,pj,steps);

		temp = pj+1;
		if(!*(map+pi*columns+temp) && steps >= abs(pi-ti) + abs(temp-tj))
			search4way(pi,temp,steps);

		temp = pj-1;
		if(!*(map+pi*columns+temp) && steps >= abs(pi-ti) + abs(temp-tj))
			search4way(pi,temp,steps);
	} // end if
	else if(pi == ti && pj == tj)
		++paths;
} // end function search4way
