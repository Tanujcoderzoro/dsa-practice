#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
int main()
{

        srand(time({0}));
        const int CELL=30;
        const int  COLS=20;
        const int ROWS=20;
        const int W=COLS *CELL;
        const int H=ROWS*CELL;
      sf::RenderWindow window(sf::VideoMode({(unsigned int)W,(unsigned int)H}),"TANUJ");
      window.setFramerateLimit(60);
      sf::Vector2i dir={0,1};
     sf::Vector2i nextdir={0,1};

       sf::Vector2i treat ={rand()%COLS,rand()%ROWS};
        std::vector<sf::Vector2i>snake;
        snake.push_back({10,10});
         snake.push_back({9,10});
          snake.push_back({8,10});

         sf::Clock clock;
         float timer=0;
         float dela=0.15;
         bool gameOver=false;
         bool gameStart=false;

      while(window.isOpen())
      {
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
         {
          gameStart=true;
         }
         else if(gameStart){
        while(const std::optional event=window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();

            }
          }

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)&&dir.y!=1)nextdir={0,-1};
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)&&dir.y!=-1)nextdir={0,1};
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)&&dir.x!=1)nextdir={-1,0};
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)&&dir.x!=-1)nextdir={1,0};
             timer+=clock.restart().asSeconds();
               if(!gameOver && timer>=dela)

               {
                timer=0;
                dir=nextdir;
                 
                 sf::Vector2i newhead=snake[0]+dir;

                 if(newhead.x<0||newhead.x>=COLS ||newhead.y<0||newhead.y>=ROWS)
                 {
                  gameOver=true;
                 }
                 else{
                     for(int i=0;i<snake.size();i++)
                     {
                              if(newhead==snake[i])
                              {
                                gameOver=true;
                                break;
                              }
                     }
                 }
                 if(!gameOver)
                 {
                  snake.insert(snake.begin(),newhead);
                  if(newhead==treat)
                  {
                    treat={rand()%COLS,rand()%ROWS};
                  }
                  else{
                    snake.pop_back();
                  }
                 }
               }
          window.clear(sf::Color::Black);
          if(gameOver)
          {
            window.clear(sf::Color::Red);
          }
          else{
            sf::CircleShape treatSh(CELL/2-2);
            treatSh.setFillColor(sf::Color::Red);
            treatSh.setPosition({(float)treat.x*CELL+2,(float)treat.y*CELL+2});
            window.draw(treatSh);

            for(int i=0;i<snake.size();i++)
            {
              sf::RectangleShape block({(float)CELL-2,(float)CELL-2});
              block.setFillColor(i==0 ?sf::Color ::Green :sf::Color(0,180,0));
              block.setPosition({(float)snake[i].x*CELL+1,(float)snake[i].y*CELL+1});
              window.draw(block);
            }
          }
        }
          window.display();
      }
    return 0;
}