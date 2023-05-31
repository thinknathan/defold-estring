# defold-estring

Defold extension implementing a variety of string-related utilities.

You may prefer [defstring](https://github.com/subsoap/defstring) for a more robust implementation.

## Installation

- Edit game.project
- Add dependency `https://github.com/thinknathan/defold-estring/archive/main.zip`

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
local joined = estring.join(arr)
print(joined)  --> Output: HelloworldLua

-- Example usage of the 'padStart' function
local paddedStart = estring.padStart("hello", "*", 10)
print(paddedStart)  --> Output: *****hello

-- Example usage of the 'padEnd' function
local paddedEnd = estring.padEnd("hello", "*", 10)
print(paddedEnd)  --> Output: hello*****

-- Example usage of the 'formatNum' function
local formattedNum = estring.formatNum("1234567")
print(formattedNum)  --> Output: 1,234,567
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
it must always use const char* instead of const char*
```

Then after it didn't understand how to return to Lua:

```
instead of returning a result in every function, use lua_pushlstring
```
