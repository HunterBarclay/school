// This class, and its subclasses,
// collectively model parse-tree nodes.
// Each kind of node can be eval()-uated,
// and/or code()-generated.

public abstract class Node {

	/* Block UI ASCII characters cuz fun */
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
	 * Load the environment with any identifiers that are established. Originally
	 * this was done by interpreting the program, which would naturally assign the
	 * variables, but I've discovered that if a variable is defined in a block that
	 * is never used, the environment didn't know about it, and the generated C code
	 * would omit it.
	 * 
	 * @param env Environment to track variables.
	 */
	public abstract void loadEnvironment(Environment env);

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

	/**
	 * Construct a printable version of the parse tree.
	 * 
	 * @return Printable parse tree.
	 */
	public String tree() {
		StringBuilder builder = new StringBuilder();
		this.tree(builder, "");
		return builder.toString();
	}

	/**
	 * Builds a printable version of the parse tree.
	 * 
	 * @param builder String builder to store print contents.
	 * @param indent Current indent of the level being printed.
	 */
	protected void tree(StringBuilder builder, String indent) {
		Node[] children = this.children();
		if (children.length == 0) {
			builder.append(Node.UI_TOP_BOTTOM);
			builder.append(" ");
			builder.append(this.toString());
			builder.append("\n");
		} else {
			builder.append(Node.UI_TOP_CENTER);
			builder.append(" ");
			builder.append(this.toString());
			builder.append("\n");
		
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

		
	}

	/**
	 * Get all parse tree children of this node.
	 * 
	 * @return Children of this node.
	 */
	protected abstract Node[] children();

}
