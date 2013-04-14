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


uint count_paths(bool *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps)					// count_paths
{
	// look for trivial instance of the problem
	if(*(map+pi*columns+pj) || steps < abs((int)(pi-ti)) + abs((int)(pj-tj)))
		return 0;
	
	// commence search
	if(steps--)
		return count_paths(map,columns,pi+1,pj,ti,tj,steps) + count_paths(map,columns,pi,pj+1,ti,tj,steps) + 
			count_paths(map,columns,pi-1,pj,ti,tj,steps) + count_paths(map,columns,pi,pj-1,ti,tj,steps);
	else
		return (pi == ti && pj == tj)?1:0;
} // end function count_paths
