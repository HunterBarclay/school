/**
 * Syntax error, encountered when tokens aren't valid within the Grammar.
 */
public class SyntaxException extends Exception {

	private int pos;
	private Token expected;
	private Token found;

	/**
	 * @param pos Position of the parse tree node in the program.
	 * @param expected The expected token.
	 * @param found The actual token.
	 */
	public SyntaxException(int pos, Token expected, Token found) {
		this.pos=pos;
		this.expected=expected;
		this.found=found;
	}

	public String toString() {
		return "syntax error"
			+", pos="+pos
			+", expected="+expected
			+", found="+found;
	}

}
