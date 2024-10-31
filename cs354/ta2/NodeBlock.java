/**
 * Block node.
 * 
 * <pre>
 * Grammar:
 * block: stmt ';' block
 *      | stmt
 * <pre>
 */
public class NodeBlock extends Node {

    public NodeStmt stmt;
    public NodeBlock block;

    public NodeBlock(NodeStmt stmt, NodeBlock block) {
        this.stmt = stmt;
        this.block = block;
    }

    /**
     * Append a new block on to this block. Will bubble
     * down to the end.
     * 
     * @param block New block to add.
     */
    public void append(NodeBlock block) {
        if (this.block == null) {
            this.block = block;
        } else {
            this.block.append(block);
        }
    }

    @Override
	public void loadEnvironment(Environment env) {
        this.stmt.loadEnvironment(env);
        if (this.block != null) this.block.loadEnvironment(env);
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

    /**
     * Constructs the statements C code.
     * 
     * @param builder String builder to store final C code.
     */
	private void buildStatements(StringBuilder builder) {
        builder.append(this.stmt.code());
        builder.append(" ");
        if (this.block != null) {
            this.block.buildStatements(builder);
        }
	}

    @Override
	protected Node[] children() {
        if (this.block == null) {
            return new Node[]{ this.stmt };
        } else {
            return new Node[]{ this.stmt, this.block };
        }
	}

	@Override
	public String toString() {
        if (this.block == null) {
            return "block - stmt";
        } else {
            return "block - stmt ';' block";
        }
	}

}
