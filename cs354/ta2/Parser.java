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

	private void match(Token t) throws SyntaxException {
		scanner.match(t);
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

	private NodeRelop parseRelop() throws SyntaxException {
		Token current = curr();
		if (current.equals(Token.RELOPS)) {
			match(current);
			return new NodeRelop(pos(), current.lex());
		}
		return null;
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
		if (curr().equals(Token.OP_ADD)) {
			match(Token.OP_ADD);
			return new NodeAddop(pos(), Token.OP_ADD.lex());
		}
		if (curr().equals(Token.OP_SUB)) {
			match(Token.OP_SUB);
			return new NodeAddop(pos(), Token.OP_SUB.lex());
		}
		return null;
	}

	private NodeBoolExpr parseBoolExpr() throws SyntaxException {
		NodeExpr exprA = parseExpr();
		NodeRelop relop = parseRelop();
		NodeExpr exprB = parseExpr();
		return new NodeBoolExpr(exprA, relop, exprB);
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
		if (curr().equals(Token.KEY_BEGIN)) {
			match(Token.KEY_BEGIN);
			NodeBlock block = parseBlock();
			match(Token.KEY_END);
			return new NodeStmtBlock(block);
		} else if (curr().equals(Token.KEY_WHILE)) {
			match(Token.KEY_WHILE);
			NodeBoolExpr boolExpr = parseBoolExpr();
			match(Token.KEY_DO);
			NodeStmt stmt = parseStmt();
			return new NodeStmtWhile(boolExpr, stmt);
		} else if (curr().equals(Token.KEY_IF)) {
			match(Token.KEY_IF);
			NodeBoolExpr boolExpr = parseBoolExpr();
			match(Token.KEY_THEN);
			NodeStmt stmtTrue = parseStmt();
			NodeStmt stmtFalse = null;
			if (curr().equals(Token.KEY_ELSE)) {
				match(Token.KEY_ELSE);
				stmtFalse = parseStmt();
			}
			return new NodeStmtIf(boolExpr, stmtTrue, stmtFalse);
		} else if (curr().equals(Token.KEY_WRITE)) {
			match(Token.KEY_WRITE);
			NodeExpr expr = parseExpr();
			return new NodeStmtWr(expr);
		} else if (curr().equals(Token.KEY_READ)) {
			match(Token.KEY_READ);
			if (!curr().equals(Token.IDENT_GENERIC)) {
				throw new SyntaxException(pos(), Token.IDENT_GENERIC, curr());
			}
			String id = curr().lex();
			match(Token.IDENT_GENERIC);
			return new NodeStmtRd(pos(), id);
		} else {
			NodeAssn assn = parseAssn();
			return new NodeStmtAssn(assn);
		}
	}

	private NodeBlock parseBlock() throws SyntaxException {
		NodeStmt stmt = parseStmt();
		NodeBlock block = new NodeBlock(stmt, null);
		if (curr().equals(Token.OP_SEMICOLON)) {
			match(Token.OP_SEMICOLON);
			block.append(parseBlock());
		}
		return block;
	}

	private NodeProg parseProg() throws SyntaxException {
		NodeBlock block = parseBlock();
		return new NodeProg(block);
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
		NodeProg prog = parseProg();
		match("EOF");
		return prog;
	}

}
