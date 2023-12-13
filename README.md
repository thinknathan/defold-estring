# defold-estring

Defold extension implementing a variety of string-related utilities.

You may prefer [DefString](https://github.com/subsoap/defstring) for a more robust implementation.

## Installation

1. Edit game.project
2. Add dependency `https://github.com/thinknathan/defold-estring/archive/main.zip` for the current version
    - Or add a specific [release](https://github.com/thinknathan/defold-estring/releases)

### TypeScript Definitions

1. Install these types

```bash
yarn add git+https://git@github.com/thinknathan/defold-estring.git#^2.0.0 -D
# or
npm install git+https://git@github.com/thinknathan/defold-estring.git#^2.0.0 --save-dev
```

2. Add `defold-estring` to `types` in `tsconfig.json`

```diff
{
	"compilerOptions": {
		"types": [
+			"defold-estring",
		],
	}
}
```

3. Add `node_modules/@types` to `typeRoots` in `tsconfig.json` if it's not already there

```diff
{
	"compilerOptions": {
		"typeRoots": [
+			"node_modules/@types",
		],
	}
}
```

## Usage

```lua
-- Concatenate strings and numbers
local resultConcat = estring.concat("Hello, ", "world", 123, "!")
print(resultConcat) -- Output: Hello, world123!

-- Trim leading and trailing whitespaces
local resultTrim = estring.trim("   This is a string with spaces   ")
print(resultTrim) -- Output: This is a string with spaces

-- Split a string
local resultSplit = estring.split("apple,orange,banana", ",")
for i, value in ipairs(resultSplit) do
    print(i, value)
end
-- Output:
-- 1   apple
-- 2   orange
-- 3   banana

-- Pad the start of a string
local resultPadStart = estring.padStart("42", "0", 5)
print(resultPadStart) -- Output: 00042

-- Pad the end of a string
local resultPadEnd = estring.padEnd("42", "0", 5)
print(resultPadEnd) -- Output: 42000

-- Format time
local resultFormatTime = estring.format_time(os.time(), 2, "-", "AM", "PM")
print(resultFormatTime) -- Output: 12-31-2023 12:45:30 PM
-- timeValue: (number or string) The time value to format. It can be either a numeric timestamp or a string representing a date and time.
-- formatType: (integer) Specifies the desired format type:
-- 1: "hh:mm AM/PM"
-- 2: "hh:mm:ss AM/PM"
-- 3: "HH:mm:ss"
-- 4: "HH:mm"
-- 5: "mm:ss"
-- delimiter: (string, optional) The delimiter used in the formatted time. Default is ":".
-- amString: (string, optional) The string representing "AM". Default is "AM".
-- pmString: (string, optional) The string representing "PM". Default is "PM".

-- Format a number
local resultFormatNumber = estring.format_number(1234567.89, 2, ",", ".")
print(resultFormatNumber) -- Output: 1,234,567.89
-- numberValue: (number or string) The number to format.
-- precision: (integer, optional) The number of decimal places. Default is 0.
-- thousandsSeparator: (string, optional) The character used as a separator for thousands. Default is ",".
-- decimalSeparator: (string, optional) The character used as a decimal point. Default is ".".
```

## Background

This project is an experiment with generating a Defold extension using Chat-GPT. The prompt was as follows:

```
create a defold extension that exposes a module to lua, use c++ that does not use any features newer than 2009, and does not use the standard library, and always uses const char* instead of std::string. the name of the module is estring.

it should have a function called concat that accepts two strings from lua and returns a concatenated string to lua.

it should have a function called replace that accepts three strings from lua and returns to lua the first string with all instances of the second string replaced with the third thing.

it should have a function called trim that removes whitespace from both sides of a string and returns it to lua.

it should have a function called split that accepts two strings from lua, an input string and a delimiter string, and returns a table to lua with values from the first string split by the delimiter

it should have a function called join that accepts a table from lua, and returns a string to lua with all strings in the table concatenated.

it should have a function called padStart that accepts two strings from lua, pads the current string with another string (multiple times, if needed) until the resulting string reaches the given length, and returns the result to lua.

it should have a function called padEnd that accepts two strings from lua, pads the current string with another string (multiple times, if needed) until the resulting string reaches the given length (the padding is applied from the end of the current string), and returns the result to lua.

it should have a function called formatNum that a string from lua, adds a comma every third character starting from the end, and returns the result to lua.
```

Then when it used std::string anyway:

```
it must always use const char* instead of std::string
```

Then after it didn't understand how to return to Lua:

```
instead of returning a result in every function, use lua_pushlstring
```

Some add-ons

```
adjust the estring_formatNum function so that it can accept either a number or a string from lua.
```

```
Add a function that receives a single variable from lua which is either a string or a number, representing a number of seconds, and formats it as hours:minutes:seconds. If hours are zero, remove them. Return the string to lua
```
