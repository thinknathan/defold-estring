/// <library version="1.0.0" src="https://github.com/thinknathan/defold-estring/archive/refs/tags/v1.0.0.zip" />
/// <reference path="./estring.d.ts" />

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
	 * Replace each occurance of `search` in `subject` with `replace` value
	 * @param subject
	 * @param search
	 * @param replace
	 */
	export function replace(
		subject: string,
		search: string,
		replace: string,
	): string;

	/**
	 * Adds comma every 3 digits as a thousands separator
	 * @param input
	 */
	export function format_number(input: string | number): string;

	/**
	 * Joins values in a `table` into one string, with a `separator` added between
	 * @param table
	 * @param separator
	 */
	export function join(table: string[], separator: string): string;

	/**
	 * Separates number of seconds into hours, minutes, and seconds with a colon in-between. Skips hours digits if they are zero.
	 * @param input
	 */
	export function format_time(input: string | number): string;
}
