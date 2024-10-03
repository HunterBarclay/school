import java.io.*;

/**
 * Class used for constructing the C file from generated code
 * provided by the Nodes as well as the environment.
 *
 * @author James Buffenbarger
 */
public class Code {

	private final String[] prologue = {
			"#include <stdio.h>",
			"int main() {",
	};

	private final String[] epilogue = {
			"return 0;",
			"}",
	};

	/**
	 * Construct and write out the generated C file for the program.
	 * It will write the generated file to the path stored in the "Code"
	 * environment variable. If the "Code" environment variable is not set,
	 * it will skip writing and constructing the generated file.
	 *
	 * Upon error, exception will be dumped to the error stream.
	 *
	 * @param code Code generated from a Node.
	 * @param env Environment structure, used to generate variable definitions.
	 */
	public Code(String code, Environment env) {
		String fn = System.getenv("Code");
		if (fn == null)
			return;
		try {
			BufferedWriter f = new BufferedWriter(new FileWriter(fn + ".c"));
			for (String s : prologue)
				f.write(s + "\n");
			f.write(env.toC());
			f.write(code);
			for (String s : epilogue)
				f.write(s + "\n");
			f.close();
		} catch (Exception e) {
			System.err.println(e);
		}
	}

}
