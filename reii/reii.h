#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned ReiiBool32;

typedef unsigned ReiiHandleTexture;
typedef unsigned ReiiHandleCommandList;
typedef unsigned ReiiHandleProgram;

typedef struct ReiiContext { void * _[54]; } ReiiContext;

typedef void * (*ReiiTypeProcedureGetProcAddress)(char * procname);

typedef enum ReiiTextureBinding {
  REII_TEXTURE_BINDING_2D              = 0x0DE1,
  REII_TEXTURE_BINDING_CUBE            = 0x8513,
  REII_TEXTURE_BINDING_CUBE_POSITIVE_X = 0x8515,
  REII_TEXTURE_BINDING_CUBE_NEGATIVE_X = 0x8516,
  REII_TEXTURE_BINDING_CUBE_POSITIVE_Y = 0x8517,
  REII_TEXTURE_BINDING_CUBE_NEGATIVE_Y = 0x8518,
  REII_TEXTURE_BINDING_CUBE_POSITIVE_Z = 0x8519,
  REII_TEXTURE_BINDING_CUBE_NEGATIVE_Z = 0x851A,
} ReiiTextureBinding;

typedef enum ReiiSamplerFiltering {
  REII_SAMPLER_FILTERING_NEAREST             = 0x2600,
  REII_SAMPLER_FILTERING_NEAREST_MIP_NEAREST = 0x2700,
  REII_SAMPLER_FILTERING_NEAREST_MIP_LINEAR  = 0x2702,
  REII_SAMPLER_FILTERING_LINEAR              = 0x2601,
  REII_SAMPLER_FILTERING_LINEAR_MIP_NEAREST  = 0x2701,
  REII_SAMPLER_FILTERING_LINEAR_MIP_LINEAR   = 0x2703,
} ReiiSamplerFiltering;

typedef enum ReiiSamplerBehaviorOutsideTextureCoordinate {
  REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_REPEAT              = 0x2901,
  REII_SAMPLER_BEHAVIOR_OUTSIDE_TEXTURE_COORDINATE_CLAMP_TO_EDGE_VALUE = 0x812F,
} ReiiSamplerBehaviorOutsideTextureCoordinate;

typedef enum ReiiTextureTexelFormat {
  REII_TEXTURE_TEXEL_FORMAT_A    = 0x1906,
  REII_TEXTURE_TEXEL_FORMAT_RGB  = 0x1907,
  REII_TEXTURE_TEXEL_FORMAT_RGBA = 0x1908,
} ReiiTextureTexelFormat;

typedef enum ReiiTextureTexelType {
  REII_TEXTURE_TEXEL_TYPE_S8    = 0x1400,
  REII_TEXTURE_TEXEL_TYPE_U8    = 0x1401,
  REII_TEXTURE_TEXEL_TYPE_S16   = 0x1402,
  REII_TEXTURE_TEXEL_TYPE_U16   = 0x1403,
  REII_TEXTURE_TEXEL_TYPE_S32   = 0x1404,
  REII_TEXTURE_TEXEL_TYPE_U32   = 0x1405,
  REII_TEXTURE_TEXEL_TYPE_FLOAT = 0x1406,
} ReiiTextureTexelType;

typedef unsigned ReiiClearFlags;
typedef enum ReiiClearFlagBits {
  REII_CLEAR_DEPTH_BIT   = 0x00000100,
  REII_CLEAR_STENCIL_BIT = 0x00000400,
  REII_CLEAR_COLOR_BIT   = 0x00004000,
} ReiiClearFlagBits;

typedef enum ReiiCullMode {
  REII_CULL_MODE_NONE  = 0,
  REII_CULL_MODE_FRONT = 0x0404,
  REII_CULL_MODE_BACK  = 0x0405,
} ReiiCullMode;

typedef enum ReiiFrontFace {
  REII_FRONT_FACE_COUNTER_CLOCKWISE = 0x0901,
  REII_FRONT_FACE_CLOCKWISE         = 0x0900,
} ReiiFrontFace;

typedef enum ReiiCompareOp {
  REII_COMPARE_OP_NEVER            = 0x0200,
  REII_COMPARE_OP_LESS             = 0x0201,
  REII_COMPARE_OP_EQUAL            = 0x0202,
  REII_COMPARE_OP_LESS_OR_EQUAL    = 0x0203,
  REII_COMPARE_OP_GREATER          = 0x0204,
  REII_COMPARE_OP_NOT_EQUAL        = 0x0205,
  REII_COMPARE_OP_GREATER_OR_EQUAL = 0x0206,
  REII_COMPARE_OP_ALWAYS           = 0x0207,
} ReiiCompareOp;

typedef enum ReiiStencilOp {
  REII_STENCIL_OP_KEEP                = 0x1E00,
  REII_STENCIL_OP_ZERO                = 0,
  REII_STENCIL_OP_REPLACE             = 0x1E01,
  REII_STENCIL_OP_INCREMENT_AND_CLAMP = 0x1E02,
  REII_STENCIL_OP_DECREMENT_AND_CLAMP = 0x1E03,
  REII_STENCIL_OP_INVERT              = 0x150A,
} ReiiStencilOp;

typedef enum ReiiLogicOp {
  REII_LOGIC_OP_CLEAR         = 0x1500,
  REII_LOGIC_OP_AND           = 0x1501,
  REII_LOGIC_OP_AND_REVERSE   = 0x1502,
  REII_LOGIC_OP_COPY          = 0x1503,
  REII_LOGIC_OP_AND_INVERTED  = 0x1504,
  REII_LOGIC_OP_NO_OP         = 0x1505,
  REII_LOGIC_OP_XOR           = 0x1506,
  REII_LOGIC_OP_OR            = 0x1507,
  REII_LOGIC_OP_NOR           = 0x1508,
  REII_LOGIC_OP_EQUIVALENT    = 0x1509,
  REII_LOGIC_OP_INVERT        = 0x150A,
  REII_LOGIC_OP_OR_REVERSE    = 0x150B,
  REII_LOGIC_OP_COPY_INVERTED = 0x150C,
  REII_LOGIC_OP_OR_INVERTED   = 0x150D,
  REII_LOGIC_OP_NAND          = 0x150E,
  REII_LOGIC_OP_SET           = 0x150F,
} ReiiLogicOp;

typedef enum ReiiBlendFactor {
  REII_BLEND_FACTOR_ZERO                     = 0,
  REII_BLEND_FACTOR_ONE                      = 1,
  REII_BLEND_FACTOR_SOURCE_COLOR             = 0x0300,
  REII_BLEND_FACTOR_ONE_MINUS_SOURCE_COLOR   = 0x0301,
  REII_BLEND_FACTOR_TARGET_COLOR             = 0x0306,
  REII_BLEND_FACTOR_ONE_MINUS_TARGET_COLOR   = 0x0307,
  REII_BLEND_FACTOR_SOURCE_ALPHA             = 0x0302,
  REII_BLEND_FACTOR_ONE_MINUS_SOURCE_ALPHA   = 0x0303,
  REII_BLEND_FACTOR_TARGET_ALPHA             = 0x0304,
  REII_BLEND_FACTOR_ONE_MINUS_TARGET_ALPHA   = 0x0305,
  REII_BLEND_FACTOR_CONSTANT_COLOR           = 0x8001,
  REII_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR = 0x8002,
  REII_BLEND_FACTOR_SOURCE_ALPHA_SATURATE    = 0x0308,
} ReiiBlendFactor;

typedef enum ReiiBlendOp {
  REII_BLEND_OP_ADD              = 0x8006,
  REII_BLEND_OP_SUBTRACT         = 0x800A,
  REII_BLEND_OP_REVERSE_SUBTRACT = 0x800B,
  REII_BLEND_OP_MIN              = 0x8007,
  REII_BLEND_OP_MAX              = 0x8008,
} ReiiBlendOp;

typedef struct ReiiMeshState {
  ReiiHandleProgram programVertex;
  ReiiHandleProgram programFragment;
  ReiiBool32        rasterizationDepthClampEnable;
  ReiiCullMode      rasterizationCullMode;
  ReiiFrontFace     rasterizationFrontFace;
  ReiiBool32        rasterizationDepthBiasEnable;
  float             rasterizationDepthBiasConstantFactor;
  float             rasterizationDepthBiasSlopeFactor;
  ReiiBool32        multisampleEnable;
  ReiiBool32        multisampleAlphaToCoverageEnable;
  ReiiBool32        multisampleAlphaToOneEnable;
  ReiiBool32        depthTestEnable;
  ReiiBool32        depthTestDepthWriteEnable;
  ReiiCompareOp     depthTestDepthCompareOp;
  ReiiBool32        stencilTestEnable;
  ReiiStencilOp     stencilTestFrontStencilTestFailOp;
  ReiiStencilOp     stencilTestFrontStencilTestPassDepthTestPassOp;
  ReiiStencilOp     stencilTestFrontStencilTestPassDepthTestFailOp;
  ReiiCompareOp     stencilTestFrontCompareOp;
  ReiiStencilOp     stencilTestBackStencilTestFailOp;
  ReiiStencilOp     stencilTestBackStencilTestPassDepthTestPassOp;
  ReiiStencilOp     stencilTestBackStencilTestPassDepthTestFailOp;
  ReiiCompareOp     stencilTestBackCompareOp;
  unsigned          stencilTestFrontAndBackCompareMask;
  unsigned          stencilTestFrontAndBackWriteMask;
  unsigned          stencilTestFrontAndBackReference;
  ReiiBool32        blendLogicOpEnable;
  ReiiLogicOp       blendLogicOp;
  float             blendConstants[4];
  ReiiBool32        outputColorWriteEnableR;
  ReiiBool32        outputColorWriteEnableG;
  ReiiBool32        outputColorWriteEnableB;
  ReiiBool32        outputColorWriteEnableA;
  ReiiBool32        outputColorBlendEnable;
  ReiiBlendFactor   outputColorBlendColorFactorSource;
  ReiiBlendFactor   outputColorBlendColorFactorTarget;
  ReiiBlendOp       outputColorBlendColorOp;
  ReiiBlendFactor   outputColorBlendAlphaFactorSource;
  ReiiBlendFactor   outputColorBlendAlphaFactorTarget;
  ReiiBlendOp       outputColorBlendAlphaOp;
  char *            codeVertex;
  char *            codeFragment;
} ReiiMeshState;

typedef struct ReiiMeshTextureBindings {
  ReiiTextureBinding binding[8];
  ReiiHandleTexture  texture[8];
} ReiiMeshTextureBindings;

typedef enum ReiiProgramBinding {
  REII_PROGRAM_BINDING_VERTEX   = 0x8620,
  REII_PROGRAM_BINDING_FRAGMENT = 0x8804,
} ReiiProgramBinding;

typedef enum ReiiStatus {
  REII_STATUS_SUCCESS                 = 0,
  REII_STATUS_ERROR_INVALID_ENUM      = 0x0500,
  REII_STATUS_ERROR_INVALID_VALUE     = 0x0501,
  REII_STATUS_ERROR_INVALID_OPERATION = 0x0502,
  REII_STATUS_ERROR_STACK_OVERFLOW    = 0x0503,
  REII_STATUS_ERROR_STACK_UNDERFLOW   = 0x0504,
  REII_STATUS_ERROR_OUT_OF_MEMORY     = 0x0505,
} ReiiStatus;

// Context

void reiiCreateContext                      (ReiiTypeProcedureGetProcAddress getProcAddress, ReiiContext * outContext);

// Texture

void reiiCreateTexture                      (ReiiContext * context, ReiiHandleTexture * outTexture);
void reiiTextureSetStateMipmap              (ReiiContext * context, ReiiTextureBinding binding, ReiiHandleTexture bindingTexture, ReiiBool32 generateMipLevels);
void reiiTextureSetStateSampler             (ReiiContext * context, ReiiTextureBinding binding, ReiiHandleTexture bindingTexture, ReiiSamplerFiltering magFiltering, ReiiSamplerFiltering minFiltering, ReiiSamplerBehaviorOutsideTextureCoordinate behaviorOutsideTextureCoordinateU, ReiiSamplerBehaviorOutsideTextureCoordinate behaviorOutsideTextureCoordinateV, int maxAnisotropy);
void reiiTextureDefineAndCopyFromCpu        (ReiiContext * context, ReiiTextureBinding binding, ReiiHandleTexture bindingTexture, int bindingLevel, ReiiTextureTexelFormat bindingTexelFormat, int width, int height, ReiiTextureTexelFormat texelsFormat, ReiiTextureTexelType texelsType, int texelsBytesAlignment, const void * texels);
void reiiTextureDefineAndCopyFromBackbuffer (ReiiContext * context, ReiiTextureBinding binding, ReiiHandleTexture bindingTexture, int bindingLevel, ReiiTextureTexelFormat bindingTexelFormat, int backbufferX, int backbufferY, int width, int height);
void reiiTextureCopyFromCpu                 (ReiiContext * context, ReiiTextureBinding binding, ReiiHandleTexture bindingTexture, int bindingLevel, int bindingX, int bindingY, int width, int height, ReiiTextureTexelFormat texelsFormat, ReiiTextureTexelType texelsType, int texelsBytesAlignment, const void * texels);
void reiiTextureCopyFromBackbuffer          (ReiiContext * context, ReiiTextureBinding binding, ReiiHandleTexture bindingTexture, int bindingLevel, int bindingX, int bindingY, int backbufferX, int backbufferY, int width, int height);
void reiiReadbackToCpuFromBackbuffer        (ReiiContext * context, int backbufferX, int backbufferY, int width, int height, ReiiTextureTexelFormat texelsFormat, ReiiTextureTexelType texelsType, int texelsBytesAlignment, void * outTexels);

// Command list

void reiiCreateCommandList                  (ReiiContext * context, ReiiHandleCommandList * outList);
void reiiCommandListSet                     (ReiiContext * context, ReiiHandleCommandList list);
void reiiCommandListEnd                     (ReiiContext * context);
void reiiCommandSetViewport                 (ReiiContext * context, int x, int y, int width, int height);
void reiiCommandSetScissor                  (ReiiContext * context, int x, int y, int width, int height);
void reiiCommandClear                       (ReiiContext * context, ReiiClearFlags clear, float depthValue, unsigned stencilValue, float colorR, float colorG, float colorB, float colorA);
void reiiCommandMeshSetState                (ReiiContext * context, ReiiMeshState * state, ReiiMeshTextureBindings * bindings);
void reiiCommandMeshSet                     (ReiiContext * context);
void reiiCommandMeshEnd                     (ReiiContext * context);
void reiiCommandMeshTexcoord                (ReiiContext * context, unsigned index, float x, float y, float z, float w);
void reiiCommandMeshColor                   (ReiiContext * context, float r, float g, float b, float a);
void reiiCommandMeshNormal                  (ReiiContext * context, float x, float y, float z);
void reiiCommandMeshPosition                (ReiiContext * context, float x, float y, float z, float w);

// Submit

void reiiSetProgramEnvironmentValueVertex   (ReiiContext * context, unsigned index, float x, float y, float z, float w);
void reiiSetProgramEnvironmentValueFragment (ReiiContext * context, unsigned index, float x, float y, float z, float w);
void reiiSubmitCommandLists                 (ReiiContext * context, unsigned listsCount, const ReiiHandleCommandList * lists);

// Destroy

void reiiDestroyTexture                     (ReiiContext * context, ReiiHandleTexture texture);
void reiiDestroyCommandList                 (ReiiContext * context, ReiiHandleCommandList list);
void reiiDestroyProgram                     (ReiiContext * context, ReiiHandleProgram program);
void reiiDestroyContext                     (ReiiContext * context);

// Status

void reiiGetStatus                          (ReiiContext * context, ReiiStatus * outStatus);

// Misc

void reiiFlush                              (ReiiContext * context);
void reiiFinish                             (ReiiContext * context);
void reiiCheckCode                          (ReiiContext * context, const char * codeVertex, const char * codeFragment);

#ifdef __cplusplus
}
#endif
