#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace DPE {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		void setMouseCoords(float x, float y);

		//Returns true if key held down
		bool isKeyDown(unsigned int keyID);

		//Returns true if key was just down
		bool isKeyPressed(unsigned int keyID);

		//getters
		glm::vec2 getMouseCoords() const { return m_mouseCoords; }
	private:
		//Returns true if key was held down
		bool wasKeyDown(unsigned int keyID);

		std::unordered_map<unsigned int, bool> m_keyMap;
		std::unordered_map<unsigned int, bool> m_previousKeyMap;
		glm::vec2 m_mouseCoords;
	};

}