/**
 * Used to print out evaluations of a node.
 */
public class NodeWr extends Node {

	private NodeExpr expr;

	/**
	 * @param expr Expression to evaulate and print.
	 */
	public NodeWr(NodeExpr expr) {
		this.expr=expr;
	}

	public double eval(Environment env) throws EvalException {
		double d=expr.eval(env);
		int i=(int) d;
		if (i==d)
			System.out.println(i);
		else
			System.out.println(d);
		return d;
	}

	public String code() {
		return "printf(\"%g\\n\","
			+"(double)("
			+expr.code()
			+"));";
	}

}
