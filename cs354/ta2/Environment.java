/**
 * Establish an environment in the program. This stores variables inside the program,
 * generating initializers for them and holding current value when evaluating the program.
 * 
 * @author Hunter Barclay, James Buffenbarger
 */

import java.util.HashMap;
import java.util.Map;

/**
 * Establish an environment of variables within a program.
 */
public class Environment {

	private java.util.Scanner m_scanner;
	private Map<String, Double> m_double_map = new HashMap<String, Double>();

	public Environment() {
		this.m_scanner = new java.util.Scanner(System.in);
	}

	/**
	 * Assigns value to a given variable.
	 * 
	 * @param var Variable name.
	 * @param val Value to assign to variable.
	 * @return Value assigned to variable.
	 */
	public double put(String var, double val) {
		m_double_map.put(var, val);
		return val;
	}

	/**
	 * Get the value of a stored variable.
	 * 
	 * @param pos Position of retrieval in code. Used for errors.
	 * @param var Variable name.
	 * @return Value within variable var.
	 * @throws EvalException If no variable with name var exists.
	 */
	public double get(int pos, String var) throws EvalException {
		if (!m_double_map.containsKey(var))
			throw new EvalException(pos, String.format("'%s' is undefined.", var));

		return m_double_map.get(var);
	}

	/**
	 * Generate double initializers.
	 * 
	 * @param builder String builder.
	 */
	private void doublesToC(StringBuilder builder) {
		for (String id : m_double_map.keySet()) {
			builder.append("double ");
			builder.append(id);
			builder.append(" = 0;\n");
		}
	}

	/**
	 * Generate C code for environment. This includes variable initializations.
	 * 
	 * @return Generate C code.
	 */
	public String toC() {
		StringBuilder builder = new StringBuilder();
		doublesToC(builder);
		return builder.toString();
	}

	public double readDouble() {
		return this.m_scanner.nextDouble();
	}

}
