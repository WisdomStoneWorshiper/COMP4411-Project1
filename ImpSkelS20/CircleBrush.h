//
// CircleBrush.h
//
// The header file for Circle Brush.
//
#pragma once

#include "ImpBrush.h"

class CircleBrush : public ImpBrush {
public:
	CircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	void ClipBrushStroke(const Point source, const Point target);
	char* BrushName(void);

private:
	int radius;
};
