/** @noSelfInFile */

/**
 * Functions for interacting with the eString native extension
 * @noResolution
 */
declare namespace estring {
	/**
	 * Joins two strings
	 * @param first
	 * @param second
	 */
	export function concat(first: string, second: string): string;

	/**
	 * Trim whitespace from input
	 * @param input
	 */
	export function trim(input: string): string;

	/**
	 * Create a table with values from `input`, split by `delimiter`
	 * @param input
	 * @param delimiter
	 */
	export function split(input: string, delimiter: string): string[];

	/**
	 * Adds `padding` to start of `input` string until it reaches specified `length`
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
	 * Adds `padding` to end of `input` string until it reaches specified `length`
	 * @param input
	 * @param padding
	 * @param length
	 */
	export function pad_end(
		input: string,
		padding: string,
		length: number,
	): string;

	/**
	 * Separates number of seconds into hours, minutes, and seconds with a colon in-between. Skips hours digits if they are zero.
	 * @param input
	 */
	export function format_time(input: string | number): string;
}
