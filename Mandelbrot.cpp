#include<SFML/Graphics.hpp>
#include<iostream>
#include<complex>
using namespace std;

 const int W=800;
 const int H=600;
 double CenterX=-0.5;
 double CenterY=0;
 bool needdrraw;
 int MAX_ITER=100;
 sf::Image image(sf::Vector2u(W,H));
 sf::Texture text(sf::Vector2u(W,H));
 sf::Sprite spr(text);
 bool dragging;
 double zoom=1;
 void mandelbrot()
 {
     image.resize(sf::Vector2u(W,H),sf::Color::Black);
     for(int px=0;px<W;px++)
     {
        for(int py=0;py<H;py++)
        {
            double cx=CenterX+(px-W/2.0)*4.0/(W*zoom);
            double cy=CenterY+(py-H/2.0)*4.0/(H*zoom);
            double zx=0;
            double zy=0;
            int iter=0;
            while(zx*zx+zy*zy<=4 && iter<MAX_ITER )
            {
                 double temp=zx*zx-zy*zy+cx;
                 zy=2*zx*zy+cy;
                 zx=temp;
                 iter++;

            }
            sf::Color color;
            if(iter==MAX_ITER)
            {
                 color=sf::Color::Black;
            }
            else
            {
                color=sf::Color((iter*5%255),(iter*2)%255,(iter*8)%255);
            }
            image.setPixel(sf::Vector2u(px,py),color);

        }

     }
   text.update(image );

 }
 int main()
 {
    sf::RenderWindow window(sf::VideoMode({W,H}),"WINDOW");
   
    sf::Vector2i lastpos;
    mandelbrot();
    while(window.isOpen())
    {

        while(const std::optional event=window.pollEvent())
        {
            if(event->is<sf::Event ::Closed>())
            {
                window.close();
            }
            if(const auto*wheel=event->getIf<sf::Event::MouseWheelScrolled>())
            {  auto mousePos=sf::Mouse::getPosition(window);
                float data=wheel->delta;
                double mouse_x=mousePos.x;
                double mouse_y=mousePos.y;
                double beforeX=CenterX+(mouse_x -W/2.0)*4.0/(W*zoom);
                 double beforeY=CenterY+(mouse_y -H/2.0)*4.0/(H*zoom);
                 if(data>0)
                 {
                    zoom*=1.1;
                    MAX_ITER=100+(int)(50*log10(zoom));
                 }
                 else{
                    zoom/=1.1;
                    MAX_ITER=100+(int)(50*log10(zoom));
                    if(MAX_ITER<100)MAX_ITER=100;
                 }
                 double after_x=(double)CenterX+(mouse_x-(W/2.0))*4.0/(W*zoom);
                 double after_y=(double)CenterY+(mouse_y-(H/2.0))*4.0/(H*zoom);
                 CenterX+=(beforeX-after_x);
                 CenterY+=(beforeY-after_y);
                needdrraw=true;
            }
            if(const auto pressed=event->getIf<sf::Event::MouseButtonPressed>())
            {
                   dragging=true;
                  lastpos=sf::Mouse::getPosition(window);
            }
            if(const auto released=event->getIf<sf::Event::MouseButtonReleased>() )
                    dragging =false;
        
        
        if(const auto b=event->getIf<sf::Event::MouseMoved>()){
               if(dragging)
               {
                 sf::Vector2i newpos=sf::Mouse::getPosition(window);
                 double dx=lastpos.x-newpos.x;
                 double dy=lastpos.y-newpos.y;

                  CenterX+=dx*4.0/(W*zoom);
                  CenterY+=dy*4.0/(H*zoom);
                  lastpos=newpos;
                  needdrraw=true;
               }
        }
        
    }
    if(needdrraw)
        {
             mandelbrot();
             needdrraw=false;

        }
    window.clear();
    window.draw(spr);
    window.display();
 }
}
