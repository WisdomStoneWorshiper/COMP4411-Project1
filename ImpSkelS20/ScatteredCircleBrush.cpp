//
// ScatteredCircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ScatteredCircleBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

#define CONVERT_TO_RADS M_PI / 180.0

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	radius = pDoc->getSize();

	glPointSize(1.0f);

	BrushMove(source, target);
}

#define RESOLUTION 24

void ScatteredCircleBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);
	for (int i = 0; i < radius * radius * M_PI / 3; ++i) {
		double r_offset = frand() * radius;
		double t_offset = (frand() * 360) * CONVERT_TO_RADS;
		int x_offset = r_offset * cos(t_offset);
		int y_offset = r_offset * sin(t_offset);
		Point s_source = source;
		s_source.x += x_offset;
		s_source.y += y_offset;
		Point t_target = target;
		t_target.x += x_offset;
		t_target.y += y_offset;
		ClipBrushStroke(s_source, t_target);
		// SetColor(s_source);
		// glVertex2d(target.x + x_offset, target.y + y_offset);
	}
	glEnd();
}

void ScatteredCircleBrush::ClipBrushStroke(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	if (target.x >= 0 && target.y >= 0 && pDoc->m_pUI->m_paintView->get_m_nDrawWidth() >= target.x
		&& pDoc->m_pUI->m_paintView->get_m_nDrawHeight() >= target.y) {
		SetColor(source);
		glVertex2d(target.x, target.y);
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
