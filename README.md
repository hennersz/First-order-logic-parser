# Parser
A first order lorgic parser
This will parse formulas defined by φ::=X[ts]| −φ|(φ◦φ)|Ezφ|Azφ
The language has no function symbols and one binary predicate symbol ’X’ denoting the edge relation in a graph, so X[xy] means that there is an edge from x to y. A binary connective is a character ’v’,  ’ or ’>’ (denoting or, and, implies). A variable is a character ’x’, ’y’ or ’z’ (three variables should be enough for this coursework). There are no constants and no function symbols, so a term is just a variable.
where ◦ is a binary connective, t, s, z are variables