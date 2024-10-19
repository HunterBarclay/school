import java.text.DecimalFormat;

public class NodeStmtWr extends NodeStmt {

    NodeExpr expr;

    public NodeStmtWr(NodeExpr expr) {
        this.expr = expr;
    }

    public double eval(Environment env) throws EvalException {
        double val = expr.eval(env);
        DecimalFormat formatter = new DecimalFormat("0.#####");
        System.out.format("> %s\n", formatter.format(val));
        return val;
	}

	public String code() {
        return String.format(
            "printf(\"> %%g\\n\", %s);",
            this.expr.code()
        );
    }
}
