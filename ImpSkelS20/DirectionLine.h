//
// DirectionLine.h
//
// The header file for Line Brush.
//
#pragma once

#include "ImpBrush.h"

class DirectionLine : public ImpBrush {
public:
	DirectionLine(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void ClipBrushStroke(const Point source, const Point target);
	char* BrushName(void);

private:
	Point start_pt;
	Point end_pt;
};
