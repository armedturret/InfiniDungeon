#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
namespace DPE {
	enum windowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };
	enum toggleFlags {VSYNC = 0x8};

	class Window
	{
	public:
		Window();
		~Window();

		/**
		* \brief Create the application's window.
		*/
		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		void changeWindowSettings(std::string windowName, int screenWidth, int screenHeight);

		void setWindowIcon(const char* filePath);

		void toggleSettings(unsigned int toggleFlags);

		/**
		* \brief swap windows at end of frame.
		*/
		void swapBuffer();

		/**
		* \brief Get the screen's width.
		*/
		int getScreenWidth() { return m_screenWidth; }

		/**
		* \brief Get the screen's height.
		*/
		int getScreenHeight() { return m_screenHeight; }

	private:
		SDL_Window* m_sdlWindow;
		SDL_Surface* m_sdlSurface;

		int m_screenWidth, m_screenHeight;

		bool m_isFullscreen;
		bool m_isBorderless;
		bool m_usesVSync;
		bool m_isInvisible;

	};
}
