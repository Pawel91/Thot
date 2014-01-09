


template< class Type_Input >
u64 CAutomataState<Type_Input>::ms_invalidInputIndex = CVector<TInputPair>::ms_invalidIndex;

template< class Type_Input >
typename CAutomataState<Type_Input>::TInputCompareFunction CAutomataState<Type_Input>::ms_compareInputFunction = NULL;

template< class Type_Input >
void CAutomataState<Type_Input>::RegisterCompareFunction ( TInputCompareFunction inputCompareFunction )
{
    ms_compareInputFunction = inputCompareFunction;
}



template<class T0, class T1>
THOT_FORCE_INLINE CPair<T0,T1>::CPair( T0 first, T1 second )
    :m_first        ( first )
    ,m_second       ( second )
{
}


template<class Type_Input>
CAutomataState< Type_Input>::CAutomataState()
    :m_eStateType       ( E_STATE_TYPE_NORMAL )
{

}


template<class Type_Input>
THOT_FORCE_INLINE CAutomataState<Type_Input>::~CAutomataState()
{
    
}


template<class Type_Input>
THOT_FORCE_INLINE CAutomataState<Type_Input>* CAutomataState<Type_Input>::CreateAutomataState( EStateType stateType, const char* tag )
{
    TSelf* state = snew( TSelf );
    state->m_tag = tag;
    state->SetStateType( stateType );
    return state;
}


template<class Type_Input>
THOT_FORCE_INLINE Bool CAutomataState<Type_Input>::IsFinal( )
{
    return m_eStateType == E_STATE_TYPE_FINAL;
}

template<class Type_Input>
THOT_FORCE_INLINE Bool CAutomataState<Type_Input>::IsInitial( )
{
    return m_eStateType == E_STATE_TYPE_FINAL;
}



template<class Type_Input>
THOT_FORCE_INLINE u64 CAutomataState<Type_Input>::Find( const Type_Input& input )const
{
    THOT_ASSERT( ms_compareInputFunction!=NULL, "Unregistred compare function. Please register a compare function for this type of input!" );

    for( u64 i=0; i<m_inputs.GetSize(); i++)
    {
        const TInputPair& pair = m_inputs[i];
        if( ms_compareInputFunction( input, pair.m_first ) == 0 )
        {
            return i;
        }
    }

    return ms_invalidInputIndex;
}

template<class Type_Input>
THOT_FORCE_INLINE Bool CAutomataState<Type_Input>::AddInput( const Type_Input& input, TSelf* nextState )
{
    if( Find(input) != ms_invalidInputIndex )
    {
        // we allready have an input of that kind
        THOT_TRACE_LINE("Posible Error in building state machine. Input allready added");
        return false;
    }

    m_inputs.Add( TInputPair(input, nextState) );

    return true;
}

template<class Type_Input>
THOT_FORCE_INLINE Bool CAutomataState<Type_Input>::AddInput( const CVector<Type_Input>& arrayInputs, TSelf* nextState )
{
    for( u64 i=0; i<arrayInputs.GetSize(); i++ )
    {
        if( !AddInput( arrayInputs[i], nextState ) )
        {
            return false;
        }
    }

    return true;
}

template<class Type_Input>
THOT_FORCE_INLINE const CAutomataState<Type_Input>* CAutomataState<Type_Input>::GetNextState( const Type_Input& input )const
{
    return const_cast< CAutomataState<Type_Input>* >( this )->GetNextState();
}

template<class Type_Input>
THOT_FORCE_INLINE CAutomataState<Type_Input>* CAutomataState<Type_Input>::GetNextState( const Type_Input& input )
{
    u64 index = Find( input );
    if( index == ms_invalidInputIndex )
    {
        // not found
        return NULL;
    }

    return m_inputs[index].m_second;
}

template<class Type_Input>
THOT_FORCE_INLINE Bool CAutomataState<Type_Input>::IsInputValid( const Type_Input& input )const
{
    return Find(input) != ms_invalidInputIndex;
}