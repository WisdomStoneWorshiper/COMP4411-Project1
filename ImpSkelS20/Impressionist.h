#ifndef IMPRESSIONIST_H
#define IMPRESSIONIST_H
#define SAMPLE_SOLUTION
#include "ImpBrush.h"

#include <FL/Fl.h>
#include <FL/gl.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include <GL/glu.h>
#else
	#include <OpenGL/glu.h>
#endif
#include <stdio.h>

#define TRUE  1
#define FALSE 0

#ifdef WIN32
	#define M_PI 3.1415926535F
#endif

#endif