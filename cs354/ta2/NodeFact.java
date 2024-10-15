/**
 * Factor node.
 * 
 * <pre>
 * Grammar:
 * fact: id
 *     | num
 *     | '(' expr ')'
 *     | '-' fact
 * </pre>
 */
public abstract class NodeFact extends Node {}
