//
//  MetaData.cpp
//  bird
//
//  Created by 汪依尘 on 7/23/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "MetaData.hpp"

namespace rttr {
    
    //========= MetaData ==========

    MetaData::MetaData()
    : m_Name(""), m_Size(0)
    {}
    
    MetaData::MetaData(const char* name, unsigned size)
    : m_Name(name), m_Size(size)
    {}
    
    MetaData::~MetaData()
    {}
    
    void MetaData::Init(const char* name, unsigned size)
    {
        m_Name = name;
        m_Size = size;
    }
    
    
    
    //========= MetaCreator ==========
    // template class defined in header
    
    
    
    //========= MetaManager ==========

    MetaManager::MetaMap MetaManager::m_MetaMap = MetaManager::MetaMap();
    
    void MetaManager::RegisterMeta(const MetaData *metaData)
    {
        m_MetaMap.insert(std::make_pair(metaData->GetName(), metaData));
    }
    
    MetaData const* MetaManager::GetMeta(const char *name)
    {
        if (m_MetaMap.find(name) == m_MetaMap.end())
            return nullptr;
        return m_MetaMap[name];
    }
    
    
    
    //========= ReType ==========
    // template struct defined in header


    
    
    //========= Member ==========
    
    Member::Member(const char* name, const unsigned long& offset, MetaData* metaData)
    : m_Name(name), m_Offset(offset), m_MetaData(metaData)
    {}
    
    Member::~Member()
    {}
    
}
