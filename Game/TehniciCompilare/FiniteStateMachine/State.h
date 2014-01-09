#pragma once
#ifndef __TEHNICI_COMPILARE_STATE_H__
#define __TEHNICI_COMPILARE_STATE_H__


#include "StateTypes.h"


#ifdef _DEBUG

#define ENABLE_TRACE_FSM_TRANZITIONS

#endif /*_DEBUG*/

#ifdef ENABLE_TRACE_FSM_TRANZITIONS
#   define TRACE_FSM_TRANZITIONS( __format, ... ) THOT_TRACE_LINE( __format, __VA_ARGS__ )
#else
#   define TRACE_FSM_TRANZITIONS(__format, ... ) void(0)
#endif /*ENABLE_TRACE_FSM_TRANZITIONS*/


template< class T0, class T1 >
class CPair
{
public:
        CPair( T0 first, T1 second );
        CPair(){}

        T0      m_first;
        T1      m_second;
};


template< class Type_Input>
class CAutomataState
{
    THOT_DECLARE_NOCOPY_CLASS(CAutomataState);

private:
     CAutomataState( ); // use only factory function to create states

public:
    ~CAutomataState( );

public:    

    typedef CAutomataState<Type_Input>                  TSelf;
    typedef CPair<Type_Input, TSelf*>                   TInputPair;
    typedef CVector<TInputPair>                         TInputs;
    typedef s32 (*TInputCompareFunction)(const Type_Input& op1, const Type_Input& op2);

static      TSelf*      CreateAutomataState     ( EStateType, const char* tag = NULL );

static      u64         ms_invalidInputIndex;

//callbacks
virtual void            OnEnter         ( ){}
virtual void            OnExit          ( ){}

        Bool            IsFinal         ( );
        Bool            IsInitial       ( );

        void            SetStateType    ( EStateType stateType )            { m_eStateType = stateType; }
        EStateType      GetStateType    ( ) const                           { return m_eStateType;}
        Bool            IsInputValid    ( const Type_Input& input ) const;
        const TSelf*    GetNextState    ( const Type_Input& input ) const;
        TSelf*          GetNextState    ( const Type_Input& input );

        Bool            AddInput        ( const Type_Input& input, TSelf* nextState );
        Bool            AddInput        ( const CVector<Type_Input>& arrayInputs, TSelf* nextState );

static  void            RegisterCompareFunction ( TInputCompareFunction inputCompareFunction );

        CString                 m_tag;          // for debug
protected:

        u64             Find            ( const Type_Input& input ) const;

protected:

        EStateType              m_eStateType;
        TInputs                 m_inputs;
static  TInputCompareFunction   ms_compareInputFunction; // function to compare inputs

};


#include "State.inl"


#endif /*__TEHNICI_COMPILARE_STATE_H__*/