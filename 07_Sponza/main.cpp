#if 0
rm -f a.out
if [ ! -e meshes.o ]; then chmod +x meshes.c && ./meshes.c; fi
cc -std=c99 main.c meshes.o ../reii/reii.c ../glfw/lib/libglfw.so.3 -lGL -lm
LD_LIBRARY_PATH=../glfw/lib/ ./a.out
exit
#endif

#include "../reii/reii.h"
#define GLFW_INCLUDE_NONE
#include "../glfw/include/glfw3.h"

#include <stdio.h>
#include <math.h>
#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_LINEAR
#define STBI_NO_HDR
#define STBI_NO_SIMD
#include "stb_image.h"

enum mesh_names {
#include "sponza_mesh_headers/mesh_enums.h"
  SUBMESH_COUNT
};

const char * mesh_texture_names[] = {
#include "sponza_mesh_headers/mesh_texture_names.h"
};

#ifdef __cplusplus
extern "C" {
#endif

extern const int   mesh_texture_indices[];
extern const float mesh_vertices[];
extern const float mesh_uvs[];
extern const int   submesh_vertex_begin[];
extern const int   submesh_vertex_end[];

#ifdef __cplusplus
}
#endif

#define countof(x) (sizeof(x) / sizeof((x)[0]))

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  glfwWindowHint(GLFW_SAMPLES, 2);
  GLFWwindow * window = glfwCreateWindow(1280, 720, "", NULL, NULL);
  glfwMakeContextCurrent(window);

  ReiiContext   context = {};
  ReiiContext * ctx     = &context;
  reiiCreateContext((ReiiTypeProcedureGetProcAddress)glfwGetProcAddress, &context);

  char vp_string[] =
    "!!ARBvp1.0"
    "TEMP pos;"
    "TEMP R0;"
    "ADD pos, vertex.position, -program.env[0];"
    "MUL R0.xyzw, pos.xzzx, program.env[1].xyxy;"
    "ADD pos.x, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MUL R0.xyzw, pos.yzzy, program.env[1].zwzw;"
    "ADD pos.y, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MUL pos.xy, pos, {0.613861, 1.091308, 1, 1};"
    "MOV result.texcoord[0], vertex.texcoord[0];"
    "MOV result.position.xyw, pos.xyzz;"
    "MOV result.position.z, 0.1;"
    "END";

  char fp_string[] =
    "!!ARBfp1.0"
    "TEX result.color, fragment.texcoord[0], texture[0], 2D;"
    "END";

  ReiiMeshState mesh_state                                  = {};
  mesh_state.codeVertex                                     = vp_string;
  mesh_state.codeFragment                                   = fp_string;
  mesh_state.rasterizationDepthClampEnable                  = 0;
  mesh_state.rasterizationCullMode                          = REII_CULL_MODE_BACK;
  mesh_state.rasterizationFrontFace                         = REII_FRONT_FACE_CLOCKWISE;
  mesh_state.rasterizationDepthBiasEnable                   = 0;
  mesh_state.rasterizationDepthBiasConstantFactor           = 0;
  mesh_state.rasterizationDepthBiasSlopeFactor              = 0;
  mesh_state.multisampleEnable                              = 1;
  mesh_state.multisampleAlphaToCoverageEnable               = 0;
  mesh_state.multisampleAlphaToOneEnable                    = 0;
  mesh_state.depthTestEnable                                = 1;
  mesh_state.depthTestDepthWriteEnable                      = 1;
  mesh_state.depthTestDepthCompareOp                        = REII_COMPARE_OP_GREATER_OR_EQUAL;
  mesh_state.stencilTestEnable                              = 0;
  mesh_state.stencilTestFrontStencilTestFailOp              = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestFrontStencilTestPassDepthTestPassOp = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestFrontStencilTestPassDepthTestFailOp = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestFrontCompareOp                      = REII_COMPARE_OP_NEVER;
  mesh_state.stencilTestBackStencilTestFailOp               = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestBackStencilTestPassDepthTestPassOp  = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestBackStencilTestPassDepthTestFailOp  = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestBackCompareOp                       = REII_COMPARE_OP_NEVER;
  mesh_state.stencilTestFrontAndBackCompareMask             = 0;
  mesh_state.stencilTestFrontAndBackWriteMask               = 0;
  mesh_state.stencilTestFrontAndBackReference               = 0;
  mesh_state.blendLogicOpEnable                             = 0;
  mesh_state.blendLogicOp                                   = REII_LOGIC_OP_CLEAR;
  mesh_state.blendConstants[0]                              = 0;
  mesh_state.blendConstants[1]                              = 0;
  mesh_state.blendConstants[2]                              = 0;
  mesh_state.blendConstants[3]                              = 0;
  mesh_state.outputColorWriteEnableR                        = 1;
  mesh_state.outputColorWriteEnableG                        = 1;
  mesh_state.outputColorWriteEnableB                        = 1;
  mesh_state.outputColorWriteEnableA                        = 1;
  mesh_state.outputColorBlendEnable                         = 0;
  mesh_state.outputColorBlendColorFactorSource              = REII_BLEND_FACTOR_ZERO;
  mesh_state.outputColorBlendColorFactorTarget              = REII_BLEND_FACTOR_ZERO;
  mesh_state.outputColorBlendColorOp                        = REII_BLEND_OP_ADD;
  mesh_state.outputColorBlendAlphaFactorSource              = REII_BLEND_FACTOR_ZERO;
  mesh_state.outputColorBlendAlphaFactorTarget              = REII_BLEND_FACTOR_ZERO;
  mesh_state.outputColorBlendAlphaOp                        = REII_BLEND_OP_ADD;

  ReiiMeshState mesh_state_with_blend                                  = {};
  mesh_state_with_blend.codeVertex                                     = vp_string;
  mesh_state_with_blend.codeFragment                                   = fp_string;
  mesh_state_with_blend.rasterizationDepthClampEnable                  = 0;
  mesh_state_with_blend.rasterizationCullMode                          = REII_CULL_MODE_NONE;
  mesh_state_with_blend.rasterizationFrontFace                         = REII_FRONT_FACE_CLOCKWISE;
  mesh_state_with_blend.rasterizationDepthBiasEnable                   = 0;
  mesh_state_with_blend.rasterizationDepthBiasConstantFactor           = 0;
  mesh_state_with_blend.rasterizationDepthBiasSlopeFactor              = 0;
  mesh_state_with_blend.multisampleEnable                              = 1;
  mesh_state_with_blend.multisampleAlphaToCoverageEnable               = 1;
  mesh_state_with_blend.multisampleAlphaToOneEnable                    = 0;
  mesh_state_with_blend.depthTestEnable                                = 1;
  mesh_state_with_blend.depthTestDepthWriteEnable                      = 1;
  mesh_state_with_blend.depthTestDepthCompareOp                        = REII_COMPARE_OP_GREATER_OR_EQUAL;
  mesh_state_with_blend.stencilTestEnable                              = 0;
  mesh_state_with_blend.stencilTestFrontStencilTestFailOp              = REII_STENCIL_OP_KEEP;
  mesh_state_with_blend.stencilTestFrontStencilTestPassDepthTestPassOp = REII_STENCIL_OP_KEEP;
  mesh_state_with_blend.stencilTestFrontStencilTestPassDepthTestFailOp = REII_STENCIL_OP_KEEP;
  mesh_state_with_blend.stencilTestFrontCompareOp                      = REII_COMPARE_OP_NEVER;
  mesh_state_with_blend.stencilTestBackStencilTestFailOp               = REII_STENCIL_OP_KEEP;
  mesh_state_with_blend.stencilTestBackStencilTestPassDepthTestPassOp  = REII_STENCIL_OP_KEEP;
  mesh_state_with_blend.stencilTestBackStencilTestPassDepthTestFailOp  = REII_STENCIL_OP_KEEP;
  mesh_state_with_blend.stencilTestBackCompareOp                       = REII_COMPARE_OP_NEVER;
  mesh_state_with_blend.stencilTestFrontAndBackCompareMask             = 0;
  mesh_state_with_blend.stencilTestFrontAndBackWriteMask               = 0;
  mesh_state_with_blend.stencilTestFrontAndBackReference               = 0;
  mesh_state_with_blend.blendLogicOpEnable                             = 0;
  mesh_state_with_blend.blendLogicOp                                   = REII_LOGIC_OP_CLEAR;
  mesh_state_with_blend.blendConstants[0]                              = 0;
  mesh_state_with_blend.blendConstants[1]                              = 0;
  mesh_state_with_blend.blendConstants[2]                              = 0;
  mesh_state_with_blend.blendConstants[3]                              = 0;
  mesh_state_with_blend.outputColorWriteEnableR                        = 1;
  mesh_state_with_blend.outputColorWriteEnableG                        = 1;
  mesh_state_with_blend.outputColorWriteEnableB                        = 1;
  mesh_state_with_blend.outputColorWriteEnableA                        = 1;
  mesh_state_with_blend.outputColorBlendEnable                         = 1;
  mesh_state_with_blend.outputColorBlendColorFactorSource              = REII_BLEND_FACTOR_SOURCE_ALPHA;
  mesh_state_with_blend.outputColorBlendColorFactorTarget              = REII_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA;
  mesh_state_with_blend.outputColorBlendColorOp                        = REII_BLEND_OP_ADD;
  mesh_state_with_blend.outputColorBlendAlphaFactorSource              = REII_BLEND_FACTOR_SOURCE_ALPHA;
  mesh_state_with_blend.outputColorBlendAlphaFactorTarget              = REII_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA;
  mesh_state_with_blend.outputColorBlendAlphaOp                        = REII_BLEND_OP_ADD;

  const int mesh_texture_names_count = countof(mesh_texture_names);

#ifdef _WIN32
  FILE *          textures_file_fd  [mesh_texture_names_count];
#else
  int             textures_file_fd  [mesh_texture_names_count];
  struct stat     textures_file_st  [mesh_texture_names_count];
  unsigned char * textures_file_mem [mesh_texture_names_count];
#endif
  void *          textures_mem      [mesh_texture_names_count];
  int             textures_mem_w    [mesh_texture_names_count];
  int             textures_mem_h    [mesh_texture_names_count];

  for (int i = 1; i < mesh_texture_names_count; i += 1) {
#ifdef _WIN32
    fopen_s(&textures_file_fd[i], mesh_texture_names[i], "rb");
    int bpp = 0;
    textures_mem[i] = stbi_load_from_file(textures_file_fd[i], &textures_mem_w[i], &textures_mem_h[i], &bpp, STBI_rgb_alpha);
#else
    textures_file_fd[i] = open(mesh_texture_names[i], O_RDONLY);
    fstat(textures_file_fd[i], &textures_file_st[i]);
    textures_file_mem[i] = mmap(0, textures_file_st[i].st_size, PROT_READ, MAP_PRIVATE, textures_file_fd[i], 0);
    int bpp = 0;
    textures_mem[i] = stbi_load_from_memory(textures_file_mem[i], textures_file_st[i].st_size, &textures_mem_w[i], &textures_mem_h[i], &bpp, STBI_rgb_alpha);
 #endif
  }

  void * textures[SUBMESH_COUNT] = {};
  int  textures_w[SUBMESH_COUNT] = {};
  int  textures_h[SUBMESH_COUNT] = {};

  for (int i = 0; i < SUBMESH_COUNT; i += 1) {
    int id = mesh_texture_indices[i];
    if (id == 0) {
      textures[i]   = NULL;
      textures_w[i] = 0;
      textures_h[i] = 0;
    } else {
      textures[i]   = textures_mem[id];
      textures_w[i] = textures_mem_w[id];
      textures_h[i] = textures_mem_h[id];
    }
  }

  ReiiHandleTexture submesh_texures[SUBMESH_COUNT] = {};

  unsigned char nil_texture[4 * 4] = {146, 146, 146, 255,
                                      146, 146, 146, 255,
                                      146, 146, 146, 255,
                                      146, 146, 146, 255};

  for (int i = 0; i < SUBMESH_COUNT; i += 1) {
    if (textures[i] == NULL) {
      reiiCreateTexture(ctx, &submesh_texures[i]);
      reiiTextureSetStateMipmap(ctx, REII_TEXTURE_BINDING_2D, submesh_texures[i], 0);
      reiiTextureSetStateSampler(ctx, REII_TEXTURE_BINDING_2D, submesh_texures[i], REII_SAMPLER_FILTERING_NEAREST, REII_SAMPLER_FILTERING_NEAREST, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, 1);
      reiiTextureDefineAndCopyFromCpu(ctx, REII_TEXTURE_BINDING_2D, submesh_texures[i], 0, REII_TEXTURE_TEXEL_FORMAT_RGBA, 2, 2, REII_TEXTURE_TEXEL_FORMAT_RGBA, REII_TEXTURE_TEXEL_TYPE_U8, 4, nil_texture);
      continue;
    }
    reiiCreateTexture(ctx, &submesh_texures[i]);
    reiiTextureSetStateMipmap(ctx, REII_TEXTURE_BINDING_2D, submesh_texures[i], 1);
    if (// Foliage:
        i == SPONZA_370_001 || i == SPONZA_369_001 || i == SPONZA_368_001 || i == SPONZA_367_001 || i == SPONZA_366_001 ||
        i == SPONZA_01_001  || i == SPONZA_372_001 || i == SPONZA_371_001 || i == SPONZA_276     || i == SPONZA_275     ||
        i == SPONZA_281     || i == SPONZA_00      || i == SPONZA_280     || i == SPONZA_279     || i == SPONZA_278     ||
        i == SPONZA_277     ||
        // Chains:
        i == SPONZA_341     || i == SPONZA_339     || i == SPONZA_340     || i == SPONZA_342     || i == SPONZA_333     ||
        i == SPONZA_331     || i == SPONZA_332     || i == SPONZA_330     || i == SPONZA_360     || i == SPONZA_358     ||
        i == SPONZA_357     || i == SPONZA_359     || i == SPONZA_348     || i == SPONZA_350     || i == SPONZA_351     ||
        i == SPONZA_349)
    {
      reiiTextureSetStateSampler(ctx, REII_TEXTURE_BINDING_2D, submesh_texures[i], REII_SAMPLER_FILTERING_LINEAR, REII_SAMPLER_FILTERING_LINEAR_MIP_LINEAR, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, 1);
    } else {
      reiiTextureSetStateSampler(ctx, REII_TEXTURE_BINDING_2D, submesh_texures[i], REII_SAMPLER_FILTERING_LINEAR, REII_SAMPLER_FILTERING_LINEAR_MIP_LINEAR, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, 8);
    }
    reiiTextureDefineAndCopyFromCpu(ctx, REII_TEXTURE_BINDING_2D, submesh_texures[i], 0, REII_TEXTURE_TEXEL_FORMAT_RGBA, textures_w[i], textures_h[i], REII_TEXTURE_TEXEL_FORMAT_RGBA, REII_TEXTURE_TEXEL_TYPE_U8, 4, textures[i]);
  }

  for (int i = 1; i < mesh_texture_names_count; i += 1) {
    if (textures_mem[i] != NULL) {
      stbi_image_free(textures_mem[i]);
      textures_mem[i] = NULL;
    }
#ifdef _WIN32
    if (textures_file_fd[i] != NULL) {
      fclose(textures_file_fd[i]);
      textures_file_fd[i] = 0;
    }
#else
    if (textures_file_mem[i] != NULL) {
      munmap(textures_file_mem[i], textures_file_st[i].st_size);
      textures_file_mem[i] = NULL;
    }
    if (textures_file_fd[i] != 0) {
      close(textures_file_fd[i]);
      textures_file_fd[i] = 0;
    }
#endif
  }

  for (int i = 0; i < SUBMESH_COUNT; i += 1) {
    textures[i]   = NULL;
    textures_w[i] = 0;
    textures_h[i] = 0;
  }

  ReiiHandleCommandList list_clear = 0;
  reiiCreateCommandList(ctx, &list_clear);
  reiiCommandListSet(ctx, list_clear);
    reiiCommandSetViewport(ctx, 0, 0, 1280, 720);
    reiiCommandSetScissor(ctx, 0, 0, 1280, 720);
    reiiCommandClear(ctx, REII_CLEAR_DEPTH_BIT | REII_CLEAR_COLOR_BIT, 0.f, 0, 0.98f, 0.98f, 0.98f, 1.f);
  reiiCommandListEnd(ctx);

  ReiiHandleCommandList list = 0;
  reiiCreateCommandList(ctx, &list);
  reiiCommandListSet(ctx, list);
    for (int j = 0; j < SUBMESH_COUNT; j += 1) {
      if (// Foliage:
          j == SPONZA_370_001 || j == SPONZA_369_001 || j == SPONZA_368_001 || j == SPONZA_367_001 || j == SPONZA_366_001 ||
          j == SPONZA_01_001  || j == SPONZA_372_001 || j == SPONZA_371_001 || j == SPONZA_276     || j == SPONZA_275     ||
          j == SPONZA_281     || j == SPONZA_00      || j == SPONZA_280     || j == SPONZA_279     || j == SPONZA_278     ||
          j == SPONZA_277     ||
          // Chains:
          j == SPONZA_341     || j == SPONZA_339     || j == SPONZA_340     || j == SPONZA_342     || j == SPONZA_333     ||
          j == SPONZA_331     || j == SPONZA_332     || j == SPONZA_330     || j == SPONZA_360     || j == SPONZA_358     ||
          j == SPONZA_357     || j == SPONZA_359     || j == SPONZA_348     || j == SPONZA_350     || j == SPONZA_351     ||
          j == SPONZA_349)
      {
        continue;
      } else {
      }
      ReiiMeshTextureBindings bindings = {};
      bindings.binding[0] = REII_TEXTURE_BINDING_2D;
      bindings.texture[0] = submesh_texures[j];
      reiiCommandMeshSetState(ctx, &mesh_state, &bindings);
      reiiCommandMeshSet(ctx);
      for (int i = submesh_vertex_begin[j]; i < submesh_vertex_end[j]; i += 1) {
        reiiCommandMeshTexcoord(ctx, 0, mesh_uvs[i * 2 + 0], 1 - mesh_uvs[i * 2 + 1], 0, 0);
        reiiCommandMeshPosition(ctx, mesh_vertices[i * 4 + 0], mesh_vertices[i * 4 + 1], mesh_vertices[i * 4 + 2], 1);
      }
      reiiCommandMeshEnd(ctx);
    }
  reiiCommandListEnd(ctx);

  ReiiHandleCommandList list_with_blend = 0;
  reiiCreateCommandList(ctx, &list_with_blend);
  reiiCommandListSet(ctx, list_with_blend);
    for (int j = 0; j < SUBMESH_COUNT; j += 1) {
      if (// Foliage:
          j == SPONZA_370_001 || j == SPONZA_369_001 || j == SPONZA_368_001 || j == SPONZA_367_001 || j == SPONZA_366_001 ||
          j == SPONZA_01_001  || j == SPONZA_372_001 || j == SPONZA_371_001 || j == SPONZA_276     || j == SPONZA_275     ||
          j == SPONZA_281     || j == SPONZA_00      || j == SPONZA_280     || j == SPONZA_279     || j == SPONZA_278     ||
          j == SPONZA_277     ||
          // Chains:
          j == SPONZA_341     || j == SPONZA_339     || j == SPONZA_340     || j == SPONZA_342     || j == SPONZA_333     ||
          j == SPONZA_331     || j == SPONZA_332     || j == SPONZA_330     || j == SPONZA_360     || j == SPONZA_358     ||
          j == SPONZA_357     || j == SPONZA_359     || j == SPONZA_348     || j == SPONZA_350     || j == SPONZA_351     ||
          j == SPONZA_349)
      {
      } else {
        continue;
      }
      ReiiMeshTextureBindings bindings = {};
      bindings.binding[0] = REII_TEXTURE_BINDING_2D;
      bindings.texture[0] = submesh_texures[j];
      reiiCommandMeshSetState(ctx, &mesh_state_with_blend, &bindings);
      reiiCommandMeshSet(ctx);
      for (int i = submesh_vertex_begin[j]; i < submesh_vertex_end[j]; i += 1) {
        reiiCommandMeshTexcoord(ctx, 0, mesh_uvs[i * 2 + 0], 1 - mesh_uvs[i * 2 + 1], 0, 0);
        reiiCommandMeshPosition(ctx, mesh_vertices[i * 4 + 0], mesh_vertices[i * 4 + 1], mesh_vertices[i * 4 + 2], 1);
      }
      reiiCommandMeshEnd(ctx);
    }
  reiiCommandListEnd(ctx);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  float pos_x = 0;
  float pos_y = 7.f;
  float pos_z = 0;
  float rot_x = 0;
  float rot_y = 0;

  glfwPollEvents();

  double start_mouse_x = 0;
  double start_mouse_y = 0;
  glfwGetCursorPos(window, &start_mouse_x, &start_mouse_y);
  double mouse_x_prev = start_mouse_x;
  double mouse_y_prev = start_mouse_y;

  for (; glfwWindowShouldClose(window) == 0;) {
    glfwPollEvents();

    double mouse_x = 0;
    double mouse_y = 0;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);

    float mouse_disp_x = (float)(mouse_x_prev - mouse_x) * 0.0035f;
    float mouse_disp_y = (float)(mouse_y - mouse_y_prev) * 0.0035f;

    rot_x += mouse_disp_x;
    rot_y += mouse_disp_y;

    float move_vec_x = 0;
    float move_vec_y = 0;
    float move_vec_z = 0;

    move_vec_x += glfwGetKey(window, GLFW_KEY_D);
    move_vec_x -= glfwGetKey(window, GLFW_KEY_A);

    move_vec_y += glfwGetKey(window, GLFW_KEY_E);
    move_vec_y -= glfwGetKey(window, GLFW_KEY_Q);

    move_vec_z += glfwGetKey(window, GLFW_KEY_W);
    move_vec_z -= glfwGetKey(window, GLFW_KEY_S);

    float move_vec_len = sqrtf(move_vec_x*move_vec_x + move_vec_y*move_vec_y + move_vec_z*move_vec_z);
    if (move_vec_len != 0) {
      move_vec_x /= move_vec_len;
      move_vec_y /= move_vec_len;
      move_vec_z /= move_vec_len;
    }

    {
      float rot_cos = cosf(rot_y);
      float rot_sin = sinf(rot_y);
      float pos_y = move_vec_y;
      float pos_z = move_vec_z;
      move_vec_y = pos_y * rot_cos - pos_z * rot_sin;
      move_vec_z = pos_z * rot_cos + pos_y * rot_sin;
    }

    {
      float rot_cos = cosf(rot_x);
      float rot_sin = sinf(rot_x);
      float pos_x = move_vec_x;
      float pos_z = move_vec_z;
      move_vec_x = pos_x * rot_cos - pos_z * rot_sin;
      move_vec_z = pos_z * rot_cos + pos_x * rot_sin;
    }

    pos_x += move_vec_x * 0.225;
    pos_y += move_vec_y * 0.225;
    pos_z += move_vec_z * 0.225;

    reiiSetProgramEnvironmentValueVertex(ctx, 0, pos_x, pos_y, pos_z, 0);
    reiiSetProgramEnvironmentValueVertex(ctx, 1, cosf(-rot_x), sinf(-rot_x), cosf(-rot_y), sinf(-rot_y));

    ReiiHandleCommandList commandLists[] = {list_clear, list, list_with_blend};
    reiiSubmitCommandLists(ctx, countof(commandLists), commandLists);

    glfwSwapBuffers(window);

    mouse_x_prev = mouse_x;
    mouse_y_prev = mouse_y;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
