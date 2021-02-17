//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "LineBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void LineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	line_size = pDoc->getSize();
	glLineWidth(dlg->getLineWidth());
	glRotatef(dlg->getLineAngle(), 0, 0, 1.0); //Note: add this line of code in scattered line brush as well

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINES);
	SetColor(source);

	glVertex2d(fmax(target.x - line_size / 2, 0), target.y);
	glVertex2d(fmin(target.x + line_size / 2, pDoc->m_nPaintWidth), target.y);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
