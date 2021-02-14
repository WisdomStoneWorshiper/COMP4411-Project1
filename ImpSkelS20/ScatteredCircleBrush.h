//
// ScatteredCircleBrush.h
//
// The header file for Circle Brush.
//
#pragma once

#include "ImpBrush.h"

class ScatteredCircleBrush : public ImpBrush {
   public:
	ScatteredCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

   private:
	int radius;
};
