# defold-estring

Defold extension implementing a variety of string-related utilities.

You may prefer [DefString](https://github.com/subsoap/defstring) for a more robust implementation.

## Installation

- Edit game.project
- Add dependency `https://github.com/thinknathan/defold-estring/archive/main.zip` for the current version
- Or add a specific [release](https://github.com/thinknathan/defold-estring/releases)

## Usage

```lua
-- Example usage of the 'concat' function
local concatenated = estring.concat("Hello", " world!")
print(concatenated)  --> Output: Hello world!

-- Example usage of the 'replace' function
local replaced = estring.replace("Hello, world!", "world", "Lua")
print(replaced)  --> Output: Hello, Lua!

-- Example usage of the 'trim' function
local trimmed = estring.trim("   Hello, world!   ")
print(trimmed)  --> Output: Hello, world!

-- Example usage of the 'split' function
local result = estring.split("Hello,world,Lua", ",")
for i, v in ipairs(result) do
    print(v)
end
-- Output:
-- Hello
-- world
-- Lua

-- Example usage of the 'join' function
local arr = { "Hello", "world", "Lua" }
local joined = estring.join(arr, "")
print(joined)  --> Output: HelloworldLua

local joined2 = estring.join(arr, ", ")
print(joined2)  --> Output: Hello, world, Lua

-- Example usage of the 'pad_start' function
local paddedStart = estring.pad_start("hello", "*", 10)
print(paddedStart)  --> Output: *****hello

-- Example usage of the 'pad_end' function
local paddedEnd = estring.pad_end("hello", "*", 10)
print(paddedEnd)  --> Output: hello*****

-- Example usage of the 'format_number' function
local formattedNum1 = estring.format_number(1234567890)
print(formattedNum1)  -- Output: 1,234,567,890

local formattedNum2 = estring.format_number("9876543210")
print(formattedNum2)  -- Output: 9,876,543,210

-- Example usage of the 'format_time' function
local timeStr1 = estring.format_time(3661)
print(timeStr1)  -- Output: 01:01:01

local timeStr2 = estring.format_time("12345")
print(timeStr2)  -- Output: 03:25:45

local timeStr3 = estring.format_time(59)
print(timeStr3)  -- Output: 00:59
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
