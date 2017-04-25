#include <stdio.h>
#include <stdlib.h>

// game field size
#define size_x 50
#define size_y 25

// character start position
#define start_x 10
#define start_y 10

// character speed
#define speed 1

// controls
#define up 119 //arrows
#define down 115
#define left 97
#define right 100
#define back 27 //esc

// theming
#define character_glyph '&'
#define background_glyph ' '

#define border 1


int check_boundaries (int pos_x, int pos_y) {
	if ((pos_x >= 0 && pos_x < size_x) &&
		(pos_y >= 0 && pos_y < size_y)) {
		return 1;
	} else {
		return 0;
	}
}

char** get_game_field () {
	char** mem = (char**) malloc(size_y * sizeof(char*));
	int i, j;
	for (i = 0; i < size_y; i++) {
		mem[i] = (char*) malloc(size_x * sizeof(char));
	}

	for (i = 0; i < size_y; i++) {
		for (j = 0; j < size_x; j++) {
			mem[i][j] = background_glyph;
		}
	}

	return mem;
}

void draw_field(char** field) {
	int i, j;

	system("cls");

	if (border) {
		//draw the top border
		printf("%c", 201);
		for (i = 0; i < size_x; i++) {
			printf("%c", 205);
		}
		printf("%c", 187);
		printf("\n");

		for (i = 0; i < size_y; i++) {
			// draw the left border
			printf("%c", 186);

			for (j = 0; j < size_x; j++) {
				// draw the field line itself
				printf("%c", field[i][j]);
			}

			// draw the right border
			printf("%c", 186);

			printf("\n");
		}

		// draw the bottom border
		printf("%c", 200);
		for (i = 0; i < size_x; i++) {
			printf("%c", 205);
		}
		printf("%c", 188);
		printf("\n");
		
	} else {

		for (i = 0; i < size_y; i++) {
			for (j = 0; j < size_x; j++) {
				printf("%c", field[i][j]);
			}
			printf("\n");
		}
	}
}

int main () {
	// create game field
	char** field = get_game_field();

	int i, j;

	// create character
	int pos_x = start_x;
	int pos_y = start_y;
	field[pos_y][pos_x] = character_glyph;

	while (1) {
		draw_field(field);

		int key = getch();

		// fill the old character position with background glyph
		field[pos_y][pos_x] = background_glyph;

		// change character position
		switch(key) {
			case up:
				if (check_boundaries(pos_x, pos_y - speed)) {
					pos_y -= speed;
				}
				break;

			case down:
				if (check_boundaries(pos_x, pos_y + speed)) {
					pos_y += speed;
				}
				break;

			case left:
				if (check_boundaries(pos_x - speed, pos_y)) {
					pos_x -= speed;
				}
				break;

			case right:
				if (check_boundaries(pos_x + speed, pos_y)) {
					pos_x += speed;
				}
				break;

			// exit game
			case back:
				return 0;
		}

		// move character
		field[pos_y][pos_x] = character_glyph;
	}
}
