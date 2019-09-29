// 17/12/2018
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <bits/stdc++.h>
#define Height 860
#define Width  480
using namespace sf;
using namespace std;

struct point{
public:
    float x, y;
    point(float _x, float _y){
        x=_x;
        y=_y;
    }
};

point bird(100, 200);
point pipe(860, 230);
point _pipe(860, -120);
point PIPE(570, 250);
point _PIPE(570, -100);
point Pipe(285, 240);
point _Pipe(285, -110);
point plat(0, 404);

int n = 0, beplayed = 0; float denta_y = 0.0f, currangle = 0, denta_angle = 0; bool isDead = false, pause = true;
float angle = 0.0f, Frame = 0, animSpeed = 0.17; int Framecount = 3; bool dte = false, ready = false, F_isvalid = true;// down-to-earth
bool enablesound = true;
int tmp = 0;

bool collision(Sprite &bird, Sprite entity)
{
    bird.setOrigin(35, 7); // don't know why ???
    if(bird.getGlobalBounds().intersects(entity.getGlobalBounds())) return true;
    return false;
}

void PlayGame(RenderWindow &window)
{
    window.setFramerateLimit(60);
    Font font, classic;
    font.loadFromFile("Font/font.ttf");
    Text coder("Duc Khai Tong", font, 17);
    Text quit("  Quit: Esc", font, 17);
    classic.loadFromFile("Font/classic.ttf");
    Text note("Press F to fly                                               Press P to pause", classic, 10);
    note.setScale(0.9, 1.6);
    note.setOutlineThickness(0.7);
    note.setOutlineColor(Color::Black);
    coder.setOutlineThickness(0.7);
    coder.setOutlineColor(Color::Black);
    quit.setOutlineThickness(0.7);
    quit.setOutlineColor(Color::Black);

    Texture t1, t2, t3, t4, t5, t6, t7, t8;
    t1.loadFromFile("Images/Background.png");
    t2.loadFromFile("Images/17.png");
    t3.loadFromFile("Images/Pipedown.png");
    t4.loadFromFile("Images/Pipeup.png");
    t5.loadFromFile("Images/Plat.png");
    Sprite background(t1), bird1(t2), pipe1(t3), _pipe1(t4), PIPE1(t3), _PIPE1(t4), Pipe1(t3), _Pipe1(t4), Plat(t5);
    t2.setSmooth(true);
    // Sound in game
    SoundBuffer buff1, buff2, buff3;
    if(enablesound == true){
        buff1.loadFromFile("Sound/Wing.wav");
        buff2.loadFromFile("Sound/Point.wav");
        buff3.loadFromFile("Sound/Hit.wav");
    }
    Sound sound1(buff1), sound2(buff2), sound3(buff3);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if(event.type==Event::Closed)
                window.close();
        }
        // Game loop
        while(isDead == false){
            // F to fly, Esc to quit
            if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
            if(Keyboard::isKeyPressed(Keyboard::P)) {
                pause = true;
                dte = true;
            }
            if(Keyboard::isKeyPressed(Keyboard::F) && F_isvalid == true){
                ready = true;
                dte = false;
                pause = false;
                denta_y = -4.0f;
                sound1.play();
                currangle = -10.f;
                denta_angle = 0.0f;
            }
            // Update textures
            Frame += animSpeed;
            if(Frame > Framecount) Frame -= Framecount;
            bird1.setTextureRect(IntRect((int)Frame*34, 0, 34, 24));

            if(pause == false){
                srand(time(0));
                float temp = rand()%35 + 35;
                if( pipe.x < 10 ){
                    pipe.x = 860; pipe.y = 230 + temp;
                    _pipe.x = 860; _pipe.y = -120 + temp;
                }
                if( PIPE.x < 10 ){
                    PIPE.x = 860; PIPE.y = 250 - temp;
                    _PIPE.x = 860; _PIPE.y = -100 - temp;
                }
                if( Pipe.x < 10){
                    Pipe.x = 860; Pipe.y = 240 + temp;
                    _Pipe.x = 860; _Pipe.y = -110 + temp;
                }
                if( plat.x < -860) plat.x = 0;
                pipe.x -= 1; _pipe.x -= 1; PIPE.x -= 1; _PIPE.x -= 1; Pipe.x -= 1; _Pipe.x -= 1; plat.x -= 1;
            }

            if(dte == false && ready == true){
                denta_y += 0.33;
                bird.y += denta_y;
                if(denta_angle < 1.977f){
                    denta_angle += 0.0375f;
                    currangle += denta_angle;
                    angle = currangle;
                    bird1.setRotation(currangle);
                    bird1.rotate(angle);
                } else angle = 0.0f;
            }
            // Update score
            string str = to_string(n);
            Text score("Score: " + str, font, 17);
            score.setOutlineThickness(0.7);
            score.setOutlineColor(Color::Black);
            if ( pipe.x == bird.x || PIPE.x == bird.x || Pipe.x == bird.x){
                n++;
                sound2.play();
            }
            // Update Game Over
            if( collision(bird1, pipe1)||collision(bird1, _pipe1)||collision(bird1, PIPE1)
            ||collision(bird1, _PIPE1)||collision(bird1, Pipe1)||collision(bird1, _Pipe1) )
            {
                F_isvalid = false;
                dte = false;
                if(beplayed == 0) sound3.play();
                beplayed++;
                pause = true;
                cout << "hit" << endl;
            }

            if(collision(bird1, Plat)){
                F_isvalid = false;
                isDead = true ;
                if(beplayed == 0) sound3.play();
                Time time = milliseconds(1742);
                sleep(time);
            }

            window.clear();
            bird1.setPosition(bird.x, bird.y);
            pipe1.setPosition(pipe.x, pipe.y);
            _pipe1.setPosition(_pipe.x, _pipe.y);
            PIPE1.setPosition(PIPE.x, PIPE.y); // down
            _PIPE1.setPosition(_PIPE.x, _PIPE.y); // up
            Pipe1.setPosition(Pipe.x, Pipe.y);
            _Pipe1.setPosition(_Pipe.x, _Pipe.y);
            Plat.setPosition(plat.x, plat.y);
            score.setPosition(400, 0);
            quit.setPosition(765, 0);
            note.setPosition(70, 440);
            window.draw(background);
            window.draw(pipe1);
            window.draw(_pipe1);
            window.draw(PIPE1);
            window.draw(_PIPE1);
            window.draw(Pipe1);
            window.draw(_Pipe1);
            window.draw(Plat);
            window.draw(bird1);
            window.draw(coder);
            window.draw(quit);
            window.draw(score);
            window.draw(note);
            window.display();
        }

        if (isDead == true)
		{
		    F_isvalid = true;
		    pause = true;
		    dte = true;
		    beplayed = 0; // hit sound
		    Texture gameover, normal, pressed, medal;
		    string url;
		    if( 0<=n && n<5) url="Images/bronze.png";
		    if( 5<=n && n<10) url="Images/silver.png";
		    if(10<=n && n<20) url="Images/gold.png";
		    if(20<=n && n<30) url="Images/platinum.png";
		    medal.loadFromFile(url);
            gameover.loadFromFile("Images/GameOver.png");
            normal.loadFromFile("Images/button_play_normal.png");
            pressed.loadFromFile("Images/button_play_pressed.png");
            Sprite Gameover(gameover), Normal(normal), Pressed(pressed), Medal(medal);
            Normal.setPosition(405, 230);
            Pressed.setPosition(405, 230);
            Medal.setPosition(420, 175);
			window.clear();
		    window.draw(Gameover);
		    window.draw(Normal);
		    window.draw(Medal);
		    string str = to_string(n);
            Text yourscore(str, font, 40);
            yourscore.setOutlineThickness(1.7);
            yourscore.setOutlineColor(Color::Black);
		    yourscore.setPosition(422, 300);
		    window.draw(yourscore);
		    window.display();
		    if(Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		    if (Mouse::isButtonPressed(Mouse::Left))
            {
                if(Mouse::getPosition(window).y < 255 && Mouse::getPosition(window).y > 225){
                    window.draw(Pressed);
                    window.display();
                    if (event.type == Event::MouseButtonReleased){
                        n = 0;
                        isDead = false;
                        pause = true;
                        bird.x = 150; bird.y = 150;
                        pipe.x = 860; pipe.y = 230;
                        _pipe.x = 860; _pipe.y = -120;
                        PIPE.x = 570; PIPE.y = 250;
                        _PIPE.x = 570; _PIPE.y = -100;
                        Pipe.x = 285; Pipe.y = 240;
                        _Pipe.x = 285; _Pipe.y = -110;
                        PlayGame(window);
                    }
                }
            }
		}
    }
}

int main()
{
    RenderWindow window(VideoMode(Height, Width), "Flappy Bird by Duc Khai Tong", Style::Titlebar);
    window.setFramerateLimit(60);
    Texture button, sndon, sndoff;
	button.loadFromFile("Images/Ready.png");
	sndon.loadFromFile("Images/soundOn.png");
	sndoff.loadFromFile("Images/soundOff.png");
	Sprite Button(button), Sndon(sndon), Sndoff(sndoff);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
		}
		window.draw(Button);
		if(enablesound == true) window.draw(Sndon);
		if(enablesound == false) window.draw(Sndoff);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
		    if(Mouse::getPosition(window).y < 400 && Mouse::getPosition(window).y > 100) PlayGame(window);
        }
        if(Keyboard::isKeyPressed(Keyboard::Space)) PlayGame(window);
        if(Mouse::isButtonPressed(Mouse::Left) && Mouse::getPosition(window).y < 35) tmp = 1;

        if( enablesound == true && tmp == 1 ){
            tmp = 0;
            enablesound = false;
        }
        if( enablesound == false && tmp == 1 ){
            tmp = 0;
            enablesound = true;
        }
		window.display();
	}
    return 0;
}


