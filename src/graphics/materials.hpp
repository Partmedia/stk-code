//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2015 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef HEADER_MATERIAL_TYPE_HPP
#define HEADER_MATERIAL_TYPE_HPP

#ifndef SERVER_ONLY

#include "graphics/shader.hpp"
#include "graphics/shaders.hpp"
#include "graphics/stk_mesh.hpp"
#include "graphics/vao_manager.hpp"


// ============================================================================
class InstancedObjectPass1Shader : public TextureShader<InstancedObjectPass1Shader, 1>
{
public:
    InstancedObjectPass1Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_object_pass.vert",
                            GL_FRAGMENT_SHADER, "instanced_object_pass1.frag");

        assignUniforms();
        assignSamplerNames(0, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedObjectPass1Shader
};   // class InstancedObjectPass1Shader

// ============================================================================
class InstancedObjectRefPass1Shader : public TextureShader<InstancedObjectRefPass1Shader, 2>
{
public:
    InstancedObjectRefPass1Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_object_pass.vert",
                            GL_FRAGMENT_SHADER, "instanced_objectref_pass1.frag");

        assignUniforms();
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }

};   // InstancedObjectRefPass1Shader

// ============================================================================
class ObjectRefPass2Shader : public TextureShader<ObjectRefPass2Shader, 6,
                                                core::matrix4, core::vector2df,
                                                core::vector2df>
{
public:
    ObjectRefPass2Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "object_pass.vert",
                            GL_FRAGMENT_SHADER, "objectref_pass2.frag");
        assignUniforms("ModelMatrix", "texture_trans", "color_change");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // ObjectRefPass2Shader
};   // ObjectRefPass2Shader

// ============================================================================
class InstancedObjectPass2Shader : public TextureShader<InstancedObjectPass2Shader, 6>
{
public:
    InstancedObjectPass2Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_object_pass.vert",
                            GL_FRAGMENT_SHADER, "instanced_object_pass2.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedObjectPass2Shader
};   // InstancedObjectPass2Shader

// ============================================================================
class InstancedObjectRefPass2Shader : public TextureShader<InstancedObjectRefPass2Shader, 6>
{
public:
    InstancedObjectRefPass2Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_object_pass.vert",
                            GL_FRAGMENT_SHADER, "instanced_objectref_pass2.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }    // InstancedObjectRefPass2Shader
};   // InstancedObjectRefPass2Shader

// ============================================================================
class ShadowShader : public TextureShader<ShadowShader, 0, core::matrix4, int>
{
public:
    ShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150)
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "shadow.vert",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        else
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "shadow.vert",
                                GL_GEOMETRY_SHADER, "shadow.geom",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        assignUniforms("ModelMatrix", "layer");
#endif
    }   // ShadowShader
};   // ShadowShader

// ============================================================================
class InstancedShadowShader : public TextureShader<InstancedShadowShader, 0, int>
{
public:
    InstancedShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150)
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_shadow.vert",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        else
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_shadow.vert",
                                GL_GEOMETRY_SHADER, "instanced_shadow.geom",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        assignUniforms("layer");
#endif
    }   // InstancedShadowShader

};   // InstancedShadowShader

// ============================================================================
class CRSMShader : public TextureShader<CRSMShader, 1, core::matrix4, core::vector2df,
                                 core::matrix4>
{
public:
    CRSMShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "rsm.vert",
                            GL_FRAGMENT_SHADER, "rsm.frag");

        assignUniforms("ModelMatrix", "texture_trans", "RSMMatrix");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // CRSMShader
};   // CRSMShader


// ============================================================================
class SplattingRSMShader : public TextureShader<SplattingRSMShader, 5, core::matrix4,
                                  core::matrix4>
{
public:
    SplattingRSMShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "rsm.vert",
                            GL_FRAGMENT_SHADER, "splatting_rsm.frag");

        assignUniforms("ModelMatrix", "RSMMatrix");
        assignSamplerNames(0, "tex_layout", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "tex_detail0", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           2, "tex_detail1", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           3, "tex_detail2", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "tex_detail3", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SplattingRSMShader

};  // SplattingRSMShader

// ============================================================================
class CInstancedRSMShader : public TextureShader<CInstancedRSMShader, 1, core::matrix4>
{
public:
    CInstancedRSMShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_rsm.vert",
                            GL_FRAGMENT_SHADER, "instanced_rsm.frag");

        assignUniforms("RSMMatrix");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // CInstancedRSMShader
};   // CInstancedRSMShader

// ============================================================================
class SphereMapShader : public TextureShader<SphereMapShader, 4, core::matrix4,
                                      core::matrix4>
{
public:
    SphereMapShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "object_pass.vert",
                            GL_FRAGMENT_SHADER, "objectpass_spheremap.frag");
        assignUniforms("ModelMatrix", "InverseModelMatrix");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SphereMapShader
};   // SphereMapShader

// ============================================================================
class InstancedSphereMapShader : public TextureShader<InstancedSphereMapShader, 4>
{
public:
    InstancedSphereMapShader()
    {
        loadProgram(OBJECT,
                    GL_VERTEX_SHADER, "instanced_object_pass.vert",
                    GL_FRAGMENT_SHADER, "instanced_objectpass_spheremap.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedSphereMapShader
};   // InstancedSphereMapShader

// ============================================================================
class SplattingShader : public TextureShader<SplattingShader, 8, core::matrix4>
{
public:
    SplattingShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "object_pass.vert",
                            GL_FRAGMENT_SHADER, "splatting.frag");
        assignUniforms("ModelMatrix");

        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "tex_layout", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "tex_detail0", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "tex_detail1", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           6, "tex_detail2", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           7, "tex_detail3", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SplattingShader
};   // SplattingShader

// ============================================================================
class ObjectRefPass1Shader : public TextureShader<ObjectRefPass1Shader, 2, core::matrix4,
                                           core::matrix4, core::vector2df>
{
public:
    ObjectRefPass1Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "object_pass.vert",
                            GL_FRAGMENT_SHADER, "objectref_pass1.frag");
        assignUniforms("ModelMatrix", "InverseModelMatrix", "texture_trans");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // ObjectRefPass1Shader
};  // ObjectRefPass1Shader


// ============================================================================
class NormalMapShader : public TextureShader<NormalMapShader, 2, core::matrix4,
                                      core::matrix4>
{
public:
    NormalMapShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "object_pass.vert",
                            GL_FRAGMENT_SHADER, "normalmap.frag");
        assignUniforms("ModelMatrix", "InverseModelMatrix");
        assignSamplerNames(0, "normalMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glossMap", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // NormalMapShader

};   // NormalMapShader

// ============================================================================
class InstancedNormalMapShader : public TextureShader<InstancedNormalMapShader, 2>
{
public:
    InstancedNormalMapShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_object_pass.vert",
                            GL_FRAGMENT_SHADER, "instanced_normalmap.frag");
        assignUniforms();
        assignSamplerNames(0, "normalMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glossMap", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedNormalMapShader
};   // InstancedNormalMapShader

// ============================================================================
class ObjectUnlitShader : public TextureShader<ObjectUnlitShader, 4, core::matrix4,
                                        core::vector2df>
{
public:
    ObjectUnlitShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "object_pass.vert",
                            GL_FRAGMENT_SHADER, "object_unlit.frag");
        assignUniforms("ModelMatrix", "texture_trans");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // ObjectUnlitShader
};   // ObjectUnlitShader

// ============================================================================
class InstancedObjectUnlitShader : public TextureShader<InstancedObjectUnlitShader, 4>
{
public:
    InstancedObjectUnlitShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_object_pass.vert",
                            GL_FRAGMENT_SHADER, "instanced_object_unlit.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedObjectUnlitShader
};   // InstancedObjectUnlitShader

// ============================================================================
class RefShadowShader : public TextureShader<RefShadowShader, 1,
                                             core::matrix4, int>
{
public:
    RefShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150)
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "shadow.vert",
                                GL_FRAGMENT_SHADER, "shadowref.frag");
        }
        else
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "shadow.vert",
                                GL_GEOMETRY_SHADER, "shadow.geom",
                                GL_FRAGMENT_SHADER, "shadowref.frag");
        }
        assignUniforms("ModelMatrix", "layer");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
#endif
    }   // RefShadowShader
};   // RefShadowShader

// ============================================================================
class InstancedRefShadowShader : public TextureShader<InstancedRefShadowShader,
                                                      1, int>
{
public:
    InstancedRefShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150)
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(OBJECT,GL_VERTEX_SHADER, "instanced_shadow.vert",
                               GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }
        else
        {
            loadProgram(OBJECT,GL_VERTEX_SHADER, "instanced_shadow.vert",
                               GL_GEOMETRY_SHADER, "instanced_shadow.geom",
                               GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }
        assignUniforms("layer");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
#endif
    }   // InstancedRefShadowShader
};   // InstancedRefShadowShader

// ============================================================================
class DisplaceMaskShader : public Shader<DisplaceMaskShader, core::matrix4>
{
public:
    DisplaceMaskShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "displace.vert",
                            GL_FRAGMENT_SHADER, "white.frag");
        assignUniforms("ModelMatrix");
    }   // DisplaceMaskShader
};   // DisplaceMaskShader

// ============================================================================
class DisplaceShader : public TextureShader<DisplaceShader, 4, core::matrix4,
                                          core::vector2df, core::vector2df>
{
public:
    DisplaceShader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "displace.vert",
                            GL_FRAGMENT_SHADER, "displace.frag");
        assignUniforms("ModelMatrix", "dir", "dir2");

        assignSamplerNames(0, "displacement_tex", ST_BILINEAR_FILTERED,
                           1, "color_tex", ST_BILINEAR_FILTERED,
                           2, "mask_tex", ST_BILINEAR_FILTERED,
                           3, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // DisplaceShader
};   // DisplaceShader

// ============================================================================
class NormalVisualizer : public Shader<NormalVisualizer, video::SColor>
{
public:
    NormalVisualizer()
    {
#if !defined(USE_GLES2)
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_object_pass.vert",
                            GL_GEOMETRY_SHADER, "normal_visualizer.geom",
                            GL_FRAGMENT_SHADER, "coloredquad.frag");
        assignUniforms("color");
#endif
    }   // NormalVisualizer
};   // NormalVisualizer

// ============================================================================
class GrassPass1Shader : public TextureShader<GrassPass1Shader, 2, core::matrix4,
                                       core::matrix4, core::vector3df>
{
public:
    GrassPass1Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "grass_pass.vert",
                            GL_FRAGMENT_SHADER, "objectref_pass1.frag");
        assignUniforms("ModelMatrix", "InverseModelMatrix", "windDir");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // GrassPass1Shader

};   // class GrassPass1Shader

// ============================================================================
class InstancedGrassPass1Shader : public TextureShader<InstancedGrassPass1Shader, 2,
                                                core::vector3df>
{
public:
    InstancedGrassPass1Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_grass.vert",
                            GL_FRAGMENT_SHADER, "instanced_objectref_pass1.frag");
        assignUniforms("windDir");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedGrassPass1Shader
};   // InstancedGrassPass1Shader

// ============================================================================
class GrassShadowShader : public TextureShader<GrassShadowShader, 1, core::matrix4,
                                        core::vector3df, int>
{
public:
    GrassShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150)
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "shadow_grass.vert",
                                GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }
        else
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "shadow_grass.vert",
                                GL_GEOMETRY_SHADER, "shadow.geom",
                                GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }
        assignUniforms("ModelMatrix", "windDir", "layer");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
#endif
    }   // GrassShadowShader
};   // GrassShadowShader

// ============================================================================
class InstancedGrassShadowShader : public TextureShader<InstancedGrassShadowShader, 1,
                                                 int, core::vector3df>
{
public:
    InstancedGrassShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150)
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_grassshadow.vert",
                                GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }
        else
        {
            loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_grassshadow.vert",
                                GL_GEOMETRY_SHADER, "instanced_shadow.geom",
                                GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }

        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
        assignUniforms("layer", "windDir");
#endif
    }   // InstancedGrassShadowShader
};   // InstancedGrassShadowShader


// ============================================================================
class GrassPass2Shader : public TextureShader<GrassPass2Shader, 7, core::matrix4,
                                       core::vector3df, core::vector2df>
{
public:
    GrassPass2Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "grass_pass.vert",
                            GL_FRAGMENT_SHADER, "grass_pass2.frag");
        assignUniforms("ModelMatrix", "windDir", "color_change");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "dtex", ST_NEAREST_FILTERED,
                           4, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           6, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // GrassPass2Shader
};   // GrassPass2Shader

// ============================================================================
class InstancedGrassPass2Shader : public TextureShader<InstancedGrassPass2Shader, 7,
                                             core::vector3df>
{
public:
    InstancedGrassPass2Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "instanced_grass.vert",
                            GL_FRAGMENT_SHADER, "instanced_grass_pass2.frag");
        assignUniforms("windDir");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "dtex", ST_NEAREST_FILTERED,
                           4, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           6, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedGrassPass2Shader
};   // InstancedGrassPass2Shader

// ============================================================================
class DetailedObjectPass2Shader : public TextureShader<DetailedObjectPass2Shader, 6,
                                                 core::matrix4>
{
public:
    DetailedObjectPass2Shader()
    {
        loadProgram(OBJECT, GL_VERTEX_SHADER, "object_pass.vert",
                            GL_FRAGMENT_SHADER, "detailed_object_pass2.frag");
        assignUniforms("ModelMatrix");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "Detail", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }  // DetailedObjectPass2Shader
};   // DetailedObjectPass2Shader

// ============================================================================
class InstancedDetailedObjectPass2Shader : public TextureShader<InstancedDetailedObjectPass2Shader, 6>
{
public:
    InstancedDetailedObjectPass2Shader()
    {
        loadProgram(OBJECT,
                   GL_VERTEX_SHADER, "instanced_object_pass.vert",
                   GL_FRAGMENT_SHADER, "instanced_detailed_object_pass2.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "Detail", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedDetailedObjectPass2Shader
};   // InstancedDetailedObjectPass2Shader

// ============================================================================
class SkinnedPass1Shader : public TextureShader<SkinnedPass1Shader, 1,
                                                core::matrix4, core::matrix4,
                                                int>
{
public:
    SkinnedPass1Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning.vert",
                            GL_FRAGMENT_SHADER, "object_pass1.frag");
        assignUniforms("ModelMatrix", "InverseModelMatrix", "skinning_offset");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SkinnedPass1Shader
};   // SkinnedPass1Shader

// ============================================================================
class InstancedSkinnedPass1Shader : public TextureShader<InstancedSkinnedPass1Shader, 1>
{
public:
    InstancedSkinnedPass1Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning.vert",
                            GL_FRAGMENT_SHADER, "instanced_object_pass1.frag");
        assignUniforms();
        assignSamplerNames(0, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedSkinnedPass1Shader
};   // InstancedSkinnedPass1Shader

// ============================================================================
class SkinnedPass2Shader : public TextureShader<SkinnedPass2Shader, 6,
                                                core::matrix4, core::vector2df,
                                                core::vector2df, int >
{
public:
    SkinnedPass2Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning.vert",
                            GL_FRAGMENT_SHADER, "object_pass2.frag");
        assignUniforms("ModelMatrix", "texture_trans", "color_change",
                       "skinning_offset");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SkinnedPass2Shader
};   // SkinnedPass2Shader

// ============================================================================
class InstancedSkinnedPass2Shader : public TextureShader<InstancedSkinnedPass2Shader, 6>
{
public:
    InstancedSkinnedPass2Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning.vert",
                            GL_FRAGMENT_SHADER, "instanced_object_pass2.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedSkinnedPass2Shader
};   // InstancedSkinnedPass2Shader

// ============================================================================
class SkinnedRefPass1Shader : public TextureShader<SkinnedRefPass1Shader, 2,
                                                   core::matrix4,
                                                   core::matrix4,
                                                   core::vector2df, int>
{
public:
    SkinnedRefPass1Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning.vert",
                            GL_FRAGMENT_SHADER, "objectref_pass1.frag");
        assignUniforms("ModelMatrix", "InverseModelMatrix", "texture_trans",
                       "skinning_offset");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SkinnedRefPass1Shader
};  // SkinnedRefPass1Shader

// ============================================================================
class InstancedSkinnedRefPass1Shader : public TextureShader<InstancedSkinnedRefPass1Shader, 2>
{
public:
    InstancedSkinnedRefPass1Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning.vert",
                            GL_FRAGMENT_SHADER, "instanced_objectref_pass1.frag");
        assignUniforms();
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glosstex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }    // InstancedSkinnedRefPass1Shader
};   // InstancedSkinnedRefPass1Shader

// ============================================================================
class SkinnedRefPass2Shader : public TextureShader<SkinnedRefPass2Shader, 6,
                                                   core::matrix4,
                                                   core::vector2df,
                                                   core::vector2df, int>
{
public:
    SkinnedRefPass2Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning.vert",
                            GL_FRAGMENT_SHADER, "objectref_pass2.frag");
        assignUniforms("ModelMatrix", "texture_trans", "color_change",
                       "skinning_offset");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SkinnedRefPass2Shader
};   // SkinnedRefPass2Shader

// ============================================================================
class InstancedSkinnedRefPass2Shader : public TextureShader<InstancedSkinnedRefPass2Shader, 6>
{
public:
    InstancedSkinnedRefPass2Shader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning.vert",
                            GL_FRAGMENT_SHADER, "instanced_objectref_pass2.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "Albedo", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           4, "SpecMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           5, "colorization_mask", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }    // InstancedSkinnedRefPass2Shader
};   // InstancedSkinnedRefPass2Shader

// ============================================================================
class SkinnedUnlitShader : public TextureShader<SkinnedUnlitShader, 4,
                                                core::matrix4, core::vector2df,
                                                int>
{
public:
    SkinnedUnlitShader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning.vert",
                            GL_FRAGMENT_SHADER, "object_unlit.frag");
        assignUniforms("ModelMatrix", "texture_trans", "skinning_offset");
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SkinnedUnlitShader
};   // SkinnedUnlitShader

// ============================================================================
class InstancedSkinnedUnlitShader : public TextureShader<InstancedSkinnedUnlitShader, 4>
{
public:
    InstancedSkinnedUnlitShader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning.vert",
                            GL_FRAGMENT_SHADER, "instanced_object_unlit.frag");
        assignUniforms();
        assignSamplerNames(0, "DiffuseMap", ST_NEAREST_FILTERED,
                           1, "SpecularMap", ST_NEAREST_FILTERED,
                           2, "SSAO", ST_BILINEAR_FILTERED,
                           3, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedSkinnedUnlitShader
};   // InstancedSkinnedUnlitShader

// ============================================================================
class SkinnedNormalMapShader : public TextureShader<SkinnedNormalMapShader, 2,
                                                    core::matrix4,
                                                    core::matrix4, int>
{
public:
    SkinnedNormalMapShader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning.vert",
                            GL_FRAGMENT_SHADER, "normalmap.frag");
        assignUniforms("ModelMatrix", "InverseModelMatrix", "skinning_offset");
        assignSamplerNames(0, "normalMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glossMap", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // SkinnedNormalMapShader
};   // SkinnedNormalMapShader

// ============================================================================
class InstancedSkinnedNormalMapShader : public TextureShader<InstancedSkinnedNormalMapShader, 2>
{
public:
    InstancedSkinnedNormalMapShader()
    {
        if (!CVS->supportsHardwareSkinning()) return;
        loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning.vert",
                            GL_FRAGMENT_SHADER, "instanced_normalmap.frag");
        assignUniforms();
        assignSamplerNames(0, "normalMap", ST_TRILINEAR_ANISOTROPIC_FILTERED,
                           1, "glossMap", ST_TRILINEAR_ANISOTROPIC_FILTERED);
    }   // InstancedSkinnedNormalMapShader
};   // InstancedSkinnedNormalMapShader

// ============================================================================
class SkinnedShadowShader : public TextureShader<SkinnedShadowShader, 0,
                                                 core::matrix4, int, int>
{
public:
    SkinnedShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150 || !CVS->supportsHardwareSkinning())
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning_shadow.vert",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        else
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning_shadow.vert",
                                GL_GEOMETRY_SHADER, "shadow.geom",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        assignUniforms("ModelMatrix", "skinning_offset", "layer");
#endif
    }   // SkinnedShadowShader
};   // SkinnedShadowShader

// ============================================================================
class InstancedSkinnedShadowShader : public TextureShader<InstancedSkinnedShadowShader, 0, int>
{
public:
    InstancedSkinnedShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150 || !CVS->supportsHardwareSkinning())
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning_shadow.vert",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        else
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning_shadow.vert",
                                GL_GEOMETRY_SHADER, "instanced_shadow.geom",
                                GL_FRAGMENT_SHADER, "shadow.frag");
        }
        assignUniforms("layer");
#endif
    }   // InstancedSkinnedShadowShader
};   // InstancedSkinnedShadowShader

// ============================================================================
class SkinnedRefShadowShader : public TextureShader<SkinnedRefShadowShader, 1,
                                                    core::matrix4, int, int>
{
public:
    SkinnedRefShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150 || !CVS->supportsHardwareSkinning())
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning_shadow.vert",
                                GL_FRAGMENT_SHADER, "shadowref.frag");
        }
        else
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "skinning_shadow.vert",
                                GL_GEOMETRY_SHADER, "shadow.geom",
                                GL_FRAGMENT_SHADER, "shadowref.frag");
        }
        assignUniforms("ModelMatrix", "skinning_offset", "layer");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
#endif
    }   // SkinnedRefShadowShader
};   // SkinnedRefShadowShader

// ============================================================================
class InstancedSkinnedRefShadowShader : public TextureShader<InstancedSkinnedRefShadowShader,
                                                          1, int>
{
public:
    InstancedSkinnedRefShadowShader()
    {
#if !defined(USE_GLES2)
        // Geometry shader needed
        if (CVS->getGLSLVersion() < 150 || !CVS->supportsHardwareSkinning())
            return;
        if (CVS->isAMDVertexShaderLayerUsable())
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning_shadow.vert",
                                GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }
        else
        {
            loadProgram(SKINNED_MESH, GL_VERTEX_SHADER, "instanced_skinning_shadow.vert",
                                GL_GEOMETRY_SHADER, "instanced_shadow.geom",
                                GL_FRAGMENT_SHADER, "instanced_shadowref.frag");
        }
        assignUniforms("layer");
        assignSamplerNames(0, "tex", ST_TRILINEAR_ANISOTROPIC_FILTERED);
#endif
    }   // InstancedSkinnedRefShadowShader
};   // InstancedSkinnedRefShadowShader

// ============================================================================
struct SkinnedSolid
{
    typedef InstancedSkinnedPass1Shader InstancedFirstPassShader;
    typedef InstancedSkinnedPass2Shader InstancedSecondPassShader;
    typedef InstancedSkinnedShadowShader InstancedShadowPassShader;
    typedef SkinnedPass1Shader FirstPassShader;
    typedef SkinnedPass2Shader SecondPassShader;
    typedef SkinnedShadowShader ShadowPassShader;
    // Todo: RSMs
    typedef ListSkinnedSolid List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_SKINNED_MESH;
    static const enum Material::ShaderType MaterialType
                                      = Material::SHADERTYPE_SOLID_SKINNED_MESH;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct SkinnedSolid

// ----------------------------------------------------------------------------
struct SkinnedAlphaRef
{
    typedef InstancedSkinnedRefPass1Shader InstancedFirstPassShader;
    typedef InstancedSkinnedRefPass2Shader InstancedSecondPassShader;
    typedef InstancedSkinnedRefShadowShader InstancedShadowPassShader;
    typedef SkinnedRefPass1Shader FirstPassShader;
    typedef SkinnedRefPass2Shader SecondPassShader;
    typedef SkinnedRefShadowShader ShadowPassShader;
    // Todo: RSMs
    typedef ListSkinnedAlphaRef List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_SKINNED_MESH;
    static const enum Material::ShaderType MaterialType =
                                   Material::SHADERTYPE_ALPHA_TEST_SKINNED_MESH;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t, size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<size_t> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct SkinnedAlphaRef

// ----------------------------------------------------------------------------
struct SkinnedNormalMat
{
    typedef InstancedSkinnedNormalMapShader InstancedFirstPassShader;
    typedef InstancedSkinnedPass2Shader InstancedSecondPassShader;
    typedef InstancedSkinnedShadowShader InstancedShadowPassShader;
    typedef SkinnedNormalMapShader FirstPassShader;
    typedef SkinnedPass2Shader SecondPassShader;
    typedef SkinnedShadowShader ShadowPassShader;
    // Todo: RSMs
    typedef ListSkinnedNormalMap List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_SKINNED_MESH;
    static const enum Material::ShaderType MaterialType =
                                   Material::SHADERTYPE_NORMAL_MAP_SKINNED_MESH;
    static const enum InstanceType Instance = InstanceTypeFourTex;
    static const STK::Tuple<size_t, size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct SkinnedNormalMat

// ----------------------------------------------------------------------------
struct SkinnedUnlitMat
{
    typedef InstancedSkinnedRefPass1Shader InstancedFirstPassShader;
    typedef InstancedSkinnedUnlitShader InstancedSecondPassShader;
    typedef InstancedSkinnedRefShadowShader InstancedShadowPassShader;
    typedef SkinnedRefPass1Shader FirstPassShader;
    typedef SkinnedUnlitShader SecondPassShader;
    typedef SkinnedRefShadowShader ShadowPassShader;
    // Todo: RSMs
    typedef ListSkinnedUnlit List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_SKINNED_MESH;
    static const enum Material::ShaderType MaterialType =
                                  Material::SHADERTYPE_SOLID_UNLIT_SKINNED_MESH;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t, size_t> FirstPassTextures;
    static const STK::Tuple<size_t> SecondPassTextures;
    static const STK::Tuple<size_t> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct SkinnedUnlitMat

// ----------------------------------------------------------------------------
struct DefaultMaterial
{
    typedef InstancedObjectPass1Shader InstancedFirstPassShader;
    typedef InstancedObjectPass2Shader InstancedSecondPassShader;
    typedef InstancedShadowShader InstancedShadowPassShader;
    typedef CInstancedRSMShader InstancedRSMShader;
    typedef Shaders::ObjectPass1Shader FirstPassShader;
    typedef Shaders::ObjectPass2Shader SecondPassShader;
    typedef ShadowShader ShadowPassShader;
    typedef CRSMShader RSMShader;
    typedef ListMatDefault List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_STANDARD;
    static const enum Material::ShaderType MaterialType
                                               = Material::SHADERTYPE_SOLID;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct DefaultMaterial

// ----------------------------------------------------------------------------
struct AlphaRef
{
    typedef InstancedObjectRefPass1Shader InstancedFirstPassShader;
    typedef InstancedObjectRefPass2Shader InstancedSecondPassShader;
    typedef InstancedRefShadowShader InstancedShadowPassShader;
    typedef CInstancedRSMShader InstancedRSMShader;
    typedef ObjectRefPass1Shader FirstPassShader;
    typedef ObjectRefPass2Shader SecondPassShader;
    typedef RefShadowShader ShadowPassShader;
    typedef CRSMShader RSMShader;
    typedef ListMatAlphaRef List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_STANDARD;
    static const enum Material::ShaderType MaterialType = Material::SHADERTYPE_ALPHA_TEST;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t, size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<size_t> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct AlphaRef

// ----------------------------------------------------------------------------
struct SphereMap
{
    typedef InstancedObjectPass1Shader InstancedFirstPassShader;
    typedef InstancedSphereMapShader InstancedSecondPassShader;
    typedef InstancedShadowShader InstancedShadowPassShader;
    typedef CInstancedRSMShader InstancedRSMShader;
    typedef Shaders::ObjectPass1Shader FirstPassShader;
    typedef SphereMapShader SecondPassShader;
    typedef ShadowShader ShadowPassShader;
    typedef CRSMShader RSMShader;
    typedef ListMatSphereMap List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_STANDARD;
    static const enum Material::ShaderType MaterialType
                                          = Material::SHADERTYPE_SPHERE_MAP;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t> FirstPassTextures;
    static const STK::Tuple<size_t> SecondPassTextures;
    static const STK::Tuple<> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct SphereMap

// ----------------------------------------------------------------------------
struct UnlitMat
{
    typedef InstancedObjectRefPass1Shader InstancedFirstPassShader;
    typedef InstancedObjectUnlitShader InstancedSecondPassShader;
    typedef InstancedRefShadowShader InstancedShadowPassShader;
    typedef CInstancedRSMShader InstancedRSMShader;
    typedef ObjectRefPass1Shader FirstPassShader;
    typedef ObjectUnlitShader SecondPassShader;
    typedef RefShadowShader ShadowPassShader;
    typedef CRSMShader RSMShader;
    typedef ListMatUnlit List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_STANDARD;
    static const enum Material::ShaderType MaterialType =
                                           Material::SHADERTYPE_SOLID_UNLIT;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t, size_t> FirstPassTextures;
    static const STK::Tuple<size_t> SecondPassTextures;
    static const STK::Tuple<size_t> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // struct UnlitMat

// ----------------------------------------------------------------------------
struct GrassMat
{
    typedef InstancedGrassPass1Shader InstancedFirstPassShader;
    typedef InstancedGrassPass2Shader InstancedSecondPassShader;
    typedef InstancedGrassShadowShader InstancedShadowPassShader;
    typedef CInstancedRSMShader InstancedRSMShader;
    typedef GrassPass1Shader FirstPassShader;
    typedef GrassPass2Shader SecondPassShader;
    typedef GrassShadowShader ShadowPassShader;
    typedef CRSMShader RSMShader;
    typedef ListMatGrass List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_STANDARD;
    static const enum Material::ShaderType MaterialType
        = Material::SHADERTYPE_VEGETATION;
    static const enum InstanceType Instance = InstanceTypeThreeTex;
    static const STK::Tuple<size_t, size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<size_t> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // GrassMat

// ----------------------------------------------------------------------------
struct NormalMat
{
    typedef InstancedNormalMapShader InstancedFirstPassShader;
    typedef InstancedObjectPass2Shader InstancedSecondPassShader;
    typedef InstancedShadowShader InstancedShadowPassShader;
    typedef CInstancedRSMShader InstancedRSMShader;
    typedef NormalMapShader FirstPassShader;
    typedef Shaders::ObjectPass2Shader SecondPassShader;
    typedef ShadowShader ShadowPassShader;
    typedef CRSMShader RSMShader;
    typedef ListMatNormalMap List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_TANGENTS;
    static const enum Material::ShaderType MaterialType
                                          = Material::SHADERTYPE_NORMAL_MAP;
    static const enum InstanceType Instance = InstanceTypeFourTex;
    static const STK::Tuple<size_t, size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // NormalMat

// ----------------------------------------------------------------------------
struct DetailMat
{
    typedef InstancedObjectPass1Shader InstancedFirstPassShader;
    typedef InstancedDetailedObjectPass2Shader InstancedSecondPassShader;
    typedef InstancedShadowShader InstancedShadowPassShader;
    typedef CInstancedRSMShader InstancedRSMShader;
    typedef Shaders::ObjectPass1Shader FirstPassShader;
    typedef DetailedObjectPass2Shader SecondPassShader;
    typedef ShadowShader ShadowPassShader;
    typedef CRSMShader RSMShader;
    typedef ListMatDetails List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_2TCOORDS;
    static const enum Material::ShaderType MaterialType
                                          = Material::SHADERTYPE_DETAIL_MAP;
    static const enum InstanceType Instance = InstanceTypeFourTex;
    static const STK::Tuple<size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<> ShadowTextures;
    static const STK::Tuple<size_t> RSMTextures;
};   // DetailMat

// ----------------------------------------------------------------------------
struct SplattingMat
{
    typedef InstancedObjectPass1Shader InstancedFirstPassShader;
    typedef InstancedShadowShader InstancedShadowPassShader;
    typedef Shaders::ObjectPass1Shader FirstPassShader;
    typedef SplattingShader SecondPassShader;
    typedef ShadowShader ShadowPassShader;
    typedef SplattingRSMShader RSMShader;
    typedef ListMatSplatting List;
    static const enum video::E_VERTEX_TYPE VertexType = video::EVT_2TCOORDS;
    static const enum Material::ShaderType MaterialType
                                          = Material::SHADERTYPE_SPLATTING;
    static const STK::Tuple<size_t> FirstPassTextures;
    static const STK::Tuple<size_t, size_t, size_t, size_t, size_t> SecondPassTextures;
    static const STK::Tuple<> ShadowTextures;
    static const STK::Tuple<size_t, size_t, size_t, size_t, size_t> RSMTextures;
};   // SplattingMat


#endif  // !SERVER_ONLY
#endif  // HEADER_MATERIAL_TYPE_HPP