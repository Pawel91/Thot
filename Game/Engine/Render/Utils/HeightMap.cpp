#include "Render_PCH.h"
#include "HeightMap.h"
#include "Kernel/FileSystem/Path.h"
#include "Kernel/ThreadApi/Thread.h"
#include "Kernel/ThreadApi/AutoLock.h"
#include "Kernel/ThreadApi/CriticalSection.h"
#include "Render/Buffers/Vertex.h"
#include "Render/Mesh/Mesh.h"
#include "Kernel/Utils/StringUtils.h"
#include "MathCore/Random.h"
#include "MathCore/MathUtils.h"

#include "Render/Render.h"
#include "Render/RenderCamera.h"
#include "Kernel/Utils/Command.h"

#include "SOIL.h"

#if defined(CreateFile)
#   undef CreateFile
#endif


THOT_IMPLEMENT_SINGLETON_LAZY(CHeightMapHelpers);

//--------------------------------------------------------------------------------
class CVisbilityCommand: public ICommand
{
public:
     CVisbilityCommand(CHeightMap* heightMap,u32 slaveCount, u32 slaveID )
         : m_heightMap(heightMap)
         , m_slaveID(slaveID)
         , m_slaveCount(slaveCount)
         , m_position(nullVect)
     {
     }

     ~CVisbilityCommand(){}

     void   SetPosition(const tVect3& position){m_position = position;}

    virtual void InternalExecute()override
    {
        m_heightMap->MakeVisTest( m_position, m_slaveID, m_slaveCount );
    }

    CHeightMap*     m_heightMap;
    tVect3          m_position;
    u32             m_slaveID;
    u32             m_slaveCount;
};

//--------------------------------------------------------------------------------
class CGenericThread:public CThread
{
public:
    CGenericThread( )
        : m_stop (false)
        , m_index (-1)
    {
    }

    void SetIndex( u32 index){m_index = index;}

    virtual void Run()override
    {
        while(!m_stop)
        {
            ICommand* commandToExecute = CHeightMapHelpers::GetInstance()->PopCommand( m_index );
            
            if( !commandToExecute )
            {
                Sleep(2);
            }
            else
            {
                commandToExecute->Execute();
            }
        
        }
    }

private:
    Bool    m_stop;
    u32     m_index;

};

CHeightMapHelpers::CHeightMapHelpers()
    : m_threadCount( 4 )
{
    const u32 coreCount = 8;


    u32 affinityMask = 1 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7;

    m_threads = THOT_NEW_ARR CGenericThread[m_threadCount];
 
#define SET_AFFINITY_ALL

    for( u32 i=0; i<m_threadCount; i++ )
    {
        m_threads[i].SetIndex(i);
    }
#if defined(SET_AFFINITY_ALL)
    for( u32 i=0; i<m_threadCount; i++ )
    {
        THOT_ASSERT( &(m_threads[i]));
        m_threads[i].Start(32*1024, affinityMask);
    }
#else
    if( !m_threads[0].Start( 32* 1024, 1<<1 | 1<<2 ) )
    {
        THOT_ASSERT(false, "CANNOT START CGenericThread");
    }

    if( !m_threads[1].Start( 32* 1024, 1<<3|1<<4))
    {
        THOT_ASSERT(false, "CANNOT START CGenericThread");
    }
    if( !m_threads[2].Start( 32* 1024,1<<5|1<<6) )
    {
        THOT_ASSERT(false, "CANNOT START CGenericThread");
    }

    if( !m_threads[3].Start( 32* 1024, 1<<7 | 1<<8))
    {
        THOT_ASSERT(false, "CANNOT START CGenericThread");
    }
#endif
}

//--------------------------------------------------------------------------------
void CHeightMapHelpers::AddAsynchronousCommand( ICommand* command )
{
    u32 commandQueueIndex = 0;
    u32 minComands = u32(-1);
    for( u32 i=0; i<m_threadCount; i++ )
    {
        CCommandQueue& commandQueue = m_commandQueues[i];
        if( minComands > commandQueue.GetNodeCount() )
        {
            minComands = commandQueue.GetNodeCount();
            commandQueueIndex = i;
        }

    }

    CCommandQueue& commandQueue = m_commandQueues[commandQueueIndex];
    {
        CAutoLock<CCritSection> lock(m_criticalSections[commandQueueIndex]);
        commandQueue.Push(command);
    }
}

//--------------------------------------------------------------------------------
ICommand* CHeightMapHelpers::PopCommand( u32 index )
{
    THOT_ASSERT( index < m_threadCount );
    ICommand* command = NULL;
    CCommandQueue& commandQueue = m_commandQueues[index];
    {
        CAutoLock<CCritSection> lock(m_criticalSections[index]);
        command = commandQueue.Pop();
    }

    return command;
}


//--------------------------------------------------------------------------------
CGraph::CGraph()
    : m_graph (NULL)
    , m_nodeCount(0)
    , m_maxNodeCount(0)
{
}

//--------------------------------------------------------------------------------
CGraph::~CGraph()
{

}

//--------------------------------------------------------------------------------
void CGraph::Init( u32 maxNodeCount )
{
    m_maxNodeCount = maxNodeCount;
}

//--------------------------------------------------------------------------------
void CGraph::PushNode( u32 node, u32 neighbour, u32 cost )
{
    THOT_ASSERT(m_graph);
    m_nodeCount++;
    THOT_ASSERT(m_nodeCount>m_maxNodeCount);
    m_graph[node].push_back( TNeighbourCostPair(neighbour, cost) );
}

//--------------------------------------------------------------------------------
void CGraph::PushDestinationNode ( u32 node )
{
    m_destinations.PushBack( node );
}

//--------------------------------------------------------------------------------
CPathResolver::CPathResolver ()
    : m_nodeCount   (0)
    , D             (NULL)
    , H             (NULL)
    , Poz           (NULL)
    , m_graph       (NULL)
    , m_startNode   (0)
    , NHeap         (0)
{

}

//--------------------------------------------------------------------------------
CPathResolver::~CPathResolver()
{
    if( D )
    {
        THOT_FREE(D);
    }

    if( H )
    {
        THOT_FREE(H);
    }

    if(Poz)
    {
        THOT_FREE(Poz);
    }
}

//--------------------------------------------------------------------------------
IPathResolver::~IPathResolver(){}

//--------------------------------------------------------------------------------
void CPathResolver::Init( const CGraph* graph, u32 startNode )
{
    m_graph = graph;
    m_nodeCount = graph->GetNodeCount();
    D = (u32*)THOT_MALLOC(m_nodeCount+1);
    H = (u32*)THOT_MALLOC(m_nodeCount+1);
    Poz = (u32*)THOT_MALLOC(m_nodeCount+1);

    Memory::Set(D, m_nodeCount, 0);
    Memory::Set(H, m_nodeCount, 0);
    Memory::Set(Poz, m_nodeCount, 0);

    for( u32 i=2;i<=m_nodeCount;i++)
    {
        D[i]=ms_infinite;
    }

    NHeap=m_nodeCount;
 
    for( u32 i=1;i<=NHeap;i++)
    {
        H[i]=i;
        Poz[i]=i;
    }
}


#if defined(__DIJKSTRA)

//--------------------------------------------------------------------------------
inline void Swap(int X, int Y, int* H, int* Poz)
{
    std::swap(H[X],H[Y]);
    std::swap(Poz[H[X]],Poz[H[Y]]);
}

//--------------------------------------------------------------------------------
inline void Sift(int X, int* H, int* Poz, int* D)
{
    THOT_ASSERT(false);

#if defined(__DIJKSTRA)
    int Son=(X<<1);
    if(Son+1<=NHeap && D[H[Son+1]]<D[H[Son]])
      Son++;
    if(Son<=NHeap && D[H[Son]]<D[H[X]])
        {
            Swap(Son,X, H, Poz);
            Sift(Son, H, Poz, D);
        }
#endif
}
inline void Percolate(int X, int*D, int*H, int* Poz)
{

    int F=X>>1;
    if(F && D[H[X]]<D[H[F]])
        {
            Swap(X,F,H,Poz);
            Percolate(F,D,H,Poz);
        }

}

//--------------------------------------------------------------------------------
int ComputeMin(int* H, int* Poz, int* D)
{
    THOT_ASSERT(false);
    return 0;



    int P=H[1];
    Swap(1,NHeap, H, Poz);
    NHeap--;
    Sift(1, H, Poz, D);
    return P;





}

//--------------------------------------------------------------------------------
inline void Relax(int Nod,int Vecin,int Cost,int*D, int*H, int*Poz)
{
   if(D[Vecin]>D[Nod]+Cost)
      {
      D[Vecin]=D[Nod]+Cost;
      Percolate(Poz[Vecin],D,H,Poz);
      }
 
}

//--------------------------------------------------------------------------------
inline void Dijkstra(int Start, std::vector< std::pair<int,int>>* G, int* destinations, std::vector< std::pair<int,int>>* T)
{
    THOT_ASSERT(false);

	int *D = new int[N+1];
	int *H = new int[N+1];
	int *Poz = new int[N+1];
	for(int i=1;i<=N;i++)
		D[i] = H[i] = Poz[i] = 0;

    InitDijkstra(Start, H, Poz, D);
 
    for(int i=1;i<=N;i++)
        {
            int Nod=ComputeMin(H, Poz, D);
            for(unsigned int j=0;j<G[Nod].size();j++)
                Relax(Nod,G[Nod][j].first,G[Nod][j].second,D,H,Poz);
        }
	Print(D,T,destinations,Start);
}


#endif
//--------------------------------------------------------------------------------
void CPathResolver::Execute()
{

}









//--------------------------------------------------------------------------------
class CVisTestSlaveThread:public CThread
{
public:
     CVisTestSlaveThread(CHeightMap* heightMap,u32 slaveCount, u32 slaveID )
         : m_heightMap(heightMap)
         , m_slaveID(slaveID)
         , m_slaveCount(slaveCount)
         , m_position(nullVect)
     {
     }

     ~CVisTestSlaveThread(){}

     void   SetPosition(const tVect3& position){m_position = position;}

    virtual void Run()
    {
        m_heightMap->MakeVisTest( m_position, m_slaveID, m_slaveCount );
    }

    CHeightMap*     m_heightMap;
    tVect3          m_position;
    u32             m_slaveID;
    u32             m_slaveCount;
};

class CVisTestThread:public CThread
{
public:
    CVisTestThread(CHeightMap* heightMap)
        : m_heightMap( heightMap)
        , m_position (nullVect)
        , m_stop(false)
        , m_makeNewTest(false)
    {
    }

    virtual void Run()
    {
        while(!m_stop)
        {
            if(m_makeNewTest) 
            {
                //m_heightMap->MakeVisTest( position );
                CVisTestSlaveThread thread1( m_heightMap, 4, 0 );
                CVisTestSlaveThread thread2( m_heightMap, 4, 1 );
                CVisTestSlaveThread thread3( m_heightMap, 4, 2 );
                CVisTestSlaveThread thread4( m_heightMap, 4, 3 );

                thread1.SetPosition(m_position);
                thread2.SetPosition(m_position);
                thread3.SetPosition(m_position);
                thread4.SetPosition(m_position);

                if( !thread1.Start( 16* 1024, 1<<1 | 1<<2 ) )
                {
                    THOT_ASSERT(false, "CANNOT START VIS TEST THREAD");
                }

                if( !thread2.Start( 16* 1024, 1<<3|1<<4))
                {
                    THOT_ASSERT(false, "CANNOT START VIS TEST THREAD");
                }
                if( !thread3.Start( 16* 1024,1<<5|1<<6) )
                {
                    THOT_ASSERT(false, "CANNOT START VIS TEST THREAD");
                }

                if( !thread4.Start( 16* 1024, 1<<7 | 1<<8))
                {
                    THOT_ASSERT(false, "CANNOT START VIS TEST THREAD");
                }

                CTimer visTestTimer;
                visTestTimer.Start();

                Sleep(1000);

                thread1.WaitUntilStopped();
                thread2.WaitUntilStopped();
                thread3.WaitUntilStopped();
                thread4.WaitUntilStopped();

                CTimer::TimeUnits deltaStart =  visTestTimer.Stop();
                THOT_TRACE_LINE( "VIS TEST ASYNCHRONOUS TIME: Seconds[%d], Milis[%d], Micros[%d]",CTimer::GetSeconds(deltaStart),  CTimer::GetMiliseconds(deltaStart), CTimer::GetMicroseconds(deltaStart) );

                m_makeNewTest = false;
            }
            else
            {
                Sleep( 10 );
            }
        }
    }
    
    void MakeNewTest( const tVect3& position )
    {
        CAutoLock<CCritSection> lock(m_criticalSection);
        m_makeNewTest = true;
        m_position = position;
    }

    void        Stop(){m_stop = true;}

public:

    CHeightMap*     m_heightMap;
    tVect3          m_position;
    Bool            m_stop;
    union 
    {
        Bool            m_makeNewTest;
        Bool            m_idle;
    };
    
};



//--------------------------------------------------------------------------------
CHeightMap::CHeightMap()
    : m_width   ( 0 )
    , m_lenght  ( 0 )
    , m_data    ( NULL )
    , m_isDirty ( false )
    , m_visTestThread(NULL)
    , m_visCommandCount(0)
    , m_commands(NULL)
{
    CHeightMapHelpers::GetInstance();
    m_visTestThread = THOT_NEW CVisTestThread(this);
    if( !m_visTestThread->Start( 16* 1024, 1 | 1<<2 | 1<<3))
    {
        THOT_ASSERT(false, "CANNOT START VIS TEST THREAD");
    }

    m_visCommandCount = 20;
    m_commands = (CVisbilityCommand**) THOT_MALLOC( m_visCommandCount* sizeof(CVisbilityCommand*) );
    for( u32 i=0; i<m_visCommandCount; i++)
    {
        m_commands[i] = THOT_NEW CVisbilityCommand( this, m_visCommandCount, i );
    }
}

//--------------------------------------------------------------------------------
CHeightMap::~CHeightMap()
{
}

//--------------------------------------------------------------------------------
Bool CHeightMap::LoadFromTexture( const CString& fileName, const SHeightMapProperties& properties  )
{


    m_properties = properties;

    int width, height, channels;
    m_data = SOIL_load_image
    	(
    		fileName.c_str(),
    		&width, &height, &channels,
    		SOIL_LOAD_L
    	);

    if( !m_data )
    {
        // load failed
        return false;
    }

    m_width = ThNumericCast<u32>( width );
    m_lenght = ThNumericCast<u32>( height );
    m_texelToVertexMesh.Resize( m_width * m_lenght);
    if( !BuildTexelToVertexMesh() )
    {
        return false;
    }

    if( !Tesselate( 3 ) )
    {
        return false;
    }

    if( !GenerateMesh() )
    {
        return false;
    }

    //MakeVisTest(tVect3());

    //FileSystem::FileHandle fileHandle = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY);
    //fileHandle->Open( "terrainData.txt", EAccesMode::E_ACCES_MODE_WRITE);
    //CString source = StringUtils::FormatString("%d %d\n", m_lenght, m_width);
    //for( u32 i=0; i<m_lenght; i++)
    //{
    //    for( u32 j=0; j<m_width; j++)
    //    {
    //        SHeightMapVertex& vertex = GetVertex(i,j);
    //        source += StringUtils::FormatString("%f %f %f\n", vertex.m_position.x, vertex.m_position.y, vertex.m_position.z);
    //    }
    //}

    //if( !fileHandle->Write( source.c_str(), source.GetLenght(), 1) )
    //{
    //    THOT_ASSERT(false, "FAILED TO WRITE TO TEST FILE");
    //}

    return true;
}

Bool CHeightMap::Tesselate( u32 iterations )
{
    return true;
}

//--------------------------------------------------------------------------------
Bool CHeightMap::GenerateMesh()
{
    const u32 triangleCount = 2 * (m_width -1) * ( m_lenght - 1);
    const u32 verticesCount = m_width * m_lenght;
    const u32 indicesCount = triangleCount * 3;
    const u32 cellsWidth = m_width - 1;
    const u32 cellsLenght = m_lenght - 1;
    const u32 cellsCount = cellsWidth * cellsLenght;

    // build vertex buffer
    typedef RenderLowLevel::SVertex_PNT TVertexType;
    thVector<TVertexType> vertices;
    vertices.Resize( verticesCount );

    for( u32 row=0; row<m_lenght; row++)
    {
        for( u32 col=0; col<m_width; col++)
        {
            SHeightMapVertex& heightMapVertex = GetVertex( col, row );
            TVertexType& vertex = vertices[row * m_lenght + col];
            vertex.m_vertex = heightMapVertex.m_position;
            vertex.m_normal = heightMapVertex.m_normal;
            vertex.m_textCoord = heightMapVertex.m_textCoord;
            //vertex.m_color = CColor( Random::GetFloat(0.f, 1.f), Random::GetFloat(0.f, 1.f), Random::GetFloat(0.f, 1.f), 1.f  );
            vertex.m_color = CColor( 1.f, 0.f, 0.f, 0.f  );

        }
    }

    THOT_ASSERT( ThNumericCast<u32>( u16(-1) ) < indicesCount, "INDEX BUFFER TO BIG");
    //thVector<u16> indices;
    for( u32 row=0; row<cellsLenght; row++ )
    {
        for( u32 col = 0; col <cellsWidth; col++ )
        {
            // add indices from a cell

            // first triangle
            m_indices.PushBack( (row + 1) * m_lenght + ( col     ) );
            m_indices.PushBack( (row    ) * m_lenght + ( col     ) );
            m_indices.PushBack( (row    ) * m_lenght + ( col + 1 ) );

            // second triangle
            m_indices.PushBack( (row + 1) * m_lenght + ( col + 1 ) );
            m_indices.PushBack( (row + 1) * m_lenght + ( col     ) );
            m_indices.PushBack( (row    ) * m_lenght + ( col + 1 ) );
        }
    }

    THOT_ASSERT(m_indices.Size() == indicesCount);

    m_generatedMesh = MeshFactory::CreateMesh( vertices, m_indices);

    CMaterial material;
    material.m_ambient = CColor(0.3f, 0.3f, 0.3f, 1.f);
    material.m_diffuse = CColor(0.8f, 0.5f, 1.f, 1.f);
    material.m_specular = CColor(0.3f, 0.3f, 0.3f, 1.f);
    material.m_shininess = 100.f;
    material.m_opacity = 1.f;
    m_generatedMesh->SetMaterial( material );

    m_generatedMesh->SetPrimitiveType(EMeshPrimitive::E_MESH_PRIMITIVE_TRIANGLES );

    return true;
}

//--------------------------------------------------------------------------------
Bool CHeightMap::BuildTexelToVertexMesh()
{
    if( m_lenght == 0 || m_width == 0)
    {
        return false;
    }

    u32 setCount = 0;
    for( u32 row=0; row<m_lenght; row++)
    {
        for( u32 col=0; col<m_width; col++)
        {
            float height = GetHeight( col, row);
            float zPos = ((float)row/float(m_lenght-1)) * m_properties.m_lenght;
            float xPos = ( (float)col/float(m_width-1)) * m_properties.m_width;
            SHeightMapVertex& heightMapVertex = GetVertex( col, row );
            heightMapVertex.m_position = tVect3( xPos, height, zPos );
            heightMapVertex.m_textCoord.x = (float)row/ (float)(m_lenght-1) * 30.f;
            heightMapVertex.m_textCoord.y = (float)col/(float)(m_width -1 ) * 30.f;
            heightMapVertex.m_textCoord.z = 0.f;
            setCount++;
        }
    }
    THOT_ASSERT( setCount == m_texelToVertexMesh.Size(), "WE DID NOT SET ALL VERTICES"); 

    ////generate normals
    for( s32 row=0; row< ThNumericCast<s32>(m_lenght); row++)
    {
        for( s32 col=0; col<ThNumericCast<s32>(m_width); col++)
        {
            SHeightMapVertex& vertex = GetVertex(col, row);

            s32 nextXPosIdx = ThMin( ThNumericCast<s32>(m_lenght -1), row + 1 );
            s32 prevXPosIdx = ThMax( 0, row -1 );
            SHeightMapVertex& nextXVertex = GetVertex( col, nextXPosIdx );
            SHeightMapVertex& prevXVertex = GetVertex( col, prevXPosIdx );
            tVect3 xDir = nextXVertex.m_position - prevXVertex.m_position;

            s32 nextZPosIdx = ThMin( ThNumericCast<s32>(m_width -1), col + 1 );
            s32 prevZPosIdx = ThMax( 0, col -1 );

            SHeightMapVertex& nextZVertex = GetVertex( nextZPosIdx, row );
            SHeightMapVertex& prevZVertex = GetVertex( prevZPosIdx, row );
            tVect3 zDir = nextZVertex.m_position - prevZVertex.m_position;

            vertex.m_normal = -Unit( Cross( xDir, zDir) );
        }
    }



    return true;
}

//--------------------------------------------------------------------------------
float CHeightMap::GetHeight( u32 x, u32 y )
{
    THOT_ASSERT(m_data, "DATA WAS NOT LOADED");
    THOT_ASSERT( x < m_width && y<m_lenght, "INVALID DATA ACCES FOR HEIGHTMAP");
    u8 value = m_data[ y * m_width + x ];
    float height = ((float)value/255.f) * m_properties.m_maxHeight;

    return height;
}

//--------------------------------------------------------------------------------
float CHeightMap::GetHeight( float x, float y)
{
    float origX = x;
    float origY = y;

    x = ( (x * float(m_lenght-1) )/(m_properties.m_lenght) );
    y = ( (y * float(m_width-1) )/(m_properties.m_width) );

    u32 _x = u32(x);
    u32 _y = u32(y);
    THOT_ASSERT(_x>=0 && _y>= 0 && _x < m_width && y<m_lenght);
    
#if defined(THOT_ENABLE_DEBUG)
    //if( _x > 0 )
    //{
    //    THOT_ASSERT(_x+1 < m_width);
    //}
    //if(_y > 0)
    //{
    //    THOT_ASSERT(_y+1< m_lenght);
    //}
#endif


    x = x - float( _x );
    y = y - float( _y );
    THOT_ASSERT( x>=0.f && x<=1.f && y>=0.f && y<=1.f);

    float a = 0.f;
    float b = 0.f;
    u32 _a =0;
    u32 _b =0;

    tVect3 localXY = tVect3(x, y, 0.f);
    if( fequals( VectLen(localXY), 0, 0.001f ) )
    {
        return GetHeight(_x, _y);
    }

    tVect3 v = Unit( localXY );
    float dot =  Dot(v, xAxis);
    const float cosinusPIOver4 = 0.70710678118654752440084436210485f;
    if( dot < cosinusPIOver4 )
    {
        b = 1.f;
        _b = 1;
    }
    else
    {
        a = 1.f;
        _a = 1;
    }

    tVect3& V0 = tVect3(0.f, 0.f, 0.f);
    tVect3& V1 = tVect3(a, b, 0.f );
    tVect3& V2 = tVect3( 1.f, 1.f, 0.f );

    tVect3 barycentricCoordinates = nullVect;
    THOT_ASSERT( MathUtils::PointInTriangle( V0, V1, V2, localXY ) );
    MathUtils::GetBarycentricCoordinates( V0, V1, V2, localXY , barycentricCoordinates);
    
#if defined(THOT_ENABLE_DEBUG)
    float sumBary = barycentricCoordinates.x + barycentricCoordinates.y + barycentricCoordinates.z;
    THOT_ASSERT(fequals(  sumBary, 1.f, 0.01f ));
#endif

    float h0 = GetHeight(_x, _y);
    float h1 = GetHeight( _x +_a, _y + _b);
    float h2 = GetHeight( _x+1, _y+1 );
   
    float height = h0 * barycentricCoordinates.x + h1 * barycentricCoordinates.y +  h2*barycentricCoordinates.z;
    return height;
}

//--------------------------------------------------------------------------------
tVect3 CHeightMap::GetNormal(float x, float y)
{
    float origX = x;
    float origY = y;
    x = ( (x * float(m_lenght) )/m_properties.m_lenght );
    y = ( (y * float(m_width) )/m_properties.m_width );
    u32 _x = u32(x);
    u32 _y = u32(y);
    THOT_ASSERT(_x>=0 && _y>= 0 && _x < m_width && y<m_lenght);


    x = x - float( _x );
    y = y - float( _y );
    THOT_ASSERT( x>=0.f && x<=1.f && y>=0.f && y<=1.f);

    float a = 0.f;
    float b = 0.f;
    u32 _a =0;
    u32 _b =0;

    tVect3 localXY = tVect3(x, y, 0.f);
    tVect3 v = Unit( localXY );
    float dot =  Dot(v, xAxis);
    const float cosinusPIOver4 = 0.70710678118654752440084436210485f;
    if( dot < cosinusPIOver4 )
    {
        b = 1.f;
        _b = 1;
    }
    else
    {
        a = 1.f;
        _a = 1;
    }

    tVect3& V0 = tVect3(0.f, 0.f, 0.f);
    tVect3& V1 = tVect3(a, b, 0.f );
    tVect3& V2 = tVect3( 1.f, 1.f, 0.f );

    tVect3 barycentricCoordinates = nullVect;
    THOT_ASSERT( MathUtils::PointInTriangle( V0, V1, V2, localXY ) );
    MathUtils::GetBarycentricCoordinates( V0, V1, V2, localXY , barycentricCoordinates);
    
#if defined(THOT_ENABLE_DEBUG)
    float sumBary = barycentricCoordinates.x + barycentricCoordinates.y + barycentricCoordinates.z;
    THOT_ASSERT(fequals(  sumBary, 1.f, 0.01f ));
#endif

    tVect3& normalV0 = GetVertex(_x, _y).m_normal;
    tVect3& normalV1 = GetVertex( _x +_a, _y + _b).m_normal;
    tVect3& normalV2 = GetVertex(_x+1, _y+1).m_normal;
   
    tVect3 normal = normalV0 * barycentricCoordinates.x + normalV1 * barycentricCoordinates.y +  normalV2*barycentricCoordinates.z;
    VectNor(normal);
    return normal;
}

//--------------------------------------------------------------------------------
SHeightMapVertex& CHeightMap::GetVertex( u32 x, u32 y )
{
    THOT_ASSERT( x < m_width && y<m_lenght, "INVALID DATA ACCES FOR HEIGHTMAP");
    const u32 verticesCount = m_width * m_lenght;
    THOT_ASSERT( m_texelToVertexMesh.Size() == verticesCount );
    return m_texelToVertexMesh[ y* m_width + x];
}

//--------------------------------------------------------------------------------
void CHeightMap::DebugUpdateVertices( IMesh* _mesh )
{
    typedef RenderLowLevel::SVertex_PNT TVertexType;
    typedef CMesh<RenderLowLevel::SVertex_PNT, u16> TMesh;
    TMesh* mesh = (TMesh*) _mesh;
    RenderLowLevel::CVertexBufferObject<TVertexType>& vertexBuffer =  mesh->GetVertexArray().GetVertexBuffer();
    
    gl::BindBuffer(gl::ARRAY_BUFFER, vertexBuffer.GetNativeHandle() );
    TVertexType* oldBuffer =  (TVertexType*) gl::MapBuffer( gl::ARRAY_BUFFER, gl::WRITE_ONLY);

    u32 size = ThNumericCast<u32>( vertexBuffer.GetSize() );
    for( u32 i=0; i<size; i++ )
    {
        //oldBuffer[i].m_color.a = 1.f;
        //oldBuffer[i].m_color.a = m_texelToVertexMesh[i].m_visible?1.f:0.f;
        //if( m_texelToVertexMesh[i].m_visible )
        //{
        //    oldBuffer[i].m_color.a = 1.f;
        //}
        //else
        //{

        //}
        oldBuffer[i].m_color = m_texelToVertexMesh[i].m_color;
    }

    gl::UnmapBuffer(gl::ARRAY_BUFFER);


}

//--------------------------------------------------------------------------------
void CHeightMap::MakeVisTest_Asynchronous( const tVect3& position)
{
    //m_visTestThread->MakeNewTest( position );

    //reset the vis colors;
    for( u64 j=0; j<m_texelToVertexMesh.Size(); j++ )
    {
        SHeightMapVertex& vertex = m_texelToVertexMesh[j];
        vertex.m_color = CColor(0.f, 0.f, 0.f, 0.f);
    }

    for( u32 i=0; i<m_visCommandCount; i++)
    {
        m_commands[i]->SetPosition(position);
        CHeightMapHelpers::GetInstance()->AddAsynchronousCommand( m_commands[i] );
    }
    m_timerVisTest.Start();
}

//--------------------------------------------------------------------------------
void CHeightMap::AddVisibleNode( CVisibleNode& visNode )
{
    CAutoLock<CCritSection> lock(m_criticalSection);
    m_visibleNodes.PushBack( visNode );
}

//--------------------------------------------------------------------------------
void CHeightMap::SetDirty( Bool value )
{
    CAutoLock<CCritSection> lock(m_criticalSection);
    m_isDirty = value;
}

//--------------------------------------------------------------------------------
Bool CHeightMap::VisTestsDone()const
{
    if( !m_commands )
    {
        return false;
    }

    for( u32 i=0; i<m_visCommandCount; i++ )
    {
        if( !m_commands[i]->IsDone() )
        {
            return false;
        }
    }

    CTimer::TimeUnits deltaStart =  m_timerVisTest.Stop();

    static bool printed = false;
    if(!printed)
    {
        THOT_TRACE_LINE("VIS TEST DONE IN: Milis[%d], Micros[%d]", CTimer::GetMiliseconds(deltaStart), CTimer::GetMicroseconds(deltaStart) );
        printed = true;
    }

    return true;
}

//--------------------------------------------------------------------------------
void CHeightMap::GetNearestVisPoint( const tVect3& source, tVect3& outTarget )
{
    float minDistance = 3600000.f;
    u64 minIndex = 0;
    for( u64 i=0; i<m_visibleNodes.Size(); i++ )
    {
        tVect3& target = m_visibleNodes[i].m_vertex.m_position;
        float lenSqr = VectLenSquared( target - source );
        if( minDistance > lenSqr )
        {
            minIndex = i;
            minDistance = lenSqr;
        }
    }

    outTarget = m_visibleNodes[minIndex].m_vertex.m_position;
}


//--------------------------------------------------------------------------------
void CHeightMap::MakeVisTest( tVect3& viewPosition, u32 index )
{
    /*
    Triangles from a cell in heightmap
      A_________B
      |       / |
      |      /  |
      |     /   |
      |    /    |
      |   /     |
      |  /      |
      | /       |
     C|/________|D
    */

    //reset the vis colors;
    for( u64 j=0; j<m_texelToVertexMesh.Size(); j++ )
    {
        SHeightMapVertex& vertex = m_texelToVertexMesh[j];
        vertex.m_color = CColor(0.f, 0.f, 0.f, 0.f);
    }

    CRenderCamera* renderCamera = CRender::GetInstance()->GetCamera();
    m4x4 cameraTM = i4x4;
    renderCamera->GetTM(cameraTM);
    tVect3 camPos = POS(cameraTM);
    tVect3 dir = AXEZ(cameraTM);
    tVect3 targetPoint = camPos + dir* 800.f;
    tVect3 to = nullVect;
    tVect3 from = camPos;

    THOT_ASSERT( m_indices.Size()%3 == 0 );

    u32 i=0;
    //u32 i = index;
    u32 nextIndex = 0;
    for( i=0; i<m_texelToVertexMesh.Size(); i++ )
    {
        THOT_ASSERT(nextIndex == i);
        nextIndex++;

        SHeightMapVertex& vertex = m_texelToVertexMesh[i];

        to = vertex.m_position;
        tVect3 dir = to-from;
        float lenght = VectNor(dir);
        //to = to + dir * (lenght - 0.3f);

        //to = camPos + AXEZ(cameraTM)*800.f;

        bool visible = true;
        for( u64 j=0; j<m_indices.Size(); j+=3)
        {
            u16 indexA = m_indices[j];
            u16 indexB = m_indices[j+1];
            u16 indexC = m_indices[j+2];

            if( indexA == i || indexB == i || indexC == i)
            {
                continue;
            }

            SHeightMapVertex& A = m_texelToVertexMesh[indexA];
            SHeightMapVertex& B = m_texelToVertexMesh[indexB];
            SHeightMapVertex& C = m_texelToVertexMesh[indexC];

            tVect3  out;

            if( MathUtils::intersect3D_RayTriangle( from, to, A.m_position, B.m_position, C.m_position, out )

                )
            {
                //A.m_color = CColor(0.f, 0.f, 1.f, 1.f);;
                //B.m_color = CColor(0.f, 0.f, 1.f, 1.f);;
                //C.m_color = CColor(0.f, 0.f, 1.f, 1.f);;
                visible = false;
                break;
            }
        }
        if(visible)
        {
            vertex.m_color = CColor(1.f, 0.f, 0.f, 1.f);
        }
        else
        {
            //vertex.m_color = CColor(0.f, 1.f, 0.f, 1.f);
        }
    }


    SetDirty();
}

//--------------------------------------------------------------------------------
void CHeightMap::MakeVisTest( tVect3& viewPosition, u32 startdIndex, u32 increment)
{
    tVect3 from = viewPosition;

    THOT_ASSERT( m_indices.Size()%3 == 0 );

    //u32 i = index;
    for( u64 i=startdIndex; i<m_texelToVertexMesh.Size(); i+=increment )
    {
        SHeightMapVertex& vertex = m_texelToVertexMesh[i];

        tVect3 to = vertex.m_position;

        bool visible = true;
        for( u64 j=0; j<m_indices.Size(); j+=3)
        {
            u16 indexA = m_indices[j];
            u16 indexB = m_indices[j+1];
            u16 indexC = m_indices[j+2];

            if( indexA == i || indexB == i || indexC == i)
            {
                continue;
            }

            SHeightMapVertex& A = m_texelToVertexMesh[indexA];
            SHeightMapVertex& B = m_texelToVertexMesh[indexB];
            SHeightMapVertex& C = m_texelToVertexMesh[indexC];

            tVect3  out;

            if( MathUtils::intersect3D_RayTriangle( from, to, A.m_position, B.m_position, C.m_position, out )

                )
            {
                visible = false;
                break;
            }
        }
        if(visible)
        {
            vertex.m_color = CColor(1.f, 0.f, 0.f, 1.f);
            CVisibleNode visibleNode;
            visibleNode.m_vertex = vertex;
            visibleNode.m_nodeIndex = ThNumericCast<u32>(i);
            AddVisibleNode( visibleNode );
        }
    }

    SetDirty();
}