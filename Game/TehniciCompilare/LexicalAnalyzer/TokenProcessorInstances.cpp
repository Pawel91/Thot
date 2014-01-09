
#include "TokenProcessorInstances.h"
#include "TokenCharacterHelper.h"
#include "..//FiniteStateMachine/MultiWordMatcher.h"




Bool CTokenIdentifierProcessor::BuildPatternMatcher()
{
    TTokenState* initialState       = TTokenState::CreateAutomataState( E_STATE_TYPE_INITIAL,       "initialState" );
    TTokenState* s0                 = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,         "s0" );

    //TTokenState* finalState       = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,         "finalState" );

    char __first []   = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
    char __all []     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789";
    
    CVector<char> first ( __first, THOT_ARRAY_SIZE(__first)-1 );
    CVector<char> all   ( __all, THOT_ARRAY_SIZE(__all)-1 );

    Bool inputsAdded = true;

    //*********** initial state
    inputsAdded &= initialState->AddInput( first, s0 );

    //*********** s0
    inputsAdded &= s0->AddInput( all, s0 );

    THOT_ASSERT(inputsAdded, "failed to add all inputs");

    m_patternMatcher = snew ( CFiniteStateMachine<char> );
    ((CFiniteStateMachine<char>*)m_patternMatcher)->SetInitialState( initialState );

    return inputsAdded;
}

Bool CTokenOperatorProcessor::BuildPatternMatcher()
{
    CMultiWordMatcher<char>* matcher = NULL;
    m_patternMatcher = matcher =  snew ( CMultiWordMatcher<char> );


    //[TODO]
    char* operators[] = { "+", "-", "++", "--", ",", "<<", ">>", "==", "=", "!=", "*", "/", "%", ">", "<", ">=", "<=", "!", "&&", "||", "&", "|"
                            ,"~", "^", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "->", "->*", ".*", "::", "." };

    for( u32 i=0; i<THOT_ARRAY_SIZE(operators); i++ )
    {
        char* word = operators[i];
        u64 lenght = strlen( word );
        
        matcher->AddNewWord( CVector<char>( word, lenght ) );
    }
    
    return true;
}

Bool CTokenPunctuatorProcessor::BuildPatternMatcher()
{
    CMultiWordMatcher<char>* matcher = NULL;
    m_patternMatcher = matcher =  snew ( CMultiWordMatcher<char> );

    //[TODO]
    char* punctuators[] = { "(", ")", "{", "}", ":", ";", "[", "]" };

    for( u32 i=0; i<THOT_ARRAY_SIZE(punctuators); i++ )
    {
        char* word = punctuators[i];
        u64 lenght = strlen( word );
        
        matcher->AddNewWord( CVector<char>( word, lenght ) );
    }
    
    return true;
}



Bool CTokenCommentSingleLineProcessor::BuildPatternMatcher()
{
    TTokenState* initialState       = TTokenState::CreateAutomataState( E_STATE_TYPE_INITIAL,       "initialState" );
    TTokenState* s0                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL,        "s0" );

    TTokenState* s1                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL,        "s1" );
    TTokenState* finalState         = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,         "finalState" );

    // setup initial state
    initialState->AddInput( '/', s0 );
    
    // setup s0
    s0->AddInput('/', s1 );

    // setup s1
    CVector<char> exclude, s1Inputs;
    exclude.Add('\n'); exclude.Add('\r');
    
    CTokenCharacterHelper::s_GetInstance()->ExcludeFromAll( exclude, s1Inputs );
    s1->AddInput( s1Inputs, s1 );

    s1->AddInput( '\n', finalState );
    s1->AddInput( '\r', finalState );

    m_patternMatcher = snew ( CFiniteStateMachine<char> );
    ((CFiniteStateMachine<char>*)m_patternMatcher)->SetInitialState( initialState );

    return true;
}

Bool CTokenCommentMultiLineProcessor::BuildPatternMatcher()
{
    TTokenState* initialState       = TTokenState::CreateAutomataState( E_STATE_TYPE_INITIAL, "initialState" );
    TTokenState* s1                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL, "s1" );
    TTokenState* s2                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL, "s2" );
    TTokenState* s3                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL, "s3" );
    TTokenState* finalState         = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL, "finalState" );

    Bool inputsAdded = true;

    // initial State
    inputsAdded &= initialState->AddInput( '/', s1 );

    //s1
    inputsAdded &= s1->AddInput('*', s2);

    //s2
    CVector<char> exclude, inputs;
    exclude.Add('*');
    CTokenCharacterHelper::s_GetInstance()->ExcludeFromAll( exclude,  inputs );
    inputsAdded &= s2->AddInput( inputs, s2 );

    inputsAdded &= s2->AddInput('*', s3);

    // s3
    exclude.Resize(0);
    exclude.Add('*');exclude.Add('/');
    CTokenCharacterHelper::s_GetInstance()->ExcludeFromAll( exclude,  inputs );
    
    inputsAdded &= s3->AddInput( inputs, s2 );

    inputsAdded &= s3->AddInput('*', s3);
    inputsAdded &= s3->AddInput('/', finalState );

    //final state nothing to do

    THOT_ASSERT(inputsAdded, "failed to add all inputs");

    m_patternMatcher = snew ( CFiniteStateMachine<char> );
    ((CFiniteStateMachine<char>*)m_patternMatcher)->SetInitialState( initialState );

    return true;
}

Bool CTokenKeyWordProcessor::BuildPatternMatcher()
{
    CMultiWordMatcher<char>* matcher = NULL;
    m_patternMatcher = matcher =  snew ( CMultiWordMatcher<char> );


    //[TODO]
    char* keyWords[] = {"void", "main", "volatile", "int", "float", "auto", "break", "case", "char", "const", "continue", "default"
                        ,"do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return"
                        ,"short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "while", "inline" };

    for( u32 i=0; i<THOT_ARRAY_SIZE(keyWords); i++ )
    {
        char* word = keyWords[i];
        u64 lenght = strlen( word );
        
        matcher->AddNewWord( CVector<char>( word, lenght ) );
    }
    
    return true;
}


Bool CTokenCharLiteral::BuildPatternMatcher()
{
    TTokenState* initialState       = TTokenState::CreateAutomataState( E_STATE_TYPE_INITIAL,   "initialState" );
    TTokenState* s1                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL,    "s1" );
    TTokenState* se                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL,    "se" );

    TTokenState* finalState         = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "finalState" );

    Bool inputsAdded = true;
    CVector<char> exclude, inputs;

    //******** initial state
    inputsAdded &= initialState->AddInput( '\'', s1 );

    //******** s1 state
    //exclude.Add('\"');
    exclude.Add('\n'); exclude.Add('\\');exclude.Add('\r'); exclude.Add('\'');
    CTokenCharacterHelper::s_GetInstance()->ExcludeFromAll(exclude, inputs);
    
    inputsAdded &= s1->AddInput( inputs, s1 );
    inputsAdded &= s1->AddInput('\\', se );
    inputsAdded &= s1->AddInput('\'', finalState );


    //********* se
    inputsAdded &= se->AddInput( 'a', s1 );
    inputsAdded &= se->AddInput( 'b', s1 );
    inputsAdded &= se->AddInput( 'f', s1 );
    inputsAdded &= se->AddInput( 'r', s1 );
    inputsAdded &= se->AddInput( 't', s1 );
    inputsAdded &= se->AddInput( 'v', s1 );
    inputsAdded &= se->AddInput( 'n', s1 );
    inputsAdded &= se->AddInput( '\'', s1 );
    inputsAdded &= se->AddInput( '\"', s1 );
    inputsAdded &= se->AddInput( '\\', s1 );
    inputsAdded &= se->AddInput( '\?', s1 );


    //
   THOT_ASSERT( inputsAdded );

    m_patternMatcher = snew ( CFiniteStateMachine<char> );
    ((CFiniteStateMachine<char>*)m_patternMatcher)->SetInitialState( initialState );

   return inputsAdded;
}

Bool CTokenLiteralStringProcessor::BuildPatternMatcher  ()
{
    TTokenState* initialState       = TTokenState::CreateAutomataState( E_STATE_TYPE_INITIAL, "initialState" );
    TTokenState* s1                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL, "s1" );
    TTokenState* se                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL, "se" );

    TTokenState* finalState         = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL, "finalState" );

    Bool inputsAdded = true;
    CVector<char> exclude, inputs;

    //********* initial state
    inputsAdded &= inputsAdded &= initialState->AddInput( '\"', s1 );


    //********* s1
    exclude.Add('\"');exclude.Add('\n'); exclude.Add('\\');exclude.Add('\r');
    CTokenCharacterHelper::s_GetInstance()->ExcludeFromAll(exclude, inputs);
    inputsAdded &= s1->AddInput( inputs, s1 );

    inputsAdded &= s1->AddInput('\"', finalState );

    inputsAdded &= s1->AddInput('\\', se );


    //********* se
    inputsAdded &= se->AddInput( 'a', s1 );
    inputsAdded &= se->AddInput( 'b', s1 );
    inputsAdded &= se->AddInput( 'f', s1 );
    inputsAdded &= se->AddInput( 'r', s1 );
    inputsAdded &= se->AddInput( 't', s1 );
    inputsAdded &= se->AddInput( 'v', s1 );
    inputsAdded &= se->AddInput( 'n', s1 );
    inputsAdded &= se->AddInput( '\'', s1 );
    inputsAdded &= se->AddInput( '\"', s1 );
    inputsAdded &= se->AddInput( '\\', s1 );
    inputsAdded &= se->AddInput( '\?', s1 );
    
    
    // [TODO] ASCII character in octal and hexa




    THOT_ASSERT(inputsAdded, "failed to add all inputs");

    m_patternMatcher = snew ( CFiniteStateMachine<char> );
    ((CFiniteStateMachine<char>*)m_patternMatcher)->SetInitialState( initialState );

    return true; 
}

Bool CTokenLiteralFloatProcessor::BuildPatternMatcher  ()
{
    TTokenState* initialState       = TTokenState::CreateAutomataState( E_STATE_TYPE_INITIAL,   "initialState" );
    TTokenState* s0                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL,     "s0" );
    TTokenState* s1                 = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "s1" );
    TTokenState* se                 = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL,    "se" );
    TTokenState* seminus            = TTokenState::CreateAutomataState( E_STATE_TYPE_NORMAL,    "seminus" );
    TTokenState* s2                 = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "s2" );
    TTokenState* ssufix             = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "ssufix" );

    Bool inputsAdded = true;

    char _floatSufixes[] = "lLFf";
    CVector<char> floatSufixes( _floatSufixes, THOT_ARRAY_SIZE(_floatSufixes)-1 );

    char _intDigits[] = "0123456789";
    CVector<char> intDigits( _intDigits, THOT_ARRAY_SIZE(_intDigits)-1 );

    char _intNoZeroDigits[] = "123456789";
    CVector<char> intNoZeroDigits( _intNoZeroDigits, THOT_ARRAY_SIZE(_intNoZeroDigits)-1 );

    //******** initial state
    inputsAdded &= initialState->AddInput(intDigits, s0 );

    //******** s0
    inputsAdded &= s0->AddInput(intDigits, s0);
    inputsAdded &= s0->AddInput('.', s1);
    inputsAdded &= s0->AddInput( 'e', se );

    //******** s1
    inputsAdded &= s1->AddInput( intDigits, s1 );
    inputsAdded &= s1->AddInput( floatSufixes, ssufix );
    inputsAdded &= s1->AddInput( 'e', se );

    //******** se
    inputsAdded &= se->AddInput('-', seminus );
    inputsAdded &= se->AddInput('+', seminus );
    inputsAdded &= se->AddInput( intDigits, s2 );

    //******** seminus
    inputsAdded &= seminus->AddInput( intDigits, s2 );

    //******** s2
    inputsAdded &= s2->AddInput( intDigits, s2 );
    inputsAdded &= s2->AddInput( floatSufixes, ssufix );

    THOT_ASSERT(inputsAdded, "failed to add all inputs");

    m_patternMatcher = snew ( CFiniteStateMachine<char> );
    ((CFiniteStateMachine<char>*)m_patternMatcher)->SetInitialState( initialState );

    return true; 
}

Bool CTokenLiteralIntegerProcessor::BuildPatternMatcher  ()
{
    TTokenState* initialState       = TTokenState::CreateAutomataState( E_STATE_TYPE_INITIAL,   "initialState" );
    TTokenState* sotherBase         = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,    "sotherBase" );
    TTokenState* sint               = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "sint" );
    TTokenState* soctal             = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "soctal" );
    TTokenState* shexa              = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "shexa" );
    TTokenState* ssufixU            = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "ssufixU" );
    TTokenState* ssufixL            = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "ssufixL" );
    TTokenState* ssufixLL           = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "ssufixLL" );
    TTokenState* ssufixUL           = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "ssufixUL" );
    TTokenState* ssufixULL          = TTokenState::CreateAutomataState( E_STATE_TYPE_FINAL,     "ssufixULL" );


    Bool inputsAdded = true;

    char _hexaDigits[] = "0123456789abcdefABCDEF";
    CVector<char> hexaDigits( _hexaDigits, THOT_ARRAY_SIZE(_hexaDigits)-1 );

    char _octalDigits[] = "01234567";
    CVector<char> octalDigits ( _octalDigits, THOT_ARRAY_SIZE(_octalDigits)-1 );

    char _intDigits[] = "0123456789";
    CVector<char> intDigits( _intDigits, THOT_ARRAY_SIZE(_intDigits)-1 );

    char _intNoZeroDigits[] = "123456789";
    CVector<char> intNoZeroDigits( _intNoZeroDigits, THOT_ARRAY_SIZE(_intNoZeroDigits)-1 );

    //******** initial state
    inputsAdded &= initialState->AddInput( '0', sotherBase );
    inputsAdded &= initialState->AddInput( intNoZeroDigits, sint );

    //******** sint
    inputsAdded &= sint->AddInput( intDigits, sint );
    inputsAdded &= sint->AddInput( 'U', ssufixU );
    inputsAdded &= sint->AddInput( 'u', ssufixU );
    inputsAdded &= sint->AddInput( 'l', ssufixL );
    inputsAdded &= sint->AddInput( 'L', ssufixL );

    //******** sother base
    inputsAdded &= sotherBase->AddInput( 'x', shexa );
    inputsAdded &= sotherBase->AddInput( 'X', shexa );
    inputsAdded &= sotherBase->AddInput( octalDigits, soctal);

    //******** soctal
    inputsAdded &= soctal->AddInput( octalDigits, soctal );
    inputsAdded &= soctal->AddInput( 'U', ssufixU );
    inputsAdded &= soctal->AddInput( 'u', ssufixU );
    inputsAdded &= soctal->AddInput( 'l', ssufixL );
    inputsAdded &= soctal->AddInput( 'L', ssufixL );


    //******** shexa
    inputsAdded &= shexa->AddInput( hexaDigits, shexa );
    inputsAdded &= shexa->AddInput( 'U', ssufixU );
    inputsAdded &= shexa->AddInput( 'u', ssufixU );
    inputsAdded &= shexa->AddInput( 'l', ssufixL );
    inputsAdded &= shexa->AddInput( 'L', ssufixL );


    //******** ssufixU
    inputsAdded &= ssufixU->AddInput( 'l', ssufixUL );
    inputsAdded &= ssufixU->AddInput( 'L', ssufixUL );

    //******** ssufixUL
    inputsAdded &= ssufixUL->AddInput( 'l', ssufixULL );
    inputsAdded &= ssufixUL->AddInput( 'L', ssufixULL );

    //******** ssufixL
     inputsAdded &= ssufixL->AddInput( 'l', ssufixLL );
     inputsAdded &= ssufixL->AddInput( 'L', ssufixLL );


    THOT_ASSERT(inputsAdded, "failed to add all inputs");

    m_patternMatcher = snew ( CFiniteStateMachine<char> );
    ((CFiniteStateMachine<char>*)m_patternMatcher)->SetInitialState( initialState );
    
    return true; 
}


