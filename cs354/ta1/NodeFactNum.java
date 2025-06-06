public class NodeFactNum extends NodeFact {

	private String num;

	/**
	 * @param num Numeric constant.
	 */
	public NodeFactNum(String num) {
		this.num=num;
	}

	public double eval(Environment env) throws EvalException {
		return Double.parseDouble(num);
	}

	public String code() { return num.contains(".") ? num : num + ".0"; }

}
