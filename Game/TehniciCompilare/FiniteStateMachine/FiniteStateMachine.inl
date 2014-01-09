

#ifndef DECLARE_DEFAULT_CONSTRUCTOR_LIST
#define DECLARE_DEFAULT_CONSTRUCTOR_LIST \
    :m_initialState     ( NULL )        \
    ,m_currentState     ( NULL )

#else
#   error DECLARE_DEFAULT_CONSTRUCTOR_LIST allready defined
#endif /*DECLARE_DEFAULT_CONSTRUCTOR_LIST*/


template<class T>
THOT_FORCE_INLINE CFiniteStateMachine<T>::CFiniteStateMachine()
    DECLARE_DEFAULT_CONSTRUCTOR_LIST
{

}



#undef DECLARE_DEFAULT_CONSTRUCTOR_LIST

template<class T>
THOT_FORCE_INLINE CFiniteStateMachine<T>::~CFiniteStateMachine()
{
    
}

template<class T>
THOT_FORCE_INLINE typename CFiniteStateMachine<T>::TState* CFiniteStateMachine<T>::GetCurrentState()
{
    return m_currentState;
}

template<class T>
THOT_FORCE_INLINE typename const CFiniteStateMachine<T>::TState* CFiniteStateMachine<T>::GetCurrentState()const
{
    return m_currentState;
}

template<class T>
THOT_FORCE_INLINE typename CFiniteStateMachine<T>::TState* CFiniteStateMachine<T>::GetInitialState()
{
    return m_initialState;
}

template<class T>
THOT_FORCE_INLINE typename const CFiniteStateMachine<T>::TState* CFiniteStateMachine<T>::GetInitialState()const
{
    return m_initialState;
}

template<class T>
Bool CFiniteStateMachine<T>::TakeInput( const T& input )
{
    if( !m_currentState )
    {
        return false;   // cannot take input anymore
    }

    TState* lastState = m_currentState;

    m_currentState = m_currentState->GetNextState( input );

    lastState->OnExit( );

    if( m_currentState )
    {
        m_currentState->OnEnter( );
    }

    TRACE_FSM_TRANZITIONS( "State[%s] -> State[%s] with input[%c]", lastState->m_tag.GetBuffer(), m_currentState?m_currentState->m_tag.GetBuffer():NULL, input  );

    return true;
}

template<class T>
Bool CFiniteStateMachine<T>::TakeInput( const CVector<T>& inputs )
{
    for( u64 i=0; i<inputs.GetSize(); i++ )
    {
        if( !TakeInput( inputs[i] ) )
        {
            return false;
        }
    }

    return true;
}

template<class T>
THOT_FORCE_INLINE void CFiniteStateMachine<T>::SetInitialState( TState* state )
{
    m_currentState = m_initialState = state;
}

template<class T>
Bool CFiniteStateMachine<T>::Match( const CVector<T>& inputs )
{
    TakeInput( inputs );
    Bool rezult =  IsMatch();
    Reset( );
    return rezult;
}

template<class T>
Bool CFiniteStateMachine<T>::IsMatch( )
{
    if( !m_currentState || m_currentState->GetStateType() != E_STATE_TYPE_FINAL )
    {
        return false;
    }
    return true;
}

template<class T>
Bool CFiniteStateMachine<T>::IsBlocked( )
{
    return m_currentState == NULL? true:false;
}

template<class T>
THOT_FORCE_INLINE void CFiniteStateMachine<T>::Reset( )
{
    m_currentState = m_initialState;
}