#include <iostream>
#include<fstream>
#include "help.h"
using namespace std;
//this function removes yellow box and replaces it with black box
static void removeBox(int box_x, int box_y)
{
	myEllipse(box_x + 5, box_y - 10, box_x + 35, box_y + 20, 0, 0, 0, 0, 0, 0);
	myRect(box_x, box_y - 5, box_x + 40, box_y + 5, 0, 0, 0);
}
//this function removes generates new yellow box
void drawBox(int box_x, int box_y)
{
	myEllipse(box_x + 5, box_y - 10, box_x + 35, box_y + 20, 255, 255, 0, 255, 255, 0);
	myRect(box_x, box_y - 5, box_x + 40, box_y + 5, 255, 255, 0);
}
//this function generates yellow circle alliens
void drawallien(int box_x, int box_y)
{
	myEllipse(box_x, box_y, box_x + 30, box_y + 30, 0, 0, 255, 255, 0, 250);
	myEllipse(box_x + 5, box_y + 5, box_x + 25, box_y + 25, 0, 0, 0, 100, 0, 100);
	myEllipse(box_x + 15, box_y + 10, box_x + 20, box_y + 20, 0, 0, 0);
}
// This function removes yellow circle alliens and replaces it with black circle alliens
static void removeallien(int box_x, int box_y)
{
	myEllipse(box_x, box_y, box_x + 30, box_y + 30, 0, 0, 0);
}
//this function makes bullets
void make_bullet(int box_x, int box_y) {
	myLine(box_x, box_y - 15, box_x, box_y, 40, 55, 440);
	myLine(box_x + 2, box_y - 15, box_x + 2, box_y, 40, 55, 400);
}
// this function erases bullets
static void erase_bullet(int box_x, int box_y) {
	myLine(box_x, box_y - 15, box_x, box_y, 0, 0, 0);
	myLine(box_x + 2, box_y - 15, box_x + 2, box_y, 0, 0, 00);
}
void make_enemy_bullet(int box_x, int box_y) {
	myLine(box_x, box_y - 15, box_x, box_y, 40, 55, 440);
	myLine(box_x + 2, box_y - 15, box_x + 2, box_y, 40, 255, 400);
}
// this function erases bullets
static void erase_enemy_bullet(int box_x, int box_y) {
	myLine(box_x, box_y - 15, box_x, box_y, 0, 0, 0);
	myLine(box_x + 2, box_y - 15, box_x + 2, box_y, 0, 0, 00);
}
//this structure stores the data of the enemies
struct enemies {
	int position_x;
	int position_y;
	bool status;
};
//this function stores the data the uptodated data of an enemy
void enemy_initialization(int allien_x, int allien_y, int tempx, int tempy, int enemynumber, enemies enemy[]) {
	for (int k = 0; k < 5; k++) {
		allien_x = tempx;
		for (int j = 0; j < 10; j++) {
			enemy[enemynumber].position_x = allien_x;
			enemy[enemynumber].position_y = allien_y;
			allien_x = allien_x + 40;
			enemynumber++;
		}
		allien_y = allien_y + 40;
	}
}
//this functions gives enemies alive status
void enemy_status(enemies enemy[]) {

	for (int i = 0; i < 50; i++) {
		enemy[i].status = true;
	}
}
//this function prints all the alive enemies
void print_enemies(enemies enemy[]) {

	for (int i = 0; i < 50; i++) {
		if (enemy[i].status == true) {
			drawallien(enemy[i].position_x, enemy[i].position_y);
		}
	}

}
//this function removes all the enemies
void remove_enemies(enemies enemy[]) {
	int x_cordinate;
	int y_cordinate;
	for (int i = 0; i < 50; i++) {
		if (enemy[i].status == true) {
			removeallien(enemy[i].position_x, enemy[i].position_y);
		}
	}
}
//main body
int main()
{
	//main menu design
	myEllipse(200, 60, 730, 360, 0, 255, 10);
	drawText(20, 420, 75, 00, 255, 0, "MENU");
	drawText(20, 320, 135, 140, 55, 140, "RESTART");
	drawText(20, 490, 135, 250, 255, 140, "press 1");
	drawText(20, 320, 205, 250, 5, 1400, "CONTINUE");
	drawText(20, 490, 205, 250, 255, 140, "press 2");
	drawText(20, 340, 275, 10, 55, 140, "QUIT");
	drawText(15, 480, 275, 250, 255, 140, "press Others");
	//this part contains data of limits and spaceship initial coordiates
	int left_limit = 20, right_limit = 730, top_limit = 60, bottom_limit = 360;
	int box_x = 400, box_y = 340, step_size = 5;
	char direction = ' ';
	//enemy data is here
	int allien_x = 20, allien_y = 70;
	int tempx = allien_x, tempy = allien_y;
	enemies enemy[50];
	int enemynumber = 0;
	int lowest_enemy_y = 0;
	int alive_enimies_count = 50;
	//bullet data is here
	int bulletx = 1, bullet_y = 1;
	bool  bullet_status = false;
	int bullet_key;
	int bullet_count = 0;
	int fired_bullet_count = 0;
	int check_x;
	bool alive_bullet = false;
	//allien bullet data is here
	bool enemy_bullet_status = false;
	int enemy_bullet_x = 0;
	int enemy_bullet_y = 0;
	int alive_enemy_check = 0;
	int temp_var = 0;
	//general intilized data is here
	int player_lives = 3;
	int iteration = 0;
	int score = 0;
	int movement_count;
	bool wallcollision = false;
	movement_count = 1;
	int pause_choice = 1;
	int start_choice;
	int general_count = 0;
	int level_speed;
	cin >> start_choice;
	//high scores file data is here
	ofstream score_out("TopScores.txt", ios::cur);
	ifstream score_in("TopScores.txt");
	int score_array[5];
	int score_reading;
	int first_high;
	int second_high;
	int third_high;
	int fourth_high;
	int fifth_high;
	//continue file data is here
	int read_integer;
	bool read_bool;
	ofstream continue_out1("Continue1.txt", ios::cur);
	ifstream continue_in1("Continue1.txt");
	//high scores is being read from the file
	int r = 0;
	while (r < 5 && score_in >> score_reading) {
		//score_in >> score_reading;
		score_array[r] = score_reading;
		r++;
	}
	//high scores from array is being stored to respective level of score
	first_high = score_array[0];
	second_high = score_array[1];
	third_high = score_array[2];
	fourth_high = score_array[3];
	fifth_high = score_array[4];
	if (start_choice == 1 || start_choice == 2) {
		Beep(750, 700);
		//game level design
		int level_choice;

		if (start_choice == 1) {
			
			//menu of game levels is printed here
			myRect(200, 60, 730, 360, 100, 50, 100);
			drawText(30, 380, 75, 140, 55, 140, "LEVELS");
			drawText(20, 340, 175, 140, 55, 140, "MEDIUM");
			drawText(20, 470, 175, 250, 255, 140, "press 1");
			drawText(20, 340, 275, 140, 55, 140, "HARD");
			drawText(20, 450, 275, 250, 255, 140, "press 2");
			drawText(15, 310, 325, 10, 255, 140, "To leave press others");
			//this part takes the choice of level from the user then allots speed and iteration number
			do {
				cin >> level_choice;
				Beep(750, 700);
				if (level_choice == 1 || level_choice == 2) {
					break;
				}
			} while (level_choice);
			//level speed and iteration number is decided here 
			if (level_choice == 1) {
				level_speed = 10;
				iteration = 10;
			}
			else if (level_choice == 2) {
				level_speed = 1;
				iteration = 7;
			}
		}
		
		//drawText(20, 10, 10, 140, 55, 140, "WELCOME TO THE GAME"); // drawText function draws text on the screen with arguments size, x, y, r, g, b, text
		myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 10, 55, 140); // myRect function draws a rectangle with arguments x1, y1, x2, y2, r, g, b, r2, g2, b2
		drawText(20, 10, 365, 0, 255, 0, "Use Cursor keys to move the box!");
		enemy_status(enemy);
		enemy_initialization(allien_x, allien_y, tempx, tempy, enemynumber, enemy);

		//game box and high score box is being printed here
		myRect(right_limit + 5, top_limit - 2, right_limit + 200, bottom_limit - 2, 10, 55, 140);
		myRect(right_limit + 10, top_limit + 3, right_limit + 195, top_limit + 55, 10, 55, 140);
		drawText(18, right_limit + 10, top_limit + 10, 0, 255, 0, "TOP SCORES");
		//this part prints all the top 5 high scores
		drawText(18, right_limit + 70, top_limit + 60, 0, 255, 0, "", true, first_high);
		drawText(18, right_limit + 70, top_limit + 110, 0, 255, 0, "", true, second_high);
		drawText(18, right_limit + 70, top_limit + 160, 0, 255, 0, "", true, third_high);
		drawText(18, right_limit + 70, top_limit + 210, 0, 255, 0, "", true, fourth_high);
		drawText(18, right_limit + 70, top_limit + 260, 0, 255, 0, "", true, fifth_high);
		if (start_choice == 2) {
			//x then y cordinateds of every allien is being read from file
			int p = 0;
			while (p < 50) {
				continue_in1 >> read_integer;
				enemy[p].position_x = read_integer;
				continue_in1 >> read_integer;
				enemy[p].position_y = read_integer;
				p++;
			}
			//first all integers are getting read one by one
			continue_in1 >> read_integer;
			allien_x = read_integer;

			continue_in1 >> read_integer;
			allien_y = read_integer;

			continue_in1 >> read_integer;
			box_x = read_integer;

			continue_in1 >> read_integer;
			box_y = read_integer;

			continue_in1 >> read_integer;
			score = read_integer;

			continue_in1 >> read_integer;
			player_lives = read_integer;

			continue_in1 >> read_integer;
			level_speed = read_integer;

			continue_in1 >> read_integer;
			iteration = read_integer;

			continue_in1 >> read_integer;
			bullet_count = read_integer;

			continue_in1 >> read_integer;
			bulletx = read_integer;

			continue_in1 >> read_integer;
			bullet_y = read_integer;

			continue_in1 >> read_integer;
			general_count = read_integer;

			continue_in1 >> read_integer;
			enemy_bullet_x = read_integer;

			continue_in1 >> read_integer;
			enemy_bullet_y = read_integer;

			continue_in1 >> read_integer;
			alive_enimies_count = read_integer;

			continue_in1 >> read_integer;
			lowest_enemy_y = read_integer;

			continue_in1 >> read_integer;
			movement_count = read_integer;

			continue_in1 >> read_integer;
			fired_bullet_count = read_integer;
			//here alive status of every allien is being read
			p = 0;
			while (p < 50) {
				continue_in1 >> read_bool;
				enemy[p].status = read_bool;
				p++;
			}
			//all the booleans are being read one by one
			continue_in1 >> read_bool;
			alive_bullet = read_bool;

			continue_in1 >> read_bool;
			bullet_status = read_bool;

			continue_in1 >> read_bool;
			enemy_bullet_status = read_bool;
		}
		//at the start of the game;allien grid is printed
		print_enemies(enemy);
		remove_enemies(enemy);
		drawBox(box_x, box_y);
		//first time lives are printed
		myRect(right_limit - 50, top_limit - 55, right_limit + 2, top_limit - 5, 10, 55, 140);
		drawText(22, right_limit - 45, 10, 250, 5, 1400, "", true, player_lives);
		drawText(17, right_limit - 260, 10, 250, 5, 1400, "PLAYER LIVES");
        //here the score at the start of game is printed
		drawText(20, 10, 10, 140, 55, 140, "SCORE");
		myRect(left_limit + 100, top_limit - 55, left_limit + 180, top_limit - 5, 10, 55, 140);
		drawText(22, left_limit + 102, 8, 0, 255, 0, "", true, score);
		//outerloop
		while (pause_choice != 0) {
			//inner loop
			int whichKey = 0;
			while (whichKey != 7) // 7 is the code for ESC key
			{
				if (isKeyPressed(whichKey)) // isKeyPressed function returns true if a key is pressed and whichKey tells that which key was pressed
				{
					switch (whichKey)
					{
					case 1:
						direction = 'L';
						break;
					case 2:
						direction = 'U';
						break;
					case 3:
						direction = 'R';
						break;
					case 4:
						direction = 'D';
						break;
					case 6:
						//if shift is pressed but there is already a bullet alive ,it will not produce a bullet
						if (alive_bullet == false) {
							bullet_status = true;
							bullet_count = 1;
							alive_bullet = true;
						}

						break;
					}
				}
				Sleep(level_speed); // 25 milliseconds
				//when general count becomes equal to iteration number ;this part of the code will work
				if (general_count == iteration) {
					//if enemy bullet status is false this part will work
					if (enemy_bullet_status == false) {
						srand(time(0));
						temp_var = rand() % 50;
						//a random number from 0 to 49 will be produced
						//at that number status of enemy is checked;if true that enemy's x and y position will be alloted to the bullet
						if (enemy[temp_var].status == true) {
							enemy_bullet_status = true;
							enemy_bullet_x = enemy[temp_var].position_x;
							enemy_bullet_y = enemy[temp_var].position_y + 10;
						}
						else {
							srand(time(0));
							temp_var = rand() % 50;
							if (enemy[temp_var].status == true) {
								enemy_bullet_status = true;
								enemy_bullet_x = enemy[temp_var].position_x;
								enemy_bullet_y = enemy[temp_var].position_y + 10;
							}
							else {
								srand(time(0));
								temp_var = rand() % 50;
								if (enemy[temp_var].status == true) {
									enemy_bullet_status = true;
									enemy_bullet_x = enemy[temp_var].position_x;
									enemy_bullet_y = enemy[temp_var].position_y + 10;
								}
							}
						}
					}
				}
		//this part removes old bullet;give it new position then prints it
				if (enemy_bullet_status == true) {
					//this part check if bullet collided with the bottom line
					if (enemy_bullet_y + 5 > bottom_limit) {
						erase_enemy_bullet(enemy_bullet_x, enemy_bullet_y);
						enemy_bullet_status = false;
						enemy_bullet_x = 0;
						enemy_bullet_y = 0;
					}
					else {
						erase_enemy_bullet(enemy_bullet_x, enemy_bullet_y);
						enemy_bullet_y += 4;
						make_enemy_bullet(enemy_bullet_x, enemy_bullet_y);
					}

				}
				//this part checks it the enemy bullet collided with spaceship
				if (enemy_bullet_status == true) {
					if (enemy_bullet_y + 5 >= box_y) {
						for (int a = box_x- 10; a <= box_x + 10; a++) {
							if (a == enemy_bullet_x) {
								//if all coordinates of the enemy bullet matched the cordinates of the spaceship
								   //player lives will be made one less
								      //and spaceship will return to default location
								player_lives--;
								erase_enemy_bullet(enemy_bullet_x, enemy_bullet_y);
								enemy_bullet_status = false;
								removeBox(box_x, box_y);
								direction = 'D';
								box_x = 400, box_y = 340;
								myRect(right_limit - 50, top_limit - 55, right_limit + 2, top_limit - 5, 10, 55, 140);
								drawText(22, right_limit - 45, 10, 250, 5, 1400, "", true, player_lives);
								break;
							}
							else
								continue;
						}
					}
				}
				//this part checks if the spaceship collided with any of the alliens
				for (int i = 49; i >= 0; i--) {
					if (enemy[i].status == true) {
						if (box_y - 15 <= enemy[i].position_y) {
							for (int a = box_x - 15; a < box_x + 15; a++) {
								if (a== enemy[i].position_x) {
									removeBox(box_x, box_y);
									player_lives--;
									box_x = 400, box_y = 340;
									direction = 'D';
									myRect(right_limit - 50, top_limit - 55, right_limit + 2, top_limit - 5, 15, 55, 140);
									drawText(22, right_limit - 45, 10, 250, 5, 1400, "", true, player_lives);
									break;
								}
							}
						}
					}
					else
						continue;
				}

				if (bullet_count == 1) {
					fired_bullet_count++;
					if (bullet_status == true) {
						bulletx = box_x + 10;
						bullet_y = box_y - 5;
						make_bullet(bulletx, bullet_y);
					}
					bullet_count++;
				}

				if (bullet_status == true) {
					erase_bullet(bulletx, bullet_y);
					bullet_y -= 5;
					make_bullet(bulletx, bullet_y);
					if (bullet_y - 15 <= top_limit) {
						bullet_status = false;
						alive_bullet = false;
						erase_bullet(bulletx, bullet_y);
					}
					for (int i = 0; i < 50; i++) {
						check_x = bulletx - 20;
						if (enemy[i].position_y + 20 == bullet_y) {
							for (int j = 0; j <= 40; j++, check_x++) {
								if (enemy[i].position_x == check_x) {
									if (enemy[i].status == true) {
										bullet_status = false;
										alive_bullet = false;
										erase_bullet(bulletx, bullet_y);
										removeallien(enemy[i].position_x, enemy[i].position_y);
										Beep(2000, 50);
										enemy[i].status = false;
										alive_enimies_count--;
										if (fired_bullet_count <= 10) {
											score += 10;
										}
										else if (fired_bullet_count <= 18 && fired_bullet_count > 10) {
											score += 7;
										}
										else if (fired_bullet_count <= 26 && fired_bullet_count > 18) {
											score += 5;
										}
										else if (fired_bullet_count <= 40 && fired_bullet_count > 26) {
											score += 3;
										}
										else {
											score += 2;
										}
										drawText(20, 10, 10, 140, 55, 140, "SCORE");
										myRect(left_limit + 100, top_limit - 55, left_limit + 180, top_limit - 5, 10, 55, 140);
										drawText(22, left_limit + 102, 8, 0, 255, 0, "", true, score);
									}
								}
								if (bullet_status == false) {
									break;
								}
							}
						}
					}
				}


				if (general_count == iteration) {
					if (movement_count == 1) {
						if (allien_x + 400 < right_limit) {
							remove_enemies(enemy);
							if (wallcollision == true) {
								wallcollision = false;
								allien_y += 10;
							}
							allien_x += 10;
							tempx = allien_x;
							tempy = allien_y;
							enemy_initialization(allien_x, allien_y, tempx, tempy, enemynumber, enemy);
							for (int h = 0; h < 50; h++) {
								if (enemy[h].status == true) {
									lowest_enemy_y = enemy[h].position_y;
								}
								else
									lowest_enemy_y = lowest_enemy_y;
							}
							if (lowest_enemy_y + 10 >= bottom_limit) {
								pause_choice = 3;
								whichKey = 7;
								break;
							}
							print_enemies(enemy);

							general_count = 0;


						}
						else {
							movement_count = 2;
							if (movement_count == 2) {
								wallcollision = true;
							}
						}
					}
					if (movement_count == 2) {
						if (allien_x - 5 > left_limit) {
							remove_enemies(enemy);
							if (wallcollision == true) {
								wallcollision = false;
								allien_y += 10;
							}
							allien_x -= 10;
							tempx = allien_x;
							tempy = allien_y;
							enemy_initialization(allien_x, allien_y, tempx, tempy, enemynumber, enemy);
							for (int h = 0; h < 50; h++) {
								if (enemy[h].status == true) {
									lowest_enemy_y = enemy[h].position_y;
								}
								else
									continue;
							}
							if (lowest_enemy_y + 10 >= bottom_limit) {
								pause_choice = 3;
								whichKey = 7;
								break;
							}
							print_enemies(enemy);
							general_count = 0;

						}
						if (allien_x - 5 < left_limit) {
							movement_count = 1;
							if (movement_count == 1) {
								wallcollision = true;
							}
						}
					}
				}


				if (player_lives == 0) {
					pause_choice = 3;
					whichKey = 7;
				}
				if (alive_enimies_count == 0) {
					pause_choice = 4;
					whichKey = 7;
					break;

				}

				switch (direction)
				{

				case 'L':
					// Left

					removeBox(box_x, box_y);
					if (box_x - 10 > left_limit)
						box_x -= step_size;

					drawBox(box_x, box_y);

					break;
				case 'U':
					// Up
					removeBox(box_x, box_y);
					if (box_y - 10 > top_limit)
						box_y -= step_size;
					drawBox(box_x, box_y);
					break;
				case 'R':
					// Right

					removeBox(box_x, box_y);
					if (box_x + 50 < right_limit)
						box_x += step_size;
					drawBox(box_x, box_y);
					break;
				case 'D':
					// Down
					removeBox(box_x, box_y);
					if (box_y + 20 < bottom_limit)
						box_y += step_size;
					drawBox(box_x, box_y);
					break;
				}
				general_count++;
			}
			myRect(15, 362, 900, 460, 500, 150, 1050);
			drawText(15, 350, 370, 140, 55, 140, "GAME IS PAUSED");
			drawText(20, 100, 410, 140, 55, 140, "1 TO CONTINUE");
			drawText(20, 500, 410, 140, 55, 140, "0 TO SAVE AND EXIT");
			if (pause_choice == 4) {
				break;
			}
			if (pause_choice == 3) {
				break;
			}
			cin >> pause_choice;
			if (pause_choice == 0)
				break;
			else {
				myRect(15, 362, 900, 460, 0, 00, 0);
				drawText(20, 10, 365, 0, 255, 0, "Use Cursor keys to move the box!");
				//drawText(20, 10, 10, 140, 55, 140, "WELCOME TO THE GAME");
			}
		}
		if (pause_choice == 4) {
			myRect(10, 5, 950, 475, 255, 0, 0);
			myRect(50, 130, 860, 400, 200, 100, 255);
			drawText(20, 250, 200, 150, 40, 40, "YOU KILLED ALL ENEMIES");
			drawText(20, 350, 250, 150, 40, 40, "YOUR SCORE");
			drawText(20, 400, 300, 150, 40, 40, "", true, score);
		}
		else if (pause_choice == 3) {
			myRect(10, 5, 950, 475, 255, 0, 0);
			myRect(50, 130, 860, 400, 200, 100, 255);
			drawText(20, 250, 200, 150, 40, 40, "ENEMIES WON; YOU LOST");

		}
		else if (pause_choice != 4) {
			myRect(10, 5, 950, 475, 255, 0, 0);
			myRect(50, 130, 860, 400, 200, 100, 255);
			drawText(20, 250, 200, 150, 40, 40, "YOU EXITED THE GAME!");
			int p = 0;
			while (p < 50) {
				continue_out1 << enemy[p].position_x << endl;
				continue_out1 << enemy[p].position_y << endl;
				p++;
			}
			continue_out1 << allien_x << endl;
			continue_out1 << allien_y << endl;
			continue_out1 << box_x << endl;
			continue_out1 << box_y << endl;
			continue_out1 << score << endl;
			continue_out1 << player_lives << endl;
			continue_out1 << level_speed << endl;
			continue_out1 << iteration << endl;
			continue_out1 << bullet_count << endl;
			continue_out1 << bulletx << endl;
			continue_out1 << bullet_y << endl;
			continue_out1 << general_count << endl;
			continue_out1 << enemy_bullet_x << endl;
			continue_out1 << enemy_bullet_y << endl;
			continue_out1 << alive_enimies_count << endl;
			continue_out1 << lowest_enemy_y << endl;
			continue_out1 << movement_count << endl;
			continue_out1 << fired_bullet_count << endl;

			p = 0;
			while (p < 50) {
				continue_out1 << enemy[p].status << endl;
				p++;
			}
			continue_out1 << alive_bullet << endl;
			continue_out1 << bullet_status << endl;
			continue_out1 << enemy_bullet_status << endl;

			continue_out1.close();
		}
		{
			if (score > first_high) {
				fifth_high = fourth_high;
				fourth_high = third_high;
				third_high = second_high;
				second_high = first_high;
				first_high = score;
			}
			else if (score > second_high) {
				fifth_high = fourth_high;
				fourth_high = third_high;
				third_high = second_high;
				second_high = score;
			}
			else if (score > third_high) {
				fifth_high = fourth_high;
				fourth_high = third_high;
				third_high = score;
			}
			else if (score > fourth_high) {
				fifth_high = fourth_high;
				fourth_high = score;
			}
			else if (score > fifth_high) {
				fifth_high = score;

			}
			score_array[0] = first_high;
			score_array[1] = second_high;
			score_array[2] = third_high;
			score_array[3] = fourth_high;
			score_array[4] = fifth_high;
			int r = 0;
			while (r < 5) {
				score_reading = score_array[r];
				score_out << score_reading << endl;
				r++;
			}
			score_out.close();
		}
	}
	
	return 0;
}