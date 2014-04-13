


template<class TVertexType, class TIndexType>
CMesh<TVertexType, TIndexType>:: CMesh()
{
}

template<class TVertexType, class TIndexType>
CMesh<TVertexType, TIndexType>::~CMesh()
{
}

template<class TVertexType, class TIndexType>
void CMesh<TVertexType, TIndexType>::OnDraw( )const
{
RENDER_GUARD_BLOCK

#if defined(THOT_PROFILER_ENABLE)
    CTimer timerDrawCall; timerDrawCall.Start();
#endif

    THOT_ASSERT(m_ePrimitiveType != EMeshPrimitive::E_MESH_PRIMITIVE_NONE);

    //CShader::GetCurrentShader()->SetMaterial( m_material );

    u32 size = m_vertexArray.GetIndexBuffer().GetSize();

    m_vertexArray.DrawElements( (eGeometricPrimitive)m_ePrimitiveType, size );

#if defined(THOT_PROFILER_ENABLE)
    timerDrawCall.Stop();
#endif

}


template<class TVertexType, class TIndexType>
Bool CMesh<TVertexType,TIndexType>::CreateBuffers ( const void* vertices, const void* indices )
{
    if( !vertices || !indices )
    {
        return false;
    }

    const thVector<TVertexType>& vecVertices = *( (const thVector<TVertexType>*)vertices);
    const thVector<TIndexType>& vecIndices = *( (const thVector<TIndexType>*)indices);

    m_vertexArray = TVertexArray::Create( vecVertices, vecIndices,  E_BUFFER_USAGE_STATIC_DRAW );

    return true;
}