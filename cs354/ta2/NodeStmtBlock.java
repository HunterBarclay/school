public class NodeStmtBlock extends NodeStmt {
    private NodeBlock block;

	public NodeStmtBlock(NodeBlock block) {
		this.block = block;
	}

	public double eval(Environment env) throws EvalException {
		return block.eval(env);
	}

	public String code() { return block.code(); }

	@Override
	protected Node[] children() {
        return new Node[]{ this.block };
	}

	@Override
	public String toString() {
        return "stmt - 'begin' block 'end'";
	}

}
