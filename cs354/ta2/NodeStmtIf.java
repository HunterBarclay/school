public class NodeStmtIf extends NodeStmt {
    
    NodeBoolExpr boolExpr;
    NodeStmt stmtTrue, stmtFalse;

    public NodeStmtIf(NodeBoolExpr boolExpr, NodeStmt stmtTrue, NodeStmt stmtFalse) {
        this.boolExpr = boolExpr;
        this.stmtTrue = stmtTrue;
        this.stmtFalse = stmtFalse;
    }

    public double eval(Environment env) throws EvalException {
        if (this.boolExpr.eval(env) == 1) {
            return this.stmtTrue.eval(env);
        } else if (this.stmtFalse != null) {
            return this.stmtFalse.eval(env);
        }
        return Double.NaN;
	}

	public String code() {
        if (this.stmtFalse == null) {
            return String.format(
                "if (%s) %s",
                this.boolExpr.code(),
                this.stmtTrue.code()
            );
        } else {
            return String.format(
                "if (%s) %s else %s",
                this.boolExpr.code(),
                this.stmtTrue.code(),
                this.stmtFalse.code()
            );
        }
    }
}
