#if 0
rm -f a.out
cc -std=c99 main.c ../reii/reii.c ../glfw/lib/libglfw.so.3 -lGL
LD_LIBRARY_PATH=../glfw/lib/ ./a.out
exit
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
  glfwWindowHint(GLFW_SAMPLES, 4);
  GLFWwindow * window = glfwCreateWindow(700, 700, "", NULL, NULL);
  glfwMakeContextCurrent(window);

  ReiiContext   context = {};
  ReiiContext * ctx     = &context;
  reiiCreateContext((ReiiTypeProcedureGetProcAddress)glfwGetProcAddress, &context);

  char vp_string[] =
    "!!ARBvp1.0"
    "MOV result.color, vertex.color;"
    "ADD result.position.xyw, vertex.position.xyzz, -program.env[0].xyzz;"
    "MOV result.position.z, 0.1;"
    "END";

  char fp_string[] =
    "!!ARBfp1.0"
    "MOV result.color, fragment.color;"
    "END";

  ReiiMeshState mesh_state                                  = {};
  mesh_state.codeVertex                                     = vp_string;
  mesh_state.codeFragment                                   = fp_string;
  mesh_state.rasterizationDepthClampEnable                  = 0;
  mesh_state.rasterizationCullMode                          = REII_CULL_MODE_NONE;
  mesh_state.rasterizationFrontFace                         = REII_FRONT_FACE_COUNTER_CLOCKWISE;
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

  ReiiHandleCommandList list = 0;
  reiiCreateCommandList(ctx, &list);
  reiiCommandListSet(ctx, list);
    reiiCommandSetViewport(ctx, 0, 0, 700, 700);
    reiiCommandSetScissor(ctx, 0, 0, 700, 700);
    reiiCommandClear(ctx, REII_CLEAR_DEPTH_BIT | REII_CLEAR_COLOR_BIT, 0.f, 0, 0.f, 0.f, 0.05f, 1.f);
    reiiCommandMeshSetState(ctx, &mesh_state, 0);
    reiiCommandMeshSet(ctx);
    for (int i = 0, mesh_vertices_count = countof(mesh_vertices) / 3; i < mesh_vertices_count; i += 1) {
      reiiCommandMeshColor(ctx, i * 0.00025f, 0, 0.1f, 1);
      reiiCommandMeshPosition(ctx, mesh_vertices[i * 3 + 0], mesh_vertices[i * 3 + 1], mesh_vertices[i * 3 + 2], 1);
    }
    reiiCommandMeshEnd(ctx);
  reiiCommandListEnd(ctx);

  float pos_x = 0;
  float pos_y = 0;
  float pos_z = -2.f;

  for (; glfwWindowShouldClose(window) == 0;) {
    glfwPollEvents();

    pos_x += glfwGetKey(window, GLFW_KEY_D) * 0.025f;
    pos_x -= glfwGetKey(window, GLFW_KEY_A) * 0.025f;

    pos_y += glfwGetKey(window, GLFW_KEY_E) * 0.025f;
    pos_y -= glfwGetKey(window, GLFW_KEY_Q) * 0.025f;

    pos_z += glfwGetKey(window, GLFW_KEY_W) * 0.025f;
    pos_z -= glfwGetKey(window, GLFW_KEY_S) * 0.025f;

    reiiSetProgramEnvironmentValueVertex(ctx, 0, pos_x, pos_y, pos_z, 0);
    reiiSubmitCommandLists(ctx, 1, &list);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
