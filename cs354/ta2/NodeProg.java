/**
 * Program node. The root node.
 * 
 * <pre>
 * Grammar:
 * prg: block
 * <pre>
 */
public class NodeProg extends Node {

	private NodeBlock block;

	/**
	 * Constructs a new program node.
	 * 
	 * @param block Block that contains the program's statements.
	 */
	public NodeProg(NodeBlock block) {
		this.block = block;
	}

	@Override
	public double eval(Environment env) throws EvalException {
		return this.block.eval(env);
	}

	@Override
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