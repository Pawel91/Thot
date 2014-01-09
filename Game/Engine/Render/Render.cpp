#include "Render_PCH.h"
#include "Render.h"
#include "RenderGL.h"
IMPLEMENT_SINGLETON_CUSTOM( CRender, CRenderGL);

#include "SOIL.h"
#include "Textures/Texture.h"

#include "Render/Buffers/Vertex.h"
#include "Render/Mesh/Mesh.h"


void CRender::DebugDraw()
{
    static thVector<RenderLowLevel::SVertex_P> m_vertices;
    static thVector<u16> m_indices;

    static IMesh* mesh = NULL;
    static bool init = false;
    float scale = 1.f;
    if(!init)
    {
    
        RenderLowLevel::SVertex_P vertex;
        vertex.m_vertex  = tVect3(-1.f, 1.f, 0.f) * scale;
        m_vertices.PushBack( vertex );

        vertex.m_vertex  = tVect3( 1.f, 1.f, 0.f)* scale;
        m_vertices.PushBack( vertex );

        vertex.m_vertex  = tVect3( -1.f, -1.f, 0.f)* scale;
        m_vertices.PushBack( vertex );

        vertex.m_vertex  = tVect3( 1.f, -1.f, 0.f)* scale;
        m_vertices.PushBack( vertex );

        m_indices.PushBack(0);
        m_indices.PushBack(1);
        m_indices.PushBack(2);

        m_indices.PushBack(1);
        m_indices.PushBack(2);
        m_indices.PushBack(3);

        mesh = MeshFactory::CreateMesh(m_vertices, m_indices);
        mesh->SetPrimitiveType( EMeshPrimitive::E_MESH_PRIMITIVE_TRIANGLES);
        init = true;
    }

    THOT_ASSERT(mesh);
    mesh->OnDraw();



}


namespace Render
{

Bool Init()
{
    if( CRender::CreateInstance()==NULL )
    {   
        THOT_TRACE("ERROR!   Could not create Render instance\n");
        return false;
    }

    if ( !CRender::GetInstance()->Init() )
    {
        THOT_TRACE("ERROR!   Could not Init Render instance\n");
        return false;
    }

    return true;
}

Bool Shutdown()
{



    CRender::DestroyInstance();
    return true;
}

}
