#include "count paths.h"
#include "cstdlib"


static uint search4way(uint pi , uint pj , uint steps);															// search4way

uint count_paths(bool *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps)					// count_paths
{
	// look for trivial instance of the problem
	if(*(map+pi*columns+pj) || steps < abs(pi-ti) + abs(pj-tj))
		return 0;
	
	// commence search
	if(steps--)
		return count_paths(map,columns,pi+1,pj,ti,tj,steps) + count_paths(map,columns,pi,pj+1,ti,tj,steps) + 
			count_paths(map,columns,pi-1,pj,ti,tj,steps) + count_paths(map,columns,pi,pj-1,ti,tj,steps);
	else
		return (pi == ti && pj == tj)?1:0;
} // end function count_paths
