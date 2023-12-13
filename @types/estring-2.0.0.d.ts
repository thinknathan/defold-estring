/// <library version="2.0.0" src="https://github.com/thinknathan/defold-estring/archive/refs/tags/v2.0.0.zip" />
/// <reference path="./estring.d.ts" />

/** @noSelfInFile */

/**
 * Functions for interacting with the eString native extension
 * @noResolution
 */
declare namespace estring {
	/**
	 * Prettily formats a number, such as `1000` becomes `1,000`
	 * @param input
	 * @param roundNumber false by default
	 * @param thousandsSeparator comma by default
	 * @param decimalSeparator period by default
	 */
	function format_number(
		input: string | number,
		roundNumber?: boolean,
		thousandsSeparator?: string,
		decimalSeparator?: string,
	): string;
}
