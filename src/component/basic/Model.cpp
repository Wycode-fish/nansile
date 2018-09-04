//
//  Model.cpp
//  bird
//
//  Created by 汪依尘 on 6/17/18.
//  Copyright © 2018 eason. All rights reserved.
//

#include "Model.hpp"
#include "DisplaySys.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "TextEditor.hpp"
#include "Material.hpp"
#include "CubeMap.hpp"
#include "LuaScript.hpp"

namespace rl {
    
    std::unordered_map<const char*, MeshElement_Group*> MeshElement_Group::MeshElement_Group_Prefabs = std::unordered_map<const char*, MeshElement_Group*>();

    Mesh::Mesh(const std::vector<VertexBuffer*> vbos, IndexBuffer* ibo)
    : m_Vbos(vbos), m_Vbo(NULL), m_Ibo(ibo)
    {}
    
    Mesh::Mesh( const void* data, unsigned int size, VertexBufferLayout layout, const unsigned* indicies, unsigned int idxCnt, std::vector<const Texture*> textures )
    : m_Vbo(new VertexBuffer(data, size)), m_Vbo_Layout(layout), m_Ibo(new IndexBuffer(indicies, idxCnt)), m_Textures(textures)
    {}

    Mesh::Mesh( const void* data, unsigned int size, VertexBufferLayout layout, const unsigned* indicies, unsigned int idxCnt)
    : m_Vbo(new VertexBuffer(data, size)), m_Vbo_Layout(layout), m_Ibo(new IndexBuffer(indicies, idxCnt)), m_Textures()
    {}
    
    Mesh::~Mesh()
    {
        // TODO: nothing yet.
        for (int i=0; i<m_Vbos.size(); i++)
        {
            if (m_Vbos[i]!=NULL)
                delete m_Vbos[i];
        }
        delete m_Ibo;
    }

    void Mesh::Use()
    {
        if(m_Vbo==NULL)
        {
            m_Vao.Bind(m_Vbos);
            //    m_Vao.Bind(m_Vbos[0], m_Vbos[1]);
            m_Ibo->Bind();
            return;
        }
        else
        {
            m_Vao.Bind(*m_Vbo, m_Vbo_Layout);
            m_Ibo->Bind();
        }
    }
    
    void Mesh::SetTextureAtPos(unsigned pos, const rl::Texture* texture)
    {
        if (m_Textures.size() == 0)
            m_Textures.push_back(texture);
        else
            m_Textures[0] = texture;
    }

    
    Model::Model( const char* modelFilePath)
    : m_Meshes(), m_ModelFilePath(modelFilePath), m_DirectoryPath(TextEditor::Str2ValuePtr(TextEditor::GetDirectoryFromPath(modelFilePath)))
    {
        std::string suffix = TextEditor::GetFileSuffix( modelFilePath );
        if (suffix == "lua")
            LoadLuaRes(modelFilePath);
        else
            LoadAssimpRes(m_ModelFilePath);
    }
    
    
    Model::~Model()
    {
        if (m_DirectoryPath != nullptr)
            delete m_DirectoryPath;
        for (auto mesh: m_Meshes)
        {
            if (mesh)
            {
                delete mesh;
            }
        }
        
        for (auto pair: m_LoadedTextures)
        {
            if (pair.second != nullptr)
            {
                delete pair.second;
            }
        }
    }
    
    void Model::LoadLuaRes(const char *modelFilePath)
    {
        LuaScript* script = LuaScript::GetLuaScript(modelFilePath, "Mesh");
        if (script == nullptr)
        {
            std::cout<<"[ERROR]: '"<<modelFilePath<<"' Lua Script Load Failed. "<<std::endl;
            return;
        }
        std::string meshesTableName = "MeshRenderer.Model.Meshes";
        std::vector<std::string> meshTags = script->GetTableKeys( meshesTableName.c_str() );
        for (auto tag : meshTags)
        {
            // ---------- Textures ----------
            std::string meshName = meshesTableName + "." + tag;
            std::vector<std::string> texturePaths = script->GetVector<std::string>((meshName + ".texture.texture_paths").c_str());
            std::vector<const Texture*> textures;
            if (script->Get<std::string>((meshName + ".texture.texture_type").c_str()) == "CubeMap")
            {
                textures.push_back(rl::CubeMap::GetCubeMap(texturePaths));
            }
            else if (script->Get<std::string>((meshName + ".texture.texture_type").c_str()) == "Default")
            {
                for (auto texName: texturePaths)
                {
                    textures.push_back(new Texture(texName.c_str()));
                }
            }
            
            // ---------- Model ----------
            unsigned int vertexCntPerSide = script->Get<unsigned int>((meshName + ".model.vertex_count_per_surface").c_str());
            
            unsigned int surfaceCnt = script->Get<unsigned int>((meshName + ".model.surface_count").c_str());
            
            unsigned int attrFloatPerVtx = script->Get<unsigned int>((meshName + ".model.attr_float_per_vertex").c_str());
            
            unsigned int idxPerSurface = script->Get<unsigned int>((meshName + ".model.idx_per_surface").c_str());
            
            std::vector<unsigned int> floatPerData = script->GetVector<unsigned int>((meshName + ".model.layout_elements").c_str());
            
            rl::VertexBufferLayout layout;
            for (int i=0; i<floatPerData.size(); i++)
            {
                layout.Add<float>(floatPerData[i], GL_FALSE);
            }
            
            unsigned int vtxPosSize = surfaceCnt * vertexCntPerSide * attrFloatPerVtx * sizeof(float);
            unsigned int vtxIdxCnt = surfaceCnt * idxPerSurface;
            
            std::vector<float> vp = script->GetVector<float>((meshName + ".model.vertex_position").c_str());

            std::vector<unsigned> idxs = script->GetVector<unsigned int>((meshName + ".model.vertex_indicies").c_str());

            m_Meshes.push_back(new Mesh( vp.data(), vtxPosSize, layout, idxs.data(), vtxIdxCnt, textures ));

        }
        
    }
    
    void Model::LoadAssimpRes( const char* modelFilePath )
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(modelFilePath,  aiProcess_Triangulate | aiProcess_OptimizeMeshes);
        
        if ( !scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
        {
            std::cout<<"[ERROR]: assimp import failed. "<<importer.GetErrorString()<<std::endl;
        }
        
        ProcessNode(scene->mRootNode, scene);
    }
    
    void Model::ProcessNode(aiNode *root, const aiScene *scene)
    {
        for (unsigned i=0; i<root->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[root->mMeshes[i]];
            AddMesh(ProcessMeshes( mesh, scene));
        }
        for (unsigned i=0; i<root->mNumChildren; i++)
        {
            ProcessNode(root->mChildren[i], scene);
        }
    }
    
    rl::Mesh* Model::ProcessMeshes(aiMesh* mesh, const aiScene* scene)
    {
        ////////// VBO Preparation //////////
        std::vector<float> vboData = AssimpGetVbo(mesh);
        
        ////////// VboLayout Preparation //////////
        VertexBufferLayout layout;
        layout.Add<float>(3, GL_FALSE);         // position
        layout.Add<float>(2, GL_FALSE);         // texCoords
        layout.Add<float>(3, GL_FALSE);         // normal
        
        ////////// IBO Preparation //////////
        std::vector<unsigned> iboData = AssimpGetIbo(mesh);
        
        ////////// Textures Preparation //////////
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<const Texture*> textures = ProcessTextures(material);
        
        return new rl::Mesh(vboData.data(),
                            static_cast<unsigned>(vboData.size()) * sizeof(float),
                            layout,
                            iboData.data(),
                            static_cast<unsigned>(iboData.size()),
                            textures);
    }
    
    std::vector<const Texture*> Model::ProcessTextures( aiMaterial*& material )
    {
        std::vector<const Texture*> res;
        std::vector<const Texture*> diffuse = AssimpGetTextures(material, aiTextureType_DIFFUSE);
        std::vector<const Texture*> specular = AssimpGetTextures(material, aiTextureType_SPECULAR);
        std::vector<const Texture*> ambient = AssimpGetTextures(material, aiTextureType_AMBIENT);
        std::vector<const Texture*> normals = AssimpGetTextures(material, aiTextureType_NORMALS);
        std::vector<const Texture*> heights = AssimpGetTextures(material, aiTextureType_HEIGHT);
        if (!diffuse.empty())
            res.insert(res.end(), diffuse.begin(), diffuse.end());
        if (!specular.empty())
            res.insert(res.end(), specular.begin(), specular.end());
        if (!ambient.empty())
            res.insert(res.end(), ambient.begin(), ambient.end());
        if (!normals.empty())
            res.insert(res.end(), normals.begin(), normals.end());
        if (!heights.empty())
            res.insert(res.end(), heights.begin(), heights.end());
        
        return res;
    }
    
    std::vector<const Texture*> Model::AssimpGetTextures(aiMaterial*& material, aiTextureType type)
    {
        std::vector<const Texture*> textures;
        for (unsigned i=0; i<material->GetTextureCount(type); i++)
        {
            aiString str;
            material->GetTexture(type, i, &str);
            
            if (m_LoadedTextures.find(str.C_Str()) != m_LoadedTextures.end())
            {
                textures.push_back(m_LoadedTextures[str.C_Str()]);
            }
            else
            {
                std::string path = std::string(m_DirectoryPath) + "/" + std::string(str.C_Str());
                Texture* texture = new Texture( TextEditor::Str2ValuePtr(path), type);
                textures.push_back(texture);
                m_LoadedTextures.insert(std::make_pair(TextEditor::Str2ValuePtr(std::string(str.C_Str())), texture));
            }
        }
        
        return textures;
    }
    
    
    std::vector<unsigned> Model::AssimpGetIbo(aiMesh*& mesh)
    {
        std::vector<unsigned> iboData;
        for (unsigned i=0; i<mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned j=0; j<face.mNumIndices; j++)
            {
                iboData.push_back(face.mIndices[j]);
            }
        }
        return iboData;
    }
    
    
    std::vector<float> Model::AssimpGetVbo(aiMesh*& mesh)
    {
        std::vector<float> vboData;
        for (unsigned i=0; i<mesh->mNumVertices; i++)
        {
            // --------- vpos ---------
            vboData.push_back(mesh->mVertices[i].x);
            vboData.push_back(mesh->mVertices[i].y);
            vboData.push_back(mesh->mVertices[i].z);
            
            // --------- texture coords ---------
            if (mesh->mTextureCoords[0])
            {
                vboData.push_back(mesh->mTextureCoords[0][i].x);
                vboData.push_back(mesh->mTextureCoords[0][i].y);
            }
            else
            {
                vboData.push_back(0.0f);
                vboData.push_back(0.0f);
            }
            
            // --------- normals ---------
            vboData.push_back(mesh->mNormals[i].x);
            vboData.push_back(mesh->mNormals[i].y);
            vboData.push_back(mesh->mNormals[i].z);
            
            //            // --------- tangents ---------
            //            vboData.push_back(mesh->mTangents[i].x);
            //            vboData.push_back(mesh->mTangents[i].y);
            //            vboData.push_back(mesh->mTangents[i].z);
            //
            //            // --------- bitTangents ---------
            //            vboData.push_back(mesh->mBitangents[i].x);
            //            vboData.push_back(mesh->mBitangents[i].y);
            //            vboData.push_back(mesh->mBitangents[i].z);
        }
        
        return vboData;
    }
    
    void Model::RenderPrepare(Material* mat) const
    {
        rl::Shader* shaderPtr = mat->GetShader();
        shaderPtr->Use();

        rl::MaterialAttribs* attribs = mat->GetAttribs();
        ml::Vector3f mat_ambient = attribs->m_Ambient;
        ml::Vector3f mat_diffuse = attribs->m_Diffuse;
        ml::Vector3f mat_specular = attribs->m_Specular;
        float mat_shiness = attribs->m_Shiness;
        float transparency = attribs->m_Transparency;
        
        if (shaderPtr->SetUniform3f("u_Material.ambient",  mat_ambient.x, mat_ambient.y, mat_ambient.z))
        {
            shaderPtr->SetUniform3f("u_Material.diffuse",  mat_diffuse.x, mat_diffuse.y, mat_diffuse.z);
            shaderPtr->SetUniform3f("u_Material.specular", mat_specular.x, mat_specular.y, mat_specular.z);
            shaderPtr->SetUniform1f("u_Material.shiness", mat_shiness);
            shaderPtr->SetUniform1f("u_Material.transparency", transparency);
        }
        
    }
    
    void Model::Draw( rl::Renderer* renderer, Material* mat) const
    {
        RenderPrepare(mat);

        for (auto mesh: m_Meshes)
        {
            Shader* shader = mat->GetShader();
//            shader->Use();
            if (mesh->GetTextures().size() > 0)
            {
                shader->SetUniform1i("u_TextureExist", 1);

                unsigned texNum = 0;
                int typeCnts[20]{};
                int currTypeCnt;
                for (auto texture: mesh->GetTextures())
                {
                    texture->Bind( texNum );
                    currTypeCnt = ++typeCnts[texture->GetType()];
                    std::string samplerName = "u_Texture" + Texture::TypeNames[texture->GetType()] + std::to_string(currTypeCnt);   // e.g "u_TextureDiffuse2"
                    shader->SetUniform1i(samplerName.c_str(), texNum++);
                }
            }
            mesh->Use();
            if (renderer->GetDrawMode() == DRAW_MODE_LINES)
                renderer->DrawLines(*mesh);
            else
                renderer->Draw(*mesh);
        }
    }
    
    void Model::DrawOutline (Renderer* renderer)
    {
        for (auto mesh: m_Meshes)
        {
            Shader::PlainShader->Use();
            mesh->Use();
            if (renderer->GetDrawMode() == DRAW_MODE_LINES)
                renderer->DrawLines(*mesh);
            else
                renderer->Draw(*mesh);
        }
    }

    void Model::DrawInstances( rl::Renderer* renderer, Material* mat, unsigned instanceNum) const
    {
        RenderPrepare(mat);
        
        for (auto mesh: m_Meshes)
        {
            Shader* shader = mat->GetShader();
            //            shader->Use();
            if (mesh->GetTextures().size() > 0)
            {
                shader->SetUniform1i("u_TextureExist", 1);
                
                unsigned texNum = 0;
                int typeCnts[20]{};
                int currTypeCnt;
                for (auto texture: mesh->GetTextures())
                {
                    texture->Bind( texNum );
                    currTypeCnt = ++typeCnts[texture->GetType()];
                    std::string samplerName = "u_Texture" + Texture::TypeNames[texture->GetType()] + std::to_string(currTypeCnt);   // e.g "u_TextureDiffuse2"
                    shader->SetUniform1i(samplerName.c_str(), texNum++);
                }
            }
            mesh->Use();
//            if (renderer->GetDrawMode() == DRAW_MODE_LINES)
//                renderer->DrawInstances(*mesh, instanceNum, DRAW_MODE_LINES);
//            else
            renderer->DrawInstances(*mesh, instanceNum);
        }
    }
    
}
