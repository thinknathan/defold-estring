/// <library version="1.0.0" src="https://github.com/thinknathan/defold-estring/archive/refs/tags/v1.0.0.zip" />
/// <reference path="./estring.d.ts" />

/** @noSelfInFile */

/**
 * Functions for interacting with the eString native extension
 * @noResolution
 */
declare namespace estring {
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
}
