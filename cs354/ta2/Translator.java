import java.util.HashMap;

public class Translator {

    private static HashMap<String, String> cTranslations = new HashMap<String, String>();

    private Translator() { }

    public static Token translate(Token t) {
        ensureCTranslations();
        String translation = cTranslations.get(t.lex());
        return translation == null ? t : new Token(t.tok(), translation);
    }

    public static String translate(String s) {
        ensureCTranslations();
        String translation = cTranslations.get(s);
        return translation == null ? s : translation;
    }

    private static void ensureCTranslations() {
        if (Translator.cTranslations != null)
            return;

        cTranslations.put("<>", "!=");
    }
}
