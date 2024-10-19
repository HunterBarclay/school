/**
 * Assignment node.
 * 
 * <pre>
 * Grammar:
 * assn: id '=' expr
 * <pre>
 */
public class NodeAssn extends Node {

	private String id;
	private NodeExpr expr;

	/**
	 * @param id Identifier to assign to.
	 * @param expr Expression to evaluation then assign to id.
	 */
	public NodeAssn(String id, NodeExpr expr) {
		this.id = id;
		this.expr = expr;
	}

	public double eval(Environment env) throws EvalException {
		return env.put(id, expr.eval(env));
	}

	public String code() {
		return id + "=" + expr.code();
	}

}
