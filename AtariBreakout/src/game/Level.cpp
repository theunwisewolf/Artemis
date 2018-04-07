#include "Level.h"

namespace ArtemisBreakout
{

Level::Level(std::string level, const Window& window) :
	m_Level( level ),
	m_Window(window),
	m_Platform(nullptr),
	m_Ball(nullptr),
	m_BallB(nullptr),
	BALL_VELOCITY(100.0f, 300.0f, 0.0f),
	m_BlocksDestroyed(0)
{
	std::string levelPath = std::string( LEVEL_PATH ) + level;

	FILE* fp;
	fopen_s(&fp, levelPath.c_str(), "rb");

	// Failed to read file
	if (fp == NULL)
	{
		std::cout << "Level " << level << " could not be opened for reading." << std::endl;
		return;
	}

	std::fseek(fp, 0, SEEK_END);
	size_t size = std::ftell(fp);
	std::fseek(fp, 0, SEEK_SET);

	std::vector<char> data(size);

	std::fread(&data[0], sizeof(char), size, fp);

	this->m_Data.assign(data.begin(), data.end());

	// Shaders
	m_ShaderProgram.AttachShader(Shader("Shaders/VertexShader.glsl", Shader::ShaderType::Vertex));
	m_ShaderProgram.AttachShader(Shader("Shaders/FragmentShader.glsl", Shader::ShaderType::Fragment));
	m_ShaderProgram.Link();
	m_ShaderProgram.Use();

	// Camera position
	m_ShaderProgram.SetUniform2f("input_position", 0.0f, 0.0f);

	// Set the Camera Projection Matrix
	glm::mat4 prMatrix = glm::ortho(-window.Width() / 2.0f, window.Width() / 2.0f, -window.Height() / 2.0f, window.Height() / 2.0f, -1.0f, 1.0f);
	m_ShaderProgram.SetMatrix4f("pr_matrix", &prMatrix[0][0]);

	m_EllipseShaderProgram.AttachShader(Shader("Shaders/EllipseVertexShader.glsl", Shader::ShaderType::Vertex));
	m_EllipseShaderProgram.AttachShader(Shader("Shaders/EllipseFragmentShader.glsl", Shader::ShaderType::Fragment));
	m_EllipseShaderProgram.Link();
	m_EllipseShaderProgram.Use();

	// Camera position
	m_EllipseShaderProgram.SetUniform2f("input_position", 0.0f, 0.0f);

	// Set the Camera Projection Matrix
	m_EllipseShaderProgram.SetMatrix4f("pr_matrix", &prMatrix[0][0]);

	// Setup animations
	AnimationFrame *expandPowerup = new AnimationFrame([this](float deltaTime) {
		float width = this->Platform()->Size().x;
		float height = this->Platform()->Size().y;

		if (width >= 198.0f)
		{
			this->Platform()->Size(glm::vec2(200.0f, height));
			return true;
		}

		width = lerp(width, 200, deltaTime * 2);

		this->Platform()->Size(glm::vec2(width, height));

		return false;
	});

	this->m_AnimationSequence.PushFrame(expandPowerup);

	this->m_AnimationSequence.Pause();
}

bool Level::Load()
{
	m_Parser.setSyntax(m_Data);
	if (m_Parser.Parse() == false)
	{
		std::cout << "Failed to parse " << m_Level << std::endl;
		return false;
	}

	m_Primitives = m_Parser.getPrimitives();

	for (int i = 0; i < m_Primitives.size(); i++)
	{
		if (m_Primitives[i]->Is(Tags::RECT))
		{
			auto rect = m_Primitives[i]->Get<Rectangle>();

			if (rect->HasAttribute("powerup"))
			{
				auto value = rect->GetAttribute("powerup");
			}

			if (m_Primitives[i]->id == "platform")
			{
				m_Platform = new PlatformObject(
					glm::vec3(rect->x, rect->y, 0.0f),
					glm::vec2(rect->width, rect->height),
					rect->color
				);

				m_GameObjects.push_back((GameObject*)m_Platform);
			}
			else
			{
				auto block = new BlockObject(
					glm::vec3(rect->x/* + 23*/, rect->y, 0.0f),
					glm::vec2(rect->width, rect->height),
					rect->color
				);

				if (rect->HasAttribute("powerup"))
				{
					auto powerup = rect->GetAttribute("powerup");
					block->PowerUp(powerup);
				}

				m_GameObjects.push_back(block);
			}
		}
		else if (m_Primitives[i]->Is(Tags::ELLIPSE))
		{
			auto ellipse = m_Primitives[i]->Get<Ellipse>();
			m_PolygonalObjects.push_back(ellipse);

			if (m_Primitives[i]->id == "ball")
			{
				m_Ball = new BallObject(
					glm::vec3(ellipse->x, ellipse->y, 0.0f),
					ellipse->color,
					glm::vec2(m_Window.Width(), m_Window.Height()),
					ellipse->rx,
					BALL_VELOCITY
				);
			}

			else if (m_Primitives[i]->id == "ballb")
			{
				m_BallB = new BallObject(
					glm::vec3(ellipse->x, ellipse->y, 0.0f),
					ellipse->color,
					glm::vec2(m_Window.Width(), m_Window.Height()),
					ellipse->rx,
					BALL_VELOCITY
				);
			}
		}
	}

	return true;
}

void Level::Render()
{
	if (m_GameObjects.size())
	{
		m_ShaderProgram.Use();
		m_Renderer.Begin();
		m_Renderer.AddGameObjects(m_GameObjects);
		m_Renderer.End();
		m_Renderer.Render();
	}

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<uint32_t> indices;

	m_EllipseShaderProgram.Use();
	for (const auto& polygon : m_PolygonalObjects)
	{
		if (polygon->name == "ellipse")
		{
			Ellipse* ellipse = (Ellipse*)polygon;

			if (ellipse->id == "ball")
			{
				ellipse->x = m_Ball->Position().x;
				ellipse->y = m_Ball->Position().y;

				ellipse->rx = m_Ball->Radius();
				ellipse->ry = m_Ball->Radius();
			}

			if (ellipse->id == "ballb")
			{
				ellipse->x = m_BallB->Position().x;
				ellipse->y = m_BallB->Position().y;

				ellipse->rx = m_BallB->Radius();
				ellipse->ry = m_BallB->Radius();
			}

			for (int i = 0; i < ellipse->vertices.size(); i++)
			{
				vertices.push_back(
					glm::vec3(
						ellipse->x + ellipse->vertices[i].x * ellipse->rx, 
						ellipse->y + ellipse->vertices[i].y * ellipse->ry, 
						0.0f
					)
				);

				uvs.push_back(glm::vec3(ellipse->uvs[i].x, ellipse->uvs[i].y, 0.0f));
			}

			m_PolygonRenderer.Begin();
			m_PolygonRenderer.AddBatch(vertices, ellipse->indices, ellipse->color, uvs);
			m_PolygonRenderer.End();
			m_PolygonRenderer.Render();

			vertices.clear();
		}
	}
}

GameObject* Level::GetObject(std::string name)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->Name() == name)
		{
			return m_GameObjects[i];
		}
	}

	return nullptr;
}

GameObject* Level::GetObject(int id)
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		if (m_GameObjects[i]->ID() == id)
		{
			return m_GameObjects[i];
		}
	}

	return nullptr;
}

void Level::CheckCollisions(float deltaTime)
{
	static bool powerup = false;
	static bool powerup2 = false;
	static bool powerup3 = false;

	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end();)
	{
		if (*it != this->m_Platform && this->m_Ball->CollidesWith(*it))
		{
			auto block = (BlockObject*)(*it);

			// Powerup
			if (block->PowerUp() == PowerUps::PLATFORM_EXPAND && powerup == false)
			{
				if (this->m_AnimationSequence.IsPaused())
				{
					this->m_AnimationSequence.Unpause();
					this->m_AnimationSequence.Play(deltaTime);
				}

				powerup = true;
			}

			m_BlocksDestroyed++;
			m_GameObjects.erase(it);
			it = m_GameObjects.begin();

			if (m_BlocksDestroyed > 20 && !powerup)
			{
				auto velocity = this->m_Ball->Velocity();

				velocity.x *= 2;
				velocity.y *= 2;
				velocity.z *= 2;

				this->m_Ball->Velocity(velocity);

				powerup = true;
			}

			if (m_BlocksDestroyed > 40 && !powerup2)
			{
				auto velocity = this->m_Ball->Velocity();

				velocity.x *= 2;
				velocity.y *= 2;
				velocity.z *= 2;

				this->m_Ball->Velocity(velocity);

				powerup2 = true;
			}

			if (m_BlocksDestroyed > 60 && !powerup3)
			{
				auto velocity = this->m_Ball->Velocity();

				velocity.x *= 2;
				velocity.y *= 2;
				velocity.z *= 2;

				//this->m_Ball->Velocity(velocity);

				powerup3 = true;
			}

			auto velocity = this->m_Ball->Velocity();

			velocity.y = -velocity.y;
			m_Ball->Velocity( velocity );
			
			// Destroy only one object at a time
			break;
		}
		else
		{
			it++;
		}
	}

	if (m_Platform && !this->m_Ball->OnPlatform() && this->m_Ball->CollidesWith(m_Platform))
	{
		float strength = 2.0f;

		float distance = this->m_Ball->Position().x - this->m_Platform->Position().x;
		float percentage = distance / ( this->m_Platform->Size().x / 2 );

		glm::vec3 oldVelocity = m_Ball->Velocity();
		glm::vec3 newVelocity;

		newVelocity.x = BALL_VELOCITY.x * percentage * strength;
		float absval = std::fabs(oldVelocity.y);
		newVelocity.y = -oldVelocity.y;

		m_Ball->Velocity(glm::normalize(newVelocity) * glm::length(oldVelocity));
	}
}

Level::~Level()
{
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		delete m_GameObjects[i];
		m_GameObjects[i] = nullptr;
	}

	m_GameObjects.clear();
}

}