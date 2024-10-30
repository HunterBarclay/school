public class NodeProg extends Node {

	private NodeBlock block;

	public NodeProg(NodeBlock block) {
		this.block = block;
	}

	public double eval(Environment env) throws EvalException {
		return this.block.eval(env);
	}

	public String code() { return this.block.code(); }

	@Override
	public void loadEnvironment(Environment env) {
        this.block.loadEnvironment(env);
    }

	@Override
	protected Node[] children() {
        return new Node[]{ this.block };
	}

	@Override
	public String toString() {
        return "prog - block";
	}

}