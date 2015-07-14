#include "ofMain.h"
#include "ofAppGlfwWindow.h"
#include "LedCostumeApp.h"


//========================================================================
int main( ){
    
    ofAppGLFWWindow window;
    ofSetupOpenGL(&window,1280, 1024, OF_WINDOW);
    ofRunApp( new LedCostumeApp());
    
}