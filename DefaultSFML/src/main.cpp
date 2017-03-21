#include <iostream>

#include <fstream>
#include <sstream>

#include <SFML\Graphics.hpp>

#include "Profile.h"
#include "Button.h"
#include "Overlay.h"
#include "TextBox.h"
#include "Game.h"

using namespace std;
using namespace sf;

void mainMenu(bool tutorial);
void profileMenu(bool tutorial);
void settingsMenu(bool tutorial);
void editor();

bool DEBUGMODE = true;
Profile player;


int tutorialState = 0;

int main()
{
	//luanch game
	if (DEBUGMODE) cout << "Luanching Game" << endl;

	//open profile list
	fstream file;
	string lineData;
	string tempProfile;
	vector<string> profileNames;

	file.open("Assets/profiles/profileList.txt");
	if (DEBUGMODE) cout << "opening Profile list" << endl;
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream iss(lineData);
			iss.str(lineData);
			iss >> tempProfile;
			profileNames.push_back(tempProfile);
		}
	}
	else
	{
		cout << "Couldnt Open file ... Assets/profiles/profileList.txt" << endl;
	}

	file.close();
	if (DEBUGMODE) cout << "Profile list closed" << endl;
	if (DEBUGMODE) cout << "Profiles present : " << profileNames.size() << endl;
	//check to see if any profiles were present
	if (profileNames.size() > 0)
	{
		// luanch profileMenu in normal mode
		player = Profile("default.txt");
		tutorialState = 11;
		profileMenu(false);
	}
	else
	{
		if (DEBUGMODE) cout << "Tutorial mode" << endl;
		if (DEBUGMODE) cout << "Loading Default profile" << endl;
		player = Profile("default.txt");
		if (DEBUGMODE) cout << "Default profile loaded" << endl;
		// luanch menu in tutorial mode
		
		mainMenu(true);
	}
	
	return 0;
}

void mainMenu(bool tutorial)
{
	Texture mainMenuBackgroundTex;
	if (!mainMenuBackgroundTex.loadFromFile("Assets/textures/menuScreen.png"))
	{
		cout << "Error: menuScreen.png was unable to load.";
	};

	if (tutorial)
	{
		//default.txt is now the profile
		//create main menu assets ......................
	

		//main menu background-------------------------
		RectangleShape mainMenuBackgroundRect;
		Sprite mainMenuBackgroundSprite;
		
		mainMenuBackgroundRect.setPosition(0, 0);
		mainMenuBackgroundRect.setSize(Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));
		mainMenuBackgroundRect.setFillColor(Color::Blue);

		mainMenuBackgroundSprite.setTexture(mainMenuBackgroundTex);
		mainMenuBackgroundSprite.setScale(Vector2f(1, 1));
		mainMenuBackgroundSprite.setPosition(mainMenuBackgroundRect.getPosition());


		//Create buttons-------------------------
		Vector2f resolutionScale(player.m_sfResolution.x / 1280, player.m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player.m_sfResolution.x / 2) - (buttonSize.x / 2), (player.m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Main Menu");
		title.setCharacterSize(50*resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Button play("Play", Vector2f(middleOfScreen.x, 100 * resolutionScale.y), buttonSize, "Button_Grey");
		Button profile("Profile", Vector2f(middleOfScreen.x, 250 * resolutionScale.y), buttonSize, "Button_Green");
		Button settings("Settings", Vector2f(middleOfScreen.x, 400 * resolutionScale.y), buttonSize, "Button_Grey");
		Button quit("Quit", Vector2f(middleOfScreen.x, 550 * resolutionScale.y), buttonSize, "Button_Grey");
	
		
		Button profileGrey("Profile", Vector2f(middleOfScreen.x, 250 * resolutionScale.y), buttonSize, "Button_Grey");
		Button settingsGreen ("Settings", Vector2f(middleOfScreen.x, 400 * resolutionScale.y), buttonSize, "Button_Green");
		
		Vector2f middleOfScreenOverlay(player.m_sfResolution.x / 2 -  (250 * resolutionScale.x), player.m_sfResolution.y / 2 - (250 * resolutionScale.y));

		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tWelcome to Traffic Management !\n\t Please click on Profiles\n\n\n(Click on messages like this to close them)");
		Overlay secondOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tYou have now created your profile!\n\t Please click on settings\n\n\n");
		if (tutorialState >= 6) firstOverlayMessage.m_bDraw = false;
		secondOverlayMessage.m_bDraw = false;
		if (tutorialState == 6)secondOverlayMessage.m_bDraw = true;

		RenderWindow window(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);


		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{
				
				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				
				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (settingsGreen.m_bClicked(sfMousePos) && tutorialState == 7)
						{
							//close and open profile menu
							tutorialState = 8;  
							window.close();
							settingsMenu(true);

						}
						if (secondOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 6)
						{
							
							tutorialState = 7;
							secondOverlayMessage.m_bDraw = false;

						}
						if (profile.m_bClicked(sfMousePos) && tutorialState == 1)
						{
							//close and open profile menu
							tutorialState = 2;
							window.close();
							profileMenu(true);

						}
						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 0)
						{
							firstOverlayMessage.m_bDraw = false;
							tutorialState = 1;
							
						}

						
					}
				}
			}


			window.clear(Color::Green);

			window.draw(mainMenuBackgroundSprite);
			window.draw(title);
			
			// buttons
			window.draw(play);
			window.draw(profile);
			if (tutorialState == 7)
			{
				window.draw(profileGrey);
			}
			else
			{
				window.draw(profile);
			}
			if (tutorialState == 7)
			{
				window.draw(settingsGreen);
		
			}
			else
			{
				window.draw(settings);
			}
			window.draw(quit);

			// first overlay
			window.draw(firstOverlayMessage);
			window.draw(secondOverlayMessage);
			window.display();
		}

	}
	else if (!tutorial)
	{
		//we now have a profile
		//create main menu assets ......................
		player.loadProfile(player.m_sProfileName);

		//main menu background-------------------------
		RectangleShape mainMenuBackgroundRect;
		Sprite mainMenuBackgroundSprite;
	
		mainMenuBackgroundRect.setPosition(0, 0);
		mainMenuBackgroundRect.setSize(Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));
		mainMenuBackgroundRect.setFillColor(Color::Blue);

		mainMenuBackgroundSprite.setTexture(mainMenuBackgroundTex);
		mainMenuBackgroundSprite.setScale(Vector2f(1, 1));
		mainMenuBackgroundSprite.setPosition(mainMenuBackgroundRect.getPosition());


		//Create buttons-------------------------
		Vector2f resolutionScale(player.m_sfResolution.x / 1280, player.m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player.m_sfResolution.x / 2) - (buttonSize.x / 2), (player.m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Main Menu");
		title.setCharacterSize(50 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Button play("Play", Vector2f(middleOfScreen.x, 100 * resolutionScale.y), buttonSize, "Button_Green");
		Button profile("Profile", Vector2f(middleOfScreen.x, 250 * resolutionScale.y), buttonSize, "Button_Green");
		Button settings("Settings", Vector2f(middleOfScreen.x, 400 * resolutionScale.y), buttonSize, "Button_Green");
		Button quit("Quit", Vector2f(middleOfScreen.x, 550 * resolutionScale.y), buttonSize, "Button_Green");

		Vector2f middleOfScreenOverlay(player.m_sfResolution.x / 2 - (250 * resolutionScale.x), player.m_sfResolution.y / 2 - (250 * resolutionScale.y));
		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tYou have now finished the tutorial! \n\nClick play to start playing");
		if (tutorialState == 11)firstOverlayMessage.m_bDraw = false;

		RenderWindow window;
		if (player.m_bFullscreen == true) window.create(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Main Menu", Style::Fullscreen);
		else window.create(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Main Menu");

		


		window.setFramerateLimit(60);
		

		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
					
						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 10)
						{
							firstOverlayMessage.m_bDraw = false;
							tutorialState = 11; // finished

						}
						if (play.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close();
							editor();

						}
						if (settings.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close();
							settingsMenu(false);

						}
						if (profile.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close();
							profileMenu(false);

						}
						if (quit.m_bClicked(sfMousePos) && tutorialState == 11)
						{
							window.close(); // Allows window to close when 'X' is pressed
							return;

						}
					}
				}
			}


			window.clear(Color::Green);

			window.draw(mainMenuBackgroundSprite);
			window.draw(title);

			// buttons
			window.draw(play);
			window.draw(profile);
			window.draw(settings);
			window.draw(quit);

			// first overlay
			window.draw(firstOverlayMessage);
			window.display();
		}

	}

}

void profileMenu(bool tutorial)
{
	Texture profileBackgroundTex;
	if (!profileBackgroundTex.loadFromFile("Assets/textures/menuScreen.png"))
	{
		cout << "Error: menuScreen.png was unable to load.";
	};

	if (tutorial)
	{
		//for profile screen
		// enter at tutorial state 2
		// after close message tutorial state 3
		// after click new tutorial sate 4
		

		//create profile assets ......................

		//profile background-------------------------
		RectangleShape profileBackgroundRect;
		Sprite profileBackgroundSprite;


		profileBackgroundRect.setPosition(0, 0);
		profileBackgroundRect.setSize(Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));
		profileBackgroundRect.setFillColor(Color::Blue);

		profileBackgroundSprite.setTexture(profileBackgroundTex);
		profileBackgroundSprite.setScale(Vector2f(1, 1));
		profileBackgroundSprite.setPosition(profileBackgroundRect.getPosition());



		//Create buttons-------------------------
		Vector2f resolutionScale(player.m_sfResolution.x / 1280, player.m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player.m_sfResolution.x / 2) - (buttonSize.x / 2), (player.m_sfResolution.y / 2) - (buttonSize.y / 2));

		Button New("New", Vector2f(middleOfScreen.x - buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, "Button_Green");
		Button Select("Select", Vector2f(middleOfScreen.x , 100 + middleOfScreen.y *resolutionScale.y), buttonSize, "Button_Grey");
		Button Delete("Delete", Vector2f(middleOfScreen.x + buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, "Button_Grey");


		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Profiles");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));
	
		//Enter you name Sprite
		RectangleShape listOfProfilesRect;
		Sprite listOfProfilesSprite;
		Texture listOfProfilesTex;
		if (!listOfProfilesTex.loadFromFile("Assets/textures/profileMenuEmpty.png"))
		{
			cout << "Error: ProfileEnterBackground.png was unable to load.";
		};
		listOfProfilesRect.setPosition(Vector2f(middleOfScreen.x - buttonSize.x , -120 + middleOfScreen.y * resolutionScale.y));
		listOfProfilesRect.setSize(Vector2f(buttonSize.x * 3, 240 * resolutionScale.y));
		listOfProfilesRect.setFillColor(Color::Blue);

		listOfProfilesSprite.setTexture(listOfProfilesTex);
		listOfProfilesSprite.setScale(Vector2f( 1 * resolutionScale.x , 1 * resolutionScale.y ));
		listOfProfilesSprite.setPosition(listOfProfilesRect.getPosition());

		//Enter you name Sprite
		RectangleShape nameEntryRect;
		Sprite nameEntrySprite;
		Texture nameEntryTex;
		if (!nameEntryTex.loadFromFile("Assets/textures/ProfileEnterBackground.png"))
		{
			cout << "Error: ProfileEnterBackground.png was unable to load.";
		};
		nameEntryRect.setPosition((player.m_sfResolution.x /2) - (579 /2 * resolutionScale.x), (player.m_sfResolution.y / 2) - (144 / 2 * resolutionScale.y));
		nameEntryRect.setSize(Vector2f(579 * resolutionScale.x, 144*resolutionScale.y));
		nameEntryRect.setFillColor(Color::Blue);

		nameEntrySprite.setTexture(nameEntryTex);
		nameEntrySprite.setScale(Vector2f(1 * resolutionScale.x, 1 * resolutionScale.y));
		nameEntrySprite.setPosition(nameEntryRect.getPosition());

		//create text box 
		Vector2f edgeOfTextBox(nameEntryRect.getPosition().x + (579 * resolutionScale.x) / 8, nameEntryRect.getPosition().y + (144 * resolutionScale.y) / 2);
		TextBox playerEnterNameBox("", edgeOfTextBox , Vector2f(343*resolutionScale.x, 37*resolutionScale.y), "Textbox");
		Button Submit("Submit", Vector2f(edgeOfTextBox.x + 343 * resolutionScale.x, edgeOfTextBox.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");

		//create overlays
		Vector2f middleOfScreenOverlay(player.m_sfResolution.x / 2 - (300 * resolutionScale.x), player.m_sfResolution.y / 2 - (300 * resolutionScale.y));
		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tWelcome to the Profile Menu !\n\t There are currently no profiles available.\n\n\n Please click New to create a profile.");
		Overlay secondOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tPlease enter your name into the box !\n\t And click submit when your finished.");
		

		firstOverlayMessage.m_bDraw = true;
		secondOverlayMessage.m_bDraw = false;
		
		RenderWindow window(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);

		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}
			
				if (event.type == sf::Event::KeyPressed && playerEnterNameBox.m_bIsEntering == true)
				{
					playerEnterNameBox.takeInput(event.key.code);
				}


				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (tutorialState == 5 && Submit.m_bClicked(sfMousePos))
						{
							tutorialState = 6;
							//create a new profile with there name
							player = Profile(playerEnterNameBox.m_sText,true);

							player.loadProfile(playerEnterNameBox.m_sText);
							window.close();
							mainMenu(true);
						}

						if (playerEnterNameBox.m_bClicked(sfMousePos) && tutorialState == 5)
						{
							playerEnterNameBox.m_bIsEntering = true;
						}

						if (secondOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 4)
						{
							tutorialState = 5;
						}
						if (New.m_bClicked(sfMousePos) && tutorialState == 3)
						{
							//change profile menu state
							tutorialState = 4;
						}
						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 2)
						{
							tutorialState = 3;
						}


					}
				}
			}


			window.clear(Color::Green);
			window.draw(profileBackgroundSprite);
		
			window.draw(title);

			// buttons
			if (tutorialState != 4 && tutorialState != 5)
			{
				window.draw(listOfProfilesSprite);
				window.draw(New);
				window.draw(Select);
				window.draw(Delete);
			}
			else // enter player name
			{
				
				window.draw(nameEntrySprite);
				window.draw(playerEnterNameBox);
				window.draw(Submit);
			}

			if(tutorialState == 3)firstOverlayMessage.m_bDraw = false;
			if (tutorialState == 4)secondOverlayMessage.m_bDraw = true;
			if (tutorialState == 5)secondOverlayMessage.m_bDraw = false;

			// overlays		
			window.draw(firstOverlayMessage);
			window.draw(secondOverlayMessage);


			window.display();
		}

	}
	else if (!tutorial)
	{
		
		//create profile assets ......................

		//profile background-------------------------
		RectangleShape profileBackgroundRect;
		Sprite profileBackgroundSprite;
		
		profileBackgroundRect.setPosition(0, 0);
		profileBackgroundRect.setSize(Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));
		profileBackgroundRect.setFillColor(Color::Blue);

		profileBackgroundSprite.setTexture(profileBackgroundTex);
		profileBackgroundSprite.setScale(Vector2f(1, 1));
		profileBackgroundSprite.setPosition(profileBackgroundRect.getPosition());



		//Create buttons-------------------------
		Vector2f resolutionScale(player.m_sfResolution.x / 1280, player.m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player.m_sfResolution.x / 2) - (buttonSize.x / 2), (player.m_sfResolution.y / 2) - (buttonSize.y / 2));

		Button New("New", Vector2f(middleOfScreen.x - buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, "Button_Green");
		Button Select("Select", Vector2f(middleOfScreen.x, 100 + middleOfScreen.y *resolutionScale.y), buttonSize, "Button_Green");
		Button Delete("Delete", Vector2f(middleOfScreen.x + buttonSize.x, 100 + middleOfScreen.y * resolutionScale.y), buttonSize, "Button_Green");


		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Profiles");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		//Enter you name Sprite
		RectangleShape listOfProfilesRect;
		Sprite listOfProfilesSprite;
		Texture listOfProfilesTex;
		if (!listOfProfilesTex.loadFromFile("Assets/textures/profileMenu.png"))
		{
			cout << "Error: ProfileEnterBackground.png was unable to load.";
		};
		listOfProfilesRect.setPosition(Vector2f(middleOfScreen.x - buttonSize.x, -120 + middleOfScreen.y * resolutionScale.y));
		listOfProfilesRect.setSize(Vector2f(buttonSize.x * 3, 240 * resolutionScale.y));
		listOfProfilesRect.setFillColor(Color::Blue);

		listOfProfilesSprite.setTexture(listOfProfilesTex);
		listOfProfilesSprite.setScale(Vector2f(1 * resolutionScale.x, 1 * resolutionScale.y));
		listOfProfilesSprite.setPosition(listOfProfilesRect.getPosition());

		
		//create text box 
		Vector2f edgeOfTextBox(listOfProfilesRect.getPosition().x , listOfProfilesRect.getPosition().y + (144 * resolutionScale.y) / 2);
		TextBox playerEnterNameBox("Enter profile name", edgeOfTextBox, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
	

		RenderWindow window(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);

		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}

				if (event.type == sf::Event::KeyPressed && playerEnterNameBox.m_bIsEntering == true)
				{
					playerEnterNameBox.takeInput(event.key.code);
				}


				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (Select.m_bClicked(sfMousePos))
						{
							player.loadProfile(playerEnterNameBox.m_sText);
							window.close();
							mainMenu(false);
							
						}

						if (Delete.m_bClicked(sfMousePos))
						{
							// open profile list
							fstream file;
							string lineData;
							string tempProfile;
							vector<string> profileNames;

							file.open("Assets/profiles/profileList.txt");
							if (DEBUGMODE) cout << "opening Profile list" << endl;
							if (file.is_open())
							{
								while (getline(file, lineData))
								{
									istringstream iss(lineData);
									iss.str(lineData);
									iss >> tempProfile;
									profileNames.push_back(tempProfile);
								}
							}
							else
							{
								cout << "Couldnt Open file ... Assets/profiles/profileList.txt" << endl;
							}

							file.close();

							//search vector of names for what was entered
							for (int i = 0; i < profileNames.size(); i++)
							{
								if (profileNames[i] == playerEnterNameBox.m_sText+".txt")
								{
									//remove the name
									profileNames.erase(profileNames.begin() + i);
								}
							}



							//ammend profile list
							ofstream ofile;
							ofile.open("Assets/profiles/profileList.txt");

							for (int i = 0; i < profileNames.size(); i++)
							{
								ofile << profileNames[i] << endl;
							}

							window.close();
							profileMenu(false);
						}

						if (playerEnterNameBox.m_bClicked(sfMousePos) )
						{
							playerEnterNameBox.m_bIsEntering = true;
						}

						
						if (New.m_bClicked(sfMousePos))
						{
							//create a new profile with there name
							player = Profile(playerEnterNameBox.m_sText, true);

							player.loadProfile(playerEnterNameBox.m_sText);
							window.close();
							mainMenu(false);
						
						}
						


					}
				}
			}


			window.clear(Color::Green);
			window.draw(profileBackgroundSprite);
			
			window.draw(title);
			window.draw(listOfProfilesSprite);
			window.draw(playerEnterNameBox);
			window.draw(New);
			window.draw(Select);
			window.draw(Delete);
			window.display();
		}

	}

}

void settingsMenu(bool tutorial)
{
	if (tutorial)
	{
		//default.txt is now the profile
		//create main menu assets ......................


		//main menu background-------------------------
		RectangleShape settingsBackgroundRect;
		Sprite settingsBackgroundSprite;
		Texture settingsBackgroundTex;
		if (!settingsBackgroundTex.loadFromFile("Assets/textures/menuScreen.png"))
		{
			cout << "Error: menuScreen.png was unable to load.";
		};
		settingsBackgroundRect.setPosition(0, 0);
		settingsBackgroundRect.setSize(Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));
		settingsBackgroundRect.setFillColor(Color::Blue);

		settingsBackgroundSprite.setTexture(settingsBackgroundTex);
		settingsBackgroundSprite.setScale(Vector2f(1, 1));
		settingsBackgroundSprite.setPosition(settingsBackgroundRect.getPosition());

		RectangleShape settingsRect;
		Sprite settingsSprite;
		Texture settingsTex;
		if (!settingsTex.loadFromFile("Assets/textures/settingsWindow.png"))
		{
			cout << "Error: menuScreen.png was unable to load.";
		};
		settingsRect.setPosition(player.m_sfResolution.x /8, player.m_sfResolution.y / 8);
		settingsRect.setSize(Vector2f(player.m_sfResolution.x * 0.75, player.m_sfResolution.y * 0.75));
		settingsRect.setFillColor(Color::Blue);

		settingsSprite.setTexture(settingsTex);
		settingsSprite.setScale(Vector2f(player.m_sfResolution.x * 0.75 / 960    , player.m_sfResolution.y * 0.75 / 302));
		settingsSprite.setPosition(settingsRect.getPosition());

		//Create buttons-------------------------
		Vector2f resolutionScale(player.m_sfResolution.x / 1280, player.m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player.m_sfResolution.x / 2) - (buttonSize.x / 2), (player.m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Settings");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Vector2f middleOfScreenOverlay(player.m_sfResolution.x / 2 - (250 * resolutionScale.x), player.m_sfResolution.y / 2 - (250 * resolutionScale.y));

		//create text box 
		Vector2f TextBoxStart(180 * resolutionScale.x , 220 * resolutionScale.y );
		string s;
		s = to_string(player.m_iGameAudioVolume);

		TextBox gameVolume("Game Volume " +s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button gameVolumeSubmit("Submit", Vector2f(TextBoxStart.x + 343 , TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;
		s = to_string(player.m_iMusicAudioVolume);

		TextBox musicVolume("Music Volume " +s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button musicVolumeSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;
		s = to_string(player.m_iInterfaceAudioVolume);


		TextBox interfaceVolume("Interface Volume " +s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button interfaceVolumeSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y = 220;
		TextBoxStart.x = 240 + player.m_sfResolution.x / 3;

		s = to_string(player.m_sfResolution.x);
		

		TextBox resolutionX("Resolution : x " +s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionXSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;

		s = to_string(player.m_sfResolution.y);
		TextBox resolutionY("Resolution : y " +s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionYSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;

		
		if (player.m_bFullscreen == true) s = "Yes";
		if (player.m_bFullscreen == false) s = "No";

		TextBox fullScreen("Fullscreen Mode " +s , TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button fullScreenSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;

		Button Save("Save", Vector2f(settingsRect.getPosition().x, settingsRect.getPosition().y + settingsBackgroundRect.getSize().y - 2 * buttonSize.y), buttonSize, "Button_Green");
		Button Reset("Reset", Vector2f(settingsRect.getPosition().x + 1.5 * buttonSize.x, settingsRect.getPosition().y + settingsBackgroundRect.getSize().y - 2 * buttonSize.y), buttonSize, "Button_Grey");
		Button Cancel("Cancel", Vector2f(settingsRect.getPosition().x + 3 * buttonSize.x, settingsRect.getPosition().y + settingsBackgroundRect.getSize().y - 2 * buttonSize.y), buttonSize, "Button_Grey");


		Overlay firstOverlayMessage(middleOfScreenOverlay, Vector2f(500 * resolutionScale.x, 500 * resolutionScale.y), "\tWelcome to the settings screen !\n\t Here you can alter any settings you wish\n\n\n Click save when your done.");

		RenderWindow window(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);


		while (window.isOpen())
		{
			 
			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}

				if (event.type == sf::Event::KeyPressed && tutorialState == 9)
				{
					gameVolume.takeInput(event.key.code);
					musicVolume.takeInput(event.key.code);
					interfaceVolume.takeInput(event.key.code);
					resolutionX.takeInput(event.key.code);
					resolutionY.takeInput(event.key.code);
					fullScreen.takeInput(event.key.code);


				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (tutorialState == 9 && Save.m_bClicked(sfMousePos))
						{
							player.saveProfile();
							window.close();
							tutorialState = 10;
							mainMenu(false);

						}
						if (tutorialState == 9  );
						{
							if (gameVolume.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = true;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (musicVolume.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = true;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (interfaceVolume.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = true;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (resolutionX.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = true;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = false;
							}
							if (resolutionY.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = true;
								fullScreen.m_bIsEntering = false;
							}
							if (fullScreen.m_bClicked(sfMousePos))
							{
								gameVolume.m_bIsEntering = false;
								musicVolume.m_bIsEntering = false;
								interfaceVolume.m_bIsEntering = false;
								resolutionX.m_bIsEntering = false;
								resolutionY.m_bIsEntering = false;
								fullScreen.m_bIsEntering = true;
							}
						
						}

						if (tutorialState == 9 && fullScreenSubmit.m_bClicked(sfMousePos))
						{
							if (fullScreen.m_sText == "yes")	player.m_bFullscreen = true;
							else if (fullScreen.m_sText == "no")	player.m_bFullscreen = false;
							else player.m_bFullscreen = false;
							
							
						}
						if (tutorialState == 9 && gameVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = gameVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 10)
							{
								player.m_iGameAudioVolume = value;
							}
						}
						
						if (tutorialState == 9 && musicVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = musicVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 10)
							{
								player.m_iMusicAudioVolume = value;
							}

						}

						if (tutorialState == 9 && interfaceVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = interfaceVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 10)
							{
								player.m_iInterfaceAudioVolume = value;
							}

						}
						if (tutorialState == 9 && resolutionXSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionX.m_sText;
							int value = atoi(input.c_str()); 
							if (value >= 800 && value <= 3840)
							{
								player.m_sfResolution.x = value;
							}
						}
						if (tutorialState == 9 && resolutionYSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionY.m_sText;
							int value = atoi(input.c_str());
							if (value >= 600 && value <= 2160)
							{
								player.m_sfResolution.y = value;
							}
						}

						if (firstOverlayMessage.m_bClicked(sfMousePos) && tutorialState == 8)
						{
							firstOverlayMessage.m_bDraw = false;
							tutorialState = 9;

						}

					}
				}
			}


			


			window.clear(Color::Green);

			window.draw(settingsBackgroundSprite);
			window.draw(settingsSprite);
			window.draw(title);

			// buttons
			window.draw(gameVolume);
			window.draw(gameVolumeSubmit);
			window.draw(interfaceVolume);
			window.draw(interfaceVolumeSubmit);
			window.draw(musicVolume);
			window.draw(musicVolumeSubmit);

			window.draw(resolutionX);
			window.draw(resolutionXSubmit);
			window.draw(resolutionY);
			window.draw(resolutionYSubmit);
			window.draw(fullScreen);
			window.draw(fullScreenSubmit);

			window.draw(Save);
			window.draw(Reset);
			window.draw(Cancel);

			// first overlay
			window.draw(firstOverlayMessage);
		
			window.display();
		}

	}
	else
	{
		//default.txt is now the profile
		//create main menu assets ......................


		//main menu background-------------------------
		RectangleShape settingsBackgroundRect;
		Sprite settingsBackgroundSprite;
		Texture settingsBackgroundTex;
		if (!settingsBackgroundTex.loadFromFile("Assets/textures/menuScreen.png"))
		{
			cout << "Error: menuScreen.png was unable to load.";
		};
		settingsBackgroundRect.setPosition(0, 0);
		settingsBackgroundRect.setSize(Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));
		settingsBackgroundRect.setFillColor(Color::Blue);

		settingsBackgroundSprite.setTexture(settingsBackgroundTex);
		settingsBackgroundSprite.setScale(Vector2f(1, 1));
		settingsBackgroundSprite.setPosition(settingsBackgroundRect.getPosition());

		RectangleShape settingsRect;
		Sprite settingsSprite;
		Texture settingsTex;
		if (!settingsTex.loadFromFile("Assets/textures/settingsWindow.png"))
		{
			cout << "Error: menuScreen.png was unable to load.";
		};
		settingsRect.setPosition(player.m_sfResolution.x / 8, player.m_sfResolution.y / 8);
		settingsRect.setSize(Vector2f(player.m_sfResolution.x * 0.75, player.m_sfResolution.y * 0.75));
		settingsRect.setFillColor(Color::Blue);

		settingsSprite.setTexture(settingsTex);
		settingsSprite.setScale(Vector2f(player.m_sfResolution.x * 0.75 / 960, player.m_sfResolution.y * 0.75 / 302));
		settingsSprite.setPosition(settingsRect.getPosition());

		//Create buttons-------------------------
		Vector2f resolutionScale(player.m_sfResolution.x / 1280, player.m_sfResolution.y / 720);
		Vector2f buttonSize(250 * resolutionScale.x, 100 * resolutionScale.y);
		Vector2f middleOfScreen((player.m_sfResolution.x / 2) - (buttonSize.x / 2), (player.m_sfResolution.y / 2) - (buttonSize.y / 2));

		Text title;
		Font font;

		if (!font.loadFromFile("Assets/fonts/ariali.ttf"))
		{
			cout << "Error: Font ariali.ttf was unable to load.";
		};

		title.setFont(font);
		title.setString("Settings");
		title.setCharacterSize(55 * resolutionScale.x);
		title.setFillColor(Color(0, 0, 0));
		title.setPosition(Vector2f(middleOfScreen.x, 25 * resolutionScale.y));

		Vector2f middleOfScreenOverlay(player.m_sfResolution.x / 2 - (250 * resolutionScale.x), player.m_sfResolution.y / 2 - (250 * resolutionScale.y));

		//create text box 
		Vector2f TextBoxStart(180 * resolutionScale.x, 220 * resolutionScale.y);
		string s;
		s = to_string(player.m_iGameAudioVolume);

		TextBox gameVolume("Game Volume " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button gameVolumeSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;
		s = to_string(player.m_iMusicAudioVolume);

		TextBox musicVolume("Music Volume " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button musicVolumeSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;
		s = to_string(player.m_iInterfaceAudioVolume);


		TextBox interfaceVolume("Interface Volume " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button interfaceVolumeSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y = 220;
		TextBoxStart.x = 240 + player.m_sfResolution.x / 3;

		s = to_string(player.m_sfResolution.x);


		TextBox resolutionX("Resolution : x " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionXSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;

		s = to_string(player.m_sfResolution.y);
		TextBox resolutionY("Resolution : y " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button resolutionYSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;


		if (player.m_bFullscreen == true) s = "Yes";
		if (player.m_bFullscreen == false) s = "No";

		TextBox fullScreen("Fullscreen Mode " + s, TextBoxStart, Vector2f(343 * resolutionScale.x, 37 * resolutionScale.y), "Textbox");
		Button fullScreenSubmit("Submit", Vector2f(TextBoxStart.x + 343, TextBoxStart.y), Vector2f(buttonSize.x / 2.5, buttonSize.y / 2.5), "Button_Green");
		TextBoxStart.y += 100;

		Button Save("Save", Vector2f(settingsRect.getPosition().x, settingsRect.getPosition().y + settingsBackgroundRect.getSize().y - 2 * buttonSize.y), buttonSize, "Button_Green");
		Button Reset("Reset", Vector2f(settingsRect.getPosition().x + 1.5 * buttonSize.x, settingsRect.getPosition().y + settingsBackgroundRect.getSize().y - 2 * buttonSize.y), buttonSize, "Button_Green");
		Button Cancel("Cancel", Vector2f(settingsRect.getPosition().x + 3 * buttonSize.x, settingsRect.getPosition().y + settingsBackgroundRect.getSize().y - 2 * buttonSize.y), buttonSize, "Button_Green");

		RenderWindow window(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Main Menu");
		window.setFramerateLimit(60);


		while (window.isOpen())
		{

			//handle input
			Event event;
			Vector2f sfMousePos;
			while (window.pollEvent(event))
			{

				sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window));

				if (event.type == Event::Closed)
				{
					window.close(); // Allows window to close when 'X' is pressed
					return;
				}
		
				gameVolume.takeInput(event.key.code);
				musicVolume.takeInput(event.key.code);
				interfaceVolume.takeInput(event.key.code);
				resolutionX.takeInput(event.key.code);
				resolutionY.takeInput(event.key.code);
				fullScreen.takeInput(event.key.code);


				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (Save.m_bClicked(sfMousePos))
						{
							player.saveProfile();
							window.close();
							mainMenu(false);

						}
						
						if (gameVolume.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = true;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (musicVolume.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = true;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (interfaceVolume.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = true;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (resolutionX.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = true;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = false;
						}
						if (resolutionY.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = true;
							fullScreen.m_bIsEntering = false;
						}
						if (fullScreen.m_bClicked(sfMousePos))
						{
							gameVolume.m_bIsEntering = false;
							musicVolume.m_bIsEntering = false;
							interfaceVolume.m_bIsEntering = false;
							resolutionX.m_bIsEntering = false;
							resolutionY.m_bIsEntering = false;
							fullScreen.m_bIsEntering = true;
						}


						if (fullScreenSubmit.m_bClicked(sfMousePos))
						{
							if (fullScreen.m_sText == "yes")	player.m_bFullscreen = true;
							else if (fullScreen.m_sText == "no")	player.m_bFullscreen = false;
							else player.m_bFullscreen = false;


						}
						if (gameVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = gameVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 10)
							{
								player.m_iGameAudioVolume = value;
							}
						}

						if ( musicVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = musicVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 10)
							{
								player.m_iMusicAudioVolume = value;
							}

						}

						if (interfaceVolumeSubmit.m_bClicked(sfMousePos))
						{
							string input = interfaceVolume.m_sText;
							int value = atoi(input.c_str());
							if (value >= 0 && value <= 10)
							{
								player.m_iInterfaceAudioVolume = value;
							}

						}
						if ( resolutionXSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionX.m_sText;
							int value = atoi(input.c_str());
							if (value >= 800 && value <= 3840)
							{
								player.m_sfResolution.x = value;
							}
						}
						if (resolutionYSubmit.m_bClicked(sfMousePos))
						{
							string input = resolutionY.m_sText;
							int value = atoi(input.c_str());
							if (value >= 600 && value <= 2160)
							{
								player.m_sfResolution.y = value;
							}
						}
					}
				}
			}


			window.clear(Color::Green);

			window.draw(settingsBackgroundSprite);
			window.draw(settingsSprite);
			window.draw(title);

			// buttons
			window.draw(gameVolume);
			window.draw(gameVolumeSubmit);
			window.draw(interfaceVolume);
			window.draw(interfaceVolumeSubmit);
			window.draw(musicVolume);
			window.draw(musicVolumeSubmit);

			window.draw(resolutionX);
			window.draw(resolutionXSubmit);
			window.draw(resolutionY);
			window.draw(resolutionYSubmit);
			window.draw(fullScreen);
			window.draw(fullScreenSubmit);

			window.draw(Save);
			window.draw(Reset);
			window.draw(Cancel);

			window.display();
		}
	}

}

void editor()
{
	//Game Object
	Game Editor("./Assets/Levels/Editor.xml");

	//Create a window with the specifications of the profile
	RenderWindow window;
	if (player.m_bFullscreen == true) window.create(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Editor", Style::Fullscreen);
	else window.create(VideoMode(player.m_sfResolution.x, player.m_sfResolution.y), "Editor");
	window.setFramerateLimit(60);

	//create a view to fill the windowfor game render
	View gameView;
	gameView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	gameView.setCenter(Vector2f(0,0));
	gameView.setSize(sf::Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));

	//create a view to fill the windowfor game render
	View hudView;
	hudView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	hudView.setCenter(sf::Vector2f(player.m_sfResolution.x / 2, player.m_sfResolution.y / 2));
	hudView.setSize(sf::Vector2f(player.m_sfResolution.x, player.m_sfResolution.y));

	//helps scale hud elements
	Vector2f resolutionScale(player.m_sfResolution.x / 1280, player.m_sfResolution.y / 720);

	//create Buttons for the editor
	Button BackgroundButton
	("Background",
		Vector2f(0, 0),
		Vector2f(300 * resolutionScale.x , 88.5 * resolutionScale.y) ,
		"Button_Green"
		);
	Button SizeButton
	("Level Size",
		Vector2f(0, 90 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		"Button_Green"
	);

	Button TimeButton
	("Time of Day",
		Vector2f(0, 180 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		"Button_Green"
	);

	Button RoadSelectorButton
	("Roads",
		Vector2f(0, 270 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		"Button_Yellow"
	);

	Button twoWayButton
	("Two Way Road",
		Vector2f(300, 270 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		"Button_Yellow"
	);

	Button trafficLightButton
	("Lights",
		Vector2f(0, 360 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		"Button_Yellow"
	);

	Button normalLightButton
	("Traffic Lights",
		Vector2f(300, 315 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		"Button_Yellow"
	);
	Button pedLightButton
	("Pedestrian Lights",
		Vector2f(300, 405 * resolutionScale.y),
		Vector2f(300 * resolutionScale.x, 88.5 * resolutionScale.y),
		"Button_Yellow"
	);

	//selections bools
	bool RoadSelectorBool = false; // true while choosing road
	bool LightSelectorBool = false; // true while choosing roads

	bool placingBool = false; // true while placing roads

	//selection string
	string sType; // type of object been placed by the editor

	while (window.isOpen())
	{
		//handle input
		Event event;
		Vector2f sfMousePos;
		Vector2f sfPlacingPos;
		int iMouseWheel;

		//move camera
		float fMoveSpeed = 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
		{
			fMoveSpeed *= 3;
		}
		//key presses
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			gameView.move(Vector2f(0.0f, -fMoveSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			gameView.move(Vector2f(0.0f, fMoveSpeed));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			gameView.move(Vector2f(-fMoveSpeed, 0.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			gameView.move(Vector2f(fMoveSpeed, 0.0f));
		}

		//move the editor objects
		sfPlacingPos = window.mapPixelToCoords(Mouse::getPosition(window), gameView);

		if (placingBool)
		{
			Editor.spawnTempObject(sfPlacingPos, 0.0f, sType);
			Editor.m_bPlacingObject = true;
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				if (sType == "Normal Road")
				{
					Editor.placeRoad(sfPlacingPos, 0.0f);
					Editor.m_bPlacingObject = false;
					//reset all selectors
					RoadSelectorBool = false;
					LightSelectorBool = false;
					placingBool = false;
				}
			}
		}

		while (window.pollEvent(event))
		{

			sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), hudView);
				
			if (event.type == Event::MouseWheelMoved)
			{
				iMouseWheel= event.mouseWheel.delta;
				if (iMouseWheel > 0)
				{
					//zoom in
					gameView.zoom(0.9);
				}
				if (iMouseWheel < 0)
				{
					//zoom out
					gameView.zoom(1.1);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					//cancel all placement
					Editor.m_bPlacingObject = false;
					LightSelectorBool = false;
					placingBool = false;
					RoadSelectorBool = false;
			
				}

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sfMousePos = window.mapPixelToCoords(Mouse::getPosition(window), hudView);

					//check if background Button has been clicked
					if (BackgroundButton.m_bClicked(sfMousePos))
					{
						Editor.cycleBackground();
						RoadSelectorBool = false;
						LightSelectorBool = false;
					}

					//check if size Button has been clicked
					else if (SizeButton.m_bClicked(sfMousePos))
					{
						Editor.cycleLevelSize();
						RoadSelectorBool = false;
						LightSelectorBool = false;
					}

					//check if time Button has been clicked
					else if (TimeButton.m_bClicked(sfMousePos))
					{
						Editor.cycleLevelTime();
						RoadSelectorBool = false;
						LightSelectorBool = false;
					}

					//check if road selector Button has been clicked
					else if (RoadSelectorButton.m_bClicked(sfMousePos))
					{
						if (RoadSelectorBool == false)
						{
							RoadSelectorBool = true;
							LightSelectorBool = false;
						}
						else if (RoadSelectorBool == true)
						{
							RoadSelectorBool = false;
							LightSelectorBool = false;
						}
						placingBool = false;
					}
					//check if 2 way road Button has been clicked
					else if (twoWayButton.m_bClicked(sfMousePos) && RoadSelectorBool == true)
					{
						placingBool = true;
						LightSelectorBool = false;
						RoadSelectorBool = false;
						sType = "Normal Road";

					}
					
					
					//check if traffic selector Button has been clicked
					else if (trafficLightButton.m_bClicked(sfMousePos))
					{
						if (LightSelectorBool == false)
						{
							LightSelectorBool = true;
							RoadSelectorBool = false;
						}
						else if (LightSelectorBool == true)
						{
							LightSelectorBool = false;
							RoadSelectorBool = false;
						}
						placingBool = false;
					}
					//check if to spawn a traffic light
					else if (normalLightButton.m_bClicked(sfMousePos) && LightSelectorBool == true )
					{
						placingBool = true;
						LightSelectorBool = false;
						sType = "Traffic Light";
						
					}
					//check if to spawn a pedestrian light
					else if (pedLightButton.m_bClicked(sfMousePos) && LightSelectorBool == true)
					{
						placingBool = true;
						LightSelectorBool = false;
						sType = "Pedestrian Light";

					}
					else
					{
						//reset all selectors
						RoadSelectorBool = false;
						LightSelectorBool = false;
						
					}
				}
			}

			if (event.type == Event::Closed)
			{
				window.close(); // Allows window to close when 'X' is pressed
				return;
			}

		

		}

		window.clear(Color::Black);

		//draw the game 
		window.setView(gameView);
		
		Editor.updateScene(0.01f);
		Editor.drawScene(window);

		//draw the hud
		window.setView(hudView);
		window.draw(BackgroundButton);
		window.draw(SizeButton);
		window.draw(TimeButton);
		window.draw(RoadSelectorButton);
		window.draw(trafficLightButton);
		if (RoadSelectorBool)
		{
			window.draw(twoWayButton);
		}
		if (LightSelectorBool)
		{
			window.draw(normalLightButton);
			window.draw(pedLightButton);
		}

		//show the window
		window.display();
	}

}
