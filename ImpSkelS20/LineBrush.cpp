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

const int sx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int sy[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void LineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	line_size = pDoc->getSize();

	glLineWidth(dlg->getLineWidth());
	last_point = source;
	BrushMove(source, target);
}


void LineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	line_size = pDoc->getSize();
	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	double dir = 0;
	int gx = 0, gy = 0;
	Point offset;
	offset.x = 0;
	offset.y = 0;
	switch (pDoc->getStrokeType()) {
		case SLIDER_RIGHT_CLICK:
			dir = (dlg->getLineAngle() / 180.0) * M_PI;
			offset.x = line_size * cos(dir) / 2;
			offset.y = line_size * sin(dir) / 2;
			break;
		case GRADIENT:

			for (int i = -1; i < 2; ++i) {
				for (int j = -1; j < 2; ++j) {
					GLubyte temp[3];
					Point temp_p = Point(source.x + i, source.y + j);
					memcpy(temp, pDoc->GetOriginalPixel(temp_p), 3);
					int temp_m = (temp[0] + temp[1] + temp[2]) / 3;
					gx += temp_m * sx[i + 1][j + 1];
					gy += temp_m * sy[i + 1][j + 1];
				}
			}
			dir = (atan2(gy, gx)) + M_PI / 2;

			offset.x = line_size * cos(dir) / 2;
			offset.y = line_size * sin(dir) / 2;


			break;
		case BRUSH_DIRECTION:
			dir = atan2(last_point.y - target.y, last_point.x - target.x);
			offset.x = line_size * cos(dir) / 2;
			offset.y = line_size * sin(dir) / 2;

			last_point = target;

			break;

		default: break;
	}

	glBegin(GL_LINES);
	SetColor(source);
	ClipBrushStroke(target, offset);

	// glVertex2d(target.x - offset.x, target.y - offset.y);
	// glVertex2d(target.x + x_offset, target.y + y_offset);

	glEnd();
}
#include <iostream>
void LineBrush::ClipBrushStroke(const Point target, const Point offset) {
	ImpressionistDoc* pDoc = GetDocument();
	Point p1 = target, p2 = target;
	p1.x += offset.x;
	p2.x -= offset.x;
	p1.y += offset.y;
	p2.y -= offset.y;
	double a = p2.y - p1.y;
	double b = p1.x - p2.x;
	double c = a * (p1.x) + b * (p1.y);
	Point* curr_point = &p1;
	// std::cout << "sx:" << pDoc->m_pUI->m_paintView->get_m_nStartCol()
	// 		  << "sy:" << pDoc->m_pUI->m_paintView->get_m_nStartRow() << ";";
	// std::cout << "dx:" << pDoc->m_pUI->m_paintView->get_m_nDrawWidth()
	// 		  << "dy:" << pDoc->m_pUI->m_paintView->get_m_nDrawHeight() << ";";
	// std::cout << "px:" << pDoc->m_nPaintWidth << "py:" << pDoc->m_nPaintHeight << ";";
	// std::cout << "px:" << pDoc->m_nPaintWidth << "py:" << pDoc->m_nPaintHeight << ";";
	// std::cout << "wy:" << pDoc->m_pUI->m_paintView->get_m_nWindowHeight() << ";";

	for (int i = 0; i < 2; ++i) {
		if (curr_point->x
			< pDoc->m_pUI->m_paintView->get_m_nWindowWidth() - pDoc->m_pUI->m_paintView->get_m_nDrawWidth()) {
			curr_point->x = 0;
			curr_point->y = c / b;
		} else if (curr_point->x > pDoc->m_pUI->m_paintView->get_m_nWindowWidth()) {
			curr_point->x = pDoc->m_pUI->m_paintView->get_m_nWindowWidth();
			curr_point->y = (c - a * curr_point->x) / b;
		}
		if (curr_point->y
			< pDoc->m_pUI->m_paintView->get_m_nWindowHeight() - pDoc->m_pUI->m_paintView->get_m_nDrawHeight()) {
			curr_point->y =
				pDoc->m_pUI->m_paintView->get_m_nWindowHeight() - pDoc->m_pUI->m_paintView->get_m_nDrawHeight();
			curr_point->x = c / a;
		} else if (curr_point->y > pDoc->m_pUI->m_paintView->get_m_nWindowHeight()) {
			curr_point->y = pDoc->m_pUI->m_paintView->get_m_nWindowHeight();
			curr_point->x = (c - b * curr_point->y) / a;
		}
		curr_point = &p2;
	}
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p2.y);
}

void LineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
