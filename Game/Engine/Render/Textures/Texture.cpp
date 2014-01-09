#include "Render_PCH.h"
#include "Render/Textures/Texture.h"
#include "Render/RenderGL.h"
#include "Kernel/FileSystem/Path.h"
#include "Kernel/FileSystem/FileSystem.h"
#include "Kernel/DataStructures/CString.h"

#include "SOIL.h"

#ifdef CreateFile
#undef CreateFile
#endif

//--------------------------------------------------------------------------------
TNativeTextureHandle DebugLoadTexture( const CString& fileName )
{
    FileSystem::FileHandle textureFile = FileSystem::CreateFile( EFileType::E_FILE_TYPE_MEMORY );
    if( !textureFile->Open( fileName, EAccesMode::E_ACCES_MODE_READ) )
    {
        return -1;
    }

    u64 fileSize = textureFile->GetSize();
    void* rawMemory = THOT_MALLOC(fileSize);
    if( !textureFile->Read( rawMemory, fileSize, 1 ) )
    {
        return -1;
    }

    SGLTextureHeader* header = (SGLTextureHeader*)rawMemory;
    if( header->m_magicNumber != SGLTextureHeader::MAGIC_NUMBER )
    {
        return -1;
    }

    //begin creating native texure handle
    GLuint nativeTextureHandle = -1;
    gl::GenTextures( 1, &nativeTextureHandle);
    gl::BindTexture( header->m_target, nativeTextureHandle );

    for( u32 mipLevel = 0; mipLevel <= header->m_levels; mipLevel ++ )
    {
        void* mipLevelData = (char*)header + header->m_mipOffsets[ mipLevel ];
        if( header->m_isCompressed )
        {
            gl::CompressedTexImage2DARB(    header->m_target,
                                            mipLevel,
                                            header->m_internalFormat,
                                            header->m_width>>mipLevel,
                                            header->m_height>>mipLevel,
                                            0,
                                            header->m_mipSizes[ mipLevel],
                                            mipLevelData);
        }
     }
    
    THOT_FREE(rawMemory);

    return nativeTextureHandle;
}


//--------------------------------------------------------------------------------
Bool IsValidTextureHandle( TNativeTextureHandle textureHandle)
{
    if( textureHandle != INVALID_TEXTURE_HANDLE )
    {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------
Bool IsValidTextureType( u32 textureType )
{
    if( textureType == gl::TEXTURE_1D ||
        textureType == gl::TEXTURE_2D ||
        textureType == gl::TEXTURE_3D ||
        textureType == gl::TEXTURE_CUBE_MAP
        )
    {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------
Bool IsValidTextureUnit( u32 textureUnit)
{
    if( textureUnit != INVALID_TEXTURE_PROP_VALUE
        && textureUnit < TEXTURE_MAX_TEXTURE_UNITS
        )
    {
        return true;
    }

    return false;
}

//--------------------------------------------------------------------------------
STextureProperties::STextureProperties()
    : m_nativeTextureHandle         (INVALID_TEXTURE_HANDLE)
    , m_textureUnit                 (INVALID_TEXTURE_PROP_VALUE)
    , m_textureType                 (INVALID_TEXTURE_PROP_VALUE)
{}

//--------------------------------------------------------------------------------
CTexture::CTexture()
{
}

//--------------------------------------------------------------------------------
CTexture::~CTexture()
{
    if( m_properties.m_nativeTextureHandle != INVALID_TEXTURE_HANDLE)
    {
        THOT_TODO("UNCOMMENT THIS AFTER FIXING THE BUG");
        //gl::DeleteTextures( 1, &m_properties.m_nativeTextureHandle);
    }
}

//--------------------------------------------------------------------------------
void CTexture::DebugLoad( const CString& fileName)
{
    Soil_TextureHeader header;
    ThZeroMemoryTmpl( header );
    
    THOT_ASSERT(CPath::FileExists(fileName), "FILE[%s] DOES NOT EXISTS");
    m_properties.m_nativeTextureHandle = SOIL_load_OGL_texture( fileName, 0, 0, SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_MIPMAPS, &header );
    m_properties.m_textureType = header.m_target;

    THOT_ASSERT(IsValidTextureType(m_properties.m_textureType));
}


//--------------------------------------------------------------------------------
Bool CTexture::IsValid()const
{
    return  IsValidTextureHandle(m_properties.m_nativeTextureHandle) &&
            IsValidTextureType(m_properties.m_textureType) &&
            IsValidTextureUnit(m_properties.m_textureUnit);
}



//--------------------------------------------------------------------------------
void CTexture::Bind()const
{
    RENDER_GUARD_BLOCK
    gl::ActiveTexture( gl::TEXTURE0 + m_properties.m_textureUnit );
    gl::BindTexture( m_properties.m_textureType, m_properties.m_nativeTextureHandle );
}