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

typedef TextureAbgrU8 Framebuffer;
Framebuffer framebuffer(W,H);
ZBuffer zbuff(W,H);
std::shared_ptr<Texture> tex = nullptr;

void printMatrices(const glm::mat4& p, const glm::mat4& v, const glm::mat4& m);

#define ASSIMP_IMPORT

#ifdef ASSIMP_IMPORT
std::vector<ModelVertexIn> vertices;
std::vector<unsigned> indices;
#else
std::vector<ModelVertexIn> vertices = {
	{ glm::vec3(-1.0f,1.0f,0.0f), glm::vec2(0.0f, 0.0f) }, // Upper left
	{ glm::vec3(1.0f,1.0f,0.0f), glm::vec2(1.0f, 0.0f) }, // Upper right
	{ glm::vec3(-1.0f,-1.0f,0.0f), glm::vec2(0.0f, 1.0f) }, // Lower left
	{ glm::vec3(1.0f,-1.0f,0.0f), glm::vec2(1.0f, 1.0f) } // Lower right
};
std::vector<unsigned> indices = { 0, 1, 2, 1, 2, 3 };
#endif

std::vector<BasicVertexIn> vertices2 = {
	{ glm::vec3(-0.90f,0.90f,0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f ) }, // Upper left
	{ glm::vec3(1.0f,1.0f,0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) }, // Upper right
	{ glm::vec3(-1.0f,-1.0f,0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) }, // Lower left
	{ glm::vec3(0.90f,-0.90f,0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) } // Lower right
};

//std::vector<ModelVertexIn> vertices;
// std::vector<unsigned> indices;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Chip8",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W,H, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_BGRX8888, SDL_TEXTUREACCESS_STREAMING, W,H);
	MH33::Io::File pngText("/home/metalhead33/printr/uvtemplate.png",MH33::Io::Mode::READ);
	tex = textureFromPNG(pngText);
	ModelUniform uniform = { &framebuffer, &zbuff, false, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR, glm::mat4(1.0f), glm::mat4(1.0f), glm::vec4(0.0f, 0.0f, float(W),float(H)) };
	//ClipspaceUniform uniform2 = { &framebuffer, &zbuff, false, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR };
	BasicUniform uniform3 = { &framebuffer };
	Model2Uniform uniform4 = { &framebuffer, &zbuff, false, tex.get(), TextureFiltering::NEAREST_NEIGHBOUR, glm::mat4(1.0f), glm::vec2(float(W),float(H)) };
	//glm::mat4 Perspective = glm::perspectiveFov(glm::radians(90.0f), float(W), float(H), 0.1f, 100.0f);
	//glm::mat4 Perspective = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);
	glm::mat4 Perspective = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);
	glm::mat4 View = camera.GetViewMatrix();
	glm::mat4 Model = glm::mat4(1.0f); // glm::vec3(0.0f, 0.0f, -10.0f)
	//Model = glm::scale(Model,glm::vec3(5.0f, 5.0f, 1.0f) );
	//Model = glm::translate(Model,glm::vec3(0.0f, 0.0f, -10.0f));
	Model = glm::translate(Model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	uniform.proj = Perspective * View;
	uniform4.mvp = Perspective * View * Model;

	bool isInterrupted=false;
#ifdef ASSIMP_IMPORT
	Assimp::Importer importer;
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
	}
#endif
	SDL_WarpMouseInWindow(NULL,CX,CY);
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
					camera.ProcessKeyboard(Camera::FORWARD, 0.016666666666667);
					break;
				case SDLK_s:
					camera.ProcessKeyboard(Camera::BACKWARD, 0.016666666666667);
					break;
				case SDLK_a:
					camera.ProcessKeyboard(Camera::LEFT, 0.016666666666667);
					break;
				case SDLK_d:
					camera.ProcessKeyboard(Camera::RIGHT, 0.016666666666667);
					break;
				case SDLK_SPACE:
					printMatrices(Perspective,View,Model); break;
				default: break;
				}
				break;
			}
			default: break;
			}
		}
		framebuffer.clearToColour(glm::vec4(0.2f,0.2f,0.6f,1.0f));
		zbuff.clear();;
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_WarpMouseInWindow(NULL,CX,CY);
		// SDL_GetRelativeMouseState(&mouseX, &mouseY);
		camera.ProcessMouseMovement(float(mouseX - CX),float((mouseY - CY) * -1),float(W),float(H),false);
		// SDL_GetRelativeMouseState(&mouseX, &mouseY);
		View = camera.GetViewMatrix();
		uniform.proj = Perspective * View;
		uniform4.mvp = Perspective * View * Model;
		// Draw a triangle
		//ModelPipeline::renderTriangles(viewport,uniform,vertices.data(),indices.data(),indices.size() );
		Model2Pipeline::renderTriangles(viewport,uniform4,vertices.data(),indices.data(),indices.size() );
		//BasicPipeline::renderTriangles(viewport,uniform3,vertices2.data(),indices.data(),indices.size() );
		//BasicPipeline::renderTriangle(viewport,uniform3,vertices2[2],vertices2[1],vertices2[0]);
		//BasicPipeline::renderTriangle(viewport,uniform3,vertices2[3],vertices2[2],vertices2[1]);
		//ClipspacePipeline::renderTriangles(viewport,uniform2,vertices.data(),indices.data(),indices.size() );

		SDL_UpdateTexture(texture, nullptr, framebuffer.getPixels(), 4*W);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	} while(!isInterrupted);
	return 0;
}

void printMatrices(const glm::mat4& p, const glm::mat4& v, const glm::mat4& m) {
	std::cout << "auto Perspective = glm::mat4(\n" << std::fixed
			<< " glm::vec4( " << p[0][0] << "f, "  << p[0][1] << "f, "  << p[0][2] << "f, " << p[0][3] << "f),\n"
			<< " glm::vec4( " << p[1][0] << "f, "  << p[1][1] << "f, "  << p[1][2] << "f, " << p[1][3] << "f),\n"
			<< " glm::vec4( " << p[2][0] << "f, "  << p[2][1] << "f, "  << p[2][2] << "f, " << p[2][3] << "f),\n"
			<< " glm::vec4( " << p[3][0] << "f, "  << p[3][1] << "f, "  << p[3][2] << "f, " << p[3][3] << "f));\n"
			<< "auto View = glm::mat4(\n" << std::fixed
			<< " glm::vec4( " << v[0][0] << "f, "  << v[0][1] << "f, "  << v[0][2] << "f, " << v[0][3] << "f),\n"
			<< " glm::vec4( " << v[1][0] << "f, "  << v[1][1] << "f, "  << v[1][2] << "f, " << v[1][3] << "f),\n"
			<< " glm::vec4( " << v[2][0] << "f, "  << v[2][1] << "f, "  << v[2][2] << "f, " << v[2][3] << "f),\n"
			<< " glm::vec4( " << v[3][0] << "f, "  << v[3][1] << "f, "  << v[3][2] << "f, " << v[3][3] << "f));\n"
			<< "auto Model = glm::mat4(\n" << std::fixed
			<< " glm::vec4( " << m[0][0] << "f, "  << m[0][1] << "f, "  << m[0][2] << "f, " << m[0][3] << "f),\n"
			<< " glm::vec4( " << m[1][0] << "f, "  << m[1][1] << "f, "  << m[1][2] << "f, " << m[1][3] << "f),\n"
			<< " glm::vec4( " << m[2][0] << "f, "  << m[2][1] << "f, "  << m[2][2] << "f, " << m[2][3] << "f),\n"
			<< " glm::vec4( " << m[3][0] << "f, "  << m[3][1] << "f, "  << m[3][2] << "f, " << m[3][3] << "f));\n";
}
