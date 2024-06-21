A simple tool for checking if a word or phrase is a `@p` substring (a
string whose letters form a substring of some legitimate `@p`).

`make` produces two executables:

* `bin/names`: Test each argument for legitimacy as a `@p` substring. If
no arguments are provided, read them from standard input.
* `bin/test`: Run a test suite.

If your system has a dictionary file, such as `/usr/share/dict/words`,
you may generate a large list of `@p` substrings by running:

    `bin/names < /usr/share/dict/words`

Fuzzy matches coming soon.
