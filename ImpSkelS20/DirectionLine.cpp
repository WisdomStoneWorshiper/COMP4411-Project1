//
// DirectionLine.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "DirectionLine.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

extern float frand();

DirectionLine::DirectionLine(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void DirectionLine::BrushBegin(const Point source, const Point target) {
	// glLineWidth(1);
	start_pt.x = target.x;
	start_pt.y = target.y;

	// BrushMove(source, target);
}

void DirectionLine::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc == NULL) {
		printf("DirectionLine::BrushMove  document is NULL\n");
		return;
	}
	glBegin(GL_LINES);
	GLubyte color[3];
	color[0] = 255;

	glColor3ubv(color);
	// SetColor(source);

	glVertex2d(start_pt.x, start_pt.y);
	glVertex2d(target.x, target.y);

	glEnd();
}

void DirectionLine::ClipBrushStroke(const Point source, const Point target) {
	// do nothing so far
}
// #include "iostream"
void DirectionLine::BrushEnd(const Point source, const Point target) {
	ImpressionistUI* dlg = GetDocument()->m_pUI;
	if (GetDocument()->m_pCurrentBrush == ImpBrush::c_pBrushes[BRUSH_LINES]
		|| GetDocument()->m_pCurrentBrush == ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]) {
		int line_size = sqrt(pow(start_pt.x - target.x, 2) + pow(start_pt.y - target.y, 2));
		dlg->setSize(line_size);
		dlg->setLineAngle((int)(atan2(target.y - start_pt.y, target.x - start_pt.x) * 180.0 / M_PI));
	}
	// std::cout << "d " << line_width << " " << cos(abs(start_pt.x - end_pt.x) / line_width);
}
