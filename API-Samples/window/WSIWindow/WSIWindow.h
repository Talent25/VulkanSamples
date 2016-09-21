// NOTE: WSIWindow.h MUST be inculded BEFORE sdtio.h, for printf to work correctly on Android.

// TODO:
//
// Message loop vsync
// Enable/Disable text event for better performance, and allows Android to show/hide on-screen keyboard.
// Multi-touch input (WIP in window_android.cpp)
// Clipboard and IME
// Multi-window support
// Documentation
// Keyboard: function to get native keycode
// Android: window resize events (WIP)
// Split OnShapeEvent into OnResizeEvent and OnMoveEvent?

#ifdef ANDROID
  #include <native.h>
#endif

//#include <stdio.h>
//#include <vulkan/vulkan.h>

#include "CInstance.h"
#include "keycodes.h"

#ifndef WSIWINDOW_H
#define WSIWINDOW_H

typedef unsigned int uint;
enum eMouseAction{ mMOVE, mDOWN, mUP };
enum eKeyAction  { keyDOWN, keyUP };

class WindowImpl;

//===========================WSIWindow==========================
class WSIWindow{
    WindowImpl* pimpl;
public:
    WSIWindow(CInstance& inst, const char* title, uint width, uint height);
    //WSIWindow(const char* title,uint width,uint height);
    virtual ~WSIWindow();

    bool GetKeyState(eKeycode key);               //Returns true if specified key is pressed. (see keycodes.h)
    bool GetBtnState(uint8_t  btn);               //Returns true if specified mouse button is pressed (button 1-5)
    void GetMousePos(int16_t& x, int16_t& y);     //Get mouse (x,y) coordinate within window client area
    void Close();                                 //Close the window
    //void SetTextInput(bool enabled);              //Enable OnTextEvent, (and on Android, show the soft-keyboard)
    //bool GetTextInput();                          //Returns true if text input is enabled (and on android, keyboard is visible.)
    void ShowKeyboard(bool enabled);              //on Android, show the soft-keyboard.




    //bool PollEvent();
    bool ProcessEvents();                         //Process keyboard and mouse events, and calls appropriate event handlers.

    //-- Virtual Functions as event handlers --
    virtual void OnMouseEvent(eMouseAction action, int16_t x, int16_t y, uint8_t btn){}   //Callback for mouse events
    virtual void OnKeyEvent  (eKeyAction   action, uint8_t keycode){}                     //Callback for keyboard events (keycodes)
    virtual void OnTextEvent (const char* str){}                                          //Callback for text typed events (text)
    virtual void OnShapeEvent(int16_t x, int16_t y, uint16_t width, uint16_t height){}    //Callback for window move/resize events
    virtual void OnFocusEvent(bool hasFocus){}                                            //Callback for window gain/lose focus events
    virtual void OnTouchEvent(eMouseAction action, float x, float y, uint8_t id){}        //Callback for Multi-touch events
};
//==============================================================

#endif
