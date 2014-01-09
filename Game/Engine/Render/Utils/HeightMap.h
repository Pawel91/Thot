//  [11/9/2013 Radu]
#if !defined(__KERNEL_HEIGHT_MAP_H__)
#define __KERNEL_HEIGHT_MAP_H__

#include "Kernel/DataStructures/Array/Vector.h"
#include "Kernel/ThreadApi/CriticalSection.h"
#include "Kernel/Singleton.h"
#include "Kernel/Time/Timer.h"
#include "MathCore/Vector/Vector.h"
#include "Render/Color.h"


#include <vector>

class CString;

//--------------------------------------------------------------------------------
class CGraph
{
public:
    RENDER_API CGraph();
    RENDER_API ~CGraph();

    void RENDER_API Init                ( u32 maxNodeCount );
    void RENDER_API PushNode            ( u32 node, u32 neighbour, u32 cost );
    void RENDER_API PushDestinationNode ( u32 node );

    u32 RENDER_API  GetNodeCount        ()const { return m_nodeCount; }

private:
    typedef std::pair<u32, u32>                 TNeighbourCostPair;
    typedef std::vector< TNeighbourCostPair >   TNeighboursList;
    typedef TNeighboursList::iterator           TIterator;
    typedef TNeighboursList::const_iterator     TConstIterator;

    thVector<u32>                                m_destinations;
    TNeighboursList*                            m_graph; //list of neighboursList
    u32                                         m_nodeCount;
    u32                                         m_maxNodeCount;
};

class IPathResolver
{
public:
            IPathResolver(){}
    virtual ~IPathResolver() = 0;


    virtual     void    Init    ( const CGraph* graph, u32 startNode ) = 0;
    virtual     void    Execute () = 0;

};



//--------------------------------------------------------------------------------
class CPathResolver: IPathResolver
{
public:
    RENDER_API CPathResolver ();
    RENDER_API ~CPathResolver();

    void RENDER_API Init        ( const CGraph* graph, u32 startNode )override;
    void RENDER_API Execute     () override;

private:
    static const u32    ms_infinite = u32(-1);
    const CGraph*       m_graph;
    u32                 m_startNode;
    u32                 m_nodeCount;
    u32*                D;
    u32*                H;
    u32*                Poz;
    u32                 NHeap;

};



struct SHeightMapProperties
{
    float       m_maxHeight;
    float       m_lenght;
    float       m_width;
};


struct RENDER_API SHeightMapVertex
{

    SHeightMapVertex()
        : m_visible (false)
        , m_color(0.f, 0.f, 0.f, 0.f)
    {
    }

    tVect3      m_position;
    tVect3      m_normal;
    tVect3      m_textCoord;
    CColor      m_color;
    Bool        m_visible;
};

struct RENDER_API CVisibleNode
{
    SHeightMapVertex        m_vertex;
    u32                     m_nodeIndex;
};

THOT_DECLARE_TEMPLATE_API( RENDER_TEMPLATE_API, thVector<CVisibleNode>);
THOT_DECLARE_TEMPLATE_API( RENDER_TEMPLATE_API, thVector<SHeightMapVertex>);
THOT_DECLARE_TEMPLATE_API( RENDER_TEMPLATE_API, thVector<u16>);

class ICommand;

class RENDER_API CCommandNode
{
public:

    CCommandNode()
        : m_command(NULL)
        , m_nextCommand(NULL)
    {
    }

    ICommand*       m_command;
    CCommandNode*   m_nextCommand;
};

class RENDER_API CCommandQueue
{
public:
    CCommandQueue()
        : m_head        (NULL)
        , m_tail        (NULL)
        , m_nodeCount   (0)
    {
    
    }

    void            Push( ICommand* command )
    {
        m_nodeCount++;
        CCommandNode* node = THOT_NEW CCommandNode;
        node->m_command = command;
        node->m_nextCommand = NULL;
        if(m_head)
        {
            m_head->m_nextCommand = node;
        }
        m_head = node;

        if( m_nodeCount == 1 )
        {
            m_tail = node;
        }
    }

    u32 GetNodeCount(){ return m_nodeCount;}

    Bool            Empty()
    {
        return m_nodeCount == 0;
    }

    ICommand*       Pop()
    {
        if(m_nodeCount == 0)
        {
            return NULL;
        }

        CCommandNode* newTail = m_tail->m_nextCommand;
        ICommand* command = m_tail->m_command;
        //THOT_DELETE( m_tail);
        m_tail = newTail;
        m_nodeCount--;
        return command;

    }


private:
    CCommandNode*   m_head;
    CCommandNode*   m_tail;
    u32             m_nodeCount;

};

class RENDER_API CHeightMapHelpers
{
    friend class CGenericThread;
public:
    THOT_DECLARE_SINGLETON_LAZY(CHeightMapHelpers);
    CHeightMapHelpers();

    void                AddAsynchronousCommand( ICommand* command );

    void                OnFinishCommand();

protected:
    ICommand*           PopCommand( u32 index );

private:
    static const u32        ms_maxThreads = 16;
    class CGenericThread*   m_threads;
    CCommandQueue           m_commandQueues[ms_maxThreads];
    u32                     m_threadCount;
    CCritSection            m_criticalSections[ms_maxThreads];
};


class IMesh;
class CVisTestThread;
// we store this class in RenderDLL because we need to load texture
class RENDER_API CHeightMap
{
    friend class CVisThreadTest;
//*********************************************
//            CONSTR/DESTR
//*********************************************
public:
     CHeightMap();
    ~CHeightMap();

//*********************************************
//            INTERFACE
//*********************************************
public:
        Bool                    LoadFromTexture( const CString& fileName, const SHeightMapProperties& properties );
        IMesh*                  GetGeneratedMesh() { return m_generatedMesh;}
        float                   GetHeight( u32 x, u32 y );
        float                   GetHeight( float xTerrain, float zTerrain);
        tVect3                  GetNormal(float xTerrain, float zTerrain);
        u32                     GetWidth()  { return m_width;}
        u32                     GetLenght() { return m_lenght;}
        float                   GetTerrainXSize(){ return m_properties.m_width;}
        float                   GetTerrainZSize(){ return m_properties.m_lenght;}
        const SHeightMapProperties& GetProperties(){ return m_properties;}
        SHeightMapVertex&       GetVertex( u32 x, u32 y);
        Bool                    IsDirty()const{ return m_isDirty;}
        void                    SetDirty( Bool value = true); //{ m_isDirty = value; }

        void                    MakeVisTest_Asynchronous( const tVect3& position);
        void                    MakeVisTest( tVect3& viewPosition, u32 index =0 );
        void                    MakeVisTest( tVect3& viewPosition, u32 startIndex, u32 increment);
        void                    AddVisibleNode( CVisibleNode& visNode );
        void                    DebugUpdateVertices( IMesh* mesh );
        Bool                    VisTestsDone()const;
        void                    GetNearestVisPoint( const tVect3& source, tVect3& outTarget );

//*********************************************
//            HELPERS
//*********************************************
protected:
    Bool                    BuildGraph();
    Bool                    BuildTexelToVertexMesh();
    Bool                    Tesselate( u32 iterations );
    Bool                    GenerateMesh();

//*********************************************
//            MEMBERS
//*********************************************
protected:
    CVisTestThread*             m_visTestThread;
    IMesh*                      m_generatedMesh;
    Bool                        m_isDirty; //triggers geometry update on GPU when false
    u32                         m_width;
    u32                         m_lenght;
    u8*                         m_data;
    SHeightMapProperties        m_properties;
    thVector<SHeightMapVertex>   m_texelToVertexMesh;
    thVector<u16>                m_indices;
    thVector<CVisibleNode>       m_visibleNodes;

    u32                         m_visCommandCount;
    class CVisbilityCommand**   m_commands;
    mutable CTimer              m_timerVisTest;

    CCritSection                m_criticalSection;
};



#endif //__KERNEL_HEIGHT_MAP_H__