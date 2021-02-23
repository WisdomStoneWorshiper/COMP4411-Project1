//
// FilterBrush.cpp
//
// The implementation of Filter Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "FilterBrush.h"


extern float frand();

FilterBrush::FilterBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void FilterBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	size = pDoc->getSize();

	glPointSize((float)(size * 2 - 1));

	BrushMove(source, target);
}
#include <iostream>
void FilterBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("FilterBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);
	int rgb[3] = {0};
	for (int i = -(size - 1); i < size; ++i) {
		for (int j = -(size - 1); j < size; ++j) {
			Point temp_s = source;
			if (i < 0 || i > dlg->m_paintView->get_m_nDrawWidth()) {
				temp_s.x += -1 * i;
			} else {
				temp_s.x += i;
			}
			if (j < 0 || j > dlg->m_paintView->get_m_nDrawHeight()) {
				temp_s.y += -1 * j;
			} else {
				temp_s.y += j;
			}
			getColor(temp_s);
			for (int k = 0; k < 3; ++k) {
				rgb[k] += temp_color[k];
			}
			// if (i == 0 && j == 0) {
			// 	for (int k = 0; k < 3; ++k) {
			// 		rgb[k] += temp_color[k];
			// 	}
			// } else {
			// 	for (int k = 0; k < 3; ++k) {
			// 		rgb[k] -= temp_color[k] / ((size * 2 - 1) * (size * 2 - 1));
			// 	}
			// }
		}
	}
	for (int k = 0; k < 3; ++k) {
		rgb[k] /= ((size * 2 - 1) * (size * 2 - 1));
	}
	// std::cout << rgb[0] << " " << rgb[1] << " " << rgb[2] << ";";
	GLubyte color[3] = {(GLubyte)rgb[0], (GLubyte)rgb[1], (GLubyte)rgb[2]};

	// glColor4ubv(color);

	glColor3ubv(color);

	glVertex2d(target.x, target.y);

	glEnd();
}

void FilterBrush::getColor(const Point source) {
	ImpressionistDoc* pDoc = GetDocument();
	memcpy(temp_color, pDoc->GetOriginalPixel(source), 3);
	// temp_color[3] = static_cast<GLubyte>(pDoc->getAlpha() * 255.f);
}

void FilterBrush::ClipBrushStroke(const Point source, const Point target) {}

void FilterBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
