#include <iostream>
#include <SDL2/SDL.h>
#include <cstring>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "StandardTexture.hpp"
#include "Pipeline/BasicPipeline.hpp"
#include "Pipeline/ModelPipeline.hpp"
#include "Pipeline/Model2Pipeline.hpp"
#include "CreateTexture.hpp"
#include "Camera.hpp"
#include <MhLib/Io/MhFile.hpp>
#include <cmath>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/mesh.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <stdexcept>

using namespace std;

static const unsigned W = 640, H = 480;
static const unsigned CX = W/2, CY = H/2;
static const glm::ivec2 viewport(W,H);
static const char* MODEL_PATH = "/home/metalhead33/printr/cube.dae";
int mouseX=0, mouseY=0;
Camera camera;

typedef TextureABGR<uint8_t> Framebuffer;
Framebuffer framebuffer(W,H);
ZBuffer zbuff(W,H);
std::shared_ptr<Texture> tex = nullptr;

std::vector<ModelVertexIn> vertices = {
	{ glm::vec3(-1.0f,1.0f,0.0f), glm::vec2(0.0f, 0.0f) }, // Upper left
	{ glm::vec3(1.0f,1.0f,0.0f), glm::vec2(1.0f, 0.0f) }, // Upper right
	{ glm::vec3(-1.0f,-1.0f,0.0f), glm::vec2(0.0f, 1.0f) }, // Lower left
	{ glm::vec3(1.0f,-1.0f,0.0f), glm::vec2(1.0f, 1.0f) } // Lower right
};
std::vector<unsigned> indices = { 0, 1, 2, 1, 2, 3 };
/*std::vector<BasicVertexIn> vertices2 = {
	{ glm::vec3(-0.90f,0.90f,0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f ) }, // Upper left
	{ glm::vec3(1.0f,1.0f,0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) }, // Upper right
	{ glm::vec3(-1.0f,-1.0f,0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, // Lower left
	{ glm::vec3(0.90f,-0.90f,0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) } // Lower right
};*/

//std::vector<ModelVertexIn> vertices;
// std::vector<unsigned> indices;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBX8888, SDL_TEXTUREACCESS_STREAMING, W,H);
	MH33::Io::File pngText("/home/metalhead33/printr/uvtemplate.png",MH33::Io::Mode::READ);
	tex = textureFromPNG(pngText);
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)W / (float)H, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	glm::mat4 Model = glm::mat4(1.0f); // glm::vec3(0.0f, 0.0f, -10.0f)
	//Model = glm::translate(Model,glm::vec3(0.0f, 0.0f, -10.0f));
	Model = glm::translate(Model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene

	ModelUniform uniform = { &framebuffer, &zbuff, false, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR, Model, Projection, glm::vec4(0.0f, 0.0f, float(W),float(H)) };
	//ClipspaceUniform uniform2 = { &framebuffer, &zbuff, false, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR };
	//BasicUniform uniform3 = { &framebuffer };
	Model2Uniform uniform4 = { &framebuffer, &zbuff, false, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR, Model, glm::vec2(float(W),float(H)) };
	bool isInterrupted=false;
	/*Assimp::Importer importer;
	importer.SetPropertyBool(AI_CONFIG_PP_PTV_NORMALIZE,true);
	const aiScene* scene = importer.ReadFile(MODEL_PATH, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
	if(!scene) throw std::runtime_error("Error loading the scene!");
	if(!scene->mNumMeshes) throw std::runtime_error("No models in the mesh!");
	const auto& mesh = *scene->mMeshes[0];
	if(!mesh.mNumVertices) throw std::runtime_error("There are no vertices in the mesh!!");
	if(!mesh.mNumFaces) throw std::runtime_error("There are no faces! in the mesh!!");
	if(!mesh.HasPositions()) throw std::runtime_error("There are no positions the mesh!!");
	if(!mesh.HasTextureCoords(0)) throw std::runtime_error("There are no texture coordinates the mesh!!");
	for(unsigned int i = 0; i < mesh.mNumVertices; ++i)
	{
		const auto& POS = mesh.mVertices[i];
		const auto& TEX = mesh.mTextureCoords[0][i];
		ModelVertexIn ver;
		ver.COORDS = { POS.x, POS.y, POS.z +2.0f };
		ver.TEXCOORD = { TEX.x, TEX.y };
		vertices.push_back(ver);
	}
	for(unsigned int i = 0; i < mesh.mNumFaces; ++i)
	{
		const auto& face = mesh.mFaces[i];
		for(unsigned int j = 0; j < face.mNumIndices; ++j) indices.push_back(face.mIndices[j]);
	}*/

	do {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
			case SDL_QUIT: isInterrupted = true; break;
			case SDL_KEYDOWN: {
				switch(ev.key.keysym.sym)
				{
				case SDLK_ESCAPE: isInterrupted = true; break;
				case SDLK_w:
					camera.ProcessKeyboard(Camera::FORWARD, 0.116666666666667);
					break;
				case SDLK_s:
					camera.ProcessKeyboard(Camera::BACKWARD, 0.116666666666667);
					break;
				case SDLK_a:
					camera.ProcessKeyboard(Camera::LEFT, 0.016666666666667);
					break;
				case SDLK_d:
					camera.ProcessKeyboard(Camera::RIGHT, 0.016666666666667);
					break;
				default: break;
				}
				break;
			}
			default: break;
			}
		}
		framebuffer.clear();
		zbuff.clear();;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_WarpMouseInWindow(NULL,CX,CY);
		// SDL_GetRelativeMouseState(&mouseX, &mouseY);
		camera.ProcessMouseMovement(float(mouseX - CX),float((mouseY - CY) * -1),float(W),float(H),false);
		// SDL_GetRelativeMouseState(&mouseX, &mouseY);
		uniform.proj = camera.GetViewMatrix() * glm::perspectiveFov(90.0f, float(W), float(H), 0.1f, 20.0f);
		uniform4.mvp = Model * camera.GetViewMatrix() * glm::perspectiveFov(90.0f, float(W), float(H), 0.1f, 20.0f);
		//uniform4.mvp = camera.GetViewMatrix() * glm::perspectiveFov(90.0f, float(W), float(H), 0.1f, 20.0f) * Model;
		//uniform.proj = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);
		// Draw a triangle
		Model2Pipeline::renderTriangles(viewport,uniform4,vertices.data(),indices.data(),indices.size() );
		//BasicPipeline::renderTriangles(viewport,uniform3,vertices2.data(),indices.data(),indices.size() );
		//BasicPipeline::renderTriangle(viewport,uniform3,vertices2[0],vertices2[1],vertices2[2]);
		//BasicPipeline::renderTriangle(viewport,uniform3,vertices2[1],vertices2[2],vertices2[3]);
		//ClipspacePipeline::renderTriangles(viewport,uniform2,vertices.data(),indices.data(),indices.size() );

		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), 4*W);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}
