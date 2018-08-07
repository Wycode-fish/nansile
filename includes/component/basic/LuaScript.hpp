//
//  LuaScript.hpp
//  bird
//
//  Created by 汪依尘 on 7/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef LuaScript_hpp
#define LuaScript_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <LuaBridge.h>
#include <memory>
#include "Component.hpp"
#include "ClassDef.hpp"

class GameObject;

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#define RESOURCE_SCRIPT 0x00
#define BEHAVIOR_SCRIPT 0x01

using namespace luabridge;

class LuaScript: public Component
{
public:
    static LuaScript* GetLuaScript(const char* scriptName, const char* componentName);
    
public:
    LuaScript(GameObject* gameObject, const char* scriptName, const char* componentName, const unsigned char& type = BEHAVIOR_SCRIPT);
    
    ~LuaScript();
public:
    void PrintError(const char* varName, const char* errMsg);
public:
    template<typename T>
    T Get(const char* varName)
    {
        if (m_State == NULL)
        {
            PrintError(varName, "Script hasn't been loaded.");
            return LuaGetDefault<T>(varName);
        }
        
        T res;
        if (!LuaPushStack(varName))      // failed to put var on stack.
        {
            PrintError(varName, "variable doesn't exist.");
            res = LuaGetDefault<T>(varName);
        }
        else
        {
            res = LuaGet<T>(varName);
        }
        
        ClearLuaStack();
        return res;
    }
    
    template<typename T>
    std::vector<T> GetVector(const char* varName)
    {
        if (!LuaPushStack(varName))
        {
            return std::vector<T>();
        }
        std::vector<T> res;
        lua_pushnil(m_State);
        while (lua_next(m_State, -2)) {
            res.push_back(LuaGet<T>(varName));
            lua_pop(m_State, 1);
        }
        
        ClearLuaStack();
        return res;
    }
    
    template<typename T>
    T LuaGet(const char* varName)
    {
        if (!lua_isuserdata(m_State, -1))
        {
            PrintError(varName, "Not a userdata.");
            std::cout<<lua_typename(m_State, lua_type(m_State, -1))<<std::endl;
        }
        
        T* res = (T*)lua_touserdata(m_State, -1);
        return *res;
    }
    
    
    
    template<typename T>
    T LuaBridgeGet(const char* varName)
    {
        std::string var = "";
        std::string varNameStr = std::string(varName);
        std::vector<const char*> parser;
        for (int i=0; i<varNameStr.length(); i++)
        {
            if (varNameStr[i] != '.')
            {
                var += varNameStr[i];
            }
            else
            {
                char* varC = new char[var.length()+1];
                strcpy(varC, var.c_str());
                parser.push_back(varC);
                var = "";
            }
        }
        char* varC = new char[var.length()+1];
        strcpy(varC, var.c_str());
        parser.push_back(varC);
        
        LuaRef curr = getGlobal(m_State, parser[0]);
        for (int i=1; i<parser.size()-1; i++)
        {
            LuaRef temp = curr[parser[i]];
            curr = temp;
        }

        T res = curr[parser[parser.size()-1]].cast<T>();
        
        for (int i=0; i<parser.size(); i++)
        {
            if (parser[i]!=NULL)
                delete parser[i];
        }
        return res;
    }
    
    template<typename T>
    T LuaGetDefault(const char* varName)
    { return T(); }
    
public:
    int LuaExecFunc2i1i(const char* funcName, int i1, int i2);
    
public:
    bool LuaPushStack(const char* varName);
    void ClearLuaStack();
    
public:
    inline const char* GetFilePath() { return m_FilePath; }
    inline const lua_State* GetState() { return m_State; }
    inline std::vector<const char*> GetTableKeys() const { return m_TableKeys; }
    inline const char* GetComponentTag() const { return m_ComponentTag;}
    
public:
    void OnBind(GameObject* gameObject);
//    void Start();
    void Update();
    void m_LoadUpdateFunction();
    void m_GetTableKeys(const char* tableName);
    void m_InitClassDef();
    
private:
    lua_State* m_State;
    int m_StkLevel;
    const char* m_FilePath;
    const char* m_ComponentTag;
    unsigned char m_Type;
    
private:
    std::unique_ptr<LuaRef> m_UpdateFunc;
    std::unique_ptr<LuaRef> m_StartFunc;

private:
    std::vector<const char*> m_TableKeys;
    rttr::ClassDef* m_ClassDef;
};
#endif /* LuaScript_hpp */
