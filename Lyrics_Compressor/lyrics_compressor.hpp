#ifndef LYRICS_COMPRESSOR_HPP
#define LYRICS_COMPRESSOR_HPP
#include "hash_map.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <list>
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::list;
using std::pair;
using std::string;

namespace data_structures
{

	class LyricCompressor
	{
	public:
		~LyricCompressor() = default;
		LyricCompressor();
		HashMap<string, vector<int>> Compress();
		void PrintCompressed(HashMap<string, vector<int>>& hashy);
		void Decompress(HashMap<string, vector<int>>& hashy);
		std::ifstream ReadFile();

	private:
		vector<pair<string, int>> song_;


	};


	LyricCompressor::LyricCompressor()
	{
		auto ist = ReadFile();
		//ist.open();
		int location = 0;
		while (!ist.eof())
		{
			std::string lyric_line;
			std::getline(ist, lyric_line, '\n');

			std::string lyric;
			for (auto x : lyric_line)
			{
				if (x == ' ')
				{
					song_.push_back(pair<string, int>(lyric, ++location));
					lyric = "";
				}
				else
				{
					lyric = lyric + x;
				}
			}
			auto end_line_location = ++location * -1;
			song_.push_back(pair<string, int>(lyric, end_line_location));
		}
		ist.close();



	}

	inline HashMap<string, vector<int>> LyricCompressor::Compress()
	{
		const auto hash_function = [&](string key) ->int
		{
			auto sum = 0;
			auto sum2 = 0;
			for (auto& ch : key)
			{
				sum2 += ch;
				sum = (sum2 << 1) ^ ch;
			}
			return sum % 13;
		};

		auto hash_map = HashMap<string, vector<int>>(13, hash_function);

		for (auto& lyric : song_)
		{
			if (!hash_map.Contains(lyric.first))
			{
				hash_map.Insert(lyric.first, { lyric.second });
			}
			else
			{
				hash_map[lyric.first].push_back(lyric.second);
			}
		}
		return hash_map;
	}

	inline void LyricCompressor::PrintCompressed(HashMap<string, vector<int>>& hashy)
	{
		bool PrintCompressed = true;
		while (PrintCompressed)
		{
			char ending;
			cout << "\n\nWould you like to print the compressed lyrics? ( y or n )";
			cin >> ending;
			if (ending != 'n')
			{
				cout << "\n\n";
				const auto visit = [&](const string& key, const vector<int>& values) -> void
				{
					cout << key << " : ";
					for (auto& value : values)
					{
						cout << value << " ";
					}
					cout << endl;

				};

				hashy.Traverse(visit);

				PrintCompressed = false;
			}
		}
	}

	inline void LyricCompressor::Decompress(HashMap<string, vector<int>>& hashy)
	{
		bool decompressOption = true;
		while (decompressOption)
		{
			char ending;
			cout << "\n\nWould you now like to decompress those lyrics back to their original state \nAnd write them to a new file while printing them to the screen? ( y or n )";
			cin >> ending;
			cout << "\n\n";
			if (ending != 'n')
			{

				int total_values = 0;
				const auto count = [&](const string& key, const vector<int>& values) -> void
				{
					for (auto& two : values)
						++total_values;
				};

				hashy.Traverse(count);

				int current_place = 1;

				cout << "\nPlease enter the name of the new file for the song lyrics";
				string file_name;
				cin >> file_name;

				std::fstream file;
				file.open(file_name.c_str(), std::ios::out);
				const auto visit = [&](const string& key, const vector<int>& values) -> void
				{
					for (auto& value : values)
					{
						if (current_place == value)
						{
							cout << key << " ";
							file << key << " ";
							current_place++;
						}
						else if (current_place * -1 == value)
						{
							cout << key << endl;
							file << key << endl;
							current_place++;
						}
					}
				};


				while (total_values > current_place)
				{
					hashy.Traverse(visit);
				}
				file.close();
				decompressOption = false;
			}
		}
	}

	inline std::ifstream LyricCompressor::ReadFile()
	{
		auto valid = true;
		while (valid)
		{
			char ending;
			cout << "Welcome to the Lyric Compressor! Ya'll want to compress them lyrics? ( y or n )";
			cin >> ending;
			if (ending != 'n')
			{
				auto good_input = true;
				do
				{
					cout << "\n\nPlease enter the name of the lyrics file!";
					string file_name;

					cin >> file_name;
					std::ifstream ist(file_name.c_str());
					cout << "\nThe filename you entered was: " << file_name << endl;
					if (!ist.is_open())
					{
						cout << "File Invalid! Try Again.";
						cin.clear();
						cin.get();
						good_input = false;
					}
					else
					{
						return ist;
					}
				} while (!good_input);
			}
			else
			{
				valid = true;
			}
		}
	}

}

#endif
