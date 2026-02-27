#if 0
rm -f a.out
cc -std=c99 main.c ../reii/reii.c ../glfw/lib/libglfw.so.3 -lGL -lm
LD_LIBRARY_PATH=../glfw/lib/ ./a.out
exit
#endif

// NOTE(Constantine): Microsoft people are all fired. https://github.com/ocornut/imgui/issues/2043
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma comment(lib, "legacy_stdio_definitions.lib")
#endif

#include "../reii/reii.h"
#define GLFW_INCLUDE_NONE
#include "../glfw/include/glfw3.h"

#include <stdio.h>
#include <math.h>

#define countof(x) (sizeof(x) / sizeof((x)[0]))

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  GLFWwindow * window = glfwCreateWindow(700, 700, "", NULL, NULL);
  glfwMakeContextCurrent(window);

  ReiiContext   context = {};
  ReiiContext * ctx     = &context;
  reiiCreateContext((ReiiTypeProcedureGetProcAddress)glfwGetProcAddress, &context);

  typedef struct {
    unsigned char r, g, b, a;
  } color;

  const color colors[] = {
    {  0,   0,   0, 255},
    {255,   0,   0, 255},
    {  0, 255,   0, 255},
    {  0,   0, 255, 255},
    {255,   0, 255, 255},
  };

#define _ 0

  const int image1[] = {
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,2,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,4,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
  };

  const int image2[] = {
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,1,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,2,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,3,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,4,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
  };

  color texture1[countof(image1)];
  for (int i = 0; i < countof(image1); i += 1) {
    texture1[i] = colors[image1[i]];
  }

  color texture2[countof(image2)];
  for (int i = 0; i < countof(image2); i += 1) {
    texture2[i] = colors[image2[i]];
  }

  char vp_string[] =
    "!!ARBvp1.0"
    "TEMP R0;"
    "MAD R0.xy, vertex.position, 0.5, 0.5;"
    "MOV result.texcoord[0].x, R0;"
    "ADD result.texcoord[0].y,-R0, 1;"
    "MOV result.position, vertex.position;"
    "END";

  char fp_string[] =
    "!!ARBfp1.0"
    "TEX result.color, fragment.texcoord[0], texture[0], 2D;"
    "END";

  ReiiHandleTexture texture1Handle = 0;
  reiiCreateTexture(ctx, &texture1Handle);
  reiiTextureSetStateMipmap(ctx, REII_TEXTURE_BINDING_2D, texture1Handle, 0);
  reiiTextureSetStateSampler(ctx, REII_TEXTURE_BINDING_2D, texture1Handle, REII_SAMPLER_FILTERING_NEAREST, REII_SAMPLER_FILTERING_NEAREST, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, 1);
  reiiTextureDefineAndCopyFromCpu(ctx, REII_TEXTURE_BINDING_2D, texture1Handle,
    0,
    REII_TEXTURE_TEXEL_FORMAT_RGBA,
    (int)sqrtf(countof(image1)), // Assuming square texture
    (int)sqrtf(countof(image1)), // Assuming square texture
    REII_TEXTURE_TEXEL_FORMAT_RGBA,
    REII_TEXTURE_TEXEL_TYPE_U8,
    4,
    texture1);

  ReiiHandleTexture texture2Handle = 0;
  reiiCreateTexture(ctx, &texture2Handle);
  reiiTextureSetStateMipmap(ctx, REII_TEXTURE_BINDING_2D, texture2Handle, 0);
  reiiTextureSetStateSampler(ctx, REII_TEXTURE_BINDING_2D, texture2Handle, REII_SAMPLER_FILTERING_NEAREST, REII_SAMPLER_FILTERING_NEAREST, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT, 1);
  reiiTextureDefineAndCopyFromCpu(ctx, REII_TEXTURE_BINDING_2D, texture2Handle,
    0,
    REII_TEXTURE_TEXEL_FORMAT_RGBA,
    (int)sqrtf(countof(image2)), // Assuming square texture
    (int)sqrtf(countof(image2)), // Assuming square texture
    REII_TEXTURE_TEXEL_FORMAT_RGBA,
    REII_TEXTURE_TEXEL_TYPE_U8,
    4,
    texture2);

  ReiiMeshState mesh_state                                  = {};
  mesh_state.codeVertex                                     = vp_string;
  mesh_state.codeFragment                                   = fp_string;
  mesh_state.rasterizationDepthClampEnable                  = 0;
  mesh_state.rasterizationCullMode                          = REII_CULL_MODE_NONE;
  mesh_state.rasterizationFrontFace                         = REII_FRONT_FACE_COUNTER_CLOCKWISE;
  mesh_state.rasterizationDepthBiasEnable                   = 0;
  mesh_state.rasterizationDepthBiasConstantFactor           = 0;
  mesh_state.rasterizationDepthBiasSlopeFactor              = 0;
  mesh_state.multisampleEnable                              = 0;
  mesh_state.multisampleAlphaToCoverageEnable               = 0;
  mesh_state.multisampleAlphaToOneEnable                    = 0;
  mesh_state.depthTestEnable                                = 0;
  mesh_state.depthTestDepthWriteEnable                      = 0;
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

  ReiiHandleCommandList list_clear = 0;
  reiiCreateCommandList(ctx, &list_clear);
  reiiCommandListSet(ctx, list_clear);
    reiiCommandSetViewport(ctx, list_clear, 0, 0, 700, 700);
    reiiCommandSetScissor(ctx, list_clear, 0, 0, 700, 700);
    reiiCommandClear(ctx, list_clear, REII_CLEAR_COLOR_BIT, 0.f, 0, 0.f, 0.f, 0.f, 1.f);
  reiiCommandListEnd(ctx, list_clear);

  ReiiHandleCommandList list1 = 0;
  reiiCreateCommandList(ctx, &list1);
  reiiCommandListSet(ctx, list1);
  {
    ReiiMeshTextureBindings bindings = {};
    bindings.binding[0] = REII_TEXTURE_BINDING_2D;
    bindings.texture[0] = texture1Handle;
    reiiCommandMeshSetState(ctx, list1, &mesh_state, &bindings);
    reiiCommandMeshSet(ctx, list1);
    reiiCommandMeshPosition(ctx, list1,-1, 3, 0, 1);
    reiiCommandMeshPosition(ctx, list1,-1,-1, 0, 1);
    reiiCommandMeshPosition(ctx, list1, 3,-1, 0, 1);
    reiiCommandMeshEnd(ctx, list1);
  }
  reiiCommandListEnd(ctx, list1);

  ReiiHandleCommandList list2 = 0;
  reiiCreateCommandList(ctx, &list2);
  reiiCommandListSet(ctx, list2);
  {
    ReiiMeshTextureBindings bindings = {};
    bindings.binding[0] = REII_TEXTURE_BINDING_2D;
    bindings.texture[0] = texture2Handle;
    reiiCommandMeshSetState(ctx, list2, &mesh_state, &bindings);
    reiiCommandMeshSet(ctx, list2);
    reiiCommandMeshPosition(ctx, list2,-1, 3, 0, 1);
    reiiCommandMeshPosition(ctx, list2,-1,-1, 0, 1);
    reiiCommandMeshPosition(ctx, list2, 3,-1, 0, 1);
    reiiCommandMeshEnd(ctx, list2);
  }
  reiiCommandListEnd(ctx, list2);

  unsigned frame = 0;

  for (; glfwWindowShouldClose(window) == 0;) {
    glfwPollEvents();
    reiiSubmitCommandLists(ctx, 1, &list_clear);
    frame % 2 ? reiiSubmitCommandLists(ctx, 1, &list1) : reiiSubmitCommandLists(ctx, 1, &list2);
    glfwSwapBuffers(window);
    frame += 1;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
