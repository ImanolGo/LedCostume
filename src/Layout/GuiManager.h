/*
 *  GuiManager.h
 *  LED Costume
 *
 *  Created by Imanol Gomez on 07/07/15.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxGui.h"
//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application´s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    
public:

    //! Constructor
    GuiManager();

    //! Destructor
    ~GuiManager();

    //! Set-up the gui
    void setup();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
private:
    
    void setupGuiParameters();
    
    void setupNoiseGui();
    
    void setupImageGui();

public:
    
     static const int GUI_WIDTH;

private:
    
    // Fluid GUI
    ofxPanel			m_gui;
    
    ofParameter<float>	m_guiFPS;
    
    
    ofParameterGroup    m_parametersNoise;
    ofParameterGroup    m_parametersImage;
    
    ofParameter<bool>     m_imageRecord;
    ofParameter<bool>     m_imageLoop;
    
    ofParameter<int>      m_noiseResolution;
    ofParameter<float>    m_noiseFrequency;
    ofParameter<float>    m_noiseSpeed;
    ofParameter<int>      m_noiseHue;
    ofParameter<int>      m_noiseBrightness;
    
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================


