public class NodeStmtWhile extends NodeStmt {
    NodeBoolExpr boolExpr;
    NodeStmt stmt;

    public NodeStmtWhile(NodeBoolExpr boolExpr, NodeStmt stmt) {
        this.boolExpr = boolExpr;
        this.stmt = stmt;
    }

    public double eval(Environment env) throws EvalException {
        while (this.boolExpr.eval(env) == 1) {
            this.stmt.eval(env);
        }
        return Double.NaN;
	}

	public String code() {
        return String.format(
            "while (%s) %s",
            this.boolExpr.code(),
            this.stmt.code()
        );
    }
}
