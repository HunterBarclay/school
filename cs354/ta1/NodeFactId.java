public class NodeFactId extends NodeFact {

	private String id;

	/**
	 * @param pos Position of the node.
	 * @param id Identifier.
	 */
	public NodeFactId(int pos, String id) {
		this.pos=pos;
		this.id=id;
	}

	public double eval(Environment env) throws EvalException {
		return env.get(pos,id);
	}

	public String code() { return id; }

}
