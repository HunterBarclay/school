public class NodeStmtAssn extends NodeStmt {

    private NodeAssn assn;

	/**
	 * @param assn Assignment.
	 */
	public NodeStmtAssn(NodeAssn assn) {
		this.assn=assn;
	}

	public double eval(Environment env) throws EvalException {
		return assn.eval(env);
	}

	public String code() { return assn.code() + ";"; }

	@Override
	protected Node[] children() {
        return new Node[]{ this.assn };
	}

	@Override
	public String toString() {
        return "stmt - assn";
	}
    
}
