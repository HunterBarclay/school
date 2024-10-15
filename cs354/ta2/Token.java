/**
 * Stores a lexical token of a program. This both contains the type
 * of token it is, and the lexeme that makes up the token.
 * 
 * @author James Buffenbarger
 */
public class Token {

	private String token;
	private String lexeme;

	/**
	 * Create a token of a given type.
	 *
	 * @param token Type of token.
	 * @param lexeme Characters that make up the token.
	 */
	public Token(String token, String lexeme) {
		this.token=token;
		this.lexeme=lexeme;
	}

	/**
	 * Create a token. This makes both the type and lexeme of the token
	 * the same.
	 *
	 * @param token Type of, and characters making up the, token. 
	 */
	public Token(String token) {
		this(token,token);
	}

	/**
	 * Get the token type.
	 *
	 * @return Token type.
	 */
	public String tok() { return token; }

	/**
	 * Get the characters making up the token.
	 *
	 * @return Token characters.
	 */
	public String lex() { return lexeme; }

	/**
	 * Test if token type is equal to this one.
	 *
	 * @param t Token to compare to.
	 * @return True if both tokens have the same type.
	 */
	public boolean equals(Token t) {
		return token.equals(t.token);
	}

	@Override
	public String toString() {
		return "<"+tok()+","+lex()+">";
	}

}
