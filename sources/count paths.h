#ifndef COUNT_PATHS_H
#define COUNT_PATHS_H

// typedefs
typedef unsigned int uint;

// types
struct Node
{
	uint dist;
	uint *paths;
}; // end struct Node


// prototypes
uint count_paths(Node *map , uint columns , uint pi , uint pj , uint ti , uint tj , uint steps);					// count_paths

#endif // COUNT_PATHS_H