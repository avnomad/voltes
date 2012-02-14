#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#include <fstream>
using std::ifstream;

#include <cstdlib>
using std::calloc;

#include <gl/glut.h>
#include <color.h>
#include <color/glColor.h>
#include <color/namings/double precision colors.h>

#include <Graphics/TablePainter.h>
#include "count paths.h"

// prototypes
void intThrower(){throw 0;}


int main(int argc , char **argv)
{
	// open input stream
	ifstream in("../../../sample inputs/test1.txt");
	if(!in)
	{
		cerr << "cannot open file!\n";
		return 0;
	}

	// variables to store the input
	int N,M,T;
	int startX,startY,stopX,stopY;
	int K;
	int tempX,tempY;
	bool *table;
	bool *p;

	in >> N >> M >> T >> startX >> startY >> stopX >> stopY >> K;	// read parameters from input.
	N += 2 , M += 2;	// adjust the number of rows and columns to accommodate the border.

	table = (bool*)calloc(N*M,sizeof(bool));	// allocate space for the table. initialize with zeros.
	while(K--)
	{
		in >> tempX >> tempY;	// read obstacle coordinates.
		*(table + M*tempX + tempY) = true;	// register obstacle
	} // end while

	// generate border
	K = M;
	p = table;
	while(K--)
		*p++ = true;
	K = N-1;
	while(--K)
	{
		*p = true;
		p += M-1;
		*p++ = true;
	} // end while
	K = M;
	while(K--)
		*p++ = true;

	// count paths
	cout << count_paths(table,M,startX,startY,stopX,stopY,T) << endl;

	// initialize glut
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(10*M+20,10*N+20);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("pame voltes");

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10,10*M+10,-10*(int)N-10,10);	// set clipping window
	glClearColor(0,0,0,0);	// set clear color.

	glutDisplayFunc(intThrower);
	try
	{
		glutMainLoop();
	}
	catch(int){}

	TablePainter<bool> painter(gold,black,green,M);
	// main loop
	while(1)
	{
		glClear(GL_COLOR_BUFFER_BIT);	// clear buffer

		painter.display(table,table+N*M);
		glColor(lime);
		glRecti(10*startY,-10*startX,10*startY+10,-10*startX-10);
		glColor(red);
		glRecti(10*stopY,-10*stopX,10*stopY+10,-10*stopX-10);

		glutSwapBuffers();
	} // end while

	free(table);
	return 0;
} // end function main