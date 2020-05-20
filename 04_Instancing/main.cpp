#if 0
rm -f a.out
cc -std=c99 main.c ../reii/reii.c ../glfw/lib/libglfw.so.3 -lGL -lm
LD_LIBRARY_PATH=../glfw/lib/ ./a.out
exit
#endif

#include "../reii/reii.h"
#define GLFW_INCLUDE_NONE
#include "../glfw/include/glfw3.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const float mesh_vertices[] = {
#include "mesh_vertices.h"
};

#define countof(x) (sizeof(x) / sizeof((x)[0]))

void RandomInit() {
  srand(time(NULL));
}

float RandomRange(float min, float max) {
  float n = rand() / (float)RAND_MAX;
  return min + n * (max - min);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, 0);
  glfwWindowHint(GLFW_SAMPLES, 4);
  GLFWwindow * window = glfwCreateWindow(1000, 1000, "", NULL, NULL);
  glfwMakeContextCurrent(window);

  ReiiContext   context = {};
  ReiiContext * ctx     = &context;
  reiiCreateContext((ReiiTypeProcedureGetProcAddress)glfwGetProcAddress, &context);

  char vp_string[] =
    "!!ARBvp1.0"
    "TEMP pos;"
    "TEMP R0;"
    "TEMP R1;"
    "MUL pos, vertex.position, program.env[1].wwww;"
    "MUL R1, pos.z, 0.35;"
    "ADD R1, R1, program.env[2];"
    "ADD pos, pos, -program.env[1];"
    "MUL R0.xyzw, pos.xzzx, program.env[0].xyxy;"
    "ADD pos.x, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MUL R0.xyzw, pos.yzzy, program.env[0].zwzw;"
    "ADD pos.y, R0.x,-R0.y;"
    "ADD pos.z, R0.z, R0.w;"
    "MUL R0, pos.z, 0.003;"
    "ADD R1, R0, R1;"
    "MOV result.color, R1;"
    "MOV result.position.xyw, pos.xyzz;"
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
  mesh_state.stencilTestFrontCompareMask                    = 0;
  mesh_state.stencilTestFrontWriteMask                      = 0;
  mesh_state.stencilTestFrontReference                      = 0;
  mesh_state.stencilTestBackStencilTestFailOp               = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestBackStencilTestPassDepthTestPassOp  = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestBackStencilTestPassDepthTestFailOp  = REII_STENCIL_OP_KEEP;
  mesh_state.stencilTestBackCompareOp                       = REII_COMPARE_OP_NEVER;
  mesh_state.stencilTestBackCompareMask                     = 0;
  mesh_state.stencilTestBackWriteMask                       = 0;
  mesh_state.stencilTestBackReference                       = 0;
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
    reiiCommandSetViewport(ctx, 0, 0, 1000, 1000);
    reiiCommandSetScissor(ctx, 0, 0, 1000, 1000);
    reiiCommandClear(ctx, REII_CLEAR_DEPTH_BIT | REII_CLEAR_COLOR_BIT, 0.f, 0, 0.1f, 0.1f, 0.15f, 1.f);
  reiiCommandListEnd(ctx);

  ReiiHandleCommandList list_mesh_state = 0;
  reiiCreateCommandList(ctx, &list_mesh_state);
  reiiCommandListSet(ctx, list_mesh_state);
    reiiCommandMeshSetState(ctx, &mesh_state, 0);
  reiiCommandListEnd(ctx);

  ReiiHandleCommandList list_mesh = 0;
  reiiCreateCommandList(ctx, &list_mesh);
  reiiCommandListSet(ctx, list_mesh);
    reiiCommandMeshSet(ctx);
    for (int i = 0, mesh_vertices_count = countof(mesh_vertices) / 3; i < mesh_vertices_count; i += 1) {
      reiiCommandMeshPosition(ctx, mesh_vertices[i * 3 + 0], mesh_vertices[i * 3 + 1], mesh_vertices[i * 3 + 2], 1);
    }
    reiiCommandMeshEnd(ctx);
  reiiCommandListEnd(ctx);

  const int instanceCountX = 25;
  const int instanceCountY = 25;
  const int instanceCountZ = 25;

  float randomScaleW[instanceCountX][instanceCountY][instanceCountZ];
  float randomColorX[instanceCountX][instanceCountY][instanceCountZ];
  float randomColorY[instanceCountX][instanceCountY][instanceCountZ];
  float randomColorZ[instanceCountX][instanceCountY][instanceCountZ];

  RandomInit();
  for (int k = 0; k < instanceCountZ; k += 1) {
    for (int j = 0; j < instanceCountY; j += 1) {
      for (int i = 0; i < instanceCountX; i += 1) {
        randomScaleW[k][j][i] = RandomRange(0.05f, 0.45f);
        randomColorX[k][j][i] = RandomRange(0.15f, 0.45f);
        randomColorY[k][j][i] = RandomRange(0.15f, 0.45f);
        randomColorZ[k][j][i] = RandomRange(0.25f, 1.f);
      }
    }
  }

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  float pos_x = -36.f;
  float pos_y = -36.f;
  float pos_z = -110.f;
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

    pos_x += move_vec_x * 0.5;
    pos_y += move_vec_y * 0.5;
    pos_z += move_vec_z * 0.5;

    reiiSubmitCommandLists(ctx, 1, &list_clear);
    reiiSubmitCommandLists(ctx, 1, &list_mesh_state);
    reiiSetProgramEnvironmentValueVertex(ctx, 0, cosf(-rot_x), sinf(-rot_x), cosf(-rot_y), sinf(-rot_y));
    for (int k = 0; k < instanceCountZ; k += 1) {
      for (int j = 0; j < instanceCountY; j += 1) {
        for (int i = 0; i < instanceCountX; i += 1) {
          reiiSetProgramEnvironmentValueVertex(ctx, 1, pos_x + (i * 3.f), pos_y + (j * 3.f), pos_z + (k * 3.f), randomScaleW[k][j][i]);
          reiiSetProgramEnvironmentValueVertex(ctx, 2, randomColorX[k][j][i], randomColorY[k][j][i], randomColorZ[k][j][i], 1);
          reiiSubmitCommandLists(ctx, 1, &list_mesh);
        }
      }
    }

    glfwSwapBuffers(window);

    mouse_x_prev = mouse_x;
    mouse_y_prev = mouse_y;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
