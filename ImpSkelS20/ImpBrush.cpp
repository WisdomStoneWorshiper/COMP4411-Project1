//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "ImpBrush.h"

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

// Static class member initializations
int ImpBrush::c_nBrushCount = 0;
ImpBrush** ImpBrush::c_pBrushes = NULL;

ImpBrush::ImpBrush(ImpressionistDoc* pDoc, char* name) : m_pDoc(pDoc), m_pBrushName(name) {}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void) { return m_pDoc; }

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void) { return m_pBrushName; }

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample
// the color from
//----------------------------------------------------
void ImpBrush::SetColor(const Point source) {
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[4];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	float sR = pDoc->m_pUI->getRedScale() * color[0];
	float sG = pDoc->m_pUI->getGreenScale() * color[1];
	float sB = pDoc->m_pUI->getBlueScale() * color[2];
	color[0] = sR >= 1.0 ? static_cast<GLubyte>(sR) : 1;
	color[1] = sG >= 1.0 ? static_cast<GLubyte>(sG) : 1;
	color[2] = sB >= 1.0 ? static_cast<GLubyte>(sB) : 1;
	color[3] = static_cast<GLubyte>(pDoc->getAlpha() * 255.f);
	glColor4ubv(color);
}