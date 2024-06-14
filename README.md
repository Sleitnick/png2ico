# PNG to ICO

The `png2ico` command line tool converts a list of PNG files into a single ICO file.

## Install
Download the latest release binary for your given platform.

## Usage
```sh
# Convert a list of PNGs to a single ICO file:
$ png2ico output.ico input1.png [input2.png]...

# Output version
$ png2ico --version

# Output help
$ png2ico --help
```

## About
I needed to generate an ICO file for a Godot application. All the other tools to do so were terrible or hosted on sketchy websites built to generate ad revenue. I also wanted to learn some more C, hence why this is written in C and not some fancy new language. Nonetheless, the project is quite small.

This tool has been written specifically for the given task of generating an ICO file from a series of PNG files. There are no external libraries outside of the standard C library. The PNG decoder is only implemented to decode the necessary parts of the PNG in order to generate the ICO file. As such, the generated binary is nice and small.

## Build from Source
Run the Makefile to build the project. The output will be `build/png2ico`.
```sh
# Run `make` from within the root project directory:
$ make
```

## Project Structure
| File | Description | Local Dependencies |
| ---- | ----------- | ------------ |
| `main` | Entry point and CLI management | _All_ |
| `ico` | ICO generator | `png`, `buffer`, `err` |
| `png` | PNG decoder | `buffer`, `err` |
| `err` | Shared error definitions | _None_ |

## Contributing
See something that's broken or insecure? Feel free to open up an issue and open up a PR. Pull requests without an attached issue will be declined.
