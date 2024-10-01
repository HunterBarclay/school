public class Logger {

    public static final boolean LOG_DISABLED = false;

    public static void debug(String format, Object... args) {
        if (LOG_DISABLED) return;

        System.err.print("[debug] ");
        System.err.format(format, args);
        System.err.print("\n");
    }

    public static void error(String format, Object... args) {
        if (LOG_DISABLED) return;

        System.err.print("[error] ");
        System.err.format(format, args);
        System.err.print("\n");
    }
}
