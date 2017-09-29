#pragma once

#include<string>

namespace DPE {
	/**
	* \brief Send a fatal error to stop the program.
	*
	*/
	extern void fatalError(std::string errorString);
}