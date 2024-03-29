#include "TextureObject.h"

bool TextureObject::bInstanceFlag = false;
TextureObject* TextureObject::textureObject = nullptr;


TextureObject::TextureObject()
{
}

TextureObject * TextureObject::getInstance()
{

	if (!bInstanceFlag) // return the singleton window class
	{
		textureObject = new TextureObject();
		bInstanceFlag = true;
		return textureObject;
	}
	else
	{
		return textureObject;
	}
}

void TextureObject::loadTextures()
{
	if (!m_bLoaded)
	{
		cout << "Loading Textures... ";

		Texture sfTempTexture;

		//base colours------------------------------------------

		//White
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_white.png"))
		{
			cout << "Error: car_white.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Black
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_black.png"))
		{
			cout << "Error: car_black.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Blue
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_blue.png"))
		{
			cout << "Error: car_blue.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//blue_light
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_blue_light.png"))
		{
			cout << "Error: car_blue_light.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Green
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_green.png"))
		{
			cout << "Error: car_green.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Orange
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_orange.png"))
		{
			cout << "Error: car_orange.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Pink
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_pink.png"))
		{
			cout << "Error: car_pink.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Purple
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_purple.png"))
		{
			cout << "Error: car_purple.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Red
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_red.png"))
		{
			cout << "Error: car_red.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Yellow
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_yellow.png"))
		{
			cout << "Error: car_yellow.png Texture was unable to load." << endl;
		};

		m_vCarColourTextures.push_back(sfTempTexture);

		//Lights-------------------------------------------------------------------------

		//rear lights
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/rearLight_notLit.png"))
		{
			cout << "Error: rearLight_notLit was unable to load." << endl;
		};

		m_vCarLights.push_back(sfTempTexture);

		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/rearLight_Lit.png"))
		{
			cout << "Error: rearLight_Lit was unable to load." << endl;
		};

		m_vCarLights.push_back(sfTempTexture);

		//front lights
		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontLights_NotLit.png"))
		{
			cout << "Error: FrontLights_NotLit.png was unable to load." << endl;
		};

		m_vCarLights.push_back(sfTempTexture);

		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontLights_Lit.png"))
		{
			cout << "Error: FrontLights_Lit.png was unable to load." << endl;
		};

		m_vCarLights.push_back(sfTempTexture);

		//Wheels

		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontWheel_left.png"))
		{
			cout << "Error: FrontWheel_left.png was unable to load." << endl;
		};

		m_vCarWheels.push_back(sfTempTexture);

		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontWheel_right.png"))
		{
			cout << "Error: FrontWheel_right.png was unable to load." << endl;
		};

		m_vCarWheels.push_back(sfTempTexture);

		if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/RearWheels.png"))
		{
			cout << "Error: RearWheels.png was unable to load." << endl;
		};

		m_vCarWheels.push_back(sfTempTexture);




		//Background Textures---------------------------------------------------------------------

		//Grass
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/GreenGrass.png"))
		{
			cout << "Error: GreenGrass.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Grass
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/YellowGrass.png"))
		{
			cout << "Error: YellowGrass.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Sand
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/GreySand.png"))
		{
			cout << "Error: GreySand.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Sand
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/YellowSand.png"))
		{
			cout << "Error: YellowSand.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Concrete
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/Concrete.png"))
		{
			cout << "Error: Concrete.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);


		//Dirt
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/DirtPath.png"))
		{
			cout << "Error: DirtPath.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Ice
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/Ice.png"))
		{
			cout << "Error: Ice.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);


		//Time Textures---------------------------------------------------------------------

		//Normal.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Normal.png"))
		{
			cout << "Error: Normal.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Day.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Day.png"))
		{
			cout << "Error: Day.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Summer.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Summer.png"))
		{
			cout << "Error: Summer.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Evening.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Evening.png"))
		{
			cout << "Error: Evening.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Night.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Night.png"))
		{
			cout << "Error: Night.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Winter.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Winter.png"))
		{
			cout << "Error: Winter.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);


		//Road Textures---------------------------------------------------------------------



		//normal2WayStreet.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/normal2WayStreet.png"))
		{
			cout << "Error: normal2WayStreet.png was unable to load." << endl;
		};
		m_vTwoWayStreetTextures.push_back(sfTempTexture);

		//normal2WayStreetWithDirections.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/normal2WayStreetWithDirections.png"))
		{
			cout << "Error: normal2WayStreetWithDirections.png was unable to load." << endl;
		};
		m_vTwoWayStreetTextures.push_back(sfTempTexture);

		//T-Junction.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/T-Junction.png"))
		{
			cout << "Error: T-Junction.png was unable to load." << endl;
		};
		m_vTJunctionTextures.push_back(sfTempTexture);

		//T-JunctionsWithDirections.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/T-JunctionsWithDirections.png"))
		{
			cout << "Error: T-JunctionsWithDirections.png was unable to load." << endl;
		};
		m_vTJunctionTextures.push_back(sfTempTexture);

		//Corner.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/Corner.png"))
		{
			cout << "Error: Corner.png was unable to load." << endl;
		};
		m_vCornerTextures.push_back(sfTempTexture);

		//CornerWithDirections.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/CornerWithDirections.png"))
		{
			cout << "Error: CornerWithDirections.png was unable to load." << endl;
		};
		m_vCornerTextures.push_back(sfTempTexture);

		//Cross Roads.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/Cross Roads.png"))
		{
			cout << "Error: Cross Roads.png was unable to load." << endl;
		};
		m_vCrossRoadsTextures.push_back(sfTempTexture);

		//CornerWithDirections.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Roads/Cross RoadsWithDirections.png"))
		{
			cout << "Error: Cross RoadsWithDirections.png was unable to load." << endl;
		};
		m_vCrossRoadsTextures.push_back(sfTempTexture);

		//Traffic lights Textures--------------------------------------------------

		//red.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Traffic Lights/red.png"))
		{
			cout << "Error: red.png was unable to load." << endl;
		};
		m_vTrafficLightTextures.push_back(sfTempTexture);

		//yellow.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Traffic Lights/yellow.png"))
		{
			cout << "Error: yellow.png was unable to load." << endl;
		};
		m_vTrafficLightTextures.push_back(sfTempTexture);

		//green.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Traffic Lights/green.png"))
		{
			cout << "Error: green.png was unable to load." << endl;
		};
		m_vTrafficLightTextures.push_back(sfTempTexture);


		//PedRed.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Traffic Lights/PedRed.png"))
		{
			cout << "Error: PedRed.png was unable to load." << endl;
		};
		m_vPedestrianLightTextures.push_back(sfTempTexture);

		//PedGreen.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Traffic Lights/PedGreen.png"))
		{
			cout << "Error: PedGreen.png was unable to load." << endl;
		};
		m_vPedestrianLightTextures.push_back(sfTempTexture);

		//Start/Endpoint

		//Goal.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Goal.png"))
		{
			cout << "Error: Goal.png was unable to load." << endl;
		};
		m_StartEndPoint = sfTempTexture;

		//Pavment Textures--------------------------------------------------

		//normal2WayStreet.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Pavements/normal2WayStreet.png"))
		{
			cout << "Error: normal2WayStreet.png was unable to load." << endl;
		};
		m_PavementTwoWayStreetTextures = sfTempTexture;

		//T-Junction.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Pavements/T-Junction.png"))
		{
			cout << "Error: T-Junction.png was unable to load." << endl;
		};
		m_PavementTJunctionTextures = sfTempTexture;

		//Corner.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Pavements/Corner.png"))
		{
			cout << "Error: Corner.png was unable to load." << endl;
		};
		m_PavementCornerTextures = sfTempTexture;

		//Cross Roads.pmg
		if (!sfTempTexture.loadFromFile("./Assets/textures/Pavements/Cross Roads.png"))
		{
			cout << "Error: Cross Roads.png was unable to load." << endl;
		};
		m_PavementCrossRoadsTextures = sfTempTexture;

		m_bLoaded = true;

		cout << "Finished" << endl;
	}
}
