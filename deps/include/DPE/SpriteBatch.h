#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <SDL/SDL.h>

#include "Vertex.h"

namespace DPE {
	enum class GlyphSortType{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	class Glyph {
	public:
		Glyph() {};
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& ColorRGBA8);
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& ColorRGBA8, float angle);
		
		GLuint texture;
		float depth;

		Vertex topLeft;
		Vertex bottomLeft;
		Vertex topRight;
		Vertex bottomRight;
	private:
		glm::vec2 rotatePoint(const glm::vec2& pos, float angle);
	};

	class RenderBatch 
	{
	public:
		RenderBatch(GLuint Offset, GLuint NumVerticies, GLuint Texture) :offset(Offset), numVertices(NumVerticies), texture(Texture) {

		}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();
		void dispose();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);

		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle);
		
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir);

		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		GLuint m_vbo;
		GLuint m_vao;

		GlyphSortType m_sortType;

		std::vector<Glyph*> m_glyphPointers;//This is for sorting
		std::vector<Glyph> m_glyphs;//These are the actual glyphs
		std::vector<RenderBatch> m_renderBatches;

	};

}