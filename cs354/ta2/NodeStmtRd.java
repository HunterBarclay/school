/**
 * Read statement. I've decided to print a newline out after receiving input
 * for consistency when piping in input.
 */
public class NodeStmtRd extends NodeStmt {

    private int pos;
    private String id;

    public NodeStmtRd(int pos, String id) {
        this.pos = pos;
        this.id = id;
    }

    public double eval(Environment env) throws EvalException {
        double in = 0;
        try {
            System.out.format("%s < ", this.id);
            in = env.readDouble();
            System.out.print("\n");
            Logger.debug("Read in '%f'", in);
        } catch(Exception e) {
            e.printStackTrace(System.err);
            throw new EvalException(this.pos, "Failed to read double.");
        }
        return env.put(id, in);
	}

	public String code() {
        return String.format(
            "printf(\"%s < \"); scanf(\"%%lf\", &%s); printf(\"\\n\");",
            this.id, this.id
        );
    }

    @Override
    public void loadEnvironment(Environment env) {
		Logger.debug("Preloading id %s", id);
        env.put(id, 0);
    }

    @Override
	protected Node[] children() {
        return new Node[]{ };
	}

	@Override
	public String toString() {
        return String.format("stmt - 'rd' '%s'", this.id);
	}

}
