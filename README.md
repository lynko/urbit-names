A simple tool for checking if a word or phrase is a `@p` substring (a
string whose letters form a substring of some legitimate `@p`).

`make` produces two executables:

* `bin/names`: Test each argument for legitimacy as a `@p` substring. If
no arguments are provided, read them from standard input.
* `bin/test`: Run a test suite.

`make` also produces [patp.txt], which contains every word from your
`/usr/share/dict/words` that's a `@p` substring. The provided `patp.txt`
is based on the dictionary from my own machine. To rebuild this file
from your own dictionary, run `rm patp.txt` and then `make patp.txt`.

Lines longer than 64 characters will be ignored when reading from the
standard input. Non-ASCII characters, including Unicode characters, are
excluded from the matching procedure, which may result in false
positives for words such as *épée*.

Inexact matching is coming soon (e.g. `~midnyt` is a reasonable match
for *midnight*).
