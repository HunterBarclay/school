// This class, and its subclasses,
// collectively model parse-tree nodes.
// Each kind of node can be eval()-uated,
// and/or code()-generated.

public abstract class Node {

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

}
