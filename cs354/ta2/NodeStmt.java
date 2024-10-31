/**
 * <pre>
 * Grammar:
 * stmt: assn
 *     | 'rd' id
 *     | 'wr' expr
 *     | 'if' boolexpr 'then' stmt
 *     | 'if' boolexpr 'then' stmt 'else' stmt
 *     | 'while' boolexpr 'do' stmt
 *     | 'begin' block 'end'
 * </pre>
 */
public abstract class NodeStmt extends Node { }
