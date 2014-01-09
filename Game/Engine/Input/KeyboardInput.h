#ifndef __KEYBOARD_INPUT_H__
#define __KEYBOARD_INPUT_H__

#include "Input.h"

#include "Kernel/Basics.h"
#include "Kernel/DataStructures/Array/Array.h"

class CKeyInput:public CDeviceInputInterface
{
public:
             CKeyInput();
virtual        ~CKeyInput(){}

virtual        Bool            ButtonPress                ( InputKey::EKeys eKey ) const;
virtual        Bool            ButtonUp                ( InputKey::EKeys eKey ) const;
virtual        Bool            ButtonDown                ( InputKey::EKeys eKey ) const;

virtual        void            OnBeforeUserInput        ( );    
virtual        void            OnAfterUserInput        ( );    
virtual        void            ClearInputBuffer        ( );
virtual        void            OnUserInput                ( InputKey::EKeys eKey, Bool bButtonDown ); // take input on this frame

protected:
            void            SwapInputBuffers        ( );
            Bool            ButtonPress                ( InputKey::EKeys eKey, Bool bThisFrame = true )const;
            void            ClearInputForThisFrame    ();

typedef CStaticArray< unsigned char, InputKey::E_KEY_BYTES_COUNT> tInputBuffer;
        
        tInputBuffer        m_aBuffer1;
        tInputBuffer        m_aBuffer2;

        tInputBuffer*        m_pInput;
        tInputBuffer*        m_pLastFrameInput;
};


#endif /*__KEYBOARD_INPUT_H__*/