public class NodeStmtWhile extends NodeStmt {
    NodeBoolExpr boolExpr;
    NodeStmt stmt;

    /**
     * Constructs a while statement.
     * 
     * @param boolExpr Boolean expression to control looping mechanism.
     * @param stmt Statement to execute everytime boolexpr is true.
     */
    public NodeStmtWhile(NodeBoolExpr boolExpr, NodeStmt stmt) {
        this.boolExpr = boolExpr;
        this.stmt = stmt;
    }

    @Override
    public double eval(Environment env) throws EvalException {
        while (this.boolExpr.eval(env) == 1) {
            this.stmt.eval(env);
        }
        return Double.NaN;
	}

    @Override
	public String code() {
        return String.format(
            "while (%s) %s",
            this.boolExpr.code(),
            this.stmt.code()
        );
    }

    @Override
	public void loadEnvironment(Environment env) {
        this.boolExpr.loadEnvironment(env);
        this.stmt.loadEnvironment(env);
    }

    @Override
	protected Node[] children() {
        return new Node[]{ this.boolExpr, this.stmt };
	}

	@Override
	public String toString() {
        return "stmt - 'while' boolexpr 'then' stmt";
	}

}
