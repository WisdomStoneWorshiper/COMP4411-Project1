//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include "ImpBrush.h"
#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H> // FLTK file chooser

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window* m_mainWindow;
	Fl_Menu_Bar* m_menubar;

	PaintView* m_paintView;
	OriginalView* m_origView;

	// for brush dialog
	Fl_Window* m_brushDialog;
	Fl_Window* m_colorDialog;
	Fl_Window* m_dissolveDialog;
	Fl_Choice* m_BrushTypeChoice;

	Fl_Choice* m_StrokeDirectionChoice;
	Fl_Slider* m_BrushSizeSlider;
	Fl_Slider* m_LineWidthSlider;
	Fl_Slider* m_LineAngleSlider;
	Fl_Slider* m_AlphaSlider;
	Fl_Slider* m_redSlider;
	Fl_Slider* m_blueSlider;
	Fl_Slider* m_greenSlider;
	Fl_Slider* m_AutoSpacingSlider;
	Fl_Slider* m_dissolveSlider;

	Fl_Button* m_ClearCanvasButton;
	Fl_Button* m_AutoDrawButton;
	Fl_Button* m_loadImageButton;
	Fl_Button* m_dissolveImageButton;

	Fl_Input* m_KernalFilter;

	// Member functions
	void setDocument(ImpressionistDoc* doc);
	ImpressionistDoc* getDocument();

	void show();
	void resize_windows(int w, int h);

	// Interface to get attribute

	int getSize();
	void setSize(int size);
	int getLineWidth();
	void setLineWidth(int lineWidth);
	int getLineAngle();
	void setLineAngle(int lineAngle);
	float getAlpha();
	void setAlpha(float alpha);
	float getRedScale();
	float getBlueScale();
	float getGreenScale();
	int getAutoSpacing();
	float getDissolveAlpha();


private:
	ImpressionistDoc* m_pDoc; // pointer to document to communicate with the document

	// All attributes here
	int m_nSize;
	int m_nLineWidth;
	int m_nLineAngle;
	float m_nAlpha;
	float m_nRedScale;
	float m_nBlueScale;
	float m_nGreenScale;
	float m_nDissolveAlpha;

	int m_nAutoSpacing;

	// Static class members
	static Fl_Menu_Item menuitems[];
	static Fl_Menu_Item brushTypeMenu[NUM_BRUSH_TYPE + 1];
	static Fl_Menu_Item strokeDirectionMenu[NUM_STROKE_TYPE + 1];

	static ImpressionistUI* whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared
	// static
	static void cb_load_image(Fl_Menu_* o, void* v);
	static void cb_save_image(Fl_Menu_* o, void* v);
	static void cb_brushes(Fl_Menu_* o, void* v);
	static void cb_clear_canvas(Fl_Menu_* o, void* v);
	static void cb_swap_content(Fl_Menu_* o, void* v);

	static void cb_undo(Fl_Menu_* o, void* v);
	static void cb_color(Fl_Menu_* o, void* v);
	static void cb_dissolve(Fl_Menu_* o, void* v);

	static void cb_exit(Fl_Menu_* o, void* v);
	static void cb_about(Fl_Menu_* o, void* v);
	static void cb_brushChoice(Fl_Widget* o, void* v);
	static void cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void cb_auto_draw_button(Fl_Widget* o, void* v);
	static void cb_load_image_button(Fl_Widget* o, void* v);
	static void cb_dissolveImage(Fl_Widget* o, void* v);
	static void cb_sizeSlides(Fl_Widget* o, void* v);
	static void cb_LineWidthSlides(Fl_Widget* o, void* v);
	static void cb_LineAngleSlides(Fl_Widget* o, void* v);
	static void cb_AlphaSlides(Fl_Widget* o, void* v);
	static void cb_RedSlides(Fl_Widget* o, void* v);
	static void cb_BlueSlides(Fl_Widget* o, void* v);
	static void cb_GreenSlides(Fl_Widget* o, void* v);
	static void cb_SpacingSlides(Fl_Widget* o, void* v);
	static void cb_strokeChoice(Fl_Widget* o, void* v);
	static void cb_DissolveSlides(Fl_Widget* o, void* v);
};

#endif
