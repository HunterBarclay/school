public class NodeFactNum extends NodeFact {

	private String num;

	/**
	 * @param num Numeric constant.
	 */
	public NodeFactNum(String num) {
		this.num=num;
	}

	@Override
	public double eval(Environment env) throws EvalException {
		return Double.parseDouble(this.num);
	}

	@Override
	public String code() { return this.num.contains(".") ? this.num : this.num + ".0"; }

	@Override
	public void loadEnvironment(Environment env) { }

	@Override
	protected Node[] children() {
        return new Node[]{ };
	}

	@Override
	public String toString() {
        return String.format("fact - '%s'", this.num);
	}

}
