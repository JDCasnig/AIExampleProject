#include "global.h"
#include <iostream>
GLFWwindow* gWindow = 0;

cCamera* gCamera = 0;

cAreaInfo gAreaInfo = cAreaInfo();
iEntity* player;
sMeshEntry monkeyMesh;
glm::mat4 gMonkeyMatrix;
glm::vec4 gMonkeyColor(1.f, 0.6f, 0.8f, 1.f);

GLuint gVertexBufferID = 0;
GLuint gTexCoordBufferID = 0;
GLuint gNormalBufferID = 0;
GLuint gIndexBufferID = 0;

GLuint gProgramID = 0;
GLuint gUniformId_ModelMatrix = 0;
GLuint gUniformId_ViewMatrix = 0;
GLuint gUniformId_PojectionMatrix = 0;
GLuint gUniformId_ModelColor = 0;
GLuint gUniformId_EyePosition = 0;


std::vector< iEntity* > g_vec_Flockers;