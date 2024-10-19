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
        } catch(Exception e) {
            throw new EvalException(this.pos, "Failed to read double.");
        } finally {
            if (sc != null) sc.close();
        }
        return env.put(id, in);
	}

	public String code() {
        return String.format(
            "printf(\"%s < \"); scanf(\"%%lf\", &%s);",
            this.id, this.id
        );
    }

}
