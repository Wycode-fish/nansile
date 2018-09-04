//
//  Mesh.hpp
//  bird
//
//  Created by 汪依尘 on 6/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace rl {
    
    class Renderer;
    class Texture;
    class Shader;
    class Material;
    
    /** Mesh Configure **/
    struct MeshElement
    {
        unsigned int m_Type;
        unsigned int m_VtxCnt;
        unsigned int m_ElemPerVer;
        unsigned int m_Tag;
        unsigned char m_Normalized;
        enum TAG
        {
            VBO, IBO
        };
        void* m_Data;
    };

    struct MeshElement_Group
    {
        static std::unordered_map<const char*, MeshElement_Group*> MeshElement_Group_Prefabs;
        
        void*               m_VboData;
        unsigned int        m_VboSize;
        VertexBufferLayout  m_VboLayout;
        
        void*               m_IboData;
        unsigned int        m_IboCnt;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<VertexBuffer*> vbos, IndexBuffer* ibo);
        
        Mesh(const void* data,
             unsigned int size,
             VertexBufferLayout layout,
             const unsigned* indicies,
             unsigned int idxCnt,
             std::vector<const Texture*> textures);
        
        Mesh(const void* data,
             unsigned int size,
             VertexBufferLayout layout,
             const unsigned* indicies,
             unsigned int idxCnt);
        
        ~Mesh();
        
    public:
        void Use();
        void SetTextureAtPos(unsigned pos, const rl::Texture* texture);
        
    public:
        inline unsigned int GetCount() { return m_Ibo->GetCount(); }
        inline std::vector<const Texture*> GetTextures() const { return m_Textures; }
    private:
        VertexArray m_Vao;
        std::vector<VertexBuffer*> m_Vbos;
        
        VertexBuffer* m_Vbo;
        VertexBufferLayout m_Vbo_Layout;
        
        IndexBuffer* m_Ibo;
        
        std::vector<const Texture*> m_Textures;
    };
    
    
//    struct AssimpMeshData
//    {
//        Mesh* m_Mesh;
//        std::vector<const Texture*> m_Textures;
//    };
    
    class Model
    {
    public:
        Model( const char* modelFilePath);
        ~Model();
    public:
        inline std::vector<Mesh*>           GetMeshes() const { return m_Meshes; }
        inline const char*                  GetFilePath() const { return m_ModelFilePath; }
        
    public:
        inline void AddMesh (Mesh* mesh) { m_Meshes.push_back(mesh); }
        void Draw( Renderer* renderer, Material* mat) const;
        void DrawOutline (Renderer* render);
        void DrawInstances (Renderer* renderer, Material* mat, unsigned instanceNum) const;
    private:
        void                            LoadAssimpRes( const char* modelFilePath );
        void                            LoadLuaRes( const char* modelFilePath );
        void                            ProcessNode(aiNode* root, const aiScene* scene);
        rl::Mesh*                       ProcessMeshes(aiMesh* mesh, const aiScene* scene);
        std::vector<const Texture*>     ProcessTextures( aiMaterial*& material );
        std::vector<float>              AssimpGetVbo( aiMesh*& mesh);
        std::vector<unsigned>           AssimpGetIbo( aiMesh*& mesh);
        std::vector<const Texture*>     AssimpGetTextures(aiMaterial*& material, aiTextureType type);
        void                            RenderPrepare(Material* mat) const;
        
    private:
        std::unordered_map<const char*, const Texture*>     m_LoadedTextures;
        
    private:
        std::vector<Mesh*>              m_Meshes;
        const char*                     m_ModelFilePath;
        const char*                     m_DirectoryPath;
    };
}
#endif /* Model_hpp */
