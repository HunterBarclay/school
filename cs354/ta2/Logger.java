/**
 * Little logger class I made cuz I was bored.
 */
public class Logger {

    /* Disables all logging using this logger. */
    public static final boolean LOG_DISABLED = false;

    /**
     * Print message to error stream with debug prefix.
     * 
     * @param format Format of the message.
     * @param args Optional arguments for format.
     */
    public static void debug(String format, Object... args) {
        if (LOG_DISABLED) return;

        System.err.print("[debug] ");
        System.err.format(format, args);
        System.err.print("\n");
    }

    /**
     * Print message to error stream with error prefix.
     * 
     * @param format Format of the message.
     * @param args Optional arguments for format.
     */
    public static void error(String format, Object... args) {
        if (LOG_DISABLED) return;

        System.err.print("[error] ");
        System.err.format(format, args);
        System.err.print("\n");
    }
}
