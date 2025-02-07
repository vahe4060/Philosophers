#ifndef CONSTANTS_H
#define CONSTANTS_H

#define USAGE "Usage:\n\
\t./philosophers [NUM_PHILOS] [TIME_TO_DIE] [TIME_TO_EAT]\
[TIME_TO_SLEEP] [[NUM_MEALS]]\n\
NUM_PHILOS\t- number of philosophers\n\
TIME_TO_DIE\t- maximum time each philosopher can spend hungry/thinking (ms)\n\
TIME_TO_EAT\t- time each philosopher spends eating (ms)\n\
TIME_TO_SLEEP\t- time each philosopher spends sleeping (ms)\n\
[NUM_MEALS]\t- optional, number of meals for each philosopher.\n"
#define MALLOC_ERROR "Memory Error\n"

typedef enum s_status {
	eating = 0,
	sleeping,
	thinking,
	dead,
	finished
} t_status;

static const char status_str[5][10] = {
	"eating   ",
	"sleeping ",
	"thinking ",
	"dead     ",
	"finished "
};

static const char color[6][10] = {
	"\033[0;32m", // green // eating status
	"\033[0;34m", // blue // sleeping status
	"\033[0;33m", // yellow // thinking status
	"\033[0;31m", // red // dead status
	"\033[0;35m", // magenta // finished status
	"\033[0m" // reset
};

#endif