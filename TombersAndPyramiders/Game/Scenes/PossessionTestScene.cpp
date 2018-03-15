#include "PossessionTestScene.h"
#include <iostream>
#include <vector>
#include "SpawnManager.h"
#include "Camera.h"
#include "GameManager.h"

/*
New Z Rule:

-10	Floor
-1	Behind-Default
0	Default
1	Above-Default
10	Ceiling

*/

PossessionTestScene::PossessionTestScene()
{
}

void PossessionTestScene::onStart()
{
	GameManager::getInstance()->resizeQuadTree(0, 0, 200, 100);
	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 115, "sandBG.png", false);

	const float size = 6;
	const float scale = 5;

	for (float x = 0; x <= size; x++)
	{
		for (float y = 0; y >= -size; y--)
		{
			float column = x * scale;
			float row = y * scale;
			float floorOffset = 0.56f;
			float wallOffset = 0.0f;

			SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset), (y * -1) - 50, scale, "stoneTile.png", false);

			if (y == 0)
			{
				// Create top left wall.
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallTopLeft_Edge.png", true);
				}
				// Create top right wall.
				else if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallTopRight_Edge.png", true);
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallHorizontal.png", true);
				}
			}
			// Create bottom walls.
			else if (y == -size)
			{
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallBottomLeft.png", true);
				}
				else if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallBottomRight.png", true);
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallHorizontal.png", true);
				}
			}
			// Create a left wall
			else if (x == 0)
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallVerticalBothEdge.png", true);
			}
			// Create a right wall.
			else if (x == size)
			{
				float wallHorizontalOffset = 0.0f;

				SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallVerticalBothEdge.png", true);
			}
		}
	}

	/*for (int x = -20; x < 21; x += 10) {
		auto bg = SpawnManager::getInstance()->generateMiscSquare(x, 0, 0, 10, "stoneTile.png", false);
		bg->getTransform()->setZ(-10);
	}
	for (int x = -20; x < 21; x += 10) {
		auto bg = SpawnManager::getInstance()->generateMiscSquare(x, 0, 0, 10, "stoneTile.png", false);
		bg->getTransform()->setZ(-10);
	}
	for (int x = -21; x < 21; x++) {
		SpawnManager::getInstance()->generateMiscSquare(x, 5, 0, 1, "stoneTile.png", true, 1.0f);
		SpawnManager::getInstance()->generateMiscSquare(x, -5, 0, 1, "stoneTile.png", true, 1.0f);
	}*/
	auto ghostCharacter = SpawnManager::getInstance()->generateGhost(0, 0);
	SpawnManager::getInstance()->generateBoulder(5, 0);
	//SpawnManager::getInstance()->generateAiCharacter(-10, 0);
	//SpawnManager::getInstance()->generateAiCharacter(15, 5);
	Camera::getActiveCamera()->addComponent<CameraFollow>((GameObject*)Camera::getActiveCamera().get())->setToFollow(ghostCharacter);
}

void PossessionTestScene::onPause()
{
}

void PossessionTestScene::onEnd()
{

}

void PossessionTestScene::onUpdate(int ticks)
{
}