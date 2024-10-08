// This class is a recursive-descent parser,
// modeled after the programming language's grammar.
// It constructs and has-a Scanner for the program
// being parsed.

public class Parser {

	private Scanner scanner;

	/**
	 * Match the next token to a provided simple token.
	 * 
	 * @param s Simple token (both token type and lexeme).
	 * @throws SyntaxException If the next token doesn't match.
	 */
	private void match(String s) throws SyntaxException {
		scanner.match(new Token(s));
	}

	/**
	 * Get the last scanned token.
	 * 
	 * @return Last scanned token.
	 * @throws SyntaxException If scanner doesn't have a token.
	 */
	private Token curr() throws SyntaxException {
		return scanner.curr();
	}

	/**
	 * Current scanner location in the program.
	 * @return Program location.
	 */
	private int pos() {
		return scanner.pos();
	}

	/**
	 * Parses tokens into a multiplication operation node.
	 * 
	 * @return Multipliciation operation node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	private NodeMulop parseMulop() throws SyntaxException {
		if (curr().equals(new Token("*"))) {
			match("*");
			return new NodeMulop(pos(), "*");
		}
		if (curr().equals(new Token("/"))) {
			match("/");
			return new NodeMulop(pos(), "/");
		}
		return null;
	}

	/**
	 * Parses tokens into a addition operation node.
	 * 
	 * @return Addition operation node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	private NodeAddop parseAddop() throws SyntaxException {
		if (curr().equals(new Token("+"))) {
			match("+");
			return new NodeAddop(pos(), "+");
		}
		if (curr().equals(new Token("-"))) {
			match("-");
			return new NodeAddop(pos(), "-");
		}
		return null;
	}

	/**
	 * Parses tokens into a factor node.
	 * 
	 * @return Factor node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	private NodeFact parseFact() throws SyntaxException {
		if (curr().equals(new Token("("))) {
			match("(");
			NodeExpr expr = parseExpr();
			match(")");
			return new NodeFactExpr(expr);
		}
		if (curr().equals(new Token("id"))) {
			Token id = curr();
			match("id");
			return new NodeFactId(pos(), id.lex());
		}
		if (curr().equals(new Token("-"))) {
			match("-");
			return new NodeFactNeg(parseFact());
		}
		Token num = curr();
		match("num");
		return new NodeFactNum(num.lex());
	}

	/**
	 * Parses tokens into a term node.
	 * 
	 * @return Term node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	private NodeTerm parseTerm() throws SyntaxException {
		NodeFact fact = parseFact();
		NodeMulop mulop = parseMulop();
		if (mulop == null)
			return new NodeTerm(fact, null, null);
		NodeTerm term = parseTerm();
		term.append(new NodeTerm(fact, mulop, null));
		return term;
	}

	/**
	 * Parses tokens into a expression node.
	 * 
	 * @return Expression node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	private NodeExpr parseExpr() throws SyntaxException {
		NodeTerm term = parseTerm();
		NodeAddop addop = parseAddop();
		if (addop == null)
			return new NodeExpr(term, null, null);
		NodeExpr expr = parseExpr();
		expr.append(new NodeExpr(term, addop, null));
		return expr;
	}

	/**
	 * Parses tokens into a assignment node.
	 * 
	 * @return Assignment node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	private NodeAssn parseAssn() throws SyntaxException {
		Token id = curr();
		match("id");
		match("=");
		NodeExpr expr = parseExpr();
		NodeAssn assn = new NodeAssn(id.lex(), expr);
		return assn;
	}

	/**
	 * Parses tokens into a statement node.
	 * 
	 * @return Statement node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	private NodeStmt parseStmt() throws SyntaxException {
		NodeAssn assn = parseAssn();
		match(";");
		NodeStmt stmt = new NodeStmt(assn);
		return stmt;
	}

	/**
	 * Parses a program into a root parse tree node.
	 * 
	 * @return Root parse tree node.
	 * @throws SyntaxException If token doesn't match grammar.
	 */
	public Node parse(String program) throws SyntaxException {
		scanner = new Scanner(program);
		scanner.next();
		NodeStmt stmt = parseStmt();
		match("EOF");
		return stmt;
	}

}
