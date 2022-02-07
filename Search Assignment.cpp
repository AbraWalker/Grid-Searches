//Bethany Walker
// Search Assignment.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
#include <memory>
#include "Search.h"
#include "SearchFactory.h"
#include "Definitions.h"

using namespace tle;

string returnCharacterInput(I3DEngine* &myEngine)
{
	if (myEngine->KeyHit(Key_A)) return "a";
	else if (myEngine->KeyHit(Key_B)) return "b";
	else if (myEngine->KeyHit(Key_C)) return "c";
	else if (myEngine->KeyHit(Key_D)) return "d";
	else if (myEngine->KeyHit(Key_E)) return "e";
	else if (myEngine->KeyHit(Key_F)) return "f";
	else if (myEngine->KeyHit(Key_G)) return "g";
	else if (myEngine->KeyHit(Key_H)) return "h";
	else if (myEngine->KeyHit(Key_I)) return "i";
	else if (myEngine->KeyHit(Key_J)) return "j";
	else if (myEngine->KeyHit(Key_K)) return "k";
	else if (myEngine->KeyHit(Key_L)) return "l";
	else if (myEngine->KeyHit(Key_M)) return "m";
	else if (myEngine->KeyHit(Key_N)) return "n";
	else if (myEngine->KeyHit(Key_O)) return "o";
	else if (myEngine->KeyHit(Key_P)) return "p";
	else if (myEngine->KeyHit(Key_Q)) return "q";
	else if (myEngine->KeyHit(Key_R)) return "r";
	else if (myEngine->KeyHit(Key_S)) return "s";
	else if (myEngine->KeyHit(Key_T)) return "t";
	else if (myEngine->KeyHit(Key_U)) return "u";
	else if (myEngine->KeyHit(Key_V)) return "v";
	else if (myEngine->KeyHit(Key_W)) return "w";
	else if (myEngine->KeyHit(Key_X)) return "x";
	else if (myEngine->KeyHit(Key_Y)) return "y";
	else if (myEngine->KeyHit(Key_Z)) return "z";

	else return "";
}

string returnNumberInput(I3DEngine* &myEngine)
{
	if (myEngine->KeyHit(Key_0)) return "0";
	else if (myEngine->KeyHit(Key_1)) return "1";
	else if (myEngine->KeyHit(Key_2)) return "2";
	else if (myEngine->KeyHit(Key_3)) return "3";
	else if (myEngine->KeyHit(Key_4)) return "4";
	else if (myEngine->KeyHit(Key_5)) return "5";
	else if (myEngine->KeyHit(Key_6)) return "6";
	else if (myEngine->KeyHit(Key_7)) return "7";
	else if (myEngine->KeyHit(Key_8)) return "8";
	else if (myEngine->KeyHit(Key_9)) return "9";
	else return "";
}


void quarterSplines(unique_ptr<SNode>& point1, unique_ptr<SNode>& point2, unique_ptr<SNode>& point3, unique_ptr<SNode>& point4,
	unique_ptr<SNode> &quarter, unique_ptr<SNode>& half, unique_ptr<SNode>& threeQuarter)
{
	// calculate a quarter of the way along the set of points
	quarter->x = point1->x * -0.0703125f + point2->x * 0.8671875f +
		point3->x * 0.2265625f + point4->x * -0.0234375f;
	quarter->y = point1->y * -0.0703125f + point2->y * 0.8671875f +
		point3->y * 0.2265625f + point4->y * -0.0234375f;

	// calculate a half of the way along the set of points
	half->x = point1->x * -0.0625f + point2->x * 0.5625f +
		point3->x * 0.5625f + point4->x * -0.0625f;
	half->y = point1->y * -0.0625f + point2->y * 0.5625f +
		point3->y * 0.5625f + point4->y * -0.0625f;

	// calculate three-quarters of the way along the set of points
	threeQuarter->x = point1->x * -0.0234375f + point2->x * 0.2265625f +
		point3->x * 0.8671875f + point4->x * -0.0703125f;
	threeQuarter->y = point1->y * -0.0234375f + point2->y * 0.2265625f +
		point3->y * 0.8671875f + point4->y * -0.0703125f;
}

void doIt(I3DEngine* &myEngine, int &x, int &y, string mapChoice, bool userEnter, NodeList& testList, ESearchType method, int userStartX, int userStartY, int userEndX, int userEndY)
{


	ifstream infile("D:\\BWalker4\\Documents\\Game Dev Assignment\\initial map files\\" + mapChoice + "Map.txt");
	string owo;
	string temp;
	getline(infile, owo);

	TerrainMap test;
	vector<ETerrainCost> line;

	for (int i = 0; i < owo.length(); i++)
	{
		if (owo[i] != ' ')
		{
			temp += owo[i];
		}
		else
		{
			x = stoi(temp);
			temp = "";
		}
	}

	y = stoi(temp);

	for (int i = 0; i < y; i++)             //Loaded squares change colour according to their costs, displaying an 'area'.
	{
		getline(infile, owo);
		for (int j = 0; j < x; j++)
		{
			if (owo[j] == '0')
			{
				line.push_back(Wall);
			}
			else if (owo[j] == '1')
			{
				line.push_back(Clear);
			}
			else if (owo[j] == '2')
			{
				line.push_back(Wood);
			}
			else if (owo[j] == '3')
			{
				line.push_back(Water);
			}
		}

		test.push_back(line);

		line.clear();
	}

	TerrainMap flippedTest;

	for (int i = test.size() - 1; i >= 0; i--)
	{
		flippedTest.push_back(move(test[i]));
	}



	infile.close();
	temp = "";


	bool userCoord = userEnter;
	int coordsX;
	int coordsY;


	unique_ptr <SNode> startBlock(new SNode);
	unique_ptr <SNode> endBlock(new SNode);

	if (!userCoord)
	{

		ifstream infileCoords("D:\\BWalker4\\Documents\\Game Dev Assignment\\initial map files\\" + mapChoice + "Coords.txt");
		string uwu;
		getline(infileCoords, uwu);



		for (int i = 0; i < uwu.length(); i++)
		{
			if (uwu[i] != ' ')
			{
				temp += uwu[i];
			}
			else
			{
				coordsX = stoi(temp);
				temp = "";
			}
		}

		coordsY = stoi(temp);

		startBlock->x = coordsX;
		startBlock->y = coordsY;

		temp = "";

		getline(infileCoords, uwu);

		for (int i = 0; i < uwu.length(); i++)
		{
			if (uwu[i] != ' ')
			{
				temp += uwu[i];
			}
			else
			{
				coordsX = stoi(temp);
				temp = "";
			}
		}

		coordsY = stoi(temp);


		


		endBlock->x = coordsX;
		endBlock->y = coordsY;

	}
	else
	{
		coordsX = userStartX;
		coordsY = userStartY;

		startBlock->x = coordsX;
		startBlock->y = coordsY;


		coordsX = userEndX;
		coordsY = userEndY;

		endBlock->x = coordsX;
		endBlock->y = coordsY;


	}



	startBlock->cost = 1;
	endBlock->cost = 1;																			///////////////////////NEEDS READING FROM////////////////////////

	IMesh* cubeMesh = myEngine->LoadMesh("Cube.x");
	vector<IModel*> across;
	vector<vector<IModel*>> cube;




	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			across.push_back(cubeMesh->CreateModel((j * 12), ((i * 12)), 0));
			if (flippedTest[i][j] == Wall)
			{
				across[j]->SetSkin("brick1.jpg");
			}

			if (flippedTest[i][j] == Clear)
			{
				across[j]->SetSkin("Grass1.jpg");
			}

			if (flippedTest[i][j] == Water)
			{
				across[j]->SetSkin("CueTip.jpg");
			}

			if (flippedTest[i][j] == Wood)
			{
				across[j]->SetSkin("BaizeDark.jpg");
			}
		}

		cube.push_back(across);
		across.clear();
	}





	// The main game loop, repeat until engine is stopped


	ISearch* aStarSearch = NewSearch(method);
	aStarSearch->FindPath(flippedTest, move(startBlock), move(endBlock), testList);


	ofstream outputPath("output" + mapChoice + "Path.txt");


	for (int i = 0; i < testList.size(); i++)
	{
		outputPath << "(" << testList[i]->x << " , " << testList[i]->y << ")" << endl;
	}

	outputPath.close();


	for (int i = 0; i < testList.size(); i++)
	{
		cube[testList[i]->y][testList[i]->x]->SetSkin("RedBall.jpg");
	}
}


void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	/**** Set up your scene here ****/
	enum eGameState
	{
		selectingMethod,
		selectingMap,
		selectingStartX,
		selectingStartY,
		selectingEndX,
		selectingEndY,
		running
	};

	eGameState gameState = selectingMethod;
	ESearchType method = AStar;
	int x;
	int y;

	string mapChoice = "";

	const EKeyCode mapChoice1 = Key_1;
	const EKeyCode mapChoice2 = Key_2;
	const EKeyCode userStartCoords = Key_X;

	ICamera* myCamera;
	myCamera = myEngine->CreateCamera(kManual, 0.0f, 0.0f, 0.0f);

	bool userEnter = false;

	NodeList testList;


	IFont* myFont = myEngine->LoadFont("Jokerman", 36);
	string selectedMap = "";

	int selectedValue = 0;

	bool pathDone = false;
	int userStartX = 0;
	int userStartY = 0;
	int userGoalX = 0;
	int userGoalY = 0;
	string inString = "";

	


	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();


		if (gameState == selectingMethod)
		{
			myFont->Draw("Select Method: ", 10, 10, kWhite);

			if (selectedValue == 0)
			{
				myFont->Draw("AStar", 10, 40, kRed);
				myFont->Draw("Dijkstras", 10, 80);
			}
			else if (selectedValue == 1)
			{
				myFont->Draw("AStar", 10, 40);
				myFont->Draw("Dijkstras", 10, 80, kRed);
			}

			if (myEngine->KeyHit(Key_Down))
			{
				if (selectedValue < 1)
				{
					selectedValue++;
				}
			}
			if (myEngine->KeyHit(Key_Up))
			{
				if (selectedValue > 0)
				{
					selectedValue--;
				}
			}

			if (myEngine->KeyHit(Key_Return))
			{
				if (selectedValue == 0)
				{
					method = AStar;
				}
				else if (selectedValue == 1)
				{
					method = Dijkstra;

				}
				gameState = selectingMap;
			}
			

		}
		else if (gameState == selectingMap)
		{
			if (method == AStar)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("AStar", 10, 40, kWhite);
			}
			else if (method == Dijkstra)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("Dijkstra", 10, 40, kWhite);
			}

			selectedMap = returnCharacterInput(myEngine);

			if (selectedMap != "")
			{
				myFont->Draw("Map: " + selectedMap, 10, 80);
				gameState = selectingStartX;
			}
			else
			{
				myFont->Draw("Map: ", 10, 80);
			}

			



		}
		else if (gameState == selectingStartX)
		{
			if (method == AStar)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("AStar", 10, 40, kWhite);
			}
			else if (method == Dijkstra)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("Dijkstra", 10, 40, kWhite);
			}

			myFont->Draw("Map: " + selectedMap, 10, 80);


			inString = inString + returnNumberInput(myEngine);
			myFont->Draw("Start X: " + inString, 10, 120);
			
			if (myEngine->KeyHit(Key_Return))
			{
				userStartX = stoi(inString);
				inString = "";
				gameState = selectingStartY;
			}
			
			


			

		}
		else if (gameState == selectingStartY)
		{
			if (method == AStar)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("AStar", 10, 40, kWhite);
			}
			else if (method == Dijkstra)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("Dijkstra", 10, 40, kWhite);
			}

			myFont->Draw("Map: " + selectedMap, 10, 80);
			myFont->Draw("Start X: " + to_string(userStartX), 10, 120);

			inString = inString + returnNumberInput(myEngine);
			myFont->Draw("Start Y: " + inString, 10, 160);
			if (myEngine->KeyHit(Key_Return))
			{
				userStartY = stoi(inString);
				inString = "";
				gameState = selectingEndX;
			}
			
		}
		else if (gameState == selectingEndX)
		{
			if (method == AStar)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("AStar", 10, 40, kWhite);
			}
			else if (method == Dijkstra)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("Dijkstra", 10, 40, kWhite);
			}

			myFont->Draw("Map: " + selectedMap, 10, 80);
			myFont->Draw("Start X: " + to_string(userStartX), 10, 120);
			myFont->Draw("Start Y: " + to_string(userStartY), 10, 160);

			inString = inString + returnNumberInput(myEngine);
			myFont->Draw("End X: " + inString, 10, 200);
			if (myEngine->KeyHit(Key_Return))
			{
				userGoalX = stoi(inString);
				inString = "";
				gameState = selectingEndY;
			}
		}
		else if (gameState == selectingEndY)
		{
			if (method == AStar)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("AStar", 10, 40, kWhite);
			}
			else if (method == Dijkstra)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("Dijkstra", 10, 40, kWhite);
			}

			myFont->Draw("Map: " + selectedMap, 10, 80);
			myFont->Draw("Start X: " + to_string(userStartX), 10, 120);
			myFont->Draw("Start Y: " + to_string(userStartY), 10, 160);
			myFont->Draw("End X: " + to_string(userGoalX), 10, 200);
			inString = inString + returnNumberInput(myEngine);
			myFont->Draw("End Y: " + inString, 10, 240);
			if (myEngine->KeyHit(Key_Return))
			{
				userGoalY = stoi(inString);
				inString = "";
				gameState = running;
			}
		}
		else if (gameState == running)
		{



			if (method == AStar)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("AStar", 10, 40, kWhite);
			}
			else if (method == Dijkstra)
			{
				myFont->Draw("Selected Method: ", 10, 10, kWhite);
				myFont->Draw("Dijkstra", 10, 40, kWhite);
			}

			myFont->Draw("Map: " + selectedMap, 10, 80);
			myFont->Draw("Start X: " + to_string(userStartX), 10, 120);
			myFont->Draw("Start Y: " + to_string(userStartY), 10, 160);
			myFont->Draw("End X: " + to_string(userGoalX), 10, 200);
			myFont->Draw("End Y: " + to_string(userGoalY), 10, 240);

			if (!pathDone)
			{
				testList.clear();
				userEnter = true;
				doIt(myEngine, x, y, selectedMap, userEnter, testList, method, userStartX, userStartY, userGoalX, userGoalY);
				pathDone = true;
			}

			myCamera->SetPosition((x * 5), (y * 5), -200);

			if (myEngine->KeyHit(Key_C))
			{
				for (int i = 0; i < testList.size() - 1; i++)
				{
					unique_ptr <SNode> first(new SNode);
					unique_ptr <SNode> second(new SNode);
					unique_ptr <SNode> third(new SNode);

					quarterSplines(testList[i], testList[i], testList[i + 1], testList[i + 1], first, second, third);

					IMesh* sphereMesh = myEngine->LoadMesh("Sphere.x");
					IModel* sphere1 = sphereMesh->CreateModel(first->x * 12, first->y * 12, -10.0f);
					IModel* sphere2 = sphereMesh->CreateModel(second->x * 12, second->y * 12, -10.0f);
					IModel* sphere3 = sphereMesh->CreateModel(third->x * 12, third->y * 12, -10.0f);

					sphere1->Scale(0.1f);
					sphere2->Scale(0.1f);
					sphere3->Scale(0.1f);

				}

			}
			// Close the program
			
		}
		// Close the program
		if (myEngine->KeyHit(Key_Escape))
		{
			myEngine->Stop();
		}






		/**** Update your scene each frame here ****/


	}

	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}
