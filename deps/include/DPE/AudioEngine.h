#pragma once

#include <SDL/SDL_mixer.h>
#include <string>
#include <map>

namespace DPE {

	class SoundEffect {
	public:
		friend class AudioEngine;

		void play(int loops = 0, int channel = -1);
	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	class Music {
	public:
		friend class AudioEngine;

		///Plays the audio file
		/// @param loops: if loops == -1 loop forever, otherwise loop the number of times specified
		void play(int loops = 1);

		static void pause();
		static void stop();
		static void resume();
	private:
		Mix_Music* m_music = nullptr;
	};

	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);
	private:

		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;

		bool m_isInitialized = false;
	};

}