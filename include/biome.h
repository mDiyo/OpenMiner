/*---------------------------------------------------------------------------------
	
	KubKraft
	Copyright (C) 2012 Quent42340 <quent42340@gmail.com>
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
---------------------------------------------------------------------------------*/
#ifndef BIOME_H
#define BIOME_H

class Biome {
	public:
		Biome(int x, int y, int z, GLuint texture);
		~Biome();
		
		void draw();
		
		void deleteCube(Cube *cube);
		
		int x() const { return m_x; }
		int y() const { return m_y; }
		int z() const { return m_z; }
		
	private:
		int m_x;
		int m_y;
		int m_z;
		
		std::vector<Cube*> m_cubes;
};

#endif // BIOME_H