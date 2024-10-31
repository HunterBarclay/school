import java.util.HashMap;

/**
 * Utility class for translating certain Grammar defined operators
 * to their C counterparts.
 */
public class Translator {

    // Direct lexeme translations
    private HashMap<String, String> m_translations;

    /**
     * Singleton constructor. Adds translations.
     */
    private Translator() {
        this.m_translations = new HashMap<String, String>();
        this.m_translations.put("<>", "!=");
    }

    /**
     * Translates the lexeme of a token to the corresponding
     * C lexeme.
     * 
     * @param t Token to translate.
     * @return Token with same id, but translated lexeme, if one
     *      exists. Otherwise, same lexeme.
     */
    public Token translate(Token t) {
        String translation = this.m_translations.get(t.lex());
        return translation == null ? t : new Token(t.tok(), translation);
    }

    /**
     * Translate a lexeme to it's corresponding C lexeme.
     * 
     * @param s Target lexeme.
     * @return C lexeme.
     */
    public String translate(String s) {
        String translation = this.m_translations.get(s);
        if (translation == null) {
            Logger.debug("RELOP: No translation");
        } else {
            Logger.debug("RELOP: Translation Found: %s", translation);
        }
        return translation == null ? s : translation;
    }

    private static Translator s_instance = null;
    public static Translator getInstance() {
        if (s_instance == null)
            s_instance = new Translator();
        return s_instance;
    }
}
