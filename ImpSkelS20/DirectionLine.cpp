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
	ImpressionistDoc* pDoc = GetDocument();

	glLineWidth(1);
	start_pt.x = target.x;
	start_pt.y = target.y;

	BrushMove(source, target);
}

void DirectionLine::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	if (end_pt.x == target.x && end_pt.y == target.y)
		return;
	end_pt.x = target.x;
	end_pt.y = target.y;
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
	glVertex2d(end_pt.x, end_pt.y);

	glEnd();
}
#include "iostream"
void DirectionLine::BrushEnd(const Point source, const Point target) {
	// do nothing so far
	ImpressionistUI* dlg = GetDocument()->m_pUI;
	int line_width = sqrt(pow(start_pt.x - end_pt.x, 2) + pow(start_pt.y - end_pt.y, 2));
	dlg->setLineWidth(line_width);
	dlg->setLineAngle(cos(abs(start_pt.x - end_pt.x) / line_width) * 180.0 / M_PI);
	std::cout << "d " << line_width << " " << cos(abs(start_pt.x - end_pt.x) / line_width);
}
