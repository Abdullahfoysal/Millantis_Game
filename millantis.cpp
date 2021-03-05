#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
#include<math.h>

#define win_x 1366
#define win_y 700

using namespace sf;
// using namespace std;
int player_number=2;
int player_no=1;
int player_maintain=0;
int score_count[6];



int circle_distance=50;
int Line_count=0;
int point_count=0;
int square_count=0;
int node1,node2;

//std::vector<int>adj[5*5;//row*column



int start_co_x=50,start_co_y=150;
int radius=8,thikness=5;
int line_width=8;
int row=10,column=10;
int extent=200;///score square

std::vector<int>adj[1010];//[row*column][row*column]

bool selected_circle=true;
bool blank_selected=true;
bool created_line=false;
bool player_point=false;

bool DoubleClickMouse=false;

bool menu=true;
bool home=true;
bool playerTotal=false;
bool selectarea=false;
bool helpp=false;
bool aboutt=false;
bool soundd=false;
bool p[5];
bool s[8];
float backClick=0.f;

float key=0.0f;
Vector2f sample_line_cordinate;

Vector2f circle_center;
Vector2f mouseCurrentPosition;

Vector2f first_node;
Vector2f second_node;

RenderWindow window(VideoMode(win_x,win_y),"Millantis",Style::Titlebar |Style::Close);


 struct Load
 {
 	Sprite s_sprite;
 	Texture t_texture;
    CircleShape circle;
    RectangleShape block;
    sf::ConvexShape polygon;
    Font font;
    Text text;
    String sentence;


 };


  Load dag(Vector2f(first_select_position),Vector2f(second_select_position),int distance)
    {
        Load line2;
        if(distance>30) ///distance between x-coordinate
        {
             line2.polygon.setPointCount(4);
        line2.polygon.setPoint(0, sf::Vector2f(first_select_position));
        line2.polygon.setPoint(1, sf::Vector2f(second_select_position.x,second_select_position.y-line_width));
        line2.polygon.setPoint(2, sf::Vector2f(second_select_position));
        line2.polygon.setPoint(3,sf::Vector2f(first_select_position.x,first_select_position.y+line_width));
        }
        else
        {
             line2.polygon.setPointCount(4);
        line2.polygon.setPoint(0, sf::Vector2f(first_select_position));
        line2.polygon.setPoint(1, sf::Vector2f(first_select_position.x+line_width,first_select_position.y));
        line2.polygon.setPoint(2, sf::Vector2f(second_select_position));
        line2.polygon.setPoint(3,sf::Vector2f(second_select_position.x-line_width,second_select_position.y));

        }


       // line2.polygon.setOutlineColor(sf::Color::Red);
       // line2.polygon.setOutlineThickness(5);
        line2.polygon.setPosition(0,0);
        blank_selected=true;
        return line2;
    }

    Load dag2(Vector2f(first_select_position),Vector2f(second_select_position),int direction)
    {
        Load line2;
        if(direction>30)
        {
        line2.polygon.setPointCount(4);
        line2.polygon.setPoint(0,sf::Vector2f(first_select_position));
        line2.polygon.setPoint(1,sf::Vector2f(second_select_position.x,second_select_position.y-line_width));
        line2.polygon.setPoint(2,sf::Vector2f(second_select_position));
        line2.polygon.setPoint(3,sf::Vector2f(first_select_position.x,first_select_position.y+line_width));
        }
        else
        {
              line2.polygon.setPointCount(4);
        line2.polygon.setPoint(0,sf::Vector2f(first_select_position));
        line2.polygon.setPoint(1,sf::Vector2f(first_select_position.x+line_width,first_select_position.y));
        line2.polygon.setPoint(2,sf::Vector2f(second_select_position));
        line2.polygon.setPoint(3,sf::Vector2f(second_select_position.x-line_width,second_select_position.y));
        }

      // line2.polygon.setOutlineColor(sf::Color::Red);
        //line2.polygon.setOutlineThickness(3);

        line2.polygon.setPosition(0,0);
        return line2;
    }

    Load dag3(Vector2f(starting_point))
    {
        Load rectangle;
        rectangle.block.setSize(sf::Vector2f(circle_distance-2*line_width,circle_distance-2*line_width));
       rectangle.block.setOutlineColor(sf::Color::Red);
      // rectangle.block.setOutlineThickness(5);
        rectangle.block.setPosition(Vector2f(starting_point.x+line_width/2,starting_point.y+line_width/2));
        if(player_no==1)rectangle.block.setFillColor(Color::Green);
        else if(player_no==2)rectangle.block.setFillColor(Color::Yellow);
        else if(player_no==3)rectangle.block.setFillColor(Color::Blue);
        else if(player_no==4)rectangle.block.setFillColor(Color::Red);
        else if(player_no==5)rectangle.block.setFillColor(Color::Magenta);

        score_count[player_no]++;

        player_point=false;
        return rectangle;
    }

   bool bfs(int source ,int check)
   {
        for(int i=0;i<adj[source].size();i++)
        {
          int next=adj[source][i];
          if(next==check)return true;
        }
        for(int i=0;i<8;i++)s[i]=false;
          s[1]=true;
        return false;
   }

  std::string To_string(int n)
  {
     std::string s="";
     if(n==0)return "0";
     while(n)
     {
       s+=(n%10+'0');
       n/=10;
     }
    reverse(s.begin(),s.end());
     return s;
  }



    void init()
    {
      // Load Resources[10],point[25][25],Line[1200],sample,square[600],player_score[6];

      player_no=1;
      player_maintain=0;
      Line_count=0;
      square_count=0;
     selected_circle=true;
      blank_selected=true;
     created_line=false;
     player_point=false;

        for(int i=0;i<1010;i++)
        {
            adj[i].clear();
        }
        for(int i=1;i<6;i++)score_count[i]=0;

    }

  class back_image
         {
         public:
              Texture texture;
              Sprite sprite;


              void load_image(std::string s)
              {
                texture.loadFromFile(s);
                sprite.setTexture(texture);
                sprite.setPosition(20,20);
                sprite.setScale(0.2,0.2);
              }

              void show()
              {

                window.draw(sprite);
              }

            /*  void Intersect()
              {
                if(sf::Mouse::getPosition(window).x > sprite.getGlobalBounds().left && sf::Mouse::getPosition(window).x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width && sf::Mouse::getPosition(window).y > sprite.getGlobalBounds().top && sf::Mouse::getPosition(window).y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height))
                {
                  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && backClick>0.2 )
                  {
                    menu=false;
                    gamemusic.stop();
                    menumusic.play();
                    backClock.restart();
                  }

                }
              }*/


         };

int main()
{
      row=10,column=10;
      player_number=2;


      window.setPosition(sf::Vector2i(0,0));
      sf::Mouse::setPosition(Vector2i(start_co_x+radius,start_co_y+radius),window);
      window.setVisible(true);
      window.setKeyRepeatEnabled(false);





    Load Resources[10],point[15][25],Line[500],sample,square[300],player_score[6];///for 25 * 10
//point[row][column]
    //Line[(column-1)*row*2]
    //square[(column-1)*(row-1)]

    ///load

    back_image Back;
    Back.load_image("resources/back.jpeg");

    Font font1,font2,font3,font4;
    font1.loadFromFile("resources/Hunters.otf");
    font2.loadFromFile("resources/Montague.ttf");
    font3.loadFromFile("resources/28 Days Later.ttf");
    font4.loadFromFile("resources/font6.TTF");

    Text gametxt,game_name,new_game,player_total,select_area,sound,about,help,exit;
    Text player1,player2,player3,player4,player5,customplayer,player6;
    Text a0,a1,a2,a3,a4,a5,a6,a7,player_turn;
    Text q1,q2,q3,q4,q5;
    Text p1,p2,p3,p4,p5;


    sf::Music gamemusic,menumusic;

    menumusic.openFromFile("resources/game_menu.wav");
    menumusic.setVolume(1000);

    gamemusic.openFromFile("resources/Magic-Ocean.wav");
    gamemusic.setVolume(1000);
    menumusic.play();


///score bar

    player_score[1].block.setSize(Vector2f(80,80));
    player_score[1].block.setPosition(100+extent,10);
    player_score[1].block.setFillColor(Color::Green);
    player_score[1].block.setOutlineThickness(8);
    player_score[1].block.setOutlineColor(sf::Color::Black);

    player_score[2].block.setSize(Vector2f(80,80));
    player_score[2].block.setPosition(100*2+extent,10);
    player_score[2].block.setFillColor(Color::Yellow);
    player_score[2].block.setOutlineThickness(8);
    player_score[2].block.setOutlineColor(sf::Color::Black);

    player_score[3].block.setSize(Vector2f(80,80));
    player_score[3].block.setPosition(100*3+extent,10);
    player_score[3].block.setFillColor(Color::Blue);
    player_score[3].block.setOutlineThickness(8);
    player_score[3].block.setOutlineColor(sf::Color::Black);

    player_score[4].block.setSize(Vector2f(80,80));
    player_score[4].block.setPosition(100*4+extent,10);
    player_score[4].block.setFillColor(Color::Red);
    player_score[4].block.setOutlineThickness(8);
    player_score[4].block.setOutlineColor(sf::Color::Black);

    player_score[5].block.setSize(Vector2f(80,80));
    player_score[5].block.setPosition(100*5+extent,10);
    player_score[5].block.setFillColor(Color::Magenta);
    player_score[5].block.setOutlineThickness(8);
    player_score[5].block.setOutlineColor(sf::Color::Black);



     p1.setString("Player: 1");
   p1.setFont(font1);
    p1.setCharacterSize(20);
    p1.setScale(1.5f,1.5f);
    //gametxt.setFillColor(Color::Red);
    p1.setPosition(100+extent-5,0);
    p1.setFillColor(Color::Black);

     p2.setString("Player: 2");
   p2.setFont(font1);
    p2.setCharacterSize(20);
    p2.setScale(1.5f,1.5f);
    //gametxt.setFillColor(Color::Red);
    p2.setPosition(100*2+extent-5,0);
    p2.setFillColor(Color::Black);

     p3.setString("Player: 3");
   p3.setFont(font1);
    p3.setCharacterSize(20);
    p3.setScale(1.5f,1.5f);
    //gametxt.setFillColor(Color::Red);
    p3.setPosition(100*3+extent-5,0);
    p3.setFillColor(Color::Black);

     p4.setString("Player: 4");
   p4.setFont(font1);
    p4.setCharacterSize(20);
    p4.setScale(1.5f,1.5f);
    //gametxt.setFillColor(Color::Red);
    p4.setPosition(100*4+extent-5,0);
    p4.setFillColor(Color::Black);

     p5.setString("Player: 5");
   p5.setFont(font1);
    p5.setCharacterSize(20);
    p5.setScale(1.5f,1.5f);
    //gametxt.setFillColor(Color::Red);
    p5.setPosition(100*5+extent-5,0);
    p5.setFillColor(Color::Black);





    Clock clock,playerTime,doubleClickClock,backClock;
    int text_y=50;

    gametxt.setString("Millantis Game");
    gametxt.setFont(font1);
    gametxt.setCharacterSize(80);
    gametxt.setScale(1.5f,1.5f);
    //gametxt.setFillColor(Color::Red);
    gametxt.setPosition(200,-30);
    gametxt.setFillColor(Color::Blue);



    new_game.setString("Play Game");
    new_game.setFont(font1);
    new_game.setCharacterSize(70);
    new_game.setScale(1.f,1.f);
    //gametxt.setFillColor(Color::Red);
    new_game.setPosition(200+150,100+text_y*0);
    new_game.setFillColor(Color::Yellow);

    player_total.setString("Player Number");
   player_total.setFont(font1);
    player_total.setCharacterSize(70);
    player_total.setScale(1.f,1.f);
    //gametxt.setFillColor(Color::Red);
    player_total.setPosition(200+100,100+text_y*1);
    player_total.setFillColor(Color::Yellow);

     select_area.setString("Select Area");
   select_area.setFont(font1);
    select_area.setCharacterSize(70);
    select_area.setScale(1.f,1.f);
    //gametxt.setFillColor(Color::Red);
    select_area.setPosition(200+150,100+text_y*2);
    select_area.setFillColor(Color::Yellow);

     sound.setString("Music");
   sound.setFont(font1);
    sound.setCharacterSize(70);
    sound.setScale(1.f,1.f);
    //gametxt.setFillColor(Color::Red);
    sound.setPosition(200+150,100+text_y*3);
    sound.setFillColor(Color::Yellow);

       help.setString("Help");
  help.setFont(font1);
    help.setCharacterSize(70);
    help.setScale(1.f,1.f);
    //gametxt.setFillColor(Color::Red);
   help.setPosition(200+150,100+text_y*4);
    help.setFillColor(Color::Yellow);

     about.setString("About");
   about.setFont(font1);
    about.setCharacterSize(70);
    about.setScale(1.f,1.f);
    //gametxt.setFillColor(Color::Red);
   about.setPosition(200+150,100+text_y*5);
    about.setFillColor(Color::Yellow);

      exit.setString("Exit");
  exit.setFont(font1);
    exit.setCharacterSize(70);
    exit.setScale(1.f,1.f);
    //gametxt.setFillColor(Color::Red);
   exit.setPosition(200+150,100+text_y*6);
    exit.setFillColor(Color::Yellow);

                     a7.setString("BACK");
                      a7.setFont(font1);
                      a7.setCharacterSize(70);
                      a7.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a7.setPosition(200+150,100+text_y*6);
                      a7.setFillColor(Color::Black);






      // std::cout<<"Turn for player No: "<<player_no<<std::endl;

       init();
       p[0]=true;   //  adj call to refresh  //[row*column][row*column]



    	Resources[0].t_texture.loadFromFile("resources/background1.png");
    	Resources[0].s_sprite.setTexture(Resources[0].t_texture);

    	Resources[1].t_texture.loadFromFile("resources/background2.png");
    	Resources[1].s_sprite.setTexture(Resources[1].t_texture);

    	Resources[2].t_texture.loadFromFile("resources/background3.png");
    	Resources[2].s_sprite.setTexture(Resources[2].t_texture);

    	Resources[3].t_texture.loadFromFile("resources/background4.png");
    	Resources[3].s_sprite.setTexture(Resources[3].t_texture);

    	Resources[4].t_texture.loadFromFile("resources/background5.png");
    	Resources[4].s_sprite.setTexture(Resources[4].t_texture);

    	Resources[5].t_texture.loadFromFile("resources/background6.png");
    	Resources[5].s_sprite.setTexture(Resources[5].t_texture);




         unsigned menuselect=1;
          //p[1]=true;


	 while(window.isOpen()) {




        Event event;
        while(window.pollEvent(event)) {
            if(event.type == event.Closed) window.close();
            //if (event.key.code == sf::Keyboard::Escape)menu=true;
            }

            Vector2f mouseCurrentPosition(Mouse::getPosition(window));


               if(menu)
                {
                       // menumusic.stop();

                         menumusic.setLoop(true);
                        gamemusic.stop();




                  Vector2f mouseCurrentPosition(Mouse::getPosition(window));



                   for(int i=0;i<row;i++)
                    {
                        for(int j=0;j<column;j++)
                        {
                            point[i][j].circle.setRadius(radius);
                            point[i][j].circle.setOutlineColor(sf::Color::Red);
                            point[i][j].circle.setOutlineThickness(thikness);
                            //point[i][j].circle.setRotation(point[i][j].circle.getRotation() + 45);
                            //point[i][j].circle.setOrigin(start_co_x+line_width+j*circle_distance,start_co_y+radius+i*circle_distance);
                            point[i][j].circle.setPosition(start_co_x+j*circle_distance,start_co_y+i*circle_distance);


                        }
                    }
                  key=clock.getElapsedTime().asSeconds();

                  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && key>0.3)
                             {
                                menuselect++;
                                 clock.restart();

                             }
                          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && key>0.3)
                            {
                                menuselect--;
                                 clock.restart();
                            }
                          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && key>0.2)
                            {
                             //if(!menu)window.close();
                            }
                            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                            {
                              if(playerTotal)
                              {
                                home=true;
                                playerTotal=false;

                                menuselect=2;
                              }
                              else if(selectarea)
                              {
                                home=true;
                                selectarea=false;
                                menuselect=3;

                              }
                              else if(soundd)
                              {
                                home=true;
                                soundd=false;
                                menuselect=4;
                              }
                              else if(helpp)
                              {
                                home=true;
                                helpp=false;
                                menuselect=5;
                              }
                              else if(aboutt)
                              {
                                home=true;
                                aboutt=false;
                                menuselect=6;
                              }
                            }
                           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)  && key>0.2 )
                            {
                              // if (Event::MouseButton.Button == sfButtonLeft && Event.Type == sfEvtMouseButtonPressed);
                                DoubleClickMouse=false;


                              if(!playerTotal && !selectarea && !soundd && !helpp && !aboutt)
                              {
                                if(menuselect%7==1 )
                                  {
                                    menumusic.stop();
                                    gamemusic.play();
                                     menu=false;
                                  }
                                else if(menuselect%7==2)
                                {
                                  playerTotal=true;
                                  home=false;
                                  menuselect=1;
                                }
                                else if(menuselect%7==3)
                                {
                                  selectarea=true;
                                  home=false;
                                  menuselect=1;
                                }
                               else if(menuselect%7==4)
                                {
                                  soundd=true;
                                  home=false;
                                  menuselect=1;
                                }
                              else  if(menuselect%7==5)
                                {
                                  helpp=true;
                                  home=false;
                                  menuselect=1;
                                }
                               else if(menuselect%7==6)
                                {
                                  aboutt=true;
                                  home=false;
                                  menuselect=1;
                                }
                              else  if(menuselect%7==0)
                                window.close();
                              }

                            else if(playerTotal)
                              {


                                 if(menuselect%7==1 || menuselect%7==0)
                                  {
                                    for(int i=1;i<5;i++)p[i]=false;
                                    player_number=2;
                                    p[1]=true;
                                    init();
                                     window.clear();
                                  }
                               else  if(menuselect%7==2)
                                 {
                                   for(int i=1;i<5;i++)p[i]=false;
                                   player_number=3;
                                   p[2]=true;
                                   init();
                                    window.clear();
                                 }
                               else if(menuselect%7==3)
                                  {
                                    for(int i=1;i<5;i++)p[i]=false;
                                    player_number=4;
                                    p[3]=true;
                                    init();
                                     window.clear();
                                  }
                               else if(menuselect%7==4)
                                  {
                                    for(int i=1;i<5;i++)p[i]=false;
                                    player_number=5;
                                    p[4]=true;
                                    init();
                                     window.clear();
                                  }
                               else if(menuselect%7==6)//back
                                {
                                 // selected=true;
                                  playerTotal=false;
                                  home=true;
                                  menuselect=2;

                                }

                              }
                              else if(selectarea)
                              {
                                 if(menuselect%7==1)
                                  {
                                    for(int i=1;i<8;i++)s[i]=false;
                                    row=5; column=5;
                                    s[1]=true;
                                    init();
                                     window.clear();


                                  }
                                if(menuselect%7==2)
                                 {
                                   for(int i=1;i<8;i++)s[i]=false;
                                   row=10;column=10;
                                   s[2]=true;
                                   init();
                                    window.clear();
                                 }
                                if(menuselect%7==3)
                                  {
                                    for(int i=1;i<8;i++)s[i]=false;
                                   row=10;column=15;
                                    s[3]=true;
                                    init();
                                     window.clear();
                                  }
                                if(menuselect%7==4)
                                  {
                                    for(int i=1;i<8;i++)s[i]=false;
                                    row=10;column=20;
                                    s[4]=true;
                                    init();
                                     window.clear();
                                  }
                                if(menuselect%7==5)
                                {
                                  for(int i=1;i<8;i++)s[i]=false;
                                    row=10;column=25;
                                    s[5]=true;
                                    init();
                                     window.clear();
                                }
                                if(menuselect%7==6)
                                {
                                  for(int i=1;i<8;i++)s[i]=false;
                                    row=5;column=5;
                                    s[6]=true;
                                    init();
                                     window.clear();
                                }
                                if(menuselect%7==0)//exit
                                {
                                 // selected=true;
                                  selectarea=false;
                                  home=true;
                                  menuselect=3;

                                }
                              }



                              clock.restart();
                           }

  float doubleClick=doubleClickClock.getElapsedTime().asSeconds();

                  if(home)
                    {


                         new_game.setFillColor(Color::Yellow);
                         player_total.setFillColor(Color::Yellow);
                         select_area.setFillColor(Color::Yellow);
                         sound.setFillColor(Color::Yellow);
                         help.setFillColor(Color::Yellow);
                         about.setFillColor(Color::Yellow);
                          exit.setFillColor(Color::Yellow);







                          if( (mouseCurrentPosition.x >new_game.getGlobalBounds().left && mouseCurrentPosition.x<new_game.getGlobalBounds().width+new_game.getGlobalBounds().left && mouseCurrentPosition.y>=new_game.getGlobalBounds().top && mouseCurrentPosition.y<new_game.getGlobalBounds().top+new_game.getGlobalBounds().height))
                             {

                              new_game.setFillColor(Color::Green);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                                {
                                  menu=false;
                                  doubleClickClock.restart();
                                  menumusic.stop();
                                  gamemusic.play();
                                }
                            }
                         else if((mouseCurrentPosition.x >player_total.getGlobalBounds().left && mouseCurrentPosition.x<player_total.getGlobalBounds().width+player_total.getGlobalBounds().left && mouseCurrentPosition.y>=player_total.getGlobalBounds().top && mouseCurrentPosition.y<player_total.getGlobalBounds().top+player_total.getGlobalBounds().height))
                             {
                                player_total.setFillColor(Color::Green);
                               if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                                {
                                  playerTotal=true;
                                  home=false;
                                  doubleClickClock.restart();
                                }

                             }

                         else if((mouseCurrentPosition.x >select_area.getGlobalBounds().left && mouseCurrentPosition.x<select_area.getGlobalBounds().width+select_area.getGlobalBounds().left && mouseCurrentPosition.y>=select_area.getGlobalBounds().top && mouseCurrentPosition.y<select_area.getGlobalBounds().top+select_area.getGlobalBounds().height))
                          {
                             select_area.setFillColor(Color::Green);
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                              {
                                selectarea=true;
                                home=false;
                                doubleClickClock.restart();
                              }

                          }
                         else if((mouseCurrentPosition.x >sound.getGlobalBounds().left && mouseCurrentPosition.x<sound.getGlobalBounds().width+sound.getGlobalBounds().left && mouseCurrentPosition.y>=sound.getGlobalBounds().top && mouseCurrentPosition.y<sound.getGlobalBounds().top+sound.getGlobalBounds().height))
                           {
                               sound.setFillColor(Color::Green);
                           if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                              {
                                soundd=true;
                                home=false;
                                doubleClickClock.restart();
                              }

                           }
                         else if((mouseCurrentPosition.x >help.getGlobalBounds().left && mouseCurrentPosition.x<help.getGlobalBounds().width+help.getGlobalBounds().left && mouseCurrentPosition.y>=help.getGlobalBounds().top && mouseCurrentPosition.y<help.getGlobalBounds().top+help.getGlobalBounds().height))
                            {
                               help.setFillColor(Color::Green);
                               if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                                {
                                  helpp=true;
                                  home=false;
                                  doubleClickClock.restart();
                                }

                            }

                         else if((mouseCurrentPosition.x >about.getGlobalBounds().left && mouseCurrentPosition.x<about.getGlobalBounds().width+about.getGlobalBounds().left && mouseCurrentPosition.y>=about.getGlobalBounds().top && mouseCurrentPosition.y<about.getGlobalBounds().top+about.getGlobalBounds().height))
                            {
                               about.setFillColor(Color::Green);
                               if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                                {
                                  aboutt=true;
                                  home=false;
                                  doubleClickClock.restart();
                                }

                            }
                         else if((mouseCurrentPosition.x >exit.getGlobalBounds().left && mouseCurrentPosition.x<exit.getGlobalBounds().width+exit.getGlobalBounds().left && mouseCurrentPosition.y>=exit.getGlobalBounds().top && mouseCurrentPosition.y<exit.getGlobalBounds().top+exit.getGlobalBounds().height))
                            {
                              exit.setFillColor(Color::Red);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2)
                                {
                                  doubleClickClock.restart();
                                  window.close();
                                }

                            }


                              if(menuselect%7==1 )
                            {
                                new_game.setFillColor(Color::Green);
                            }
                             if(menuselect%7==2 )
                            {
                                player_total.setFillColor(Color::Green);
                            }
                             if(menuselect%7==3  )
                            {
                                select_area.setFillColor(Color::Green);
                            }
                             if(menuselect%7==4 )
                            {
                                sound.setFillColor(Color::Green);
                            }
                             if(menuselect%7==5 )
                            {
                                help.setFillColor(Color::Green);
                            }
                             if(menuselect%7==6)
                            {
                                about.setFillColor(Color::Green);
                            }
                            if(menuselect%7==0)
                            {
                                exit.setFillColor(Color::Green);
                            }

                               window.draw(Resources[0].s_sprite);
                               window.draw(gametxt);

                               window.draw(new_game);
                               window.draw(player_total);
                               window.draw(select_area);
                               window.draw(sound);
                               window.draw(help);
                               window.draw(about);
                               window.draw(exit);




                    }

                   else if(playerTotal)
                     {
                        //clock.restart();
                      //float playerkey=playerTime.getElapsedTime().asSeconds();
                      window.draw(Resources[0].s_sprite);



                      player1.setString("Play between 2 players");
                      player1.setFont(font1);
                      player1.setCharacterSize(70);
                      player1.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      player1.setPosition(200+150,100+text_y*0);
                      player1.setFillColor(Color::Yellow);


                       player2.setString("Play between 3 players");
                      player2.setFont(font1);
                      player2.setCharacterSize(70);
                      player2.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      player2.setPosition(200+150,100+text_y*1);
                      player2.setFillColor(Color::Yellow);

                       player3.setString("Play between 4 players");
                      player3.setFont(font1);
                      player3.setCharacterSize(70);
                      player3.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      player3.setPosition(200+150,100+text_y*2);
                      player3.setFillColor(Color::Yellow);

                       player4.setString("Play between 5 players");
                      player4.setFont(font1);
                      player4.setCharacterSize(70);
                      player4.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      player4.setPosition(200+150,100+text_y*3);
                      player4.setFillColor(Color::Yellow);

                       player5.setString("Custom players");
                      player5.setFont(font1);
                      player5.setCharacterSize(70);
                      player5.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      player5.setPosition(200+150,100+text_y*4);
                      player5.setFillColor(Color::Yellow);

                       player6.setString("BACK");
                      player6.setFont(font1);
                      player6.setCharacterSize(70);
                      player6.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      player6.setPosition(200+150,100+text_y*5);
                      player6.setFillColor(Color::Black);


                      if((mouseCurrentPosition.x >player1.getGlobalBounds().left && mouseCurrentPosition.x<player1.getGlobalBounds().width+player1.getGlobalBounds().left && mouseCurrentPosition.y>=player1.getGlobalBounds().top && mouseCurrentPosition.y<player1.getGlobalBounds().top+player1.getGlobalBounds().height))
                         {
                              player1.setFillColor(Color::Green);
                               if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                              {
                                doubleClickClock.restart();
                                for(int i=1;i<5;i++)p[i]=false;
                                    player_number=2;
                                    p[1]=true;
                                    init();

                              }
                          }
                     if((mouseCurrentPosition.x >player2.getGlobalBounds().left && mouseCurrentPosition.x<player2.getGlobalBounds().width+player2.getGlobalBounds().left && mouseCurrentPosition.y>=player2.getGlobalBounds().top && mouseCurrentPosition.y<player2.getGlobalBounds().top+player2.getGlobalBounds().height))
                           {
                              player2.setFillColor(Color::Green);
                               if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                                {
                                  doubleClickClock.restart();
                                  for(int i=1;i<5;i++)p[i]=false;
                                    player_number=3;
                                    p[2]=true;
                                    init();

                                }
                          }
                     if((mouseCurrentPosition.x >player3.getGlobalBounds().left && mouseCurrentPosition.x<player3.getGlobalBounds().width+player3.getGlobalBounds().left && mouseCurrentPosition.y>=player3.getGlobalBounds().top && mouseCurrentPosition.y<player3.getGlobalBounds().top+player3.getGlobalBounds().height))
                            {
                              player3.setFillColor(Color::Green);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                              {
                                doubleClickClock.restart();

                                for(int i=1;i<5;i++)p[i]=false;
                                    player_number=4;
                                    p[3]=true;
                                    init();

                              }
                          }
                     if((mouseCurrentPosition.x >player4.getGlobalBounds().left && mouseCurrentPosition.x<player4.getGlobalBounds().width+player4.getGlobalBounds().left && mouseCurrentPosition.y>=player4.getGlobalBounds().top && mouseCurrentPosition.y<player4.getGlobalBounds().top+player4.getGlobalBounds().height))
                            {
                              player4.setFillColor(Color::Green);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                              {
                                doubleClickClock.restart();
                                for(int i=1;i<5;i++)p[i]=false;
                                    player_number=5;
                                    p[4]=true;
                                    init();

                              }
                          }
                     if((mouseCurrentPosition.x >player5.getGlobalBounds().left && mouseCurrentPosition.x<player5.getGlobalBounds().width+player5.getGlobalBounds().left && mouseCurrentPosition.y>=player5.getGlobalBounds().top && mouseCurrentPosition.y<player5.getGlobalBounds().top+player5.getGlobalBounds().height))
                            {
                              player5.setFillColor(Color::Green);
                              /*if (event.type == event.MouseButtonReleased && event.mouseButton.button== sf::Mouse::Left )
                              {
                                for(int i=1;i<5;i++)p[i]=false;
                                    player_number=;
                                    p[1]=true;
                                    init();
                                     window.clear();
                              }*/
                          }
                      else if((mouseCurrentPosition.x >player6.getGlobalBounds().left && mouseCurrentPosition.x<player6.getGlobalBounds().width+player6.getGlobalBounds().left && mouseCurrentPosition.y>=player6.getGlobalBounds().top && mouseCurrentPosition.y<player6.getGlobalBounds().top+player6.getGlobalBounds().height))
                          {
                              player6.setFillColor(Color::Red);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                              {
                                playerTotal=false;
                                home=true;
                                doubleClickClock.restart();


                              }
                          }



                          if(menuselect%7==1 || menuselect%7==0)
                            {
                                player1.setFillColor(Color::Green);
                            }
                            else if(menuselect%7==2 )
                            {
                                player2.setFillColor(Color::Green);

                            }
                            else if(menuselect%7==3 )
                            {
                                player3.setFillColor(Color::Green);

                            }
                            else if(menuselect%7==4)
                            {
                                player4.setFillColor(Color::Green);
                            }
                            else if(menuselect%7==5 )
                            {
                                player5.setFillColor(Color::Green);
                            }
                            if(menuselect%7==6)
                            {
                              player6.setFillColor(Color::Red);
                            }

                             if(p[1])player1.setFillColor(Color::Red);
                              if(p[2])player2.setFillColor(Color::Red);
                               if(p[3])player3.setFillColor(Color::Red);
                                if(p[4])player4.setFillColor(Color::Red);
                                 //if(p[5])player5.setFillColor(Color::Red);




                      window.draw(player1);
                      window.draw(player2);
                      window.draw(player3);
                      window.draw(player4);
                      window.draw(player5);
                      window.draw(player6);



                      }

                  else if(selectarea)
                      {
                        window.draw(Resources[0].s_sprite);

                      a0.setString("Select The Area");
                      a0.setFont(font1);
                      a0.setCharacterSize(90);
                      a0.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a0.setPosition(200+150,100+text_y*0-100);
                      a0.setFillColor(Color::Green);

                       a1.setString("Row: 5::5 :Column");
                      a1.setFont(font1);
                      a1.setCharacterSize(70);
                      a1.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a1.setPosition(200+150,100+text_y*0);
                      a1.setFillColor(Color::Yellow);

                       a2.setString("Row: 10::10 :Column");
                      a2.setFont(font1);
                      a2.setCharacterSize(70);
                      a2.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a2.setPosition(200+150,100+text_y*1);
                      a2.setFillColor(Color::Yellow);

                       a3.setString("Row: 10::15 :Column");
                      a3.setFont(font1);
                      a3.setCharacterSize(70);
                      a3.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a3.setPosition(200+150,100+text_y*2);
                      a3.setFillColor(Color::Yellow);

                       a4.setString("Row: 10::20 :Column");
                      a4.setFont(font1);
                      a4.setCharacterSize(70);
                      a4.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a4.setPosition(200+150,100+text_y*3);
                      a4.setFillColor(Color::Yellow);

                       a5.setString("Row: 10::25 :Column");
                      a5.setFont(font1);
                      a5.setCharacterSize(70);
                      a5.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a5.setPosition(200+150,100+text_y*4);
                      a5.setFillColor(Color::Yellow);

                       a6.setString("Custom Area");
                      a6.setFont(font1);
                      a6.setCharacterSize(70);
                      a6.setScale(1.f,1.f);
                      //gametxt.setFillColor(Color::Red);
                      a6.setPosition(200+150,100+text_y*5);
                      a6.setFillColor(Color::Yellow);






                      if((mouseCurrentPosition.x >a1.getGlobalBounds().left && mouseCurrentPosition.x<a1.getGlobalBounds().width+a1.getGlobalBounds().left && mouseCurrentPosition.y>=a1.getGlobalBounds().top && mouseCurrentPosition.y<a1.getGlobalBounds().top+a1.getGlobalBounds().height))
                           {
                              a1.setFillColor(Color::Green);

                             if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                                doubleClickClock.restart();
                                for(int i=1;i<8;i++)s[i]=false;
                                    row=5; column=5;
                                    s[1]=true;
                                    init();

                             }
                           }

                          if((mouseCurrentPosition.x >a2.getGlobalBounds().left && mouseCurrentPosition.x<a2.getGlobalBounds().width+a2.getGlobalBounds().left && mouseCurrentPosition.y>=a2.getGlobalBounds().top && mouseCurrentPosition.y<a2.getGlobalBounds().top+a2.getGlobalBounds().height))
                            {
                              a2.setFillColor(Color::Green);

                             if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                                doubleClickClock.restart();
                                for(int i=1;i<8;i++)s[i]=false;
                                    row=10; column=10;
                                    s[2]=true;
                                    init();

                             }
                           }

                          if((mouseCurrentPosition.x >a3.getGlobalBounds().left && mouseCurrentPosition.x<a3.getGlobalBounds().width+a3.getGlobalBounds().left && mouseCurrentPosition.y>=a3.getGlobalBounds().top && mouseCurrentPosition.y<a3.getGlobalBounds().top+a3.getGlobalBounds().height))
                            {
                              a3.setFillColor(Color::Green);

                             if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                                doubleClickClock.restart();
                                for(int i=1;i<8;i++)s[i]=false;
                                    row=10; column=15;
                                    s[3]=true;
                                    init();

                             }
                           }

                          if((mouseCurrentPosition.x >a4.getGlobalBounds().left && mouseCurrentPosition.x<a4.getGlobalBounds().width+a4.getGlobalBounds().left && mouseCurrentPosition.y>=a4.getGlobalBounds().top && mouseCurrentPosition.y<a4.getGlobalBounds().top+a4.getGlobalBounds().height))
                            {
                              a4.setFillColor(Color::Green);

                             if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                                doubleClickClock.restart();
                                for(int i=1;i<8;i++)s[i]=false;
                                    row=10; column=20;
                                    s[4]=true;
                                    init();

                             }
                           }

                          if((mouseCurrentPosition.x >a5.getGlobalBounds().left && mouseCurrentPosition.x<a5.getGlobalBounds().width+a5.getGlobalBounds().left && mouseCurrentPosition.y>=a5.getGlobalBounds().top && mouseCurrentPosition.y<a5.getGlobalBounds().top+a5.getGlobalBounds().height))
                            {
                              a5.setFillColor(Color::Green);

                             if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                                doubleClickClock.restart();
                                for(int i=1;i<8;i++)s[i]=false;
                                    row=10; column=25;
                                    s[5]=true;
                                    init();

                             }
                           }

                          if((mouseCurrentPosition.x >a6.getGlobalBounds().left && mouseCurrentPosition.x<a6.getGlobalBounds().width+a6.getGlobalBounds().left && mouseCurrentPosition.y>=a6.getGlobalBounds().top && mouseCurrentPosition.y<a6.getGlobalBounds().top+a6.getGlobalBounds().height))
                            a6.setFillColor(Color::Green);
                          if((mouseCurrentPosition.x >a7.getGlobalBounds().left && mouseCurrentPosition.x<a7.getGlobalBounds().width+a7.getGlobalBounds().left && mouseCurrentPosition.y>=a7.getGlobalBounds().top && mouseCurrentPosition.y<a7.getGlobalBounds().top+a7.getGlobalBounds().height))
                            {
                              a7.setFillColor(Color::Red);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                              doubleClickClock.restart();
                               selectarea=false;
                               home=true;
                             }
                            }


                      if(menuselect%7==1)
                            {
                                a1.setFillColor(Color::Green);
                            }
                            else if(menuselect%7==2 )
                            {
                                a2.setFillColor(Color::Green);

                            }
                            else if(menuselect%7==3 )
                            {
                                a3.setFillColor(Color::Green);

                            }
                            else if(menuselect%7==4)
                            {
                                a4.setFillColor(Color::Green);
                            }
                            else if(menuselect%7==5 )
                            {
                                a5.setFillColor(Color::Green);
                            }
                            if(menuselect%7==6)
                            {
                              a6.setFillColor(Color::Green);
                            }
                            if(menuselect%7==0)
                            {
                              a7.setFillColor(Color::Red);
                            }

                             if(s[1])a1.setFillColor(Color::Red);
                              if(s[2])a2.setFillColor(Color::Red);
                               if(s[3])a3.setFillColor(Color::Red);
                                if(s[4])a4.setFillColor(Color::Red);
                                 if(s[5])a5.setFillColor(Color::Red);
                                 if(s[6])a6.setFillColor(Color::Red);
                               //  if(select[7])a7.setFillColor(Color::Red);



                      window.draw(a0);
                      window.draw(a1);
                      window.draw(a2);
                      window.draw(a3);
                      window.draw(a4);
                      window.draw(a5);
                      window.draw(a6);
                      window.draw(a7);



                      }

                      if(soundd)
                      {
                        if((mouseCurrentPosition.x >a7.getGlobalBounds().left && mouseCurrentPosition.x<a7.getGlobalBounds().width+a7.getGlobalBounds().left && mouseCurrentPosition.y>=a7.getGlobalBounds().top && mouseCurrentPosition.y<a7.getGlobalBounds().top+a7.getGlobalBounds().height))
                            {
                              a7.setFillColor(Color::Red);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                              doubleClickClock.restart();
                               soundd=false;
                               home=true;
                             }
                            }

                         window.draw(Resources[0].s_sprite);
                         window.draw(a7);
                      }
                      if(helpp)
                      {
                        if((mouseCurrentPosition.x >a7.getGlobalBounds().left && mouseCurrentPosition.x<a7.getGlobalBounds().width+a7.getGlobalBounds().left && mouseCurrentPosition.y>=a7.getGlobalBounds().top && mouseCurrentPosition.y<a7.getGlobalBounds().top+a7.getGlobalBounds().height))
                            {
                              a7.setFillColor(Color::Red);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                              doubleClickClock.restart();
                               helpp=false;
                               home=true;
                             }
                            }
                         window.draw(Resources[0].s_sprite);
                         window.draw(a7);
                      }
                      if(aboutt)
                      {
                        if((mouseCurrentPosition.x >a7.getGlobalBounds().left && mouseCurrentPosition.x<a7.getGlobalBounds().width+a7.getGlobalBounds().left && mouseCurrentPosition.y>=a7.getGlobalBounds().top && mouseCurrentPosition.y<a7.getGlobalBounds().top+a7.getGlobalBounds().height))
                            {
                              a7.setFillColor(Color::Red);
                              if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && doubleClick>0.2 )
                             {
                              doubleClickClock.restart();
                               aboutt=false;
                               home=true;
                             }
                            }
                         window.draw(Resources[0].s_sprite);
                         window.draw(a7);
                      }







                }
                if(!menu)
                {
                        //gamemusic.play();
                        gamemusic.setLoop(true);

                      /*  menumusic.play();
                       menumusic.setLoop(true);
*/

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){menu=true;menumusic.play();}

                            if(s[1])window.draw(Resources[1].s_sprite);
                            else if(s[2])window.draw(Resources[2].s_sprite);
                            else if(s[3])window.draw(Resources[3].s_sprite);
                            else if(s[4])window.draw(Resources[4].s_sprite);
                            else if(s[5])window.draw(Resources[5].s_sprite);




                      if (sf::Event::MouseButtonReleased)
                          if(event.mouseButton.button==Mouse::Left)

                          {
                              selected_circle=true;
                              for(int i=0;i<row && blank_selected;i++)
                              {
                                  for(int j=0;j<column;j++)
                                  {

                                     Vector2f circle_center(point[i][j].circle.getPosition().x+radius+thikness , point[i][j].circle.getPosition().y+radius+radius/2);

                                     if(((circle_center.x-mouseCurrentPosition.x)*(circle_center.x-mouseCurrentPosition.x))+((circle_center.y- mouseCurrentPosition.y)*(circle_center.y- mouseCurrentPosition.y))<=(2*radius+thikness)*(2*radius+thikness))///changed *2
                                     {
                                       second_node=circle_center;
                                       node2=j+column*i;
                                       blank_selected=false;
                                       created_line=true;
                                     }

                                  }

                              }
                           }


                      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                      {
                          blank_selected=true;
                            for(int i=0,point_count=0;i<row && selected_circle;i++)
                           {

                             for(int j=0;j<column;j++)
                              {

                                  Vector2f circle_center(point[i][j].circle.getPosition().x+radius/1.5 , point[i][j].circle.getPosition().y+radius/2);

                                  if(((circle_center.x-mouseCurrentPosition.x)*(circle_center.x-mouseCurrentPosition.x))+((circle_center.y- mouseCurrentPosition.y)*(circle_center.y- mouseCurrentPosition.y))<=(radius+thikness)*(radius+thikness))
                                    {
                                          sample_line_cordinate=circle_center;

                                          first_node=circle_center;//line first node
                                           node1=j+column*i;

                                          selected_circle=false;
                                    }

                               }



                           }


                      }







                      //draw line && square

                      ///bfs to check is not connect node
                        bool connect=bfs(node1,node2);
                         bool connect2;

                      if(selected_circle && !blank_selected && node1!=node2 && !connect)
                      {
                          int direction=(abs(first_node.x-second_node.x));
                          int direction2=abs(first_node.y-second_node.y);

                          if(sqrt((first_node.x+radius/1.5-second_node.x+radius/1.5)*(first_node.x+radius/1.5-second_node.x+radius/1.5)+(first_node.y+radius/2-second_node.y+radius/2)*(first_node.y+radius/2-second_node.y+radius/2))<=circle_distance+thikness)
                          {



                              Line[Line_count]=dag(first_node,second_node,direction);
                              Line_count++;





                             // std::cout<<Line_count<<std::endl;

                              created_line=false;
                              int small_selected_node=node1;
                              int large_selected_node=node2;
                              int temp;
                              if(small_selected_node>large_selected_node)
                                  {
                                      temp=small_selected_node;
                                      small_selected_node=large_selected_node;
                                      large_selected_node=temp;
                                  }



                             adj[node1].push_back(node2);
                             adj[node2].push_back(node1);
                          /* adj[node1][node2]=true;
                           adj[node2][node1]=true;*/
                           //player
                           player_point=false;



                             if(abs(first_node.x-second_node.x)>30)//means horizontal line
                             {
                                  if(small_selected_node-column>=0)
                                  {
                                      connect=bfs(small_selected_node,small_selected_node-column);
                                      connect2=bfs(large_selected_node,large_selected_node-column);

                                      if(connect && connect2)
                                      {
                                         ///work from here
                                            connect=bfs(small_selected_node-column,large_selected_node-column);

                                          if(connect)
                                          {
                                              ///draw rectangle at if(node1<node2) first_node up coordinate
                                            if(node1<node2) square[square_count]=dag3(Vector2f(first_node.x+line_width,first_node.y-circle_distance+line_width));
                                            else square[square_count]=dag3(Vector2f(second_node.x,second_node.y-circle_distance));

                                             square_count++;
                                             player_point=true;

                                          }

                                      }
                                  }


                                   if(small_selected_node+column<=(row*column))
                                  {
                                      connect=bfs(small_selected_node,small_selected_node+column);
                                      connect2=bfs(large_selected_node,large_selected_node+column);

                                     if(connect && connect2)
                                      {
                                          connect=bfs(small_selected_node+column,large_selected_node+column);

                                          if(connect)
                                          {
                                              //draw rectangle at if(node1<node2) first_node down coordinate
                                             if(node1<node2) square[square_count]=dag3(Vector2f(first_node.x+line_width,first_node.y+line_width));
                                             else square[square_count]=dag3(Vector2f(second_node.x,second_node.y));
                                              square_count++;
                                              player_point=true;
                                          }
                                      }
                                  }

                             }
                             else
                             {
                                  if(small_selected_node-1>=0)
                                  {
                                        connect=bfs(small_selected_node,small_selected_node-1);
                                        connect2=bfs(large_selected_node,large_selected_node-1);

                                      if(connect && connect2)
                                      {
                                          connect=bfs(small_selected_node-1,large_selected_node-1);
                                          if(connect)
                                          {
                                              ///draw rectangle at if(node1<node2) left side of first_node
                                              if(node1<node2)square[square_count]=dag3(Vector2f(first_node.x-circle_distance+line_width,first_node.y+line_width));
                                              else square[square_count]=dag3(Vector2f(second_node.x-circle_distance,second_node.y));
                                              square_count++;
                                              player_point=true;

                                          }
                                      }
                                  }

                                  if(small_selected_node+1<=(row*column))
                                  {
                                      connect=bfs(small_selected_node,small_selected_node+1);
                                      connect2=bfs(large_selected_node,large_selected_node+1);
                                      if(connect && connect2)
                                      {
                                          connect=bfs(small_selected_node+1,large_selected_node+1);

                                          if(connect)
                                          {
                                              ///draw rectangle at if(node1<node2)Right side of first_node coordinate
                                              if(node1<node2)square[square_count]=dag3(Vector2f(first_node.x+line_width,first_node.y+line_width));
                                              else square[square_count]=dag3(Vector2f(second_node.x,second_node.y));
                                              square_count++;
                                              player_point=true;
                                          }
                                      }
                                  }
                             }

                              // std::cout<<player_point<<std::endl;



                             if(!player_point)
                               {
                                  player_maintain++;
                               }
                               player_no=player_maintain%player_number+1;//+1=player numberb
                            //std::cout<<"Turn for player No: "<<player_no<<std::endl;


                              //blank_selected=true;
                              ///work for adjacency matrice

                          }


                      }



                        ///player turn's

                        player_score[1].block.setOutlineColor(Color::Black);
                        player_score[2].block.setOutlineColor(Color::Black);
                        player_score[3].block.setOutlineColor(Color::Black);
                        player_score[4].block.setOutlineColor(Color::Black);
                        player_score[5].block.setOutlineColor(Color::Black);


                         std::string Score_str;

                             Score_str="Turn for Player N0: ";
                            Score_str += To_string(player_no);


                            player_turn.setString(Score_str);
                            player_turn.setFont(font1);
                            player_turn.setCharacterSize(60);
                            player_turn.setScale(1.f,1.f);
                         //gametxt.setFillColor(Color::Red);
                            player_turn.setPosition(200+150,start_co_y-75);
                            if(player_no==1)
                            {
                              player_score[1].block.setOutlineColor(Color::White);
                              player_turn.setFillColor(Color::Green);
                            }

                          else if(player_no==2)
                          {
                            player_score[2].block.setOutlineColor(Color::White);
                            player_turn.setFillColor(Color::Yellow);
                          }
                          else if(player_no==3)
                          {
                            player_score[3].block.setOutlineColor(Color::White);
                            player_turn.setFillColor(Color::Blue);
                          }
                          else if(player_no==4)
                          {
                            player_score[4].block.setOutlineColor(Color::White);
                            player_turn.setFillColor(Color::Red);
                          }
                          else if(player_no==5)
                          {
                            player_score[4].block.setOutlineColor(Color::White);
                            player_turn.setFillColor(Color::Magenta);
                          }


                      ///score of player 1-5
                       std::string Score_str1;
                        Score_str1 = To_string(score_count[1]);

                           q1.setString(Score_str1);
                            q1.setFont(font1);
                           q1.setCharacterSize(70);
                            q1.setScale(1.f,1.f);
                           q1.setFillColor(Color::Black);
                            q1.setPosition(100+extent+30,0);


                        Score_str1 = To_string(score_count[2]);

                           q2.setString(Score_str1);
                            q2.setFont(font1);
                           q2.setCharacterSize(70);
                            q2.setScale(1.f,1.f);
                           q2.setFillColor(Color::Black);
                            q2.setPosition(100*2+extent+30,0);

                            Score_str1 = To_string(score_count[3]);

                           q3.setString(Score_str1);
                            q3.setFont(font1);
                           q3.setCharacterSize(70);
                            q3.setScale(1.f,1.f);
                           q3.setFillColor(Color::Black);
                            q3.setPosition(100*3+extent+30,0);

                             Score_str1 = To_string(score_count[4]);

                           q4.setString(Score_str1);
                            q4.setFont(font1);
                           q4.setCharacterSize(70);
                            q4.setScale(1.f,1.f);
                           q4.setFillColor(Color::Black);
                            q4.setPosition(100*4+extent+30,0);

                             Score_str1 = To_string(score_count[5]);

                           q5.setString(Score_str1);
                            q5.setFont(font1);
                           q5.setCharacterSize(70);
                            q5.setScale(1.f,1.f);
                           q5.setFillColor(Color::Black);
                            q5.setPosition(100*5+extent+30,0);


                      if(player_number==2)
                      {
                        window.draw(player_score[1].block);
                        window.draw(player_score[2].block);

                           window.draw(q1);
                            window.draw(q2);

                            //player no
                            window.draw(p1);
                            window.draw(p2);
                      }
                      else if(player_number==3)
                      {
                        window.draw(player_score[1].block);
                        window.draw(player_score[2].block);
                        window.draw(player_score[3].block);

                        window.draw(q1);
                            window.draw(q2);
                            window.draw(q3);

                            window.draw(p1);
                            window.draw(p2);
                            window.draw(p3);

                      }
                      else if(player_number==4)
                      {
                        window.draw(player_score[1].block);
                        window.draw(player_score[2].block);
                        window.draw(player_score[3].block);
                        window.draw(player_score[4].block);

                        window.draw(q1);
                            window.draw(q2);
                            window.draw(q3);
                            window.draw(q4);

                              window.draw(p1);
                            window.draw(p2);
                            window.draw(p3);
                            window.draw(p4);

                      }
                       else if(player_number==5)
                      {
                        window.draw(player_score[1].block);
                        window.draw(player_score[2].block);
                        window.draw(player_score[3].block);
                        window.draw(player_score[4].block);
                        window.draw(player_score[5].block);

                        window.draw(q1);
                            window.draw(q2);
                            window.draw(q3);
                            window.draw(q4);
                            window.draw(q5);

                             window.draw(p1);
                            window.draw(p2);
                            window.draw(p3);
                            window.draw(p4);
                            window.draw(p5);

                      }


                     for(int i=0;i<row;i++)
                      {
                          for(int j=0;j<column;j++)
                          {

                             window.draw(point[i][j].circle);

                          }
                      }


                      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                      {
                        // sample=sample_line(sample_line_cordinate,mouseCurrentPosition);
                          int direction=abs(mouseCurrentPosition.x-sample_line_cordinate.x);
                          if(!selected_circle)
                          sample=dag2(Vector2f(sample_line_cordinate),mouseCurrentPosition,direction);
                          else
                              sample=dag2(mouseCurrentPosition,mouseCurrentPosition,direction);
                          window.draw(sample.polygon);
                         // window.draw(quad);

                      }
                      for(int i=0;i<square_count;i++)
                      {
                          window.draw(square[i].block);
                      }



                   for(int i=0;i<Line_count;i++)
                      {

                        window.draw(Line[i].polygon);

                      }
                      //window.draw(Line[0].polygon);
                   //   window.draw(polygon);
                      window.draw(player_turn);

                      backClick=backClock.getElapsedTime().asSeconds();

                if(mouseCurrentPosition.x>Back.sprite.getPosition().x+3 && mouseCurrentPosition.x<Back.sprite.getPosition().x+40 && mouseCurrentPosition.y>Back.sprite.getPosition().y && mouseCurrentPosition.y<Back.sprite.getPosition().y+15)
                 {
                  //std::cout<<"YEs"<<std::endl;
                  if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && backClick>0.3 )
                  {
                    menu=true;
                    gamemusic.stop();
                    menumusic.play();
                    backClock.restart();
                  }

                }

                      Back.show();



                }

                window.display();
                window.clear();




    }
	return 0;
}
