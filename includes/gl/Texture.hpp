//
//  Texture.hpp
//  bird
//
//  Created by 汪依尘 on 6/12/18.
//  Copyright © 2018 eason. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include <unordered_map>
#include <utility>
#include <vector>

#define TEXTYPE_NONE        0x0

#define TEXTYPE_DIFFUSE     0x1
#define TEXTYPE_SPECULAR    0x2
#define TEXTYPE_AMBIENT     0x3
#define TEXTYPE_EMISSIVE    0x4
#define TEXTYPE_HEIGHT      0x5
#define TEXTYPE_NORMALS     0x6
#define TEXTYPE_SHINESS     0x7
#define TEXTYPE_OPACITY     0x8

//
//enum aiTextureType
//{
//    /** Dummy value.
//     *
//     *  No texture, but the value to be used as 'texture semantic'
//     *  (#aiMaterialProperty::mSemantic) for all material properties
//     *  *not* related to textures.
//     */
//    aiTextureType_NONE = 0x0,
//
//
//
//    /** The texture is combined with the result of the diffuse
//     *  lighting equation.
//     */
//    aiTextureType_DIFFUSE = 0x1,
//
//    /** The texture is combined with the result of the specular
//     *  lighting equation.
//     */
//    aiTextureType_SPECULAR = 0x2,
//
//    /** The texture is combined with the result of the ambient
//     *  lighting equation.
//     */
//    aiTextureType_AMBIENT = 0x3,
//
//    /** The texture is added to the result of the lighting
//     *  calculation. It isn't influenced by incoming light.
//     */
//    aiTextureType_EMISSIVE = 0x4,
//
//    /** The texture is a height map.
//     *
//     *  By convention, higher gray-scale values stand for
//     *  higher elevations from the base height.
//     */
//    aiTextureType_HEIGHT = 0x5,
//
//    /** The texture is a (tangent space) normal-map.
//     *
//     *  Again, there are several conventions for tangent-space
//     *  normal maps. Assimp does (intentionally) not
//     *  distinguish here.
//     */
//    aiTextureType_NORMALS = 0x6,
//
//    /** The texture defines the glossiness of the material.
//     *
//     *  The glossiness is in fact the exponent of the specular
//     *  (phong) lighting equation. Usually there is a conversion
//     *  function defined to map the linear color values in the
//     *  texture to a suitable exponent. Have fun.
//     */
//    aiTextureType_SHININESS = 0x7,
//
//    /** The texture defines per-pixel opacity.
//     *
//     *  Usually 'white' means opaque and 'black' means
//     *  'transparency'. Or quite the opposite. Have fun.
//     */
//    aiTextureType_OPACITY = 0x8,
//
//    /** Displacement texture
//     *
//     *  The exact purpose and format is application-dependent.
//     *  Higher color values stand for higher vertex displacements.
//     */
//    aiTextureType_DISPLACEMENT = 0x9,
//
//    /** Lightmap texture (aka Ambient Occlusion)
//     *
//     *  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
//     *  covered by this material property. The texture contains a
//     *  scaling value for the final color value of a pixel. Its
//     *  intensity is not affected by incoming light.
//     */
//    aiTextureType_LIGHTMAP = 0xA,
//
//    /** Reflection texture
//     *
//     * Contains the color of a perfect mirror reflection.
//     * Rarely used, almost never for real-time applications.
//     */
//    aiTextureType_REFLECTION = 0xB,
//
//    /** Unknown texture
//     *
//     *  A texture reference that does not match any of the definitions
//     *  above is considered to be 'unknown'. It is still imported,
//     *  but is excluded from any further postprocessing.
//     */
//    aiTextureType_UNKNOWN = 0xC,
//
//
//#ifndef SWIG
//    _aiTextureType_Force32Bit = INT_MAX
//#endif
//};
namespace rl {
    class Texture
    {
    public:
        static std::string TypeNames[9];
        
    public:
        static Texture* GetTexture(const char* filePath, unsigned char type = TEXTYPE_NONE);
        Texture();
        Texture(const char* filePath, unsigned char type = TEXTYPE_NONE);

        virtual ~Texture();
        virtual void Bind(unsigned int slot=0) const;
        virtual void Unbind() const;
        void LoadTexture(const char* filePath);
        
    public:
        inline const char* GetFilePath() const { return m_FilePath; }
        inline unsigned char GetType() const { return m_Type; }
        
    private:
        unsigned int m_RendererID;
        const char* m_FilePath;
        unsigned char m_Type;
    };
    
}
#endif /* Texture_hpp */
