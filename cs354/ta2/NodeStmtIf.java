public class NodeStmtIf extends NodeStmt {
    
    NodeBoolExpr boolExpr;
    NodeStmt stmtTrue, stmtFalse;

    /**
     * Construct an if statement node.
     * 
     * @param boolExpr Boolean expression to determine path of
     *      execution.
     * @param stmtTrue Statement to execute when boolexpr is true.
     * @param stmtFalse Statement to execute when boolexpr is false.
     */
    public NodeStmtIf(NodeBoolExpr boolExpr, NodeStmt stmtTrue, NodeStmt stmtFalse) {
        this.boolExpr = boolExpr;
        this.stmtTrue = stmtTrue;
        this.stmtFalse = stmtFalse;
    }

    @Override
    public double eval(Environment env) throws EvalException {
        if (this.boolExpr.eval(env) == 1) {
            return this.stmtTrue.eval(env);
        } else if (this.stmtFalse != null) {
            return this.stmtFalse.eval(env);
        }
        return Double.NaN;
	}

    @Override
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

    @Override
	public void loadEnvironment(Environment env) {
        this.boolExpr.loadEnvironment(env);
        this.stmtTrue.loadEnvironment(env);
        if (this.stmtFalse != null)
            this.stmtFalse.loadEnvironment(env);
    }

    @Override
	protected Node[] children() {
        if (this.stmtFalse == null) {
            return new Node[]{ this.boolExpr, this.stmtTrue };
        } else {
            return new Node[]{ this.boolExpr, this.stmtTrue, this.stmtFalse };
        }
	}

	@Override
	public String toString() {
        if (this.stmtFalse == null) {
            return "stmt - 'if' boolexpr 'then' stmt";
        } else {
            return "stmt - 'if' boolexpr 'then' stmt 'else' stmt";
        }
	}

}
