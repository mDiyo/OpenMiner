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
#ifndef SCENE_H
#define SCENE_H

typedef struct {
	float x;
	float y;
	float z;
} vect3D;

class Scene {
	public:
		Scene();
		~Scene();
		
		void exec();
		
		void manageEvents();
		void animate();
		void draw();
		void display();
		
		void loadTextures();
		void drawField();
		
		void lockMouse();
		void unlockMouse();
		
		static float intersectionLinePlane(vect3D normal, vect3D planePoint, vect3D lineOrigPoint, vect3D directionVector);
		static float intersectionLineCube(int cubeX, int cubeY, int cubeZ, vect3D lineOrigPoint, vect3D directionVector);
		static void testCubes(std::vector<Cube*> cubes);
		
		static Player *player;
		static Biome *biome;
		static Cube *selectedCube;
		
	private:
		typedef std::map<std::string, GLuint> Textures;
		
		bool m_cont;
		Textures m_textures;
};

#endif // SCENE_H