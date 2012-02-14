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

// variables shared by main and display
int N,M,T;
int startX,startY,stopX,stopY;
bool *table;
TablePainter<bool> *painter;


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	painter->display(table,table+N*M);
	glColor(lime);
	glRecti(10*startY,-10*startX,10*startY+10,-10*startX-10);
	glColor(red);
	glRecti(10*stopY,-10*stopX,10*stopY+10,-10*stopX-10);

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
	int K;
	int tempX,tempY;
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