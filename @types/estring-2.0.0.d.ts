/// <library version="2.0.0" src="https://github.com/thinknathan/defold-estring/archive/refs/tags/v2.0.0.zip" />
/// <reference path="./estring.d.ts" />

/** @noSelfInFile */

/**
 * eString native extension for concatenation, trimming, splitting, padding, formatting time, and formatting numbers
 * @noResolution
 */
declare namespace estring {
	/**
	 * Joins strings or numbers into a single string
	 */
	export function concat(...args: Array<string | number>): string;

	/**
	 * Prettily formats a number, such as `1000` becomes `1,000`
	 * @param input
	 * @param digitPrecision 0 by default
	 * @param thousandsSeparator comma by default
	 * @param decimalSeparator period by default
	 */
	export function format_number(
		input: string | number,
		digitPrecision?: number,
		thousandsSeparator?: string,
		decimalSeparator?: string,
	): string;

	/**
	 * Format a time value based on the specified format type
	 * @param timeValue The time value (number or string).
	 * @param formatType The format type: 1-12-hour without seconds, 2-12-hour with seconds,
	 *                   3-HH:MM:SS format, 4-HH:MM format, 5-MM:SS format
	 * @param delimiter Optional delimiter string (default is ":").
	 */
	export function format_time(
		timeValue: number | string,
		formatType: 1 | 2 | 3 | 4 | 5,
		delimiter?: string,
	): string;
}
