#include "count paths.h"
#include "cstdlib"

// shared variables
static bool *map;
static uint columns;
static uint ti,tj;

static uint search4way(uint pi , uint pj , uint steps);															// search4way

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

	// commence search
	if(steps--)
		return search4way(pi+1,pj,steps) + search4way(pi,pj+1,steps) + 
			search4way(pi-1,pj,steps) + search4way(pi,pj-1,steps);
	else
		return (pi == ti && pj == tj)?1:0;
} // end function count_paths


static uint search4way(uint pi , uint pj , uint steps)															// search4way
{
	if(*(map+pi*columns+pj) || steps < (uint)(abs((int)(pi-ti)) + abs((int)(pj-tj))))
		return 0;
	if(steps--)
		return search4way(pi+1,pj,steps) + search4way(pi,pj+1,steps) + 
			search4way(pi-1,pj,steps) + search4way(pi,pj-1,steps);
	else
		return (pi == ti && pj == tj)?1:0;
} // end function search4way
