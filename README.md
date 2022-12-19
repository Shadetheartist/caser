# caser

Caser is a command line utility that converts input strings based on a standard naming convention. It will split the input string on the delimiters " ", "_", ".", and "-". Except for when using file mode `-f/--file`, where the "." delimiter is not used.

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

### Standardizing File Names

This is really the target use-case of this program. It was created in order to standardize file names easily. But as UNIX is all about 'doing one thing, and doing it well', `caser` itself does not rename files, however it can be very easily made to do so using the shell, as this program supports piping. 

`echo "hello world" | caser -s` -> `hello_world`

### Bash Functions

Add the following function to your `~/.bashrc` file in order to quickly standardize file names using `caser`.

```
cmv(){
	FORMATTED=$(caser -sf -i l "$1")
	mv "$1" "$FORMATTED"
}
```

example usage `cmv "some InSaNe FILE.namE"` -> `some_insane_file.name`

###

This function will standardize all files in the current working directory. Great for converting multiple files at once. For instance, converting a folder containing episodes of a tv series.

```
cmv_all(){
	for n in *; do cmv "$n"; done
}

```




## Installation

extract the .tar.gz file and run 

```
./configure
make
make install
```
