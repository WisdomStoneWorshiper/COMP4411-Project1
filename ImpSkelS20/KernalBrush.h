//
// KernalBrush.h
//
// The header file for Kernal Brush.
//
#pragma once

#include "ImpBrush.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

#include <cstring>
#include <sstream>
#include <vector>

class KernalBrush : public ImpBrush {
public:
	KernalBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void ClipBrushStroke(const Point source, const Point target);
	char* BrushName(void);
	void getColor(const Point source);
	void setKernalFilter(std::string input);

private:
	const int FILTER_SIZE = 21;
	void mean_filter_applier(const Point target);
	GLubyte temp_color[3];
	std::vector<int> filter;
	int size;
};
