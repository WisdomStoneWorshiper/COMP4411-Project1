//
// impressionistUI.h
//
// The user interface part for the program.
//

#include "ImpressionistUI.h"

#include "ImpressionistDoc.h"

#include <FL/fl_ask.h>
#include <math.h>

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the
project.  You can copy and paste these into your code and then change them to
make them look how you want.  Descriptions for all of the widgets here can be found
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------

	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions

		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
	m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v)
	{
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
	mySlider->labelfont(FL_COURIER);
	mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}


//------------Choice---------------------------------------

	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);

	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------

	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

	//---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o) { return ((ImpressionistUI*)(o->parent()->user_data())); }

//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}

void ImpressionistUI::cb_mural_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadMuralImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp");
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) { whoami(o)->m_brushDialog->show(); }

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();

	pDoc->clearCanvas();
}

void ImpressionistUI::cb_swap_content(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	// ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	unsigned char* temp = pDoc->m_ucBitmap;
	pDoc->m_ucBitmap = pDoc->m_ucPainting;
	pDoc->m_ucPainting = temp;
	pDoc->m_pUI->m_origView->refresh();
	pDoc->m_pUI->m_paintView->refresh();
}

void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v) {
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->undo();
	// ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	// pUI->m_paintView->undo();
}

// Color callback function
void ImpressionistUI::cb_color(Fl_Menu_* o, void* v) { whoami(o)->m_colorDialog->show(); }

// Dissolve callback function
void ImpressionistUI::cb_dissolve(Fl_Menu_* o, void* v) { whoami(o)->m_dissolveDialog->show(); }

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) {
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) {
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush
// choice.
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)(size_t)v;

	pDoc->setBrushType(type);
	if (pUI->m_StrokeDirectionChoice != nullptr) {
		if (type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES) {
			pUI->m_StrokeDirectionChoice->activate();
			pUI->m_LineWidthSlider->activate();
			pUI->m_LineAngleSlider->activate();

		} else if (type == BRUSH_ALPHA_MAPPING) {
			pUI->m_StrokeDirectionChoice->deactivate();
			pUI->m_LineWidthSlider->deactivate();
			pUI->m_LineAngleSlider->deactivate();
			pUI->m_BrushSizeSlider->deactivate();
			pUI->m_AlphaSlider->deactivate();
		} else {
			pUI->m_StrokeDirectionChoice->deactivate();
			pUI->m_LineWidthSlider->deactivate();
			pUI->m_LineAngleSlider->deactivate();
			pUI->m_BrushSizeSlider->activate();
			pUI->m_AlphaSlider->activate();
		}
	}
}

void ImpressionistUI::cb_strokeChoice(Fl_Widget* o, void* v) {
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int type = (int)(size_t)v;

	pDoc->setStrokeType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

void ImpressionistUI::cb_load_alphaMap_button(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAlphaMapImage(newfile);
	}
}

void ImpressionistUI::cb_auto_draw_button(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->m_pUI->m_paintView->at_draw();
	// pDoc->auto_draw();
}
#include "KernalBrush.h"

#include <cstring>
#include <iostream>
void ImpressionistUI::cb_apply_filter_button(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	reinterpret_cast<KernalBrush*>(ImpBrush::c_pBrushes[BRUSH_KERNAL])
		->setKernalFilter((std::string)pDoc->m_pUI->m_KernalFilter->value());
	// std::cout << (std::string)pDoc->m_pUI->m_KernalFilter->value();

	// pDoc->auto_draw();
}

void ImpressionistUI::cb_normalize_button(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	static bool n = false;
	n = !n;
	reinterpret_cast<KernalBrush*>(ImpBrush::c_pBrushes[BRUSH_KERNAL])->set_normalize(n);
}

void ImpressionistUI::cb_load_image_button(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadDissolveImage(newfile);
	}
}

void ImpressionistUI::cb_dissolveImage(Fl_Widget* o, void* v) {
	ImpressionistDoc* pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->dissolveImage();
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nSize = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_LineWidthSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_LineAngleSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle = int(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_AlphaSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = float(((Fl_Slider*)o)->value());
}


void ImpressionistUI::cb_RedSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nRedScale = float(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_BlueSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nBlueScale = float(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_GreenSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nGreenScale = float(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_SpacingSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nAutoSpacing = float(((Fl_Slider*)o)->value());
}

void ImpressionistUI::cb_DissolveSlides(Fl_Widget* o, void* v) {
	((ImpressionistUI*)(o->user_data()))->m_nDissolveAlpha = float(((Fl_Slider*)o)->value());
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument() { return m_pDoc; }

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w, h);
	m_origView->size(w, h);
}

//------------------------------------------------
// Set the ImpressionistDoc used by the UI to
// communicate with the brushes
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc) {
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize() { return m_nSize; }

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize(int size) {
	m_nSize = size;

	if (size <= 40)
		m_BrushSizeSlider->value(m_nSize);
}

int ImpressionistUI::getLineWidth() { return m_nLineWidth; }

void ImpressionistUI::setLineWidth(int lineWidth) { m_nLineWidth = lineWidth; }

int ImpressionistUI::getLineAngle() { return m_nLineAngle; }

void ImpressionistUI::setLineAngle(int lineAngle) { m_nLineAngle = lineAngle; }

float ImpressionistUI::getAlpha() { return m_nAlpha; }

float ImpressionistUI::getRedScale() { return m_nRedScale; }
float ImpressionistUI::getBlueScale() { return m_nBlueScale; }
float ImpressionistUI::getGreenScale() { return m_nGreenScale; }
int ImpressionistUI::getAutoSpacing() { return m_nAutoSpacing; }
float ImpressionistUI::getDissolveAlpha() { return m_nDissolveAlpha; }

void ImpressionistUI::setAlpha(float alpha) {
	m_nAlpha = alpha;

	if (alpha <= 1.0)
		m_AlphaSlider->value(m_nAlpha);
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{"&File", 0, 0, 0, FL_SUBMENU},
	{"&Load Image...", FL_ALT + 'l', (Fl_Callback*)ImpressionistUI::cb_load_image},
	{"&Save Image...", FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_save_image},
	{"&Brushes...", FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_brushes},
	{"&Clear Canvas", FL_ALT + 'c', (Fl_Callback*)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER},
	{"&Swap Content", FL_ALT + 'w', (Fl_Callback*)ImpressionistUI::cb_swap_content},
	{"&Colors", FL_ALT + 'y', (Fl_Callback*)ImpressionistUI::cb_color},
	{"&Dissolve Image", FL_ALT + 'd', (Fl_Callback*)ImpressionistUI::cb_dissolve},
	{"&New Mural Image", FL_ALT + 'm', (Fl_Callback*)ImpressionistUI::cb_mural_image},

	{"&Quit", FL_ALT + 'q', (Fl_Callback*)ImpressionistUI::cb_exit},
	{0},

	{"&Option", 0, 0, 0, FL_SUBMENU},
	{"&Undo", FL_CTRL + 'z', (Fl_Callback*)ImpressionistUI::cb_undo},
	{0},

	{"&Help", 0, 0, 0, FL_SUBMENU},
	{"&About", FL_ALT + 'a', (Fl_Callback*)ImpressionistUI::cb_about},
	{0},

	{0}};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE + 1] = {
	{"Points", FL_ALT + 'p', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_POINTS},
	{"Lines", FL_ALT + 'l', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_LINES},
	{"Circles", FL_ALT + 'c', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_CIRCLES},
	{"Scattered Points", FL_ALT + 'q', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SCATTERED_POINTS},
	{"Scattered Lines", FL_ALT + 'm', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SCATTERED_LINES},
	{"Scattered Circles", FL_ALT + 'd', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SCATTERED_CIRCLES},
	{"Filter Points", FL_ALT + 'f', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_FILTER_POINTS},
	{"Kernal", FL_ALT + 'f', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_KERNAL},
	{"Alpha Mapped", FL_ALT + 'x', (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_ALPHA_MAPPING},
	{0}};

Fl_Menu_Item ImpressionistUI::strokeDirectionMenu[NUM_STROKE_TYPE + 1] = {
	{"Slider/Right Click", FL_ALT + 's', (Fl_Callback*)ImpressionistUI::cb_strokeChoice, (void*)SLIDER_RIGHT_CLICK},
	{"Gradient", FL_ALT + 'g', (Fl_Callback*)ImpressionistUI::cb_strokeChoice, (void*)GRADIENT},
	{"Brush Direction", FL_ALT + 'b', (Fl_Callback*)ImpressionistUI::cb_strokeChoice, (void*)BRUSH_DIRECTION},
	{0}};

//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
	m_mainWindow->user_data((void*)(this)); // record self to be used by static callback functions
	// install menu bar
	m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
	m_menubar->menu(menuitems);

	// Create a group that will hold two sub windows inside the main
	// window
	Fl_Group* group = new Fl_Group(0, 25, 600, 275);

	// install paint view window
	m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view"); // 0jon
	m_paintView->box(FL_DOWN_FRAME);

	// install original view window
	m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view"); // 300jon
	m_origView->box(FL_DOWN_FRAME);
	m_origView->deactivate();

	group->end();
	Fl_Group::current()->resizable(group);
	m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 2;
	m_nLineAngle = 0;
	m_nAlpha = 1.0;
	m_nRedScale = 1.0;
	m_nBlueScale = 1.0;
	m_nGreenScale = 1.0;
	m_nAutoSpacing = 4;
	m_nDissolveAlpha = 1.0;
	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 325, "Brush Dialog");
	// Add a brush type choice to the dialog
	m_BrushTypeChoice = new Fl_Choice(50, 10, 150, 25, "&Brush");
	m_BrushTypeChoice->user_data((void*)(this)); // record self to be used by static callback functions
	m_BrushTypeChoice->menu(brushTypeMenu);
	m_BrushTypeChoice->callback(cb_brushChoice);

	m_ClearCanvasButton = new Fl_Button(240, 10, 150, 25, "&Clear Canvas");
	m_ClearCanvasButton->user_data((void*)(this));
	m_ClearCanvasButton->callback(cb_clear_canvas_button);

	m_loadAlphaMapImage = new Fl_Button(10, 260, 180, 25, "&Load AlphaMap Image");
	m_loadAlphaMapImage->user_data((void*)(this));
	m_loadAlphaMapImage->callback(cb_load_alphaMap_button);

	m_StrokeDirectionChoice = new Fl_Choice(113, 40, 150, 25, "&Stroke Direction");
	m_StrokeDirectionChoice->user_data((void*)(this)); // record self to be used by static callback functions
	m_StrokeDirectionChoice->menu(strokeDirectionMenu);
	m_StrokeDirectionChoice->callback(cb_strokeChoice);
	m_StrokeDirectionChoice->deactivate();

	// Add brush size slider to the dialog
	m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
	m_BrushSizeSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
	m_BrushSizeSlider->labelfont(FL_COURIER);
	m_BrushSizeSlider->labelsize(12);
	m_BrushSizeSlider->minimum(1);
	m_BrushSizeSlider->maximum(40);
	m_BrushSizeSlider->step(1);
	m_BrushSizeSlider->value(m_nSize);
	m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
	m_BrushSizeSlider->callback(cb_sizeSlides);

	m_LineWidthSlider = new Fl_Value_Slider(10, 100, 300, 20, "Line Width");
	m_LineWidthSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
	m_LineWidthSlider->labelfont(FL_COURIER);
	m_LineWidthSlider->labelsize(12);
	m_LineWidthSlider->minimum(1);
	m_LineWidthSlider->maximum(40);
	m_LineWidthSlider->step(1);
	m_LineWidthSlider->value(m_nLineWidth);
	m_LineWidthSlider->align(FL_ALIGN_RIGHT);
	m_LineWidthSlider->callback(cb_LineWidthSlides);
	m_LineWidthSlider->deactivate();

	m_LineAngleSlider = new Fl_Value_Slider(10, 120, 300, 20, "Line Angle");
	m_LineAngleSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
	m_LineAngleSlider->labelfont(FL_COURIER);
	m_LineAngleSlider->labelsize(12);
	m_LineAngleSlider->minimum(0);
	m_LineAngleSlider->maximum(359);
	m_LineAngleSlider->step(1);
	m_LineAngleSlider->value(m_nLineAngle);
	m_LineAngleSlider->align(FL_ALIGN_RIGHT);
	m_LineAngleSlider->callback(cb_LineAngleSlides);
	m_LineAngleSlider->deactivate();

	m_AlphaSlider = new Fl_Value_Slider(10, 140, 300, 20, "Alpha");
	m_AlphaSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
	m_AlphaSlider->labelfont(FL_COURIER);
	m_AlphaSlider->labelsize(12);
	m_AlphaSlider->minimum(0);
	m_AlphaSlider->maximum(1);
	m_AlphaSlider->step(0.01);
	m_AlphaSlider->value(m_nAlpha);
	m_AlphaSlider->align(FL_ALIGN_RIGHT);
	m_AlphaSlider->callback(cb_AlphaSlides);

	m_AutoSpacingSlider = new Fl_Value_Slider(10, 160, 150, 20, "Spacing");
	m_AutoSpacingSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_AutoSpacingSlider->type(FL_HOR_NICE_SLIDER);
	m_AutoSpacingSlider->labelfont(FL_COURIER);
	m_AutoSpacingSlider->labelsize(12);
	m_AutoSpacingSlider->minimum(1);
	m_AutoSpacingSlider->maximum(40);
	m_AutoSpacingSlider->step(1);
	m_AutoSpacingSlider->value(m_nAutoSpacing);
	m_AutoSpacingSlider->align(FL_ALIGN_RIGHT);
	m_AutoSpacingSlider->callback(cb_SpacingSlides);

	m_AutoDrawButton = new Fl_Button(300, 160, 70, 20, "&Auto Draw");
	m_AutoDrawButton->user_data((void*)(this));
	m_AutoDrawButton->callback(cb_auto_draw_button);

	m_KernalFilter = new Fl_Input(90, 180, 150, 50, "&Kernel Filter");
	m_KernalFilter->user_data((void*)(this));

	m_ApplyFilterButton = new Fl_Button(300, 180, 70, 20, "&Apply");
	m_ApplyFilterButton->user_data((void*)(this));
	m_ApplyFilterButton->callback(cb_apply_filter_button);

	m_Normalize = new Fl_Light_Button(300, 200, 90, 20, "&Normalize");
	m_Normalize->user_data((void*)(this));

	m_brushDialog->end();

	m_colorDialog = new Fl_Window(375, 200, "Color Dialog");

	m_redSlider = new Fl_Value_Slider(10, 40, 300, 20, "Red");
	m_redSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_redSlider->type(FL_HOR_NICE_SLIDER);
	m_redSlider->labelfont(FL_COURIER);
	m_redSlider->labelsize(12);
	m_redSlider->minimum(0);
	m_redSlider->maximum(1);
	m_redSlider->step(0.01);
	m_redSlider->value(m_nRedScale);
	m_redSlider->align(FL_ALIGN_RIGHT);
	m_redSlider->callback(cb_RedSlides);

	m_greenSlider = new Fl_Value_Slider(10, 80, 300, 20, "Green");
	m_greenSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_greenSlider->type(FL_HOR_NICE_SLIDER);
	m_greenSlider->labelfont(FL_COURIER);
	m_greenSlider->labelsize(12);
	m_greenSlider->minimum(0);
	m_greenSlider->maximum(1);
	m_greenSlider->step(0.01);
	m_greenSlider->value(m_nGreenScale);
	m_greenSlider->align(FL_ALIGN_RIGHT);
	m_greenSlider->callback(cb_GreenSlides);

	m_blueSlider = new Fl_Value_Slider(10, 120, 300, 20, "Blue");
	m_blueSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_blueSlider->type(FL_HOR_NICE_SLIDER);
	m_blueSlider->labelfont(FL_COURIER);
	m_blueSlider->labelsize(12);
	m_blueSlider->minimum(0);
	m_blueSlider->maximum(1);
	m_blueSlider->step(0.01);
	m_blueSlider->value(m_nBlueScale);
	m_blueSlider->align(FL_ALIGN_RIGHT);
	m_blueSlider->callback(cb_BlueSlides);


	m_colorDialog->end();

	m_dissolveDialog = new Fl_Window(375, 150, "Dissolve Dialog");

	m_loadImageButton = new Fl_Button(200, 10, 150, 25, "&Load Image");
	m_loadImageButton->user_data((void*)(this));
	m_loadImageButton->callback(cb_load_image_button);

	m_dissolveImageButton = new Fl_Button(30, 10, 150, 25, "&Dissolve");
	m_dissolveImageButton->user_data((void*)(this));
	m_dissolveImageButton->callback(cb_dissolveImage);

	m_dissolveSlider = new Fl_Value_Slider(30, 80, 300, 20, "Alpha");
	m_dissolveSlider->user_data((void*)(this)); // record self to be used by static callback functions
	m_dissolveSlider->type(FL_HOR_NICE_SLIDER);
	m_dissolveSlider->labelfont(FL_COURIER);
	m_dissolveSlider->labelsize(12);
	m_dissolveSlider->minimum(0);
	m_dissolveSlider->maximum(1);
	m_dissolveSlider->step(0.01);
	m_dissolveSlider->value(m_nDissolveAlpha);
	m_dissolveSlider->align(FL_ALIGN_RIGHT);
	m_dissolveSlider->callback(cb_DissolveSlides);

	m_dissolveDialog->end();
}
