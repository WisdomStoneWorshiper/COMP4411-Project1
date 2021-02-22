//
// ScatteredLineBrush.h
//
// The header file for Line Brush.
//

#pragma once

#include "ImpBrush.h"

class ScatteredLineBrush : public ImpBrush {
public:
	ScatteredLineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void ClipBrushStroke(const Point source, const Point target);
	char* BrushName(void);

private:
	int ran_size;
	double line_size;
	Point last_point;
};