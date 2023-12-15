/// <library version="2.0.0" src="https://github.com/thinknathan/defold-estring/archive/refs/tags/v2.0.0.zip" />
/// <reference path="./estring.d.ts" />

/** @noSelfInFile */

/**
 * Defold native extension with functions for string manipulation in Lua scripts.
 * @noResolution
 */
declare namespace estring {
	/**
	 * Joins strings or numbers and returns the result.
	 * @param args
	 */
	export function concat(...args: Array<string | number>): string;

	/**
	 * Formats a number as a string with options for precision, thousands separator, and decimal separator.
	 * @param input
	 * @param digitPrecision Default is 0.
	 * @param thousandsSeparator Default is "," (comma).
	 * @param decimalSeparator Default is "." (period).
	 */
	export function format_number(
		input: string | number,
		digitPrecision?: number,
		thousandsSeparator?: string,
		decimalSeparator?: string,
	): string;

	/**
	 * Formats a time value based on the provided format type, optionally using a specified delimiter.
	 * @param timeValue
	 * @param formatType The format type:
	 * 									 1: 12-hour without leading zero + without seconds.
	 * 									 2: 12-hour with leading zero + without seconds.
	 * 									 3: 12-hour with seconds.
	 *                   4: HH:MM:SS format. 5: HH:MM format. 6: MM:SS format.
	 * @param delimiter Default is ":" (colon).
	 */
	export function format_time(
		timeValue: number | string,
		formatType: 1 | 2 | 3 | 4 | 5 | 6,
		delimiter?: string,
	): string;
}
