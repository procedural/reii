#include "../rei/rei.h"
#include "../rei/rei.c"

#include <string.h>
#include <stdio.h>

#define REII_MAX_TEXTURE_BINDINGS_COUNT 8

typedef struct ReiiMeshTextureBindings {
  ReiTextureBinding binding[REII_MAX_TEXTURE_BINDINGS_COUNT];
  ReiHandleTexture  texture[REII_MAX_TEXTURE_BINDINGS_COUNT];
} ReiiMeshTextureBindings;

typedef struct ReiiMeshState {
  ReiHandleProgram programVertex;
  ReiHandleProgram programFragment;
  ReiBool32        rasterizationDepthClampEnable;
  ReiCullMode      rasterizationCullMode;
  ReiFrontFace     rasterizationFrontFace;
  ReiBool32        rasterizationDepthBiasEnable;
  float            rasterizationDepthBiasConstantFactor;
  float            rasterizationDepthBiasSlopeFactor;
  ReiBool32        multisampleEnable;
  ReiBool32        multisampleAlphaToCoverageEnable;
  ReiBool32        multisampleAlphaToOneEnable;
  ReiBool32        depthTestEnable;
  ReiBool32        depthTestDepthWriteEnable;
  ReiCompareOp     depthTestDepthCompareOp;
  ReiBool32        stencilTestEnable;
  ReiStencilOp     stencilTestFrontStencilTestFailOp;
  ReiStencilOp     stencilTestFrontStencilTestPassDepthTestPassOp;
  ReiStencilOp     stencilTestFrontStencilTestPassDepthTestFailOp;
  ReiCompareOp     stencilTestFrontCompareOp;
  ReiStencilOp     stencilTestBackStencilTestFailOp;
  ReiStencilOp     stencilTestBackStencilTestPassDepthTestPassOp;
  ReiStencilOp     stencilTestBackStencilTestPassDepthTestFailOp;
  ReiCompareOp     stencilTestBackCompareOp;
  unsigned         stencilTestFrontAndBackCompareMask;
  unsigned         stencilTestFrontAndBackWriteMask;
  unsigned         stencilTestFrontAndBackReference;
  ReiBool32        blendLogicOpEnable;
  ReiLogicOp       blendLogicOp;
  float            blendConstants[4];
  ReiBool32        outputColorWriteEnableR;
  ReiBool32        outputColorWriteEnableG;
  ReiBool32        outputColorWriteEnableB;
  ReiBool32        outputColorWriteEnableA;
  ReiBool32        outputColorBlendEnable;
  ReiBlendFactor   outputColorBlendColorFactorSource;
  ReiBlendFactor   outputColorBlendColorFactorTarget;
  ReiBlendOp       outputColorBlendColorOp;
  ReiBlendFactor   outputColorBlendAlphaFactorSource;
  ReiBlendFactor   outputColorBlendAlphaFactorTarget;
  ReiBlendOp       outputColorBlendAlphaOp;
  char *           codeVertex;
  char *           codeFragment;
} ReiiMeshState;

// Context

void reiiCreateContext(ReiTypeProcedureGetProcAddress getProcAddress, ReiContext * outContext) {
  reiCreateContext(getProcAddress, outContext);
}

// Texture

void reiiCreateTexture(ReiContext * context, ReiTextureBinding binding, ReiHandleTexture * outTexture) {
  outTexture[0] = reiCreateTexture(context);
}

void reiiTextureSetStateMipmap(ReiContext * context, ReiTextureBinding binding, ReiHandleTexture bindingTexture, ReiBool32 generateMipLevels) {
  ReiTextureBinding metabinding = binding == REI_TEXTURE_BINDING_2D ? REI_TEXTURE_BINDING_2D : REI_TEXTURE_BINDING_CUBE;
  reiSetActiveTextureSlot(context, 0);
  reiBindTextureToActiveTextureSlot(context, metabinding, bindingTexture);
  reiTextureSetStateMipmap(context, binding, generateMipLevels);
  reiBindTextureToActiveTextureSlot(context, metabinding, 0);
}

void reiiTextureSetStateSampler(ReiContext * context, ReiTextureBinding binding, ReiHandleTexture bindingTexture, ReiSamplerFiltering magFiltering, ReiSamplerFiltering minFiltering, ReiSamplerBehaviorOutsideTextureCoordinate behaviorOutsideTextureCoordinateU, ReiSamplerBehaviorOutsideTextureCoordinate behaviorOutsideTextureCoordinateV, int maxAnisotropy) {
  ReiTextureBinding metabinding = binding == REI_TEXTURE_BINDING_2D ? REI_TEXTURE_BINDING_2D : REI_TEXTURE_BINDING_CUBE;
  reiSetActiveTextureSlot(context, 0);
  reiBindTextureToActiveTextureSlot(context, metabinding, bindingTexture);
  reiTextureSetStateSampler(context, binding, magFiltering, minFiltering, behaviorOutsideTextureCoordinateU, behaviorOutsideTextureCoordinateV, maxAnisotropy);
  reiBindTextureToActiveTextureSlot(context, metabinding, 0);
}

void reiiTextureDefineAndCopyFromCpu(ReiContext * context, ReiTextureBinding binding, ReiHandleTexture bindingTexture, int bindingLevel, ReiTextureTexelFormat bindingTexelFormat, int width, int height, ReiTextureTexelFormat texelsFormat, ReiTextureTexelType texelsType, int texelsBytesAlignment, const void * texels) {
  ReiTextureBinding metabinding = binding == REI_TEXTURE_BINDING_2D ? REI_TEXTURE_BINDING_2D : REI_TEXTURE_BINDING_CUBE;
  reiSetActiveTextureSlot(context, 0);
  reiBindTextureToActiveTextureSlot(context, metabinding, bindingTexture);
  reiTextureDefineAndCopyFromCpu(context, binding, bindingLevel, bindingTexelFormat, width, height, texelsFormat, texelsType, texelsBytesAlignment, texels);
  reiBindTextureToActiveTextureSlot(context, metabinding, 0);
}

void reiiTextureDefineAndCopyFromBackbuffer(ReiContext * context, ReiTextureBinding binding, ReiHandleTexture bindingTexture, int bindingLevel, ReiTextureTexelFormat bindingTexelFormat, int backbufferX, int backbufferY, int width, int height) {
  ReiTextureBinding metabinding = binding == REI_TEXTURE_BINDING_2D ? REI_TEXTURE_BINDING_2D : REI_TEXTURE_BINDING_CUBE;
  reiSetActiveTextureSlot(context, 0);
  reiBindTextureToActiveTextureSlot(context, metabinding, bindingTexture);
  reiTextureDefineAndCopyFromBackbuffer(context, binding, bindingLevel, bindingTexelFormat, backbufferX, backbufferY, width, height);
  reiBindTextureToActiveTextureSlot(context, metabinding, 0);
}

void reiiTextureCopyFromCpu(ReiContext * context, ReiTextureBinding binding, ReiHandleTexture bindingTexture, int bindingLevel, int bindingX, int bindingY, int width, int height, ReiTextureTexelFormat texelsFormat, ReiTextureTexelType texelsType, int texelsBytesAlignment, const void * texels) {
  ReiTextureBinding metabinding = binding == REI_TEXTURE_BINDING_2D ? REI_TEXTURE_BINDING_2D : REI_TEXTURE_BINDING_CUBE;
  reiSetActiveTextureSlot(context, 0);
  reiBindTextureToActiveTextureSlot(context, metabinding, bindingTexture);
  reiTextureCopyFromCpu(context, binding, bindingLevel, bindingX, bindingY, width, height, texelsFormat, texelsType, texelsBytesAlignment, texels);
  reiBindTextureToActiveTextureSlot(context, metabinding, 0);
}

void reiiTextureCopyFromBackbuffer(ReiContext * context, ReiTextureBinding binding, ReiHandleTexture bindingTexture, int bindingLevel, int bindingX, int bindingY, int backbufferX, int backbufferY, int width, int height) {
  ReiTextureBinding metabinding = binding == REI_TEXTURE_BINDING_2D ? REI_TEXTURE_BINDING_2D : REI_TEXTURE_BINDING_CUBE;
  reiSetActiveTextureSlot(context, 0);
  reiBindTextureToActiveTextureSlot(context, metabinding, bindingTexture);
  reiTextureCopyFromBackbuffer(context, binding, bindingLevel, bindingX, bindingY, backbufferX, backbufferY, width, height);
  reiBindTextureToActiveTextureSlot(context, metabinding, 0);
}

void reiiReadbackToCpuFromBackbuffer(ReiContext * context, int backbufferX, int backbufferY, int width, int height, ReiTextureTexelFormat texelsFormat, ReiTextureTexelType texelsType, int texelsBytesAlignment, void * outTexels) {
  reiReadbackToCpuFromBackbuffer(context, backbufferX, backbufferY, width, height, texelsFormat, texelsType, texelsBytesAlignment, outTexels);
}

// Command list

void reiiCreateCommandList(ReiContext * context, ReiHandleCommandList * outList) {
  outList[0] = reiCreateCommandList(context);
}

void reiiCommandListSet(ReiContext * context, ReiHandleCommandList list) {
  reiCommandListSet(context, list);
}

void reiiCommandListEnd(ReiContext * context, ReiHandleCommandList list) {
  reiCommandListEnd(context);
}

void reiiCommandSetViewport(ReiContext * context, ReiHandleCommandList list, int x, int y, int width, int height) {
  reiCommandSetViewport(context, x, y, width, height);
}

void reiiCommandSetScissor(ReiContext * context, ReiHandleCommandList list, int x, int y, int width, int height) {
  reiCommandSetScissor(context, x, y, width, height);
}

void reiiCommandClear(ReiContext * context, ReiHandleCommandList list, ReiClearFlags clear, float depthValue, unsigned stencilValue, float colorR, float colorG, float colorB, float colorA) {
  reiCommandClear(context, clear, depthValue, stencilValue, colorR, colorG, colorB, colorA);
}

void reiiCommandMeshSetState(ReiContext * context, ReiHandleCommandList list, ReiiMeshState * state, ReiiMeshTextureBindings * bindings) {
  const char * error = NULL;
  unsigned i = 0;
  if (state != 0) {
    if (state->programVertex == 0) {
      ReiHandleProgram program = reiCreateProgram(context);
      reiBindProgram(context, REI_PROGRAM_BINDING_VERTEX, program);
      reiProgramInitialize(context, REI_PROGRAM_BINDING_VERTEX, strlen(state->codeVertex), state->codeVertex);
      reiBindProgram(context, REI_PROGRAM_BINDING_VERTEX, 0);
      error = reiGetProgramStatusString(context);
      if (error != NULL) {
        if (error[0] != '\0') {
          printf("%s", "[reiiCommandMeshSetState] Vertex code error:\n");
          printf("%s", error);
          fflush(stdout);
        }
      }
      state->programVertex = program;
    }
    if (state->programFragment == 0) {
      ReiHandleProgram program = reiCreateProgram(context);
      reiBindProgram(context, REI_PROGRAM_BINDING_FRAGMENT, program);
      reiProgramInitialize(context, REI_PROGRAM_BINDING_FRAGMENT, strlen(state->codeFragment), state->codeFragment);
      reiBindProgram(context, REI_PROGRAM_BINDING_FRAGMENT, 0);
      error = reiGetProgramStatusString(context);
      if (error != NULL) {
        if (error[0] != '\0') {
          printf("%s", "[reiiCommandMeshSetState] Fragment code error:\n");
          printf("%s", error);
          fflush(stdout);
        }
      }
      state->programFragment = program;
    }
    reiCommandMeshSetState(context, (ReiMeshState *)((void *)state));
  }
  if (bindings != 0) {
    for (; i < REII_MAX_TEXTURE_BINDINGS_COUNT; i += 1) {
      if (bindings->binding[i] != 0 && bindings->texture[i] == 0) {
        printf("Error: binding[%d] != 0 but texture[%d] == 0\n", i, i);
        fflush(stdout);
      }
      if (bindings->binding[i] == 0 && bindings->texture[i] != 0) {
        printf("Error: binding[%d] == 0 but texture[%d] != 0\n", i, i);
        fflush(stdout);
      }
      if (bindings->binding[i] != 0) {
        reiSetActiveTextureSlot(context, i);
        reiBindTextureToActiveTextureSlot(context, bindings->binding[i], bindings->texture[i]);
      } else {
        reiSetActiveTextureSlot(context, i);
        reiBindTextureToActiveTextureSlot(context, REI_TEXTURE_BINDING_2D, 0);
      }
    }
  }
}

void reiiCommandMeshSet(ReiContext * context, ReiHandleCommandList list) {
  reiCommandMeshSet(context);
}

void reiiCommandMeshEnd(ReiContext * context, ReiHandleCommandList list) {
  reiCommandMeshEnd(context);
}

void reiiCommandMeshTexcoord(ReiContext * context, ReiHandleCommandList list, unsigned index, float x, float y, float z, float w) {
  reiCommandMeshTexcoord(context, index, x, y, z, w);
}

void reiiCommandMeshColor(ReiContext * context, ReiHandleCommandList list, float r, float g, float b, float a) {
  reiCommandMeshColor(context, r, g, b, a);
}

void reiiCommandMeshNormal(ReiContext * context, ReiHandleCommandList list, float x, float y, float z) {
  reiCommandMeshNormal(context, x, y, z);
}

void reiiCommandMeshPosition(ReiContext * context, ReiHandleCommandList list, float x, float y, float z, float w) {
  reiCommandMeshPosition(context, x, y, z, w);
}

// Submit

void reiiSetProgramEnvironmentValueVertex(ReiContext * context, unsigned index, float x, float y, float z, float w) {
  reiSetProgramEnvironmentValue(context, REI_PROGRAM_BINDING_VERTEX, index, x, y, z, w);
}

void reiiSetProgramEnvironmentValueFragment(ReiContext * context, unsigned index, float x, float y, float z, float w) {
  reiSetProgramEnvironmentValue(context, REI_PROGRAM_BINDING_FRAGMENT, index, x, y, z, w);
}

void reiiSubmitCommandLists(ReiContext * context, unsigned listsCount, const ReiHandleCommandList * lists) {
  reiSubmitCommandLists(context, listsCount, lists);
}

// Destroy

void reiiDestroyTexture(ReiContext * context, ReiHandleTexture texture) {
  reiDestroyTexture(context, texture);
}

void reiiDestroyCommandList(ReiContext * context, ReiHandleCommandList list) {
  reiDestroyCommandList(context, list);
}

void reiiDestroyProgram(ReiContext * context, ReiHandleProgram program) {
  reiDestroyProgram(context, program);
}

void reiiDestroyContext(ReiContext * context) {
}

// Status

void reiiGetStatus(ReiContext * context, ReiStatus * outStatus) {
  outStatus[0] = reiGetStatus(context);
}

// Misc

void reiiFlush(ReiContext * context) {
  reiFlush(context);
}

void reiiFinish(ReiContext * context) {
  reiFinish(context);
}

void reiiCheckCode(ReiContext * context, const char * codeVertex, const char * codeFragment) {
  reiCheckCode(context, codeVertex, codeFragment);
}
