/** @noSelfInFile */

/**
 * Defold native extension with functions for string manipulation in Lua scripts.
 * @noResolution
 */
declare namespace estring {
	/**
	 * Removes leading and trailing whitespace from a string.
	 * @param input String to trim.
	 */
	export function trim(input: string): string;

	/**
	 * Splits a string into parts using a specified delimiter and returns them in a table.
	 * @param input
	 * @param delimiter
	 */
	export function split(input: string, delimiter: string): string[];

	/**
	 * Pads the start of a string with a specified padding string to reach a target length.
	 * @param input
	 * @param padding
	 * @param length
	 */
	export function pad_start(
		input: string,
		padding: string,
		length: number,
	): string;

	/**
	 * Pads the end of a string with a specified padding string to reach a target length.
	 * @param input
	 * @param padding
	 * @param length
	 */
	export function pad_end(
		input: string,
		padding: string,
		length: number,
	): string;
}
