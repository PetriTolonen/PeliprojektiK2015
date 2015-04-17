#include "Game.h"

#include "AnimatedSprite.h"


void Game::run()
{

	//----Main Menu------------------//

	MainMenu *main_menu = new MainMenu;

	//------Screen setup------//
	sf::Vector2i screen_dimensions(screen_widht, screen_height);
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(screen_dimensions.x, screen_dimensions.y), "Tank Hunter Arcade");	
	window->setFramerateLimit(60);

	//------View setup------//
	sf::View *view = new sf::View(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	//view.reset(sf::FloatRect(0, 0, screen_dimensions.x, screen_dimensions.y));
	view->setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	view->rotate(180);
	
	level_creation();

	begin_of_game = 0;
	_game_state = Game::showing_splash;
	
	gameloop(window, view, main_menu);	
}

//-----Game_loop-----//
void Game::gameloop(sf::RenderWindow *window, sf::View *view, MainMenu *main_menu)
{
	//---creating box2d world---//
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 0.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);
	//world.Step(1.0f / 60.0f, 8, 4);

	sf::Texture BoxTexture;
	BoxTexture.loadFromFile("box.png");
	//--------------------------//

	//---------Contact Listener-----------------//
	MyContactListener *ContactListener;
	ContactListener = new MyContactListener;
	world.SetContactListener(ContactListener);

	//---player_b2_body---//
	float SCALE = 30.f;
	b2BodyDef BodyDef;
	//BodyDef.position = b2Vec2(2048.0f / SCALE, (screen_height / 2) / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* player_body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((31.f) / SCALE, (66.f) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 10.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	player_body->CreateFixture(&FixtureDef);
	player_body->SetTransform(b2Vec2(2048.0 / SCALE, (screen_height / 2) / SCALE),0);
	//Tank movement dampening
	player_body->SetLinearDamping(5);
	player_body->SetAngularDamping(10);
	//---player_b2_body---//

	//------ammo_b2_body----------//
	
	//----------------//
	
	


	Tank_hull hull("tank_hull", 0.4, 0.2, 1, 2, 1, 38000, 165);
	Tank_turret turret("tank_tower", 10, 10, 10, 10, 45, 100, 0.8, 1.5, 0.5, 25);
	Player *player = new Player(player_body, &hull, &turret, 0, 0, 0, 0, 0, 0, 0, 0);
	
	player->set_position(2048.0f, 0 + (screen_height / 2));
	o_manager.add_object(player);

	
	

	


	//----Animation test----//
	sf::Texture animtexture;
	animtexture.loadFromFile("hit_explosion_animation.png");

	Animation explosion;
	explosion.setSpriteSheet(animtexture);
	
	for (int i = 0; i <= 12; i++)
	{
		explosion.addFrame(sf::IntRect(i * 256, 0, 256, 256));
	}

	Animation* currentAnimation = &explosion;

	AnimatedSprite animatedSprite(sf::seconds(0.05f), true, false);
	//----Animation test----//
	
	//----Animation test----//
	sf::Texture animtexture2;
	animtexture2.loadFromFile("animation_cloud_explosion_512.png");

	Animation explosion2;
	explosion2.setSpriteSheet(animtexture2);

	for (int i = 0; i <= 16; i++)
	{
		explosion2.addFrame(sf::IntRect(i * 512, 0, 512, 512));
	}

	Animation* currentAnimation2 = &explosion2;

	AnimatedSprite animatedSprite2(sf::seconds(0.05f), true, false);
	//----Animation test----//
	//
	//b2d
	//float SCALE = 30.f;
	//b2BodyDef BodyDef2;
	//BodyDef2.position = b2Vec2(player->get_position().x / SCALE, player->get_position().y + 20 / SCALE);
	//BodyDef2.type = b2_kinematicBody;
	//BodyDef2.bullet = true;
	//
	//b2Body* Body2 = world.CreateBody(&BodyDef2);
	//b2PolygonShape Shape2;
	//Shape.SetAsBox((10.f) / SCALE, (10.f) / SCALE);
	//b2FixtureDef FixtureDef2;
	//FixtureDef.density = 1.f;
	//FixtureDef.friction = 0.7f;
	//FixtureDef.shape = &Shape;
	//Body->CreateFixture(&FixtureDef2);
	//
	//view->setCenter(player.get_position());
	
	sf::Clock clock;
	while (!is_exiting())
	{
		sf::Event event;
		window->pollEvent(event);

		switch (_game_state)
		{
		case Game::showing_menu:
		{
			show_menu(window);
			break;
		}
		case Game::showing_splash:
		{
			show_splash_screen(window);
			break;
		}
		case Game::playing:
		{
			window->clear(sf::Color(100, 200, 0));

			sf::Time elapsed = clock.restart();

			set_view(view, player);

			world.Step(1.0f / 60.0f, 8, 4);
			
			//----Animation test----//
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				animatedSprite.play(*currentAnimation);
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(*window);
				sf::Vector2f coord_pos = window->mapPixelToCoords(pixel_pos);
				animatedSprite.setPosition(coord_pos.x - 100, coord_pos.y - 100);
			}
			animatedSprite.update(elapsed);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				animatedSprite2.play(*currentAnimation2);
				animatedSprite2.setPosition(player->get_position().x - 258, player->get_position().y - 258);
			}
			animatedSprite2.update(elapsed);

			

		//-----------------Firing Main Gun--------------------------------------//

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{


				if (player->get_can_fire() == true)
				{

					//--ammo_b2_body-----//
					
					b2Body* ammo_body;

					b2BodyDef ammoBodyDef;
					ammoBodyDef.position = b2Vec2((((player->get_position().x) + (-cos(player->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE), ((player->get_position().y) + (-sin(player->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE);
					ammoBodyDef.type = b2_kinematicBody;
					//ammoBodyDef.bullet = true;

					ammo_body = world.CreateBody(&ammoBodyDef);

					b2PolygonShape shape_ammo;
					shape_ammo.SetAsBox((10.f) / SCALE, (10.f) / SCALE);
					b2FixtureDef AmmoFixtureDef;
					/*AmmoFixtureDef.density = 0.02f;
					AmmoFixtureDef.friction = 4.7f;*/
					
					AmmoFixtureDef.shape = &shape_ammo;
					
					ammo_body->CreateFixture(&AmmoFixtureDef);
					//ammo_body->SetUserData(this);
					

					//------------------------//

				Ammo *round = new Ammo("box", ammo_body, 12.0f, 1.0, 3.0, player->get_position().x, player->get_position().y);

				float x = 0;
				float y = 0;
				
				
				//x = (player->get_rotation_turret());
				//y = (player->get_rotation_turret());
				
				
				x = round->get_velocity() * (-cos(player->get_rotation_turret() / (180.0f/b2_pi)));
				y = round->get_velocity() * (-sin(player->get_rotation_turret() / (180.0f / b2_pi)));
				round->set_velocity(x, y, ammo_body);
				//std::cout << __LINE__  << "Fired main gun!"<< std::endl;
				//float ammo_location_x = (player->get_position().x);
				//float ammo_location_y = (player->get_position().y);
				//
				//
				//
				//Ammo *round = new Ammo(BodyDef2);
				//o_manager.add_object(round);
				//round->set_position(ammo_location_x, ammo_location_y + 10);

				player->set_cooldown();
				ammo_vector.push_back(round);
				
				}


			}

			//----------------end of Main Gun------------------------------------------//

			
			window->setView(*view);
			window->draw(map);
			//player->update(event, window);
			//player->on_draw(window);*/
			o_manager.update(event, window);
			o_manager.draw(window);
			//----Animation test----//
			window->draw(animatedSprite);
			window->draw(animatedSprite2);
			//----Animation test----//

			for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
			{
				if (BodyIterator->GetType() == b2_dynamicBody)
				{
					sf::Sprite Sprite;
					Sprite.setTexture(BoxTexture);
					Sprite.setOrigin(20.f, 20.f);
					Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
					window->draw(Sprite);
				}

				if (BodyIterator->GetType() == b2_kinematicBody)
				{
					sf::Sprite Sprite;
					Sprite.setTexture(BoxTexture);
					Sprite.setOrigin(16.f, 16.f);
					Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
					window->draw(Sprite);
				}
				//if (BodyIterator->GetType() == b2_staticBody)
				//{
				//	sf::Sprite Sprite;
				//	Sprite.setTexture(BoxTexture);
				//	Sprite.setOrigin(16.f, 16.f);
				//	Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
				//	Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
				//	window->draw(Sprite);
				//}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(*window);
				sf::Vector2f coord_pos = window->mapPixelToCoords(pixel_pos);
				CreateBox(world, coord_pos.x, coord_pos.y);
			}


			//window.draw(sprite_tank_hull);
			//window.draw(sprite_tank_turret);
			window->draw(map2);
			window->display();

			if (event.type == sf::Event::Closed) _game_state = Game::exiting;

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) show_menu(window);
			}

			//---------reduce gun cooldown-----------------//
			player->reduce_cooldown(1);

			//-------------------check contacts------------------------------------//
			std::vector<ContactCheck>::iterator pos;
			for (pos = ContactListener->_contacts.begin();
				pos != ContactListener->_contacts.end(); ++pos) {
				ContactCheck contact = *pos;
				
				//if (contact.fixtureA == player_body->GetFixtureList()) //&&
				//	contact.fixtureB == ->GetFixtureList())
				//{
				//	std::cout << "Player hit the ammo!" << std::endl;
				//}
			}
			//--------------------------------------------------------------------------//

			//-----------------------Go through ammo and delete-----------------------------------------------//
			
			std::vector<Ammo*>::iterator it = ammo_vector.begin();
				while ( it != ammo_vector.end())
				{
					if (((*it)->get_position().x * 30)> player->get_position().x + (500) || ((*it)->get_position().x * 30)< player->get_position().x - (500) ||
						((*it)->get_position().y * 30)> player->get_position().y + (200) || ((*it)->get_position().y * 30)< player->get_position().y - (200)
						)
					{


						//(*it)->destroy();	
						world.DestroyBody((*it)->get_ammo_body());
						it = ammo_vector.erase(it);
					}
					else
						it++;
				}

			//-----------------------------------------------------------------------//

			

			break;
		}
	}
	

	
	}
	delete ContactListener;
	window->close();
	
	
	
	
}

void Game::level_creation()
{
	const int level[] =
			{
				0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
				3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
				0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3,
				3, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
				0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
				3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
				3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
				0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0,
				0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0,
				3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 3, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
				0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
				3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0,
				0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0,
				3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0,
				0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 3,
				3, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
				0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
				3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
				3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
				0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0,
				0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1, 2, 0, 0, 3, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0,
				3, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 3, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0,
				0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
				3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 2, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 3,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0,
			};
		
			map.load("tileset_green_backround.png", sf::Vector2u(128, 128), level, 32, 32);
			
			
			//Give me some trees...
	const int level_trees[] =
			{
				1, 2, 0, 3, 1, 1, 2, 0, 0, 1, 2, 2, 3, 1, 1, 1,
				2, 1, 0, 3, 0, 0, 2, 0, 0, 1, 2, 0, 3, 1, 0, 1,
				1, 1, 1, 1, 3, 3, 2, 0, 0, 3, 3, 3, 3, 2, 3, 1,
				3, 1, 0, 1, 1, 0, 1, 0, 0, 1, 2, 3, 3, 1, 0, 1,
				3, 2, 3, 3, 0, 0, 3, 0, 0, 3, 2, 3, 3, 3, 0, 1,
				1, 3, 0, 1, 1, 1, 3, 0, 0, 2, 1, 0, 1, 1, 3, 1,
				2, 2, 2, 3, 3, 0, 1, 0, 0, 2, 2, 1, 1, 1, 3, 1,
				1, 1, 0, 3, 1, 0, 1, 0, 0, 1, 2, 0, 3, 1, 0, 1,
				1, 2, 0, 3, 1, 1, 2, 0, 0, 1, 2, 2, 3, 1, 1, 1,
				2, 1, 0, 3, 0, 0, 2, 0, 0, 1, 2, 0, 3, 1, 0, 1,
				1, 1, 1, 1, 3, 3, 2, 0, 0, 3, 3, 3, 3, 2, 3, 1,
				3, 1, 0, 1, 1, 0, 1, 0, 0, 1, 2, 3, 3, 1, 0, 1,
				3, 2, 3, 3, 0, 0, 3, 0, 0, 3, 2, 3, 3, 3, 0, 1,
				1, 3, 0, 1, 1, 1, 3, 0, 0, 2, 1, 0, 1, 1, 3, 1,
				2, 2, 2, 3, 3, 0, 1, 0, 0, 2, 2, 1, 1, 1, 3, 1,
				1, 1, 0, 3, 1, 0, 1, 0, 0, 1, 2, 0, 3, 1, 0, 1,
			};
		
			map2.load("tileset_trees.png", sf::Vector2u(256, 256), level_trees, 16, 16);
}

void Game::set_view(sf::View *view, Player *player)
{
	//Alussa siirretään kamera pelaajaan.
	if ((view->getCenter().y < 2045.0f - (screen_height / 2)) && begin_of_game == 0)
	{
		view->setCenter(player->get_position());
		begin_of_game = 1;
	}


	view->setCenter(player->get_distance_traveled());
	
	
}

void Game::show_splash_screen(sf::RenderWindow *window)
{
	SplashScreen splash_screen;
	splash_screen.show(window);
	_game_state = Game::showing_menu;
}

void Game::show_menu(sf::RenderWindow *window)
{
	MainMenu main_menu;
	MainMenu::menu_result result = main_menu.show(window);
	switch (result)
	{
	case MainMenu::exit :
		std::cout << "Exit pressed" << std::endl;
		_game_state = exiting;
		break;
	case MainMenu::play :
		std::cout << "Play pressed" << std::endl;
		_game_state = playing;
		break;

	}
}

bool Game::is_exiting()
{
	if (_game_state == Game::exiting)
		return true;
	else
		return false;
}

void Game::fire_main_gun(b2World& world, int MouseX, int MouseY, Player *player, Ammo *ammo) //, Ammo *ammo)
{
   //float angle = player->get_rotation_turret();
   //float velocity = 100;
   //for (int i = 0; i < 1000000000; i++) {
	  //// sleep(1);    // look in unistd.h
	  // x += velocity*cos(angle);  // include math.h
	  // y += velocity*sin(angle);  // angle in radian, of course
	  // // draw your sprite here, at (x, y)
   //}
   //std::cout << player->get_rotation_turret() << std::endl;

  //std::cout << x << "     " << y << std::endl;


  
}

void Game::CreateBox(b2World& world, int MouseX, int MouseY)
{
	float SCALE = 30.f;
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((20.f) / SCALE, (20.f) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
	Body->SetLinearDamping(3);
	Body->SetAngularDamping(3);
}



Game::game_state Game::_game_state = uninitialized;
ObjectManager Game::o_manager;