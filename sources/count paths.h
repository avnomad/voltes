#ifndef COUNT_PATHS_H
#define COUNT_PATHS_H

// typedefs
typedef unsigned int uint;	// uint can be e.g. unsigned long long int, but UINT_MAX should
							// be substituted with an appropriate #define for the new type

// prototypes
uint count_paths(uint *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps);					// count_paths

#endif // COUNT_PATHS_H