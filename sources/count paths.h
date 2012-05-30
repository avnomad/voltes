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

#ifndef COUNT_PATHS_H
#define COUNT_PATHS_H

// #includes
#include <climits>

#ifdef INT_64
#undef UINT_MAX
#define UINT_MAX ULLONG_MAX
// typedefs
typedef unsigned __int64 uint;
#else
// typedefs
typedef unsigned int uint;
#endif


// prototypes
uint count_paths(uint *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps);					// count_paths

#endif // COUNT_PATHS_H