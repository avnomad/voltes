// #includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "count paths.h"

	/************************************************************************************************
	*																								*
	*	Note: 																						*
	*		The work is distributed as follows: the main function undertakes the responsibility to	*
	*	read the description of the problem from the standard input and write the solution to the	*
	*	standard output, as well as to create and initialize an array to pass on to the count_paths	*
	*	function which will do the actual solving.													*
	*																								*
	*	Array usage convention:																		*
	*		The array will be allocated dynamically and used as if it were a 3-dimensional array	*
	*	table[N+2][M+2][T+1]. Each individual 1-dimensional array table[i][j] will represent a		*
	*	square in the plateau. For each i and j, table[i][j][0] will be the Manhattan distance		*
	*	between the square (i,j) and the target square, if the square is not an obstacle, or		*
	*	infinite if it is an obstacle. Of course we can't use infinite with integral types, so we	*
	*	use the maximum unsigned value instead.														*
	*		We use an (N+2)x(M+2) array instead of an NxM to accommodate a border, i.e. we fill the	*
	*	first and last lines and columns with obstacles so as to check for obstacles and the end of	*
	*	the array in a uniform way. In fact, combined with the above convention, this merges 3		*
	*	tests to 1, but we will see that in the implementation of count_paths.							*
	*		The rest of the 1-dimentional array table[i][j] should be initialized to the maximum	*
	*	unsigned value if the square is not an obstacle and can have any values if it is.			*
	*		The following is not needed to be known in main, but count_paths, uses table[i][j][s]	*
	*	to store the number of paths of length s (steps) from square (i,j) to the target square		*
	*	and considers that this number is not known if table[i][j][s] equals the maximum unsigned	*
	*	value and known (and equal to table[i][j][s]) otherwise.									*
	*																								*
	************************************************************************************************/


int main()
{
	// variable declarations
	uint N,M,T;	// # of rows, columns and steps
	uint startI,startJ,stopI,stopJ;	// the source and destination row and column.
	uint K;	// the number of obstacles
	uint tempI,tempJ;	// to read the row and colunm of and obstacle and for generic temporary use.
	uint *table;	// will be used to hold the base address of an array.
	uint *p,*q,*sp,*sq;	// for pointer based loops. 's' is for "stop"
	uint distanceBase,distance;	// for the initialization of the array.
	uint D;	// will hold T+1.

	scanf("%u%u%u%u%u%u%u%u",&N,&M,&T,&startI,&startJ,&stopI,&stopJ,&K);	// read parameters from input.
																			// the obstacles will be read later.


		/*******************
		* create the table *
		*******************/

	N += 2 , M += 2;	// adjust the number of rows and columns to accommodate the border.
						// (the original values of N and M won't be needed later.)
	D = T+1;	// the original value of T will be needed again, so use another variable for T+1.

	table = (uint*)malloc(N*M*D*sizeof(uint));	// allocate space for the table.
	memset(table,UINT_MAX,N*M*D*sizeof(uint));	// initialize the whole table to the maximum unsigned value.

	tempI = M*D;	// if p points to table[i][j][s] then p + tempI points to table[i+1][j][s].
	tempJ = tempI-D;	// if p points to table[i][0][0] then p + tempJ points to table[i][M-1][0].

	/************************************************************************************************
	*																								*
	*	Note: initialization of the elements table[i][j][0], 0<i<N-1 , 0<i<M-1 with the Manhattan	*
	*	distances. Initialization is done from the inside out, thus the dual for loops with a dual	*
	*	for loop each. distanceBase holds the starting distance for the line, while distance holds	*
	*	the distance of the particular square. The loops are pointer based because the compiler		*
	*	didn't optimize well for indexed loops with accesses of the form *(table + (M*i+j)*D + 0).	*
	*																								*
	************************************************************************************************/

	distanceBase = 0;
	for(p = table+tempI*stopI ; p > table ; p -= tempI)
	{
		distance = distanceBase;
		for(q = p + stopJ*D ; q > p ; q -= D)
			*q = distance++;
		distance = ++distanceBase;
		sq = p + tempJ;
		for(q = p + stopJ*D+D ; q < sq ; q += D)
			*q = distance++;
	} // end p for

	distanceBase = 1;
	sp = table+(N-1)*tempI;
	for(p = table+tempI*stopI+tempI ; p < sp ; p += tempI)
	{
		distance = distanceBase;
		for(q = p + stopJ*D ; q > p ; q -= D)
			*q = distance++;
		distance = ++distanceBase;
		sq = p + tempJ;
		for(q = p + stopJ*D+D ; q < sq ; q += D)
			*q = distance++;
	} // end p for


		/*****************
		* read obstacles *
		*****************/

	while(K--)	// while there is another obstacle to read,
	{
		scanf("%u%u",&tempI,&tempJ);	// read the obstacle coordinates.
		*(table + (M*tempI + tempJ)*D) = UINT_MAX;	// register the obstacle.
	} // end while


		/**************
		* count paths *
		**************/

	uint paths = count_paths(table,M,startI,startJ,stopI,stopJ,T);	// count paths.

	printf("%u\n",paths);	// print result in a line by its own.

	free(table);	// free memory.

	return 0;
} // end function main