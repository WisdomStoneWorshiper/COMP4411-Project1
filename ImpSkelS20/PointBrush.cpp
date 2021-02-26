//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "PointBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

PointBrush::PointBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void PointBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glPointSize((float)size);

	BrushMove(source, target);
}

void PointBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);
	ClipBrushStroke(source, target);

	glEnd();
}

void PointBrush::ClipBrushStroke(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	if (target.x >= 0 && target.y >= 0 && pDoc->m_pUI->m_paintView->get_m_nDrawWidth() >= target.x
		&& target.y >= pDoc->m_pUI->m_paintView->get_m_nWindowHeight() - pDoc->m_pUI->m_paintView->get_m_nDrawHeight()
		&& pDoc->m_pUI->m_paintView->get_m_nWindowHeight() >= target.y) {
		SetColor(source);
		glVertex2d(target.x, target.y);
	}
}

void PointBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
