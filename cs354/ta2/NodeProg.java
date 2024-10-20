public class NodeProg extends Node {

	private NodeBlock block;

	public NodeProg(NodeBlock block) {
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
        return "prog - block";
	}

}