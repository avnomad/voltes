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

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#include <fstream>
using std::ifstream;

#include <climits>

#include <gl/glut.h>
#include <color.h>
#include <color/glColor.h>
#include <color/namings/double precision colors.h>

#include <Graphics/TablePainter.h>
#include "count paths.h"

// variables shared by main and display
uint N,M,T;
uint startI,startJ,stopI,stopJ;
uint *table;
uint D;
TablePainter<bool> *painter;

// this class is specific to this program!
// adapts a standard pointer that points to a memory block formated according to 
// this program's format to an iterator suitable for use with TablePainter::display
template<typename T>
class TableIterator	// does not assume ownership of pointed object!
{
	T *iPointer;
	int iElementsToProgress;

public:

	TableIterator(T *pointer, int elementsToProgress)
		:iPointer(pointer),iElementsToProgress(elementsToProgress)
	{
		// empty body
	} // end TableIterator constructor

	bool operator*() const	// <-- !!!
	{
		return *iPointer == UINT_MAX;
	} // end function operator*

	bool operator==(const TableIterator &right)
	{
		return iPointer == right.iPointer;
	} // end function operator==

	bool operator!=(const TableIterator &right)
	{
		return !(*this==right);
	} // end function operator!=

	TableIterator &operator++()
	{
		iPointer += iElementsToProgress;
		return *this;
	} // end function operator++

}; // end class TableIterator


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	painter->display(TableIterator<uint>(table,D),TableIterator<uint>(table+N*M*D,D));
	glColor(lime);
	glRecti(10*startJ,-10*startI,10*startJ+10,-10*startI-10);
	glColor(red);
	glRecti(10*stopJ,-10*stopI,10*stopJ+10,-10*stopI-10);

	glutPostRedisplay();
	glutSwapBuffers();
} // end function display


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	} // end switch
} // end function keyboard


void reshape(int w, int h)
{
	glViewport(0,0,w,h);
} // end function reshape


int main(int argc , char **argv)
{
	// open input stream
	ifstream in("../../../sample inputs/test2.txt");
	if(!in)
	{
		cerr << "cannot open input file!\n";
		return 0;
	}

	// variables to store the input
	uint K;
	uint tempI,tempJ;
	uint *p,*q,*sp,*sq;
	uint distanceBase,distance;

	// read from input
	in >> N >> M >> T >> startI >> startJ >> stopI >> stopJ >> K;	// read parameters from input.
	// create the table
	N += 2 , M += 2;	// adjust the number of rows and columns to accommodate the border.
	D = T+1;
	table = new uint[N*M*D];	// allocate space for the table.
	memset(table,UINT_MAX,N*M*D*sizeof(uint));	// fill the table with a special value.

		// initialize distances to destination
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

	while(K--)	// for each obstacle
	{
		in >> tempI >> tempJ;	// read obstacle coordinates.
		*(table + (M*tempI + tempJ)*D) = UINT_MAX;	// register obstacle
	} // end while


	// count paths
	cout << count_paths(table,M,startI,startJ,stopI,stopJ,T) << endl;

	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(10*M+20,10*N+20);
	glutInitWindowPosition(0,0);
	glutCreateWindow("pame voltes");

	// OpenGL initialization
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10,10*M+10,-10*(int)N-10,10);	// set clipping window

	// application initialization
	painter = new TablePainter<bool>(gold,black,green,M);

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();

	// clean-up
	delete painter;
	free(table);
	return 0;
} // end function main