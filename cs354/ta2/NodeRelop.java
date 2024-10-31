/**
 * Relational Operator node.
 * 
 * <pre>
 * Grammar:
 * relop: '<'
 *      | '<='
 *      | '>'
 *      | '>='
 *      | '<>'
 *      | '=='
 * <pre>
 */
public class NodeRelop extends Node {
    
	private String relop;

	/**
	 * @param pos Position of the node.
	 * @param mulop Multiplication operation.
	 */
	public NodeRelop(int pos, String relop) {
		this.pos = pos;
		this.relop = relop;
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
		if (this.relop.equals("<"))
			return o1 < o2 ? 1 : 0;
		if (this.relop.equals("<="))
			return o1 <= o2 ? 1 : 0;
        if (this.relop.equals(">"))
            return o1 > o2 ? 1 : 0;
        if (this.relop.equals(">="))
            return o1 >= o2 ? 1 : 0;
        if (this.relop.equals("<>"))
            return o1 != o2 ? 1 : 0;
        if (this.relop.equals("=="))
            return o1 == o2 ? 1 : 0;
        throw new EvalException(
            this.pos,
            String.format("Invalid relational operator: '%s'", this.relop)
        );
	}

	@Override
	public String code() {
        return Translator.getInstance().translate(this.relop);
    }

	@Override
	public void loadEnvironment(Environment env) { }

	@Override
	protected Node[] children() {
        return new Node[]{ };
	}

	@Override
	public String toString() {
        return String.format("relop - '%s'", this.relop);
	}

}
