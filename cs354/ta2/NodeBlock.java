public class NodeBlock extends Node {

    public NodeStmt stmt;
    public NodeBlock block;

    public NodeBlock(NodeStmt stmt, NodeBlock block) {
        this.stmt = stmt;
        this.block = block;
    }

    public void append(NodeBlock block) {
        if (this.block == null) {
            this.block = block;
        } else {
            this.block.append(block);
        }
    }

    @Override
	public double eval(Environment env) throws EvalException {
		double val = this.stmt.eval(env);
        if (this.block != null) {
            val = this.block.eval(env);
        }
        // Eh, why not.
        return val;
	}

	@Override
	public String code() {
        StringBuilder builder = new StringBuilder();
        builder.append("{ ");
        this.buildStatements(builder);
        builder.append("}");
        return builder.toString();
	}

	private void buildStatements(StringBuilder builder) {
        builder.append(this.stmt.code());
        builder.append(" ");
        if (this.block != null) {
            this.block.buildStatements(builder);
        }
	}
}
