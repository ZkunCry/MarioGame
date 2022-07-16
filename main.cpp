#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
using namespace sf;



class PLAYER
{
public:
	float dx, dy;
	int dir = 0; // направление движения игрока
	FloatRect rect;
	String File; //файл с расширением
	Texture texture; // сфмл текстура
	Sprite s; //спрайт
	bool OnGround;
	float CurrentFrame;
	bool life;

	PLAYER(String F)
	{
		File = F;
		texture.loadFromFile(F);
		s.setTexture(texture);
		rect = FloatRect(100, 180, 16, 16);
		CurrentFrame = 0;
		dx = dy = 0.1;
		life = true;
	}

	void update(float time)
	{

		rect.left += dx * time; //движение игрока по x
		interactionMap(0);

		if (!this->OnGround)
		{
			dy += 0.0005 * time;
		}// если мы не на земле то падаем с ускорением
		else
			s.setTextureRect(IntRect(80, 144, 16, 16));
		rect.top +=dy * time; // Перемещение игрока(скорость) y
		OnGround = false;

		interactionMap(1);

		CurrentFrame += time * 0.005;

		if (CurrentFrame > 3)
			CurrentFrame -= 3;

		if (dx > 0)
			s.setTextureRect(IntRect(112 + 31 * int(CurrentFrame), 144, 16, 16));// анимация вправо
		if (dx < 0)
			s.setTextureRect(IntRect(112 + 31 * int(CurrentFrame) + 16, 144, -16, 16)); //анимация влево

		s.setPosition(rect.left - offsetX,rect.top - offsetY); //выводим спрайт в позицию
		dx = 0;
	}
	float GetCoordX()
	{
		return rect.left;

	}
	float GetCoordY()
	{
		return rect.top;

	}
	void interactionMap(int num) //Взаимодействие игрока с картой
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't')|| (TileMap[i][j] == 'y'))
				{
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;  
						dy = 0;   
						OnGround = true;
					}
					if (dy < 0 && num == 1)
					{
						rect.top = i * 16 + 16;   
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
				}
				if (TileMap[i][j] == 'c') {
					 TileMap[i][j]=' '; 
				}if (TileMap[i][j] == 'q')
					continue;
			}
	}
};
class ENEMY
{
public:
	float dx; //скорость противника по х
	bool life; //жив ли он после того как марио на него прыгнул
	Sprite sprite; //загрузка спрайта 
	Texture texture;
	String File;
	FloatRect rect; // данная переменная хранит координаты по х у и высоту и ширину прямоугольника(Спрайта)
	float currentFrame; //скорость анимации
	ENEMY()
	{
		dx = 0.05;
		rect = FloatRect(30 * 16, 13 * 16, 16, 16);
		currentFrame = 0;
		life = true;
	}
	ENEMY(String F, int x, int y)
	{
		File = F;
		texture.loadFromFile(F); //загружаем в текстуру текстуру
		sprite.setTexture(texture); //теперь загружаем в спрайт текстуру
		rect = FloatRect(x, y, 16, 16); //задаем ширину, высоту, координаты по х и у
		dx = 0.05; //задаем первоначальную скорость
		currentFrame = 0; // и анимацию
		life = true; //также делаем живым его
	}
	void update(float time) 
	{
		rect.left += dx * time;
		interactionMap();
		currentFrame += time * 0.005;
		if (currentFrame > 2) currentFrame -= 2;
		sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life)
			sprite.setTextureRect(IntRect(58, 0, 16, 16));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}
	void interactionMap() //Взаимодействие врага с картой
	{
		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0') || (TileMap[i][j] == 't') || (TileMap[i][j] == 'r')|| (TileMap[i][j] == 'y'))
				{
					if (dx > 0)
					{
						rect.left = j * 16 - rect.width;
						dx*= -1;
					}
					else if (dx < 0)
					{
						rect.left = j * 16 + 16;
						dx *= -1;
					}

				}
			}
	}

};


int main()
{
	RenderWindow window(VideoMode(400, 250), "SFML works!");
	const int Length = 25;
	PLAYER Mario("Mario.png");
	ENEMY Gumba[Length];
	Gumba[0] = ENEMY("Mario.png", 30* 16, 13 * 16);
	Gumba[1] = ENEMY("Mario.png", 58 * 16, 13 * 16);
	Gumba[2] = ENEMY("Mario.png", 80 * 16, 13 * 16);
	Gumba[3] = ENEMY("Mario.png", 85 * 16, 13 * 16);
	Clock clock;

	Image map_image;
	map_image.loadFromFile("Mario.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite sprite;
	sprite.setTexture(map);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time/500;
		if (time > 20) time = 20;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Mario.life)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				Mario.dx = -0.1; // при нажатии влево ускорение становится отрицательным
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				Mario.dx = 0.1; // и наоборот
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				if (Mario.OnGround) // если мы на земле то придаем ускорение персонажу 
				{
					Mario.dy = -0.27;
					Mario.OnGround = false;
					Mario.s.setTextureRect(IntRect(229, 144, 16, 16));
				}
			}
		}
		Mario.update(time);
		int j = 0;
		while (j != 4)
		{
			Gumba[j].update(time);
			j++;
		}
		j = 0;
		int i = 0;
		while (i != 4)
		{
			if (Mario.rect.intersects(Gumba[i].rect))
			{
				if (Gumba[i].life)
				{
					if (Mario.dy > 0)
					{
						Gumba[i].dx = 0; Mario.dy = -0.2; Gumba[i].life = false;
					}
					else
					{
						Mario.s.setColor(Color::Red);
						Mario.life = false;
						Gumba[i].life = true;
					}

				}

			}
			i++;
		}
		if (Mario.rect.left > 200) offsetX = Mario.rect.left - 200;
		if (Mario.rect.top > 125) offsetY = Mario.rect.top - 125;

		window.clear(Color(107, 140, 255));

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')  sprite.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

				if (TileMap[i][j] == 'k')  sprite.setTextureRect(IntRect(143, 112, 16, 16));

				if (TileMap[i][j] == 'c')  sprite.setTextureRect(IntRect(143 - 16, 112, 16, 16));

				if (TileMap[i][j] == 't')  sprite.setTextureRect(IntRect(0, 47, 32, 95 - 47));

				if (TileMap[i][j] == 'g')  sprite.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

				if (TileMap[i][j] == 'G')  sprite.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

				if (TileMap[i][j] == 'd')  sprite.setTextureRect(IntRect(0, 106, 74, 127 - 106));

				if (TileMap[i][j] == 'w')  sprite.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

				if (TileMap[i][j] == 'r')  sprite.setTextureRect(IntRect(143 - 32, 112, 16, 16));

				if (TileMap[i][j] == 'u')  sprite.setTextureRect(IntRect(48, 57, 45, 23));

				if (TileMap[i][j] == 'y')  sprite.setTextureRect(IntRect(0, 79, 32, 18)); 

				if (TileMap[i][j] == 'W')  sprite.setTextureRect(IntRect(4, 224, 88, 32));

				if (TileMap[i][j] == '2')  sprite.setTextureRect(IntRect(94, 159, 66, 33));

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'q')) continue;

				sprite.setPosition(j * 16-offsetX, i * 16-offsetY);
				window.draw(sprite);
			}
		}

		window.draw(Mario.s);
		window.draw(Gumba[0].sprite);
		window.draw(Gumba[1].sprite);
		window.draw(Gumba[2].sprite);
		window.draw(Gumba[3].sprite);
		window.display();

	}
	return 0;
}