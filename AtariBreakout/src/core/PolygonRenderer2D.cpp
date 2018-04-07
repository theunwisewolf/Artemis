#include "PolygonRenderer2D.h"

PolygonRenderer2D::PolygonRenderer2D() :
	m_IndexCount(0),
	m_Buffer(nullptr),
	m_VBO(0),
	m_EBO(0),
	m_VAO(0)
{
	GL(glGenVertexArrays(1, &this->m_VAO));
	GL(glGenBuffers(1, &this->m_VBO));
	GL(glGenBuffers(1, &this->m_EBO));

	GL(glBindVertexArray(this->m_VAO));

	GL(glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO));

	GL(glEnableVertexAttribArray(VERTEX_LAYOUT_POSITION));
	GL(glEnableVertexAttribArray(VERTEX_LAYOUT_COLOR));
	GL(glEnableVertexAttribArray(VERTEX_LAYOUT_UVS));

	GL(glVertexAttribPointer(VERTEX_LAYOUT_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(PolygonVertexLayout), reinterpret_cast<void*>(0)));
	GL(glVertexAttribPointer(VERTEX_LAYOUT_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(PolygonVertexLayout), reinterpret_cast<void*>(offsetof(PolygonVertexLayout, PolygonVertexLayout::color))));
	GL(glVertexAttribPointer(VERTEX_LAYOUT_UVS, 2, GL_FLOAT, GL_FALSE, sizeof(PolygonVertexLayout), reinterpret_cast<void*>(offsetof(PolygonVertexLayout, PolygonVertexLayout::uvs))));

	GL(glBindVertexArray(0));
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void PolygonRenderer2D::AddBatch(const std::vector<glm::vec3>& vertices, const std::vector<uint32_t>& indices, uint32_t color, const std::vector<glm::vec2>& uvs)
{
	std::copy(vertices.begin(), vertices.end(), std::back_inserter(this->m_Vertices));

	this->m_Indices.clear();

	for (int i = 0; i < indices.size(); i++)
	{
		this->m_Indices.push_back(indices[i]);
		this->m_IndexCount++;
	}

	m_PolygonColor = Color::toThreeComponents(color);
	m_UVs = uvs;
}

void PolygonRenderer2D::Begin()
{
	GL(glBindVertexArray(this->m_VAO));
}

void PolygonRenderer2D::End()
{
	GL(glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO));
	GL(glBufferData(GL_ARRAY_BUFFER, sizeof(PolygonVertexLayout) * 1 * this->m_Vertices.size(), NULL, GL_DYNAMIC_DRAW));

	this->m_Buffer = (PolygonVertexLayout*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	float angle = 0.0f;//90.0f * M_PI / 180.0f;
	for (int i = 0; i < this->m_Vertices.size(); i++)
	{
		// TODO: Fix for polygons
		float x = m_Vertices[i].x * cos(angle) - m_Vertices[i].y * sin(angle);
		float y = m_Vertices[i].y * cos(angle) + m_Vertices[i].x * sin(angle);

		this->m_Buffer->position = glm::vec3(x, y, m_Vertices[i].z);
		this->m_Buffer->color = this->m_PolygonColor;
		this->m_Buffer->uvs = this->m_UVs[i];
		this->m_Buffer++;
	}

	GL(glUnmapBuffer(GL_ARRAY_BUFFER));

	glBindVertexArray(0);
	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));

	this->m_Vertices.clear();
}

void PolygonRenderer2D::Render()
{
	glBindVertexArray(this->m_VAO);

	GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_EBO));
	GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * this->m_Indices.size(), &this->m_Indices[0], GL_DYNAMIC_DRAW));

	GL(glDrawElements(GL_TRIANGLES, this->m_IndexCount, GL_UNSIGNED_INT, 0));
	glBindVertexArray(0);

	// Reset the index count
	this->m_IndexCount = 0;
}

PolygonRenderer2D::~PolygonRenderer2D()
{
	glDeleteBuffers(1, &this->m_VBO);
	glDeleteBuffers(1, &this->m_EBO);
	glDeleteVertexArrays(1, &this->m_VAO);

	this->m_Indices.clear();
	this->m_Buffer = nullptr;

	this->m_Vertices.clear();
}