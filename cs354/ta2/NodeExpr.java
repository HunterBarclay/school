/**
 * Expression node.
 * 
 * <pre>
 * Grammar:
 * expr: term addop expr
 *     | term
 * </pre>
 */
public class NodeExpr extends Node {

	private NodeTerm term;
	private NodeAddop addop;
	private NodeExpr expr;

	/**
	 * @param term Left-hand operand.
	 * @param addop Operation.
	 * @param expr Right-hand operand.
	 */
	public NodeExpr(NodeTerm term, NodeAddop addop, NodeExpr expr) {
		this.term=term;
		this.addop=addop;
		this.expr=expr;
	}

	/**
	 * Appends expressions onto the right-hand side of this node.
	 * 
	 * @param expr Expression to append.
	 */
	public void append(NodeExpr expr) {
		if (this.expr==null) {
			this.addop=expr.addop;
			this.expr=expr;
			expr.addop=null;
		} else
			this.expr.append(expr);
	}

	@Override
	public double eval(Environment env) throws EvalException {
		return expr==null
			? term.eval(env)
			: addop.op(expr.eval(env),term.eval(env));
	}

	@Override
	public String code() {
		return (expr==null ? "" : expr.code()+addop.code())+term.code();
	}

}
