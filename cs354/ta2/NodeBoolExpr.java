/**
 * Boolean Expression node.
 * 
 * <pre>
 * Grammar:
 * boolexpr: expr relop expr
 * <pre>
 */
public class NodeBoolExpr extends Node {

    public NodeExpr exprA, exprB;
    public NodeRelop relop;

	/**
	 * Construct new boolean expression.
	 * 
	 * @param exprA Left-hand expression.
	 * @param relop Relation to check between the two expressions.
	 * @param exprB Right-hand expression.
	 */
    public NodeBoolExpr(NodeExpr exprA, NodeRelop relop, NodeExpr exprB) {
        this.exprA = exprA;
        this.relop = relop;
        this.exprB = exprB;
    }

	@Override
	public void loadEnvironment(Environment env) {
        this.exprA.loadEnvironment(env);
		this.exprB.loadEnvironment(env);
		this.relop.loadEnvironment(env);
    }

    @Override
	public double eval(Environment env) throws EvalException {
		return this.relop.op(this.exprA.eval(env), this.exprB.eval(env));
	}

	@Override
	public String code() {
		return String.format("%s %s %s", this.exprA.code(), this.relop.code(), this.exprB.code());
	}

    @Override
	protected Node[] children() {
		return new Node[]{ this.exprA, this.relop, this.exprB };
	}

	@Override
	public String toString() {
        return "boolexpr - expr relop expr";
	}

}
