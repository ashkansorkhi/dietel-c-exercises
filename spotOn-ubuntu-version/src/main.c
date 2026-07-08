
// SpotOn.c
/* SpotOn challenges the player to click as many spots as possible before
   they leave the screen and before the player runs out of lives. This
   game's code consists of the following functions:

   ----------------------------------
   Overview of this game's functions:
   ----------------------------------
   - main: Controls the game's lifecycle and contains the game loop.

   - InitGame: Loads the game's sounds, and initializes the game's elements
     and state variables. This is called when the game launches and when the
     user chooses to play again.

   - UpdateGame: Called from main's game loop and defines the game logic that
     updates the game elements for the next animation frame.

   - DrawGame: Draws the game elements for the next animation frame.

   - UnloadGame: Unloads the game's sounds.


   - newSpot: Creates the spots at the beginning of the game, and creates
     each new spot when one goes out of the screen's bounds or when the user

     destroys one by clicking it.

   - increaseSpotSpeed: Called for each new level to boost every existing

     spot's speed by 5%.

   --------------------------------------

   Raylib functions used in this program:
   --------------------------------------
   - BeginDrawing: Prepare to begin drawing next animation frame in memory--
     known as an off-screen buffer.

   - CheckCollisionPointCircle: Check if a point is in a circle's bounds.

   - ClearBackground: Set off-screen buffer's background color

   - CloseAudioDevice: Release the raylib audio system's resources.


   - CloseWindow: Release game window's resources and closes window.

   - DrawCircleV: Draw a circle with the specified center, radius and color.


   - DrawText: Draw text at the specified location using the specified
     font size and color.


   - EndDrawing: Complete the current animation frame and display it on the
     screen, replacing the previous animation frame.

   - GetMousePosition: Returns the mouse's x-y coordinates.

   - GetRandomValue: Return a random integer in the range that includes both

     its first argument and its second argument.

   - InitAudioDevice: Prepare raylib's audio system to play sounds.

   - InitWindow: Set window size and title.

   - IsKeyPressed: Check if user pressed a specified key.


   - IsMouseButtonPressed: Check if user pressed a specified mouse button.

   - LoadSound: Load a sound file.


   - MeasureText: Determine the width in pixels of the specified text in the
     specified font size--often used to help center text horizontally.


   - PlaySound: Play a sound.

   - SetTargetFPS: Set target frames-per-second to drive animation.


   - UnloadSound: Release a loaded sound's resources.

   - WindowShouldClose: Check if user closed the game window.


   Raylib is Copyright ©2013-2020 Ramon Santamaria (@raysan5).
*/
#include <math.h>
#include "raylib.h" // included in every raylib game

// symbolic constants for the maximum spots and lives
#define MAX_SPOTS 3
#define MAX_SPOTS_EXTENDED 10
#define MAX_LIVES 7
#define EXPLOSION_TIMER 10
#define LIFE_EVENT_TIMER 40
// struct to maintain a spot's information
typedef struct Spot {
   Vector2 position; // x-y coordinate of the spot
   Vector2 speed; // x-y changes to spot's position in each animation frame
   double radius; // radius of the spot
   bool clicked; // false until the spot is clicked
   bool Special;
   // stores a color's r (red), g (green), b (blue) and a (alpha) components,
   // each as a value in the range 0-255.
   Color color;
} Spot;

typedef struct Life {
   Vector2 position; // x-y coordinate of the life indicator
   double radius; // radius of the life indicator
   Color color; // stores color's r, g, b, a components
} Life;

typedef struct {
 char name[10];
 int score ;   

}scoreRecord 

// global static constants
static const int screenWidth = 800;
static const int screenHeight = 450;
static const double spotRadius = 30.0;
static const double spotSpeed = 3.0; // used to determine initial speed
static const double lifeRadius = 10;
static const int startingLives = 3;
static const int newLevel = 10; // new level every 10 spots
static const int fontSize = 30; // for game text
static const double speedBoost = 1.05; // 5% speed boost each new level
static Spot ExplodedSpot = {};
static int explosionTimer = 0;
static float explosionExpandRadius = 0.0f;
static int increaseSpots = 3;
static int loseLifeTextTimer = 0 ;
static int gainLifeTextTimer = 0 ;
static int bonusExplosionTimer = 0;
// global static game state variables
static bool gameOver = false;
static bool pause = false;
static bool firstInitialization = true;
static int hitSpots = 0; // tracks total clicked spots
static Spot hitspots[MAX_SPOTS_EXTENDED] = {0};
static int lifeCount = 0; // set in InitGame
static int score = 0; // initial score
static int level = 1; // initial level
static bool loseLife = false;
static bool gainLife = false;

// global arrays to store current spots and lives
static Spot spots[MAX_SPOTS_EXTENDED]; // maintains all spots in the game
static Life lives[MAX_LIVES]; // lives displayed in lower-left corner

// global variables to store sounds loaded in InitGame
static Sound hit;
static Sound miss;
static Sound disappear;
static Sound siren;

// function prototypes
static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static Spot newSpot(void);
static void increaseSpotSpeed(void);

// controls the game's lifecycle
int main(void) {

   // initialization
   InitWindow(screenWidth, screenHeight, "SpotOn"); // prepare game window
   InitGame(); // load sounds; initialize game elements and state
   SetTargetFPS(60); // target animation frame rate

   // main game loop processing
   while (!WindowShouldClose()) { // loop until user closes window
      UpdateGame(); // update game element positions
      DrawGame(); // draw next animation frame
   }

   // termination cleanup
   UnloadGame(); // unload game sounds and release raylib's audio resources
   CloseWindow(); // close the game window
}

// initialize a new game
void InitGame(void) {

   // load sounds: this is performed once
   if (firstInitialization) {
      // raylib function InitAudioDevice prepares the raylib audio system

      InitAudioDevice();

      // raylib function LoadSound loads a specified sound file;
      // these files are located in the sounds subfolder
      hit = LoadSound("../../resources/sounds/hit.wav");
      miss = LoadSound("../../resources/sounds/miss.wav");
      disappear = LoadSound("../../resources/sounds/disappear.wav");
      siren = LoadSound("../../resources/sounds/siren.mp3");

      // set each Life objects' radius, color and coordinates
      for (int i = 0; i < MAX_LIVES; ++i) {
         lives[i].radius = lifeRadius;
         lives[i].color = GREEN; // GREEN is a predefined color constant

         // position is a raylib Vector2 object containing x and y members;
         // places the Life objects in the screen's lower-left corner
         lives[i].position.x = 20 + lives[i].radius * 2 * i + 5 * i;
         lives[i].position.y = screenHeight - 10 - lives[i].radius;
      }

      firstInitialization = false;
   }

   // reset game state
   gameOver = false;
   pause = false;
   loseLife = false;
   gainLife = false;
   score = 0;
   level = 1;
   increaseSpots = MAX_SPOTS;
   hitSpots = 0;
   lifeCount = startingLives; // start with 3 lives

   // create Spot objects by calling our newSpot function
   for (int i = 0; i < MAX_SPOTS; ++i) {
      spots[i] = newSpot();
   }
}

// update all game elements before next frame is displayed
void UpdateGame(void) {
   if (!gameOver) {
      // raylib function IsKeyPressed returns true if the specified
      // key is pressed--this game can be paused by pressing P.
      if (IsKeyPressed('P')) {
         pause = !pause;
      }

      if (!pause) { // if the game is not paused, update game state
         // raylib function IsMouseButtonPressed returns true if specified
         // mouse button is pressed--in this game, if the user clicked the
         // left mouse button, check whether click hit a spot
         if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // raylib function GetMousePosition returns a Vector2
            // containing the coordinates of the mouse click
            Vector2 clickPoint = GetMousePosition();
            bool hitSpot = false;

            for (int i = 0; level >= 3 ? i < increaseSpots: i < MAX_SPOTS; ++i) {
               // raylib provides many collision detection functions.
               // CheckCollisionPointCircle receives a Vector2 for a point
               // and a Vector2 and a double representing a Circle's
               // center and radius, and returns true if the point is
               // inside the circle.
               if (CheckCollisionPointCircle(clickPoint,
                      spots[i].position, spots[i].radius)) {
                  if(spots[i].Special){ // clicking the black spot
                            score += 100 * level; // bonus
                             PlaySound(hit);
                            hitSpot = true;
                             ExplodedSpot = spots[i];
                            bonusExplosionTimer =20;
                            for(int j = 0; level >= 3 ? j < increaseSpots: j < MAX_SPOTS; ++j){
                                 hitspots[j] = spots[j]; // saving the exploded spots
                                 spots[j] = newSpot();
                                 }
                  }
                  else{
                     spots[i].clicked = true;
                  ++hitSpots;
                  score += 10 * level; // increment the score
                  PlaySound(hit); // raylib function to play a sound
                  hitSpot = true;
                  ExplodedSpot = spots[i];
                  }

                    explosionTimer = EXPLOSION_TIMER;
                  if(hitSpots % newLevel == 0) { // check for level-up
                     ++level; // next level achieved
                     PlaySound(siren);
                     if(level >=3 && increaseSpots < MAX_SPOTS_EXTENDED){
                       spots[increaseSpots] = newSpot();
                       increaseSpots++ ;
                     }
                     increaseSpotSpeed(); // make spots move faster

                     // add a life if maximum lives has not been reached
                     if(lifeCount < MAX_LIVES) {
                        ++lifeCount;
                        gainLife = true;
                        gainLifeTextTimer= LIFE_EVENT_TIMER;
                     }
                  }
               }
            }

            // if the preceding loop did not detect a clicked spot,
            // subtract penalty amount from the score
            if (!hitSpot) {
               score -= 15 * level; // penalty for click that misses
               PlaySound(miss); // raylib function to play a sound
            }
         }
       // timer
        if(explosionTimer >0) explosionTimer --;
        if(gainLifeTextTimer >0) gainLifeTextTimer --;
         if(loseLifeTextTimer >0) loseLifeTextTimer --;
         if(bonusExplosionTimer > 0)bonusExplosionTimer-- ;
         // update spot positions to prepare for drawing them
         int clickedSpotsCounter =0 ;
         for (int i = 0; level >= 3 ? i < increaseSpots : i < MAX_SPOTS; ++i) {
            if(spots[i].clicked)
                clickedSpotsCounter++;
            if (!spots[i].clicked) { // update only unclicked spots
               // move spot
               spots[i].position.x += spots[i].speed.x;
               spots[i].position.y += spots[i].speed.y;

               // if spot left screen, replace it with a new one
               if (spots[i].position.x > screenWidth + spots[i].radius ||
                   spots[i].position.x < 0 - spots[i].radius ||
                   spots[i].position.y > screenHeight + spots[i].radius ||
                   spots[i].position.y < 0 - spots[i].radius) {
                  --lifeCount;
                  loseLife = true;
                  loseLifeTextTimer = LIFE_EVENT_TIMER;
                  PlaySound(disappear); // raylib function to play a sound
                  spots[i] = newSpot();
               }
            }
            else { // replace clicked spot with a new one
               spots[i] = newSpot();
            }
         }
         if(clickedSpotsCounter >1)
         score += 5;

      }
    if(loseLifeTextTimer ==0 )
        loseLife = false;
    if(gainLifeTextTimer==0)
        gainLife = false;
      // check if game over
      if (0 == lifeCount) {
         gameOver = true;
      }
   }
   // game is over so check if user want's to play again
   else {
      // start new game?
      if (IsKeyPressed(KEY_ENTER)) {
         InitGame(); // reset all game elements
      }
   }
}

// draw next animation frame
void DrawGame(void) {

   // raylib function BeginDrawing sets up the offscreen canvas for next
   // animation frame to display--this must be called before drawing
   BeginDrawing(); // set up

   // raylib function ClearBackground sets specified background color
   ClearBackground(WHITE); // WHITE is a raylib predefined color constant

   // draw spots
   for (int i = 0;level >= 3 ? i < increaseSpots: i < MAX_SPOTS; ++i) {
      // raylib function DrawCircleV draws a circle based on a Vector2
      // representing its center, a double radius and a color--raylib
      // often provides multiple functions that can draw a shape with
      // different sets of arguments (there are five functions for circles

     DrawCircleV(spots[i].position, spots[i].radius, spots[i].color);
   }

   //draw distroyed spot

      if(explosionTimer >0) {
        explosionExpandRadius = (EXPLOSION_TIMER-explosionTimer)* 2.0;
    DrawCircleSector(ExplodedSpot.position,ExplodedSpot.radius + explosionExpandRadius, 0.0f, 45.0f, 1 ,ExplodedSpot.color);
            DrawCircleSector(ExplodedSpot.position,ExplodedSpot.radius + explosionExpandRadius , 55.0f, 100.0f, 10 ,ExplodedSpot.color);
            DrawCircleSector(ExplodedSpot.position,ExplodedSpot.radius + explosionExpandRadius , 110.0, 155.0f, 10 ,ExplodedSpot.color);
            DrawCircleSector(ExplodedSpot.position,ExplodedSpot.radius + explosionExpandRadius , 165.0f, 210.0f, 10 ,ExplodedSpot.color);
            DrawCircleSector(ExplodedSpot.position,ExplodedSpot.radius + explosionExpandRadius , 220.0f, 265.0f, 10 ,ExplodedSpot.color);
            DrawCircleSector(ExplodedSpot.position,ExplodedSpot.radius + explosionExpandRadius , 275.0f, 320.0f, 10 ,ExplodedSpot.color);
            DrawCircleSector(ExplodedSpot.position,ExplodedSpot.radius + explosionExpandRadius , 330.0f, 350.0f, 10 ,ExplodedSpot.color);

                }
                if(bonusExplosionTimer >0) {
                    for(int i = 0;level >= 3 ? i < increaseSpots: i < MAX_SPOTS; ++i){
                        DrawCircleSector(hitspots[i].position,hitspots[i].radius + explosionExpandRadius, 0.0f, 45.0f, 1 ,hitspots[i].color);
            DrawCircleSector(hitspots[i].position,hitspots[i].radius + explosionExpandRadius , 55.0f, 100.0f, 10 ,hitspots[i].color);
            DrawCircleSector(hitspots[i].position,hitspots[i].radius + explosionExpandRadius , 110.0, 155.0f, 10 ,hitspots[i].color);
            DrawCircleSector(hitspots[i].position,hitspots[i].radius + explosionExpandRadius , 165.0f, 210.0f, 10 ,hitspots[i].color);
            DrawCircleSector(hitspots[i].position,hitspots[i].radius + explosionExpandRadius , 220.0f, 265.0f, 10 ,hitspots[i].color);
            DrawCircleSector(hitspots[i].position,hitspots[i].radius + explosionExpandRadius , 275.0f, 320.0f, 10 ,hitspots[i].color);
            DrawCircleSector(hitspots[i].position,hitspots[i].radius + explosionExpandRadius , 330.0f, 350.0f, 10 ,hitspots[i].color);
                    }
                 }
if(loseLife && loseLifeTextTimer >0){
      DrawText("YOU LOST A LIFE",screenWidth / 2 - MeasureText("YOU LOST A LIFE", fontSize) / 2 ,screenHeight/5 , fontSize, GRAY);
   }
if(gainLife && gainLifeTextTimer >0){
      DrawText("YOU GAINED A LIFE",screenWidth / 2 - MeasureText("YOU GAINED A LIFE", fontSize) / 2 ,screenHeight-screenHeight/5 , fontSize, GRAY);
   }
   // game paused?

   if (pause) {
      static char *paused = "Paused: Press P to Continue";

      // Show paused message centered horizontally and vertically.
      // raylib function DrawText receives the text to draw and two
      // doubles representing where to start drawing the text.
      // raylib function MeasureText returns the width of the text in its
      // first argument, based on the font size in its second argument.
      DrawText(paused,
         screenWidth / 2 - MeasureText(paused, fontSize) / 2,
         screenHeight / 2 - fontSize / 2, fontSize, GRAY);
   }

   // game over?
   if (gameOver) {
      static char *playAgain = "PRESS ENTER TO PLAY AGAIN";

      // show playAgain message centered horizontally and vertically
      DrawText(playAgain,
         screenWidth / 2 - MeasureText(playAgain, fontSize) / 2,
         screenHeight / 2 - fontSize / 2, fontSize, GRAY);
   }

   // draw lives
   for (int i = 0; i < lifeCount && i < MAX_LIVES; ++i) {
      DrawCircleV(lives[i].position, lives[i].radius, lives[i].color);
   }

   // draw score and level--raylib function FormatText works like printf,
   // but returns the formatted text.
   DrawText(TextFormat("LEVEL: %d", level), 15, 15, 25, BLACK);
   DrawText(TextFormat("SCORE: %d", score), 15, 45, 25, BLACK);

   // raylib function EndDrawing terminates the drawing phase,
   // then raylib displays this animation frame
   EndDrawing();
}

// release game resources
void UnloadGame(void) {

   // raylib function UnloadSound releases resources for specified Sound
   UnloadSound(hit);
   UnloadSound(miss);
   UnloadSound(disappear);
   UnloadSound(siren);
   // raylib function CloseAudioDevice releases the raylib audio resources
   CloseAudioDevice();
}

// create one Spot
Spot newSpot(void) {
   Spot s;

   // choose random start position
   // raylib function GetRandomValue returns an integer in the range
   // from its first argument up to and including its second, so
   // GetRandomValue (1, 6) would return an integer from 1 to 6.
   s.position.x = GetRandomValue(spotRadius, screenWidth - spotRadius);
   s.position.y = GetRandomValue(spotRadius, screenHeight - spotRadius);

   // choose random dx (change in x) by which a spot's x-coordinate changes
   // in each animation frame
   double dx = 0.0;

   // if x in left half of screen, spot moves right; otherwise, moves left
   if (s.position.x < screenWidth / 2) {
      dx = GetRandomValue(1, spotSpeed);
   }
   else {
      dx = GetRandomValue(-spotSpeed, -1);
   }

   // choose random dy (change in y) by which a spot's y-coordinate changes
   // in each animation frame
   double dy = 0.0;

   // if y in top half of screen, spot moves down; otherwise, moves up
   if (s.position.y < screenHeight / 2) {
      dy = GetRandomValue(1, spotSpeed);
   }
   else {
      dy = GetRandomValue(-spotSpeed, -1);
   }

   // calculate speed boost based on level
   double currentSpeedBoost = pow(speedBoost, level - 1);
    int specialSpot = GetRandomValue(1,100);
    if(specialSpot%10 == 0){
    s.speed.x = dx * 2.0f;
   s.speed.y = dy * 2.0f;

   s.radius = spotRadius;
   s.clicked = false;
   s.color = BLACK ;
   s.Special = true;
      return s;
    }
   s.speed.x = dx * currentSpeedBoost;
   s.speed.y = dy * currentSpeedBoost;
   s.radius = specialSpot % 20 ==0 ? 15 : spotRadius;
   s.clicked = false;
   static Color colors[] = {RED, ORANGE, GREEN, BLUE, VIOLET};
   s.color = colors[GetRandomValue(0, 4)]; // select random color from colors
   s.Special = false;
   return s;
}

// increase the spot speed by for new level
void increaseSpotSpeed(void) {
   for (int i = 0;level >= 3 ? i < increaseSpots: i < MAX_SPOTS; ++i) {
      spots[i].speed.x *= speedBoost;
      spots[i].speed.y *= speedBoost;
   }
}



/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/






