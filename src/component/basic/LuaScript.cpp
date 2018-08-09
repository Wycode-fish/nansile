//
//  LuaScript.cpp
//  bird
//
//  Created by 汪依尘 on 7/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "LuaScript.hpp"
#include "GameObject.hpp"
#include "MeshRenderer.hpp"
#include "ResourceManager.hpp"
#include "Attribute.hpp"
#include "Value.hpp"

LuaScript* LuaScript::GetLuaScript(const char *scriptName, const char *componentName)
{
    if (ResourceManager::GetLuaScriptResourceMap().find(scriptName) != ResourceManager::GetLuaScriptResourceMap().end())
    {
        return ResourceManager::GetLuaScriptResourceMap()[scriptName];
    }
    return nullptr;
}

LuaScript::LuaScript(GameObject* gameObject, const char* scriptName, const char* componentTag, const unsigned char& isBehavior)
: m_State(NULL), m_StkLevel(0), m_FilePath(scriptName), m_ComponentTag(componentTag), m_Type(isBehavior), m_ClassDef(nullptr),  m_UpdateFunc(nullptr), Component(gameObject, "Lua Script")
{
    m_State = luaL_newstate();
    luaL_openlibs(m_State);
    
    if (m_Type == BEHAVIOR_SCRIPT)
    {
        getGlobalNamespace(m_State)
        .beginClass<ml::Vector3f>("vec3")
        .addConstructor<void(*)(const float&, const float&, const float&)>()
        .addData("x", &ml::Vector3f::x)
        .addData("y", &ml::Vector3f::y)
        .addData("z", &ml::Vector3f::z)
        .endClass()
        .beginClass<Transform>("Transform")
        .addConstructor<void(*)(ml::Vector3f, ml::Vector3f, ml::Vector3f)>()
        .addProperty("position", &Transform::GetPosition, &Transform::SetPosition)
        .addProperty("rotation", &Transform::GetRotation, &Transform::SetRotation)
        .addProperty("scale", &Transform::GetScale, &Transform::SetScale)
        .endClass()
        .beginClass<MaterialAttribs>("MaterialAttribs")
        .addProperty("ambient", &MaterialAttribs::GetMatAmbient, &MaterialAttribs::SetMatAmbient)
        .addProperty("diffuse", &MaterialAttribs::GetMatDiffuse, &MaterialAttribs::SetMatDiffuse)
        .addProperty("specular", &MaterialAttribs::GetMatSpecular, &MaterialAttribs::SetMatSpecular)
        .endClass()
        .beginClass<Material>("Material")
        .addProperty("matAttribs", &Material::GetAttribs)
        .endClass()
        .beginClass<Component>("Component")
        .addProperty("tag", &Component::GetTagCstr)
        .endClass()
        .deriveClass<MeshRenderer, Component>("MeshRenderer")
        .addProperty("material", &MeshRenderer::GetMaterial)
        .endClass()
        .beginClass<GameObject>("GameObject")
        .addConstructor<void(*)(const char*)>()
        .addProperty("tag", &GameObject::GetTag)
        .addProperty("transform", &GameObject::GetTransform)
        .addProperty("meshRenderer", &GameObject::GetComponent<MeshRenderer>)
        .endClass();
        
        ClearLuaStack();
        
        if ( luaL_loadfile(m_State, scriptName) || lua_pcall(m_State, 0, 0, 0))
        {
            std::cout<<"[INFO]: script '"<<scriptName<<"' load failed."<<std::endl;
        }
        
        m_GetTableKeys(m_ComponentTag);
        
        std::cout<<"[SCRIPT]: ";
        for (auto key: m_TableKeys)
        {
            std::cout<<key<<" ";
        }
        std::cout<<std::endl;
        
        m_LoadUpdateFunction();
    }
    else
    {
        getGlobalNamespace(m_State)
            .beginClass<ml::Vector3f>("vec3")
            .addConstructor<void(*)(const float&, const float&, const float&)>()
            .addData("x", &ml::Vector3f::x)
            .addData("y", &ml::Vector3f::y)
            .addData("z", &ml::Vector3f::z)
        .endClass();
        ClearLuaStack();
        
        if ( luaL_loadfile(m_State, scriptName) || lua_pcall(m_State, 0, 0, 0))
        {
            std::cout<<"[INFO]: script '"<<scriptName<<"' load failed."<<std::endl;
        }
    }
    
}


void LuaScript::m_InitClassDef()
{
//    std::vector<rttr::Attribute> m_Attrs;
//    for (auto key: m_TableKeys)
//    {
//        
//        m_Attrs.push_back(rttr::Attribute( , key));
//    }
//    m_ClassDef = new rttr::ClassDef(nullptr, m_ComponentTag, m_Attrs.begin(), m_Attrs.end());
}


void LuaScript::PrintError(const char* varName, const char* errMsg)
{
    std::cout<<"[ERROR]: Lua variable '"<<varName<<"', error: "<<errMsg<<std::endl;
}

template<>
float LuaScript::LuaGet<float>(const char* varName)
{
    if (!lua_isnumber(m_State, -1))
    {
        PrintError(varName, "Not a number.");
    }
    
    return (float)lua_tonumber(m_State, -1);
}

template<>
int LuaScript::LuaGet<int>(const char* varName)
{
    if (!lua_isnumber(m_State, -1))
    {
        PrintError(varName, "Not a number.");
    }
    
    return (int)lua_tonumber(m_State, -1);
}

template<>
unsigned int LuaScript::LuaGet<unsigned int>(const char* varName)
{
    if (!lua_isnumber(m_State, -1))
    {
        PrintError(varName, "Not a number.");
    }
    
    return (unsigned int)lua_tonumber(m_State, -1);
}



template<>
bool LuaScript::LuaGet<bool>(const char* varName)
{
    if (!lua_isboolean(m_State, -1))
    {
        PrintError(varName, "Not a boolean.");
    }
    
    return (bool)lua_toboolean(m_State, -1);
}

template<>
std::string LuaScript::LuaGet<std::string>(const char* varName)
{
    if (!lua_isstring(m_State, -1))
    {
        PrintError(varName, "Not a string.");
    }
    return std::string(lua_tostring(m_State, -1));
}


template<>
float LuaScript::LuaGetDefault<float>(const char* varName)
{
    return -1.0f;
}

template<>
int LuaScript::LuaGetDefault<int>(const char* varName)
{
    return -1;
}

template<>
bool LuaScript::LuaGetDefault<bool>(const char* varName)
{
    return false;
}

template<>
std::string LuaScript::LuaGetDefault<std::string>(const char* varName)
{
    return "";
}


bool LuaScript::LuaPushStack(const char *varName)
{
    std::string varNameStr(varName);
    std::string var = "";
    for (int i=0; i<varNameStr.length(); i++)
    {
        if (varNameStr[i] != '.')
        {
            var += varName[i];
        }
        else
        {
            if (m_StkLevel == 0)
            {
                lua_getglobal(m_State, var.c_str());
            }
            else
            {
                lua_getfield(m_State, -1, var.c_str());
            }
            
            if (lua_isnil(m_State, -1))
            {
                PrintError(var.c_str(), "variable doesn't exist.");
                return false;
            }
            else
            {
                var = "";
                m_StkLevel++;
            }
        }
    }
    
    // last segment of variable name.
    if ( m_StkLevel == 0)
    {
        lua_getglobal(m_State, var.c_str());
    }
    else
    {
        lua_getfield(m_State, -1, var.c_str());
    }
    
    if (lua_isnil(m_State, -1))
    {
        PrintError(varName, "variable doesn't exist.");
        return false;
    }

    return true;
}

void LuaScript::ClearLuaStack()
{
    int n = lua_gettop(m_State);
    m_StkLevel = 0;
    lua_pop(m_State, n);
}

void LuaScript::m_GetTableKeys(const char* tableName)
{
    std::string code =
        "function getKeys(name) "
            "s = \"\""
            "for k, v in pairs(_G[name][\"public\"]) do "
            "    s = s..k..\",\" "
            "    end "
            "return s "
        "end";
    
    luaL_loadstring(m_State, code.c_str());
    lua_pcall(m_State, 0, 0, 0);
    lua_getglobal(m_State, "getKeys");
    lua_pushstring(m_State, tableName);
    lua_pcall(m_State, 1, 1, 0);
    std::string keyStr = std::string((const char*)lua_tostring(m_State, -1));
    
    int i=0;
    std::string aKey;
    while (i<keyStr.length())
    {
        if (keyStr[i]!=',')
        {
            aKey += keyStr[i];
        }
        else
        {
            char* key = new char[aKey.length()+1];
            strcpy(key, aKey.c_str());
            m_TableKeys.push_back(key);
            aKey = "";
        }
        i++;
    }
}

int LuaScript::LuaExecFunc2i1i(const char* funcName, int i1, int i2)
{
    if (!LuaPushStack(funcName))
    {
        PrintError(funcName, "function doesn't exist.");
        return -1;
    }
    lua_pushnumber(m_State, i1);
    lua_pushnumber(m_State, i2);
    
    lua_pcall(m_State, 2, 1, 0);
    
    int res = (int)lua_tonumber(m_State, -1);
    ClearLuaStack();
    
    return res;
}

void LuaScript::OnBind(GameObject* gameObject)
{
    
}

void LuaScript::Update()
{
    if (m_UpdateFunc)
    {
        try
        {
            (*m_UpdateFunc)(GetGameObject());

//            ml::Vector3f rotvel = LuaBridgeGet<ml::Vector3f>("SpinningCube.public.rotationVel");
//            std::cout<<rotvel.x<<" "<<rotvel.y<<" "<<rotvel.z<<std::endl;
        }
        catch (luabridge::LuaException const & e)
        {
            std::cout<<"[ERROR]: Lua Exception - "<<e.what()<<std::endl;
        }
    }
}

void LuaScript::m_LoadUpdateFunction()
{
    LuaRef publicScope = getGlobal(m_State, m_ComponentTag)["public"];
    LuaRef updateFunc = publicScope["Update"];
    if (updateFunc)
    {
        m_UpdateFunc = std::make_unique<LuaRef>(updateFunc);
    }
}

//void LuaScript::Start()
//{
//
//}


LuaScript::~LuaScript()
{
    for (int i=0; i<m_TableKeys.size(); i++)
    {
        if (m_TableKeys[i] != nullptr)
            delete m_TableKeys[i];
    }
    m_StartFunc.reset(nullptr);
    m_UpdateFunc.reset(nullptr);
    
    if (m_State)
        lua_close(m_State);
}
