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

	public boolean equals(Token... tokens) {
		for (Token t : tokens) {
			if (this.equals(t))
				return true;
		}
		return false;
	}

	@Override
	public String toString() {
		return "<"+tok()+","+lex()+">";
	}

	/**
	 * Just a lost of explicit token definitions.
	 */
	public static final Token OP_SEMICOLON = new Token(";");
	public static final Token OP_ADD = new Token("+");
	public static final Token OP_SUB = new Token("-");
	public static final Token OP_MUL = new Token("*");
	public static final Token OP_DIV = new Token("/");
	public static final Token OP_LT = new Token("<");
	public static final Token OP_LTE = new Token("<=");
	public static final Token OP_GT = new Token(">");
	public static final Token OP_GTE = new Token(">=");
	public static final Token OP_NEQ = new Token("<>");
	public static final Token OP_EQ = new Token("==");
	public static final Token OP_ASSN = new Token("=");
	public static final Token OP_PAREN_OPEN = new Token("(");
	public static final Token OP_PAREN_CLOSE = new Token(")");
	public static final Token OP_NEG = new Token("-");

	public static final Token KEY_READ = new Token("rd");
	public static final Token KEY_WRITE = new Token("wr");
	public static final Token KEY_IF = new Token("if");
	public static final Token KEY_THEN = new Token("then");
	public static final Token KEY_ELSE = new Token("else");
	public static final Token KEY_WHILE = new Token("while");
	public static final Token KEY_DO = new Token("do");
	public static final Token KEY_BEGIN = new Token("begin");
	public static final Token KEY_END = new Token("end");

	public static final Token IDENT_GENERIC = new Token("id");
	public static final Token NUM_GENERIC = new Token("num");

	public static final Token[] RELOPS = {
		Token.OP_LT,
		Token.OP_LTE,
		Token.OP_GT,
		Token.OP_GTE,
		Token.OP_NEQ,
		Token.OP_EQ,
	};

	public static final Token[] ADDOPS = {
		Token.OP_ADD, Token.OP_SUB
	};

	public static final Token[] MULOPS = {
		Token.OP_MUL, Token.OP_DIV
	};

}
