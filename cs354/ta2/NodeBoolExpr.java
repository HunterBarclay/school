public class NodeBoolExpr extends Node {

    public NodeExpr exprA, exprB;
    public NodeRelop relop;

    public NodeBoolExpr(NodeExpr exprA, NodeRelop relop, NodeExpr exprB) {
        this.exprA = exprA;
        this.relop = relop;
        this.exprB = exprB;
    }

    @Override
	public double eval(Environment env) throws EvalException {
		return this.relop.op(this.exprA.eval(env), this.exprB.eval(env));
	}

	@Override
	public String code() {
		return String.format("%s %s %s", this.exprA, this.relop, this.exprB);
	}

}
