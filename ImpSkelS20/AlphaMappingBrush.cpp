#include "AlphaMappingBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

AlphaMappingBrush::AlphaMappingBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void AlphaMappingBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(1.0f);

	BrushMove(source, target);
}

void AlphaMappingBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("AlphaMappingBrush::BrushMove  document is NULL\n");
		return;
	}

    if (!pDoc->m_ucAlphaMap) return;

	glBegin(GL_POINTS);
	SetColor(source);

	glVertex2d(target.x, target.y);

	glEnd();
}

void AlphaMappingBrush::ClipBrushStroke(const Point source, const Point target) {}

void AlphaMappingBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
