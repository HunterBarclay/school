public class NodeFactNeg extends NodeFact {

	private NodeFact fact;

	/**
	 * @param fact Factor to negate.
	 */
	public NodeFactNeg(NodeFact fact) {
		this.fact=fact;
	}

	@Override
	public double eval(Environment env) throws EvalException {
		return -this.fact.eval(env);
	}

	@Override
	public String code() { return "-"+this.fact.code(); }

	@Override
	public void loadEnvironment(Environment env) {
        this.fact.loadEnvironment(env);
    }

	@Override
	protected Node[] children() {
        return new Node[]{ this.fact };
	}

	@Override
	public String toString() {
        return "fact - '-' fact";
	}

}
