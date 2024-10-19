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
        java.util.Scanner sc = null;
        try {
            System.out.format("%s < ", this.id);
            sc = new java.util.Scanner(System.in);
            in = sc.nextDouble();
            System.out.print("\n");
        } catch(Exception e) {
            throw new EvalException(this.pos, "Failed to read double.");
        } finally {
            if (sc != null) sc.close();
        }
        return env.put(id, in);
	}

	public String code() {
        return String.format(
            "printf(\"%s < \"); scanf(\"%%lf\", &%s); printf(\"\\n\");",
            this.id, this.id
        );
    }

}
