# caser

Caser is a command line utility that converts input strings based on a standard naming convention. 

## Usage
```
Usage: caser [OPTION...] [STRING]...
Converts strings and file names to a standard naming convention scheme.

  -c, --camel                Convert to camelCase.
  -d, --dash                 Convert to dash-case.
  -f, --file                 Allow dot '.' to remain in output strings.
  -i, --casing=l|u|p         Lower case ('l'), upper case ('u') or preserve
                             case ('p').  Only works with the 'none', 'snake',
                             and 'dash' naming conventions.
  -n, --none                 Do not enforce a naming convention scheme.
  -p, --pascal               Convert to PascalCase.
  -s, --snake                Convert to snake_case.
  -t, --title                Convert to Title Case.
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.
```

## Examples

`caser -s -i l "some input text"` outputs `some_input_text`

`caser -i u "some input text"` outputs `SOME INPUT TEXT`

You could use it to standardize your file names, using file mode, the '.' character remains in the string.

```for n in *; do mv "$n" `caser -sf -i l "$n"`; done```

## Installation

extract the .tar.gz file and run 

```
./configure
make
make install
```
