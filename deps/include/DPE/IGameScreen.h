#pragma once

#define SCREEN_INDEX_NO_SCREEN -1

namespace DPE {

	class IMainGame;

	enum class ScreenState {
		NONE,
		RUNNING,
		EXIT_APPLICATION,
		CHANGE_NEXT,
		CHANGE_PREVIOUS
	};

	class IGameScreen
	{
	public:
		friend class ScreenList;
		IGameScreen() {

		}
		virtual ~IGameScreen() {

		}

		//Return index of next or prev screen when changing
		virtual int getNextScreenIndex() const = 0;
		virtual int getPreviousScreenIndex() const = 0;


		//called at begining and end of app.
		virtual void build() = 0;
		virtual void destroy() = 0;
		
		//called during entry and exit of focus
		virtual void onEntry() = 0;
		virtual void onExit() = 0;


		virtual void update() = 0;
		virtual void draw() = 0;

		int getScreenIndex() const {
			return m_screenIndex;
		}
		
		ScreenState getState()const {
			return m_currentState;
		}

		void setRunning() {
			m_currentState = ScreenState::RUNNING;
		}

		void setParentGame(IMainGame* game) { m_game = game; }

	protected:
		ScreenState m_currentState = ScreenState::NONE;
		IMainGame* m_game = nullptr;

		int m_screenIndex = -1;
	};

}