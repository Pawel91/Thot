#if !defined(__KERNEL_MEMORY_HANDLING_H__)
#define __KERNEL_MEMORY_HANDLING_H__

#include "Kernel/DataTypes.h"
#include "Kernel/DebugSystem/Assert.h"
#include "Kernel/MetaTemplates/MetaTemplates.h"
#include "Kernel/MemoryManagement/MemoryConfig.h"
#include "Kernel/MemoryManagement/MemoryOperation.h"
#include "Kernel/Externals.h"
#include "Kernel/KernelUtils.h"

#if defined(THOT_ENABLE_HANDLE_MEMORY_OPERATION)
#   define MEM_HANDLING_ADD_OPERATION( __buffer, __realBuffer, __size, __realSize, __operation, __objCount, __file, __line) \
    do                                                                                  \
    {                                                                                   \
        MemoryManagement::CMemoryOperation operation;                                   \
        operation.m_operation = __operation;                                            \
        operation.m_buffer = __buffer;                                                 \
        operation.m_realBuffer = __realBuffer;                                          \
        operation.m_bufferSize = __size;                                                      \
        operation.m_realBufferSize = __realSize;                                        \
        operation.m_fileLine = __line;                                                  \
        operation.m_objectCount = __objCount;                                           \
        strcpy(operation.m_fileName, __file);                                           \
        MemoryManagement::CMemoryOperationHandler::GetInstance()->AddMemoryOperation( operation );   \
    }while(false)


#else
#   define MEM_HANDLING_ADD_OPERATION( __buffer, __realBuffer, __size, __realSize, __operation, __objCount, __file, __line) do{}while(false)
#endif //THOT_ENABLE_MEMORY_TRACKING



namespace MemoryManagement
{
    class CMemoryOperation;
    ///////////////////////////////////////////////////////////////////////////
    //          MAIN CLASS USED TO HANDLE ALL MEMORY ALLOCATIONS/DEALLOCATIONS
    //////////////////////////////////////////////////////////////////////////
    class KERNEL_API CMemoryOperationHandler
    {
    public:
        static CMemoryOperationHandler*        GetInstance();
        static CMemoryOperationHandler*        CreateInstance();
        static void                            DestroyInstance();
    
    public:
        void    AddMemoryOperation      ( const CMemoryOperation& operation );
    
    };
    


    //////////////////////////////////////////////////////////////////////////////////////////
    //      HELPER TEMPLATE CLASS USED TO TRACK MEMORY BY C++ new/delete OPERATORS
    //////////////////////////////////////////////////////////////////////////////////////////
    template<class T, u32 MEM_OPERATION> // MEM_OPERATION FROM MemoryManagement::EMemoryOperation
    class CHelper
    {
        friend class CNewArrayHandler;
        friend class CNewHandler;
        friend class CDeleteHandler;
        friend class CDeleteArrayHandler;
    private:
        //compile-time values used to find internal buffer allocated by new operator
        enum
        {
             CLASS_ALIGNMENT = MetaTemplates::enable_if<
                                                        MetaTemplates::CTypeTraits<T>::Properties::isAbstract,
                                                        MetaTemplates::CIntWrap<0>, MetaTemplates::CIntWrap<__alignof(T)> 
                                                        >::result::value  //MetaTemplates::CTypeTraits<T>::Properties::alignment
            
            // the destructor must not be trivial and MUST NOT BE A FUNDAMENTAL TYPE because 
            // intrinsic compiler __has_trivial_destructor(T) seems to have a bug for pointer types
            // [TODO] add this condition inside Trivial::hasDestructor to fix the bug
            ,HAS_DESTRUCTOR =   !MetaTemplates::CTypeTraits<T>::Properties::isFundamental &&
                                !MetaTemplates::CTypeTraits<T>::Trivial::hasDestructor 
            
            // din experimente:D..daca nu e bine o sa sara asserturile cu HeapValidate;
            ,NEW_ARRAY_OFFSET = MetaTemplates::Clamp<4,16, CLASS_ALIGNMENT>::value

            ,OFFSET_IS_ENABLED = HAS_DESTRUCTOR && (MEM_OPERATION == MemoryManagement::EMemoryOperation_NewArray || MEM_OPERATION == MemoryManagement::EMemoryOperation_DeleteArray)

            // avem toate informatiile la compile-time ca sa calculam offsetul care-l face operatorul new atunci cand aloca memorie
            ,NEW_REAL_OFFSET = MetaTemplates::enable_if< OFFSET_IS_ENABLED, MetaTemplates::CIntWrap<NEW_ARRAY_OFFSET>, MetaTemplates::CIntWrap<0>>::result::value
        };

        static inline T* GetRealBuffer( T* bufferAllocatedByNew )
        {
            return reinterpret_cast<T*>( ((u8*)bufferAllocatedByNew) - NEW_REAL_OFFSET );
        }

        static inline void Track( T* buffer, const char* file, u64 line )
        {
            MemoryManagement::CMemoryOperation operation;
            operation.m_operation = ThNumericCast<MemoryManagement::EMemoryOperation>(MEM_OPERATION);
            operation.m_buffer = buffer;
            operation.m_realBuffer = GetRealBuffer( buffer );
            THOT_ASSERT( MemoryManagement::CManager::GetInstance()->Validate( operation.m_realBuffer ), "FAILED TO COMPUTE REAL BUFFER ALLOCATED BY NEW OPERATOR" );
            operation.m_realBufferSize = MemoryManagement::CManager::GetInstance()->GetBlockSize( operation.m_realBuffer );
            operation.m_bufferSize = operation.m_realBufferSize - NEW_REAL_OFFSET;
            thSize size = sizeof(T);
            THOT_ASSERT( ( MEM_OPERATION & MemoryManagement::EMemoryOperation_Allocation)?operation.m_bufferSize % sizeof(T) == 0 : true );
            operation.m_objectCount = ( MEM_OPERATION & MemoryManagement::EMemoryOperation_Allocation)? operation.m_bufferSize / sizeof(T) : -1;
            
            operation.m_fileLine = line;
            strcpy(operation.m_fileName, file);

            MemoryManagement::CMemoryOperationHandler::GetInstance()->AddMemoryOperation( operation );
        }
    };



    class KERNEL_API CNewDeleteHandlerBase
    {
    protected:
        CNewDeleteHandlerBase( const char* file, u64 line );


    protected:
        char        m_file[256];
        u64         m_line;
    
    };


    ////////////////////////////////////////////////////////////////////////////
    //              HELPER CLASS USED TO TRACK MEMORY ALLOCATED BY NEW
    ////////////////////////////////////////////////////////////////////////////
    class KERNEL_API CNewHandler:public CNewDeleteHandlerBase
    {
    public:

        typedef CNewDeleteHandlerBase super;
        CNewHandler(const char* file, u64 line)
            :super( file, line)
        {
        }
    
    public:
        template<class T>
        inline T* operator * ( T* bufferAllocatedByNew)
        {
            CHelper<T, MemoryManagement::EMemoryOperation_New>::Track( bufferAllocatedByNew, m_file, m_line );
            return bufferAllocatedByNew;
        };
    };

    ////////////////////////////////////////////////////////////////////////////
    //              HELPER CLASS USED TO TRACK MEMORY ALLOCATED BY NEW ARRAY
    ////////////////////////////////////////////////////////////////////////////
    class KERNEL_API CNewArrayHandler:public CNewDeleteHandlerBase
    {
    public:

        typedef CNewDeleteHandlerBase super;
        CNewArrayHandler(const char* file, u64 line)
            :super( file, line)
        {
        }
    
    public:
        template<class T>
        inline T* operator * ( T* bufferAllocatedByNew)
        {
            CHelper<T, MemoryManagement::EMemoryOperation_NewArray>::Track( bufferAllocatedByNew, m_file, m_line );
            return bufferAllocatedByNew;
        };
    };

    /////////////////////////////////////////////////////////////////////////////////
    //              HELPER CLASS USED TO TRACK MEMORY FREED BY DELETE
    //////////////////////////////////////////////////////////////////////////////////
    class KERNEL_API CDeleteHandler:public CNewDeleteHandlerBase
    {
    public:
        typedef CNewDeleteHandlerBase super;
        CDeleteHandler(const char* file, u64 line)
            :super( file, line)
        {
        }

    public:
        template<class T>
        inline T* operator ^( T* toDeleteBuffer )
        {
            CHelper<T, MemoryManagement::EMemoryOperation_Delete>::Track( toDeleteBuffer, m_file, m_line );
            return toDeleteBuffer;
        }
    };


    /////////////////////////////////////////////////////////////////////////////////
    //              HELPER  CLASS USED TO TRACK MEMORY FREED BY DELETE ARRAY
    //////////////////////////////////////////////////////////////////////////////////
    class KERNEL_API CDeleteArrayHandler:public CNewDeleteHandlerBase
    {
    public:
        typedef CNewDeleteHandlerBase super;
        CDeleteArrayHandler(const char* file, u64 line)
            :super( file, line)
        {
        }

    public:
        template<class T>
        inline T* operator ^( T* toDeleteBuffer )
        {
            CHelper<T, MemoryManagement::EMemoryOperation_DeleteArray>::Track( toDeleteBuffer, m_file, m_line );
            return toDeleteBuffer;
        }
    };

} // namespace MemoryManagement




#endif //__KERNEL_MEMORY_HANDLING_H__