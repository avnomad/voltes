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