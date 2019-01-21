/*
 * =====================================================================================
 *
 *       Filename:  ServerWorld.hpp
 *
 *    Description:
 *
 *        Created:  12/01/2019 14:02:07
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SERVERWORLD_HPP_
#define SERVERWORLD_HPP_

#include <memory>
#include <vector>

#include "ServerChunk.hpp"

struct Client;
class Server;

class ServerWorld {
	public:
		ServerWorld();

		void update(Server &server);

		void sendWorldData(Client &client);
		void sendChunkData(Client &client, ServerChunk *chunk);
		void sendRequestedData(Client &client, int cx, int cy, int cz);

		ServerChunk *getChunk(int cx, int cy, int cz) const;

		// FIXME: Duplicated with ClientWorld
		u16 getBlock(int x, int y, int z) const;
		void setBlock(int x, int y, int z, u16 id);

	private:
		// FIXME: Duplicated with those in ClientWorld
		const s32 m_width = 64;
		const s32 m_height = 4;
		const s32 m_depth = 64;

		std::vector<std::unique_ptr<ServerChunk>> m_chunks;
};

#endif // SERVERWORLD_HPP_
