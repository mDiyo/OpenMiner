/*
 * =====================================================================================
 *
 *  OpenMiner
 *
 *  Copyright (C) 2018-2020 Unarelith, Quentin Bazin <openminer@unarelith.net>
 *  Copyright (C) 2019-2020 the OpenMiner contributors (see CONTRIBUTORS.md)
 *
 *  This file is part of OpenMiner.
 *
 *  OpenMiner is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  OpenMiner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with OpenMiner; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 *
 * =====================================================================================
 */
#include <gk/core/Exception.hpp>

#include "Registry.hpp"
#include "TextureAtlas.hpp"

void TextureAtlas::addFile(const std::string &path, const std::string &filename) {
	if (filename.empty()) return;

	auto it = m_textureMap.find(filename);
	if (it != m_textureMap.end())
		return;

	SurfacePtr surface{IMG_Load((path + filename).c_str()), &SDL_FreeSurface};
	if(!surface) {
		DEBUG("WARNING: Failed to load texture:", path + filename);
		return;
	}

	if (!m_tileSize)
		m_tileSize = surface->w;

	if (m_tileSize != surface->w || m_tileSize != surface->h)
		throw EXCEPTION("Texture size unexpected for", path + filename + ". Got", surface->w, surface->h, "instead of", m_tileSize, m_tileSize);

	m_textureMap.emplace(filename, m_textures.size());
	m_textures.emplace_back(std::move(surface));
}

void TextureAtlas::packTextures() {
	if (!m_tileSize)
		throw EXCEPTION("Cannot pack zero-sized textures!");

	SurfacePtr atlas{nullptr, &SDL_FreeSurface};

	// Max amount of textures on one line
	const u16 atlasWidth = 16;

	// Max amount of textures on one column
	const u16 atlasHeight = std::ceil((float)m_textures.size() / atlasWidth);

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	atlas.reset(SDL_CreateRGBSurface(0, atlasWidth * m_tileSize, atlasHeight * m_tileSize, 32, rmask, gmask, bmask, amask));
	if (!atlas) {
		throw EXCEPTION("Failed to create surface:", SDL_GetError());
	}

	u16 i = 0;
	for (auto &it : m_textures) {
		SDL_Rect outRect;
		outRect.x = (i % atlasWidth) * m_tileSize;
		outRect.y = (i / atlasWidth) * m_tileSize;
		outRect.w = m_tileSize;
		outRect.h = m_tileSize;

		SDL_BlitSurface(it.get(), nullptr, atlas.get(), &outRect);

		++i;
	}

	m_textures.clear();

	m_isReady = true;

	if (IMG_SavePNG(atlas.get(), "test_atlas.png") < 0)
		throw EXCEPTION("Failed to save texture to: test_atlas.png. Reason:", IMG_GetError());

	m_texture.loadFromSurface(atlas.get());
}

void TextureAtlas::loadFromRegistry() {
	addFile("mods/default/textures/blocks/", "undefined.png");

	for (auto &block : Registry::getInstance().blocks()) {
		const TilesDef &tiles = block->tiles();
		for (auto &textureFilename : tiles.textureFilenames())
			addFile("mods/" + block->modName() + "/textures/blocks/", textureFilename);
		for (auto &textureFilename : tiles.altTextureFilenames())
			addFile("mods/" + block->modName() + "/textures/blocks/", textureFilename);
	}

	for (auto &item : Registry::getInstance().items()) {
		if (!item.isBlock()) {
			const TilesDef &tiles = item.tiles();
			for (auto &textureFilename : tiles.textureFilenames())
				addFile("mods/" + item.modName() + "/textures/items/", textureFilename);
			for (auto &textureFilename : tiles.altTextureFilenames())
				addFile("mods/" + item.modName() + "/textures/items/", textureFilename);
		}
	}

	packTextures();
}

u16 TextureAtlas::getTextureID(const std::string &filename) const {
	auto it = m_textureMap.find(filename);
	if (it == m_textureMap.end()) {
		return 0;
	}

	return it->second;
}

gk::FloatRect TextureAtlas::getTexCoords(const std::string &filename, bool normalized) const {
	if (filename.empty()) return gk::FloatRect{0, 0, 0, 0};

	if (!m_isReady)
		throw EXCEPTION("Can't get texture coordinates from empty atlas");

	u16 textureID = getTextureID(filename);

	float textureX = (textureID % (m_texture.getSize().x / m_tileSize)) * m_tileSize;
	float textureY = (textureID / (m_texture.getSize().x / m_tileSize)) * m_tileSize;

	if (normalized)
		return gk::FloatRect{textureX / m_texture.getSize().x,
							 textureY / m_texture.getSize().y,
							 (float)m_tileSize / m_texture.getSize().x,
							 (float)m_tileSize / m_texture.getSize().y};
	else
		return gk::FloatRect{textureX,
							 textureY,
							 (float)m_tileSize,
							 (float)m_tileSize};
}

