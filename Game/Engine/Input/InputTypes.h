#pragma once
#ifndef __INPUT_TYPES_H__
#define __INPUT_TYPES_H__

#ifndef THOT_STRINGIFY
#   define THOT_STRINGIFY(_x) (#_x)
#endif /*THOT_STRINGIFY*/

#include "Input/InputDef.h"

namespace InputKey
{
    enum EKeys
    {
        E_KEY_INVALID = -1

        ,E_KEY_A                
        ,E_KEY_B                
        ,E_KEY_C                
        ,E_KEY_D                
        ,E_KEY_E                
        ,E_KEY_F                
        ,E_KEY_G                
        ,E_KEY_H                
                                
        ,E_KEY_I                
        ,E_KEY_J                
        ,E_KEY_K                
        ,E_KEY_L                
        ,E_KEY_M                
        ,E_KEY_N                
        ,E_KEY_O                
        ,E_KEY_P                
                                
        ,E_KEY_Q                
        ,E_KEY_R                
        ,E_KEY_S                
        ,E_KEY_T                
        ,E_KEY_U                
        ,E_KEY_V                
        ,E_KEY_W                
        ,E_KEY_X                
                                
        ,E_KEY_Y                
        ,E_KEY_Z                
        ,E_KEY_ENTER            
        ,E_KEY_SPACE            
        ,E_KEY_TAB                
        ,E_KEY_CAPSLOCK            
        ,E_KEY_LSHIFT            
        ,E_KEY_LCTRL            
                                
        ,E_KEY_LALT                
        ,E_KEY_RSHIFT            
        ,E_KEY_RCTRL            
        ,E_KEY_RALT                
        ,E_KEY_BACKSPACE        
        ,E_KEY_ARR_UP            
        ,E_KEY_ARR_DOWN            
        ,E_KEY_ARR_LEFT            
                                
        ,E_KEY_ARR_RIGHT        
        ,E_KEY_PGUP                
        ,E_KEY_PGDOWN            
        ,E_KEY_HOME                
        ,E_KEY_INSERT            
        ,E_KEY_DELETE            
        ,E_KEY_TILDA            
        ,E_KEY_0                
                                
        ,E_KEY_1                
        ,E_KEY_2                
        ,E_KEY_3                
        ,E_KEY_4                
        ,E_KEY_5                
        ,E_KEY_6                
        ,E_KEY_7                
        ,E_KEY_8                
                                
        ,E_KEY_9                
        ,E_KEY_ESC                
        ,E_KEY_F1                
        ,E_KEY_F2                
        ,E_KEY_F3                
        ,E_KEY_F4                
        ,E_KEY_F5                
        ,E_KEY_F6                
                                
        ,E_KEY_F7                
        ,E_KEY_F8                
        ,E_KEY_F9                
        ,E_KEY_F10                
        ,E_KEY_F11                
        ,E_KEY_F12                
        ,E_KEY_MINUS            
        ,E_KEY_PLUS                
                                
        ,E_KEY_OPEN_BRAKET        
        ,E_KEY_CLOSE_BRAKET        
        ,E_KEY_BACKSLASH        
        ,E_KEY_FORWARDSLASH        
        ,E_KEY_POINT            
        ,E_KEY_COMMA            
        ,E_KEY_SEMICOLON        
        ,E_KEY_APOSTROPHE        
                                


        ,E_KEY_COUNT
        ,E_KEY_BYTES_COUNT        = E_KEY_COUNT/8 +1    // number of bytes that will be used for buffer;
        //,E_KEY_FORCE_DWORD        = FORCE_DWORD
    };

    enum EMouseButton
    {
        E_MOUSEB_INVALID = -1

        ,E_MOUSEB_LEFT        
        ,E_MOUSEB_RIGHT        
        ,E_MOUSEB_SCROLL    
    
        ,E_MOUSEB_COUNT
        ,E_MOUSEB_BYTES_COUNT    = E_MOUSEB_COUNT/8 +1
        //,E_MOUSEB_FORCE_DWORD    = FORCE_DWORD
    };

INPUT_API       EKeys           GetFromNativeKeyID          ( u64 keyID );
INPUT_API       EMouseButton    GetFromNativeMouseButtonID  ( u64 keyID );

const char MOUSEB_STRING_ARRAY[E_MOUSEB_COUNT][32] = 
{
         THOT_STRINGIFY(E_MOUSEB_LEFT    )
        ,THOT_STRINGIFY(E_MOUSEB_RIGHT   )    
        ,THOT_STRINGIFY(E_MOUSEB_SCROLL  )
};

const char KEY_STRING_ARRAY[E_KEY_COUNT][32] = 
{
THOT_STRINGIFY(E_KEY_A               )
,THOT_STRINGIFY(E_KEY_B              )
,THOT_STRINGIFY(E_KEY_C              )
,THOT_STRINGIFY(E_KEY_D              )
,THOT_STRINGIFY(E_KEY_E              )
,THOT_STRINGIFY(E_KEY_F              )
,THOT_STRINGIFY(E_KEY_G              )
,THOT_STRINGIFY(E_KEY_H              )
,THOT_STRINGIFY(E_KEY_I              )
,THOT_STRINGIFY(E_KEY_J              )
,THOT_STRINGIFY(E_KEY_K              )
,THOT_STRINGIFY(E_KEY_L              )
,THOT_STRINGIFY(E_KEY_M              )
,THOT_STRINGIFY(E_KEY_N              )
,THOT_STRINGIFY(E_KEY_O              )
,THOT_STRINGIFY(E_KEY_P              )
,THOT_STRINGIFY(E_KEY_Q              )
,THOT_STRINGIFY(E_KEY_R              )
,THOT_STRINGIFY(E_KEY_S              )
,THOT_STRINGIFY(E_KEY_T              )
,THOT_STRINGIFY(E_KEY_U              )
,THOT_STRINGIFY(E_KEY_V              )
,THOT_STRINGIFY(E_KEY_W              )
,THOT_STRINGIFY(E_KEY_X              )
,THOT_STRINGIFY(E_KEY_Y              )
,THOT_STRINGIFY(E_KEY_Z              )
,THOT_STRINGIFY(E_KEY_ENTER          )
,THOT_STRINGIFY(E_KEY_SPACE          )
,THOT_STRINGIFY(E_KEY_TAB            )
,THOT_STRINGIFY(E_KEY_CAPSLOCK       )
,THOT_STRINGIFY(E_KEY_LSHIFT         )
,THOT_STRINGIFY(E_KEY_LCTRL          )
,THOT_STRINGIFY(E_KEY_LALT           )
,THOT_STRINGIFY(E_KEY_RSHIFT         )
,THOT_STRINGIFY(E_KEY_RCTRL          )
,THOT_STRINGIFY(E_KEY_RALT           )
,THOT_STRINGIFY(E_KEY_BACKSPACE      )
,THOT_STRINGIFY(E_KEY_ARR_UP         )
,THOT_STRINGIFY(E_KEY_ARR_DOWN       )
,THOT_STRINGIFY(E_KEY_ARR_LEFT       )
,THOT_STRINGIFY(E_KEY_ARR_RIGHT      )
,THOT_STRINGIFY(E_KEY_PGUP           )
,THOT_STRINGIFY(E_KEY_PGDOWN         )
,THOT_STRINGIFY(E_KEY_HOME           )
,THOT_STRINGIFY(E_KEY_INSERT         )
,THOT_STRINGIFY(E_KEY_DELETE         )
,THOT_STRINGIFY(E_KEY_TILDA          )
,THOT_STRINGIFY(E_KEY_0              )
,THOT_STRINGIFY(E_KEY_1              )
,THOT_STRINGIFY(E_KEY_2              )
,THOT_STRINGIFY(E_KEY_3              )
,THOT_STRINGIFY(E_KEY_4              )
,THOT_STRINGIFY(E_KEY_5              )
,THOT_STRINGIFY(E_KEY_6              )
,THOT_STRINGIFY(E_KEY_7              )
,THOT_STRINGIFY(E_KEY_8              )
,THOT_STRINGIFY(E_KEY_9              )
,THOT_STRINGIFY(E_KEY_ESC            )
,THOT_STRINGIFY(E_KEY_F1             )
,THOT_STRINGIFY(E_KEY_F2             )
,THOT_STRINGIFY(E_KEY_F3             )
,THOT_STRINGIFY(E_KEY_F4             )
,THOT_STRINGIFY(E_KEY_F5             )
,THOT_STRINGIFY(E_KEY_F6             )
,THOT_STRINGIFY(E_KEY_F7             )
,THOT_STRINGIFY(E_KEY_F8             )
,THOT_STRINGIFY(E_KEY_F9             )
,THOT_STRINGIFY(E_KEY_F10            )
,THOT_STRINGIFY(E_KEY_F11            )
,THOT_STRINGIFY(E_KEY_F12            )
,THOT_STRINGIFY(E_KEY_MINUS          )
,THOT_STRINGIFY(E_KEY_PLUS           )
,THOT_STRINGIFY(E_KEY_OPEN_BRAKET    )
,THOT_STRINGIFY(E_KEY_CLOSE_BRAKET   )
,THOT_STRINGIFY(E_KEY_BACKSLASH      )
,THOT_STRINGIFY(E_KEY_FORWARDSLASH   )
,THOT_STRINGIFY(E_KEY_POINT          )
,THOT_STRINGIFY(E_KEY_COMMA          )
,THOT_STRINGIFY(E_KEY_SEMICOLON      )
,THOT_STRINGIFY(E_KEY_APOSTROPHE     )
};

} // namespace InputKey

namespace InputDevices
{
    enum eDevices
    {
         E_INPUT_DEVICE_NONE            = -1
        ,E_INPUT_DEVICE_KEYBOARD
        ,E_INPUT_DEVICE_MOUSE


        ,E_INPUT_DEVICE_COUNT
        //,E_INPUT_DEVICE_FORCE_DWORD = FORCE_DWORD
    };
}




#endif /*__INPUT_TYPES_H__*/