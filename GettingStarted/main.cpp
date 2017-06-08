//Project 1 for AI

//Author Jesse Casnig based on 'GettingStarted'
//Purpose: Creates 10 AI that try and collide or avoid
//The player depending on whether they're being looked
//At or not. The scoundrels.





// glfw needs these guys :(
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include "externals.h"
#include "global.h"
#include "LoadShaders.h"
#include "LoadMesh.h"
#include "LoadTexture.h"
#include "cEntity.h"
#include  "cAreaInfo.h"
#include "cEntityBuilder.h"

//sMeshEntry monkeyMesh;
sMeshEntry boxMesh;
//iEntity* player;
std::vector< iEntity* > g_vec_pEnt;


void Callback_WindowResize(GLFWwindow* window, int width, int height);
void CreateTheBuffers(std::vector<sMeshVertex>& vertices, std::vector<unsigned int>& indices);
void BindTheBuffers();
void DrawBufferEntry(sMeshEntry& entry);
bool SetUpTheShader();
void Update();
void DrawScene();
void LoadSceneFromFile(std::string sceneFile);
void ManageFlocks();
void CalculateFlocking(iEntity* entity);
int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}
	gCamera = new cCamera();

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	gWindow = glfwCreateWindow(1024, 768, "SuperWindow", NULL, NULL);
	if (gWindow == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(gWindow);
	
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(gWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwPollEvents();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	// Load the shader
	if (!SetUpTheShader())
	{
		std::cout << "Oh no! The shaders didn't load!!" << std::endl;
		system("pause");
		return -1;
	}

	// load the mesh buffers
	std::vector<sMeshVertex> vertices;
	std::vector<unsigned int> indices;
	bool success = false;
	success = LoadMesh("assets/suzanne.obj", indices, vertices, monkeyMesh);

	success = LoadMesh("assets/box.obj", indices, vertices, boxMesh);
	if (!success)
	{
		std::cout << "we couldn't load the monkey head!" << std::endl;
		system("pause");
		return -1;
	}
	
	CreateTheBuffers(vertices, indices);
	
	LoadSceneFromFile("Level.scene");




	do {
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		static double lastTime = glfwGetTime();
		double currentTime = glfwGetTime();
	//	float deltaTime = float(currentTime - lastTime);

		float deltaTime = 0.01f;
		for (unsigned int i = 0; ::g_vec_pEnt.size() > i; i++)
		{
			//Go through each of the entities in the vector
			//Call their update function with deltaTime
			
		//	cNameValuePair hop("Jump", observerHeight);
			//::g_vec_pEnt[i]->ExecuteCommand(hop);
			::g_vec_pEnt[i]->Update(deltaTime);
			
		}

		DrawScene();

		// Swap buffers
		glfwSwapBuffers(gWindow);
		glfwPollEvents();
		lastTime = currentTime;

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(gWindow) == 0);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	delete gCamera; // clean and tidy :)
	gCamera = 0;
	return 0;
}

// this is just terrific!
void DrawTheFloor()
{
	glm::mat4 boxMat;
	boxMat = glm::scale(boxMat, glm::vec3(0.5f, 0.25f, 0.5f));
	glm::vec4 boxColorLight(9.f, 9.f, 9.f, 1.f);
	glm::vec4 boxColorDark(0.1f, 0.1f, 0.1f, 1.f);
	glm::vec4 red(1.f, 0.f, 0.f, 1.f);
	glm::vec4 blue(0.f, 0.f, 1.f, 1.f);

	// per item uniforms
	glUniformMatrix4fv(gUniformId_ModelMatrix, 1, GL_FALSE, glm::value_ptr(boxMat));
	glUniform4fv(gUniformId_ModelColor, 1, glm::value_ptr(boxColorLight));

	glm::vec3 center(-0.f, -1.4f, -0.f);
	glm::vec3 xStep(1.f, 0.f, 0.f);
	glm::vec3 zStep(0.f, 0.f, 1.f);
	for (int i = -gAreaInfo.width; i <= gAreaInfo.width; i++)
	{
		for (int k = -gAreaInfo.height; k <= gAreaInfo.height; k++)
		{
			glm::vec3 pos = center + xStep * (float)i + zStep * (float)k;
			glm::vec4 color = (i * k) % 2 == 0 ? boxColorDark : boxColorLight;
			if (i * k == 0 && i + k != 0)
			{
				if (i == 0) color = blue;
				else color = red;
			}
			boxMat[3].x = pos.x;  boxMat[3].y = pos.y; boxMat[3].z = pos.z;

			glUniformMatrix4fv(gUniformId_ModelMatrix, 1, GL_FALSE, glm::value_ptr(boxMat));
			glUniform4fv(gUniformId_ModelColor, 1, glm::value_ptr(color));

			DrawBufferEntry(boxMesh);
		}
	}
	
}

void DrawScene()
{
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	gCamera->GetProjectionMatrix(projectionMatrix);
	gCamera->GetViewMatrix(viewMatrix);

	BindTheBuffers();
	glUseProgram(gProgramID);
	
	// per frame uniforms
	glUniformMatrix4fv(gUniformId_PojectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(gUniformId_ViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glm::vec4 eye4;
	gCamera->GetEyePosition(eye4);
	glUniform4fv(gUniformId_EyePosition, 1, glm::value_ptr(eye4));
	
	DrawTheFloor();
	
	// for each entity:
	// grab the entity
	// get the physics stuff, pass the transform as a model matrix
	// get the render stuff, pass the color, and render the mesh entry

	// per item uniforms
	for (unsigned int i = 0; i < ::g_vec_pEnt.size(); i++)
	{
		
		sMeshEntry meshEntry;
		glm::vec4 colour;
		glm::mat4 model;
		::g_vec_pEnt[i]->GetMatrix(model);
		::g_vec_pEnt[i]->GetColour(colour);
		glUniformMatrix4fv(gUniformId_ModelMatrix, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4fv(gUniformId_ModelColor, 1, glm::value_ptr(colour));
		::g_vec_pEnt[i]->GetMeshEntry(meshEntry);
		DrawBufferEntry(meshEntry);
	}
}

bool SetUpTheShader()
{
	// Create and compile our GLSL program from the shaders
	gProgramID = LoadShaders("SimpleShader.vert", "SimpleShader.frag");
	if (!gProgramID)
	{
		std::cout << "Oh no! The shaders didn't load!!" << std::endl;
		return false;
	}
	
	// per item
	gUniformId_ModelMatrix = glGetUniformLocation(gProgramID, "ModelMatrix");
	gUniformId_ModelColor = glGetUniformLocation(gProgramID, "ModelColor");
	// per frame
	gUniformId_ViewMatrix = glGetUniformLocation(gProgramID, "ViewMatrix");
	gUniformId_PojectionMatrix = glGetUniformLocation(gProgramID, "ProjectionMatrix");
	gUniformId_EyePosition = glGetUniformLocation(gProgramID, "EyePosition");


	return true;
}

void Callback_WindowResize(GLFWwindow* window, int width, int height)
{
	gCamera->WindowResize(width, height);
}

void CreateTheBuffers(std::vector<sMeshVertex>& vertices, std::vector<unsigned int>& indices)
{
	glGenVertexArrays(1, &gVertexBufferID);
	glBindVertexArray(gVertexBufferID);

	glGenBuffers(1, &gTexCoordBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, gTexCoordBufferID);

	glGenBuffers(1, &gNormalBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, gNormalBufferID);

	int bytesInVertexArray = vertices.size() * sizeof(sMeshVertex);
	glBufferData(GL_ARRAY_BUFFER, bytesInVertexArray, &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &gIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferID);

	int bytesInIndexArray = indices.size() * sizeof(GLuint);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytesInIndexArray, &indices[0], GL_STATIC_DRAW);

	BindTheBuffers();
}

void BindTheBuffers()
{
	glBindVertexArray(gVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, gTexCoordBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, gNormalBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferID);

	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // TexCoord
	glEnableVertexAttribArray(2); // Normal

	glVertexAttribPointer(0,		// index or "slot" in the shader
		4,							// Number of variables: vec4 would be 4 32-bit variables
		GL_FLOAT,					// Type: vec4 is float
		GL_FALSE,					// "normalize" the values (or not)
		sizeof(sMeshVertex),			// Number of bytes per vertex (the "stride")
		(GLvoid*)0);				// Offset from vertex (position is first, so offset = 0

	int offsetToTexCoordsInBytes = sizeof(((sMeshVertex*)0)->Position);
	glVertexAttribPointer(1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(sMeshVertex),
		(GLvoid*)offsetToTexCoordsInBytes);		// Offset in bytes to TexCoords

	int offsetToNormalInBytes = offsetToTexCoordsInBytes + sizeof(((sMeshVertex*)0)->TexCoord);
	glVertexAttribPointer(2,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(sMeshVertex),
		(GLvoid*)offsetToNormalInBytes);		// Offset in bytes to Normal
}

void DrawBufferEntry(sMeshEntry& entry)
{
	glDrawElementsBaseVertex(GL_TRIANGLES,
		entry.NumIndices,
		GL_UNSIGNED_INT,
		(void*)(sizeof(unsigned int) * entry.BaseIndex),
		entry.BaseVertex);
}

void LoadSceneFromFile(std::string sceneFile)
{
	std::ifstream theFile(sceneFile.c_str());
	if (!theFile.is_open())
	{
		return;
	}

	// Assume formant is only xyz with no other vertex attribs

	// Read until we get to the text "vertex" 
	std::string header;
	float playerSpeed = 0.f;
	float playX, playY, playZ;
	float minSpeed, maxSpeed = 0.f;
	float camOffsetMin, camOffsetMax, camOffset;
	int hunters, observers;
	float arenaX, arenaY;
	theFile >> header >> playerSpeed;
	cEntityBuilder* pEntityBuilder = cEntityBuilder::getInstance();
	player = cEntityBuilder::getInstance()->CreateEntity("Player");
	//gCamera = new cCamera();
	if (header == "PlayerSpeed")
	{
		player->SetSpeed(playerSpeed);
	}
	theFile >> header >> playX >> playY >> playZ;
	if (header == "PlayerLocation")
	{
		glm::mat4 playerMat = glm::mat4();
		playerMat[3].x = playX;
		playerMat[3].y = playY;
		playerMat[3].z = playZ;
		player->SetMatrix(playerMat);
		
	}
	::g_vec_pEnt.push_back(player);
	theFile >> header >> arenaX >> arenaY;
	if (header == "Dimensions")
	{
		gAreaInfo.height=arenaX;
		gAreaInfo.width=arenaX;
	}
	theFile >> header >> minSpeed >> maxSpeed;

	theFile >> header >> hunters;
	//Add number of hunters described in file
	if (header == "NumOfHunters")
	{
		for (unsigned int i = 0; i < hunters; i++)
		{
			iEntity* enemy = cEntityBuilder::getInstance()->CreateEntity("Hunter");
			float speed = glm::linearRand(minSpeed, maxSpeed);
			enemy->SetSpeed(speed);
			::g_vec_pEnt.push_back(enemy);
			
		}
	}
	theFile >> header >> observers;
	//Add number of Observers described in file
	if (header == "NumOfObservers")
	{
		for (unsigned int i = 0; i < observers; i++)
		{
			iEntity* enemy = cEntityBuilder::getInstance()->CreateEntity("Observer");
			float speed = glm::linearRand(minSpeed, maxSpeed);
			enemy->SetSpeed(speed);
			::g_vec_pEnt.push_back(enemy);
		}
	}
	//Add number of Flockers described in file
	for (unsigned int i = 0; i < 30; i++)
	{
		iEntity* flocker = cEntityBuilder::getInstance()->CreateEntity("Flocker");
		float speed = glm::linearRand(minSpeed, maxSpeed);
		flocker->SetSpeed(speed);
		::g_vec_pEnt.push_back(flocker);
	}
	//theFile >> header >> camOffsetMin;
	//if (header == "CamOffsetMin")
	//{
	//	gCamera->SetMinDistance(camOffsetMin);
	//}
	//theFile >> header >> camOffsetMax;
	//if (header == "CamOffsetMax")
	//{
	//
	//		gCamera->SetMaxDistance(camOffsetMax);
	//}
	//theFile >> header >> camOffset;
	//if (header == "CamStart")
	//{

	//	gCamera->SetMaxDistance(camOffset);
	//}

}

