//
//  MetaData.hpp
//  bird
//
//  Created by 汪依尘 on 7/23/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef MetaData_hpp
#define MetaData_hpp

#include <stdio.h>
#include <map>
#include <vector>

/*          Utility         */
#define     NAME_GENERATOR()    CREATOR##__LINE__

/*          Declare MetaData         */
#define     DECLARE_META( TYPE ) \
static      rttr::ReType<TYPE>::type*    NULL_CAST(); \
static      void                         RegisterMetaMember(); \
static      void                         AddMember( const char* name, \
                                                    const unsigned long& offset, \
                                                    rttr::MetaData* metaData)

/*          Define MetaData         */
#define     DEFINE_META( TYPE )\
rttr::MetaCreator<rttr::ReType<TYPE>::type> NAME_GENERATOR()( #TYPE, sizeof(TYPE)); \
rttr::ReType<TYPE>::type* TYPE::NULL_CAST() { return reinterpret_cast<rttr::ReType<TYPE>::type*>(NULL); } \
\
void TYPE::AddMember(const char* name, const unsigned long& offset, rttr::MetaData* metaData)\
{\
    rttr::MetaCreator<rttr::ReType<TYPE>::type >::AddMember( name, offset, metaData);\
}\
\
void TYPE::RegisterMetaMember()

/*          Get MetaData by String/Object       */
#define     META_BYSTR( NAME )        rttr::MetaManager::Get(NAME)
#define     META_BYOBJ( OBJ )         rttr::MetaCreator< rttr::ReType<decltype(OBJ)>::type >::Get()
#define     META_BYTYPE( TYPE )       rttr::MetaCreator< rttr::ReType<TYPE>::type >::Get()

/*          Add a Member to MetaData       */
#define     ADD_MEMBER( VAR_NAME ) \
AddMember( #VAR_NAME, (unsigned long)(&(NULL_CAST()->VAR_NAME)), META_BYOBJ(NULL_CAST()->VAR_NAME))


namespace rttr {
    
    //========= MetaData ==========
    
    class Member;
    class MetaData
    {
    public:
        MetaData();
        MetaData(const char* name, unsigned size);
        ~MetaData();
        void Init(const char* name, unsigned size);
        inline char const * GetName() const { return m_Name; }
        inline unsigned GetSize() const { return m_Size; }
        inline std::vector<rttr::Member*>& GetMembers() { return m_Members; }
        
    private:
        std::vector<rttr::Member*> m_Members;
        const char* m_Name;
        unsigned m_Size;
    };
    
    
    
    //========= Refined Type ==========
    
    template<typename T>
    struct ReType
    {
        typedef T type;
    };
    
    template<typename T>
    struct ReType<const T>
    {
        typedef typename ReType<T>::type type;
    };
    
    template<typename T>
    struct ReType<T&>
    {
        typedef typename ReType<T>::type type;
    };
    
    template<typename T>
    struct ReType<const T&>
    {
        typedef typename ReType<T>::type type;
    };
    
    template<typename T>
    struct ReType<T&&>
    {
        typedef typename ReType<T>::type type;
    };
    
    template<typename T>
    struct ReType<const T*>
    {
        typedef typename ReType<T*>::type type;
    };
    
    
    
    //========= MetaManager ==========
    
    class MetaManager
    {
    public:
        typedef std::map<const char*, MetaData const*> MetaMap;
        static inline MetaMap& GetMetaMap() { return m_MetaMap; }
        
        static void RegisterMeta(MetaData const * metaData);
        static MetaData const* GetMeta(const char* name);
        
    private:
        static MetaMap m_MetaMap;
    };
    
    
    
    //========= Member ==========
    
    class Member
    {
    public:
        Member(const char* name, const unsigned long& offset, MetaData* metaData);
        ~Member();
        inline unsigned long GetOffset() const { return m_Offset; }
        inline const char* GetName() const { return m_Name; }
        inline MetaData const* GetMeta() const { return m_MetaData;}
    private:
        const char* m_Name;
        unsigned long m_Offset;
        MetaData const* m_MetaData;
    };
    
    
    
    //========= MetaCreator ==========
    
    template <class T>
    class MetaCreator
    {
    public:
        MetaCreator(const char* name, unsigned size);
        ~MetaCreator();
    public:
        static void Init(const char* name, unsigned size);
        static MetaData* Get();
        static void RegisterMetaMember();
        static void AddMember(const char* name, const unsigned long& offset, MetaData* metaData);
    private:
        static MetaData m_MetaData;
    };
    template<class T>
    MetaData MetaCreator<T>::m_MetaData;
    
    template<class T>
    MetaData* MetaCreator<T>::Get()
    {
        return &m_MetaData;
    }
    
    template<class T>
    void MetaCreator<T>::AddMember(const char* name,
                                   const unsigned long& offset,
                                   MetaData* metaData)
    {
        m_MetaData.GetMembers().push_back(new Member(name, offset, metaData));
    }
    
    template<class T>
    void MetaCreator<T>::RegisterMetaMember()
    {
        //        MetaManager::RegisterMeta(&m_MetaData);
        ReType<T>::type::RegisterMetaMember();
    }
    
    template<class T>
    MetaCreator<T>::MetaCreator(const char* name, unsigned size)
    {
        Init(name, size);
        MetaManager::RegisterMeta(&m_MetaData);
    }
    
    template<class T>
    MetaCreator<T>::~MetaCreator()
    {
    }
    
    template<class T>
    void MetaCreator<T>::Init(const char* name, unsigned size)
    {
        Get()->Init(name, size);
    }

    
}

#endif /* MetaData_hpp */
