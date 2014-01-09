#pragma  once

#include "State.h"


#include "PatternMatcher.h"



template< class T>
class CFiniteStateMachine: public IPatternMatcher<T>
{
public:
     CFiniteStateMachine();
    ~CFiniteStateMachine();

public:

typedef CAutomataState<T>   TState;
typedef CVector<TState*>    TStateArray;               

        TState*         GetCurrentState     ( );
        const TState*   GetCurrentState     ( )const;
        TState*         GetInitialState     ( );
        const TState*   GetInitialState     ( )const;
        void            SetInitialState     ( TState* state );

virtual Bool            IsMatch             ( )                             override;
virtual Bool            IsBlocked           ( )                             override;
virtual Bool            TakeInput           ( const T& input )              override;
virtual Bool            TakeInput           ( const CVector<T>& inputs )    override;
virtual Bool            Match               ( const CVector<T>& inputs )    override;
virtual void            Reset               ( )                             override;

protected:
    TState*         m_initialState;
    TState*         m_currentState;

    TStateArray     m_states;
};


#include "FiniteStateMachine.inl"