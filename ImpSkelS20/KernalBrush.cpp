//
// KernalBrush.cpp
//
// The implementation of Kernal Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "KernalBrush.h"


extern float frand();

KernalBrush::KernalBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void KernalBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	size = pDoc->getSize();
	normalize = false;
	glPointSize(1);

	BrushMove(source, target);
}
#include <iostream>
void KernalBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	size = pDoc->getSize();
	if (pDoc == NULL) {
		printf("KernalBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_POINTS);
	int rgb[3] = {0};
	for (int i = -(size - 1); i < size; ++i) {
		for (int j = -(size - 1); j < size; ++j) {
			Point temp_s = Point(source.x + i, source.y + j);
			if (temp_s.x < 0 || temp_s.x > dlg->m_paintView->get_m_nDrawWidth() || temp_s.y < 0
				|| temp_s.y > dlg->m_paintView->get_m_nDrawHeight()) {
				continue;
			} else {
				filter_applier(temp_s);
				glVertex2d(target.x + i, target.y + j);
			}
		}
	}
	glEnd();
}

void KernalBrush::filter_applier(const Point source) {
	ImpressionistUI* dlg = GetDocument()->m_pUI;
	double rgb[3] = {0};
	for (int i = -(filter_size - 1) / 2; i <= (filter_size - 1) / 2; ++i) {
		for (int j = -(filter_size - 1) / 2; j <= (filter_size - 1) / 2; ++j) {
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
			double filter_value = filter[(i + (filter_size - 1) / 2) + (j + (filter_size - 1) / 2) * filter_size];
			if (normalize)
				filter_value /= filter_sum;
			for (int k = 0; k < 3; ++k) {
				rgb[k] += temp_color[k] * filter_value;
			}
		}
	}
	GLubyte color[3] = {(GLubyte)rgb[0], (GLubyte)rgb[1], (GLubyte)rgb[2]};
	glColor3ubv(color);
}

void KernalBrush::getColor(const Point source) {
	ImpressionistDoc* pDoc = GetDocument();
	memcpy(temp_color, pDoc->GetOriginalPixel(source), 3);
	// temp_color[3] = static_cast<GLubyte>(pDoc->getAlpha() * 255.f);
}
void KernalBrush::setKernalFilter(std::string input) {
	std::stringstream temp(input);
	std::string buf;
	filter.clear();
	filter_sum = 0;
	while (temp >> buf) {
		double temp = stod(buf);
		filter.push_back(stod(buf));
		filter_sum += temp;
	}
	filter_size = sqrt(filter.size());

	// for (int i = 0; i < filter.size(); ++i) {
	// 	std::cout << filter[i] << " ";
	// }
}

void KernalBrush::ClipBrushStroke(const Point source, const Point target) {}

void KernalBrush::set_normalize(bool input) { normalize = input; }

void KernalBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
