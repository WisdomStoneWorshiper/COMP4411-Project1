//
// FilterBrush.h
//
// The header file for Filter Brush.
//
#pragma once

#include "ImpBrush.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

class FilterBrush : public ImpBrush {
public:
	FilterBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void ClipBrushStroke(const Point source, const Point target);
	char* BrushName(void);
	void getColor(const Point source);

private:
	const int FILTER_SIZE = 21;
	void mean_filter_applier(const Point target);
	GLubyte temp_color[3];
	int size;
};
