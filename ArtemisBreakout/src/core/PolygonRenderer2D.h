#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <iterator>
#include <cmath>

#include <src/core/Common.h>

#include <src/core/VertexArray.h>
#include <src/core/Buffer.h>
#include <src/core/Color.h>
#include <src/core/IndexBuffer.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#define MAX_SPRITES					60000
#define VERTEX_LAYOUT_POSITION		0
#define VERTEX_LAYOUT_COLOR			1
#define VERTEX_LAYOUT_UVS			2

struct PolygonVertexLayout
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 uvs;
};

class PolygonRenderer2D
{
private:
	std::vector<glm::vec2> m_UVs;
	std::vector<glm::vec3> m_Vertices;
	std::vector<uint32_t> m_Indices;
	glm::vec4 m_PolygonColor;

	uint32_t m_VBO;
	uint32_t m_EBO;
	uint32_t m_VAO;
	uint32_t m_IndexCount;

	PolygonVertexLayout* m_Buffer;

public:
	PolygonRenderer2D();

	// Generates a new VBO, EBO and a corresponding VAO
	void Begin();

	// This sends the data stored on the client side to the GPU buffers
	void End();

	// Renders the sprites
	void Render();

	// Adds Vertices & Indices
	void AddBatch(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices, uint32_t color, const std::vector<glm::vec2>& uvs);

	~PolygonRenderer2D();
};