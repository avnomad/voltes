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

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "count paths.h"


int main(int argc , char **argv)
{
	// variables to store the input
	uint N,M,T;
	uint startI,startJ,stopI,stopJ;
	uint K;
	uint tempI,tempJ;
	uint *table;
	uint *p,*q,*sp,*sq;
	uint distanceBase,distance;
	uint D;

	scanf("%u%u%u%u%u%u%u%u",&N,&M,&T,&startI,&startJ,&stopI,&stopJ,&K);	/* read parameters from input. */


	/********************/
	/* create the table */
	/********************/

	N += 2 , M += 2;	/* adjust the number of rows and columns to accommodate the border. */
	D = T+1;
	table = (uint*)malloc(N*M*D*sizeof(uint));	/* allocate space for the table. */

	// initialize distances from destination
	tempI = M*D;
	tempJ = tempI-D;

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


	/******************/
	/* read obstacles */
	/******************/

	while(K--)	// for each obstacle
	{
		scanf("%u%u",&tempI,&tempJ);	// read obstacle coordinates.
		*(table + (M*tempI + tempJ)*D) = UINT_MAX;	// register obstacle
	} // end while


	/*******************/
	/* generate border */
	/*******************/

	K = M;
	p = table;
	while(K--)
	{
		*p = UINT_MAX;
		p += D;
	} /* end while */
	K = N-1;
	while(--K)
	{
		*p = UINT_MAX;
		p += (M-1)*D;
		*p = UINT_MAX;
		p += D;
	} /* end while */
	K = M;
	while(K--)
	{
		*p = UINT_MAX;
		p += D;
	} /* end while */


	/********************/
	/* initialize lists */
	/********************/

	tempI = M*D;
	tempJ = tempI-D;
	sp = table+(N-1)*tempI;
	for(p = table + tempI ; p < sp ; p += tempI)
	{
		sq = p + tempJ;
		for(q = p + D ; q < sq ; q += D)
			if(*q != UINT_MAX)
				for(uint c = 1 ; c <= T ; ++c)
					*(q + c) = UINT_MAX;
	} // end p for


	/***************/
	/* count paths */
	/***************/

	uint paths = count_paths(table,M,startI,startJ,stopI,stopJ,T);

	printf("%u\n",paths);	// print result in a line by it's own.

	free(table);	// free memory

	return 0;
} // end function main