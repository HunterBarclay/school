public class NodeStmtAssn extends NodeStmt {

    private NodeAssn assn;

	/**
	 * @param assn Assignment.
	 */
	public NodeStmtAssn(NodeAssn assn) {
		this.assn=assn;
	}

	@Override
	public double eval(Environment env) throws EvalException {
		return this.assn.eval(env);
	}

	@Override
	public String code() { return this.assn.code() + ";"; }

	@Override
	public void loadEnvironment(Environment env) {
		this.assn.loadEnvironment(env);
    }

	@Override
	protected Node[] children() {
        return new Node[]{ this.assn };
	}

	@Override
	public String toString() {
        return "stmt - assn";
	}
    
}
