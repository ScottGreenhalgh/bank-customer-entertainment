# Bank Customer Entertainment

This is a small banking application that allows users in the lobby area of a bank to seek entertainment while waiting to be served. This C application contains a character which has the functionality to move left and right. After selecting the number of attempts the customer wishes to take (selected via the 0 – 9 keys on the keyboard), they have the ability to throw a projectile towards a designated marker using left mouse button, all while avoiding a moving object that could obstruct the projectile. If the projectile comes into contact with the obstruction, the projectile is reflected back towards the character, damaging their final score values. After each throw, the marker found on the virtual ground will move to various different locations, adding some level of difficulty to the game. While the customer participates in the game, it is retaining information related to your best throw and worst throw. This will be followed up with a mean and standard deviation calculation of all the throws that the customer has partaken in. This information is produced to the user at the end of their final attempt. This information is that persons score at the end of the game. The game will proceed with a prompt to either hit “Esc” to terminate the game, or “Space” to restart, pressing either will execute the selected function. While playing the game the user has the ability to move left and right using the “A” and “D” keys on the keyboard to do so.

### Problem Analysis

During the construction of the banking application there were a few hurdles that I needed to overcome that would allow my application to function as intended. My largest hurdle that I was required to overcome was an error that was repeatedly occurring during my development of the game. This error was called a “Segmentation fault”. After rigorous research into why this problem was occurring it appears that it was when my application was trying to read portions of my system memory that it didn’t have access to. When I was attempting to fix this, it appears on a couple occasions it was occurring as a result of a very minor error on my part where I would for example perform calculations that were involving integers and floating-point values together. The picture found below is the exact issue I was presented with during development of this game as it was a recurring theme.

This particular segmentation fault that was occurring took an estimated 90 minutes to resolve with many attempts at various different fixes before finding a solution. It was an issue that resulted from improper usage of string concatenation. Originally, I was using:

```c
else if(currentAttempt + 1 <= attempts) {
        char text[255];
        sprintf(text, "Current Attempts %i/%i", currentAttempt + 1, attempts);
        GFX_DrawText(10, 10, text);
```

### Specification

The basis of the application was originally created with the aid of the weekly labs, however upon receiving the assignment, I decided to rebuild the whole game from the ground up as there were a few things I wanted to do differently. This decision was mainly down to the fact that I had only used a single function up to this point that heavily relied on the other elements present and segmentation would’ve been easier from the ground up. Obviously, I’m still going to use elements that were already present in the original. For example, the following was used to construct my character in my original work:

```c
int head[3] = {160, 400, 10}; // x y radius
    int leye[4] = {head[0] - 3, head[1] - 5, head[0] - 3, head[1] - 1}; // xS yS xE xS
    int reye[4] = {head[0] + 3, head[1] - 5, head[0] + 3, head[1] - 1}; // xS yS xE xS
    int mouth[5] = {head[0], head[1], 5, 0, 180}; //x y radius arc_s arc_e
    int body[4] = {head[0], head[1] + 10, head[0], head[1]+ 60};// xS yS xE xS
    int larm[4] = {body[0], body[1], body[0] - 30, body[1] + 30};// xS yS xE xS
    int rarm[4] = {body[0], body[1], body[0] + 30, body[1] + 30};// xS yS xE xS
    int lleg[4] = {body[2], body[3], body[2] + 30, body[3] + 30};// xS yS xE xS
    int rleg[4] = {body[2], body[3], body[2] - 30, body[3] + 30};// xS yS xE xS
    int floorY = 490;
```

As you can see from the arrays above, I tried to minimise the hard coding in the document as much as possible. This made it incredible easy to initialise a new variable inside the head array which would control movement on the X coordinate (160 in this example). As these arrays all refer to the head, it made it extremely easy to modify the location of the character by simply changing a single value. This was later reconstructed but I’ll cover that further down.

### Creating the marker and projectile

Before I move onto how I rebuilt my applications core functionality, I’ll briefly cover the original in a little more detail. As the labs previously stated, it was imperative to have a projectile launch from the character towards a marker. To complete this task, I originally made the following:

```c
int random_x = GFX_RandNumber(300, 1000);
        GFX_DrawLine(random_x, floorY, random_x, floorY + 40, thickness);
        GFX_UpdateDisplay();

int initial_pos_x = rarm[2];
int initial_pos_y = rarm[3];
int pos_y = initial_pos_y;
int pos_x = initial_pos_x;

const float gravity = 9.81;

GFX_MoveTo(initial_pos_x, initial_pos_y);

int landing_x = 0;

bool projectile = true;
	while (projectile) {
            float time = (pos_x - rarm[2]) / vel_x;
            if (pos_y < floorY) { //if its smaller than floor
                pos_y = initial_pos_y - (vel_y * time) + (gravity * time * time)/2;
                pos_x += 1;
                landing_x = pos_x;
            } else if(pos_y == floorY) { //if it is on floor
                projectile = false;
            }
            GFX_DrawLineTo(pos_x, pos_y, thickness);
            GFX_UpdateDisplay();
    }
```

There are two different components to the portion that is shown above. The top three lines dictate where the marker goes using the random values. Alongside this I also used the following to improve the range of values that were randomly generated using the system clock as it appeared to originally cycle between only a couple values:

```c
#include <time.h>

    time_t dd;
    srand((unsigned) time(&dd) + clock());
```

After the marker line is drawn, the segment that followed this dealt with drawing the arc that would become the projectile. To do this I created a Boolean expression that would set itself to false once the projectiles coordinates were below the level of the floor (variable named floorY). This was followed up with a while loop that contained two if statements, one that would check if the projectile was above the coordinate of the floor, the other which would check if the projectile reached the floor. Once the projectiles coordinate reached the level of the floor, the Boolean expression would be set to false and would no longer execute the loop. A few other variables were initialised before the calculations as they were a core element in their operation.

### Mathematical calculations

The last fundamental feature of my original application (which I will be adapting and reusing) was the mathematics, and calculations related to this, which would analyse a variety of different pieces of data, such as best throw, worst throw, mean of all throws and standard deviation of those throws. This information was input into the console window at this time and relied heavily on “printf”. The following is the way in which this was completed:

```c
int distance = abs(random_x - landing_x);

printf("Attempt %d: Distance from marker: %d\n", currentAttempt + 1, distance);

player_attempts_values[currentAttempt] = distance;

if(best_throw > distance || currentAttempt == 0) {
	best_throw = distance;
}
if(worst_throw < distance || currentAttempt == 0) {
       worst_throw = distance;
}

total_throw_distance += distance;

printf("Mean Distance: %d, Best Throw: %d, Worst Throw: %d\n\n", (total_throw_distance / (currentAttempt + 1)), best_throw, worst_throw);
if(attempts != currentAttempt + 1) {
        printf("Press enter to take your next attempt\n");
	} else {
        printf("Press enter to see final results\n");
	}
	getchar();
       getchar();
}

int calculated_mean = total_throw_distance / attempts;

int average_sqaured = 0;
for(int i = 0; i < attempts; i++) {
	player_attempts_values[i] -= calculated_mean; //subtract mean
       player_attempts_values[i] *= player_attempts_values[i]; //square itself
       average_sqaured += player_attempts_values[i]; //add to total
}
average_sqaured = average_sqaured / attempts; //get average

printf("Standard Deviation: %d, Mean Distance: %d, Best Throw: %d, Worst Throw: %d\n\n", (int) sqrt(average_sqaured), (total_throw_distance / attempts), best_throw, worst_throw);

```

To create all the mathematics shown above I was required to find the distance between the location the projectile landed and the location in which the marker was located. To do that I needed to take the absolute value of the two subtracted from each other. This prevented this value from becoming a negative and damaging all my calculations. An array was then created which would store the distance of the projectile from the marker after each attempt. This array would scale with the number of selected attempts, so it would never be too large. Once these values were placed into the array, a couple of if statements would check to see what the largest and smallest values of distance were inside the array and assign them to the variables best and worst throws respectively. From here I can just use the formula for both the mean and standard deviation to manipulate the variables I already possess to calculate these values for me. In the configuration shown above, I am outputting the result to console using printf. The comments found within the standard deviation calculation show exactly how this segment was broken down and calculated.

### Using classes to segment the application

The original application did function as intended but heavily relied on the usage of the terminal window, which I decided was going to be removed from my application altogether. Therefore, using everything shown above I was ready to begin reconstructing the application again from the ground up. To begin I decided to make a plan of action. Each of the core components of the application would be categorised into a class of its own, consisting of “GamePlayer.c”, “Level.c” and “InputHandler.c”, all of which had an accompanying .h file. I would then use #include to bring the game together at the end via “main.c”. I decided to take this approach as it would allow me to segment the game into different components, making development, and readably much easier.

To solidify my plan of action further I decided to segment my `main.c` into 3 easy to use sections, one for when the game is playing, one for when the menu is open, and a last one for when the game is closing or about to close. These states were labelled as “GAMESTATUS_QUIT”, “GAMESTATUS_PLAYING” and “GAMESTATUS_MENU”. As it turns out, I never got around to creating a menu in the end, so instead I just have a placeholder which can be used to add a menu to the game in the future. As a result I no longer needed GAMESTATUS_PLAYING as I could just create an else statement on the menu instead.

### TPS limiter

Following on from this I decided to build something that would lock my ticks per second. This is something I noticed originally when I created my game the first time, that different machines would handle the game at different rates (high end PC’s would execute elements of the game too fast, e.g. character movement), limiting this allowed my game to run identically on all systems, no matter the hardware. This was conducted using the following:

```c
end = time(NULL);
        double elapsed = difftime(end, start);
        double allowedTPS = (float)1 / (float)30;
        if(elapsed < allowedTPS) {
            usleep((allowedTPS - elapsed) * 1000000);

```

At the same time, I also created something that would allow the “X” or “Cross” in the top right-hand corner to function as intended (closing the window), which happened to turn out to be very useful later on when I added an exit element to the game which would terminate the application. This component was added under the previously mentioned “GAMESTATUS_QUIT” segment of the main.c file.

### Handling Inputs

Storing the states of any input (the key presses/release) was very important if I wanted to move away from a terminal style input system. To do this I designed something that would grab any key press and assign the value to a variable called key. I would then run an if statement that would check if a certain key was pressed (using the allegro key codes). If a certain key was pressed it would complete the conditions for the if statement and allow the whatever desired action to perform. This was a very important feature for my game and was one of the main reasons for rebuilding the application from the ground up as I wanted this to be the core element when designing its functionality. I completed this by using the following:

```c

else if(GFX_IsEventKeyDown()) {
	int key;
	GFX_GetKeyPress(&key);
	SetKeyPressed(key);
}
else if(GFX_IsEventKeyUp()) {
	int key;
	GFX_GetKeyPress(&key);
	SetKeyReleased(key);
}
else if(GFX_IsEventMouseButton()) {
	int key;
	GFX_GetMouseButton(&key);
	MouseButtonPressed(key);
}
else if(GFX_IsEventMouseMoved()) {
	int mx, my;
	GFX_GetMouseCoordinates(&mx, &my);
	SetMousePosition(mx, my);
}

```

A required feature for the application was the creation and implementation of an obstacle that would impede the users efforts to reach the randomly generating marker. I originally wanted this to be a cube, but half way through development I decided a line would’ve been more appropriate, which is why some of my variables mention a cube instead of a line as the obstruction. When I was designing the marker for my usage, I had some criteria that I wanted to achieve. After completing it I can say that I managed to exceed all my expectations. My criteria needed the obstacle to move up and down to make it somewhat difficult to avoid, allow it to vary in size during each attempt, always appear between the user and the marker and to reflect the projectile if it came into contact with the obstacle. That last piece of criteria originally during development reflected exactly along the path it took to begin with (as I never made any form of air resistance), so instead I had it slightly change the way in which it would reflect the projectile by modifying the velocity slightly. I think this was an acceptable compromise as it would benefit the user if the projectile wasn’t launched too far away from the marker, ruining their score too much. This obstacle was created using the following (elements not necessarily in the given order):

```c
int cubePosX = 500;
int cubePosY = 200; //random
int cubeSize = 30; //random
int cubeMovementDirection = 4;

GFX_DrawLine(cubePosX, cubePosY, cubePosX, cubePosY + cubeSize, 2);

if(cubePosY <= 50) cubeMovementDirection = 4; // varies the obstructions location
else if(cubePosY+cubeSize >= 450) cubeMovementDirection = -4;
	cubePosY += cubeMovementDirection;

```

### Adding a bitmap image

As an integral part of the application was to make it bank themed I decided that I was going to import a bank related image to represent this piece of criteria. Originally, I wasn’t too sure what the image was going to be, but I eventually settled on the Harry Potter bank, Gringotts (image referenced below the appendix). I decided that this would be the most appropriate image to represent this element as it isn’t a physical bank, instead it is fictional. This therefore means that the image won’t be requiring change if the usage location differs. To add this image, I looked into how the graphics_lib.c wrapper handled this. After sourcing the image, it actually wasn’t too difficult to implement, and I used the flowing to do so:

under level.c

```c
BITMAP backgroundImage;

void LoadBitmaps() // loads the bank related background image
{
    backgroundImage = GFX_LoadBitmap("res/bank_image.bmp");

(under main.c)

LoadBitmaps();
```

A feature I decided would be useful to have during the gameplay is the ability to move the character left and right at the press of a button, so that’s exactly what I designed. To do this I used my already existing key variable which is assigned to whatever allegro key code that is pressed at that particular moment. From here all I needed to do is create an if statement that would check whether the key is down using that particular allegro key code. To perform this action the following is used:

```c
if(GetKeyPressed(1)) { //check if A key is pressed
        playerInformation.playerX = playerInformation.playerX - 4;
        if(160 + playerInformation.playerX < 20) playerInformation.playerX = 20 - 160;
    }
if(GetKeyPressed(4)) { //check if D key is pressed
        playerInformation.playerX = playerInformation.playerX + 4;
        if(160 + playerInformation.playerX > 250) playerInformation.playerX = 250 - 160;
```

### Evaluating successful completion and testing

As previously stated, after the user has gone through the designated number of attempts, the user is produced with a score that they can use as a means of representing how good they performed in the game. To my current knowledge, there isn’t a way of breaking my particular game as all the inputs for the game are handled by monitored key presses, if keys are pressed that aren’t being monitored, nothing will execute. If keys are pressed out of order, they won’t execute their function until the top left hand corner prompts the user to do so. This was completed using “printf” on multiple occasions to debug what is doing what at any given time. As far as testing goes, as long as the main function is executed, the program will run without a single problem. This is due to main.c featuring #include on all the other external classes that were created. Everything is brought together with the execution of the main.c and runs as a whole (after being compiled).

## Evaluation

The application in its current configuration works exactly as I intended it to. To elaborate on exactly how it works; once the program is launched, the user has the ability to move left and right using the keys “A” and “D” on the keyboard. All of the other game functionality is limited until the user decides to select a number of attempts they would like at the game, as prompted in the top left-hand corner. This value is determined using the number keys that are situated along the top row of the keyboard. I decided to use these keys instead of the number pad as some keyboards and or laptops don’t have the number pad, so for the application to be universally functional on any keyboard, these keys were the best fit. After the number of attempts have been selected, the top left-hand corner will update in real time with the attempt that you are currently performing and will wait for the user to left click on the screen to draw a projectile towards the marker. The arc is calculated based on how far the mouse cursor is from the mans right arm. This therefore means that for the most powerful throw, you would need to situate your mouse in the top right-hand corner before clicking. Once all the attempts have been completed personal score will be developed based on your results. Below your total score, you will find a couple options, pressing “Esc” to close the application, or “Space” to have another go from the beginning.

While I feel that the application perfectly fits the criteria in terms of feature set, and having built it twice already, there are a few things that I would like to add/change if I decided to rebuild or modify the app further. For one the application doesn’t use very detailed graphics, it is currently composed of many different lines that were drawn using allegro features. A much more visually appealing, easy to implement solution would be the creation of bitmap images that are placed at certain coordinates. These could potentially have many different alterations which would cycle depending on the action that is being performed. This would’ve cut down on the number of arrays required to draw the player in the first place, cleaning that portion of the application up significantly.
Another small adaptation that I would’ve liked to make given the chance is the creation of a main menu. I added the required elements into main.c that would’ve been required to implement the menu in the first place, however I never got around to ever creating the menu as I felt that the game had a good enough flow already. The only reason I say this addition would be good in hindsight is down to the fact that I would’ve liked to add a high score system to the application too, which wouldn’t be readily accessible without the addition of the main menu (at least how I envision it to be at least).  
Lastly, I probably would’ve made it more banker specific. Currently the only slightly banking related element of the whole application is the large dragon in the background which is a reference to the bank found in Harry Potter called Gringotts bank. This was chosen as it quite an iconic bank that I believe the majority of people can relate to.

### References

sato, m. and profile, V. (2018). The myths and folktales behind Harry Potter. [online] Mimisato.blogspot.co.uk. Available at: https://mimisato.blogspot.co.uk/2016/12/the-myths-and-folktales-behind-harry.html [Accessed 23 Mar. 2018].

graphics_lib.h is a licensed library and has been ommited.
