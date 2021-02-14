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
	for (int i = 0; i < radius * radius * M_PI / 2; ++i) {
		double r_offset = frand() * radius;
		double t_offset = (frand() * 360) * CONVERT_TO_RADS;
		int x_offset = r_offset * cos(t_offset);
		int y_offset = r_offset * sin(t_offset);
		Point s_source = source;
		s_source.x += x_offset;
		s_source.y += y_offset;
		SetColor(s_source);
		glVertex2d(target.x + x_offset, target.y + y_offset);
	}
	glEnd();
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
