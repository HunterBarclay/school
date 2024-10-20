/**
 * <pre>
 * Grammar:
 * term: fact mulop term
 *     | fact
 * </pre>
 */
public class NodeTerm extends Node {

	private NodeFact fact;
	private NodeMulop mulop;
	private NodeTerm term;

	/**
	 * @param fact Left-hand factor.
	 * @param mulop Multiplication operation.
	 * @param term Right-hand term.
	 */
	public NodeTerm(NodeFact fact, NodeMulop mulop, NodeTerm term) {
		this.fact=fact;
		this.mulop=mulop;
		this.term=term;
	}

	/**
	 * Append a term to the right-hand side of this term.
	 * 
	 * @param term Term to append.
	 */
	public void append(NodeTerm term) {
		if (this.term==null) {
			this.mulop=term.mulop;
			this.term=term;
			term.mulop=null;
		} else
			this.term.append(term);
	}

	public double eval(Environment env) throws EvalException {
		return term==null
			? fact.eval(env)
			: mulop.op(term.eval(env),fact.eval(env));
	}

	public String code() {
		return (term==null ? "" : term.code()+mulop.code())+fact.code();
	}

	@Override
	protected Node[] children() {
		if (this.term == null) {
			return new Node[]{ this.fact };
		} else {
			return new Node[]{ this.fact, this.mulop, this.term };
		}
	}

	@Override
	public String toString() {
		if (this.term == null) {
			return "term - fact";
		} else {
			return "term - fact mulop term";
		}
	}

}
