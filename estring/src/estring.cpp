#include <dmsdk/sdk.h>
#include <cstring>
#include <ctime>
#include <cstdio>

static const char* get_string_arg(lua_State* L, int i) {
	if (lua_isnumber(L, i) || lua_isstring(L, i)) {
		return lua_tostring(L, i);
	} else {
		luaL_error(L, "Invalid argument at index %d. Expected string or number.", i);
		return nullptr;
	}
}

static int estring_concat(lua_State* L) {
	size_t resultLength = 0;

	int numArgs = lua_gettop(L);

	for (int i = 1; i <= numArgs; ++i) {
		const char* argStr = get_string_arg(L, i);
		resultLength += strlen(argStr);
	}

	char* resultBuffer = new char[resultLength + 1];
	resultBuffer[0] = '\0';

	for (int i = 1; i <= numArgs; ++i) {
		const char* argStr = get_string_arg(L, i);
		strcat(resultBuffer, argStr);
	}

	lua_pushstring(L, resultBuffer);
	delete[] resultBuffer;

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
	// Check if the first parameter is a number or string
	if (!lua_isnumber(L, 1) && !lua_isstring(L, 1)) {
		return luaL_error(L, "Invalid argument. Expected number or string.");
	}

	// Get the time from Lua
	lua_Number timeValue = lua_tonumber(L, 1);

	// Get format type
	int formatType = luaL_checkinteger(L, 2);

	// Get delimiter (default to colon)
	const char* delimiter = luaL_optstring(L, 3, ":");

	// Format the time based on the format type
	struct tm* timeInfo;
	time_t rawTime = static_cast<time_t>(timeValue);
	timeInfo = localtime(&rawTime);

	char formattedTime[15]; // Assuming the formatted time won't exceed 15 characters

	switch (formatType) {
		case 1:
			strftime(formattedTime, sizeof(formattedTime), "%l:%M %p", timeInfo);
			break;
		case 2:
			strftime(formattedTime, sizeof(formattedTime), "%I:%M %p", timeInfo);
			break;
		case 3:
			strftime(formattedTime, sizeof(formattedTime), "%I:%M:%S %p", timeInfo);
			break;
		case 4:
			strftime(formattedTime, sizeof(formattedTime), "%H:%M:%S", timeInfo);
			break;
		case 5:
			strftime(formattedTime, sizeof(formattedTime), "%H:%M", timeInfo);
			break;
		case 6:
			strftime(formattedTime, sizeof(formattedTime), "%M:%S", timeInfo);
			break;
		default:
			return luaL_error(L, "Invalid format type. Expected 1-6.");
	}

	// Replace default delimiter with the specified one
	for (char* p = formattedTime; *p; ++p) {
		if (*p == ':') {
			*p = *delimiter;
		}
	}

	lua_pushstring(L, formattedTime);

	return 1;
}

static int estring_formatNumber(lua_State* L) {
	char buffer[128];

	// Check if the first parameter is a number or string
	if (!lua_isnumber(L, 1) && !lua_isstring(L, 1)) {
		return luaL_error(L, "Invalid argument. Expected number or string.");
	}

	// Determine precision
	int precision = 0;
	if (lua_isnumber(L, 2)) {
		precision = luaL_checkinteger(L, 2);
	}

	// Get thousands separator (default to comma)
	const char* thousandsSeparator = ",";
	if (lua_isstring(L, 3)) {
		thousandsSeparator = lua_tostring(L, 3);
	}

	// Get decimal separator (default to period)
	const char* decimalSeparator = ".";
	if (lua_isstring(L, 4)) {
		decimalSeparator = lua_tostring(L, 4);
	}

	// Format the number with dynamic precision using dmSnPrintf
	int result = dmSnPrintf(buffer, sizeof(buffer), "%.*f", precision, lua_tonumber(L, 1));

	// Check for dmSnPrintf error
	if (result < 0 || result >= sizeof(buffer)) {
		return luaL_error(L, "Error formatting number in estring_formatNumber.");
	}

	// Add thousands separator every 3 digits (before the decimal point)
	char* decimalPoint = strchr(buffer, '.');
	if (decimalPoint == nullptr) {
		decimalPoint = buffer + strlen(buffer); // Point to the end if no decimal point
	}

	for (char* p = decimalPoint - 1; p > buffer; --p) {
		if ((decimalPoint - p) % 3 == 0) {
			memmove(p + 1, p, strlen(buffer) - (p - buffer) + 1);
			*p = *thousandsSeparator;
		}
	}

	// Replace default separators
	for (char* p = buffer; *p; ++p) {
		if (*p == ',' || *p == '.') {
			*p = (*p == ',') ? *thousandsSeparator : *decimalSeparator;
		}
	}

	lua_pushstring(L, buffer);

	return 1;
}

static const luaL_Reg estring_functions[] = {
	{ "format_time", estring_formatTime },
	{ "concat", estring_concat },
	{ "trim", estring_trim },
	{ "split", estring_split },
	{ "pad_start", estring_padStart },
	{ "pad_end", estring_padEnd },
	{ "format_number", estring_formatNumber },
	{ 0, 0 }
};

static void LuaInit(lua_State* L) {
	luaL_register(L, "estring", estring_functions);

	// Add 6 number constants corresponding to formatType
	lua_pushinteger(L, 1);
	lua_setfield(L, -2, "FORMAT_12H");

	lua_pushinteger(L, 2);
	lua_setfield(L, -2, "FORMAT_12H_LEADING_ZERO");

	lua_pushinteger(L, 3);
	lua_setfield(L, -2, "FORMAT_12H_LEADING_ZERO_WITH_SECONDS");

	lua_pushinteger(L, 4);
	lua_setfield(L, -2, "FORMAT_HH_MM_SS");

	lua_pushinteger(L, 5);
	lua_setfield(L, -2, "FORMAT_HH_MM");

	lua_pushinteger(L, 6);
	lua_setfield(L, -2, "FORMAT_MM_SS");

	lua_pop(L, 1);
}

static dmExtension::Result InitializeMyExtension(dmExtension::Params* params) {
	LuaInit(params->m_L);
	dmLogInfo("Registered %s Extension\n", "estring");
	return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(estring, "estring", 0, 0, InitializeMyExtension, 0, 0, 0)
