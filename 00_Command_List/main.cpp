#if 0
rm -f a.out
cc -std=c99 main.c ../reii/reii.c ../glfw/lib/libglfw.so.3 -lGL
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

const float mesh_vertices[] = {
#include "mesh_vertices.h"
};

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

  char vp_string[] =
    "!!ARBvp1.0"
    "MOV result.color, vertex.color;"
    "MOV result.position, vertex.position;"
    "END";

  char fp_string[] =
    "!!ARBfp1.0"
    "MOV result.color, fragment.color;"
    "END";

  reiiCheckCode(ctx, vp_string, fp_string);

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

  ReiiHandleCommandList list = 0;
  reiiCreateCommandList(ctx, &list);
  reiiCommandListSet(ctx, list);
    reiiCommandSetViewport(ctx, list, 0, 0, 700, 700);
    reiiCommandSetScissor(ctx, list, 0, 0, 700, 700);
    reiiCommandClear(ctx, list, REII_CLEAR_DEPTH_BIT | REII_CLEAR_COLOR_BIT, 0.f, 0, 0.f, 0.f, 0.05f, 1.f);
    reiiCommandMeshSetState(ctx, list, &mesh_state, 0);
    reiiCommandMeshSet(ctx, list);
    for (int i = 0, mesh_vertices_count = countof(mesh_vertices) / 3; i < mesh_vertices_count; i += 1) {
      float scale = 0.5f;
      reiiCommandMeshColor(ctx, list, i * 0.00025f, 0, 0.1f, 1);
      reiiCommandMeshPosition(ctx, list, mesh_vertices[i * 3 + 0] * scale, mesh_vertices[i * 3 + 1] * scale, mesh_vertices[i * 3 + 2] * scale, 1);
    }
    reiiCommandMeshEnd(ctx, list);
  reiiCommandListEnd(ctx, list);

  for (; glfwWindowShouldClose(window) == 0;) {
    glfwPollEvents();
    reiiSubmitCommandLists(ctx, 1, &list);
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
