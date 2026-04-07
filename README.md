# Lyrics Compressor

![Repo Size](https://img.shields.io/github/repo-size/drussell33/Lyrics-Compressor)
![Last Commit](https://img.shields.io/github/last-commit/drussell33/Lyrics-Compressor)
![Top Language](https://img.shields.io/github/languages/top/drussell33/Lyrics-Compressor)

Lyrics Compressor is a small C++ console application that reads a text-based lyrics file, compresses repeated words into a hash map representation, and optionally reconstructs the original lyrics into a new output file. The project is structured as a Visual Studio solution and doubles as a compact example of custom data structures, file I/O, and interactive command-line workflow in modern C++.

## Key Features

- Reads a user-supplied lyrics text file from the command line
- Tokenizes lyrics into words while preserving line boundaries through signed positional markers
- Builds a compressed representation using a custom `HashMap<string, vector<int>>`
- Stores each unique lyric token once and tracks every occurrence position
- Prints the compressed hash map representation on demand
- Decompresses the stored structure back into original lyric order
- Writes decompressed lyrics to a new user-named output file
- Includes a custom exception type for data-structure validation and lookup failures
- Supports repeated runs in a single application session

## Tech Stack

### Backend
- C++
- Standard Library file and stream handling
- Custom templated hash map implementation

### Frontend
- Console-based command-line interface

### Database
- None

### Tools / Services
- Visual Studio solution (`.sln`)
- Visual C++ project (`.vcxproj`)
- MSVC toolset `v142`
- Windows console application target

## Architecture Overview

The application is a single-process console program centered around the `LyricCompressor` class. At startup, `main()` creates a compressor instance, invokes compression, prints the compressed structure, and optionally runs decompression before allowing the user to process another file.

### Flow

1. The program prompts the user for an input text file.
2. `LyricCompressor` reads the file line by line and tokenizes each line into words.
3. Each token is stored internally as a pair of:
   - the lyric word
   - an integer position marker

Positive integers represent standard word order, while negative integers mark end-of-line positions so line breaks can be reconstructed during decompression.

### Core Components

- **`LyricCompressor`**  
  Encapsulates file reading, tokenization, compression, compressed output, and decompression.

- **`HashMap<K, V>`**  
  A custom templated hash map backed by `vector<list<pair<K, V>>>`, used to store each unique lyric token and all of its occurrence positions.

- **`AdtException`**  
  A lightweight custom exception type used for invalid hash map operations such as null hash functions, invalid table sizes, and missing keys.

### Visible Patterns

- **Encapsulation** via the `LyricCompressor` class
- **Template-based generic data structure** in `HashMap`
- **Dependency on injected behavior** through a provided hash function passed into `HashMap`
- **Value-object style storage** using `pair<string, int>` and `vector<int>`
- **Interactive workflow orchestration** in `main()`

Because the repository contains only a console application, there is no frontend/backend split in the web-application sense and no database layer. The primary interaction is between the input file, the in-memory compression structure, and the output file generated during decompression.

## Project Structure

```tree
Lyrics-Compressor/
├── .gitignore
├── Lyrics_Compressor.sln
├── README.md
└── Lyrics_Compressor/
    ├── Lyrics_Compressor.vcxproj
    ├── Lyrics_Compressor.vcxproj.filters
    ├── Main.cpp
    ├── adt_exception.hpp
    ├── hash_map.hpp
    └── lyrics_compressor.hpp
```

### Folder and File Notes

- **`Lyrics_Compressor.sln`**  
  Visual Studio solution entry point for the project.

- **`Lyrics_Compressor/`**  
  Main application source directory containing the console entry point, compressor implementation, and supporting headers.

- **`Lyrics_Compressor/Main.cpp`**  
  Program entry point and top-level interaction loop.

- **`Lyrics_Compressor/lyrics_compressor.hpp`**  
  Contains the `LyricCompressor` class and the core compression/decompression workflow.

- **`Lyrics_Compressor/hash_map.hpp`**  
  Defines the custom generic hash map used by the compressor.

- **`Lyrics_Compressor/adt_exception.hpp`**  
  Custom exception implementation for data-structure-related errors.

## Getting Started

### Prerequisites

- Windows
- Visual Studio with C++ desktop development tools installed
- MSVC toolset compatible with `v142`
- A plain text lyrics file to use as input

### Installation

```bash
git clone https://github.com/drussell33/Lyrics-Compressor.git
cd Lyrics-Compressor
```

### Build

#### Option 1: Visual Studio

1. Open `Lyrics_Compressor.sln` in Visual Studio.
2. Select a configuration such as `Debug` or `Release`.
3. Build the solution.
4. Run the generated console application.

#### Option 2: MSBuild

```bash
msbuild Lyrics_Compressor.sln /p:Configuration=Debug
```

### Usage

Run the compiled executable, then follow the prompts:

1. Confirm that you want to compress a file
2. Enter the source lyrics filename
3. Choose whether to print the compressed output
4. Choose whether to decompress the lyrics
5. Enter a filename for the reconstructed output

Example runtime flow:

```text
Welcome to the Lyric Compressor! Ya'll want to compress them lyrics? ( y or n )
Please enter the name of the lyrics file!
Would you like to print the compressed lyrics? ( y or n )
Would you now like to decompress those lyrics back to their original state
And write them to a new file while printing them to the screen? ( y or n )
Please enter the name of the new file for the song lyrics
```

## Roadmap

- [x] Read lyrics from a user-specified text file
- [x] Tokenize lyrics into ordered word positions
- [x] Preserve line endings during reconstruction
- [x] Compress repeated lyric tokens into a hash map structure
- [x] Print compressed data to the console
- [x] Decompress stored data back into readable lyrics
- [x] Write decompressed output to a new file
- [ ] Add automated tests for compression and decompression logic
- [ ] Separate declarations and implementations into `.cpp` files for cleaner compilation units
- [ ] Improve input validation and recovery behavior
- [ ] Support punctuation-aware tokenization
- [ ] Add compression statistics such as unique token count and reduction ratio
- [ ] Add support for configurable hash table sizing
- [ ] Modernize the build workflow with CMake or cross-platform tooling

## Contributing

Contributions are welcome through the standard GitHub workflow:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Commit with clear messages
5. Push your branch
6. Open a pull request

When contributing, keep changes aligned with the current project scope and preserve the existing command-line workflow unless the change is intentionally expanding it.

## Screenshots / Demo

Screenshots and demo assets have not been included in the repository yet.

Suggested additions for future updates:

- Console startup prompt
- Example compressed output
- Example decompressed file output
- Short animated terminal demo

## Contact

- GitHub: [drussell33](https://github.com/drussell33)
