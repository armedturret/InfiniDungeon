#pragma once
#include "Sprite.h"
#include "Window.h"
#include "GLTexture.h"
#include "GLSLProgram.h"
#include "DPEErrors.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Timing.h"

/* 
*	Divide by Pixel Engine (DPE) is Copyright(c) Bad Byte Games and is licensed under the following agreement
*	
*	All DPE files in the 'DPE' include directory are copyright Bad Byte Games and the other copyrighted material has their corresponding notices in each folder
*
*	This software is provided 'as-is', without any express or implied
*	warranty. In no event will the authors be held liable for any damages
*	arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
*	Any abuse of the regulations will require a 10% royalty fee to be applied to sales in any commercial usage.
*
*	Robert J. White holds the right to rescend any rights of usage of the engine.
*
*	Use for any military purposes will make a bunny unhappy.
*
*/
namespace DPE {
	/**
	* /brief Initiate the settings of the Divide by Pixel Engine.
	* 
	*/
	extern int init();
}