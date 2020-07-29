unsigned int eight_from_eight(organism_t *organism, unsigned int uint_0,
		unsigned int uint_1, unsigned int uint_2, unsigned int uint_3,
		unsigned int uint_4, unsigned int uint_5, unsigned int uint_6,
		unsigned int uint_7)
{
	unsigned int cells[8][EFE_LENGTH];
	unsigned int each_x;
	unsigned int each_y;
	unsigned int ca_in_0;
	unsigned int ca_in_1;
	unsigned int ca_in_2;
	unsigned int ca_index_0;
	unsigned int ca_index_1;
	unsigned int ca_index_2;
	unsigned int ca_out_address;
	unsigned int ca_out;
	unsigned int result;
	unsigned int result_bit_0;
	unsigned int result_bit_1;
	unsigned int result_bit_2;

	cells[0][0] = uint_0;
	cells[1][0] = uint_1;
	cells[2][0] = uint_2;
	cells[3][0] = uint_3;
	cells[4][0] = uint_4;
	cells[5][0] = uint_5;
	cells[6][0] = uint_6;
	cells[7][0] = uint_7;

	for (each_y = 1; each_y < EFE_LENGTH; each_y++) {
		for (each_x = 0; each_x < 8; each_x++) {

			/*  it might make a difference if these indexes, before being
				wrapped, had a constant added to them so that they weren't at
				the beginning of the genome (like how with gene indexes I've
				been starting them at 2 so they're offset from the start of
				the gene)...the thinking behind this was something like: for
				some reason I thought maybe the code had, as a byproduct of
				some algorithm, given a preference for gene cutting/selection/
				copying during the meet...that I had given some preference
				that would make cutting/selecting/copying less likely at the
				beginning of the gene, so having these things farther into the
				gene would make them more likely to be changeable.  but I'm
				not sure there even is such a preference.  */
			ca_index_0 = wrapped_index(each_x - 1, 8);
			ca_index_1 = each_x;
			ca_index_2 = wrapped_index(each_x + 1, 8);

			ca_in_0 = cells[ca_index_0][each_y - 1];
			ca_in_1 = cells[ca_index_1][each_y - 1];
			ca_in_2 = cells[ca_index_2][each_y - 1];
			ca_out_address = CA_OUT_ADDRESS_SPREAD_FACTOR * (
				(4 * ca_in_0) + (2 * ca_in_1) + (1 * ca_in_2)
				);
			ca_out = unsigned_int_from_genome(organism, ca_out_address, 1);
			cells[each_x][each_y] = ca_out;
		}
	}

	result_bit_0 = cells[0][EFE_LENGTH - 1];
	result_bit_1 = cells[1][EFE_LENGTH - 1];
	result_bit_2 = cells[2][EFE_LENGTH - 1];
	result = (4 * result_bit_0) + (2 * result_bit_1) + result_bit_2;

	return result;
}
