
template<class T>
CMultiWordMatcher<T>::CMultiWordMatcher()
{

}

template<class T>
CMultiWordMatcher<T>::~CMultiWordMatcher()
{
}

template<class T> 
Bool CMultiWordMatcher<T>::AddNewWord  ( const TWord& newWord )
{
    TWord* temp = snew(TWord);
    for( u64 i=0; i<newWord.GetSize(); i++ )
    {
        temp->Add( newWord[i]  );
    }

    m_wordArray.Add( temp );
    return true;
}

template<class T> 
Bool CMultiWordMatcher<T>::IsBlocked( )
{
    if( m_currentWord.GetSize() == 0 )
    {
        return false;
    }

    return ( !CurrentWordIsPrefix() );
}

template<class T> 
Bool CMultiWordMatcher<T>::TakeInput( const T& input )
{
    m_currentWord.Add( input );
    return true;
}

template<class T>
Bool CMultiWordMatcher<T>::TakeInput( const CVector<T>& inputs )
{
    Bool rezult = true;
    for( u64 i=0; i<inputs.GetSize(); i++ )
    {
        rezult &= TakeInput(inputs[i]);
    }

    return rezult;
}


template<class T>
Bool CMultiWordMatcher<T>::IsMatch()
{
    for( u64 i=0; i<m_wordArray.GetSize(); i++ )
    {
        TWord* word = m_wordArray[i];
        THOT_ASSERT(word);

        if( WordEquals( *word, m_currentWord) )
        {
            return true; // we find a word;
        }
    }

    return false;

}

template<class T>
Bool CMultiWordMatcher<T>::Match( const CVector<T>& inputs )
{
    for( u64 i=0; i<m_wordArray.GetSize(); i++ )
    {
        TWord* word = m_wordArray[i];
        THOT_ASSERT(word);

        if( WordEquals( *word, inputs) )
        {
            return true; // we find a word;
        }
    }

    return false;
}

template<class T> 
void CMultiWordMatcher<T>::Reset( )
{
    m_currentWord.Resize( 0 );
}


template<class T> 
Bool CMultiWordMatcher<T>::IsPrefix( const TWord& word, const TWord& prefix )
{
    if( prefix.GetSize() > word.GetSize() )
    {
        return false;
    }

    for( u64 i=0; i<prefix.GetSize(); i++ )
    {
        if( prefix[i] != word[i]  )
        {
            return false;
        }
    }


    return true;
}

template<class T> 
Bool CMultiWordMatcher<T>::CurrentWordIsPrefix ( )
{
    for( u64 i=0; i<m_wordArray.GetSize(); i++ )
    {
        if( IsPrefix(*m_wordArray[i], m_currentWord ) )
        {
            return true;
        }
    }

    return false;
}


template<class T> 
Bool CMultiWordMatcher<T>::WordEquals ( const TWord& w1, const TWord& w2 )
{
    if( w1.GetSize() != w2.GetSize() )
    {
        return false;
    }

    for( u64 i=0; i<w1.GetSize(); i++ )
    {
        if( w1[i] != w2[i] )
        {
            return false;
        }
    }

    return true;
}