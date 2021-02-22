//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "CircleBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void CircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	radius = pDoc->getSize();

	BrushMove(source, target);
}

#define RESOLUTION 24

void CircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POLYGON);
	SetColor(source);
	for (double i = 0; i < 2 * M_PI; i += M_PI / RESOLUTION) {
		Point t_target = target;
		t_target.x += cos(i) * radius;
		t_target.y += sin(i) * radius;
		ClipBrushStroke(source, t_target);
		// glVertex2d((cos(i) * radius) + target.x, (sin(i) * radius) + target.y);
	}

	glEnd();
}

void CircleBrush::ClipBrushStroke(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	if (target.x >= 0 && target.y >= 0 && pDoc->m_pUI->m_paintView->get_m_nDrawWidth() >= target.x
		&& pDoc->m_pUI->m_paintView->get_m_nDrawHeight() >= target.y) {
		glVertex2d(target.x, target.y);
	}
}

void CircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
