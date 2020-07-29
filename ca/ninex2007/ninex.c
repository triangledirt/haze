/* ------------------------------------------------------------------------- */
/*  ninex.c - created 2007 by inhaesio zha (zha@inhesion.com)                */
/*                                                                           */
/*  gcc -ansi -O3 -I/opt/local/include -L/usr/X11R6/lib -L/opt/local/lib     */
/*    -lX11 -ljpeg -o ninex ninex.c                                          */
/* ------------------------------------------------------------------------- */

/*
  + I think the idea was that all the genes of all the organisms in the
    neighborhood would operate as one string during the meet/move
  + try reversing the order of move() and meet() during the iteration
  + ...
*/

#include <curses.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <jpeglib.h>

/* --[ initial settings ]--------------------------------------------------- */
#define RANDOM_SEED 0

/* --[ organism settings ]-------------------------------------------------- */
#define GENOME_ADDRESS_SIZE 8
#define NEIGHBORHOOD_RADIUS 1
#define BIT_HISTORY_SIZE 32

/* --[ world settings ]----------------------------------------------------- */
#define ITERATIONS 1024
#define WORLD_WIDTH 128
#define WORLD_HEIGHT 64

/* --[ gene settings ]------------------------------------------------------ */
#define GENE_INDEX_DISPLAY 0
#define GENE_INDEX_MOVE 1
#define GENE_INDEX_MEET 2
#define GENE_INDEX_HISTORY_BIT 3

/* --[ poster settings ]---------------------------------------------------- */
#define POSTER_VISUALIZATION 1
#define POSTER_WIDTH 4
#define POSTER_HEIGHT 4
#define POSTER_FRAME_SKIP (ITERATIONS) / (POSTER_WIDTH * POSTER_HEIGHT)
#define POSTER_SAVE 0
#define POSTER_WINDOW_MARGIN_PIXELS 16

/* --[ movie settings ]----------------------------------------------------- */
#define MOVIE_SAVE_FRAMES 0
#define MOVIE_FRAME_DIRECTORY "frames_x"
#define MOVIE_JPEG_QUALITY 100

/* --[ calculated constants ]----------------------------------------------- */
#define TOTAL_ORGANISMS WORLD_WIDTH * WORLD_HEIGHT
#define TOTAL_GENES TOTAL_ORGANISMS * GENOME_SIZE

/* --[ etc ]---------------------------------------------------------------- */
#define COLOR_INTEGER_SIZE 8
#define RED_MODULUS 8192
#define USLEEP 1024

struct meet_gene_t {
	unsigned int address_a;
	unsigned int address_b;
	unsigned int size;
};
typedef struct meet_gene_t meet_gene_t;

struct move_gene_t {
	unsigned int address_of_gene_in_participant_a;
	unsigned int address_of_gene_in_participant_b;
};
typedef struct move_gene_t move_gene_t;

struct display_gene_t {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
};
typedef struct display_gene_t display_gene_t;

struct position_t {
	unsigned int x;
	unsigned int y;
};
typedef struct position_t position_t;

struct relative_position_t {
	int x;
	int y;
};
typedef struct relative_position_t relative_position_t;

struct organism_t {
	struct world_t *world;
	position_t position;
	unsigned int *genome;
	unsigned int bit_history[BIT_HISTORY_SIZE];
};
typedef struct organism_t organism_t;

struct world_t {
	unsigned int genome_size;
	unsigned int neighborhood_size_in_cells;
	unsigned int neighborhood_address_size;
	organism_t *organisms[WORLD_WIDTH][WORLD_HEIGHT];
};
typedef struct world_t world_t;

unsigned int calculate_genome_size();
unsigned int calculate_neighborhood_address_size(
	unsigned int neighborhood_size_in_cells, unsigned int genome_size);
unsigned int calculate_neighborhood_size_in_cells();
void destroy_organism(organism_t *organism);
void destroy_world(world_t *world);
unsigned int gene_at_virtual_index(organism_t *organism,
		unsigned int virtual_index);
void iterate_organism(organism_t *organism);
void iterate_world(world_t *world);
void meet_organism(organism_t *organism);
void move_organism(organism_t *organism);
organism_t *new_organism(world_t *world, unsigned int position_x,
		unsigned int position_y);
world_t *new_world();
void parse_display_gene(organism_t *organism, display_gene_t *display_gene);
void parse_meet_gene(organism_t *organism, meet_gene_t *meet_gene);
void parse_move_gene(organism_t *organism, move_gene_t *move_gene);
unsigned int random_unsigned_int(unsigned int range);
void shift_bit_history(organism_t *organism);
unsigned int unsigned_int_from_bit_history(organism_t *organism);
unsigned int unsigned_int_from_genome(organism_t *organism,
		unsigned int gene_start_address, unsigned int gene_size);
unsigned int wrapped_index(int virtual_index, unsigned int range);

unsigned int calculate_genome_size()
{
	return (unsigned int) pow(2, GENOME_ADDRESS_SIZE);
}

unsigned int calculate_neighborhood_address_size(
	unsigned int neighborhood_size_in_cells, unsigned int genome_size)
{
	unsigned int genome_address_size = 1;
	unsigned int addressable_size;
	unsigned int minimum_addressable_size;

	minimum_addressable_size = neighborhood_size_in_cells * genome_size;

	addressable_size = (unsigned int) pow(2, genome_address_size);
	while (addressable_size < minimum_addressable_size) {
		genome_address_size++;
		addressable_size = (unsigned int) pow(2, genome_address_size);
	}

	return genome_address_size;
}

unsigned int calculate_neighborhood_size_in_cells()
{
	return (unsigned int) pow(1 + (2 * NEIGHBORHOOD_RADIUS), 2);
}

void destroy_organism(organism_t *organism)
{
	free(organism->genome);
	free(organism);
}

void destroy_world(world_t *world)
{
	unsigned int each_x;
	unsigned int each_y;

	for (each_x = 0; each_x < WORLD_WIDTH; each_x++) {
		for (each_y = 0; each_y < WORLD_HEIGHT; each_y++) {
			destroy_organism(world->organisms[each_x][each_y]);
		}
	}

	free(world);
}

unsigned int gene_at_virtual_index(organism_t *organism,
		unsigned int virtual_index)
{
	unsigned int actual_index;

	actual_index = wrapped_index(virtual_index, organism->world->genome_size);
	return organism->genome[actual_index];
}

void iterate_organism(organism_t *organism)
{
	move_organism(organism);
	meet_organism(organism);
	shift_bit_history(organism);
}

void iterate_world(world_t *world)
{
	unsigned int each_x;
    unsigned int each_y;

	for (each_x = 0; each_x < WORLD_WIDTH; each_x++) {
		for (each_y = 0; each_y < WORLD_HEIGHT; each_y++) {
			iterate_organism(world->organisms[each_x][each_y]);
		}
	}
}

void meet_organism(organism_t *organism)
{
	/*  TODO: implement  */
}

void move_organism(organism_t *organism)
{
	/*  TODO: implement  */
}

organism_t *new_organism(world_t *world, unsigned int position_x,
		unsigned int position_y)
{
	organism_t *organism;
	unsigned int each_bit;
	unsigned int each_gene;

	organism = malloc(sizeof(organism_t));

	organism->world = world;
	organism->position.x = position_x;
	organism->position.y = position_y;

	organism->genome = malloc(sizeof(unsigned int) * world->genome_size);
	for (each_gene = 0; each_gene < world->genome_size; each_gene++) {
		organism->genome[each_gene] = random_unsigned_int(2);
	}

	for (each_bit = 0; each_bit < BIT_HISTORY_SIZE; each_bit++) {
		organism->bit_history[each_bit] = random_unsigned_int(2);
	}

	return organism;
}

world_t *new_world()
{
	world_t *world;
	unsigned int each_x;
	unsigned int each_y;

	world = malloc(sizeof(world_t));

	world->genome_size = calculate_genome_size();
	world->neighborhood_size_in_cells = calculate_neighborhood_size_in_cells();
	world->neighborhood_address_size = calculate_neighborhood_address_size(
		world->neighborhood_size_in_cells, world->genome_size);

	for (each_x = 0; each_x < WORLD_WIDTH; each_x++) {
		for (each_y = 0; each_y < WORLD_HEIGHT; each_y++) {
			world->organisms[each_x][each_y] = new_organism(world, each_x,
					each_y);
		}
	}

	return world;
}

void parse_display_gene(organism_t *organism, display_gene_t *display_gene)
{
	unsigned int gene_start_address;

	gene_start_address = unsigned_int_from_genome(organism,
			GENE_INDEX_DISPLAY * GENOME_ADDRESS_SIZE, GENOME_ADDRESS_SIZE);

	display_gene->red = unsigned_int_from_genome(organism,
			gene_start_address + (0 * COLOR_INTEGER_SIZE), COLOR_INTEGER_SIZE);
	display_gene->green = unsigned_int_from_genome(organism,
			gene_start_address + (1 * COLOR_INTEGER_SIZE), COLOR_INTEGER_SIZE);
	display_gene->blue = unsigned_int_from_genome(organism,
			gene_start_address + (2 * COLOR_INTEGER_SIZE), COLOR_INTEGER_SIZE);
}

void parse_meet_gene(organism_t *organism, meet_gene_t *meet_gene)
{
	unsigned int gene_start_address;

	gene_start_address = unsigned_int_from_genome(organism,
			GENE_INDEX_MEET * GENOME_ADDRESS_SIZE, GENOME_ADDRESS_SIZE);

	meet_gene->address_a = unsigned_int_from_genome(organism,
			gene_start_address + (0 * GENOME_ADDRESS_SIZE),
			GENOME_ADDRESS_SIZE);
	meet_gene->address_b = unsigned_int_from_genome(organism,
			gene_start_address + (1 * GENOME_ADDRESS_SIZE),
			GENOME_ADDRESS_SIZE);
	meet_gene->size = unsigned_int_from_genome(organism,
			gene_start_address + (2 * GENOME_ADDRESS_SIZE),
			GENOME_ADDRESS_SIZE);
}

unsigned int random_unsigned_int(unsigned int range)
{
	return random() % range;
}

void shift_bit_history(organism_t *organism)
{
	unsigned int each_bit;
	unsigned int new_bit;
	unsigned int new_bit_address;

	new_bit_address = 0;  /*  TODO: implement  */
	new_bit = unsigned_int_from_genome(organism, new_bit_address, 1);

	for (each_bit = 1; each_bit < BIT_HISTORY_SIZE; each_bit++) {
		organism->bit_history[each_bit - 1] = organism->bit_history[each_bit];
	}
	organism->bit_history[BIT_HISTORY_SIZE - 1] = new_bit;
}

unsigned int unsigned_int_from_bit_history(organism_t *organism)
{
	int each_bit;
	unsigned int each_bit_value = 1;
	unsigned int r = 0;

	for (each_bit = (BIT_HISTORY_SIZE - 1); each_bit >= 0; each_bit--) {
		r += each_bit_value * organism->bit_history[each_bit];
		each_bit_value *= 2;
	}

	return r;
}

unsigned int unsigned_int_from_genome(organism_t *organism,
		unsigned int gene_start_address, unsigned int gene_size)
{
	unsigned int each_part_of_address;
	unsigned int each_part_of_address_value = 1;
	unsigned int r = 0;
	unsigned int gene_end_address;

	gene_end_address = gene_start_address + gene_size;

	for (each_part_of_address = gene_start_address;
		 each_part_of_address < gene_end_address;
		 each_part_of_address++) {
		r += each_part_of_address_value
			* gene_at_virtual_index(organism, each_part_of_address);
		each_part_of_address_value *= 2;
	}

	return r;
}

unsigned int wrapped_index(int virtual_index, unsigned int range)
{
	unsigned int wrapped_index;

	if (virtual_index >= (int) range) {
		wrapped_index = virtual_index % range;
	}
	else if (virtual_index < 0) {
		wrapped_index = range - ((-1 * virtual_index) % range);
	}
	else {
		wrapped_index = virtual_index;  
	}

	return wrapped_index;
}

GLOBAL(void) write_JPEG_file(char *filename, int quality,
		JSAMPLE *image_buffer, int image_height, int image_width)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE *outfile;
	JSAMPROW row_pointer[1];
	int row_stride;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if ((outfile = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		exit(1);
	}
	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = image_width;
	cinfo.image_height = image_height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE);

	jpeg_start_compress(&cinfo, TRUE);
	row_stride = image_width * 3;

	while (cinfo.next_scanline < cinfo.image_height) {
		row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);
	fclose(outfile);

	jpeg_destroy_compress(&cinfo);
}

int main(int argc, char *argv[])
{
	world_t *world;
	unsigned int each_iteration;
	unsigned int displayed_iteration = 0;
	unsigned int display_gene_start_address;
	organism_t *organism;
	display_gene_t display_gene;

	Display *display;
	GC gc;
	int screen_number;
	int window_x;
	int window_y;
	unsigned int each_x;
	unsigned int each_y;
	unsigned int window_border_width;
	unsigned int window_height;
	unsigned int window_width;
	unsigned long gc_value_mask;
	unsigned long window_background_color;
	unsigned long window_border_color;
	Window root_window;
	Window window;
	XGCValues gc_values;
	Visual* default_visual;
	Colormap colormap;
	XColor color;

	JSAMPLE *image_buffer;
	char *filename;

#if POSTER_VISUALIZATION
	display = XOpenDisplay(NULL);
	screen_number = DefaultScreen(display);
	root_window = RootWindow(display, screen_number);
	window_x = 0;
	window_y = 0;
	window_width = (WORLD_WIDTH * POSTER_WIDTH) + POSTER_WINDOW_MARGIN_PIXELS
		+ (POSTER_WIDTH - 1);
	window_height = (WORLD_HEIGHT * POSTER_HEIGHT)
		+ POSTER_WINDOW_MARGIN_PIXELS + (POSTER_HEIGHT - 1);
	window_border_width = 0;
	window_border_color = BlackPixel(display, screen_number);
	window_background_color = WhitePixel(display, screen_number);
	window = XCreateSimpleWindow(display, root_window, window_x, window_y,
			window_width, window_height, window_border_width,
			window_border_color, window_background_color);
	XMapWindow(display, window);
	XFlush(display);

	gc_value_mask = 0;
	gc = XCreateGC(display, window, gc_value_mask, &gc_values);
	XSync(display, False);

	default_visual = DefaultVisual(display, DefaultScreen(display));
	colormap = XCreateColormap(display, window, default_visual, AllocNone);
#endif

#if MOVIE_SAVE_FRAMES
	image_buffer = malloc(sizeof(JSAMPLE) * WORLD_WIDTH * WORLD_HEIGHT * 3);
	filename = malloc(sizeof(char) * 128);
#endif

	srandom(RANDOM_SEED);
	world = new_world();

	for (each_iteration = 0; each_iteration < ITERATIONS; each_iteration++) {

#if POSTER_VISUALIZATION
		if (0 == (each_iteration % POSTER_FRAME_SKIP)) {
			for (each_x = 0; each_x < WORLD_WIDTH; each_x++) {
				for (each_y = 0; each_y < WORLD_HEIGHT; each_y++) {
					organism = world->organisms[each_x][each_y];

					parse_display_gene(organism, &display_gene);
					color.red = display_gene.red % RED_MODULUS;
					color.green = display_gene.green;
					color.blue = display_gene.blue;
					XAllocColor(display, colormap, &color);
					XSetForeground(display, gc, color.pixel);

					XDrawPoint(display, window, gc,
							((displayed_iteration % POSTER_WIDTH)
									* WORLD_WIDTH)
							+ (displayed_iteration % POSTER_WIDTH) + each_x,
							((displayed_iteration / POSTER_WIDTH)
									* WORLD_HEIGHT) +
							 (displayed_iteration / POSTER_WIDTH) + each_y);
				}
			}
			displayed_iteration++;
			XFlush(display);
		}
#endif

#if MOVIE_SAVE_FRAMES
		for (each_x = 0; each_x < WORLD_WIDTH; each_x++) {
			for (each_y = 0; each_y < WORLD_HEIGHT; each_y++) {
				organism = world->organisms[each_x][each_y];

				parse_display_gene(world, organism, display_gene);
				color.red = display_gene.red % RED_MODULUS;
				color.green = display_geen.green;
				color.blue = display_gene.blue;

				image_buffer[(each_y * WORLD_WIDTH * 3)
						+ (each_x * 3) + 0] = display_gene.red;
				image_buffer[(each_y * WORLD_WIDTH * 3)
						+ (each_x * 3) + 1] = display_gene.green;
				image_buffer[(each_y * WORLD_WIDTH * 3)
						+ (each_x * 3) + 2] = display_gene.blue;
			}
		}
		sprintf(filename, "frames_y/teoc.%04i.jpg", each_iteration);
		write_JPEG_file(filename, MOVIE_JPEG_QUALITY, image_buffer,
				WORLD_HEIGHT, WORLD_WIDTH);
#endif

		iterate_world(world);
	}

#if POSTER_VISUALIZATION
	while (1) {
		usleep(USLEEP);
	}

	XUnmapWindow(display, window);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
#endif

	destroy_world(world);

#if MOVIE_SAVE_FRAMES
	free(filename);
	free(image_buffer);
#endif

	return 0;
}
