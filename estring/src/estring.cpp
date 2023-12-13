#include <dmsdk/sdk.h>
#include <cstring>

static int estring_concat(lua_State* L) {
    const char* str1 = luaL_checkstring(L, 1);
    const char* str2 = luaL_checkstring(L, 2);
    size_t str1Length = strlen(str1);
    size_t str2Length = strlen(str2);
    size_t resultLength = str1Length + str2Length;
    char* result = new char[resultLength + 1];
    strcpy(result, str1);
    strcpy(result + str1Length, str2);
    lua_pushlstring(L, result, resultLength);
    delete[] result;
    return 1;
}

static int estring_trim(lua_State* L) {
    const char* str = luaL_checkstring(L, 1);
    const char* whitespace = " \t\n\r\f\v";
    size_t strLength = strlen(str);
    const char* start = str;
    const char* end = str + strLength - 1;
    while (start <= end && strchr(whitespace, *start)) {
        ++start;
    }
    while (end > start && strchr(whitespace, *end)) {
        --end;
    }
    size_t resultLength = end - start + 1;
    char* result = new char[resultLength + 1];
    memcpy(result, start, resultLength);
    result[resultLength] = '\0';
    lua_pushlstring(L, result, resultLength);
    delete[] result;
    return 1;
}

static int estring_split(lua_State* L) {
    const char* str = luaL_checkstring(L, 1);
    const char* delimiter = luaL_checkstring(L, 2);
    size_t strLength = strlen(str);
    size_t delimiterLength = strlen(delimiter);
    size_t count = 1;
    const char* pos = str;
    while ((pos = strstr(pos, delimiter)) != nullptr) {
        pos += delimiterLength;
        ++count;
    }
    lua_newtable(L);
    pos = str;
    for (size_t i = 1; i <= count; ++i) {
        const char* found = strstr(pos, delimiter);
        size_t segmentLength = found ? found - pos : strLength - (pos - str);
        char* segment = new char[segmentLength + 1];
        strncpy(segment, pos, segmentLength);
        segment[segmentLength] = '\0';
        lua_pushstring(L, segment);
        lua_rawseti(L, -2, i);
        delete[] segment;
        pos = found + delimiterLength;
    }
    return 1;
}

static int estring_join(lua_State* L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    const char* delimiter = luaL_checkstring(L, 2); // Get the delimiter string from Lua

    lua_pushnil(L);
    size_t totalLength = 0;
    while (lua_next(L, 1) != 0) {
        if (lua_type(L, -1) == LUA_TSTRING) {
            size_t segmentLength;
            const char* segment = lua_tolstring(L, -1, &segmentLength);
            totalLength += segmentLength;
        }
        lua_pop(L, 1);
    }

    // Add the length of the delimiter for each string in the table
    size_t delimiterLength = strlen(delimiter);
    totalLength += (delimiterLength * (lua_objlen(L, 1) - 1));

    char* result = new char[totalLength + 1];
    char* current = result;

    lua_pushnil(L);
    bool firstString = true; // Flag to skip adding delimiter before the first string
    while (lua_next(L, 1) != 0) {
        if (lua_type(L, -1) == LUA_TSTRING) {
            size_t segmentLength;
            const char* segment = lua_tolstring(L, -1, &segmentLength);
            if (!firstString) {
                strncpy(current, delimiter, delimiterLength);
                current += delimiterLength;
            }
            strncpy(current, segment, segmentLength);
            current += segmentLength;
            firstString = false;
        }
        lua_pop(L, 1);
    }

    *current = '\0';
    lua_pushlstring(L, result, totalLength);
    delete[] result;
    return 1;
}

static int estring_padStart(lua_State* L) {
    const char* str = luaL_checkstring(L, 1);
    const char* padStr = luaL_checkstring(L, 2);
    size_t targetLength = luaL_checkinteger(L, 3);
    size_t strLength = strlen(str);
    if (targetLength <= strLength) {
        lua_pushstring(L, str);
        return 1;
    }
    size_t padStrLength = strlen(padStr);
    size_t paddingLength = targetLength - strLength;
    size_t padCount = paddingLength / padStrLength;
    size_t remainder = paddingLength % padStrLength;
    size_t resultLength = targetLength;
    char* result = new char[resultLength + 1];
    char* current = result;
    for (size_t i = 0; i < padCount; ++i) {
        strncpy(current, padStr, padStrLength);
        current += padStrLength;
    }
    strncpy(current, padStr, remainder);
    current += remainder;
    strncpy(current, str, strLength);
    current[strLength] = '\0';
    lua_pushstring(L, result);
    delete[] result;
    return 1;
}

static int estring_padEnd(lua_State* L) {
    const char* str = luaL_checkstring(L, 1);
    const char* padStr = luaL_checkstring(L, 2);
    size_t targetLength = luaL_checkinteger(L, 3);
    size_t strLength = strlen(str);
    if (targetLength <= strLength) {
        lua_pushstring(L, str);
        return 1;
    }
    size_t padStrLength = strlen(padStr);
    size_t paddingLength = targetLength - strLength;
    size_t padCount = paddingLength / padStrLength;
    size_t remainder = paddingLength % padStrLength;
    size_t resultLength = targetLength;
    char* result = new char[resultLength + 1];
    char* current = result;
    strncpy(current, str, strLength);
    current += strLength;
    for (size_t i = 0; i < padCount; ++i) {
        strncpy(current, padStr, padStrLength);
        current += padStrLength;
    }
    strncpy(current, padStr, remainder);
    current += remainder;
    *current = '\0';
    lua_pushstring(L, result);
    delete[] result;
    return 1;
}

static int estring_formatTime(lua_State* L) {
    int seconds;

    if (lua_type(L, 1) == LUA_TNUMBER) {
        seconds = (int)lua_tonumber(L, 1);
    } else if (lua_type(L, 1) == LUA_TSTRING) {
        const char* str = lua_tostring(L, 1);
        seconds = atoi(str);
    } else {
        return luaL_error(L, "Invalid argument. Expected number or string.");
    }

    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds = seconds % 60;

    char result[64];
    if (hours > 0) {
        snprintf(result, sizeof(result), "%02d:%02d:%02d", hours, minutes, seconds);
    } else {
        snprintf(result, sizeof(result), "%02d:%02d", minutes, seconds);
    }

    lua_pushstring(L, result);
    return 1;
}

static int estring_formatNumber(lua_State* L) {
    const char* input;
    char* buffer = nullptr; // Added buffer variable

    if (lua_type(L, 1) == LUA_TSTRING) {
        input = lua_tostring(L, 1);
    } else if (lua_type(L, 1) == LUA_TNUMBER) {
        double number = lua_tonumber(L, 1);

        // Check if rounding is requested
        bool roundNumber = false;
        if (lua_type(L, 2) == LUA_TBOOLEAN) {
            roundNumber = (lua_toboolean(L, 2) != 0);  // Convert boolean to integer
        }

        // Get thousands separator (default to comma)
        const char* thousandsSeparator = ",";
        if (lua_type(L, 3) == LUA_TSTRING) {
            thousandsSeparator = lua_tostring(L, 3);
        }

        // Get decimal separator (default to period)
        const char* decimalSeparator = ".";
        if (lua_type(L, 4) == LUA_TSTRING) {
            decimalSeparator = lua_tostring(L, 4);
        }

        // Format the number
        if (roundNumber) {
            asprintf(&buffer, "%'f", number);  // Allocates memory using asprintf
        } else {
            asprintf(&buffer, "%f", number);  // Allocates memory using asprintf
        }

        // Replace default separators
        for (char* p = buffer; *p; ++p) {
            if (*p == ',') {
                *p = *thousandsSeparator;
            } else if (*p == '.') {
                *p = *decimalSeparator;
            }
        }

        input = buffer;
    } else {
        return luaL_error(L, "Invalid argument. Expected string or number.");
    }

    lua_pushstring(L, input);

    // Free the allocated buffer
    free(buffer);

    return 1;
}

static const luaL_Reg estring_functions[] = {
    { "format_time", estring_formatTime },
    { "concat", estring_concat },
    { "trim", estring_trim },
    { "split", estring_split },
    { "join", estring_join },
    { "pad_start", estring_padStart },
    { "pad_end", estring_padEnd },
    { "format_number", estring_formatNumber },
    { 0, 0 }
};

static void LuaInit(lua_State* L) {
    int top = lua_gettop(L);
    luaL_register(L, "estring", estring_functions);
    lua_pop(L, 1);
}

static dmExtension::Result InitializeMyExtension(dmExtension::Params* params) {
    LuaInit(params->m_L);
	dmLogInfo("Registered %s Extension\n", "estring");
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(estring, "estring", 0, 0, InitializeMyExtension, 0, 0, 0)
