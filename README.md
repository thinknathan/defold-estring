<img src="_docs/def-estring-x1.png" alt="Def-eString">

# Def-eString

[![Build with bob](https://github.com/thinknathan/defold-estring/actions/workflows/bob.yml/badge.svg)](https://github.com/thinknathan/defold-estring/actions/workflows/bob.yml)

This Defold native extension implements functions for string manipulation in Lua scripts.

## API

- `estring.concat(...)`
- Joins strings or numbers and returns the result.

- `estring.trim(str)`
- Removes leading and trailing whitespace from a string.

- `estring.split(str, delimiter)`
- Splits a string into parts using a specified delimiter and returns them in a table.

- `estring.pad_start(str, padStr, targetLength)`
- Pads the start of a string with a specified padding string to reach a target length.

- `estring.pad_end(str, padStr, targetLength)`
- Pads the end of a string with a specified padding string to reach a target length.

- `estring.format_time(timeValue, formatType, delimiter)`
- Formats a time value based on the provided format type, optionally using a specified delimiter.

- `estring.format_number(number, precision, thousandsSeparator, decimalSeparator)`
- Formats a number as a string with options for precision, thousands separator, and decimal separator.

## Background

In Lua, strings are immutable. Every modification you make to a string value causes a new string object to be allocated.

Example:

```lua
local first = 'the '
local second = 'lazy '
local third = 'dog'
local sentence = first .. second .. third -- 'the lazy dog'
-- An intermediate string 'the lazy ' is allocated when first and second are joined
```

This library aims to avoid the creation of intermediate Lua strings by doing the work in C++ and only returning the final result to Lua.

```lua
local first = 'the '
local second = 'lazy '
local third = 'dog'
local sentence = estring.concat(first, second, third) -- 'the lazy dog'
-- No intermediate string is allocated
```

## Installation

1. Edit game.project
2. Add dependency `https://github.com/thinknathan/defold-estring/archive/main.zip` for the current version
   - Or add a specific [release](https://github.com/thinknathan/defold-estring/releases)

### TypeScript Definitions

This extension includes types for use with [TypeScript + Defold](https://ts-defold.dev/).

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
-- concat
-- Joins strings or numbers and returns the result.
local result_concat = estring.concat("Hello, ", "world", 123, "!")
print(result_concat) -- Output: Hello, world123!

-- trim
-- Removes leading and trailing whitespace from a string.
local result_trim = estring.trim("   This is a string with spaces   ")
print(result_trim) -- Output: This is a string with spaces

-- split
-- Splits a string into parts using a specified delimiter and returns them in a table.
local result_split = estring.split("apple,orange,banana", ",")
for i, value in ipairs(result_split) do
    print(i, value)
end
-- Output:
-- 1   apple
-- 2   orange
-- 3   banana

-- pad_start
-- Pads the start of a string with a specified padding string to reach a target length.
local result_pad_start = estring.pad_start("42", "0", 5)
print(result_pad_start) -- Output: 00042

-- pad_end
-- Pads the end of a string with a specified padding string to reach a target length.
local result_pad_end = estring.pad_end("42", "0", 5)
print(result_pad_end) -- Output: 42000

-- format_time
-- Formats a time value based on the provided format type, optionally using a specified delimiter.
local result_format_time = estring.format_time(os.time(), 2, "-")
print(result_format_time) -- Output: 12-45-30 PM
-- Parameters:
-- timeValue: (number or string) The time value to format. It can be either a numeric timestamp or a string representing a date and time.
-- formatType: (constant) Specifies the desired format type:
-- 	estring.FORMAT_12H: "h:mm AM/PM"
-- 	estring.FORMAT_12H_LEADING_ZERO: "hh:mm AM/PM"
-- 	estring.FORMAT_12H_LEADING_ZERO_WITH_SECONDS: "hh:mm:ss AM/PM"
-- 	estring.FORMAT_HH_MM_SS: "HH:mm:ss"
-- 	estring.FORMAT_HH_MM: "HH:mm"
-- 	estring.FORMAT_MM_SS: "mm:ss"
-- delimiter: (string, optional) The delimiter used in the formatted time. Default is ":".

-- format_number
-- Formats a number as a string with options for precision, thousands separator, and decimal separator.
local result_format_number = estring.format_number(1234567.89, 2, ",", ".")
print(result_format_number) -- Output: 1,234,567.89
-- Parameters:
-- numberValue: (number or string) The number to format.
-- precision: (integer, optional) The number of decimal places. Default is 0.
-- thousandsSeparator: (string, optional) The character used as a separator for thousands. Default is ",".
-- decimalSeparator: (string, optional) The character used as a decimal point. Default is ".".
```

## Alternatives

[DefString](https://github.com/subsoap/defstring) is a pure Lua implementation of string manipulation.
