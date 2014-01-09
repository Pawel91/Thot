

template<typename TYPE, u32 SIZE>
THOT_FORCE_INLINE TYPE& CShaderParameterTemplateBase<TYPE, SIZE>::operator[] ( u32 index )
{
    THOT_ASSERT(index < SIZE);
    return m_data[index];
}

template<typename TYPE, u32 SIZE>
THOT_FORCE_INLINE const TYPE& CShaderParameterTemplateBase<TYPE, SIZE>::operator[] ( u32 index )const
{
    THOT_ASSERT(index < SIZE);
    return m_data[index];
}


//template<typename TYPE, u32 SIZE>
//THOT_FORCE_INLINE CShaderParameterTemplateBase<TYPE, SIZE>::operator const TYPE* ()const
//{
//    return m_data;
//}
//
//template<typename TYPE, u32 SIZE>
//THOT_FORCE_INLINE CShaderParameterTemplateBase<TYPE, SIZE>::operator TYPE* ()
//{
//    return m_data;
//}

template<typename TYPE>
CShaderParameterTemplateBase<TYPE, 1>::operator const TYPE& ()const
{
    return m_data;
}

template<typename TYPE>
CShaderParameterTemplateBase<TYPE, 1>::operator TYPE& ()
{
    return m_data;
}

