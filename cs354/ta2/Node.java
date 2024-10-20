// This class, and its subclasses,
// collectively model parse-tree nodes.
// Each kind of node can be eval()-uated,
// and/or code()-generated.

public abstract class Node {

	public static final String UI_TOP_LEFT      = "┌";
	public static final String UI_TOP_RIGHT     = "┐";
	public static final String UI_BOTTOM_LEFT   = "└";
	public static final String UI_BOTTOM_RIGHT  = "┘";
	public static final String UI_TOP_BOTTOM    = "─";
	public static final String UI_LEFT_RIGHT    = "│";
	public static final String UI_CENTER_LEFT   = "├";
	public static final String UI_CENTER_RIGHT  = "┤";
	public static final String UI_TOP_CENTER    = "┬";
	public static final String UI_BOTTOM_CENTER = "┴";

	protected int pos=0;

	/**
	 * Evaluate a given node, determine the result or throw evaluation exception.
	 * 
	 * @param env Environment to evaluate node in.
	 * @return The result of the node.
	 * @throws EvalException If the node is unable to evaluate.
	 */
	public double eval(Environment env) throws EvalException {
		throw new EvalException(pos,"cannot eval() node!");
	}

	/**
	 * Generates the C code for this node.
	 * 
	 * @return Generated C code.
	 */
	public String code() { return ""; }

	public String tree() {
		StringBuilder builder = new StringBuilder();
		this.tree(builder, "");
		return builder.toString();
	}

	protected void tree(StringBuilder builder, String indent) {
		builder.append(Node.UI_TOP_CENTER);
		builder.append(" ");
		builder.append(this.toString());
		builder.append("\n");
		Node[] children = this.children();
		if (children.length == 0) {
			return;
		}
		String midwayIndent = String.format("%s%s", indent, Node.UI_LEFT_RIGHT);
		for (int i = 0; i < children.length - 1; ++i) {
			builder.append(indent);
			builder.append(Node.UI_CENTER_LEFT);
			children[i].tree(builder, midwayIndent);
		}
		String endIndent = String.format("%s ", indent);
		builder.append(indent);
		builder.append(Node.UI_BOTTOM_LEFT);
		children[children.length - 1].tree(builder, endIndent);
	}

	protected abstract Node[] children();

}
