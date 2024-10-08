/**
 * <pre>
 * Grammar:
 * stmt: assn ';'
 * </pre>
 */
public class NodeStmt extends Node {

	private NodeAssn assn;

	/**
	 * @param assn Assignment.
	 */
	public NodeStmt(NodeAssn assn) {
		this.assn=assn;
	}

	public double eval(Environment env) throws EvalException {
		return assn.eval(env);
	}

	public String code() { return assn.code(); }

}
