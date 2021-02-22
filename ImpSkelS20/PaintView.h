//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include <GL/glu.h>
#else
	#include <OpenGL/glu.h>
#endif
#include <stdlib.h>

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window {
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();

	void resizeWindow(int width, int height);

	void SaveCurrentContent();

	void RestoreContent();

	int get_m_nDrawWidth();

	int get_m_nDrawHeight();

	ImpressionistDoc* m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	int m_nDrawWidth, m_nDrawHeight, m_nStartRow, m_nEndRow, m_nStartCol, m_nEndCol, m_nWindowWidth, m_nWindowHeight;
};

#endif