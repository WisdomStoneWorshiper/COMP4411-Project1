//
// ScatteredPointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ScatteredPointBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	brush_range = pDoc->getSize();

	glPointSize(1.0f);

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);

	for (int i = 0; i < brush_range * brush_range / 2; ++i) {
		int x_offset = rand() % (brush_range * 2) - brush_range;
		int y_offset = rand() % (brush_range * 2) - brush_range;
		Point s_source = source;
		s_source.x += x_offset;
		s_source.y += y_offset;
		SetColor(s_source);
		glVertex2d(target.x + x_offset, target.y + y_offset);
	}

	glEnd();
}

void ScatteredPointBrush::ClipBrushStroke(const Point source, const Point target) {}


void ScatteredPointBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
