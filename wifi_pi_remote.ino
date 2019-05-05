#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

int s_in;                                        //define string to be read
String s_out;

int s = 255; //set default speed

int picbutton = 49;
int manualbutton = 47; // define all button pins
int camerabutton = 48;

LiquidCrystal screen(2, 3, 4, 5, 44, 45); // reset, enable, digital pins


int mbuttonstate; //set all button states
int cbuttonstate;
int pbuttonstate;

int motor[] = {6, 7, 9, 8, 10, 11, 13, 12}; //define all motor pins fwd, bkwrd



/*
  pin [fwd, bkwrd] - identifier [fwrd, bkwrd]
    [6, 7]  motor[0, 1]    [8, 9]motor [2,3]




    [12, 13]  motor[6,7]  [10, 11]  motor[4,5]
*/

void setup()
{
  screen.begin(16, 2); // set width and height of screen

  Serial.begin(9600); //begin serial connnection


  for (int i = 0; i < 8; i++) //define motors as outputs
  {
    pinMode(motor[i], OUTPUT);
    analogWrite(motor[i], 0);
  }

  pinMode(manualbutton, INPUT_PULLUP); //define buttons as inputs
  pinMode(camerabutton, INPUT_PULLUP);
  pinMode(picbutton, INPUT_PULLUP);

  screen.print("Select Mode"); //print to lcd
  screen.setCursor(1, 2); //set start of next lcd line
  screen.noBlink();
}


void manual()
{
  int a = 50;    //delay
  s_out = 'm';
  Serial.println(s_out);                             //send string to pi
  screen.print("Manual Mode"); //lcd display reads maual mode
  screen.noBlink();
  s_in = 1;
  s_in = s_in * (Serial.read() - '0');    //convert to int

  if (s_in == 1) //forward
  {
    Serial.println("up");
    analogWrite(motor[1], 0);
    analogWrite(motor[3], 0);
    analogWrite(motor[5], 0);
    analogWrite(motor[7], 0);

    analogWrite(motor[0], s);
    analogWrite(motor[2], s);
    analogWrite(motor[4], s);
    analogWrite(motor[6], s);
    delay(a);
  }

  if (s_in == 2) //backward
  {
    analogWrite(motor[0], 0);
    analogWrite(motor[2], 0);
    analogWrite(motor[4], 0);
    analogWrite(motor[6], 0);


    analogWrite(motor[1], s);
    analogWrite(motor[3], s);
    analogWrite(motor[5], s);
    analogWrite(motor[7], s);
    delay(a);
  }

  if (s_in == 3) //left
  {
    analogWrite(motor[1], 0);
    analogWrite(motor[6], 0);
    analogWrite(motor[2], 0);
    analogWrite(motor[5], 0);

    analogWrite(motor[0], s);
    analogWrite(motor[3], s);
    analogWrite(motor[4], s);
    analogWrite(motor[7], s);
    delay(a);
  }

  if (s_in == 4) //right
  {
    analogWrite(motor[0], 0);
    analogWrite(motor[3], 0);
    analogWrite(motor[4], 0);
    analogWrite(motor[7], 0);

    analogWrite(motor[1], s);
    analogWrite(motor[6], s);
    analogWrite(motor[2], s);
    analogWrite(motor[5], s);
    delay(a);
  }

  if (s_in == 5) //up left
  {
    analogWrite(motor[1], 0);
    analogWrite(motor[2], 0);
    analogWrite(motor[3], 0);
    analogWrite(motor[5], 0);
    analogWrite(motor[6], 0);
    analogWrite(motor[7], 0);

    analogWrite(motor[0], s);
    analogWrite(motor[4], s);
    delay(a);
  }

  if (s_in == 6) //down right
  {
    analogWrite(motor[0], 0);
    analogWrite(motor[1], 0);
    analogWrite(motor[2], 0);
    analogWrite(motor[4], 0);
    analogWrite(motor[6], 0);
    analogWrite(motor[5], 0);

    analogWrite(motor[3], s);
    analogWrite(motor[7], s);
    delay(a);
  }

  if (s_in == 7) //up left
  {
    analogWrite(motor[1], 0);
    analogWrite(motor[3], 0);
    analogWrite(motor[0], 0);
    analogWrite(motor[4], 0);
    analogWrite(motor[5], 0);
    analogWrite(motor[7], 0);

    analogWrite(motor[2], s);
    analogWrite(motor[6], s);
    delay(a);
  }

  if (s_in == 8) //down left
  {
    analogWrite(motor[0], 0);
    analogWrite(motor[2], 0);
    analogWrite(motor[3], 0);
    analogWrite(motor[4], 0);
    analogWrite(motor[7], 0);
    analogWrite(motor[6], 0);

    analogWrite(motor[1], s);
    analogWrite(motor[5], s);
    delay(a);
  }

  if (s_in == 9) //spin ccw
  {
    analogWrite(motor[0], 0);
    analogWrite(motor[3], 0);
    analogWrite(motor[5], 0);
    analogWrite(motor[6], 0);

    analogWrite(motor[1], s);
    analogWrite(motor[2], s);
    analogWrite(motor[7], s);
    analogWrite(motor[4], s);
    delay(a);
  }

  if (s_in == 0) //off
  {
    for (int i = 0; i < 8; i++)
    {
      analogWrite(motor[i], 0);
    }
    delay(a);
  }
  delay(250);
  screen.clear();
}

void camera()
{
  screen.clear();
  screen.print("Camera Mode"); //lcd display reads Camera Mode
  screen.setCursor(1, 2);
  pbuttonstate = digitalRead(picbutton);
  delay(250);
  if (pbuttonstate == 0)
  {
    s_out = 'c';
    Serial.println(s_out);                             //send string to pi
  }
  if (Serial.available())                        //if connection is avalible
  {
    int b = 2000;
    s_in = 1;
    s_in = s_in * (Serial.read() - '0');    //convert to int
    screen.clear();
    if (s_in == 1) //forward
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[1], 0);
      analogWrite(motor[3], 0);
      analogWrite(motor[5], 0);
      analogWrite(motor[7], 0);

      analogWrite(motor[0], s);
      analogWrite(motor[2], s);
      analogWrite(motor[4], s);
      analogWrite(motor[6], s);

      Serial.println("go");
      delay(b);
      screen.clear();

      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }

    }
    else if (s_in == 2) //backward
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[0], 0);
      analogWrite(motor[2], 0);
      analogWrite(motor[4], 0);
      analogWrite(motor[6], 0);


      analogWrite(motor[1], s);
      analogWrite(motor[3], s);
      analogWrite(motor[5], s);
      analogWrite(motor[7], s);
      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 3) //left
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[1], 0);
      analogWrite(motor[6], 0);
      analogWrite(motor[2], 0);
      analogWrite(motor[5], 0);

      analogWrite(motor[0], s);
      analogWrite(motor[3], s);
      analogWrite(motor[4], s);
      analogWrite(motor[7], s);

      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 4) //right
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[0], 0);
      analogWrite(motor[3], 0);
      analogWrite(motor[4], 0);
      analogWrite(motor[7], 0);

      analogWrite(motor[1], s);
      analogWrite(motor[6], s);
      analogWrite(motor[2], s);
      analogWrite(motor[5], s);

      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 5) // up left
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[1], 0);
      analogWrite(motor[2], 0);
      analogWrite(motor[3], 0);
      analogWrite(motor[6], 0);
      analogWrite(motor[5], 0);
      analogWrite(motor[7], 0);

      analogWrite(motor[0], s);
      analogWrite(motor[4], s);

      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 6) //down left
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[0], 0);
      analogWrite(motor[1], 0);
      analogWrite(motor[2], 0);
      analogWrite(motor[5], 0);
      analogWrite(motor[6], 0);
      analogWrite(motor[4], 0);

      analogWrite(motor[7], s);
      analogWrite(motor[3], s);

      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 7) // down right
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[0], 0);
      analogWrite(motor[2], 0);
      analogWrite(motor[3], 0);
      analogWrite(motor[4], 0);
      analogWrite(motor[5], 0);
      analogWrite(motor[6], 0);

      analogWrite(motor[1], s);
      analogWrite(motor[5], s);

      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 8) //up right
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[0], 0);
      analogWrite(motor[1], 0);
      analogWrite(motor[2], 0);
      analogWrite(motor[4], 0);
      analogWrite(motor[6], 0);
      analogWrite(motor[7], 0);

      analogWrite(motor[3], s);
      analogWrite(motor[7], s);
      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 9) //spin ccw
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[0], 0);
      analogWrite(motor[3], 0);
      analogWrite(motor[5], 0);
      analogWrite(motor[6], 0);

      analogWrite(motor[1], s);
      analogWrite(motor[2], s);
      analogWrite(motor[7], s);
      analogWrite(motor[4], s);

      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
    else if (s_in == 0) //spin cw
    {
      screen.print("Number from Pi"); //insert data from pi
      screen.setCursor(1, 2);
      screen.print(s_in);

      analogWrite(motor[1], 0);
      analogWrite(motor[2], 0);
      analogWrite(motor[4], 0);
      analogWrite(motor[7], 0);

      analogWrite(motor[0], s);
      analogWrite(motor[3], s);
      analogWrite(motor[5], s);
      analogWrite(motor[6], s);

      delay(b);
      screen.clear();
      for (int i = 0; i < 8; i++)
      {
        analogWrite(motor[i], 0);
      }
    }
  }
}

void loop()
{
  mbuttonstate = digitalRead(manualbutton); //check the button state//check the button state
  cbuttonstate = digitalRead(camerabutton);  // if (mbuttonstate == 0) //if manual button pressed run manual button function

  if ((mbuttonstate == 0) && (cbuttonstate == 1))
  {
    manual();
  }

  else if ((cbuttonstate == 0) && (mbuttonstate == 1))// if camera button pressed run maual button function
  {
    camera();
  }

  else
  {
    screen.clear();
    screen.print("Select One Mode");
    delay(250);
  }
}
