
#include "hash_map.hpp"
#include "lyrics_compressor.hpp"
#include "string"
using std::string;

using namespace data_structures;


int main()
{
	bool EntireProgram = true;
	while (EntireProgram)
	{
		auto new_program = LyricCompressor();

		auto hash_map = new_program.Compress();

		new_program.PrintCompressed(hash_map);

		new_program.Decompress(hash_map);

		cout << "\n\n\n\nThanks for Playing!\n\n\n";

		char ending;
		cout << "\n\nWould you like to try a different file? ( y or n ) ";
		cin >> ending;
		if (ending != 'y')
		{
			EntireProgram = false;
		}
	}
}