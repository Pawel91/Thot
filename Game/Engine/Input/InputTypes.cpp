#include "Input_PCH.h"
#include "InputTypes.h"

#include <map>
#include "Kernel/ThotWindows.h"

namespace InputKey
{
    typedef std::map<DWORD, EMouseButton>   TMouseMap;
    typedef std::map<DWORD, EKeys>          TKeyboardMap;
    TMouseMap                       mouseButtonMap;
    TKeyboardMap                    keyboardKeyIDMap;
    bool                            wasInitialized;
    struct SMapInitializer
    {
        SMapInitializer();
        void InitMaps();

        void InitKeyboardMap();
        void InitMouseMap();
    };

    SMapInitializer::SMapInitializer()
    {
        if( !wasInitialized )
        {
            InitMaps();
        }

        wasInitialized = true;
    }

    void SMapInitializer::InitMouseMap()
    {
        mouseButtonMap[RI_MOUSE_LEFT_BUTTON_DOWN    ] = E_MOUSEB_LEFT   ;
        mouseButtonMap[RI_MOUSE_RIGHT_BUTTON_DOWN   ] = E_MOUSEB_RIGHT  ;
        mouseButtonMap[RI_MOUSE_LEFT_BUTTON_UP      ] = E_MOUSEB_LEFT   ;
        mouseButtonMap[RI_MOUSE_RIGHT_BUTTON_UP     ] = E_MOUSEB_RIGHT  ;
        mouseButtonMap[RI_MOUSE_MIDDLE_BUTTON_DOWN  ] = E_MOUSEB_SCROLL ;
        mouseButtonMap[RI_MOUSE_MIDDLE_BUTTON_UP    ] = E_MOUSEB_SCROLL ;
    }


    void SMapInitializer::InitKeyboardMap()
    {
        keyboardKeyIDMap[VK_LSHIFT      ] = E_KEY_LSHIFT;
        keyboardKeyIDMap[VK_RSHIFT      ] = E_KEY_RSHIFT;
        keyboardKeyIDMap[VK_LCONTROL    ] = E_KEY_LCTRL;
        keyboardKeyIDMap[VK_LCONTROL    ] = E_KEY_LCTRL;
        keyboardKeyIDMap[VK_RCONTROL    ] = E_KEY_RCTRL;
        keyboardKeyIDMap[VK_RETURN      ] = E_KEY_ENTER;
        keyboardKeyIDMap[VK_CAPITAL     ] = E_KEY_CAPSLOCK;
        keyboardKeyIDMap[VK_ESCAPE      ] = E_KEY_ESC;
        keyboardKeyIDMap[VK_SPACE       ] = E_KEY_SPACE;
        keyboardKeyIDMap[VK_HOME        ] = E_KEY_HOME;
        keyboardKeyIDMap[VK_UP          ] = E_KEY_ARR_UP;
        keyboardKeyIDMap[VK_DOWN        ] = E_KEY_ARR_DOWN;
        keyboardKeyIDMap[VK_LEFT        ] = E_KEY_ARR_LEFT;
        keyboardKeyIDMap[VK_RIGHT       ] = E_KEY_ARR_RIGHT;
        keyboardKeyIDMap[VK_INSERT      ] = E_KEY_INSERT;
        keyboardKeyIDMap[VK_DELETE      ] = E_KEY_DELETE;
        keyboardKeyIDMap[VK_PRIOR       ] = E_KEY_PGUP;
        keyboardKeyIDMap[VK_NEXT        ] = E_KEY_PGDOWN;
        keyboardKeyIDMap[VK_LMENU       ] = E_KEY_LALT;
        keyboardKeyIDMap[VK_RMENU       ] = E_KEY_RALT;
        keyboardKeyIDMap[VK_OEM_1       ] = E_KEY_SEMICOLON;
        keyboardKeyIDMap[VK_OEM_PLUS    ] = E_KEY_PLUS;
        keyboardKeyIDMap[VK_OEM_COMMA   ] = E_KEY_COMMA;
        keyboardKeyIDMap[VK_OEM_MINUS   ] = E_KEY_MINUS;
        keyboardKeyIDMap[VK_OEM_PERIOD  ] = E_KEY_POINT;
        keyboardKeyIDMap[VK_OEM_2       ] = E_KEY_FORWARDSLASH;
        keyboardKeyIDMap[VK_OEM_3       ] = E_KEY_TILDA;
        keyboardKeyIDMap[VK_OEM_4       ] = E_KEY_OPEN_BRAKET;
        keyboardKeyIDMap[VK_OEM_5       ] = E_KEY_BACKSLASH;
        keyboardKeyIDMap[VK_OEM_6       ] = E_KEY_CLOSE_BRAKET;
        keyboardKeyIDMap[VK_OEM_7       ] = E_KEY_APOSTROPHE;
        keyboardKeyIDMap[VK_BACK        ] = E_KEY_BACKSPACE;
        keyboardKeyIDMap[VK_TAB         ] = E_KEY_TAB;
    }

    void SMapInitializer::InitMaps()
    {
        InitKeyboardMap();
        InitMouseMap();
    }

#define GUARD_GET_KEY_ID_FUNCT()\
    static SMapInitializer initializer

    INPUT_API EKeys GetFromNativeKeyID  ( u64 keyID )
    {
        GUARD_GET_KEY_ID_FUNCT();

        DWORD winkeyA = 0x41;
        DWORD winkeyZ = 0x5a;
        DWORD winkey0 = 0x30; // De modifiicat aici;
        DWORD winkey9 = 0x39; //

        DWORD vkCode = (DWORD)keyID;

        //[TODO] add this cases to map;
        if( vkCode >= winkeyA  && vkCode <=winkeyZ )
        {
            int idx = vkCode - winkeyA;
            int keyEnumIdx = (int)(InputKey::E_KEY_A);
            keyEnumIdx+= idx;
            InputKey::EKeys key = (InputKey::EKeys)(keyEnumIdx);
            return key;
        }
        if( vkCode >= winkey0  && vkCode <=winkey9 )
        {
            int idx = vkCode - winkey0;
            int keyEnumIdx = (int)(InputKey::E_KEY_0);
            keyEnumIdx+= idx;
            InputKey::EKeys key = (InputKey::EKeys)(keyEnumIdx);
            return key;
        }
        if( vkCode >= VK_F1  && vkCode <= VK_F12 )
        {
            int idx = vkCode - VK_F1;
            int keyEnumIdx = (int)(InputKey::E_KEY_F1);
            keyEnumIdx+= idx;
            InputKey::EKeys key = (InputKey::EKeys)(keyEnumIdx);
            return key;
        }

        TKeyboardMap::iterator it =  keyboardKeyIDMap.find((DWORD)keyID);
        if( it != keyboardKeyIDMap.end() )
        {
            return it->second;
        }

        return EKeys::E_KEY_INVALID;
    }

    INPUT_API EMouseButton GetFromNativeMouseButtonID  ( u64 keyID )
    {
        GUARD_GET_KEY_ID_FUNCT();
        TMouseMap::iterator it =  mouseButtonMap.find((DWORD)keyID);
        if( it == mouseButtonMap.end() )
        {
            return E_MOUSEB_INVALID;
        }
        return it->second;
    }

}
