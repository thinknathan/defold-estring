/** @noSelfInFile */

/**
 * Functions for interacting with the eString native extension
 */
declare namespace estring {
	/**
	 * Joins two strings
	 * @param first 
	 * @param second 
	 */
	export function concat(first: string, second:string): string
	/**
	 * Replace each occurance of `search` in `subject` with `replace` value
	 * @param subject 
	 * @param search 
	 * @param replace 
	 */
	export function replace(subject: string, search: string, replace: string): string
	/**
	 * Trim whitespace from input
	 * @param input 
	 */
	export function trim(input: string): string
	/**
	 * Create a table with values from `input`, split by `delimiter`
	 * @param input 
	 * @param delimiter 
	 */
	export function split(input: string, delimiter: string): string[]
	/**
	 * Joins values in a `table` into one string, with a `separator` added between
	 * @param table 
	 * @param separator 
	 */
	export function join(table: object, separator: string): string
	/**
	 * Adds `padding` to start of `input` string until it reaches specified `length`
	 * @param input 
	 * @param padding 
	 * @param length 
	 */
	export function pad_start(input: string, padding: string, length: number): string
	/**
	 * Adds `padding` to end of `input` string until it reaches specified `length`
	 * @param input 
	 * @param padding 
	 * @param length 
	 */
	export function pad_end(input: string, padding: string, length: number): string
	/**
	 * Adds comma every 3 digits as a thousands separator
	 * @param input 
	 */
	export function format_number(input: string | number): string
	/**
	 * Separates number of seconds into hours, minutes, and seconds with a colon in-between. Skips hours digits if they are zero.
	 * @param input 
	 */
	export function format_time(input: string | number): string
}
