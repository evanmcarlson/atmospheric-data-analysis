/**
 * Evan Carlson
 *
 * climate.c
 *
 * Performs analysis on climate data provided by the
 * National Oceanic and Atmospheric Administration (NOAA).
 *
 * Input:    Tab-delimited file(s) to analyze.
 * Output:   Summary information about the data.
 *
 * Compile:  run make
 *
 * Example Run:      ./climate data_tn.tdv data_wa.tdv
 *
 */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_STATES 50

/* TODO: Add elements to the climate_info struct as necessary. */
typedef struct climate_info {
    char code[3];
    unsigned long num_records;
    double sum_temperature;
    double sum_humidity;
    double max_temp;
    double min_temp;
    unsigned long max_date;
    unsigned long min_date;
    int lightning;
    int snow;
    long double sum_cloudcover;
}state;

void analyze_file(FILE *file, struct climate_info *states[], int num_states);
void print_report(struct climate_info *states[], int num_states);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s tdv_file1\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Let's create an array to store our state data in. As we know, there are
     * 50 US states. */
    struct climate_info *states[NUM_STATES] = { NULL };

    int i;
    for (i = 1; i < argc; ++i) {
        /* TODO: Open the file for reading */
	FILE *file;
	file = fopen(argv[1], "r");

        /* TODO: If the file doesn't exist, print an error message and move on
         * to the next file. */
	if(file == NULL) {
		printf("File does not exist.\n");
	}
	else {
		analyze_file(file, states, NUM_STATES);
	}

        /* TODO: Analyze the file */
    }

    /* Now that we have recorded data for each file, we'll summarize them: */
    print_report(states, NUM_STATES);

    return 0;
}

void analyze_file(FILE *file, struct climate_info **states, int num_states) {
    int num_items = 0;
    int in_array = 0;
    const int line_sz = 100;
    char line[line_sz];
    while (fgets(line, line_sz, file) != NULL) {
    	char* token = strtok(line, "\t"); // obtain state code

	int i;
	for(i = 0; i < num_items; i++) {
		if(strcmp(states[i]->code, token) == 0) { // state entry already exists
			token = strtok(NULL, "\t\n"); // obtain date
			unsigned long this_date = atoi(token); // record date in temp variable

			token = strtok(NULL, "\t"); // skip geolocation
			token = strtok(NULL, "\t"); // obtain humidity
			
			states[i]->sum_humidity += atoi(token); //add to humidity running total

			token = strtok(NULL, "\t"); // obtain snow
			states[i]->snow += atoi(token);

			token = strtok(NULL, "\t"); // obtain cloud cover
			states[i]->sum_cloudcover += atoi(token);

			token = strtok(NULL, "\t"); // obtain lightning
			states[i]->lightning += atoi(token);

			token = strtok(NULL, "\t"); // skip pressure

			token = strtok(NULL, "\t"); // obtain temp in kelvin
			states[i]->sum_temperature += atoi(token);
			// check if this record has a higher or lower temp than our current stored min/max
			if(states[i]->min_temp > atoi(token)) {
				states[i]->min_temp = atoi(token);
				states[i]->min_date = this_date;
			}

			if(states[i]->max_temp < atoi(token)) {
				states[i]->max_temp = atoi(token);
				states[i]->max_date = this_date;
			}

			states[i]->num_records += 1;
			in_array = 1;
			break;
		}
	}

	if(!in_array) { // new state entry
		states[num_items] = (state*) malloc(sizeof(state)); // allocate space

		// initialize state fields
		strcpy(states[num_items]->code, token);

		token = strtok(NULL, "\t"); // obtain date
		states[num_items]->min_date = atoi(token); // record date in temp variable
		states[num_items]->max_date = atoi(token); // record date in temp variable

		token = strtok(NULL, "\t"); // skip geolocation

		token = strtok(NULL, "\t"); // obtain humidity
		states[i]->sum_humidity = atoi(token); //add to humidity running total		

		token = strtok(NULL, "\t"); // obtain snow
		states[i]->snow = atoi(token);

		token = strtok(NULL, "\t"); // obtain cloud cover
		states[i]->sum_cloudcover = atoi(token);

		token = strtok(NULL, "\t"); // obtain lightning
		states[i]->lightning = atoi(token);

		token = strtok(NULL, "\t"); // skip pressure

		token = strtok(NULL, "\t"); // obtain temp in kelvin
		states[i]->sum_temperature = atoi(token);
		states[i]->min_temp = atoi(token);
		states[i]->max_temp = atoi(token);

		states[num_items]->num_records = 1;
		num_items += 1;
	}

        /* TODO: We need to do a few things here:
         *
         *       * Tokenize the line.
         *       * Determine what state the line is for. This will be the state
         *         code, stored as our first token.
         *       * If our states array doesn't have a climate_info entry for
         *         this state, then we need to allocate memory for it and put it
         *         in the next open place in the array. Otherwise, we reuse the
         *         existing entry.
         *       * Update the climate_info structure as necessary.
         */

    }
}

void print_report(struct climate_info *states[], int num_states) {
    printf("States found: ");
    int i;
    for (i = 0; i < num_states; ++i) {
        if (states[i] != NULL) {
            struct climate_info *info = states[i];
            printf("%s ", info->code);
        }
    }
    printf("\n");

    int j;
    for (j = 0; j < num_states; j++) {
    	if(states[j] != NULL) {
		printf("-- State: %s --\n", states[j]->code);
		printf("Number of Records: %lu\n", states[j]->num_records);
		double avg_humidity = states[j]->sum_humidity / states[j]->num_records;
		printf("Average Humidity: %.1f%%\n", avg_humidity);
		double avg_temp = states[j]->sum_temperature / states[j]->num_records;
		double avg_f = (avg_temp * 1.8) - 459.67;
		printf("Average Temperature: %.2fF\n", avg_f);
		const time_t maxstamp = states[j]->max_date / 1000;
		double max_f = (states[j]->max_temp * 1.8) - 459.67;
		printf("Max Temp: %.1f on %s", max_f, ctime(&maxstamp));
		const time_t minstamp = states[j]->min_date / 1000;
		double min_f = (states[j]->min_temp * 1.8) - 459.67;
		printf("Min Temp: %.1f on %s", min_f, ctime(&minstamp));

		printf("Lightning Strikes: %d\n", states[j]->lightning);
		printf("Records with Snow Cover: %d\n", states[j]->snow);
		double avg_cc = states[j]->sum_cloudcover / states[j]->num_records;
		printf("Average Cloud Cover: %.1f%%\n", avg_cc);
	}
    }

    printf("\n");

    /* TODO: Print out the summary for each state. See format above. */
}
