// This is the main class/method for the interpreter/compiler.
// Each command-line argument is a complete program,
// which is scanned, parsed, and evaluated.
// All evaluations share the same environment,
// so they can share variables.

/**
 * Compiler/Interpreter, compiling some unnamed language to C.
 * Each command-line argument is an individual program that shares an
 * environment with each other included program. Each program consists
 * of a single assignment statement for now.
 */
public class Main {

	private static void printUsage() {
		System.out.println(
			"Usage:\n" +
			"$ java Main [--help] <program>...\n"
		);
	}

	public static void main(String[] args) {
		if (args.length == 0 || args[0].equals("--help")) {
			printUsage();
			return;
		}

		Parser parser = new Parser();
		Environment env = new Environment();
		String code = "";
		for (String prog : args)
			try {
				Node node = parser.parse(prog);
				node.eval(env);
				code += node.code();
			} catch (Exception e) {
				System.err.println(e);
			}
		new Code(code, env);
	}

}
