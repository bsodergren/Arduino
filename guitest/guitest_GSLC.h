//<File !Start!>
// FILE: [guitest_GSLC.h]
// Created by GUIslice Builder version: [0.17.b02]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XKeyPad_Alpha.h"
#include "elem/XTextbox.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if defined(DRV_DISP_TFT_ESPI)
  #error Project tab->Target Platform should be tft_espi
#endif
#include <Adafruit_GFX.h>
#include "Fonts/FreeMono18pt7b.h"
#include "Fonts/FreeMonoBold12pt7b.h"
#include "Fonts/FreeMonoBold12pt7b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_POP_KEYPAD_ALPHA};
enum {E_ELEM_CPS,E_ELEM_LIFTSIZE,E_ELEM_RIBBONS,E_ELEM_TEXTINPUT1
      ,T_ELEM_CPS,T_ELEM_Liftsize,T_ELEM_RIBBONS,E_ELEM_KEYPAD_ALPHA};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN5X8,E_DOSIS_BOOK16,E_FREEMONO18,E_FREEMONOBOLD12
      ,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                2

#define MAX_ELEM_PG_MAIN 7 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asKeypadAlphaElem[1];
gslc_tsElemRef                  m_asKeypadAlphaElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadAlpha;
gslc_tsXTextbox                 m_sTextbox3;
char                            m_acTextboxBuf3[6]; // NRows=1 NCols=6
gslc_tsXTextbox                 m_sTextbox5;
char                            m_acTextboxBuf5[6]; // NRows=1 NCols=6
gslc_tsXTextbox                 m_sTextbox6;
char                            m_acTextboxBuf6[6]; // NRows=1 NCols=6

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pElemCps;
extern gslc_tsElemRef* m_pElemInTxt1;
extern gslc_tsElemRef* m_pElemRibbobs;
extern gslc_tsElemRef* m_pElem_Liftsize;
extern gslc_tsElemRef* m_pTextSlider1;
extern gslc_tsElemRef* m_pTextSlider1;
extern gslc_tsElemRef* m_pTextSlider1;
extern gslc_tsElemRef* m_pElemKeyPadAlpha;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_DOSIS_BOOK16,GSLC_FONTREF_PTR,&dosis_book16pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREEMONO18,GSLC_FONTREF_PTR,&FreeMono18pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREEMONOBOLD12,GSLC_FONTREF_PTR,&FreeMonoBold12pt7b,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_ALPHA,m_asKeypadAlphaElem,1,m_asKeypadAlphaElemRef,1);  // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to an image
  gslc_SetBkgndImage(&m_gui,,));

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  
  // Create T_ELEM_Liftsize text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,T_ELEM_Liftsize,E_PG_MAIN,(gslc_tsRect){330,10,125,17},
    (char*)"Lift size",0,E_FREEMONOBOLD12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_LIFTSIZE,E_PG_MAIN,&m_sTextbox3,
    (gslc_tsRect){330,32,146,39},E_DOSIS_BOOK16,
    (char*)&m_acTextboxBuf3,1,6);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_RED);
  m_pElem_Liftsize = pElemRef;
  
  // Create T_ELEM_RIBBONS text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,T_ELEM_RIBBONS,E_PG_MAIN,(gslc_tsRect){330,76,98,17},
    (char*)"Ribbons",0,E_FREEMONOBOLD12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  
  // Create T_ELEM_CPS text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,T_ELEM_CPS,E_PG_MAIN,(gslc_tsRect){330,142,138,26},
    (char*)"Copies out",0,E_FREEMONOBOLD12);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_LEFT);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_CPS,E_PG_MAIN,&m_sTextbox5,
    (gslc_tsRect){330,173,146,39},E_DOSIS_BOOK16,
    (char*)&m_acTextboxBuf5,1,6);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_RED);
  m_pElemCps = pElemRef;
   
  // Create textbox
  pElemRef = gslc_ElemXTextboxCreate(&m_gui,E_ELEM_RIBBONS,E_PG_MAIN,&m_sTextbox6,
    (gslc_tsRect){330,98,146,39},E_DOSIS_BOOK16,
    (char*)&m_acTextboxBuf6,1,6);
  gslc_ElemXTextboxWrapSet(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_WHITE,GSLC_COL_RED);
  m_pElemRibbobs = pElemRef;
  
  // Create E_ELEM_TEXTINPUT1 text input field
  static char m_sInputText1[11] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXTINPUT1,E_PG_MAIN,(gslc_tsRect){310,290,180,22},
    (char*)m_sInputText1,11,E_FREEMONO18);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemInTxt1 = pElemRef;

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_ALPHA
  
  static gslc_tsXKeyPadCfg_Alpha sCfgTx;
  sCfgTx = gslc_ElemXKeyPadCfgInit_Alpha();
  m_pElemKeyPadAlpha = gslc_ElemXKeyPadCreate_Alpha(&m_gui, E_ELEM_KEYPAD_ALPHA, E_POP_KEYPAD_ALPHA,
    &m_sKeyPadAlpha, 65, 80, E_BUILTIN5X8, &sCfgTx);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadAlpha, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
