#include "GameplayScreen.h"

#include <random>
#include <ctime>
#include <DPE/IMainGame.h>

#include "Rat.h"

const float MAX_SCROLL = 5.5f;

const float MIN_SCROLL = 1.5f;

const char* VERT_SRC = R"(#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P;

void main() {
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	
	fragmentColor = vertexColor;
	
	fragmentUV = vec2(vertexUV.x, 1.0-vertexUV.y);
})";

const char* FRAG_SRC = R"(#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;

void main(){

	vec4 textureColor = texture(mySampler, fragmentUV);
	
	color = fragmentColor * textureColor;
})";

GameplayScreen::GameplayScreen(DPE::Window * window) :
	m_window(window),
	m_scrollLevel(1.5f),
	m_difficulty(1),
	m_prevTicks(0.0f)
{
}

GameplayScreen::~GameplayScreen()
{
}

int GameplayScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build()
{
}

void GameplayScreen::destroy()
{
}

void GameplayScreen::onEntry()
{
	m_spriteBatch.init();

	m_debugRender.init();

	m_textureProgram.compileShadersFromSource(VERT_SRC, FRAG_SRC);
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();


	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(1.0f/1.5f);

	//choose a theme of matching difficulty
	if (m_difficulty == 1) {
		static std::mt19937 randomEngine(time(nullptr));
		std::uniform_int_distribution<int> randInt(0, sizeof(LEVEL_ONE) / sizeof(LEVEL_ONE[0]) - 1);
		//choose random theme
		m_level.init(LEVEL_ONE[randInt(randomEngine)]);
	}

	m_badGuys.push_back(new Rat());
	m_badGuys[0]->Spawn(m_level.getStartPos(), m_level.getMap(), m_level.getEntMap());

	m_player.init("Data/Textures/Characters/Mage.png", glm::ivec2(3, 2), &m_game->inputManager, &m_camera, m_level.getStartPos());
}

void GameplayScreen::onExit()
{
	m_spriteBatch.dispose();
	m_textureProgram.dispose();
	m_debugRender.dispose();
	m_level.dispose();

	for (int i = 0; i < m_badGuys.size(); i++) {
		delete m_badGuys[i];
		m_badGuys.erase(m_badGuys.begin() + i);
	}
}

void GameplayScreen::update(){
	
	
	if (!m_prevTicks)
	{
		m_prevTicks = SDL_GetTicks();
	}
	const float DESIRED_FPS = 60.0f;

	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS;

	auto entMap = m_level.getEntMap();
	
	float newTicks = SDL_GetTicks();
	float frameTime = newTicks - m_prevTicks;
	m_prevTicks = newTicks;
	float totalDeltaTime = frameTime / DESIRED_FRAMETIME;

	float deltaTimeMoveFactor = m_player.getDeltaFactor()/* * totalDeltaTime bugs*/;

	m_player.update(deltaTimeMoveFactor, m_level.getMap(), entMap);

	for (int b = 0; b < m_badGuys.size(); b++) {
		m_badGuys[b]->update(deltaTimeMoveFactor, m_level.getMap(), entMap);
	}

	m_level.setEntMap(entMap);

	m_camera.setPosition(m_player.getPosition());

	m_camera.update();
	checkInput();
}

void GameplayScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.use();

	// Upload texture uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_level.draw();

	m_spriteBatch.begin(DPE::GlyphSortType::BACK_TO_FRONT);

	m_player.draw(m_spriteBatch);

	for (int b = 0; b < m_badGuys.size(); b++) {
		m_badGuys[b]->draw(m_spriteBatch);
	}

	m_spriteBatch.end();
	
	m_spriteBatch.renderBatch();
	
	m_debugRender.end();
	m_debugRender.render(projectionMatrix, 2.0f);

	m_textureProgram.unuse();
}

void GameplayScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);

		switch (evnt.type) {
		case SDL_MOUSEWHEEL:
			if (evnt.wheel.y == -1 && m_scrollLevel < MAX_SCROLL)
				m_scrollLevel += 0.5f;
			else if (evnt.wheel.y == 1 && m_scrollLevel > MIN_SCROLL)
				m_scrollLevel -= 0.5f;

			m_camera.setScale(1.0f / m_scrollLevel);
			break;
		}
	}
}