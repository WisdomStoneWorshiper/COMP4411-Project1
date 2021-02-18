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

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	double dir = 0;
	int gx = 0, gy = 0;
	int x_offset = 0;
	int y_offset = 0;
	switch (pDoc->getStrokeType()) {
		case SLIDER_RIGHT_CLICK:
			dir = (dlg->getLineAngle() / 180.0) * M_PI;
			x_offset = line_size * cos(dir) / 2;
			y_offset = line_size * sin(dir) / 2;
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

			x_offset = line_size * cos(dir) / 2;
			y_offset = line_size * sin(dir) / 2;


			break;
		case BRUSH_DIRECTION:
			dir = atan2(last_point.y - target.y, last_point.x - target.x);
			x_offset = line_size * cos(dir) / 2;
			y_offset = line_size * sin(dir) / 2;

			last_point = target;

			break;

		default: break;
	}

	glBegin(GL_LINES);
	SetColor(source);

	glVertex2d(target.x - x_offset, target.y - y_offset);
	glVertex2d(target.x + x_offset, target.y + y_offset);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
