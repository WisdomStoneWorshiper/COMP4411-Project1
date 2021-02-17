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
#include "iostream"

void LineBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	line_size = pDoc->getSize();

	glLineWidth(dlg->getLineWidth());
	glRotatef(dlg->getLineAngle(), 0, 0, 1.0); // Note: add this line of code in scattered line brush as well
	// std::cout << "line " << dlg->getLineWidth() << " " << dlg->getLineAngle();
	last_point = source;
	BrushMove(source, target);
}

void LineBrush::StrokeHandler(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	float dir = 0;
	int gx = 0, gy = 0;
	switch (pDoc->getStrokeType()) {
		case SLIDER_RIGHT_CLICK:
			glBegin(GL_LINES);
			SetColor(source);

			glVertex2d(fmax(target.x - line_size / 2, 0), target.y);
			glVertex2d(fmin(target.x + line_size / 2, pDoc->m_nPaintWidth), target.y);

			glEnd();
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
			dir = (atan2(gy, gx) * 180.0 / M_PI) + 90;
			// if (dir > 360) {
			// 	dir -= 360;
			// }
			glRotatef(dir, 0, 0, 1.0);
			glBegin(GL_LINES);
			SetColor(source);

			glVertex2d(fmax(target.x - line_size / 2, 0), target.y);
			glVertex2d(fmin(target.x + line_size / 2, pDoc->m_nPaintWidth), target.y);

			glEnd();
			// std::cout << "d " << dir;
			break;
		case BRUSH_DIRECTION:
			dir = atan2(last_point.y - source.y, last_point.x - source.x) * 180.0 / M_PI;
			glRotatef(dir, 0, 0, 1.0);
			glBegin(GL_LINES);
			SetColor(source);

			glVertex2d(fmax(target.x - line_size / 2, 0), target.y);
			glVertex2d(fmin(target.x + line_size / 2, pDoc->m_nPaintWidth), target.y);

			glEnd();
			last_point = source;

			break;

			// default: break;
	}
}

void LineBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	float dir = 0;
	int gx = 0, gy = 0;
	switch (pDoc->getStrokeType()) {
		case SLIDER_RIGHT_CLICK:
			glBegin(GL_LINES);
			SetColor(source);

			glVertex2d(fmax(target.x - line_size / 2, 0), target.y);
			glVertex2d(fmin(target.x + line_size / 2, pDoc->m_nPaintWidth), target.y);

			glEnd();
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
			dir = (atan2(gy, gx) * 180.0 / M_PI) + 90;
			// if (dir > 360) {
			// 	dir -= 360;
			// }
			glRotatef(dir, 0, 0, 1.0);
			glBegin(GL_LINES);
			SetColor(source);

			glVertex2d(fmax(target.x - line_size / 2, 0), target.y);
			glVertex2d(fmin(target.x + line_size / 2, pDoc->m_nPaintWidth), target.y);

			glEnd();
			// std::cout << "d " << dir;
			break;
		case BRUSH_DIRECTION:
			dir = atan2(last_point.y - source.y, last_point.x - source.x) * 180.0 / M_PI;
			glRotatef(dir, 0, 0, 1.0);
			glBegin(GL_LINES);
			SetColor(source);

			glVertex2d(fmax(target.x - line_size / 2, 0), target.y);
			glVertex2d(fmin(target.x + line_size / 2, pDoc->m_nPaintWidth), target.y);

			glEnd();
			last_point = source;

			break;

			// default: break;
	}
}

void LineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
