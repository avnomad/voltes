#include "count paths.h"
#include "cstdlib"

// shared variables
static uint *target;
static uint columns;
static uint paths;

static void search4way(uint *current , uint steps);															// search4way

uint count_paths(uint *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps)					// count_paths
{	/* now steps must be less than UINT_MAX which is of course no problem almost all cases. */
	// look for trivial instance of the problem
	uint *current = map+pi*columns+pj;
	uint D = *current;
	if(D > steps || (steps-D) & 0x1)
		return 0;
	
	// initialize global variables
	::target = map+ti*columns+tj;
	::columns = columns;
	::paths = 0;

	// commence search
	if(steps)
	{
		uint *temp;
		--steps;

		if(steps)
		{
			temp = current-1;
			if(*temp <= steps)
				search4way(temp,steps);

			temp = current+1;
			if(*temp <= steps)
				search4way(temp,steps);

			temp = current-columns;
			if(*temp <= steps)
				search4way(temp,steps);

			temp = current+columns;
			if(*temp <= steps)
				search4way(temp,steps);
		} // end if
		else
		{
			if(current-1 == target)
				++paths;
			if(current+1 == target)
				++paths;
			if(current-columns == target)
				++paths;
			if(current+columns == target)
				++paths;
		} // end else
	} // end if
	else if(current == target)
		++paths;
	return paths;
} // end function count_paths


static void search4way(uint *current , uint steps)															// search4way
{	/* 0 < steps < UINT_MAX *current not an obstacle and not too far */
	uint *temp;
	--steps;

	if(steps)
	{
		temp = current-1;
		if(*temp <= steps)
			search4way(temp,steps);

		temp = current+1;
		if(*temp <= steps)
			search4way(temp,steps);

		temp = current-columns;
		if(*temp <= steps)
			search4way(temp,steps);

		temp = current+columns;
		if(*temp <= steps)
			search4way(temp,steps);
	} // end if
	else
	{
		if(current-1 == target)
			++paths;
		if(current+1 == target)
			++paths;
		if(current-columns == target)
			++paths;
		if(current+columns == target)
			++paths;
	} // end else
} // end function search4way
