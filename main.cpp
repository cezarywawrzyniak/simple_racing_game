#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include "player.h"
#include "lines.h"
#include "obstacles.h"
#include "buttons.h"
#include "opponents.h"

bool playing = false;
std::string highscorestring;
float highscorefloat;

//tryb menu
//0 - ekran tytulowy
//1 - highscore
//2 - wybor trybu
//3 - wybor auta
int menu = 0;

//tryb gry
//0 - swobodna jazda
//1 - komputer
//2 - 2 graczy
int gamemode = 0;


int main()
{
	restart:
	//tworzenie okna
	sf::RenderWindow game(sf::VideoMode(1280, 720), "Samochody");
	game.setFramerateLimit(60);

	//wczytanie highscore
	std::ifstream readfile("save/save.txt");
	if (readfile.is_open())
	{
		std::cout << "Wczytywanie pliku" << std::endl;
		getline(readfile, highscorestring);
		readfile.close();
		highscorefloat = std::stof(highscorestring);

		std::cout << "String: " << highscorestring << std::endl;
		std::cout << "Float: " << highscorefloat << std::endl;
	}


	//wczytanie menu
	sf::Texture backgroundmenu;
	backgroundmenu.loadFromFile("img/menu/menubackground.png");
	backgroundmenu.setSmooth(true);
	sf::Sprite sMenu;
	sMenu.setTexture(backgroundmenu);

	sf::Texture modetext;
	modetext.loadFromFile("img/menu/mode/mode.png");
	modetext.setSmooth(true);
	sf::Sprite sModetext;
	sModetext.setTexture(modetext);
	sModetext.setPosition(460, 30);

	sf::Color blue(84, 159, 193);
	sf::Color lightblue(0, 162, 255);
	sf::Color sand(221, 174, 148);
	sf::Color red(234, 73, 81);

	//wczytanie trasy
	sf::Texture backgroundtrack;
	backgroundtrack.loadFromFile("img/tracks/track.png");
	backgroundtrack.setSmooth(true);
	sf::Sprite sTrack;
	sTrack.setTexture(backgroundtrack);

	//-------deklaracja calego menu---------------------

	//opening
	Button racing;
	racing.loadtexture1("img/menu/opening/racing.png");
	racing.setsprite(345, 30);
	Button play;
	play.loadtexture1("img/menu/opening/play.png");
	play.loadtexture2("img/menu/opening/playlight.png");
	play.setsprite(370, 245);
	Button score;
	score.loadtexture1("img/menu/opening/score.png");
	score.loadtexture2("img/menu/opening/scorelight.png");
	score.setsprite(370, 380);
	Button exit;
	exit.loadtexture1("img/menu/opening/exit.png");
	exit.loadtexture2("img/menu/opening/exitlight.png");
	exit.setsprite(370, 510);

	//mode
	Button computer;
	computer.loadtexture1("img/menu/mode/com.png");
	computer.loadtexture2("img/menu/mode/comlight.png");
	computer.setsprite(370, 245);
	Button players2;
	players2.loadtexture1("img/menu/mode/2p.png");
	players2.loadtexture2("img/menu/mode/2plight.png");
	players2.setsprite(370, 380);

	//car
	Button choice;
	choice.loadtexture1("img/menu/car/choice.png");
	choice.setsprite(0, 0);
	Button easycar;
	easycar.loadtexture1("img/cars/truck.png");
	easycar.setsprite(250, 220);
	Button mediumcar;
	mediumcar.loadtexture1("img/cars/defaultcar.png");
	mediumcar.setsprite(590, 220);
	Button hardcar;
	hardcar.loadtexture1("img/cars/racecar.png");
	hardcar.setsprite(950, 220);
	//--------------------------------------------------

	//deklaracja oraz wczytanie lini mety, checkpointu i licznika okrazen
	Finishline lines;
	lines.loadtextures("img/tracks/line.png", "img/tracks/checkpoint.png", "img/hud/03.png", "img/hud/13.png", "img/hud/23.png", "img/hud/33.png", "img/hud/finish.png");
	Finishline lines2;
	lines2.loadtextures("img/tracks/line.png", "img/tracks/checkpoint.png", "img/hud/03.png", "img/hud/13.png", "img/hud/23.png", "img/hud/33.png", "img/hud/finish2.png");

	//deklaracje tekstow
	sf::Font font;
	font.loadFromFile("font/thatfont.ttf");
	sf::Text tlap1;
	tlap1.setFillColor(blue);
	tlap1.setCharacterSize(50);
	tlap1.setFont(font);
	tlap1.setPosition(300, 0);
	sf::Text tlap2;
	tlap2.setFillColor(blue);
	tlap2.setCharacterSize(50);
	tlap2.setFont(font);
	tlap2.setPosition(300, 50);
	sf::Text tlap3;
	tlap3.setFillColor(blue);
	tlap3.setCharacterSize(50);
	tlap3.setFont(font);
	tlap3.setPosition(300, 100);
	sf::Text finaltime;
	finaltime.setFillColor(blue);
	finaltime.setCharacterSize(50);
	finaltime.setFont(font);
	finaltime.setPosition(440, 540);

	sf::Text t2lap1;
	t2lap1.setFillColor(red);
	t2lap1.setCharacterSize(50);
	t2lap1.setFont(font);
	t2lap1.setPosition(645, 0);
	sf::Text t2lap2;
	t2lap2.setFillColor(red);
	t2lap2.setCharacterSize(50);
	t2lap2.setFont(font);
	t2lap2.setPosition(645, 50);
	sf::Text t2lap3;
	t2lap3.setFillColor(red);
	t2lap3.setCharacterSize(50);
	t2lap3.setFont(font);
	t2lap3.setPosition(645, 100);
	sf::Text finaltime2;
	finaltime2.setFillColor(red);
	finaltime2.setCharacterSize(50);
	finaltime2.setFont(font);
	finaltime2.setPosition(440, 540);
	
	sf::Text highscoretext;
	highscoretext.setFillColor(lightblue);
	highscoretext.setCharacterSize(100);
	highscoretext.setFont(font);
	highscoretext.setPosition(300, 240);

	//deklaracja trawy
	Grass middlegrass;
	middlegrass.loadtexture("img/tracks/grass.png");

	//deklaracja piachu
	Sand upsand;
	upsand.loadtexture("img/tracks/upsand.png");
	Sand downsand;
	downsand.loadtexture("img/tracks/downsand.png");
	Sand leftsand;
	leftsand.loadtexture("img/tracks/leftsand.png");
	Sand rightsand;
	rightsand.loadtexture("img/tracks/rightsand.png");

	//deklaracja opon
	Tires lefttires;
	lefttires.loadtexture("img/tracks/shorttires.png");
	Tires righttires;
	righttires.loadtexture("img/tracks/shorttires.png");
	Tires uptires;
	uptires.loadtexture("img/tracks/longtires.png");
	Tires downtires;
	downtires.loadtexture("img/tracks/longtires.png");

	//deklaracja trybun
	Stand leftstand1;
	leftstand1.loadtexture("img/tracks/standleft.png");
	Stand leftstand2;
	leftstand2.loadtexture("img/tracks/standleft.png");
	Stand rightstand1;
	rightstand1.loadtexture("img/tracks/standright.png");
	Stand rightstand2;
	rightstand2.loadtexture("img/tracks/standright.png");

	//deklaracja gracza
	Player player;
	player.loadtextures("img/cars/defaultcar.png", "img/cars/truck.png", "img/cars/racecar.png");
	player.setsprite();
	player.setorigin();
	player.setcords(650, 3200);
	Player player2;
	player2.loadtextures("img/cars/defaultcar.png", "img/cars/truck.png", "img/cars/racecar.png");
	player2.setsprite();
	player2.setorigin();
	player2.setcords(950, 3200);

	//deklaracja zegara
	sf::Clock clock;

	//kamera
	sf::View playerview(sf::FloatRect(0, 0, game.getSize().x, game.getSize().y));
	sf::View player1view;
	player1view.setViewport(sf::FloatRect(0, 0, 0.5f, 1.0f));
	player1view.setSize(game.getSize().x / 2, game.getSize().y);
	sf::View player2view;
	player2view.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1.0f));
	player2view.setSize(game.getSize().x / 2, game.getSize().y);;


	//deklaracja przeciwnikow
	const int nr = 2;
	

	sf::Texture otexture;
	otexture.loadFromFile("img/cars/opponentcar.png");
	otexture.setSmooth(true);
	sf::Sprite ocar;
	ocar.setTexture(otexture);
	ocar.setOrigin(50, 100);

	Opponents opponents[2];

	opponents[0].x = 650;
	opponents[0].y = 3200;
	opponents[1].x = 950;
	opponents[1].y = 3400;

	for (int i = 0; i < nr; i++)
	{
		opponents[i].speed = 15 + (i*0.5);
	}
	
	while (game.isOpen())
	{
		sf::Event zdarzenie;
		while (game.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
			{
				game.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				game.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				goto restart;
			}
		}

		player.move();
		if (gamemode == 2) player2.move();

		//------------------------------------------------menu----------------------------------------------
		if (!playing)
		{	
			game.clear(sf::Color::Black);
			game.draw(sMenu);
			sf::Vector2i position = sf::Mouse::getPosition(game);
			std::cout << position.x <<"      "<< position.y << std::endl;

			//ekran tytulowy
			if (menu == 0)
			{	//rysowanie menu
				racing.drawsprite(game);

				game.draw(play.sSprite);
				if (370 <= position.x && position.x <=907 && 245 <= position.y && position.y <= 332)
				{
					play.changesprite2();
				}
				else
				{
					play.changesprite1();
				}

				game.draw(score.sSprite);
				if (370 <= position.x && position.x <=907 && 380 <= position.y && position.y <= 467)
				{
					score.changesprite2();
				}
				else
				{
					score.changesprite1();
				}

				game.draw(exit.sSprite);
				if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
				{
					exit.changesprite2();
				}
				else
				{
					exit.changesprite1();
				}
				//sprawdzanie klikniêcie myszy
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (370 <= position.x && position.x <= 907 && 245 <= position.y && position.y <= 332)
					{
						menu = 2;
						Sleep(250);
					}
					else if (370 <= position.x && position.x <= 907 && 380 <= position.y && position.y <= 467)
					{
						menu = 1;
						Sleep(250);
					}
					else if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
					{
						game.close();
						Sleep(250);
					}
				}
			}

			//ekran highscore
			else if (menu == 1)
			{
				highscoretext.setString(highscorestring);
				game.draw(highscoretext);
				game.draw(exit.sSprite);
				if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
				{
					exit.changesprite2();
				}
				else
				{
					exit.changesprite1();
				}
				//sprawdzanie klikniêcie myszy
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
					{
						menu = 0;
						Sleep(250);
					}
				}
			}

			//ekran mode
			else if (menu == 2)
			{	
				game.draw(sModetext);
				game.draw(computer.sSprite);
				if (370 <= position.x && position.x <= 907 && 245 <= position.y && position.y <= 332)
				{
					computer.changesprite2();
				}
				else
				{
					computer.changesprite1();
				}

				game.draw(players2.sSprite);
				if (370 <= position.x && position.x <= 907 && 380 <= position.y && position.y <= 467)
				{
					players2.changesprite2();
				}
				else
				{
					players2.changesprite1();
				}
				game.draw(exit.sSprite);
				if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
				{
					exit.changesprite2();
				}
				else
				{
					exit.changesprite1();
				}
				//sprawdzanie klikniêcie myszy
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (370 <= position.x && position.x <= 907 && 245 <= position.y && position.y <= 332)
					{
						menu = 3;
						gamemode = 1;
						Sleep(250);
					}
					else if (370 <= position.x && position.x <= 907 && 380 <= position.y && position.y <= 467)
					{
						menu = 3;
						gamemode = 2;
						Sleep(250);
					}
					else if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
					{
						menu = 0;
						Sleep(250);
					}
					else
					{
						menu = 3;
						gamemode = 0;
						Sleep(250);
					}
				}
			}

			//ekran auta
			else if (menu == 3)
			{
				game.draw(choice.sSprite);
				game.draw(easycar.sSprite);
				game.draw(mediumcar.sSprite);
				game.draw(hardcar.sSprite);
				game.draw(exit.sSprite);
				if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
				{
					exit.changesprite2();
				}
				else
				{
					exit.changesprite1();
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (250 <= position.x && position.x <= 350 && 220 <= position.y && position.y <= 420)
					{
						Sleep(250);
						player.chosencar = 2;
						if (gamemode == 1 || gamemode == 0) playing = true;
						if (gamemode == 2) menu = 4;
					}
					else if (590 <= position.x && position.x <= 690 && 220 <= position.y && position.y <= 420)
					{
						Sleep(250);
						player.chosencar = 1;
						if (gamemode == 1 || gamemode == 0) playing = true;
						if (gamemode == 2) menu = 4;
					}
					else if (950 <= position.x && position.x <= 1050 && 220 <= position.y && position.y <= 420)
					{
						Sleep(250);
						player.chosencar = 3;
						if (gamemode == 1 || gamemode == 0) playing = true;
						if (gamemode == 2) menu = 4;
					}
					else if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
					{
						menu = 2;
						Sleep(250);
					}
				}
			}
			else if (menu == 4)
			{
				game.draw(choice.sSprite);
				game.draw(easycar.sSprite);
				game.draw(mediumcar.sSprite);
				game.draw(hardcar.sSprite);
				game.draw(exit.sSprite);
				if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
				{
					exit.changesprite2();
				}
				else
				{
					exit.changesprite1();
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (250 <= position.x && position.x <= 350 && 220 <= position.y && position.y <= 420)
					{
						Sleep(250);
						player2.chosencar = 2;
						playing = true;
					}
					else if (590 <= position.x && position.x <= 690 && 220 <= position.y && position.y <= 420)
					{
						Sleep(250);
						player2.chosencar = 1;
						playing = true;
					}
					else if (950 <= position.x && position.x <= 1050 && 220 <= position.y && position.y <= 420)
					{
						Sleep(250);
						player2.chosencar = 3;
						playing = true;
					}
					else if (370 <= position.x && position.x <= 907 && 510 <= position.y && position.y <= 597)
					{
						menu = 3;
						Sleep(250);
					}
				}
			}
		}
		//------------------------------------------------gra----------------------------------------------
		if (playing)
		{	
			if (gamemode == 1 || gamemode == 0)
			{
				game.clear(sand);

				//kamera gracz1
				playerview.setCenter(player.playercar.getPosition());
				game.setView(playerview);

				//tor
				sTrack.setPosition(0, 0);
				game.draw(sTrack);

				//trawa
				middlegrass.setsprite(1232, 1177);
				middlegrass.drawsprite(game);

				//piach
				upsand.setsprite(0, 0);
				upsand.drawsprite(game);
				downsand.setsprite(0, 5340);
				downsand.drawsprite(game);
				leftsand.setsprite(0, 535);
				leftsand.drawsprite(game);
				rightsand.setsprite(7451, 535);
				rightsand.drawsprite(game);

				//opony
				lefttires.setsprite(5, 0);
				lefttires.drawsprite(game);
				righttires.setsprite(7900, 0);
				righttires.drawsprite(game);
				uptires.setsprite(100, 0);
				uptires.drawsprite(game);
				downtires.setsprite(100, 5900);
				downtires.drawsprite(game);

				//trybuny
				leftstand1.setsprite(1200, 3150);
				leftstand1.drawsprite(game);
				leftstand2.setsprite(1200, 2250);
				leftstand2.drawsprite(game);
				rightstand1.setsprite(6450, 3150);
				rightstand1.drawsprite(game);
				rightstand2.setsprite(6450, 2250);
				rightstand2.drawsprite(game);

				//gracz
				player.drawplayer(game, player.x, player.y, player.angle / 1.5 * 180.0 / 3.141592);
				if (gamemode == 0) player.choosecar();
				player.changecar();
				player.drive(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);

				//przeciwnicy
				if (gamemode == 1)
				{
					for (int i = 0; i < nr; i++)
					{
						ocar.setPosition(opponents[i].x, opponents[i].y);
						ocar.setRotation(opponents[i].angle * 180.0 / 3.141592);
						game.draw(ocar);

					}
				}
				if (gamemode == 1)
				{
					for (int i = 0; i < nr; i++)
					{
						opponents[i].move();
						opponents[i].findcheckpoint();
					}
				}

				//kamera hud
				game.setView(game.getDefaultView());

				//linia mety, checkpoint i licznik
				lines.setsprites(445, 2984, 6851, 2994, 20, 0);
				lines.drawsprite(game);
			}

			else if (gamemode == 2)
			{
				game.clear(sand);

				//----------------------kamera-gracz1-----------------
				player1view.setCenter(player.playercar.getPosition());
				game.setView(player1view);
			
				//tor
				sTrack.setPosition(0, 0);
				game.draw(sTrack);

				//trawa
				middlegrass.setsprite(1232, 1177);
				middlegrass.drawsprite(game);

				//piach
				upsand.setsprite(0, 0);
				upsand.drawsprite(game);
				downsand.setsprite(0, 5340);
				downsand.drawsprite(game);
				leftsand.setsprite(0, 535);
				leftsand.drawsprite(game);
				rightsand.setsprite(7451, 535);
				rightsand.drawsprite(game);

				//opony
				lefttires.setsprite(5, 0);
				lefttires.drawsprite(game);
				righttires.setsprite(7900, 0);
				righttires.drawsprite(game);
				uptires.setsprite(100, 0);
				uptires.drawsprite(game);
				downtires.setsprite(100, 5900);
				downtires.drawsprite(game);

				//trybuny
				leftstand1.setsprite(1200, 3150);
				leftstand1.drawsprite(game);
				leftstand2.setsprite(1200, 2250);
				leftstand2.drawsprite(game);
				rightstand1.setsprite(6450, 3150);
				rightstand1.drawsprite(game);
				rightstand2.setsprite(6450, 2250);
				rightstand2.drawsprite(game);

				//gracz
				player.drawplayer(game, player.x, player.y, player.angle / 1.5 * 180.0 / 3.141592);
				//player.choosecar();
				player.changecar();
				player.drive(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
				player2.drawplayer(game, player2.x, player2.y, player2.angle / 1.5 * 180.0 / 3.141592);
				//player2.choosecar();
				player2.changecar();
				player2.drive(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);

				//----------------------kamera-gracz2---------------------------------
				player2view.setCenter(player2.playercar.getPosition());
				game.setView(player2view);

				//tor
				sTrack.setPosition(0, 0);
				game.draw(sTrack);

				//trawa
				middlegrass.setsprite(1232, 1177);
				middlegrass.drawsprite(game);

				//piach
				upsand.setsprite(0, 0);
				upsand.drawsprite(game);
				downsand.setsprite(0, 5340);
				downsand.drawsprite(game);
				leftsand.setsprite(0, 535);
				leftsand.drawsprite(game);
				rightsand.setsprite(7451, 535);
				rightsand.drawsprite(game);

				//opony
				lefttires.setsprite(5, 0);
				lefttires.drawsprite(game);
				righttires.setsprite(7900, 0);
				righttires.drawsprite(game);
				uptires.setsprite(100, 0);
				uptires.drawsprite(game);
				downtires.setsprite(100, 5900);
				downtires.drawsprite(game);

				//trybuny
				leftstand1.setsprite(1200, 3150);
				leftstand1.drawsprite(game);
				leftstand2.setsprite(1200, 2250);
				leftstand2.drawsprite(game);
				rightstand1.setsprite(6450, 3150);
				rightstand1.drawsprite(game);
				rightstand2.setsprite(6450, 2250);
				rightstand2.drawsprite(game);

				//gracz
				player.drawplayer(game, player.x, player.y, player.angle / 1.5 * 180.0 / 3.141592);
				//player.choosecar();
				player.changecar();
				player.drive(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
				player2.drawplayer(game, player2.x, player2.y, player2.angle / 1.5 * 180.0 / 3.141592);
				//player2.choosecar();
				player2.changecar();
				player2.drive(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
				
				//----------------------------kamera-hud--------------------------------
				game.setView(game.getDefaultView());

				//linia mety, checkpoint i licznik
				lines.setsprites(445, 2984, 6851, 2994, 20, 0);
				lines.drawsprite(game);
				lines2.setsprites(445, 2984, 6851, 2994, 1050, 0);
				lines2.drawsprite(game);
			}

			//-------------------------------------kolizja--------------------------------------------
			//linia startu i checkpoint
			if (gamemode == 1 || gamemode == 0)
			{
				lines.checkpointcounter(player.playercar);
				lines.lapcounter(player.playercar);

				lines.gettime(clock);

				tlap1.setString(lines.stringlap1);
				game.draw(tlap1);
				tlap2.setString(lines.stringlap2);
				game.draw(tlap2);
				tlap3.setString(lines.stringlap3);
				game.draw(tlap3);

				lines.changelapcounter(game);

				lines.end(game);
				finaltime.setString(lines.stringfullrace);
				game.draw(finaltime);
				if (lines.finaltime < highscorefloat)
				{
					std::cout << "Zapisywanie pliku" << std::endl;
					std::ofstream saving;
					saving.open("save/save.txt");
					saving << lines.stringfullrace << std::endl;
					saving.close();
				}
			}
			if (gamemode == 2)
			{	
				lines.checkpointcounter(player.playercar);
				lines.lapcounter(player.playercar);

				lines.gettime(clock);

				tlap1.setString(lines.stringlap1);
				game.draw(tlap1);
				tlap2.setString(lines.stringlap2);
				game.draw(tlap2);
				tlap3.setString(lines.stringlap3);
				game.draw(tlap3);

				lines.changelapcounter(game);

				finaltime.setString(lines.stringfullrace);
				if (lines.finaltime < highscorefloat)
				{
					std::cout << "Zapisywanie pliku" << std::endl;
					std::ofstream saving;
					saving.open("save/save.txt");
					saving << lines.stringfullrace << std::endl;
					saving.close();
				}
			

				lines2.checkpointcounter(player2.playercar);
				lines2.lapcounter(player2.playercar);

				lines2.gettime(clock);

				t2lap1.setString(lines2.stringlap1);
				game.draw(t2lap1);
				t2lap2.setString(lines2.stringlap2);
				game.draw(t2lap2);
				t2lap3.setString(lines2.stringlap3);
				game.draw(t2lap3);

				lines2.changelapcounter(game);

				if (lines2.lapcntr > lines.lapcntr && lines2.lapcntr == 4)
				{
					lines2.end(game);
					player.speed = 0;
				}
				if (lines.lapcntr > lines2.lapcntr && lines.lapcntr == 4)
				{
					lines.end(game);
					player2.speed = 0;
				}
				
				finaltime2.setString(lines2.stringfullrace);
				game.draw(finaltime2);
				game.draw(finaltime);
				if (lines2.finaltime < highscorefloat)
				{
					std::cout << "Zapisywanie pliku" << std::endl;
					std::ofstream saving;
					saving.open("save/save.txt");
					saving << lines2.stringfullrace << std::endl;
					saving.close();
				}
			}

			//trawa
			player.ongrass(middlegrass.sSprite);
			if (gamemode == 2)
			{
				player2.ongrass(middlegrass.sSprite);
			}

			//piach
			player.onsand(upsand.sSprite);
			player.onsand(downsand.sSprite);
			player.onsand(leftsand.sSprite);
			player.onsand(rightsand.sSprite);

			if (gamemode == 2)
			{
				player2.onsand(upsand.sSprite);
				player2.onsand(downsand.sSprite);
				player2.onsand(leftsand.sSprite);
				player2.onsand(rightsand.sSprite);
			}

			//opony
			player.hittires(uptires.sSprite);
			player.hittires(downtires.sSprite);
			player.hittires(lefttires.sSprite);
			player.hittires(righttires.sSprite);

			if (gamemode == 2)
			{
				player2.hittires(uptires.sSprite);
				player2.hittires(downtires.sSprite);
				player2.hittires(lefttires.sSprite);
				player2.hittires(righttires.sSprite);
			}
			//trybuny
			player.stand(leftstand1.x, leftstand1.y);
			player.stand(leftstand2.x, leftstand2.y);
			player.stand(rightstand1.x, rightstand1.y);
			player.stand(rightstand2.x, rightstand2.y);

			if (gamemode == 2)
			{
				player2.stand(leftstand1.x, leftstand1.y);
				player2.stand(leftstand2.x, leftstand2.y);
				player2.stand(rightstand1.x, rightstand1.y);
				player2.stand(rightstand2.x, rightstand2.y);
			}

			//samochody
			if (gamemode == 2)
			{
				int disx = 0;
				int disy = 0;
					while (disx*disx + disy * disy < 4 * 50 * 50)
					{
						player.x += disx / 5.0;
						player.y += disy / 5.0;
						player2.x -= disx / 5.0;
						player2.y -= disy / 5.0;
						
						disx = player.x - player2.x;
						disy = player.y - player2.y;

						if (!disx && !disy) break;
					}
			}

			if (gamemode == 1)
			{
				int disx = 0;
				int disy = 0;
				for (int i = 0; i < nr; i++)
				{
					for (int j = 0; j < nr; j++)
					{
						while (disx*disx + disy * disy < 4 * 100 * 100)
						{
							opponents[i].x += disx / 10.0;
							opponents[i].y += disy / 10.0;
							opponents[j].x -= disx / 10.0;
							opponents[j].y -= disy / 10.0;

							disx = opponents[i].x - opponents[j].x;
							disy = opponents[i].y - opponents[j].y;

							if (!disx && !disy) break;
						}
					}
				}

				for (int i = 0; i < nr; i++)
				{
					int dispx = 0;
					int dispy = 0;
					while (dispx*dispx + dispy * dispy < 4 * 50 * 50)
					{
						player.x += dispx / 10.0;
						player.y += dispy / 10.0;
						opponents[i].x -= dispx / 10.0;
						opponents[i].y -= dispy / 10.0;

						dispx = player.x - opponents[i].x;
						dispy = player.y - opponents[i].y;

						if (!dispx && !dispy) break;
					}
				}

			}

			//---------------------------------------gra-----------------------------------------------
		}
		game.display();
	}
return 0;
}