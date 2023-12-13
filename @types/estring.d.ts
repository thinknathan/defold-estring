/** @noSelfInFile */

/**
 * eString native extension for concatenation, trimming, splitting, padding, formatting time, and formatting numbers
 * @noResolution
 */
declare namespace estring {
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
}
