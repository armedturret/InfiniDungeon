#include "InitGameScreen.h"
#include "ScreenIndicies.h"

#include <DPE/IMaingame.h>
#include <DPE/ResourceManager.h>

#include "Console.h"

const char* INIT_VERT_SRC = R"(#version 130

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

const char* INIT_FRAG_SRC = R"(#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D mySampler;

void main(){

	vec4 textureColor = texture(mySampler, fragmentUV);
	
	color = fragmentColor * textureColor;
})";

InitGameScreen::InitGameScreen(DPE::Window * window) :m_window(window)
{
}

InitGameScreen::~InitGameScreen()
{
}

int InitGameScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_GAMEPLAY;
}

int InitGameScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void InitGameScreen::build()
{
}

void InitGameScreen::destroy()
{
}

void InitGameScreen::onEntry()
{
	m_window->changeWindowSettings("Infini-Dungeon",1024,768);
	m_window->toggleSettings(DPE::VSYNC);

	m_textureProgram.compileShadersFromSource(INIT_VERT_SRC, INIT_FRAG_SRC);
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	m_spriteBatch.init();

	m_texture = DPE::ResourceManager::getTexture("Data/Textures/GameLogo.png");

	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScale(1.0f);
}

void InitGameScreen::onExit()
{
	m_spriteBatch.dispose();
	m_textureProgram.dispose();
}

void InitGameScreen::update()
{
	m_animTime += 0.003f;

	m_camera.update();
	checkInput();
	if (Command::getCvar("infi_shouldquit") == "1") {
		m_currentState = DPE::ScreenState::EXIT_APPLICATION;
	}
}

void InitGameScreen::draw()
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

	m_spriteBatch.begin();

	int alpha = 0;
	if (m_game->inputManager.isKeyPressed(SDLK_RETURN) || m_game->inputManager.isKeyPressed(SDLK_SPACE)) {
		alpha = 0;
		m_currentState = DPE::ScreenState::CHANGE_NEXT;
	}
	if (m_animTime <= 1.0f) {
		alpha = 255 * m_animTime;
	}
	else if (m_animTime <= 2.0f) {
		alpha = 255;
	}
	else if (m_animTime <= 3.0f){
		m_animTime += 0.003f;
		alpha = (3.0f - m_animTime) * 255;
	}
	else {
		alpha = 0;
		m_currentState = DPE::ScreenState::CHANGE_NEXT;
	}

	m_spriteBatch.draw(glm::vec4(-(float)m_window->getScreenWidth() / 4.0f, -(float)m_window->getScreenHeight() / 4.0f, (float)m_window->getScreenWidth()/2.0f,  (float)m_window->getScreenHeight()/2.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), m_texture.id, 0.0f, DPE::ColorRGBA8(255, 255, 255, alpha));

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

}

void InitGameScreen::checkInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
	}
}
