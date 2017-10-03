#include "GameplayScreen.h"

#include <DPE/IMainGame.h>

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

GameplayScreen::GameplayScreen(DPE::Window * window) : m_window(window)
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

	m_player.init("Data/Textures/Characters/Mage.png", glm::ivec2(2, 2), &m_game->inputManager, 2.0f);

	m_level.init(1);
}

void GameplayScreen::onExit()
{
	m_spriteBatch.dispose();
	m_textureProgram.dispose();
	m_debugRender.dispose();
	m_level.dispose();
}

void GameplayScreen::update(){
	m_player.update(0.0f);

	m_camera.setPosition(glm::vec2(0.0f));

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

	m_level.draw(projectionMatrix, m_textureProgram);

	m_spriteBatch.begin(DPE::GlyphSortType::BACK_TO_FRONT);

	m_player.draw(m_spriteBatch, m_debugRender);

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
	}
}
