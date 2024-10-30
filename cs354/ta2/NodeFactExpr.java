public class NodeFactExpr extends NodeFact {

	private NodeExpr expr;

	/**
	 * @param expr Expression wrapped in parentheses.
	 */
	public NodeFactExpr(NodeExpr expr) {
		this.expr=expr;
	}

	public double eval(Environment env) throws EvalException {
		return this.expr.eval(env);
	}

	public String code() { return "(" + this.expr.code() + ")"; }

	@Override
	public void loadEnvironment(Environment env) {
        this.expr.loadEnvironment(env);
    }

	@Override
	protected Node[] children() {
        return new Node[]{ this.expr };
	}

	@Override
	public String toString() {
        return "fact - '(' expr ')'";
	}

}
