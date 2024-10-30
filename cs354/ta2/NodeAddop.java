/**
 * Node for an add operation.
 * 
 * <pre>
 * Grammar:
 * addop: '+'
 * 		| '-'
 * </pre>
 */
public class NodeAddop extends Node {

	private String addop;

	/**
	 * Create an add operation node.
	 * 
	 * @param pos Position of the node.
	 * @param addop Operation specifier.
	 */
	public NodeAddop(int pos, String addop) {
		this.pos=pos;
		this.addop=addop;
	}

	/**
	 * Evaluation the add operation.
	 * 
	 * @param o1 Operand 1.
	 * @param o2 Operand 2.
	 * @return Evaulation of this add node.
	 * @throws EvalException
	 */
	public double op(double o1, double o2) throws EvalException {
		if (addop.equals("+"))
			return o1+o2;
		if (addop.equals("-"))
			return o1-o2;
		throw new EvalException(pos,"bogus addop: "+addop);
	}

	@Override
	public String code() { return String.format(" %s ", addop); }

	@Override
	public void loadEnvironment(Environment env) { }

	@Override
	protected Node[] children() {
        return new Node[]{ };
	}

	@Override
	public String toString() {
        return String.format("addop - '%s'", this.addop);
	}

}
