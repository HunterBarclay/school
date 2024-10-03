/**
 * Evaluation Exception, encountered when a node fails
 * to evaluate it's syntax tree.
 *
 * @author James Buffenbarger
 */
public class EvalException extends Exception {

	private int pos;
	private String msg;

	/**
	 * Constructs an EvalException
	 *
	 * @param pos Position in the source file of evaluation error.
	 * @param msg Accompanying message, detailing the error.
	 */
	public EvalException(int pos, String msg) {
		this.pos=pos;
		this.msg=msg;
	}

	@Override
	public String toString() {
		return "eval error"
			+", pos="+pos
			+", "+msg;
	}

}
