# JSON Path Command line Tool

Extract parts of a json file using JSONPath.

## Prerequisite

This code was built with glib-2.0 and json-glib-1.0. You will need the
development packages if you build from scratch.

If you are on Ubuntu.

```bash
apt-get install libglib2.0-dev libjson-glib-dev libjson-glib-dev
```

## Build From Source

```bash
make && sudo make install PREFIX=/usr/local
# or pick a better prefix. Default: ~/.local
```

## Usage

From a file

```bash
jcp "$.name" file.json
```

From stdin

```bash
cat file.json | jcp "$.name"
```

## Disclaimer

This was built because i needed it now. Not because i planned to create a full
featured tool.  There are memory leaks and security issues. Use at your own
risk.
