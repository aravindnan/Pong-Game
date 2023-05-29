#include<conio.h>
#include<dos.h>
#include<string.h>
#include<stdlib.h>
#include<fstream.h>
#include<stdio.h>

/*      THIS PROJECT WAS DONE BY ARAVIND NANDAKUMAR OF CLASS 12-B
	 OF BHAVANS VIDYA MANDIR GIRINAGAR ON THE YEAR 2018-19     */

char op,b;
int del=5;
typedef int mode;
int hitv=0;
int h;
text(int a,int b,char str[])
{gotoxy(a,b);
cprintf("%s",str);}

class leaderboard{              //class for storing score and name to file
    public:              char name[10];
		  int score;
     public:	  leaderboard(){score=0;strcpy(name,"NIL");}
		  void output(int j)
		  {
		  textcolor(3);
		  gotoxy(26,j);
		  cprintf(name);
		  gotoxy(42,j);
		  cprintf("%d",score);
		  }

		  }l[5];

struct paddle{int xl,xr;                     //structure assosiated with movement of paddle
	      paddle(){xl=30;xr=39;}

	      void operator ++()
	      {if(xl<=60){xl++;xr++;}}

	      void operator --()
	      {if(xr>10){xl--;xr--;}}

	      int getpos()
	      {return((xl+xr)/2);}

	      void print(int y)
	      {
	      if(xl>1){gotoxy(xl-1,y);cprintf(" ");}
	      if(xr<70){gotoxy(xr+1,y);cprintf(" ");}
	      gotoxy(xl,y);
	      cprintf("ÜÛÛÛÛÛÛÛÛÜ");
	      }
	      };

class user{                      //class for storing user details
      public: char name[5];
	    int score,regn;
	    paddle p;
	    void input()
	    {cin>>name>>score;}
	    user(){score=0;}   //default constructor
	    void paddlerest();
	    void in();
	    void automove(int);
	    int hit(int,int);
	    void  paddlereset(){p=paddle();p.print(regn);} }pl,cmp;
	   void user::in()
	    { h=0;
	    char op;
	    op=getch();
	    if(kbhit()) op=getch();
	   switch(op)
	   {
	    case 75:--p;break;
	    case 77:++p;break;
	    case 'x':h=1;break;
	    }
	    p.print(regn);
	    while(kbhit()) getch();
	    }

	    void user:: automove(int bx)
	    {
	    //if(random(5)==0) return;  //handicap
	    int did=0;
	    if(p.getpos()<bx) {did=1;++p;};
	    if(p.getpos()>bx) {did=1;--p;}
	    if(did) p.print(regn);
	    }

	    int user:: hit(int bx,int by)
	      {
	      if(by==regn &&(bx<=p.xr && bx>=p.xl))
		{hitv=1;
		return 1;}
	      hitv=0;
	      return 0;
	      }



struct ball{int x,y,estx,esty,rf;        //structure for the the movement of the ball
	   mode m[2];

	   ball(int p,int q,mode r[2],int t)   //parametrized contructor
	   {x=p;
	   y=q;
	   m[0]=r[0];
	   m[1]=r[1];
	   rf=t;}

	   ball()                               //default contructor
	   {x=35;y=25;rf=1;m[0]=-1+(random(2)?2:0);m[1]=-2;
	   estcalc();
	   print();}

	   void print(){gotoxy(x,y);cprintf("\t");}

	   void update()
	   {
	   x+=rf*m[0];
	   y+=m[1]/2;
	   }

	   void estcalc()
	   {
	   ball temp(x,y,m,rf);
	   temp.update();
		   while(temp.y!=y &&temp.y!=2 && temp.y!=49 && temp.x!=1 && temp.x!=70)
		temp.update();
		estx=temp.x;
		 esty=temp.y;
	    }

	   void move()
	   {
	   gotoxy(x,y);
	   if(y!=2 && y!=49 && x>0 && x<=70) cprintf(" ");
	   update();
if(x>=70 || x<=1 || pl.hit(x,y) || cmp.hit(x,y))     //inequality cuz of rf
		{
		 if(x>=70 || x<=1) m[0]=-m[0];
		 sound(200);
		 delay(10);
		 nosound();
		 if(y==2  || y==49) {m[1]=-m[1];rf=random(3);}
		 sound(890);
		 delay(10);
		 nosound();
		 estcalc();
		}
	   if(y!=2 && y!=49 && x>0 && x<70) print(); }
	   };

void bar(int d)        //the main game function
{
randomize();
textmode(64);
textbackground(WHITE);clrscr();
for(int w=1;w<=50;w++)
{textcolor(0);gotoxy(71,w);cprintf("³");}
gotoxy(71,25);
cprintf("ÃÄÄÄÄÄÄÄÄÄÄÄ");
window(1,2,70,49);
textbackground(WHITE);
clrscr();
window(1,1,80,50);
textcolor(WHITE);
pl.regn=49;
cmp.regn=2;
pl.score=0;
do{
ball b;
textcolor(0);
pl.paddlereset();
cmp.paddlereset();
int fps=0;
while(1)
	{fps++;
	textcolor(0);
	if(fps%5==0) b.move();
	if(kbhit()) {pl.in();if(h)goto game;}
	//pl.automove(b.estx);
	if(fps%d==0) cmp.automove(b.estx);
	if(!hitv  && (b.y==2 || b.y==49))
		{
		if(b.y==49) cmp.score++;
		if(b.y==2) pl.score++;
		gotoxy(75,2);
		cprintf("%d",cmp.score);
		gotoxy(75,49);
		cprintf("%d",pl.score);
		textcolor(LIGHTGRAY);
		cmp.p.print(2);
		pl.p.print(49);
		textcolor(3);
		textcolor(3);
		break;
		}
	delay(15);}
 //score=pl.score;
 }
while(cmp.score!=1||pl.score!=0);
game:                                  //gameover
textmode(C80);
textbackground(BLACK);
clrscr();
textcolor(3);
if(pl.score>l[0].score)
{gotoxy(30,5);textcolor(4);cprintf("!!NEW HIGH SCORE!!");}
textcolor(3);
text(10,11," Ûßßßß                         ÜÜÜÜÜÜÜ                     ");
text(10,12," Ý      ÞßßßßÝ ÛßÜ  ÜßÛ Þßßßß  Ý     Þ Ý    Þ  Þßßßß ÛßßßÝ ");
text(10,13," Ý   ßÝ ÛÜÜÜÜÛ Ý  ßß  Þ Þßßß   Ý     Þ ßÝ  Þß  Þßßß  ÝßÛß  ");
text(10,14," ßßßßßß ß    ß ß      ß ßßßßß  ßßßßßßß  ßßßß   ßßßßß ß  ß  ");
text(33,15,"YOUR SCORE :");cprintf("%d",pl.score);
text(31,17,"ENTER YOUR NAME");
text(25,18,"(not more than 3 charecters)");
gotoxy(34,20);
cin>>pl.name;
leaderboard tl;
int v;
if(pl.score>l[4].score)
	for(v=0;v<5;++v)
		if(pl.score>l[v].score) break;
tl=l[v];
l[v].score=pl.score;
strcpy(l[v].name,pl.name);
for(v+=1;v<5;++v)
	{
	leaderboard tl2=l[v];
	l[v]=tl;
	tl=tl2;
	}

gotoxy(80,25);
getch();
}
int difficulty()          //function to choose difficulty
 { int r,o=0;
  do{
   textbackground(0);
   clrscr();
   textcolor(3);
   gotoxy(16,4);
   text(16,4,"ÜÜÜÜÜÜÜÜÜ                                Ü  Ü      ");
   text(16,5," Ý     ÛÛ  ß Þßßßß  Þßßßß ß ÜÜÜÜÜ Ü    Ü Ý ßÝßßßß  ");
   text(16,6," Ý     ÛÛ  Ý ÞÜÜÜÜ  ÞÜÜÜÜ Ý Ý     Ý    Þ Ý  Ý Ý   Ý");
   text(16,7," Ý     ÛÛ  Ý Þ      Þ     Ý Ý     Ý    Þ Ý  Ý ßßßßÝ");
   text(16,8,"ßßßßßßßßß  ß ß      ß     ß ßßßßß ßßßßßß ßß ß     ß");
   text(29,11,"¯");
   cprintf(" EASY");
   r=11;
   text(29,12,"  MEDIUM");
   text(29,13,"  HARD");
   textbackground(0);
do{
  op=getch();
 switch(op)
 {case char(80):gotoxy(29,r);cout<<" ";
		if(r==13)
	       {r=11;o=0;}
		else
		{++r;o+=2;}
		 gotoxy(29,r);cout<<"¯";
		 break;
  case char(72):gotoxy(29,r);cout<<" ";
		if(r==11)
		{r=13;o=4;}
		else
		{--r;o-=2;}
		 gotoxy(29,r);cout<<"¯";
		  }
if(op==13)
if(o==0)
return(7);
else if(o==2)
return(5);
else
return(3);

}
while(op!=13);
}
while(op!=3);
 }
void newgame(int x)          //function to play the game
{
bar(x);
textmode(C80);
return;}
 void scoreboard()               //funtion to display scores
  {textbackground(0);
  clrscr();
  textcolor(3);
    text(17,4," ÜÜÜÜÜÜ  ÜÜÜÜÜÜ  ÜÜÜÜÜÜ  ÜÜÜÜÜÜ  ÜÜÜÜÜÜ  ÜÜÜÜÜÜ ");
    text(17,5," Ý       Ý       Ý    Þ  Ý    Þ  Ý       Ý      ");
    text(17,6," ßßßßßÛ  Ý       Ý    Þ  ÝßÝßßß  Ûßßßßß  ßßßßßÛ ");
    text(17,7,"      Þ  Ý       Ý    Þ  Ý ßÛÜ   Ý            Þ ");
    text(17,8," ßßßßßß  ßßßßßß  ßßßßßß  ß   ßß  ßßßßßß  ßßßßßß ");
     textcolor(3);
     for(int i=24;i<51;i++)
     {text(i,12,"Í");}
     for(i=11;i<19;i++)
    {text(24,i,"º");}
    textcolor(3);
     text(26,11,"NAME");
     text(39,11," SCORE");
     textcolor(3);
     for(i=11;i<19;i++)
    {text(51,i,"º");}
     text(24,12,"Ì");
     text(51,12,"¹");
     i=13;
     for(int w=0;w<5;++w)
	{
	gotoxy(16,w+13);
	l[w].output(w+13);
	}
     textcolor(3);
    for(i=11;i<19;i++)
     {text(37,i,"º");}
      text(37,12,"Î");
    for(i=24;i<51;i++)
     {text(i,10,"Í");}
      text(24,10,"É");
      text(51,10,"»");

      for(i=24;i<51;i++)
     {text(i,19,"Í");}
      text(24,19,"È");
      text(51,19,"¼");
      text(37,19,"Ê");
      text(37,10,"Ë");

     gotoxy(80,25);
     op=getch();
   if (op==1)
   return;
   }
void main()
{
int i;
ifstream fin;
fin.open("LDRBRD",ios::binary);         // reading the file called LDRBRD
for(int w=0;w<5;w++)
	fin.read((char*)&(l[w]),sizeof(leaderboard));
fin.close();
clrscr();
_setcursortype(_NOCURSOR);
textbackground(0);textcolor(3);
text(35,4,"RULES");                 //displaying rules
text(5,10,"þ Use up arrow() or down arrow() to move up and down the menu respectively");
text(5,12,"þ Use left key() or right key() to move the paddle to respective sides");
text(5,14,"þ enter the player name under 4 charecters or the program may malfunction");
text(35,20," Press any key to continue");
int z;
while(!kbhit())
{gotoxy(61,20);
 cprintf("    ");
 z=0;
 delay(50);
 while(z<4)
{  gotoxy(61+z,20);
  cprintf(".");
  delay(200);
 z++; }
  }
 getch();
 do
 {_setcursortype(_NOCURSOR);
  textbackground(0);
  clrscr();
  textcolor(11);
  gotoxy(80,25);
  int p=19,q=6;
  gotoxy(p,q);
  text(p,q,  "ÛßßßßÛ    ÜÛßßÛÜ      ÛÛÜ   Ý     Ûßßßß   ");
  text(19,7, "Ý    Þ    Ý ÜÜ Þ      Ý ÞÜ  Ý     Ý       ");
  text(19,8, "ÛÜÜÜÜÛ    Ý ÝÞ Þ      Ý  ÞÜ Ý     Ý   ÛßßÝ");
  text(19,9, "Ý         Ý ßß Þ      Ý   Þ Ý     Ý      Ý");
  text(19,10,"Ý         ßÛÜÜÛß      Ý    ÛÝ     ÛÜÜÜÜÜÛÝ");
  textcolor(6);
  p=27;
  gotoxy(p,13);
  q=13;
  textcolor(3);
  cout<<"¯";
  cprintf(" NEW GAME");
  text(p,14,"  DIFFICULTY");
  text(p,15,"  SCOREBOARD");
  text(p,16,"  QUIT");
  int i=0;
  do{
  textcolor(CYAN);
  textbackground(BLACK);
  gotoxy(80,25);
   op=getch();
 switch(op)             //scroll choice on main menu
 {case 80:text(p,q," ");
		if(q==16)
		{q=13;i=0;}
		else
		{++q;i=i+2;}
		text(p,q,"¯");
		break;
  case 72:text(p,q," ");
		if(q==13)
		{q=16;i=6;}
		else
		{--q;i=i-2;}
		text(p,q,"¯");

}

 if(op==13)
if(i==0)        // calling appropriate functions on the basis of choice
   { newgame(del);
   gotoxy(80,25);
    continue;}
  else if(i==2)
   { del=difficulty();
    continue;}
  else if(i==4)
    {scoreboard();
    continue;}
  else if(i==6)
    break;
  else
  ;

gotoxy(80,25);
 }
 while(op!=13);
 if(i==6) break;}
while(op!=5);
ofstream fout;
fout.open("LDRBRD",ios::binary);    //writing into the file LDRBRD
for(w=0;w<5;++w)
fout.write((char*)&(l[w]),sizeof(leaderboard));
fout.close();
 }