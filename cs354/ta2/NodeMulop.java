/**
 * <pre>
 * Grammar:
 * mulop: '*'
 *      | '/'
 * </pre>
 */
public class NodeMulop extends Node {

	private String mulop;

	/**
	 * @param pos Position of the node.
	 * @param mulop Multiplication operation.
	 */
	public NodeMulop(int pos, String mulop) {
		this.pos=pos;
		this.mulop=mulop;
	}

	/**
	 * Evaluate the node with given parameters.
	 * 
	 * @param o1 Operand 1.
	 * @param o2 Operand 2.
	 * @return Result of the operation.
	 * @throws EvalException If unable to evaluate the operation.
	 */
	public double op(double o1, double o2) throws EvalException {
		if (mulop.equals("*"))
			return o1*o2;
		if (mulop.equals("/"))
			return o1/o2;
		throw new EvalException(pos,"bogus mulop: " + this.mulop);
	}

	public String code() { return String.format(" %s ", this.mulop); }

	@Override
	public void loadEnvironment(Environment env) { }

	@Override
	protected Node[] children() {
        return new Node[]{ };
	}

	@Override
	public String toString() {
        return String.format("mulop - '%s'", this.mulop);
	}

}
