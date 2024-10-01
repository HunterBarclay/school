public class NodeFactNeg extends NodeFact {

	private NodeFact fact;

	public NodeFactNeg(NodeFact fact) {
		this.fact=fact;
	}

	public double eval(Environment env) throws EvalException {
		return -fact.eval(env);
	}

	public String code() { return "-"+fact.code(); }

}
