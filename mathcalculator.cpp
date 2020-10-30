#include<alloc.h>     // // Declares memory management functions (allocation,
	     // deallocation, etc.).
#include<assert.h>     // Defines the assert debugging macro.
#include<bcd.h>        // Declares the C++ class bcd and the overloaded operators for
	     // bcd and bcd math functions.
#include<bios.h>       // Declares various functions used in calling IBM-PC ROM BIOS
	     // routines.
#include<complex.h>    // Declares the C++ complex math functions.
#include<conio.h>      // Declares various functions used in calling the DOS console
	     // I/O routines.
#include<ctype.h>      // Contains information used by the character classification
	     // and character conversion macros.
#include<dir.h>        // Contains structures, macros, and functions for working with
	     // directories and path names.
#include<direct.h>     // Defines structures, macros, and functions for working with
	     // directories and path names.
#include<dirent.h>     // Declares functions and structures for POSIX directory
	     // operations.
#include<dos.h>        // Defines various constants and gives declarations needed for
	     // DOS and 8086-specific calls.
#include<errno.h>      // Defines constant mnemonics for the error codes.
#include<fcntl.h>      // Defines symbolic constants used in connection with the
	     // library routine open.
#include<float.h>      // Contains parameters for floating-point routines.
#include<fstream.h>    // Declares the C++ stream classes that support file input and
	     // output.
#include<generic.h>    // Contains macros for generic class declarations.
#include<graphics.h>   // Declares prototypes for the graphics functions.
#include<io.h>         // Contains structures and declarations for low-level
	     // input/output routines.
#include<iomanip.h>    // Declares the C++ streams I/O manipulators and contains
	     // macros for creating parameterized manipulators.
#include<iostream.h>   // Declares the basic C++ (version 2.0) streams (I/O) routines.
#include<limits.h>     // Contains environmental parameters, information about
	     // compile-time limitations, and ranges of integral quantities.
#include<locale.h>     // Declares functions that provide country- and language-
	     // specific information.
#include<malloc.h>     // Memory management functions and variables.
#include<math.h>       // Declares prototypes for the math functions, defines the
	     // macro HUGE_VAL, and declares the exception structure used by
	     // matherr.
#include<mem.h>        // Declares the memory-manipulation functions. (Many of these
	     // are also defined in string.h>.)
#include<memory.h>     // Memory manipulation functions.
#include<new.h>        // Access to operator new and newhandler.
#include<process.h>    // Contains structures and declarations for the spawn... and
	     // exec... functions.
#include<search.h>     // Declares functions for searching and sorting.
#include<setjmp.h>     // Defines a type used by longjmp and setjmp.
#include<share.h>      // Defines parameters used in functions that use file-sharing.
#include<signal.h>     // Defines constants and declarations for signal and raise.
//#include<stdarg.h>     // Defines macros used for reading the argument list in
	     // functions declared to accept a variable number of arguments.
#include<stddef.h>     // Defines several common data types and macros.
#include<stdio.h>      // Defines types and macros needed for the Standard I/O Package
	     // defined in Kernighan and Ritchie and extended under UNIX
	     // System V. Defines the standard I/O predefined streams stdin,
	     // stdout, stdprn, and stderr, and declares stream-level I/O
	     // routines.
#include<stdiostr.h>   // Declares the C++ (version 2.0) stream classes for use with
	     // stdio FILE structures.
#include<stdlib.h>     // Declares several commonly used routines: conversion
	     // routines, search/sort routines, and other miscellany.
//#include<stream.h>     // Declares the C++ (version 1.2) streams (I/O) routines.
#include<string.h>     // Declares several string- and memory-manipulation routines.
#include<strstrea.h>   // Declares the C++ stream classes for use with byte arrays in
	     // memory.
//#include<sys\locking.h>// Definitions for mode parameter of locking function.
#include<sys\stat.h>   // Defines symbolic constants used for opening and creating
             // files.
#include<sys\timeb.h>  // Declares the function ftime and the structure timeb that
             // ftime returns.
#include<sys\types.h>  // Declares the type time_t used with time functions.
#include<time.h>       // Defines a structure filled in by the time-conversion
             // routines, and a type used by other time routines; also
             // provides prototypes for these routines.
#include<utime.h>      // Declares the functions utime and the structure utimbuf
#include<values.h>     // Defines important constants, including machine dependencies;
             // provided for UNIX System V compatibility.
#include<varargs.h>    //Defines old style marcos for processing variable argumnet
             // lists.  Superceded by stdarg.h>

int temp=0,no;
char character,problem[80];
union REGS i,o;
struct SREGS s;
char c[32]=	{
			/*0xfff,0x8001,0xfff,0x8001,
			0x4002,0x2004,0x1008,0x0240,
			0x0240,0x0810,0x2004,0x4002,
			0x8001,0xfff,0x8001,0xfff*/
			0xe1ff,0xe1ff,0xe1ff,0xe1ff,0xe1ff,0x0000,
			0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
			0x0000,0x0000,0x0000,0x0000,0x1e00,0x1200,
			0x1200,0x1200,0x13ff,0x1249,0x1249,0xf249,
			0x9001,0x9001,0x9001,0x8001,0x8001,0x8001,
			0xffff,0x0000,
		};
#define ON 1
#define OFF 0

void cursor(int);
/*UI*/
void tabspace()
{
	moveto(getx()+textwidth("HELLOHOWAREYOU"),gety());
}
void newline()
{
	moveto(20,gety()+textheight("A"));
}
/*UI End*/
void getgrstring(char *inputstring)
{
	int stringindex=0,oldcolor;
	char ch,outstring[2];
	int xval[255];

	outstring[1]=0;
	xval[0]=getx();

	do
	{
		cursor(ON);
		ch=getch();
		cursor(OFF);

		if(ch==0)
			getch();
		else
		{
			if(ch==8)
			{
				oldcolor=getcolor();
				--stringindex;
				if(stringindex<0);
					stringindex=0;

				moveto(xval[stringindex],gety());
				setcolor(getbkcolor());
				outstring[0]=inputstring[stringindex];
				outtext(outstring);
				moveto(xval[stringindex],gety());
				setcolor(oldcolor);
			}
			else
			{
				inputstring[stringindex]=ch;
				outstring[0]=ch;
				outtext(outstring);
				++stringindex;
				xval[stringindex]=getx();
			}
		}
	}while(ch!=13&&ch!=10);
	inputstring[stringindex]=0;
}

void cursor(int on)
{
	int curx,oldcolor;
	char uBarStr[2]={'_',0};

	if(!on)
	{
		oldcolor=getcolor();
		setcolor(getbkcolor());
	}
	curx=getx();
	outtext(uBarStr);
	moveto(curx,gety());

	if(!on)
		setcolor(oldcolor);
}
void add()
{
	int a,b,c;
	char num1[80],num2[80],ans[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********ADDITION**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the first number");
	getgrstring(num1);
	newline();
	outtext("Enter the second number");
	getgrstring(num2);
	a=atoi(num1);
	b=atoi(num2);
	c=a+b;
	newline();
	sprintf(ans,"%d",c);
	newline();
	outtext("Sum is equal to");
	outtext(ans);
	newline();
	outtext("Thankyou");
	newline();
	outtext("\n Press Enter to exit");
	getch();
}
void subtract()
{
	int a,b,c;
	char num1[80],num2[80],ans[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********S*UBTRACTION*********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the first number");
	getgrstring(num1);
	newline();
	outtext("Enter the second number");
	getgrstring(num2);
	a=atoi(num1);
	b=atoi(num2);
	c=a-b;
	newline();
	sprintf(ans,"%d",c);
	newline();
	outtext("Difference is equal to");
	outtext(ans);
	newline();
	outtext("Thankyou");
	newline();
	outtext("\n Press Enter to exit");
	getch();
}
void multiply()
{
	int a,b,c;
	char num1[80],num2[80],ans[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********MULTIPLICATION**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the first number");
	getgrstring(num1);
	newline();
	outtext("Enter the second number");
	getgrstring(num2);
	a=atoi(num1);
	b=atoi(num2);
	c=a*b;
	newline();
	sprintf(ans,"%d",c);
	newline();
	outtext("Product is equal to");
	outtext(ans);
	newline();
	outtext("Thankyou");
	newline();
	outtext("\n Press Enter to exit");
	getch();
}
void divide()
{
	float a,b,c;
	char num1[80],num2[80],ans[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********DIVISION**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the first number");
	getgrstring(num1);
	newline();
	outtext("Enter the second number");
	getgrstring(num2);
	a=atof(num1);
	b=atof(num2);
	c=a/b;
	newline();
	sprintf(ans,"%f",c);
	newline();
	outtext("Sum is equal to");
	outtext(ans);
	newline();
	outtext("Thankyou");
	newline();
	outtext("\n Press Enter to exit");
	getch();
}
void m_addition()
{
	int i,j,k,l,r,c,matrix1[20],matrix2[20],m,a;
	char *m1[20],*m2[20];
	char row1[80],col1[80],row2[80],col2[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********MATRIX ADDITION**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(2,HORIZ_DIR,5);
	newline();
	newline();
	newline();
	newline();
	newline();
	newline();

	outtext("Enter the dimensions of the first matrix : ");
	newline();
	getgrstring(row1);
	newline();
	getgrstring(col1);
	i=atoi(row1);
	j=atoi(col1);
	newline();
	outtext("Enter the dimensions of the second matrix : ");
	newline();
	getgrstring(row2);
	newline();
	getgrstring(col2);
	k=atoi(row2);
	l=atoi(col2);
	if(i==k&&j==l)
	{
		newline();
	      outtext("Enter the elements of the first matrix");
	      for(m=0;m<(i*j);m++)
	      {
		newline();
		getgrstring(m1[m]);
	      }
	      newline();
	      for(m=0;m<(i*j);m++)
	      {
		   matrix1[m]=atoi(m1[m]);
	      }
		newline();
	      outtext("Enter the elements of the second matrix");
	      for(m=0;m<(i*j);m++)
	      {
		newline();
		getgrstring(m2[m]);
	      }
	      newline();
	      for(m=0;m<(i*j);m++)
	      {
		   matrix2[m]=atoi(m2[m]);
	      }
	      for(m=0;m<(i*j);m++)
	      {
		   matrix1[m]=matrix1[m]+matrix2[m];
	      }
	      for(m=0;m<(i*j);m++)
	      {
		sprintf(m1[m],"%d",matrix1[m]);
	      }
	      newline();
	      outtext("Answer : ");
	      newline();
	      a=-i;
	       for(r=0;r<j;r++)
	       {
			for(c=0;c<j;c++)
			{
				outtext(m1[a+i]);
				tabspace();
				a++;
			}
		newline();
	       }
	}
	else
	{
		newline();
		outtext("Dimensions not valid");
	}
	newline();
	outtext("Thank You");
	newline();
	outtext("Press enter to exit");
	getch();

}
void m_subtraction()
{
	int i,j,k,l,r,c,matrix1[20],matrix2[20],m,a;
	char *m1[20],*m2[20];
	char row1[80],col1[80],row2[80],col2[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********MATRIX SUBTRACTION**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(2,HORIZ_DIR,5);
	newline();
	newline();
	newline();
	newline();
	newline();
	newline();
	outtext("Enter the dimensions of the first matrix : ");
	newline();
	getgrstring(row1);
	newline();
	getgrstring(col1);
	i=atoi(row1);
	j=atoi(col1);
	newline();
	outtext("Enter the dimensions of the second matrix : ");
	newline();
	getgrstring(row2);
	newline();
	getgrstring(col2);
	k=atoi(row2);
	l=atoi(col2);
	if(i==k&&j==l)
	{
		newline();
	      outtext("Enter the elements of the first matrix");
	      for(m=0;m<(i*j);m++)
	      {
		newline();
		getgrstring(m1[m]);
	      }
	      newline();
	      for(m=0;m<(i*j);m++)
	      {
		   matrix1[m]=atoi(m1[m]);
	      }
		newline();
	      outtext("Enter the elements of the second matrix");
	      for(m=0;m<(i*j);m++)
	      {
		newline();
		getgrstring(m2[m]);
	      }
	      newline();
	      for(m=0;m<(i*j);m++)
	      {
		   matrix2[m]=atoi(m2[m]);
	      }
	      for(m=0;m<(i*j);m++)
	      {
		   matrix1[m]=matrix1[m]-matrix2[m];
	      }
	      for(m=0;m<(i*j);m++)
	      {
		sprintf(m1[m],"%d",matrix1[m]);
	      }
	      newline();
	      outtext("Answer : ");
	      newline();
	      a=-i;
	       for(r=0;r<j;r++)
	       {
			for(c=0;c<j;c++)
			{
				outtext(m1[a+i]);
				tabspace();
				a++;
			}
		newline();
	       }
	}
	else
	{
		newline();
		outtext("Dimensions not valid");
	}
	newline();
	outtext("Thank You");
	newline();
	outtext("Press enter to exit");
	getch();

}

void m_transpose()
{
	int i,j,r,c,matrix1[80],tran_matrix[80],temp[40][40],m,a;
	char m1[80][80],row1[80],col1[80],transpose[80][80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********TRANSPOSE OF A MATRIX**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(2,HORIZ_DIR,5);
	newline();
	newline();
	newline();
	newline();
	newline();
	newline();

	outtext("Enter the dimensions of the matrix : ");
	newline();
	getgrstring(row1);
	newline();
	getgrstring(col1);
	i=atoi(row1);
	j=atoi(col1);
	newline();
	newline();
	      outtext("Enter the elements of the first matrix");
	      for(m=0;m<(i*j);m++)
	      {
		newline();
		getgrstring(m1[m]);
	      }
	      newline();
	      newline();
	      outtext("You entered : ");
	      newline();
	      a=-i;
	       for(r=0;r<j;r++)
	       {
			for(c=0;c<j;c++)
			{
				outtext(m1[a+i]);
				tabspace();
				a++;
			}
		newline();
	       }
	      for(m=0;m<(i*j);m++)
	      {
		   matrix1[m]=atoi(m1[m]);
	      }
	      m=0;
	      for(r=0;r<i;r++)
	      {
		for(c=0;c<j;c++)
		{
			temp[r][c]=matrix1[m];
			m++;
		}
	      }
	      m=0;
	  for(r=0;r<i;r++)
	     {
		for(c=0;c<j;c++)
		{
			matrix1[m]=temp[c][r];
			m++;
		}
	      }
	      newline();
	      for(m=0;m<(i*j);m++)
	      {
	      sprintf(transpose[m],"%d",matrix1[m]);
	      }
	      newline();
	      outtext("The transpose of the above matrix is :");
	      newline();
	      newline();
	      a=-i;
	       for(r=0;r<j;r++)
	       {
			for(c=0;c<j;c++)
			{
				outtext(transpose[a+i]);
				tabspace();
				a++;
			}
		newline();
	       }

	outtext("Thank You");
	newline();
	outtext("Press enter to exit");
	getch();


}
void m_multipliction()
{
	m_addition();
}

void factorial()
{
	int no,i;
	long fact=1;
	char Q[80],ans[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********FACTORIAL**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the number");
	getgrstring(Q);
	no=atoi(Q);
	for(i=1;i<=no;i++)
	{
	   fact=fact*i;
	}
	newline();
	outtext("The Factorial of the number is");
	sprintf(ans,"%ld",fact);
	outtext(ans);
	newline();
	outtext("Thank You");
	newline();
	outtext("Press Ente to exit");
	getch();
}
void speed()
{
	char distance[50],time[50],ans[50];
	float t,d,speed;
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********SPEED**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	newline();
	outtext("Enter the distance travelled (in km) : ");
	getgrstring(distance);
	newline();
	outtext("Enter the time taken (in seconds) : ");
	getgrstring(time);
	d=atof(distance);
	t=atof(time);
	speed=d/t;
	newline();
	sprintf(ans,"%f",speed);
	outtext("Speed (per second) = ");
	outtext(ans);
	newline();
	outtext("Thank You");
	newline();
	outtext("Press Ente to exit");
	getch();

}
void triangle_area()
{
	char base[50],height[50],ans[50];
	float h,b,area;
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********TRIANGLE'S AREA**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the height of the triangle : ");
	getgrstring(height);
	newline();
	outtext("Enter the base of the triangle : ");
	getgrstring(base);
	h=atof(height);
	b=atof(base);
	area=0.5*h*b;
	newline();
	sprintf(ans,"%f",area);
	outtext("Area = ");
	outtext(ans);
	newline();
	outtext("Thank You");
	newline();
	outtext("Press Enter to exit");
	getch();


}
void square_area()
{
	char length[80],ans[80];
	float len,area;
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********SQUARE'S AREA**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("\n Enter the length of the square");
	newline();
	getgrstring(length);
	len=atof(length);
	area=len*len;
	sprintf(ans,"%f",area);
	newline();
	outtext("Area = ");
	outtext(ans);
	newline();
	outtext("Thank You");
	newline();
	outtext("Press Enter to exit");
	getch();
}
void rectangle_area()
{
	char length[50],breadth[50],ans[50];
	float len,br,area;
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********RECTANGLE'S AREA**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the length of the rectangle : ");
	getgrstring(length);
	newline();
	outtext("Enter the breadth of the rectangle : ");
	getgrstring(breadth);
	len=atof(length);
	br=atof(breadth);
	area=len*br;
	sprintf(ans,"%f",area);
	newline();
	outtext("Area = ");
	outtext(ans);
	newline();
	outtext("Thank You");
	newline();
	outtext("Press Enter to exit");
	getch();
}
void circle_area()
{
	float r,pi=3.14,area;
	char radius[50],ans[50];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********CIRCLE'S AREA**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the radius of the circle");
	getgrstring(radius);
	r=atof(radius);
	area=r*r*pi;
	sprintf(ans,"%f",area);
	newline();
	outtext("Area = ");
	outtext(ans);
	newline();
	outtext("Thank You");
	newline();
	outtext("Press Ente to exit");
	getch();
}
void simpleinterest()
{
	char principal[50],time[50],rate_of_interest[50],ans[50];
	float t,r,p,interest;
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********SIMPLE INTEREST**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	newline();
	outtext("Enter the principal amount: ");
	getgrstring(principal);
	newline();
	outtext("Enter the time period (in years) : ");
	getgrstring(time);
	newline();
	outtext("Enter the rate of interest : ");
	getgrstring(rate_of_interest);
	t=atof(time);
	p=atof(principal);
	r=atof(rate_of_interest);
	interest=p*r*t/100;
	sprintf(ans,"%f",interest);
	newline();
	outtext("Simple Interest = ");
	outtext(ans);
	newline();
	outtext("Thank You");
	newline();
	outtext("Press Enter to exit");
	getch();
}
void compoundinterest()
{
	float p,r,i,t,f;
	char principal[80],rate[80],time[80],ans[80];
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"**********COMPOUND INTEREST**********");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
	settextstyle(1,HORIZ_DIR,1);
	newline();
	newline();
	newline();
	outtext("Enter the principal amount : ");
	getgrstring(principal);
	newline();
	outtext("Ente the rate of interest : ");
	getgrstring(rate);
	newline();
	outtext("Enter the time (in years) : ");
	getgrstring(time);
	newline();
	p=atof(principal);
	r=atof(rate);
	t=atof(time);
	i=r/100;
	f=p*pow((1+i),t);
	sprintf(ans,"%f",f);
	newline();
	outtext("Compound Interest = ");
	outtext(ans);
	outtext("Thank You");
	newline();
	outtext("Press Enter to exit");
	getch();
}
int initmouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	return(o.x.ax);
}

void showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
}

void hidemouseptr()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
}
void getmousepos(int *button,int *x,int *y)
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
}

int getresponse()
{
	int x,y,button;
	while(1)
	{
		getmousepos(&button,&x,&y);

		if(x>=10&&x<=getmaxx()-10&&y>=10&&y<=getmaxy()-10)
		{
			if((button&1)==1)
			{
				while((button&1)==1)
					getmousepos(&button,&x,&y);

				if(x>=20&&x<=134&&y>=58&&y<=78)
				{
					moveto(20,360);
					newline();
					outtext("You chose subtraction");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					subtract();
					getch();
					exit(0);
				}
				else if(x>=174&&x<=258&&y>=58&&y<=78)
				{
				       moveto(20,360);
					newline();
					outtext("You chose addition");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					add();
					getch();
					exit(0);
				}
				else if(x>=298&&x<=436&&y>=58&&y<=78)
				{
					moveto(20,360);
					newline();
					outtext("You chose multiplication");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					multiply();
					getch();
					exit(0);
				}
				else if(x>=472&&x<=550&&y>=58&&y<=78)
				{
					moveto(20,360);
					newline();
					outtext("You chose division");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					divide();
					getch();
					exit(0);
				}
				else if(x>=20&&x<=170&&y>=98&&y<=118)
				{
					moveto(20,360);
					newline();
					outtext("You chose matrix addition");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					m_addition();
					getch();
					exit(0);
				}
				else if(x>=190&&x<=370&&y>=98&&y<=118)
				{
					moveto(20,360);
					newline();
					outtext("You chose matrix subtraction");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					m_subtraction();
					getch();
					exit(0);
				}
				else if(x>=390&&x<=590&&y>=98&&y<=118)
				{
					moveto(20,360);
					newline();
					outtext("You chose matrix multiplication");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					divide();
					getch();
					exit(0);
				}
				else if(x>=20&&x<=250&&y>=138&&y<=158)
				{
					moveto(20,360);
					newline();
					outtext("You chose transpose of a matrix");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					m_transpose();
					getch();
					exit(0);
				}
				else if(x>=20&&x<=170&&y>=218&&y<=238)
				{
					moveto(20,360);
					newline();
					outtext("You chose speed");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					speed();
					getch();
					exit(0);
				}
				else if(x>=200&&x<=360&&y>=218&&y<=238)
				{
					moveto(20,360);
					newline();
					outtext("You chose factorial");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					factorial();
					getch();
					exit(0);
				}else if(x>=20&&x<=170&&y>=178&&y<=198)
				{
					moveto(20,360);
					newline();
					outtext("You chose simple interest");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					simpleinterest();
					getch();
					exit(0);
				}else if(x>=190&&x<=360&&y>=178&&y<=198)
				{
					moveto(20,360);
					newline();
					outtext("You chose compound interest");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					compoundinterest();
					getch();
					exit(0);
				}else if(x>=20&&x<=170&&y>=258&&y<=278)
				{
					moveto(20,360);
					newline();
					outtext("You chose triangle's area");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					triangle_area();
					getch();
					exit(0);
				}
				else if(x>=190&&x<=278&&y>=258&&y<=278)
				{
					moveto(20,360);
					newline();
					outtext("You chose square's area");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					square_area();
					getch();
					exit(0);
				}

				else if(x>=380&&x<=540&&y>=258&&y<=278)
				{
					moveto(20,360);
					newline();
					outtext("You chose rectangle's area");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					rectangle_area();
					getch();
					exit(0);
				}

				else if(x>=20&&x<=170&&y>=298&&y<=318)
				{
					moveto(20,360);
					newline();
					outtext("You chose circle's area");
					newline();
					outtext("Press Enter to continue");
					getch();
					cleardevice();
					circle_area();
					getch();
					exit(0);
				}

			}
		}
	}
}
void changecursor(char *shape)
{
	   i.x.ax=9;
	   i.x.bx=0;
	   i.x.cx=0;
	   i.x.dx=(unsigned)shape;
	   segread(&s);
	   s.es=(unsigned int)s.ds;
	   int86(0x33,&i,&o);
}

/*void sum(int temp,int no)
{
	temp=temp+no;
	scanf("%c",&character);

	if(charcacter=='+')
	{
		scanf("%d",&no);
		sum(temp,no);
	}
	else if(character=='=')
	{
		setcolor(BLUE);
		outtextxy(150,150,"Sum is equl to ");
		printf("\n\n\n\t\t\t %d",temp);
	}
}*/
void menus()
{
	int boxlength;
	setcolor(LIGHTRED);
	settextstyle(2,HORIZ_DIR,6);

	rectangle(20,58,134,78);
	outtextxy(23,60,"SUBTRACTION");

	rectangle(174,58,258,78);
	outtextxy(177,60,"ADDITION");

	rectangle(298,58,436,78);
	outtextxy(301,60,"MULTIPLICATION");

	rectangle(472,58,550,78);
	outtextxy(475,60,"DIVISION");

	setcolor(CYAN);
	settextstyle(2,HORIZ_DIR,6);
	boxlength=0;
	rectangle(20,98,170,118);
	outtextxy(23,100,"MATRIX ADDITION");

	rectangle(190,98,370,118);
	outtextxy(193,100,"MATRIX SUBTRACTION");

	rectangle(390,98,590,118);
	outtextxy(393,100,"MATRIX MULTIPLICATION");

	boxlength=0;
	rectangle(20,138,250,158);
	outtextxy(23,140,"TRANSPOSE OF A MATRIX");

	boxlength=0;
	rectangle(20,178,170,198);
	outtextxy(23,180,"SIMPLE INTEREST");

	rectangle(190,178,360,198);
	outtextxy(193,180,"COMPOUND INTEREST");

	setcolor(RED);
	rectangle(20,218,180,238);
	outtextxy(23,220,"SPEED");

	rectangle(200,218,360,238);
	outtextxy(203,220,"FACTORIAL");

	setcolor(GREEN);
	rectangle(20,258,170,278);
	outtextxy(23,260,"TRIANGLE'S AREA");

	rectangle(190,258,360,278);
	outtextxy(193,260,"SQUARE'S AREA");

	rectangle(380,258,540,278);
	outtextxy(383,260,"RECTANGLE'S AREA");

	rectangle(20,298,170,318);
	outtextxy(23,300,"CIRCLE'S AREA");

}

void frontpage()
{
	setcolor(BLUE);
	rectangle(10,10,getmaxx()-10,getmaxy()-10);
	setfillstyle(1,MAGENTA);
	bar(10,10,getmaxx()-10,52);
	setcolor(WHITE);
	settextstyle(6,HORIZ_DIR,3);
	outtextxy(200,10,"MATHCALCULATOR");
	setcolor(BLUE);
	line(10,52,getmaxx()-10,52);
}

void problemdetermination(char *problem)
{
	if(strcmpi(problem,"addition")==13)
	{
	}
	else  if(strcmpi(problem,"subtraction")==13)
	{
	}
	else  if(strcmpi(problem,"multiplication")==13)
	{
	}
	else  if(strcmpi(problem,"division")==13)
	{
	}
	else  if(strcmpi(problem,"matrix addition")==13)
	{
	}
	else  if(strcmpi(problem,"matrix subtraction")==13)
	{
	}
	else  if(strcmpi(problem,"matrix multiplication")==13)
	{
	}
	else  if(strcmpi(problem,"transpose of a matrix")==13)
	{
	}
    else  if(strcmpi(problem,"subtraction")==13)
	{
	}
	else  if(strcmpi(problem,"multiplication")==13)
	{
	}
	else  if(strcmpi(problem,"division")==13)
	{
	}
	else  if(strcmpi(problem,"matrix addition")==13)
	{
	}
	else  if(strcmpi(problem,"matrix subtraction")==13)
	{
	}
	else  if(strcmpi(problem,"matrix multiplication")==13)
	{
	}
	else  if(strcmpi(problem,"transpose of a matrix")==13)
	{
	}
}
void main()
{
	int gd=DETECT,gm,button,x,y;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	setbkcolor(WHITE);
	frontpage();
	menus();
	changecursor(c);
	showmouseptr();
	getresponse();
	moveto(50,340);
	outtext("Enter the problem from the various options listed above");
	moveto(20,360);
	getgrstring(problem);
	moveto(20,380);
	problemdetermination(problem);
	getch();
	restorecrtmode();
	closegraph();
}
