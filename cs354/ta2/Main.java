// This is the main class/method for the interpreter/compiler.
// Each command-line argument is a complete program,
// which is scanned, parsed, and evaluated.
// All evaluations share the same environment,
// so they can share variables.

import java.nio.file.Files;
import java.nio.file.Paths;

import java.io.BufferedWriter;
import java.io.FileWriter;

/**
 * Compiler/Interpreter, compiling some unnamed language to C.
 * Each command-line argument is an individual program that shares an
 * environment with each other included program. Each program consists
 * of a single assignment statement for now.
 */
public class Main {

	private static void printUsage() {
		System.err.println(
			"Usage:\n" +
			"$ java Main [--help] <program>...\n"
		);
	}

	public static void main(String[] args) {
		if (args.length == 0 || args[0].equals("--help")) {
			printUsage();
			System.exit(1);
			return;
		}

		if (args.length > 1) {
			System.err.println("Too many arguments.");
			printUsage();
			System.exit(1);
			return;
		}

		String program;
		try {
			program = Files.readString(Paths.get(args[0]));
		} catch (Exception e) {
			System.err.format("Failed to read program file '%s'.\n", args[0]);
			System.exit(1);
			return;
		}

		Parser parser = new Parser();
		Environment env = new Environment();
		Node parseTree;
		try {
			parseTree = parser.parse(program);
			// Dumps tree to text file if env var is set.
			dumpTree(parseTree);
			parseTree.loadEnvironment(env);
			parseTree.eval(env);
		} catch (Exception e) {
			System.err.println(e);
			System.exit(1);
			return;
		}
		new Code(parseTree.code(), env);
	}

	/**
	 * Dumps the parse tree of a node to a text file.
	 * The text file is determined by the contents of
	 * the 'Tree' environment variable.
	 * 
	 * @param parseTree Root node of the parse tree.
	 */
	public static void dumpTree(Node parseTree) {
		String treeFile = System.getenv("Tree");
		if (treeFile != null) {
			try {
				BufferedWriter f = new BufferedWriter(new FileWriter(treeFile));
				f.write(parseTree.tree());
				f.close();
			} catch (Exception e) {
				System.err.println(e);
			}
		}
	}

}
