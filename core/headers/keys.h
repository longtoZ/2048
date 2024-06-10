#pragma once

// Char size
#define USERNAME_SIZE 17
#define PASSWORD_SIZE 33
#define DATE_SIZE 16
#define INTERVAL_SIZE 6
#define INT_SIZE 5

// ANSI code for text color
#define YELLOW_TEXT "\x1b[38;5;11m"
#define GREEN_TEXT "\x1b[38;5;10m"
#define RED_TEXT "\x1b[38;5;9m"
#define WHITE_TEXT "\x1b[38;5;255m"
#define BLACK_TEXT "\x1b[38;5;0m"
#define DISABLE_TEXT "\x1b[38;5;231m"

// ANSCI code for background color
#define RESET_BACKGROUND_COLOR "\x1b[49m"
#define BOARD_BACKGROUND_COLOR "\x1b[48;5;137m"
#define EMPTY_POS_COLOR "\x1b[48;5;180m"
#define MENU_BACKGROUND_COLOR "\x1b[48;5;252m"
#define CELL_BACKGROUND_COLOR "\x1b[48;5;254m"
#define TWO_BACKGROUND_COLOR "\x1b[48;5;15m"
#define FOUR_BACKGROUND_COLOR "\x1b[48;5;222m"
#define EIGTH_BACKGROUND_COLOR "\x1b[48;5;215m"
#define SIXTEEN_BACKGROUND_COLOR "\x1b[48;5;208m"
#define THIRTY_TWO_BACKGROUND_COLOR "\x1b[48;5;203m"
#define SIXTY_FOUR_BACKGROUND_COLOR "\x1b[48;5;160m"
#define ONE_TWENTY_EIGTH_BACKGROUND_COLOR "\x1b[48;5;166m"
#define TWO_FIFTY_SIX_BACKGROUND_COLOR "\x1b[48;5;167m"
#define FIVE_TWELVE_BACKGROUND_COLOR "\x1b[48;5;178m"
#define TEN_TWENTY_FOUR_COLOR "\x1b[48;5;202m"
#define TWENTY_FORTY_EIGHT_COLOR "\x1b[48;5;9m"
#define FORTY_NINETY_SIX_COLOR "\x1b[48;5;196m"
#define WHITE_BACKGROUND_COLOR "\x1b[48;5;255m"

// ANSI code for text format
#define RESET_FORMAT "\033[0m"
#define BOLD_TEXT "\033[1m"
#define UNDERLINE_TEXT "\033[4m"

// Keyboard button
#define KEYUP 72
#define KEYDOWN 80
#define KEYLEFT 75
#define KEYRIGHT 77
#define ENTER 13
#define N_KEY 110
#define R 114
#define S 115
#define U 117
#define X_key 120
#define Y_key 121
#define ONE 49
#define TWO 50
#define THREE 51
#define FOUR 52
#define FIVE 53
#define SIX 54

// File path
#define FILE_PATH "./database/"
#define USER_FILE_PATH "./database/user.bin"

// Spacing
#define TAB_WIDTH_2 "\t\t"
#define TAB_WIDTH_1 "\t"