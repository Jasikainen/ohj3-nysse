***
# TIE-02402 - Programming 3: Techniques - project work
## Nysse Game
Game based in Tampere city centre where main actor is "Nysse" that is word "bus" in Tampere dialect (Finnish city).

## Course
This content in the folder Course was given by the course. Our project team wasn't eligible to modificate the contents and its functionality.

## Documentation
The documentation of the project can be found under Documentation folder as PDF file.

## Game in brief
After starting the game there will be a start-up dialog. In the dialog you will be asked to enter your player nickname.
After that the game screen is shown to you. 

The game starts after clicking *start* button. There will be a aeroplane in the view that player
can move with *WASD* keys. The plane shoots projectiles by pressing *SPACE* key.
Your mission is to destroy the red Nysses (busses) with projectiles so that you get score. 

The score is calculated by:
* 10 pts per Nysse
* n points per amount of passengers in the nysse

By clicking the game view there will appear radar for a couple of seconds that shows the areas passengers and nysses on the right side of GUI.
Radar takes in count also the passengers at the white stops in game view.
Accuracy is calculated by destroyed nysses and shot projectiles, there is a chance to shoot two nysses with one projectile if lucky.

Elapsed game time and the in-game time are shown on the top right corner of GUI.
Game may be stopped, but also continued if chosen so after pressing *end* button.

If the game is stopped by running out of time there will be shown top-10 statistics.
Your score, accuracy and nickname are saved to highscores if it's sufficient.

---
HOX:
Game time may be changed from file config.hh variable PLAY_TIME. Now it is set to two minutes as (0,2,0) in (h,m,s) form.

IF pressing the *end* button and continuing game, you may have to refocus to screen by in example scanning the gameview with radar.
Or else the focus may not be back in the gameview for you to move the plane!
---

## Authorities
* Name: Jani Asikainen
* E-Mail: jani.asikainen@tuni.fi
* Github @ Jasikainen

* Name: Rasmus Silander
* E-Mail: rasmus.silander@tuni.fi
* Github @ -
