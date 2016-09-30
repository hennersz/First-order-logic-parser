# Parser
A first order lorgic parser

If you are a first year UCL student doing your logic coursework and found this useful consider starring it.

This will parse formulas defined by 
φ::=X[ts]| −φ|(φ◦φ)|Ezφ|Azφ
where ◦ is a binary connective, t, s, z are variables. E and A are the unversal quantifiers.

The language has no function symbols and one binary predicate symbol ’X’ denoting the edge relation in a graph, so X[xy] means that there is an edge from x to y. A binary connective is a character ’v’, '^’ or ’>’ (denoting or, and, implies). A variable is a character ’x’, ’y’ or ’z’ (three variables should be enough for this coursework). There are no constants and no function symbols, so a term is just a variable.
