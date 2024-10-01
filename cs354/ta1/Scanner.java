// This class is a scanner for the program
// and programming language being interpreted.

import java.util.*;

public class Scanner {

	private String program; // source program being interpreted
	private int pos; // index of next char in program
	private Token token; // last/current scanned token

	// sets of various characters and lexemes
	private Set<String> whitespace = new HashSet<String>();
	private Set<String> digits = new HashSet<String>();
	private Set<String> letters = new HashSet<String>();
	private Set<String> legits = new HashSet<String>();
	private Set<String> keywords = new HashSet<String>();
	private Set<String> operators = new HashSet<String>();

	// initializers for previous sets

	private void fill(Set<String> s, char lo, char hi) {
		for (char c = lo; c <= hi; c++)
			s.add(c + "");
	}

	private void initWhitespace(Set<String> s) {
		s.add(" ");
		s.add("\n");
		s.add("\t");
	}

	private void initDigits(Set<String> s) {
		fill(s, '0', '9');
	}

	private void initLetters(Set<String> s) {
		fill(s, 'A', 'Z');
		fill(s, 'a', 'z');
	}

	private void initLegits(Set<String> s) {
		s.addAll(letters);
		s.addAll(digits);
	}

	private void initOperators(Set<String> s) {
		s.add("=");
		s.add("+");
		s.add("-");
		s.add("*");
		s.add("/");
		s.add("(");
		s.add(")");
		s.add(";");
	}

	private void initKeywords(Set<String> s) {
	}

	// constructor:
	// - squirrel-away source program
	// - initialize sets
	public Scanner(String program) {
		this.program = program;
		pos = 0;
		token = null;
		initWhitespace(whitespace);
		initDigits(digits);
		initLetters(letters);
		initLegits(legits);
		initKeywords(keywords);
		initOperators(operators);
	}

	// handy string-processing methods

	/**
	 * Determine if the scanner has reached the end of the program.
	 * 
	 * @return Has the end been reached.
	 */
	public boolean done() {
		return pos >= program.length();
	}

	/**
	 * Consume characters of the program that match a provided set.
	 * 
	 * @param s Set of characters to consume.
	 */
	private void many(Set<String> s) {
		while (!done() && s.contains(program.charAt(pos) + ""))
			pos++;
	}

	/**
	 * Moves the scanner one character past the target character.
	 * 
	 * @param c Target character.
	 */
	private void past(char c) {
		while (!done() && c != program.charAt(pos))
			pos++;
		if (!done() && c == program.charAt(pos))
			pos++;
	}

	// scan various kinds of lexeme

	/**
	 * Consume and tokenize next number in the program.
	 * 
	 * @return True if a number was tokenized successfully. Will always consume.
	 */
	private boolean nextNumber() {
		int old = pos;
		many(digits);
		if (program.charAt(pos) == '.') {
			pos++;
			many(digits);
			if (pos - old < 2) {
				System.err.println("illegal number at position " + old);
				return false;
			}
		}
		token = new Token("num", program.substring(old, pos));
		return true;
	}

	/**
	 * Consume and tokenize an identifier or keyword.
	 */
	private void nextKwId() {
		int old = pos;
		many(letters);
		many(legits);
		String lexeme = program.substring(old, pos);
		token = new Token((keywords.contains(lexeme) ? lexeme : "id"), lexeme);
	}

	/**
	 * Consume and tokenize an operator.
	 */
	private void nextOp() {
		int old = pos;
		pos = old + 2;
		if (!done()) {
			String lexeme = program.substring(old, pos);
			if (operators.contains(lexeme)) {
				token = new Token(lexeme); // two-char operator
				return;
			}
		}
		pos = old + 1;
		String lexeme = program.substring(old, pos);
		token = new Token(lexeme); // one-char operator
	}

	/**
	 * Consume a comment
	 * 
	 * @return True if a comment was consumed.
	 */
	private boolean matchComment() {
		if (pos + 2 < program.length() && program.substring(pos, pos + 2).equals("/*")) {
			pos += 2;
			// Skip everything until end of comment
			while (pos + 2 <= program.length() && !program.substring(pos, pos + 2).equals("*/"))
				pos++;
			
			pos += 2;
			return true;
		}
		return false;
	}

	/**
	 * Consumes and tokenizes the program. This method will find the next token, provided
	 * with the curr() method.
	 * 
	 * @return True if a token was found.
	 */
	public boolean next() {
		// Skip the whitespace
		many(whitespace);

		// Check for End of File
		if (done()) {
			token = new Token("EOF");
			return false;
		}

		// Check for comment
		if (matchComment()) {
			return next();
		}

		String c = program.charAt(pos) + "";
		if (digits.contains(c) || c.equals(".")) {
			if (!nextNumber()) {
				return next();
			}
		} else if (letters.contains(c)) {
			nextKwId();
		} else if (operators.contains(c)) {
			nextOp();
		} else {
			System.err.println("illegal character at position " + pos);
			pos++;
			return next();
		}
		return true;
	}

	/**
	 * Matches current token to a given token, advances tokenizer.
	 * 
	 * @param t Token to match to.
	 * @throws SyntaxException If current token is not equal to given token.
	 */
	public void match(Token t) throws SyntaxException {
		if (!t.equals(curr()))
			throw new SyntaxException(pos, t, curr());
		next();
	}

	/**
	 * Gets current token.
	 * 
	 * @return Current token in the program.
	 * @throws SyntaxException If current token is null.
	 */
	public Token curr() throws SyntaxException {
		if (token == null)
			throw new SyntaxException(pos, new Token("ANY"), new Token("EMPTY"));
		return token;
	}

	/**
	 * Current scanning location in the program.
	 * 
	 * @return Position of the scanner.
	 */
	public int pos() {
		return pos;
	}

	// for unit testing
	public static void main(String[] args) {
		try {
			Scanner scanner = new Scanner(args[0]);
			while (scanner.next())
				System.out.println(scanner.curr());
		} catch (SyntaxException e) {
			System.err.println(e);
		}
	}

}
