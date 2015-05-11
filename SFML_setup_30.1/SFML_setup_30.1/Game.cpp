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

	//---death_image--//
	sf::Texture image;
	if (image.loadFromFile("game_over.png") != true)
	{
		return;
	}

	sf::Sprite game_over_sprite(image);
	//---after_death_timer---//
	time_passed_after_death = 60 * 10;

	//---------Contact Listener-----------------//
	ContactListener = new MyContactListener();
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
	player_body->SetUserData("player");
	player_body->CreateFixture(&FixtureDef);
	player_body->SetTransform(b2Vec2(2048.0 / SCALE, (screen_height / 2) / SCALE),0);
	//Tank movement dampening
	player_body->SetLinearDamping(5);
	player_body->SetAngularDamping(10);
	//---player_b2_body---//

	//---enemy_b2_body---//
	b2BodyDef BodyDef2;
	BodyDef2.type = b2_dynamicBody;

	b2PolygonShape Shape2;
	Shape2.SetAsBox((31.f) / SCALE, (66.f) / SCALE);

	b2FixtureDef FixtureDef2;
	b2Body* enemy_body1 = world.CreateBody(&BodyDef2);
	FixtureDef2.density = 10.f;
	FixtureDef2.friction = 0.7f;
	FixtureDef2.shape = &Shape2;
	enemy_body1->SetUserData("enemy1");
	enemy_body1->CreateFixture(&FixtureDef2);
	enemy_body1->SetTransform(b2Vec2(2048.0/ SCALE, ((screen_height / 2) +500)/ SCALE), 0);
	//Tank movement dampening
	enemy_body1->SetLinearDamping(5);
	enemy_body1->SetAngularDamping(10);
	//---enemy_b2_body---//
	
	//---enemy_b2_body---//
	b2BodyDef BodyDef3;
	BodyDef3.type = b2_dynamicBody;

	b2PolygonShape Shape3;
	Shape3.SetAsBox((31.f) / SCALE, (66.f) / SCALE);

	b2FixtureDef FixtureDef3;
	b2Body* enemy_body2 = world.CreateBody(&BodyDef2);
	FixtureDef3.density = 10.f;
	FixtureDef3.friction = 0.7f;
	FixtureDef3.shape = &Shape2;
	enemy_body2->SetUserData("enemy2");
	enemy_body2->CreateFixture(&FixtureDef2);
	enemy_body2->SetTransform(b2Vec2(2048.0 / SCALE, ((screen_height / 2) + 2000) / SCALE), 0);
	//Tank movement dampening
	enemy_body2->SetLinearDamping(5);
	enemy_body2->SetAngularDamping(10);
	//---enemy_b2_body---//
	//------ammo_b2_body----------//
	//----------------//
	
	

	Tank_hull hull("tank_hull", 0.4, 0.2, 1, 2, 1, 38000, 165);
	Tank_turret turret("tank_tower", 10, 10, 10, 10, 45, 100, 0.8, 1.5, 0.5, 25);
	Tank_hull hull2("tank_hull", 0.4, 0.2, 1, 2, 1, 38000, 165);
	Tank_turret turret2("tank_tower", 10, 10, 10, 10, 45, 100, 0.8, 1.5, 0.5, 25);
	Tank_hull hull3("tank_hull", 0.4, 0.2, 1, 2, 1, 38000, 165);
	Tank_turret turret3("tank_tower", 10, 10, 10, 10, 45, 100, 0.8, 1.5, 0.5, 25);
	Player *player = new Player(player_body, &hull, &turret, 0, 0, 0, 0, 0, 0, 0, 0);
	Enemy *enemy1 = new Enemy(enemy_body1, &hull2, &turret2, 0, 0, 0, 0, 0, 0, 0, 0);
	Enemy *enemy2 = new Enemy(enemy_body2, &hull3, &turret3, 0, 0, 0, 0, 0, 0, 0, 0);
	//player->set_body_position(500, 0);
	//enemy->set_position(2048.0f + 250, 0 + (screen_height / 2) + 250);
	o_manager.add_object(player);
	o_manager.add_object(enemy1);
	o_manager.add_object(enemy2);

	AiManager *ai_manager = new AiManager();
	
	//----Hit_Explosion_Animation----//
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
	//----Animation----//
	
	//----Explosion_Animation----//
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
	//----Animation----//

	//----Shooting_Animation----//
	sf::Texture animtexture3;
	animtexture3.loadFromFile("turret_shooting_animation.png");

	Animation explosion3;
	explosion3.setSpriteSheet(animtexture3);

	for (int i = 0; i <= 16; i++)
	{
		explosion3.addFrame(sf::IntRect(i * 256, 0, 256, 256));
	}

	Animation* currentAnimation3 = &explosion3;

	AnimatedSprite animatedSprite3(sf::seconds(0.05f), true, false);
	animatedSprite3.setOrigin(128, 128);

	//enemy_animations
	Animation* currentAnimation4 = &explosion3;

	AnimatedSprite animatedSprite4(sf::seconds(0.05f), true, false);
	animatedSprite4.setOrigin(128, 128);

	Animation* currentAnimation5 = &explosion3;

	AnimatedSprite animatedSprite5(sf::seconds(0.05f), true, false);
	animatedSprite5.setOrigin(128, 128);
	//----Animation----//
	
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
		case Game::showing_game_over:
		{
			show_game_over(window);
			break;
		}		
		case Game::playing:
		{
			window->clear(sf::Color(100, 200, 0));

			sf::Time elapsed = clock.restart();

			set_view(view, player);

			world.Step(1.0f / 60.0f, 8, 4);
			
			//----Animation test----//
	/*		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				animatedSprite.play(*currentAnimation);
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(*window);
				sf::Vector2f coord_pos = window->mapPixelToCoords(pixel_pos);
				animatedSprite.setPosition(coord_pos.x - 100, coord_pos.y - 100);
			}*/


	/*		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				animatedSprite2.play(*currentAnimation2);
				animatedSprite2.setPosition(player->get_position().x - 258, player->get_position().y - 258);
			}*/

			


		//-----------------Firing Main Gun--------------------------------------//

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->get_health()>0)
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
					shape_ammo.SetAsBox((10.f) / SCALE, (5.f) / SCALE);
					b2FixtureDef AmmoFixtureDef;
					/*AmmoFixtureDef.density = 0.02f;
					AmmoFixtureDef.friction = 4.7f;*/
					
					AmmoFixtureDef.shape = &shape_ammo;
					ammo_body->SetUserData("ammo");
					ammo_body->CreateFixture(&AmmoFixtureDef);
					


					//------------------------//

				Ammo *round = new Ammo("ammo", ammo_body, 12.0f, 1.0, 3.0, player->get_position().x, player->get_position().y);

				float x = 0;
				float y = 0;
				
				
				//x = (player->get_rotation_turret());
				//y = (player->get_rotation_turret());
				
				
				x = round->get_velocity() * (-cos(player->get_rotation_turret() / (180.0f/b2_pi)));
				y = round->get_velocity() * (-sin(player->get_rotation_turret() / (180.0f / b2_pi)));
				
				round->set_velocity(x, y);
				round->set_rotation(player->get_rotation_turret() / (180.0f / b2_pi));
				
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

				
				animatedSprite3.setPosition((player->get_position().x) + (180 * (-cos(player->get_rotation_turret() / (180.0f / b2_pi)))), (player->get_position().y) + (180 * (-sin(player->get_rotation_turret() / (180.0f / b2_pi)))));
				animatedSprite3.setRotation(player->get_rotation_turret()-90);
				animatedSprite3.play(*currentAnimation3);
				
				}


			}

			//----------------end of Main Gun------------------------------------------//

			//---enemy1_firing---//
			if (enemy1->get_health() <= 0)
			{
				enemy1->set_can_fire_false();
			}
			
			else if (player->get_position().y - enemy1->get_position().y < 600 || enemy1->get_health()>0)
			{
				

				if (enemy1->get_can_fire() == true && player->get_health()>0)
				{

					//--ammo_b2_body-----//

					b2Body* ammo_body;

					b2BodyDef ammoBodyDef;
					ammoBodyDef.position = b2Vec2((((enemy1->get_position().x) + (-cos(enemy1->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE), ((enemy1->get_position().y) + (-sin(enemy1->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE);
					ammoBodyDef.type = b2_kinematicBody;
					//ammoBodyDef.bullet = true;

					ammo_body = world.CreateBody(&ammoBodyDef);

					b2PolygonShape shape_ammo;
					shape_ammo.SetAsBox((10.f) / SCALE, (5.f) / SCALE);
					b2FixtureDef AmmoFixtureDef;
					/*AmmoFixtureDef.density = 0.02f;
					AmmoFixtureDef.friction = 4.7f;*/

					AmmoFixtureDef.shape = &shape_ammo;
					ammo_body->SetUserData("ammo");
					ammo_body->CreateFixture(&AmmoFixtureDef);



					//------------------------//

					Ammo *round = new Ammo("ammo", ammo_body, 12.0f, 1.0, 3.0, enemy1->get_position().x, enemy1->get_position().y);

					float x = 0;
					float y = 0;


					//x = (player->get_rotation_turret());
					//y = (player->get_rotation_turret());


					x = round->get_velocity() * (-cos(enemy1->get_rotation_turret() / (180.0f / b2_pi)));
					y = round->get_velocity() * (-sin(enemy1->get_rotation_turret() / (180.0f / b2_pi)));

					round->set_velocity(x, y);
					round->set_rotation(enemy1->get_rotation_turret() / (180.0f / b2_pi));

					//std::cout << __LINE__  << "Fired main gun!"<< std::endl;
					//float ammo_location_x = (player->get_position().x);
					//float ammo_location_y = (player->get_position().y);
					//
					//
					//
					//Ammo *round = new Ammo(BodyDef2);
					//o_manager.add_object(round);
					//round->set_position(ammo_location_x, ammo_location_y + 10);

					enemy1->set_cooldown();
					ammo_vector.push_back(round);

					animatedSprite4.setPosition((enemy1->get_position().x) + (180 * (-cos(enemy1->get_rotation_turret() / (180.0f / b2_pi)))), (enemy1->get_position().y) + (180 * (-sin(enemy1->get_rotation_turret() / (180.0f / b2_pi)))));
					animatedSprite4.setRotation(enemy1->get_rotation_turret() - 90);
					animatedSprite4.play(*currentAnimation4);

				}
			}

			//---enemy2_firing---//
			if (enemy2->get_health() <= 0)
			{
				enemy2->set_can_fire_false();
			}
			
			else if (player->get_position().y - enemy2->get_position().y < 600 || enemy2->get_health()>0)
			{


				if (enemy2->get_can_fire() == true && player->get_health()>0)
				{

					//--ammo_b2_body-----//

					b2Body* ammo_body;

					b2BodyDef ammoBodyDef;
					ammoBodyDef.position = b2Vec2((((enemy2->get_position().x) + (-cos(enemy2->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE), ((enemy2->get_position().y) + (-sin(enemy2->get_rotation_turret() / (180.0f / b2_pi))) * 90) / SCALE);
					ammoBodyDef.type = b2_kinematicBody;
					//ammoBodyDef.bullet = true;

					ammo_body = world.CreateBody(&ammoBodyDef);

					b2PolygonShape shape_ammo;
					shape_ammo.SetAsBox((10.f) / SCALE, (5.f) / SCALE);
					b2FixtureDef AmmoFixtureDef;
					/*AmmoFixtureDef.density = 0.02f;
					AmmoFixtureDef.friction = 4.7f;*/

					AmmoFixtureDef.shape = &shape_ammo;
					ammo_body->SetUserData("ammo");
					ammo_body->CreateFixture(&AmmoFixtureDef);

			

					//------------------------//

					Ammo *round = new Ammo("ammo", ammo_body, 12.0f, 1.0, 3.0, enemy2->get_position().x, enemy2->get_position().y);

					float x = 0;
					float y = 0;


					//x = (player->get_rotation_turret());
					//y = (player->get_rotation_turret());


					x = round->get_velocity() * (-cos(enemy2->get_rotation_turret() / (180.0f / b2_pi)));
					y = round->get_velocity() * (-sin(enemy2->get_rotation_turret() / (180.0f / b2_pi)));

					round->set_velocity(x, y);
					round->set_rotation(enemy2->get_rotation_turret() / (180.0f / b2_pi));

					//std::cout << __LINE__  << "Fired main gun!"<< std::endl;
					//float ammo_location_x = (player->get_position().x);
					//float ammo_location_y = (player->get_position().y);
					//
					//
					//
					//Ammo *round = new Ammo(BodyDef2);
					//o_manager.add_object(round);
					//round->set_position(ammo_location_x, ammo_location_y + 10);

					enemy2->set_cooldown();
					ammo_vector.push_back(round);

					animatedSprite5.setPosition((enemy2->get_position().x) + (180 * (-cos(enemy2->get_rotation_turret() / (180.0f / b2_pi)))), (enemy2->get_position().y) + (180 * (-sin(enemy2->get_rotation_turret() / (180.0f / b2_pi)))));
					animatedSprite5.setRotation(enemy2->get_rotation_turret() - 90);
					animatedSprite5.play(*currentAnimation5);
				}
			}

			if (player->get_health() <= 0 && player->get_has_animation_played() == false)
			{
				animatedSprite2.setPosition(player->get_position().x - 256, player->get_position().y - 256);
				animatedSprite2.play(*currentAnimation2);
				player->set_animation_has_played();
			}
			if (enemy1->get_health() <= 0 && enemy1->get_has_animation_played() == false)
			{				
				animatedSprite2.setPosition(enemy1->get_position().x - 256, enemy1->get_position().y - 256);
				animatedSprite2.play(*currentAnimation2);
				enemy1->set_animation_has_played();
			}
			if (enemy2->get_health() <= 0 && enemy2->get_has_animation_played() == false)
			{				
				animatedSprite2.setPosition(enemy2->get_position().x - 256, enemy2->get_position().y - 256);
				animatedSprite2.play(*currentAnimation2);
				enemy2->set_animation_has_played();
			}

			window->setView(*view);
			window->draw(map);
			//player->update(event, window);
			//player->on_draw(window);*/
			o_manager.update(event, window);
			o_manager.draw(window);
			
			//---DrawAmmo---//
			for (std::vector<Ammo*>::const_iterator iterator = ammo_vector.begin(), end = ammo_vector.end(); iterator != end; ++iterator)
			{
				(*iterator)->on_update(window);
				(*iterator)->on_draw(window);
			}
			//--------------//

			//----Animations----//
			animatedSprite.update(elapsed);
			animatedSprite2.update(elapsed);
			animatedSprite3.update(elapsed);
			animatedSprite4.update(elapsed);
			animatedSprite5.update(elapsed);
			window->draw(animatedSprite);
			window->draw(animatedSprite2);
			window->draw(animatedSprite3);
			window->draw(animatedSprite4);
			window->draw(animatedSprite5);
			//----Animations----//

			/*if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(*window);
				sf::Vector2f coord_pos = window->mapPixelToCoords(pixel_pos);
				CreateBox(world, coord_pos.x, coord_pos.y);
			}*/

		
			//window.draw(sprite_tank_hull);
			//window.draw(sprite_tank_turret);
			window->draw(map2);
		

			//---after_player_dies---//
			if (player->get_health() < 0)
			{
				window->setView(window->getDefaultView());
				window->draw(game_over_sprite);
			}
			//---after_player_dies---//

			//---Draw_display---//
			window->display();

			//---------reduce gun cooldown-----------------//
			player->reduce_cooldown(1);
			enemy1->reduce_cooldown(1);
			enemy2->reduce_cooldown(1);

			//-------------------check contacts------------------------------------//
			std::vector<ContactCheck>::iterator pos;
			for (pos = ContactListener->_contacts.begin();
				pos != ContactListener->_contacts.end(); ++pos) {
				ContactCheck contact = *pos;
				
				if ((contact.fixtureA->GetBody()->GetUserData() == "ammo" && contact.fixtureB->GetBody()->GetUserData() == "player") ||
					(contact.fixtureA->GetBody()->GetUserData() == "player" && contact.fixtureB->GetBody()->GetUserData() == "ammo"))
				{													
					player->reduce_health(1);
				}
				if ((contact.fixtureA->GetBody()->GetUserData() == "ammo" && contact.fixtureB->GetBody()->GetUserData() == "enemy1") ||
					(contact.fixtureA->GetBody()->GetUserData() == "enemy1" && contact.fixtureB->GetBody()->GetUserData() == "ammo"))
				{													
					enemy1->reduce_health(1);
				}
				if ((contact.fixtureA->GetBody()->GetUserData() == "ammo" && contact.fixtureB->GetBody()->GetUserData() == "enemy2") ||
					(contact.fixtureA->GetBody()->GetUserData() == "enemy2" && contact.fixtureB->GetBody()->GetUserData() == "ammo"))
				{
					enemy2->reduce_health(1);
				}
				
			}
			//--------------------------------------------------------------------------//

			//-----------------------Go through ammo and delete-----------------------------------------------//
			
			std::vector<Ammo*>::iterator it = ammo_vector.begin();
				while ( it != ammo_vector.end())
				{
					if ((*it)->get_timer() <= 0 )/*(((*it)->get_position().x * SCALE)> player->get_position().x + (500) || ((*it)->get_position().x * SCALE)< player->get_position().x - (500) ||
						((*it)->get_position().y * SCALE)> player->get_position().y + (300) || ((*it)->get_position().y * SCALE)< player->get_position().y - (300)
						)*/
					{


						//(*it)->destroy();	
						world.DestroyBody((*it)->get_ammo_body());
						it = ammo_vector.erase(it);
					}
					else
						it++;
				}

			//-----------------------------------------------------------------------//

			
			//------------------------Handling_AI----------------------------------//
			ai_manager->update(player, enemy1);
			ai_manager->update(player, enemy2);

				

			//-------------------------End_of_Handling_AI--------------------------//

			break;
		}
	}

	if (event.type == sf::Event::Closed) _game_state = Game::exiting;

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape) show_menu(window);
	}	
	
	//---wait_before_final_gameover---//
	if (player->get_health() < 0)
	{
		time_passed_after_death--;
		
		if (time_passed_after_death <= 0)
		{
			show_game_over(window);
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

void Game::show_game_over(sf::RenderWindow *window)
{
	GameOver game_over;
	game_over.show(window);
	_game_state = exiting;
}

bool Game::is_exiting()
{
	if (_game_state == Game::exiting)
		return true;
	else
		return false;
}

//void Game::CreateBox(b2World& world, int MouseX, int MouseY)
//{
//	float SCALE = 30.f;
//	b2BodyDef BodyDef;
//	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
//	BodyDef.type = b2_dynamicBody;
//	b2Body* Body = world.CreateBody(&BodyDef);
//
//	b2PolygonShape Shape;
//	Shape.SetAsBox((20.f) / SCALE, (20.f) / SCALE);
//	b2FixtureDef FixtureDef;
//	FixtureDef.density = 1.f;
//	FixtureDef.friction = 0.7f;
//	FixtureDef.shape = &Shape;
//	//Body->CreateFixture(&FixtureDef);
//	Body->SetLinearDamping(3);
//	Body->SetAngularDamping(3);
//	Body->SetUserData("box");
//	Body->CreateFixture(&FixtureDef);
//}



Game::game_state Game::_game_state = uninitialized;
ObjectManager Game::o_manager;