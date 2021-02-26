#include "AlphaMappingBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

extern float frand();

AlphaMappingBrush::AlphaMappingBrush(ImpressionistDoc* pDoc, char* name) : ImpBrush(pDoc, name) {}

void AlphaMappingBrush::BrushBegin(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(1.0f);

	BrushMove(source, target);
}

void AlphaMappingBrush::BrushMove(const Point source, const Point target) {
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("AlphaMappingBrush::BrushMove  document is NULL\n");
		return;
	}

    if (!pDoc->m_ucAlphaMap) return;

    int start_point_x = target.x - pDoc->m_nAlphaWidth/2;
    int start_point_y = target.y - pDoc->m_nAlphaHeight/2;
    float original_alpha = pDoc->getAlpha();

	glBegin(GL_POINTS);
	
    for (int i = 0; i < 3*pDoc->m_nAlphaHeight*pDoc->m_nAlphaWidth; i+=3) {
        float alpha = (pDoc->m_ucAlphaMap[i]+pDoc->m_ucAlphaMap[i+1]+pDoc->m_ucAlphaMap[i+2])/765.f;
        pDoc->setAlpha(alpha);
        Point pos;
        pos.x = start_point_x+(i/3 % pDoc->m_nAlphaWidth);
        pos.y = start_point_y+(i/(3*pDoc->m_nAlphaWidth));
        ClipBrushStroke(source, pos);
    }

	glEnd();

    pDoc->setAlpha(original_alpha);
}

void AlphaMappingBrush::ClipBrushStroke(const Point source, const Point target) {
    ImpressionistDoc* pDoc = GetDocument();
	if (target.x >= 0 && target.y >= 0 && pDoc->m_pUI->m_paintView->get_m_nDrawWidth() >= target.x
		&& target.y >= pDoc->m_pUI->m_paintView->get_m_nWindowHeight() - pDoc->m_pUI->m_paintView->get_m_nDrawHeight()
		&& pDoc->m_pUI->m_paintView->get_m_nWindowHeight() >= target.y) {
		SetColor(source);
		glVertex2d(target.x, target.y);
	}
}

void AlphaMappingBrush::BrushEnd(const Point source, const Point target) {
	// do nothing so far
}
