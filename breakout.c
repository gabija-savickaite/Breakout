/* Code adapted by Gabija Savickaite from:
 *
 * Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 * 
 * Also used some functions and taken inspiration from Space Invaders by Giacomo Meanti.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "rotary.h"
#include "led.h"
#include "image.h"


#define BALL_SIZE	4
#define BAT_WIDTH	50
#define BAT_HEIGHT	2
#define BAT_INC		10

// height and width of game's window in pixels
#define HEIGHT 320
#define WIDTH 240
 
// height and width of the paddle in pixels
#define PHEIGHT 10
#define PWIDTH 60
 
// number of rows of bricks
int rows = 5;
 
// number of columns of bricks
int cols = 10;
 
// radius of ball in pixels
#define RADIUS 10
 
// lives
#define LIVES 3

brick** bricks;
int num_bricks;
int level = 1;

const rectangle start_bat = {(LCDWIDTH-BAT_WIDTH)/2, (LCDWIDTH+BAT_WIDTH)/2, LCDHEIGHT-BAT_HEIGHT-1, LCDHEIGHT-1};
const rectangle start_ball = {(LCDWIDTH-BALL_SIZE)/2, (LCDWIDTH+BALL_SIZE)/2, LCDHEIGHT-BAT_HEIGHT-BALL_SIZE-1, LCDHEIGHT-BAT_HEIGHT-1};

volatile rectangle bat, ball, last_bat, last_ball;
volatile uint16_t score;
volatile uint8_t lives;
volatile uint8_t fps = 0;

static int8_t xinc = 1, yinc = 1;

int center_down = 0;
int left_down = 0;
int right_down = 0;
int up_down = 0;
int down_down = 0;
int down = 0;

ISR(INT6_vect)
{
	fill_rectangle(last_ball, display.background);
	fill_rectangle(ball, display.foreground);
	fill_rectangle(last_bat, display.background);
	fill_rectangle(bat, display.foreground);
	last_ball = ball;
	last_bat = bat;
	char buffer1[4];
	char buffer2[10];
	sprintf(buffer1, "%03d", score);
	sprintf(buffer2, "Level %d", level);
	display_string_xy(buffer1, 200, 20);
	display_string_xy(buffer2, 20, 20);
	draw_hearts();
	fps++;
}

ISR(TIMER1_COMPA_vect)
{
	_delay_ms(6/level);
	ball.left   += xinc;
	ball.right  += xinc;
	ball.top    += yinc;
	ball.bottom += yinc;
	if (ball.right >= display.width-1 || ball.left <= 0)
		xinc = -xinc;
	if (ball.top <= 0)
		yinc = -yinc;
	if (ball.bottom == display.height-1 && ball.left <= bat.right && ball.right >= bat.left) {
		yinc = -yinc;
	}
	if (rotary<0 && bat.left >= BAT_INC) {
		bat.left  -= BAT_INC;
		bat.right -= BAT_INC;
	}
	if (rotary>0 && bat.right < display.width-BAT_INC) {
		bat.left  += BAT_INC;
		bat.right += BAT_INC;
	}
	rotary = 0;
	if (ball.bottom > display.height) {
		lives--;
		draw_hearts();
		led_brightness(0x03 << (lives << 1));
		ball = start_ball;
		bat = start_bat;
	}
	detect_collision();
	if (!num_bricks)
	{
		level_up();
		ball = start_ball;
		bat = start_bat;
	}
}

ISR(TIMER3_COMPA_vect) {}

void init_bricks()
{
	free(bricks); 
	int i,j;

	bricks = (brick **)malloc(sizeof(brick *) * cols);
    for (i=0; i<cols; i++)
         bricks[i] = (brick *)malloc(rows * sizeof(brick));

    srand(TCNT2);
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
			brick brick;
			brick.rectangle.left = 2 + j * WIDTH / cols;
			brick.rectangle.top = 45 + i * 15;
			brick.rectangle.right = 2 + j * WIDTH / cols + WIDTH / cols - 5;
			brick.rectangle.bottom = 45 + i * 15 + 10;
			brick.broken = 0;
			bricks[j][i] = brick;
			int colour = colours[rand() % 1301];
            fill_rectangle(brick.rectangle, colour);
        }
    }
}

void detect_collision() {
	int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
			if (!bricks[j][i].broken)
			{
				rectangle brick_rectangle = bricks[j][i].rectangle;
				if (ball.right >= brick_rectangle.left && ball.left <= brick_rectangle.right && (ball.top == brick_rectangle.bottom || ball.bottom == brick_rectangle.top))
				{
					fill_rectangle(brick_rectangle, BLACK);
					yinc = -yinc;
					bricks[j][i].broken = 1;
					score++;
					num_bricks--;
				}
				else if (ball.bottom >= brick_rectangle.top && ball.top <= brick_rectangle.bottom && (ball.right == brick_rectangle.right || ball.left == brick_rectangle.left))
				{
					fill_rectangle(brick_rectangle, BLACK);
					xinc = -xinc;
					bricks[j][i].broken = 1;
					score++;
					num_bricks--;
				}
			}
        }
    }
}

void level_up()
{
	level++;
	rows++;
	cols++;
	num_bricks = rows*cols;
	init_bricks();
}

int center_pressed(){
	if ((~PINE & _BV(PE7)) && !center_down && !down) {
		center_down = 1;
		down = 1;
		return 1;
	} else if ((PINE & _BV(PE7)) && center_down){
		center_down = 0;
		down = 0;
	}
	return 0;
}

void draw_hearts(void) {

    fill_rectangle_c(WIDTH/2 - 12 - 11/2, 20, 10, 9, display.background);
	if (lives)
	{
		fill_image_pgm(WIDTH/2 - 12 - 11/2, 20, 10, 9, heart_sprite);
	}
	else
	{
    	fill_image_pgm(WIDTH/2 - 12 - 11/2, 20, 10, 9, empty_heart_sprite);
	}

    fill_rectangle_c(WIDTH/2 - 11/2, 20, 10, 9, display.background);
	if (lives > 1)
	{
    	fill_image_pgm(WIDTH/2 - 11/2, 20, 10, 9, heart_sprite);
	}
	else
	{
		fill_image_pgm(WIDTH/2 - 11/2, 20, 10, 9, empty_heart_sprite);
	}

    fill_rectangle_c(WIDTH/2+1 + 11/2, 20, 10, 9, display.background);
	if (lives > 2)
	{
		fill_image_pgm(WIDTH/2+1 + 11/2, 20, 10, 9, heart_sprite);
	}
	else
	{
		fill_image_pgm(WIDTH/2+1 + 11/2, 20, 10, 9, empty_heart_sprite);
	}
}

int main()
{
	/* Clear DIV8 to get 8MHz clock */
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;
	init_rotary();
	init_led();
	init_lcd();
	set_frame_rate_hz(61); /* > 60 Hz  (KPZ 30.01.2015) */
	/* Enable tearing interrupt to get flicker free display */
	EIMSK |= _BV(INT6);
	/* Enable rotary interrupt to respond to input */
	EIMSK |= _BV(INT4) | _BV(INT5);
	/* Enable game timer interrupt (Timer 1 CTC Mode 4) */
	TCCR1A = 0;
	TCCR1B = _BV(WGM12);
	TCCR1B |= _BV(CS10);
	TIMSK1 |= _BV(OCIE1A);
	/* Enable performance counter (Timer 3 CTC Mode 4) */
	TCCR3A = 0;
	TCCR3B = _BV(WGM32);
	TCCR3B |= _BV(CS32);
	TIMSK3 |= _BV(OCIE3A);
	OCR3A = 31250;
	srand(TCNT2);
	while(!center_pressed())
	{
		display.foreground = colours[rand() % 1301];

		display_string_xy("  ___.                         __    \n", 0, 25);
		display_string("  \\_ |_________   ____ _____  |  | __\n");
		display_string("   | __ \\_  __ \\_/ __ \\\\__  \\ |  |/ /\n");
		display_string("   | \\_\\ \\  | \\/\\  ___/ / __ \\|    < \n");
		display_string("   |___  /__|    \\___  >____  /__|_ \\\n");
		display_string("       \\/            \\/     \\/     \\/\n\n");
		display_string("                         __ \n");
		display_string("            ____  __ ___/  |_ \n");
		display_string("           /  _ \\|  |  \\   __\\  \n");
		display_string("          (  <_> )  |  /|  |\n");
		display_string("           \\____/|____/ |__|");

		display_string_xy("\n         Press Center to Start", 100, 285);
	}
	num_bricks = rows*cols;
	/* Play the game */
	do {
		level = 1;
		clear_screen();
		init_bricks();
		last_bat = bat = start_bat;
		last_ball = ball = start_ball;
		lives = 3;
		score = 0;
		OCR1A = 65535;
		led_on();
		sei();
		while(lives);
		cli();
		led_off();
		while(!center_pressed())
		{
			display.foreground = colours[rand() % 1301];
			display_string_xy("            Game Over.", 20, 200);
			display_string_xy("\n        Press Center to Restart", 100, 285);
		}
	} while(1);
}
